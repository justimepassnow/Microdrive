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
        <h3>Position Control</h3>
        <span class="control-badge" class:active={isConnected}>
            {isConnected ? 'Ready' : 'Standby'}
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
                <filter id="glow-accent" x="-10%" y="-10%" width="120%" height="120%">
                    <feGaussianBlur stdDeviation="2" result="blur" />
                    <feMerge>
                        <feMergeNode in="blur" />
                        <feMergeNode in="SourceGraphic" />
                    </feMerge>
                </filter>
                <filter id="glow-target" x="-20%" y="-20%" width="140%" height="140%">
                    <feGaussianBlur stdDeviation="2" result="blur" />
                    <feMerge>
                        <feMergeNode in="blur" />
                        <feMergeNode in="SourceGraphic" />
                    </feMerge>
                </filter>
                <radialGradient id="cap-grad" cx="50%" cy="50%" r="50%">
                    <stop offset="60%" stop-color="#1c1c1e" />
                    <stop offset="90%" stop-color="#2c2c2e" />
                    <stop offset="100%" stop-color="#3a3a3c" />
                </radialGradient>
            </defs>

            <!-- Outer decorative ring -->
            <circle cx="100" cy="100" r={R + 10} class="dial-outer-border" />

            <!-- Tick marks -->
            {#each Array(24) as _, i}
                {@const angle = i * 15}
                <line 
                    x1={getPolarX(angle, R - 6)} 
                    y1={getPolarY(angle, R - 6)} 
                    x2={getPolarX(angle, R - 1)} 
                    y2={getPolarY(angle, R - 1)} 
                    class="dial-tick" 
                    class:major={i % 6 === 0}
                />
            {/each}

            <!-- Track ring -->
            <circle cx="100" cy="100" r={R} class="dial-track" />
            
            <!-- Actual angle arc -->
            {#if isConnected && actualAngle > 0}
                <path 
                    d="M {getPolarX(0, R)} {getPolarY(0, R)} A {R} {R} 0 {actualAngle > 180 ? 1 : 0} 1 {getPolarX(actualAngle, R)} {getPolarY(actualAngle, R)}"
                    class="dial-fill-actual"
                />
            {/if}
            
            <!-- Center cap -->
            <circle cx="100" cy="100" r="52" fill="url(#cap-grad)" stroke="rgba(255,255,255,0.08)" stroke-width="1" />
            <circle cx="100" cy="100" r="46" class="dial-center-inset" />

            <!-- Needle -->
            {#if isConnected}
                <polygon 
                    points="
                        {getPolarX(actualAngle - 4, 14)} {getPolarY(actualAngle - 4, 14)}, 
                        {getPolarX(actualAngle, R - 14)} {getPolarY(actualAngle, R - 14)}, 
                        {getPolarX(actualAngle + 4, 14)} {getPolarY(actualAngle + 4, 14)}
                    "
                    class="dial-needle-poly"
                    class:disarmed={!isArmed}
                />
            {/if}
            
            <!-- Target handle -->
            {#if isConnected}
                <circle 
                    cx={getPolarX(targetAngle, R)} 
                    cy={getPolarY(targetAngle, R)} 
                    r="12" 
                    class="dial-target-halo"
                    class:dragging={isDragging}
                />
                <circle 
                    cx={getPolarX(targetAngle, R)} 
                    cy={getPolarY(targetAngle, R)} 
                    r="7" 
                    class="dial-target-handle"
                />
            {/if}
            
            <!-- Center text -->
            <text x="100" y="95" class="dial-text-val">{isConnected ? actualAngle : '--'}</text>
            <text x="100" y="110" class="dial-text-deg">{isConnected ? 'DEG' : ''}</text>
            <text x="100" y="122" class="dial-text-lbl">Position</text>
        </svg>

        <!-- Current Speedometer -->
        <svg 
            width="220" 
            height="220" 
            viewBox="0 0 200 200"
            class="servo-svg-dial speedometer-svg-dial"
            class:disabled={!isConnected}
        >
            <defs>
                <filter id="glow-warning" x="-10%" y="-10%" width="120%" height="120%">
                    <feGaussianBlur stdDeviation="2" result="blur" />
                    <feMerge>
                        <feMergeNode in="blur" />
                        <feMergeNode in="SourceGraphic" />
                    </feMerge>
                </filter>
                <radialGradient id="cap-grad-warning" cx="50%" cy="50%" r="50%">
                    <stop offset="60%" stop-color="#1c1c1e" />
                    <stop offset="90%" stop-color="#2a2520" />
                    <stop offset="100%" stop-color="#3a3530" />
                </radialGradient>
            </defs>

            <!-- Outer decorative ring -->
            <circle cx="100" cy="100" r={R + 10} class="dial-outer-border" />

            <!-- Track arc -->
            <path d={trackPath} class="dial-track" />

            <!-- Tick marks and labels -->
            {#each ticks as tick}
                <line 
                    x1={getPolarX(tick.angle, R - 6)} 
                    y1={getPolarY(tick.angle, R - 6)} 
                    x2={getPolarX(tick.angle, R - 1)} 
                    y2={getPolarY(tick.angle, R - 1)} 
                    class="dial-tick speedometer-tick" 
                    class:major={tick.isMajor}
                    class:highlighted={isConnected && $smoothedCurrent >= tick.value}
                    class:red-line={tick.value >= currentLimit}
                />
                {#if tick.isMajor}
                    <text
                        x={getPolarX(tick.angle, R - 16)}
                        y={getPolarY(tick.angle, R - 16)}
                        class="speedometer-tick-label"
                        class:highlighted={isConnected && $smoothedCurrent >= tick.value}
                        class:red-line={tick.value >= currentLimit}
                    >
                        {Math.round(tick.value)}
                    </text>
                {/if}
            {/each}

            <!-- Red-line danger zone -->
            {#if isConnected}
                <path 
                    d={redLinePath}
                    class="speedometer-red-line"
                />
            {/if}
            
            <!-- Current arc -->
            {#if isConnected && $smoothedCurrent > 0}
                <path 
                    d={activeArcPath}
                    class="dial-fill-actual speedometer-fill-actual"
                />
            {/if}
            
            <!-- Center cap -->
            <circle cx="100" cy="100" r="52" fill="url(#cap-grad-warning)" stroke="rgba(255,255,255,0.08)" stroke-width="1" />
            <circle cx="100" cy="100" r="46" class="dial-center-inset speedometer-center-inset" />

            <!-- Needle -->
            {#if isConnected}
                <polygon 
                    points="
                        {getPolarX(currentAngle - 4, 14)} {getPolarY(currentAngle - 4, 14)}, 
                        {getPolarX(currentAngle, R - 14)} {getPolarY(currentAngle, R - 14)}, 
                        {getPolarX(currentAngle + 4, 14)} {getPolarY(currentAngle + 4, 14)}
                    "
                    class="dial-needle-poly speedometer-needle"
                />
            {/if}
            
            <!-- Center text -->
            <text x="100" y="95" class="dial-text-val speedometer-text-val">{isConnected ? Math.round($smoothedCurrent) : '--'}</text>
            <text 
                x="100" 
                y="110" 
                class="dial-text-deg speedometer-text-ma" 
                class:overlimit={$smoothedCurrent >= currentLimit}
            >
                {isConnected ? 'mA' : ''}
            </text>
            <text x="100" y="122" class="dial-text-lbl">Current Draw</text>
        </svg>
    </div>

    <!-- Slider Controls -->
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
                <div class="slider-fill" style="width: {(targetAngle / 360) * 100}%"></div>
            </div>
        </div>
        
        <div class="slider-group">
            <div class="label-row">
                <span class="label">Velocity</span>
                <span class="value-highlight">{targetVelocity === 0 ? 'Default' : `${targetVelocity} °/s`}</span>
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
                <div class="slider-fill velocity-fill" style="width: {(targetVelocity / 1000) * 100}%"></div>
            </div>
            <span class="hint-text">0 = flash default speed</span>
        </div>

        <div class="slider-group">
            <div class="label-row">
                <span class="label">Force Limit</span>
                <span class="value-highlight">{targetCurrent === 0 ? 'Default' : `${targetCurrent} mA`}</span>
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
                <div class="slider-fill current-fill" style="width: {targetCurrent === 0 ? 0 : (targetCurrent / currentLimit) * 100}%"></div>
            </div>
            <span class="hint-text">0 = flash default limit</span>
        </div>

        <div class="slider-group toggle-group">
            <div class="toggle-row">
                <span class="label">Actuator</span>
                <span class="status-indicator" class:armed={isArmed} class:disarmed={!isArmed}>
                    {isConnected ? (isArmed ? 'Armed' : 'Disarmed') : '—'}
                </span>
            </div>
            <button 
                class="btn small disarm-btn" 
                class:armed={isArmed}
                disabled={!isConnected} 
                onclick={toggleArm}
            >
                {isArmed ? 'Disarm' : 'Arm & Hold'}
            </button>
        </div>
    </div>
</div>

<style>
    /* ── Panel ─────────────────────────────────────────── */
    .glass-subpanel {
        background: rgba(255, 255, 255, 0.03);
        border: 1px solid rgba(255, 255, 255, 0.06);
        border-radius: 16px;
        padding: 1.5rem;
        display: flex;
        flex-direction: column;
        gap: 1.5rem;
    }
    .panel-header {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding-bottom: 0.8rem;
        border-bottom: 1px solid rgba(255, 255, 255, 0.06);
    }
    .panel-header h3 {
        margin-bottom: 0;
        font-size: 0.85rem;
        text-transform: uppercase;
        letter-spacing: 0.08em;
        color: var(--text-secondary, #a1a1a6);
        font-weight: 600;
    }
    .control-badge {
        font-size: 0.68rem;
        font-weight: 600;
        text-transform: uppercase;
        letter-spacing: 0.06em;
        background: rgba(255, 255, 255, 0.04);
        color: var(--text-muted);
        padding: 0.2rem 0.6rem;
        border-radius: 6px;
        border: 1px solid rgba(255, 255, 255, 0.06);
        transition: all 0.25s ease;
    }
    .control-badge.active {
        background: rgba(10, 132, 255, 0.1);
        color: var(--accent, #0A84FF);
        border-color: rgba(10, 132, 255, 0.2);
    }

    /* ── Dial Container ────────────────────────────────── */
    .dial-container {
        display: flex;
        justify-content: center;
        align-items: center;
        gap: 2rem;
        user-select: none;
    }
    .servo-svg-dial {
        cursor: pointer;
        transition: opacity 0.3s ease;
    }
    .servo-svg-dial.disabled {
        cursor: not-allowed;
        opacity: 0.2;
    }
    .speedometer-svg-dial {
        cursor: default;
    }
    .speedometer-svg-dial.disabled {
        opacity: 0.2;
    }

    /* ── SVG Dial Elements ─────────────────────────────── */
    .dial-outer-border {
        fill: none;
        stroke: rgba(255, 255, 255, 0.04);
        stroke-width: 0.5px;
    }

    .dial-tick {
        stroke: rgba(255, 255, 255, 0.1);
        stroke-width: 1px;
        transition: stroke 0.2s ease;
    }
    .dial-tick.major {
        stroke: rgba(255, 255, 255, 0.2);
        stroke-width: 1.5px;
    }

    .dial-track {
        fill: none;
        stroke: rgba(255, 255, 255, 0.06);
        stroke-width: 5px;
    }

    .dial-fill-actual {
        fill: none;
        stroke: var(--accent, #0A84FF);
        stroke-width: 5px;
        stroke-linecap: round;
    }

    .dial-center-inset {
        fill: #1c1c1e;
        stroke: rgba(255, 255, 255, 0.06);
        stroke-width: 0.5px;
    }

    .dial-needle-poly {
        fill: var(--accent, #0A84FF);
        stroke: rgba(255, 255, 255, 0.5);
        stroke-width: 0.5px;
        transition: fill 0.2s ease;
    }
    .dial-needle-poly.disarmed {
        fill: var(--text-muted, #6e6e73) !important;
        stroke: rgba(255, 255, 255, 0.15) !important;
    }

    .dial-target-handle {
        fill: var(--warning, #FF9F0A);
        stroke: rgba(255, 255, 255, 0.7);
        stroke-width: 1.5px;
        cursor: grab;
        transition: r 0.15s ease;
    }
    .dial-target-halo {
        fill: rgba(255, 159, 10, 0.06);
        stroke: rgba(255, 159, 10, 0.15);
        stroke-width: 1px;
        stroke-dasharray: 2, 3;
        pointer-events: none;
        transition: all 0.15s ease;
    }
    .dial-target-halo.dragging {
        stroke-width: 1.5px;
        r: 15;
        stroke: rgba(255, 159, 10, 0.3);
        fill: rgba(255, 159, 10, 0.08);
    }

    /* ── Center Typography ──────────────────────────────── */
    .dial-text-val {
        fill: var(--text-main, #f5f5f7);
        font-size: 2rem;
        font-weight: 700;
        text-anchor: middle;
        dominant-baseline: middle;
        font-family: var(--font), monospace;
        letter-spacing: -0.5px;
    }
    .dial-text-deg {
        fill: var(--accent, #0A84FF);
        font-size: 0.55rem;
        font-weight: 600;
        letter-spacing: 1.5px;
        text-anchor: middle;
        dominant-baseline: middle;
    }
    .dial-text-lbl {
        fill: var(--text-muted, #6e6e73);
        font-size: 0.5rem;
        text-transform: uppercase;
        letter-spacing: 1px;
        text-anchor: middle;
        dominant-baseline: middle;
    }

    /* ── Speedometer Overrides ──────────────────────────── */
    .speedometer-center-inset {
        stroke: rgba(255, 159, 10, 0.06) !important;
    }

    .speedometer-tick {
        stroke: rgba(255, 255, 255, 0.08);
        transition: stroke 0.2s ease;
    }
    .speedometer-tick.highlighted {
        stroke: var(--warning, #FF9F0A) !important;
    }
    .speedometer-tick.red-line {
        stroke: rgba(255, 69, 58, 0.2);
    }
    .speedometer-tick.red-line.highlighted {
        stroke: var(--danger, #FF453A) !important;
    }

    .speedometer-tick-label {
        fill: rgba(255, 255, 255, 0.2);
        font-size: 0.45rem;
        font-weight: 600;
        text-anchor: middle;
        dominant-baseline: middle;
        font-family: var(--font), monospace;
    }
    .speedometer-tick-label.highlighted {
        fill: var(--warning, #FF9F0A);
    }
    .speedometer-tick-label.red-line {
        fill: rgba(255, 69, 58, 0.3);
    }
    .speedometer-tick-label.red-line.highlighted {
        fill: var(--danger, #FF453A);
    }

    .speedometer-red-line {
        fill: none;
        stroke: var(--danger, #FF453A);
        stroke-width: 2px;
        stroke-linecap: round;
        opacity: 0.5;
    }

    .speedometer-fill-actual {
        stroke: var(--warning, #FF9F0A) !important;
        stroke-width: 5px;
        stroke-linecap: round;
    }

    .speedometer-needle {
        fill: var(--warning, #FF9F0A) !important;
        stroke: rgba(255, 255, 255, 0.5);
        stroke-width: 0.5px;
    }

    .speedometer-text-val {
        font-family: var(--font), monospace;
        letter-spacing: -0.5px;
    }
    .speedometer-text-ma {
        fill: var(--warning, #FF9F0A) !important;
        transition: fill 0.2s ease;
    }
    .speedometer-text-ma.overlimit {
        fill: var(--danger, #FF453A) !important;
        animation: subtlePulse 2s ease-in-out infinite;
    }

    @keyframes subtlePulse {
        0%, 100% { opacity: 1; }
        50% { opacity: 0.5; }
    }

    /* ── Slider Controls ───────────────────────────────── */
    .slider-controls {
        display: flex;
        flex-direction: column;
        gap: 1rem;
    }
    .slider-group {
        display: flex;
        flex-direction: column;
        gap: 0.4rem;
    }
    .label-row {
        display: flex;
        justify-content: space-between;
        align-items: baseline;
        font-size: 0.8rem;
    }
    .label {
        color: var(--text-muted, #6e6e73);
        font-weight: 500;
        text-transform: uppercase;
        font-size: 0.7rem;
        letter-spacing: 0.05em;
    }
    .value-highlight {
        color: var(--text-main, #f5f5f7);
        font-weight: 600;
        font-family: var(--font), monospace;
        font-size: 0.82rem;
        font-variant-numeric: tabular-nums;
    }

    .slider-wrapper {
        position: relative;
        display: flex;
        align-items: center;
        background: rgba(255, 255, 255, 0.06);
        border-radius: 3px;
        height: 4px;
        width: 100%;
        overflow: visible;
    }

    .slider-fill {
        position: absolute;
        left: 0;
        top: 0;
        height: 100%;
        background: var(--accent, #0A84FF);
        border-radius: 3px;
        pointer-events: none;
        z-index: 1;
        transition: width 0.05s linear;
    }
    .slider-fill.velocity-fill {
        background: var(--indigo, #5E5CE6);
    }
    .slider-fill.current-fill {
        background: var(--warning, #FF9F0A);
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
        height: 14px;
        width: 14px;
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
        height: 14px;
        width: 14px;
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
        background: var(--text-muted, #6e6e73);
        box-shadow: none;
        cursor: not-allowed;
    }

    .hint-text {
        font-size: 0.68rem;
        color: var(--text-muted, #6e6e73);
        font-style: normal;
        opacity: 0.7;
    }

    /* ── Arm/Disarm Toggle ──────────────────────────────── */
    .toggle-group {
        border-top: 1px solid rgba(255, 255, 255, 0.06);
        padding-top: 1rem;
        display: flex;
        flex-direction: row;
        justify-content: space-between;
        align-items: center;
        margin-top: 0.25rem;
    }

    .toggle-row {
        display: flex;
        flex-direction: column;
        gap: 0.2rem;
    }

    .status-indicator {
        font-family: var(--font), sans-serif;
        font-size: 0.82rem;
        font-weight: 600;
        letter-spacing: 0.02em;
    }
    .status-indicator.armed {
        color: var(--success, #30D158);
    }
    .status-indicator.disarmed {
        color: var(--text-muted, #6e6e73);
    }

    .disarm-btn {
        font-weight: 600;
        font-size: 0.72rem;
        padding: 0.4rem 1rem;
        border-radius: 100px;
        background: rgba(255, 255, 255, 0.05);
        border: 1px solid rgba(255, 255, 255, 0.08);
        color: var(--text-main, #f5f5f7);
        transition: all 0.2s ease;
        text-transform: none;
        letter-spacing: 0.02em;
        cursor: pointer;
    }

    .disarm-btn:not(:disabled).armed:hover {
        background: rgba(255, 69, 58, 0.1);
        color: var(--danger, #FF453A);
        border-color: rgba(255, 69, 58, 0.25);
    }

    .disarm-btn:not(:disabled):not(.armed):hover {
        background: rgba(10, 132, 255, 0.1);
        color: var(--accent, #0A84FF);
        border-color: rgba(10, 132, 255, 0.25);
    }

    .disarm-btn:disabled {
        opacity: 0.3;
        cursor: not-allowed;
    }
</style>
