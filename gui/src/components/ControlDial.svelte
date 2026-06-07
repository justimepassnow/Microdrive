<!-- src/components/ControlDial.svelte -->
<script>
    import { tweened } from 'svelte/motion';
    import { cubicOut } from 'svelte/easing';

    let { 
        isConnected = false, 
        actualAngle = 0, 
        targetAngle = $bindable(90), 
        targetVelocity = $bindable(0), 
        targetCurrent = $bindable(0),
        actualCurrent = 0,
        currentLimit = 500,
        isArmed = true,
        onMove,
        onDisarm
    } = $props();

    const R = 80;
    const CX = 100;
    const CY = 100;

    function getPolarX(deg, radius) {
        const rad = ((deg - 90) * Math.PI) / 180;
        return CX + radius * Math.cos(rad);
    }

    function getPolarY(deg, radius) {
        const rad = ((deg - 90) * Math.PI) / 180;
        return CY + radius * Math.sin(rad);
    }

    const maxCurrent = $derived(currentLimit);
    
    // Smooth speedometer needle tracking
    const smoothedCurrent = tweened(0, {
        duration: 350,
        easing: cubicOut
    });
    
    $effect(() => {
        if (isConnected) {
            smoothedCurrent.set(actualCurrent);
        } else {
            smoothedCurrent.set(0);
        }
    });

    let currentAngle = $derived.by(() => {
        const I = $smoothedCurrent;
        const ratio = Math.max(0, Math.min(1, I / maxCurrent));
        return 220 + ratio * 280;
    });

    let trackPath = $derived.by(() => {
        const startDeg = 220;
        const endDeg = 500;
        const x1 = getPolarX(startDeg, R);
        const y1 = getPolarY(startDeg, R);
        const x2 = getPolarX(endDeg, R);
        const y2 = getPolarY(endDeg, R);
        return `M ${x1} ${y1} A ${R} ${R} 0 1 1 ${x2} ${y2}`;
    });

    let activeArcPath = $derived.by(() => {
        const startDeg = 220;
        const endDeg = currentAngle;
        const largeArc = (endDeg - startDeg > 180) ? 1 : 0;
        const x1 = getPolarX(startDeg, R);
        const y1 = getPolarY(startDeg, R);
        const x2 = getPolarX(endDeg, R);
        const y2 = getPolarY(endDeg, R);
        return `M ${x1} ${y1} A ${R} ${R} 0 ${largeArc} 1 ${x2} ${y2}`;
    });

    let redLinePath = $derived.by(() => {
        const startDeg = 220 + 0.85 * 280; // Red-line starts at 85% of limit (458 degrees)
        const endDeg = 500; // Maxes out at 100% of limit
        const x1 = getPolarX(startDeg, R);
        const y1 = getPolarY(startDeg, R);
        const x2 = getPolarX(endDeg, R);
        const y2 = getPolarY(endDeg, R);
        return `M ${x1} ${y1} A ${R} ${R} 0 0 1 ${x2} ${y2}`;
    });

    let ticks = $derived.by(() => {
        const list = [];
        for (let i = 0; i <= 10; i++) {
            const ratio = i / 10;
            const angle = 220 + ratio * 280;
            const value = ratio * maxCurrent;
            list.push({ angle, value, isMajor: i % 2 === 0 });
        }
        return list;
    });

    let svgEl = $state(null);
    let isDragging = $state(false);

    // Throttle helper to protect the UART bus from congestion
    let throttleTimeout = null;
    let pendingAngle = null;
    
    function sendThrottledMove(angle) {
        if (!isConnected) return;
        
        pendingAngle = angle;
        if (throttleTimeout) return;

        onMove(pendingAngle, targetVelocity, targetCurrent);
        pendingAngle = null;

        throttleTimeout = setTimeout(() => {
            throttleTimeout = null;
            if (pendingAngle !== null) {
                onMove(pendingAngle, targetVelocity, targetCurrent);
                pendingAngle = null;
            }
        }, 50);
    }

    function calculateAngleFromEvent(e) {
        if (!svgEl) return;
        
        const rect = svgEl.getBoundingClientRect();
        const centerX = rect.left + rect.width / 2;
        const centerY = rect.top + rect.height / 2;

        const clientX = e.touches ? e.touches[0].clientX : e.clientX;
        const clientY = e.touches ? e.touches[0].clientY : e.clientY;

        const dx = clientX - centerX;
        const dy = clientY - centerY;

        let angleRad = Math.atan2(dy, dx) + Math.PI / 2;
        if (angleRad < 0) {
            angleRad += 2 * Math.PI;
        }

        let angleDeg = Math.round((angleRad * 180) / Math.PI);
        if (angleDeg < 0) angleDeg = 0;
        if (angleDeg > 360) angleDeg = 360;

        targetAngle = angleDeg;
        sendThrottledMove(targetAngle);
    }

    function handleMouseDown(e) {
        if (!isConnected) return;
        isDragging = true;
        calculateAngleFromEvent(e);
        window.addEventListener('mousemove', handleMouseMove);
        window.addEventListener('mouseup', handleMouseUp);
    }

    function handleMouseMove(e) {
        if (!isDragging) return;
        calculateAngleFromEvent(e);
    }

    function handleMouseUp() {
        isDragging = false;
        window.removeEventListener('mousemove', handleMouseMove);
        window.removeEventListener('mouseup', handleMouseUp);
    }

    function handleTouchStart(e) {
        if (!isConnected) return;
        isDragging = true;
        calculateAngleFromEvent(e);
        window.addEventListener('touchmove', handleTouchMove, { passive: false });
        window.addEventListener('touchend', handleTouchEnd);
    }

    function handleTouchMove(e) {
        if (!isDragging) return;
        e.preventDefault();
        calculateAngleFromEvent(e);
    }

    function handleTouchEnd() {
        isDragging = false;
        window.removeEventListener('touchmove', handleTouchMove);
        window.removeEventListener('touchend', handleTouchEnd);
    }

    function toggleArm() {
        if (!isConnected) return;
        if (isArmed) {
            onDisarm();
        } else {
            onMove(targetAngle, targetVelocity);
        }
    }
</script>

<div class="control-panel glass-subpanel">
    <div class="panel-header">
        <h3>Position Control & Actuation</h3>
        <span class="control-badge" class:active={isConnected}>
            {isConnected ? 'Actuator Ready' : 'Standby'}
        </span>
    </div>
    
    <div class="dial-container">
        <!-- svelte-ignore a11y_no_static_element_interactions -->
        <svg 
            bind:this={svgEl}
            width="220" 
            height="220" 
            viewBox="0 0 200 200"
            class="servo-svg-dial"
            class:disabled={!isConnected}
            onmousedown={handleMouseDown}
            ontouchstart={handleTouchStart}
        >
            <defs>
                <!-- Neon Cyan Glow for Actual Angle -->
                <filter id="glow-cyan" x="-20%" y="-20%" width="140%" height="140%">
                    <feGaussianBlur stdDeviation="5" result="blur" />
                    <feMerge>
                        <feMergeNode in="blur" />
                        <feMergeNode in="SourceGraphic" />
                    </feMerge>
                </filter>
                <!-- Neon Magenta Glow for Target Handle -->
                <filter id="glow-magenta" x="-50%" y="-50%" width="200%" height="200%">
                    <feGaussianBlur stdDeviation="6" result="blur" />
                    <feMerge>
                        <feMergeNode in="blur" />
                        <feMergeNode in="SourceGraphic" />
                    </feMerge>
                </filter>
                <!-- Central Cap Radial Shading -->
                <radialGradient id="cap-grad" cx="50%" cy="50%" r="50%">
                    <stop offset="70%" stop-color="#0b0e14" />
                    <stop offset="95%" stop-color="#1a2230" />
                    <stop offset="100%" stop-color="#2a364a" />
                </radialGradient>
                <!-- Outer Track Glow Shader -->
                <radialGradient id="track-grad" cx="50%" cy="50%" r="50%">
                    <stop offset="85%" stop-color="rgba(0,0,0,0)" />
                    <stop offset="100%" stop-color="rgba(0, 240, 255, 0.05)" />
                </radialGradient>
            </defs>

            <!-- Outer Tech Ring (Faint decorative boundary) -->
            <circle cx="100" cy="100" r={R + 10} class="dial-outer-border" />

            <!-- Circular Background Shading -->
            <circle cx="100" cy="100" r={R} fill="url(#track-grad)" />

            <!-- Dynamic Precision Angular Ticks -->
            {#each Array(24) as _, i}
                {@const angle = i * 15}
                <line 
                    x1={getPolarX(angle, R - 8)} 
                    y1={getPolarY(angle, R - 8)} 
                    x2={getPolarX(angle, R - 2)} 
                    y2={getPolarY(angle, R - 2)} 
                    class="dial-tick" 
                    class:major={i % 6 === 0}
                    class:highlighted={isConnected && actualAngle >= angle}
                />
            {/each}

            <!-- Background Dial Ring Track -->
            <circle cx="100" cy="100" r={R} class="dial-track" />
            
            <!-- Swept Actual Angle Gradient Sector (Semi-transparent background path) -->
            {#if isConnected && actualAngle > 0}
                <path 
                    d="M {getPolarX(0, R)} {getPolarY(0, R)} A {R} {R} 0 {actualAngle > 180 ? 1 : 0} 1 {getPolarX(actualAngle, R)} {getPolarY(actualAngle, R)} L 100 100 Z"
                    class="dial-swept-sector"
                />
                
                <!-- Glowing Cyan Actual Angle Trail -->
                <path 
                    d="M {getPolarX(0, R)} {getPolarY(0, R)} A {R} {R} 0 {actualAngle > 180 ? 1 : 0} 1 {getPolarX(actualAngle, R)} {getPolarY(actualAngle, R)}"
                    class="dial-fill-actual"
                    filter="url(#glow-cyan)"
                />
            {/if}
            
            <!-- Central Cap Display Shield -->
            <circle cx="100" cy="100" r="54" fill="url(#cap-grad)" stroke="rgba(255,255,255,0.06)" stroke-width="1.5" />
            <circle cx="100" cy="100" r="48" class="dial-center-inset" />

            <!-- Glowing Actual position needle pointer (Futuristic Tapered Polygon) -->
            {#if isConnected}
                <!-- Dynamic shadow line underneath needle -->
                <line 
                    x1="100" 
                    y1="100" 
                    x2={getPolarX(actualAngle, R - 10)} 
                    y2={getPolarY(actualAngle, R - 10)} 
                    class="dial-needle-shadow"
                />
                <!-- Tapered Glowing Needle -->
                <polygon 
                    points="
                        {getPolarX(actualAngle - 5, 12)} {getPolarY(actualAngle - 5, 12)}, 
                        {getPolarX(actualAngle, R - 12)} {getPolarY(actualAngle, R - 12)}, 
                        {getPolarX(actualAngle + 5, 12)} {getPolarY(actualAngle + 5, 12)}
                    "
                    class="dial-needle-poly"
                    class:disarmed={!isArmed}
                    filter={isArmed ? 'url(#glow-cyan)' : ''}
                />
            {/if}
            
            <!-- Target position handle (Neon Magenta circular node) -->
            {#if isConnected}
                <!-- Outer dashed halo of target handle -->
                <circle 
                    cx={getPolarX(targetAngle, R)} 
                    cy={getPolarY(targetAngle, R)} 
                    r="15" 
                    class="dial-target-halo"
                    class:dragging={isDragging}
                />
                <!-- Interactive Handle -->
                <circle 
                    cx={getPolarX(targetAngle, R)} 
                    cy={getPolarY(targetAngle, R)} 
                    r="8" 
                    class="dial-target-handle"
                    filter="url(#glow-magenta)"
                />
            {/if}
            
            <!-- Numerical display inside the Central Cap -->
            <text x="100" y="96" class="dial-text-val">{isConnected ? actualAngle : '--'}</text>
            <text x="100" y="112" class="dial-text-deg">{isConnected ? 'DEG' : ''}</text>
            <text x="100" y="125" class="dial-text-lbl">Actual Position</text>
        </svg>

        <!-- Speedometer Gauge -->
        <svg 
            width="220" 
            height="220" 
            viewBox="0 0 200 200"
            class="servo-svg-dial speedometer-svg-dial"
            class:disabled={!isConnected}
        >
            <defs>
                <!-- Neon Amber Glow for Actual Current -->
                <filter id="glow-warning" x="-20%" y="-20%" width="140%" height="140%">
                    <feGaussianBlur stdDeviation="5" result="blur" />
                    <feMerge>
                        <feMergeNode in="blur" />
                        <feMergeNode in="SourceGraphic" />
                    </feMerge>
                </filter>
                <!-- Central Cap Radial Shading -->
                <radialGradient id="cap-grad-warning" cx="50%" cy="50%" r="50%">
                    <stop offset="70%" stop-color="#0b0d10" />
                    <stop offset="95%" stop-color="#241e17" />
                    <stop offset="100%" stop-color="#3b2d1d" />
                </radialGradient>
                <!-- Outer Track Glow Shader -->
                <radialGradient id="track-grad-warning" cx="50%" cy="50%" r="50%">
                    <stop offset="85%" stop-color="rgba(0,0,0,0)" />
                    <stop offset="100%" stop-color="rgba(245, 158, 11, 0.04)" />
                </radialGradient>
            </defs>

            <!-- Outer Tech Ring -->
            <circle cx="100" cy="100" r={R + 10} class="dial-outer-border" />

            <!-- Circular Background Shading -->
            <circle cx="100" cy="100" r={R} fill="url(#track-grad-warning)" />

            <!-- Background Dial Ring Track (Swept) -->
            <path d={trackPath} class="dial-track" />

            <!-- Dynamic Precision Angular Ticks & Numerical Labels -->
            {#each ticks as tick}
                <line 
                    x1={getPolarX(tick.angle, R - 8)} 
                    y1={getPolarY(tick.angle, R - 8)} 
                    x2={getPolarX(tick.angle, R - 2)} 
                    y2={getPolarY(tick.angle, R - 2)} 
                    class="dial-tick speedometer-tick" 
                    class:major={tick.isMajor}
                    class:highlighted={isConnected && $smoothedCurrent >= tick.value}
                    class:red-line={tick.value >= currentLimit}
                />
                {#if tick.isMajor}
                    <text
                        x={getPolarX(tick.angle, R - 17)}
                        y={getPolarY(tick.angle, R - 17)}
                        class="speedometer-tick-label"
                        class:highlighted={isConnected && $smoothedCurrent >= tick.value}
                        class:red-line={tick.value >= currentLimit}
                    >
                        {Math.round(tick.value)}
                    </text>
                {/if}
            {/each}

            <!-- Danger/Red-line Zone Arc -->
            {#if isConnected}
                <path 
                    d={redLinePath}
                    class="speedometer-red-line"
                    filter="url(#glow-magenta)"
                />
            {/if}
            
            <!-- Swept Actual Current Gradient Sector -->
            {#if isConnected && $smoothedCurrent > 0}
                <path 
                    d="M {getPolarX(220, R)} {getPolarY(220, R)} A {R} {R} 0 {currentAngle - 220 > 180 ? 1 : 0} 1 {getPolarX(currentAngle, R)} {getPolarY(currentAngle, R)} L 100 100 Z"
                    class="dial-swept-sector speedometer-swept-sector"
                />
                
                <!-- Glowing Amber Actual Current Trail -->
                <path 
                    d={activeArcPath}
                    class="dial-fill-actual speedometer-fill-actual"
                    filter="url(#glow-warning)"
                />
            {/if}
            
            <!-- Central Cap Display Shield -->
            <circle cx="100" cy="100" r="54" fill="url(#cap-grad-warning)" stroke="rgba(255,255,255,0.06)" stroke-width="1.5" />
            <circle cx="100" cy="100" r="48" class="dial-center-inset speedometer-center-inset" />

            <!-- Glowing Actual position needle pointer -->
            {#if isConnected}
                <!-- Dynamic shadow line underneath needle -->
                <line 
                    x1="100" 
                    y1="100" 
                    x2={getPolarX(currentAngle, R - 10)} 
                    y2={getPolarY(currentAngle, R - 10)} 
                    class="dial-needle-shadow"
                />
                <!-- Tapered Glowing Needle -->
                <polygon 
                    points="
                        {getPolarX(currentAngle - 5, 12)} {getPolarY(currentAngle - 5, 12)}, 
                        {getPolarX(currentAngle, R - 12)} {getPolarY(currentAngle, R - 12)}, 
                        {getPolarX(currentAngle + 5, 12)} {getPolarY(currentAngle + 5, 12)}
                    "
                    class="dial-needle-poly speedometer-needle"
                    filter="url(#glow-warning)"
                />
            {/if}
            
            <!-- Numerical display inside the Central Cap -->
            <text x="100" y="96" class="dial-text-val speedometer-text-val">{isConnected ? Math.round($smoothedCurrent) : '--'}</text>
            <text 
                x="100" 
                y="112" 
                class="dial-text-deg speedometer-text-ma" 
                class:overlimit={$smoothedCurrent >= currentLimit}
            >
                {isConnected ? 'mA' : ''}
            </text>
            <text x="100" y="125" class="dial-text-lbl">Current Draw</text>
        </svg>
    </div>

    <!-- Fine Tuning & Speed Configuration Controls -->
    <div class="slider-controls">
        <div class="slider-group">
            <div class="label-row">
                <span class="label">Target Angle</span>
                <span class="value-highlight">{targetAngle}°</span>
            </div>
            <div class="slider-wrapper">
                <input 
                    type="range" 
                    min="0" 
                    max="360" 
                    bind:value={targetAngle} 
                    disabled={!isConnected}
                    oninput={() => sendThrottledMove(targetAngle)}
                />
                <!-- Progress bar behind track for premium slider look -->
                <div class="slider-fill" style="width: {(targetAngle / 360) * 100}%"></div>
            </div>
        </div>
        
        <div class="slider-group">
            <div class="label-row">
                <span class="label">Target Velocity</span>
                <span class="value-highlight">{targetVelocity === 0 ? 'DEFAULT' : `${targetVelocity} °/s`}</span>
            </div>
            <div class="slider-wrapper">
                <input 
                    type="range" 
                    min="0" 
                    max="1000" 
                    step="10"
                    bind:value={targetVelocity} 
                    disabled={!isConnected}
                    oninput={() => sendThrottledMove(targetAngle)}
                />
                <div class="slider-fill" style="width: {(targetVelocity / 1000) * 100}%"></div>
            </div>
            <span class="hint-text">0 = Use Flash default speed limit</span>
        </div>

        <div class="slider-group">
            <div class="label-row">
                <span class="label">Dynamic Force Limit</span>
                <span class="value-highlight">{targetCurrent === 0 ? 'DEFAULT' : `${targetCurrent} mA`}</span>
            </div>
            <div class="slider-wrapper">
                <input 
                    type="range" 
                    min="0" 
                    max={currentLimit} 
                    step="10"
                    bind:value={targetCurrent} 
                    disabled={!isConnected}
                    oninput={() => sendThrottledMove(targetAngle)}
                />
                <div class="slider-fill" style="width: {targetCurrent === 0 ? 0 : (targetCurrent / currentLimit) * 100}%"></div>
            </div>
            <span class="hint-text">0 = Use Flash default limit</span>
        </div>

        <div class="slider-group toggle-group">
            <div class="toggle-row">
                <span class="label">Actuator Status</span>
                <span class="status-indicator" class:armed={isArmed} class:disarmed={!isArmed}>
                    {isConnected ? (isArmed ? 'Armed & Holding' : 'Disarmed / Free') : '--'}
                </span>
            </div>
            <button 
                class="btn small disarm-btn" 
                class:armed={isArmed}
                disabled={!isConnected} 
                onclick={toggleArm}
            >
                {isArmed ? 'Disarm Motor' : 'Arm & Hold'}
            </button>
        </div>
    </div>
</div>

<style>
    .glass-subpanel {
        background: rgba(0, 0, 0, 0.18);
        border: 1px solid rgba(255, 255, 255, 0.03);
        border-radius: 14px;
        padding: 1.5rem;
        display: flex;
        flex-direction: column;
        gap: 1.5rem;
    }
    .panel-header {
        display: flex;
        justify-content: space-between;
        align-items: center;
        border-bottom: 1px solid rgba(255,255,255,0.03);
        padding-bottom: 0.8rem;
    }
    .panel-header h3 {
        margin-bottom: 0;
        font-size: 0.95rem;
        text-transform: uppercase;
        letter-spacing: 1px;
    }
    .control-badge {
        font-size: 0.7rem;
        font-weight: 700;
        text-transform: uppercase;
        letter-spacing: 1px;
        background: rgba(255, 255, 255, 0.03);
        color: var(--text-muted);
        padding: 0.2rem 0.5rem;
        border-radius: 4px;
        border: 1px solid rgba(255, 255, 255, 0.05);
    }
    .control-badge.active {
        background: rgba(0, 240, 255, 0.1);
        color: var(--accent);
        border-color: var(--accent);
    }

    .dial-container {
        display: flex;
        justify-content: center;
        align-items: center;
        gap: 2.5rem;
        user-select: none;
        position: relative;
    }
    .servo-svg-dial {
        cursor: pointer;
    }
    .servo-svg-dial.disabled {
        cursor: not-allowed;
        opacity: 0.2;
    }
    
    .speedometer-svg-dial.disabled {
        opacity: 0.2;
    }

    .speedometer-center-inset {
        stroke: rgba(245, 158, 11, 0.03) !important;
    }

    .speedometer-tick {
        stroke: rgba(255, 255, 255, 0.08);
        transition: stroke 0.2s;
    }
    .speedometer-tick.highlighted {
        stroke: var(--warning) !important;
        filter: drop-shadow(0 0 1px var(--warning-glow));
    }
    .speedometer-tick.red-line {
        stroke: rgba(255, 42, 95, 0.2);
    }
    .speedometer-tick.red-line.highlighted {
        stroke: var(--magenta) !important;
        filter: drop-shadow(0 0 1px var(--magenta-glow));
    }

    .speedometer-tick-label {
        fill: rgba(255, 255, 255, 0.2);
        font-size: 0.5rem;
        font-weight: 700;
        text-anchor: middle;
        dominant-baseline: middle;
        font-family: 'Outfit', monospace;
    }
    .speedometer-tick-label.highlighted {
        fill: var(--warning);
        text-shadow: 0 0 3px var(--warning-glow);
    }
    .speedometer-tick-label.red-line {
        fill: rgba(255, 42, 95, 0.35);
    }
    .speedometer-tick-label.red-line.highlighted {
        fill: var(--magenta);
        text-shadow: 0 0 3px var(--magenta-glow);
    }

    .speedometer-red-line {
        fill: none;
        stroke: var(--magenta);
        stroke-width: 2.5px;
        stroke-linecap: round;
        opacity: 0.65;
    }

    .speedometer-fill-actual {
        stroke: var(--warning) !important;
        stroke-width: 6px;
        stroke-linecap: round;
    }

    .speedometer-swept-sector {
        fill: rgba(245, 158, 11, 0.015);
    }

    .speedometer-needle {
        fill: var(--warning) !important;
        stroke: #fff;
        stroke-width: 0.5px;
    }

    .speedometer-text-ma {
        fill: var(--warning) !important;
        transition: fill 0.2s;
    }
    .speedometer-text-ma.overlimit {
        fill: var(--magenta) !important;
        animation: textGlowPulseRed 1.2s infinite;
    }
    
    .speedometer-text-val {
        font-family: 'Outfit', monospace;
        letter-spacing: -0.5px;
    }

    .dial-needle-poly.disarmed {
        fill: var(--text-muted) !important;
        stroke: rgba(255,255,255,0.15) !important;
    }

    .toggle-group {
        border-top: 1px solid rgba(255, 255, 255, 0.04);
        padding-top: 1.2rem;
        display: flex;
        flex-direction: row;
        justify-content: space-between;
        align-items: center;
        margin-top: 0.5rem;
    }
    
    .toggle-row {
        display: flex;
        flex-direction: column;
        gap: 0.25rem;
    }
    
    .status-indicator {
        font-family: 'Outfit', sans-serif;
        font-size: 0.85rem;
        font-weight: 700;
        text-transform: uppercase;
        letter-spacing: 0.5px;
    }
    .status-indicator.armed {
        color: var(--accent);
        text-shadow: 0 0 5px var(--accent-glow);
    }
    .status-indicator.disarmed {
        color: var(--text-muted);
    }
    
    .disarm-btn {
        font-weight: 700;
        font-size: 0.75rem;
        padding: 0.45rem 1.2rem;
        border-radius: 6px;
        background: rgba(255, 255, 255, 0.03);
        border: 1px solid rgba(255, 255, 255, 0.05);
        color: var(--text-main);
        transition: all 0.2s cubic-bezier(0.4, 0, 0.2, 1);
        text-transform: uppercase;
        letter-spacing: 0.5px;
    }
    
    .disarm-btn:not(:disabled).armed:hover {
        background: rgba(255, 42, 95, 0.1);
        color: var(--magenta);
        border-color: rgba(255, 42, 95, 0.3);
        box-shadow: 0 0 10px rgba(255, 42, 95, 0.15);
    }

    .disarm-btn:not(:disabled):not(.armed):hover {
        background: rgba(0, 240, 255, 0.1);
        color: var(--accent);
        border-color: rgba(0, 240, 255, 0.3);
        box-shadow: 0 0 10px rgba(0, 240, 255, 0.15);
    }
    
    /* Outer tech visual decorations */
    .dial-outer-border {
        fill: none;
        stroke: rgba(255, 255, 255, 0.02);
        stroke-width: 1px;
        stroke-dasharray: 4, 12;
    }
    .dial-center-inset {
        fill: #06090e;
        stroke: rgba(0, 240, 255, 0.03);
        stroke-width: 1px;
    }

    /* Tick styling */
    .dial-tick {
        stroke: rgba(255, 255, 255, 0.1);
        stroke-width: 1.5px;
        transition: stroke 0.2s;
    }
    .dial-tick.major {
        stroke: rgba(255, 255, 255, 0.25);
        stroke-width: 2px;
    }
    .dial-tick.highlighted {
        stroke: var(--accent);
        filter: drop-shadow(0 0 1px var(--accent));
    }

    .dial-track {
        fill: none;
        stroke: rgba(255, 255, 255, 0.04);
        stroke-width: 6px;
    }
    .dial-fill-actual {
        fill: none;
        stroke: var(--accent);
        stroke-width: 6px;
        stroke-linecap: round;
    }
    .dial-swept-sector {
        fill: rgba(0, 240, 255, 0.02);
        pointer-events: none;
    }

    /* Glowing Needle */
    .dial-needle-shadow {
        stroke: rgba(0,0,0,0.5);
        stroke-width: 5px;
        stroke-linecap: round;
    }
    .dial-needle-poly {
        fill: var(--accent);
        stroke: #fff;
        stroke-width: 0.5px;
    }

    /* Target Handle and Halo */
    .dial-target-handle {
        fill: #FF2A5F;
        stroke: #fff;
        stroke-width: 1.5px;
        cursor: grab;
    }
    .dial-target-halo {
        fill: rgba(255, 42, 95, 0.05);
        stroke: rgba(255, 42, 95, 0.15);
        stroke-width: 1px;
        stroke-dasharray: 2, 2;
        pointer-events: none;
        transform-origin: center;
        transition: stroke-width 0.2s, r 0.2s;
    }
    .dial-target-halo.dragging {
        stroke-width: 1.5px;
        r: 18;
        stroke: rgba(255, 42, 95, 0.3);
        fill: rgba(255, 42, 95, 0.08);
    }

    /* Interior Typography */
    .dial-text-val {
        fill: #fff;
        font-size: 2.2rem;
        font-weight: 700;
        text-anchor: middle;
        dominant-baseline: middle;
        font-family: 'Outfit', monospace;
        letter-spacing: -0.5px;
    }
    .dial-text-deg {
        fill: var(--accent);
        font-size: 0.62rem;
        font-weight: 700;
        letter-spacing: 1px;
        text-anchor: middle;
        dominant-baseline: middle;
    }
    .dial-text-lbl {
        fill: var(--text-muted);
        font-size: 0.58rem;
        text-transform: uppercase;
        letter-spacing: 1px;
        text-anchor: middle;
        dominant-baseline: middle;
    }

    /* Premium Custom Sliders */
    .slider-controls {
        display: flex;
        flex-direction: column;
        gap: 1.2rem;
    }
    .slider-group {
        display: flex;
        flex-direction: column;
        gap: 0.5rem;
    }
    .label-row {
        display: flex;
        justify-content: space-between;
        font-size: 0.8rem;
    }
    .label {
        color: var(--text-muted);
        font-weight: 500;
        text-transform: uppercase;
        font-size: 0.72rem;
        letter-spacing: 0.5px;
    }
    .value-highlight {
        color: var(--accent);
        font-weight: bold;
        font-family: monospace;
    }
    
    .slider-wrapper {
        position: relative;
        display: flex;
        align-items: center;
        background: rgba(255,255,255,0.03);
        border-radius: 4px;
        height: 6px;
        width: 100%;
        overflow: visible;
        border: 1px solid rgba(255,255,255,0.02);
    }
    
    .slider-fill {
        position: absolute;
        left: 0;
        top: 0;
        height: 100%;
        background: linear-gradient(90deg, rgba(0, 240, 255, 0.4), var(--accent));
        border-radius: 4px;
        pointer-events: none;
        z-index: 1;
        box-shadow: 0 0 5px rgba(0, 240, 255, 0.3);
    }
    
    input[type=range] {
        -webkit-appearance: none;
        width: 100%;
        background: transparent;
        position: relative;
        z-index: 2;
        cursor: pointer;
        margin: 0;
    }
    input[type=range]::-webkit-slider-thumb {
        -webkit-appearance: none;
        height: 16px; 
        width: 16px;
        border-radius: 50%;
        background: #fff;
        cursor: pointer;
        box-shadow: 0 0 8px rgba(0, 240, 255, 0.6);
        border: 2px solid var(--accent);
        transition: transform 0.1s;
    }
    input[type=range]::-webkit-slider-thumb:hover {
        transform: scale(1.15);
    }
    input[type=range]::-webkit-slider-runnable-track {
        width: 100%; 
        height: 6px;
        background: transparent;
    }
    input[type=range]:disabled::-webkit-slider-thumb {
        background: var(--text-muted);
        box-shadow: none;
        border-color: transparent;
        cursor: not-allowed;
    }
    .hint-text {
        font-size: 0.7rem;
        color: var(--text-muted);
        font-style: italic;
    }
</style>
