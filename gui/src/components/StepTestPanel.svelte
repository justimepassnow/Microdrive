<!-- src/components/StepTestPanel.svelte -->
<script>
    import { onMount, tick } from 'svelte';
    import Dropdown from './Dropdown.svelte';

    let { 
        isConnected = false, 
        activeId = null, 
        telemetry = {}, 
        config = null, 
        sendCommand,
        addLog,
        targetVelocity = $bindable(0),
        targetCurrent = $bindable(0)
    } = $props();

    let stepSize = $state(60);
    let testDuration = $state(1500); // ms
    let isTesting = $state(false);
    let showGuide = $state(true);
    
    let metrics = $state(null);
    let canvasEl = $state(null);
    
    let stepData = [];
    let startTime = null;
    let startAngleRecorded = null;
    let targetAngleRecorded = null;
    let localPollInterval = null;

    // Watch telemetry updates during testing
    $effect(() => {
        if (isTesting && telemetry && startTime !== null) {
            const elapsed = Date.now() - startTime;
            // Record sample
            stepData.push({
                time: elapsed,
                actual: telemetry.angle,
                target: targetAngleRecorded
            });
        }
    });

    function runStepTest() {
        if (!isConnected || activeId === null || isTesting) return;

        stepData = [];
        metrics = null;
        isTesting = true;
        
        startAngleRecorded = telemetry.angle;
        
        // Retrieve travel limits from config (fall back to safe default bounds if config unavailable)
        const minLim = config ? (config.min_angle ?? 0) : 0;
        const maxLim = config ? (config.max_angle ?? 360) : 360;

        let activeStepSize = stepSize;
        let targetVal = startAngleRecorded + activeStepSize;

        // Auto-invert step direction if it would exceed limits, otherwise clamp
        if (targetVal > maxLim) {
            const invertedTarget = startAngleRecorded - activeStepSize;
            if (invertedTarget >= minLim && invertedTarget <= maxLim) {
                activeStepSize = -activeStepSize;
                targetVal = invertedTarget;
                addLog('sys', `Target exceeds max limit (${maxLim}°). Auto-inverting step direction to ${activeStepSize}°.`);
            } else {
                targetVal = maxLim;
                activeStepSize = targetVal - startAngleRecorded;
                addLog('sys', `Target exceeds max limit. Clamping step delta to ${activeStepSize}°.`);
            }
        } else if (targetVal < minLim) {
            const invertedTarget = startAngleRecorded - activeStepSize;
            if (invertedTarget >= minLim && invertedTarget <= maxLim) {
                activeStepSize = -activeStepSize;
                targetVal = invertedTarget;
                addLog('sys', `Target falls below min limit (${minLim}°). Auto-inverting step direction to +${activeStepSize}°.`);
            } else {
                targetVal = minLim;
                activeStepSize = targetVal - startAngleRecorded;
                addLog('sys', `Target falls below min limit. Clamping step delta to ${activeStepSize}°.`);
            }
        }

        targetAngleRecorded = targetVal;
        
        addLog('sys', `Step Test triggered: ${startAngleRecorded}° -> ${targetAngleRecorded}° (True Step: ${activeStepSize}°)`);
        
        // Execute step command
        sendCommand({
            cmd: 'move',
            id: activeId,
            angle: Math.round(targetAngleRecorded),
            velocity: targetVelocity,
            current: targetCurrent
        });

        startTime = Date.now();

        // High frequency poll loop (25Hz / 40ms) for step response measurement
        localPollInterval = setInterval(() => {
            sendCommand({ cmd: 'poll', id: activeId });
        }, 40);

        // Stop test after duration
        setTimeout(() => {
            if (localPollInterval) {
                clearInterval(localPollInterval);
                localPollInterval = null;
            }
            isTesting = false;
            analyzeStepData();

            // Safety reset: return actuator back to its pre-test start position
            addLog('sys', `Step test completed. Returning actuator back to ${startAngleRecorded}°...`);
            sendCommand({
                cmd: 'move',
                id: activeId,
                angle: Math.round(startAngleRecorded),
                velocity: targetVelocity,
                current: targetCurrent
            });
        }, testDuration);
    }

    function analyzeStepData() {
        if (stepData.length < 5) {
            addLog('error', 'Completed Step Test but collected insufficient telemetry samples.');
            return;
        }

        const totalStep = targetAngleRecorded - startAngleRecorded;
        if (Math.abs(totalStep) < 3) {
            addLog('sys', 'Step size too small to calculate PID response metrics.');
            return;
        }

        // 1. Overshoot calculation
        let maxActual = startAngleRecorded;
        let overshootPct = 0;
        
        if (totalStep > 0) {
            maxActual = Math.max(...stepData.map(d => d.actual));
            overshootPct = ((maxActual - targetAngleRecorded) / totalStep) * 100;
        } else {
            maxActual = Math.min(...stepData.map(d => d.actual));
            overshootPct = ((targetAngleRecorded - maxActual) / Math.abs(totalStep)) * 100;
        }
        overshootPct = Math.max(0, overshootPct);

        // 2. Rise Time (10% to 90% of final command step)
        const y10 = startAngleRecorded + 0.1 * totalStep;
        const y90 = startAngleRecorded + 0.9 * totalStep;
        
        let t10 = null;
        let t90 = null;

        for (let pt of stepData) {
            if (totalStep > 0) {
                if (t10 === null && pt.actual >= y10) t10 = pt.time;
                if (t90 === null && pt.actual >= y90) t90 = pt.time;
            } else {
                if (t10 === null && pt.actual <= y10) t10 = pt.time;
                if (t90 === null && pt.actual <= y90) t90 = pt.time;
            }
        }

        const riseTime = (t10 !== null && t90 !== null) ? (t90 - t10) : null;

        // 3. Settling Time (remains within 3% tolerance band of step size)
        const settleBand = 0.03 * Math.abs(totalStep);
        let tSettled = null;
        let lastIdxOutside = -1;

        for (let i = stepData.length - 1; i >= 0; i--) {
            if (Math.abs(stepData[i].actual - targetAngleRecorded) > settleBand) {
                lastIdxOutside = i;
                break;
            }
        }

        if (lastIdxOutside === -1) {
            tSettled = stepData[0].time;
        } else if (lastIdxOutside < stepData.length - 1) {
            tSettled = stepData[lastIdxOutside + 1].time;
        } else {
            tSettled = null; // did not settle in time limit
        }

        // 4. Steady-state error
        const lastSample = stepData[stepData.length - 1];
        const steadyError = Math.abs(lastSample.actual - targetAngleRecorded);

        metrics = {
            overshoot: Math.round(overshootPct * 10) / 10,
            riseTime: riseTime,
            settlingTime: tSettled,
            steadyError: Math.round(steadyError * 10) / 10
        };

        addLog('sys', `PID Metrics — Overshoot: ${metrics.overshoot}%, Rise: ${metrics.riseTime ?? 'N/A'}ms, Settle: ${metrics.settlingTime ?? 'N/A'}ms, SSE: ${metrics.steadyError}°`);

        drawChart();
    }

    function drawChart() {
        if (!canvasEl) return;
        
        const ctx = canvasEl.getContext('2d');
        const dpr = window.devicePixelRatio || 1;
        const W = canvasEl.width / dpr;
        const H = canvasEl.height / dpr;

        // Reset scale transform and clear logical area
        ctx.setTransform(1, 0, 0, 1, 0, 0);
        ctx.scale(dpr, dpr);

        ctx.fillStyle = '#1c1c1e';
        ctx.fillRect(0, 0, W, H);

        if (stepData.length < 2) return;

        // Compute dynamic Y scaling range
        const allAngles = [...stepData.map(d => d.actual), startAngleRecorded, targetAngleRecorded];
        let minAngle = Math.min(...allAngles);
        let maxAngle = Math.max(...allAngles);
        let range = maxAngle - minAngle;
        if (range === 0) range = 10;
        
        // Add padding
        minAngle -= 0.15 * range;
        maxAngle += 0.15 * range;
        const totalYRange = maxAngle - minAngle;

        const getY = (val) => {
            const paddingTop = 20;
            const paddingBottom = 25;
            return H - paddingBottom - ((val - minAngle) / totalYRange) * (H - paddingTop - paddingBottom);
        };

        const getX = (timeMs) => {
            const paddingRight = 20;
            const paddingLeft = 45;
            return paddingLeft + (timeMs / testDuration) * (W - paddingLeft - paddingRight);
        };

        // Draw horizontal grid lines
        ctx.strokeStyle = 'rgba(255, 255, 255, 0.05)';
        ctx.lineWidth = 1;
        ctx.fillStyle = 'rgba(148, 163, 184, 0.6)';
        ctx.font = '10px system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif';
        ctx.textAlign = 'right';

        const gridDivisions = 4;
        for (let i = 0; i <= gridDivisions; i++) {
            const val = minAngle + (totalYRange / gridDivisions) * i;
            const y = getY(val);
            
            ctx.beginPath();
            ctx.moveTo(getX(0), y);
            ctx.lineTo(getX(testDuration), y);
            ctx.stroke();

            ctx.fillText(`${Math.round(val)}°`, 38, y + 3);
        }

        // Draw vertical grid lines (every 250ms)
        ctx.textAlign = 'center';
        for (let t = 0; t <= testDuration; t += 250) {
            const x = getX(t);
            ctx.beginPath();
            ctx.moveTo(x, getY(maxAngle));
            ctx.lineTo(x, getY(minAngle));
            ctx.stroke();

            ctx.fillText(`${t}ms`, x, H - 8);
        }

        // Draw target angle step response (Soft Orange Dashed)
        ctx.strokeStyle = '#FF9F0A';
        ctx.lineWidth = 1.5;
        ctx.setLineDash([4, 4]);
        ctx.beginPath();
        // Starts at 0ms at startAngle
        ctx.moveTo(getX(0), getY(startAngleRecorded));
        // Instantly steps to targetAngle at 0ms
        ctx.lineTo(getX(0), getY(targetAngleRecorded));
        ctx.lineTo(getX(testDuration), getY(targetAngleRecorded));
        ctx.stroke();
        ctx.setLineDash([]);

        // Draw actual angle response curve (Accent Blue with glow)
        ctx.strokeStyle = '#0A84FF';
        ctx.lineWidth = 2.5;
        ctx.shadowColor = 'rgba(10, 132, 255, 0.35)';
        ctx.shadowBlur = 5;
        ctx.beginPath();
        
        stepData.forEach((pt, idx) => {
            const x = getX(pt.time);
            const y = getY(pt.actual);
            if (idx === 0) ctx.moveTo(getX(0), getY(startAngleRecorded));
            ctx.lineTo(x, y);
        });
        ctx.stroke();
        ctx.shadowBlur = 0; // reset
    }

    onMount(() => {
        // Setup initial sizes for high-DPI scaling
        if (canvasEl) {
            const rect = canvasEl.parentElement.getBoundingClientRect();
            const dpr = window.devicePixelRatio || 1;
            canvasEl.width = rect.width * dpr;
            canvasEl.height = 320 * dpr;
            canvasEl.style.width = `${rect.width}px`;
            canvasEl.style.height = `320px`;

            const ctx = canvasEl.getContext('2d');
            ctx.setTransform(1, 0, 0, 1, 0, 0);
            ctx.scale(dpr, dpr);
            ctx.fillStyle = '#1c1c1e';
            ctx.fillRect(0, 0, rect.width, 320);
            
            ctx.fillStyle = 'rgba(148, 163, 184, 0.4)';
            ctx.font = '12px system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif';
            ctx.textAlign = 'center';
            ctx.fillText('Awaiting step test execution...', rect.width / 2, 160);
        }

        const resizeObserver = new ResizeObserver(() => {
            if (canvasEl) {
                const rect = canvasEl.parentElement.getBoundingClientRect();
                const dpr = window.devicePixelRatio || 1;
                canvasEl.width = rect.width * dpr;
                canvasEl.height = 320 * dpr;
                canvasEl.style.width = `${rect.width}px`;
                canvasEl.style.height = `320px`;
                
                if (stepData.length > 0) {
                    drawChart();
                } else {
                    const ctx = canvasEl.getContext('2d');
                    ctx.setTransform(1, 0, 0, 1, 0, 0);
                    ctx.scale(dpr, dpr);
                    ctx.fillStyle = '#1c1c1e';
                    ctx.fillRect(0, 0, rect.width, 320);
                    ctx.fillStyle = 'rgba(148, 163, 184, 0.4)';
                    ctx.font = '12px system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif';
                    ctx.textAlign = 'center';
                    ctx.fillText('Awaiting step test execution...', rect.width / 2, 160);
                }
            }
        });
        resizeObserver.observe(canvasEl.parentElement);

        return () => {
            resizeObserver.disconnect();
            if (localPollInterval) clearInterval(localPollInterval);
        };
    });
</script>

<div class="step-panel glass-subpanel">
    <div class="panel-header">
        <h3>Step Response Grapher</h3>
        <span class="control-badge" class:active={isConnected}>
            {isTesting ? 'Running Test…' : 'Ready'}
        </span>
    </div>

    <div class="step-dashboard">
        <!-- Configuration & Trigger -->
        <div class="step-controls">
            <div class="control-group">
                <span class="lbl">Step Delta</span>
                <div class="button-toggle-row">
                    <button class="toggle-btn" class:active={stepSize === -90} onclick={() => stepSize = -90} disabled={isTesting}>-90°</button>
                    <button class="toggle-btn" class:active={stepSize === -30} onclick={() => stepSize = -30} disabled={isTesting}>-30°</button>
                    <button class="toggle-btn" class:active={stepSize === 30} onclick={() => stepSize = 30} disabled={isTesting}>+30°</button>
                    <button class="toggle-btn" class:active={stepSize === 90} onclick={() => stepSize = 90} disabled={isTesting}>+90°</button>
                </div>
                
                <div class="custom-step-input">
                    <label for="custom-step">Custom Step size</label>
                    <div class="input-wrap">
                        <input type="number" id="custom-step" min="-180" max="180" bind:value={stepSize} disabled={isTesting} />
                        <span class="input-unit">°</span>
                    </div>
                </div>
            </div>

            <div class="control-group">
                <span class="lbl">Test Duration</span>
                <Dropdown 
                    value={testDuration}
                    options={[
                        { value: 1000, label: "1000 ms (1.0s)" },
                        { value: 1500, label: "1500 ms (1.5s)" },
                        { value: 2000, label: "2000 ms (2.0s)" }
                    ]}
                    onChange={(val) => testDuration = val}
                    disabled={isTesting}
                />
            </div>

            <div class="control-group">
                <div class="slider-label-row">
                    <span class="lbl">Velocity</span>
                    <span class="val-highlight">{targetVelocity === 0 ? 'Default' : `${targetVelocity} °/s`}</span>
                </div>
                <div class="slider-wrap-custom">
                    <input 
                        type="range" 
                        min="0" 
                        max="1000" 
                        step="10"
                        bind:value={targetVelocity} 
                        disabled={isTesting || !isConnected}
                    />
                    <div class="slider-fill-custom velocity" style="width: {(targetVelocity / 1000) * 100}%"></div>
                </div>
                <span class="hint">0 = default speed</span>
            </div>

            <div class="control-group">
                <div class="slider-label-row">
                    <span class="lbl">Force Limit</span>
                    <span class="val-highlight">{targetCurrent === 0 ? 'Default' : `${targetCurrent} mA`}</span>
                </div>
                <div class="slider-wrap-custom">
                    <input 
                        type="range" 
                        min="0" 
                        max={config?.current_limit || 500} 
                        step="10"
                        bind:value={targetCurrent} 
                        disabled={isTesting || !isConnected}
                    />
                    <div class="slider-fill-custom current" style="width: {targetCurrent === 0 ? 0 : (targetCurrent / (config?.current_limit || 500)) * 100}%"></div>
                </div>
                <span class="hint">0 = default limit</span>
            </div>

            <button class="btn primary full-width run-test-btn" onclick={runStepTest} disabled={!isConnected || activeId === null || isTesting}>
                {#if isTesting}
                    <span class="test-spinner"></span>
                    Testing PID Response…
                {:else}
                    Trigger Step Response
                {/if}
            </button>
        </div>

        <!-- Realtime / Analyzed Step Plot -->
        <div class="step-plot-container">
            <div class="chart-legend">
                <span class="legend-item target">
                    <span class="color-dot target"></span> Command Step
                </span>
                <span class="legend-item actual">
                    <span class="color-dot actual"></span> Encoder Response
                </span>
            </div>
            
            <div class="canvas-container">
                <canvas bind:this={canvasEl}></canvas>
            </div>
        </div>
    </div>

    <!-- Output Metrics Grid -->
    {#if metrics}
        <div class="metrics-summary-grid">
            <div class="summary-metric">
                <span class="m-lbl">Rise Time (10%-90%)</span>
                <span class="m-val">{metrics.riseTime !== null ? `${metrics.riseTime} ms` : '—'}</span>
                <span class="m-sub">Speed of response</span>
            </div>
            <div class="summary-metric">
                <span class="m-lbl">Overshoot</span>
                <span class="m-val" class:warning-val={metrics.overshoot > 8} class:danger-val={metrics.overshoot > 20}>
                    {metrics.overshoot}%
                </span>
                <span class="m-sub">Damping indicator</span>
            </div>
            <div class="summary-metric">
                <span class="m-lbl">Settling Time (3%)</span>
                <span class="m-val">{metrics.settlingTime !== null ? `${metrics.settlingTime} ms` : 'Not settled'}</span>
                <span class="m-sub">Settle duration</span>
            </div>
            <div class="summary-metric">
                <span class="m-lbl">Steady-State Error</span>
                <span class="m-val">{metrics.steadyError}°</span>
                <span class="m-sub">Accuracy error</span>
            </div>
        </div>
    {/if}

    <!-- PID Tuning & Performance Guide -->
    <div class="tuning-guide-card">
        <!-- svelte-ignore a11y_click_events_have_key_events -->
        <!-- svelte-ignore a11y_no_static_element_interactions -->
        <div class="guide-header" onclick={() => showGuide = !showGuide}>
            <span class="guide-title">
                <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                    <circle cx="12" cy="12" r="10"></circle>
                    <line x1="12" y1="16" x2="12" y2="12"></line>
                    <line x1="12" y1="8" x2="12.01" y2="8"></line>
                </svg>
                PID Tuning & Performance Reference Guide
            </span>
            <span class="toggle-icon">{showGuide ? '▼' : '►'}</span>
        </div>
        {#if showGuide}
            <div class="guide-content">
                <div class="guide-intro">
                    The step response test assesses how the actuator responds to sudden changes in target angle. 
                    Tuning the PID parameters changes the trajectory shape:
                </div>
                <div class="guide-grid">
                    <div class="guide-item">
                        <span class="metric-name rise">Rise Time (ms)</span>
                        <p>How fast the motor moves from 10% to 90% of the target step. To speed this up, increase proportional gain <strong>Kp</strong>.</p>
                    </div>
                    <div class="guide-item">
                        <span class="metric-name overshoot">Overshoot (%)</span>
                        <p>How far the motor flies past the target angle. Reduce overshoot by increasing derivative damping <strong>Kd</strong>, or lowering <strong>Kp</strong>.</p>
                    </div>
                    <div class="guide-item">
                        <span class="metric-name settling">Settling Time (ms)</span>
                        <p>The time the motor takes to stay within ±3% of target. Good damping (high <strong>Kd</strong>) minimizes oscillations and settling time.</p>
                    </div>
                    <div class="guide-item">
                        <span class="metric-name error">Steady-State Error (°)</span>
                        <p>The final gap between command and actual position. To overcome friction and close this error, inject integral gain <strong>Ki</strong>.</p>
                    </div>
                    <div class="guide-item">
                        <span class="metric-name velocity-guide">Velocity Limit (°/s)</span>
                        <p>Caps the maximum speed of the step transition. A lower speed limit flattens the transition curve, which increases the <strong>Rise Time</strong> but significantly reduces mechanical shock and <strong>Overshoot</strong>.</p>
                    </div>
                    <div class="guide-item">
                        <span class="metric-name current-guide">Force Limit (mA)</span>
                        <p>Caps the peak torque allowed during the move. A low force limit prevents the motor from quickly overcoming inertia, which increases <strong>Rise Time</strong> and can lead to steady-state lag or failure to reach target under friction.</p>
                    </div>
                </div>
            </div>
        {/if}
    </div>
</div>

<style>
    .step-dashboard {
        display: grid;
        grid-template-columns: 200px 1fr;
        gap: 1.5rem;
        align-items: flex-start;
    }

    .step-controls {
        display: flex;
        flex-direction: column;
        gap: 1.1rem;
    }

    .control-group {
        display: flex;
        flex-direction: column;
        gap: 0.4rem;
    }

    .lbl {
        color: var(--text-muted);
        font-size: 0.68rem;
        text-transform: uppercase;
        letter-spacing: 0.05em;
        font-weight: 600;
    }

    .button-toggle-row {
        display: grid;
        grid-template-columns: repeat(4, 1fr);
        gap: 3px;
        background: rgba(0, 0, 0, 0.2);
        border: 1px solid rgba(255, 255, 255, 0.06);
        border-radius: 8px;
        padding: 2px;
    }
    .toggle-btn {
        background: transparent;
        border: none;
        color: var(--text-secondary);
        font-family: var(--font);
        font-size: 0.72rem;
        font-weight: 550;
        padding: 0.35rem 0;
        border-radius: 6px;
        cursor: pointer;
        transition: all 0.15s ease;
    }
    .toggle-btn:hover:not(:disabled) {
        color: var(--text-main);
        background: rgba(255, 255, 255, 0.05);
    }
    .toggle-btn.active {
        background: rgba(255, 255, 255, 0.1);
        color: var(--text-main);
        box-shadow: 0 1px 3px rgba(0,0,0,0.3);
    }
    .toggle-btn:disabled {
        opacity: 0.3;
        cursor: not-allowed;
    }

    .custom-step-input {
        margin-top: 0.2rem;
        display: flex;
        flex-direction: column;
        gap: 0.25rem;
    }
    .custom-step-input label {
        font-size: 0.65rem;
        color: var(--text-muted);
    }
    .input-wrap {
        position: relative;
        display: flex;
        align-items: center;
    }
    .input-unit {
        position: absolute;
        right: 10px;
        font-size: 0.72rem;
        color: var(--text-muted);
        pointer-events: none;
    }
    input[type=number] {
        width: 100%;
        background: rgba(0, 0, 0, 0.2);
        border: 1px solid rgba(255, 255, 255, 0.06);
        color: var(--text-main);
        padding: 0.4rem 0.6rem;
        border-radius: 6px;
        font-size: 0.8rem;
        transition: border-color 0.2s;
    }
    input[type=number]:focus {
        outline: none;
        border-color: var(--accent);
    }
    input[type=number]:disabled {
        opacity: 0.4;
    }


    .run-test-btn {
        display: flex;
        align-items: center;
        justify-content: center;
        gap: 0.4rem;
    }
    .test-spinner {
        width: 13px;
        height: 13px;
        border: 2px solid rgba(255,255,255,0.15);
        border-top-color: #fff;
        border-radius: 50%;
        animation: spin 0.8s linear infinite;
        flex-shrink: 0;
    }
    @keyframes spin {
        to { transform: rotate(360deg); }
    }

    /* ---- Plot Container ---- */
    .step-plot-container {
        display: flex;
        flex-direction: column;
        gap: 0.5rem;
        background: rgba(28, 28, 30, 0.5);
        border: 1px solid rgba(255, 255, 255, 0.06);
        border-radius: 12px;
        padding: 0.75rem 0.9rem;
    }
    .chart-legend {
        display: flex;
        gap: 1.2rem;
        font-size: 0.7rem;
    }
    .legend-item {
        display: flex;
        align-items: center;
        gap: 0.4rem;
        color: var(--text-secondary);
        font-weight: 500;
    }
    .color-dot {
        width: 7px;
        height: 7px;
        border-radius: 50%;
    }
    .color-dot.target {
        background: var(--warning);
    }
    .color-dot.actual {
        background: var(--accent);
        box-shadow: 0 0 4px rgba(10, 132, 255, 0.4);
    }

    .canvas-container {
        width: 100%;
        height: 320px;
        border-radius: 8px;
        overflow: hidden;
    }
    canvas {
        display: block;
        width: 100%;
        height: 100%;
    }

    /* ---- Metrics Summary Grid ---- */
    .metrics-summary-grid {
        display: grid;
        grid-template-columns: repeat(4, 1fr);
        gap: 0.75rem;
        margin-top: 0.25rem;
        border-top: 1px solid rgba(255, 255, 255, 0.06);
        padding-top: 1.25rem;
    }
    .summary-metric {
        background: rgba(255, 255, 255, 0.02);
        border: 1px solid rgba(255, 255, 255, 0.04);
        padding: 0.75rem 1rem;
        border-radius: 10px;
        display: flex;
        flex-direction: column;
        gap: 0.2rem;
    }
    .m-lbl {
        font-size: 0.65rem;
        color: var(--text-muted);
        text-transform: uppercase;
        letter-spacing: 0.05em;
        font-weight: 600;
    }
    .m-val {
        font-family: var(--font), monospace;
        font-size: 1.25rem;
        font-weight: 700;
        color: var(--text-main);
    }
    .m-val.warning-val {
        color: var(--warning);
    }
    .m-val.danger-val {
        color: var(--danger);
    }
    .m-sub {
        font-size: 0.62rem;
        color: var(--text-muted);
    }

    @media (max-width: 768px) {
        .step-dashboard {
            grid-template-columns: 1fr;
        }
        .metrics-summary-grid {
            grid-template-columns: 1fr 1fr;
        }
    }

    /* ---- Tuning Guide ---- */
    .tuning-guide-card {
        background: rgba(255, 255, 255, 0.02);
        border: 1px solid rgba(255, 255, 255, 0.05);
        border-radius: 12px;
        margin-top: 1.25rem;
        overflow: hidden;
    }
    .guide-header {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding: 0.75rem 1.1rem;
        background: rgba(255, 255, 255, 0.015);
        cursor: pointer;
        user-select: none;
        transition: background 0.2s;
    }
    .guide-header:hover {
        background: rgba(255, 255, 255, 0.04);
    }
    .guide-title {
        font-size: 0.76rem;
        font-weight: 600;
        text-transform: uppercase;
        letter-spacing: 0.05em;
        color: var(--text-secondary);
        display: flex;
        align-items: center;
        gap: 0.5rem;
    }
    .guide-title svg {
        opacity: 0.7;
    }
    .toggle-icon {
        font-size: 0.75rem;
        color: var(--text-muted);
    }
    .guide-content {
        padding: 1.1rem;
        border-top: 1px solid rgba(255, 255, 255, 0.04);
        display: flex;
        flex-direction: column;
        gap: 1rem;
        animation: slideDown 0.2s ease-out;
    }
    @keyframes slideDown {
        from { opacity: 0; transform: translateY(-4px); }
        to { opacity: 1; transform: translateY(0); }
    }
    .guide-intro {
        font-size: 0.8rem;
        color: var(--text-secondary);
        line-height: 1.45;
        border-bottom: 1px solid rgba(255, 255, 255, 0.04);
        padding-bottom: 0.75rem;
    }
    .guide-grid {
        display: grid;
        grid-template-columns: repeat(2, 1fr);
        gap: 1rem;
    }
    .guide-item {
        display: flex;
        flex-direction: column;
        gap: 0.25rem;
        background: rgba(0,0,0,0.12);
        border: 1px solid rgba(255,255,255,0.02);
        padding: 0.75rem 0.95rem;
        border-radius: 8px;
    }
    .metric-name {
        font-size: 0.8rem;
        font-weight: 650;
        margin-bottom: 0.1rem;
    }
    .metric-name.rise { color: var(--indigo); }
    .metric-name.overshoot { color: var(--warning); }
    .metric-name.settling { color: #BF5AF2; }
    .metric-name.error { color: var(--accent); }
    .metric-name.velocity-guide { color: var(--indigo); }
    .metric-name.current-guide { color: var(--warning); }
    .guide-item p {
        font-size: 0.76rem;
        color: var(--text-secondary);
        line-height: 1.4;
        margin: 0;
    }
    .guide-item strong {
        color: var(--text-main);
    }
    @media (max-width: 600px) {
        .guide-grid {
            grid-template-columns: 1fr;
        }
    }

    /* ---- Custom Slider Styles ---- */
    .slider-label-row {
        display: flex;
        justify-content: space-between;
        align-items: baseline;
    }
    .val-highlight {
        color: var(--text-main);
        font-weight: 600;
        font-family: var(--font), monospace;
        font-size: 0.8rem;
        font-variant-numeric: tabular-nums;
    }
    .slider-wrap-custom {
        position: relative;
        display: flex;
        align-items: center;
        background: rgba(255, 255, 255, 0.06);
        border-radius: 3px;
        height: 4px;
        width: 100%;
        overflow: visible;
        margin-top: 0.15rem;
    }
    .slider-fill-custom {
        position: absolute;
        left: 0;
        top: 0;
        height: 100%;
        border-radius: 3px;
        pointer-events: none;
        z-index: 1;
        transition: width 0.05s linear;
    }
    .slider-fill-custom.velocity {
        background: var(--indigo);
    }
    .slider-fill-custom.current {
        background: var(--warning);
    }
    .hint {
        font-size: 0.65rem;
        color: var(--text-muted);
        opacity: 0.7;
        margin-top: 1px;
    }

    input[type=range] {
        -webkit-appearance: none;
        appearance: none;
        width: 100%;
        background: transparent;
        position: relative;
        z-index: 2;
        cursor: pointer;
        margin: 0;
    }
    input[type=range]::-webkit-slider-thumb {
        -webkit-appearance: none;
        height: 12px;
        width: 12px;
        border-radius: 50%;
        background: #fff;
        cursor: pointer;
        box-shadow: 0 1px 4px rgba(0, 0, 0, 0.4);
        border: none;
        transition: transform 0.15s ease;
    }
    input[type=range]::-webkit-slider-thumb:hover {
        transform: scale(1.15);
    }
    input[type=range]::-webkit-slider-runnable-track {
        width: 100%;
        height: 4px;
        background: transparent;
    }
    input[type=range]::-moz-range-thumb {
        height: 12px;
        width: 12px;
        border-radius: 50%;
        background: #fff;
        cursor: pointer;
        box-shadow: 0 1px 4px rgba(0, 0, 0, 0.4);
        border: none;
    }
    input[type=range]::-moz-range-track {
        width: 100%;
        height: 4px;
        background: transparent;
    }
    input[type=range]:disabled::-webkit-slider-thumb {
        background: var(--text-muted);
        box-shadow: none;
        cursor: not-allowed;
    }
</style>
