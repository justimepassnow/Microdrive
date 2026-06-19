<!-- src/components/ConfigPanel.svelte -->
<script>

    let { 
        isConnected = false, 
        activeId = null, 
        config = null, 
        onRead, 
        onWrite 
    } = $props();

    // Local form values
    let servoId = $state("");
    let minAngle = $state("");
    let maxAngle = $state("");
    let maxVelocity = $state("");
    let currentLimit = $state("");
    let kp = $state("");
    let ki = $state("");
    let kd = $state("");
    let directionInvert = $state(false);
    let zeroAdc = $state("");
    let adcPer360 = $state("");

    // Sync local form states when config is read from device
    $effect(() => {
        if (config) {
            servoId = config.servo_id ?? "";
            minAngle = config.min_angle ?? "";
            maxAngle = config.max_angle ?? "";
            maxVelocity = config.max_velocity ?? "";
            currentLimit = config.current_limit ?? "";
            kp = config.kp !== undefined ? config.kp.toFixed(2) : "";
            ki = config.ki !== undefined ? config.ki.toFixed(3) : "";
            kd = config.kd !== undefined ? config.kd.toFixed(2) : "";
            directionInvert = config.direction_invert ?? false;
            zeroAdc = config.zero_adc ?? "";
            adcPer360 = config.adc_per_360 ?? "";
        } else {
            // Reset fields
            servoId = "";
            minAngle = "";
            maxAngle = "";
            maxVelocity = "";
            currentLimit = "";
            kp = "";
            ki = "";
            kd = "";
            directionInvert = false;
            zeroAdc = "";
            adcPer360 = "";
        }
    });

    function updateRam() {
        if (!isConnected || activeId === null) return;
        
        const idVal = parseInt(servoId, 10);
        const minA = parseInt(minAngle, 10);
        const maxA = parseInt(maxAngle, 10);
        const maxV = parseInt(maxVelocity, 10);
        const curL = parseInt(currentLimit, 10);
        const kpVal = parseFloat(kp);
        const kiVal = parseFloat(ki);
        const kdVal = parseFloat(kd);
        const zeroA = parseInt(zeroAdc, 10);
        const adcP = parseInt(adcPer360, 10);

        if (isNaN(idVal) || isNaN(minA) || isNaN(maxA) || isNaN(maxV) || isNaN(curL) ||
            isNaN(kpVal) || isNaN(kiVal) || isNaN(kdVal) || isNaN(zeroA) || isNaN(adcP)) {
            return;
        }

        const params = {
            servo_id: idVal,
            min_angle: minA,
            max_angle: maxA,
            max_velocity: maxV,
            current_limit: curL,
            kp: kpVal,
            ki: kiVal,
            kd: kdVal,
            direction_invert: directionInvert,
            zero_adc: zeroA,
            adc_per_360: adcP,
            ram_only: true
        };
        
        onWrite(params);
    }


    function handleSubmit(e) {
        e.preventDefault();
        if (!isConnected || activeId === null) return;
        
        const params = {
            servo_id: parseInt(servoId, 10),
            min_angle: parseInt(minAngle, 10),
            max_angle: parseInt(maxAngle, 10),
            max_velocity: parseInt(maxVelocity, 10),
            current_limit: parseInt(currentLimit, 10),
            kp: parseFloat(kp),
            ki: parseFloat(ki),
            kd: parseFloat(kd),
            direction_invert: directionInvert,
            zero_adc: parseInt(zeroAdc, 10),
            adc_per_360: parseInt(adcPer360, 10),
            ram_only: false
        };
        
        onWrite(params);
    }
</script>

<section class="glass-panel config-view">
    <div class="config-header">
        <h2>Configuration</h2>
        <button 
            type="button"
            class="btn secondary small-btn read-btn" 
            disabled={!isConnected || activeId === null}
            onclick={onRead}
        >
            <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <polyline points="1 4 1 10 7 10"></polyline>
                <path d="M3.51 15a9 9 0 1 0 2.13-9.36L1 10"></path>
            </svg>
            Read
        </button>
    </div>
    
    <form onsubmit={handleSubmit} class="config-form">
        <!-- Bus Addressing Section -->
        <div class="config-section">
            <div class="category-title">Bus Addressing</div>
            <div class="section-card">
                <div class="config-grid adr-section">
                    <div class="input-group">
                        <label for="servo-id">Servo ID</label>
                        <div class="input-wrap">
                            <input type="number" min="0" max="127" id="servo-id" bind:value={servoId} disabled={!isConnected || activeId === null} required onchange={updateRam} placeholder="0–127" />
                        </div>
                    </div>
                </div>
                <div class="info-text">
                    <span class="warning-marker">
                        <svg width="12" height="12" viewBox="0 0 24 24" fill="currentColor"><path d="M12 2L1 21h22L12 2zm0 4l7.53 13H4.47L12 6zm-1 5v4h2v-4h-2zm0 6v2h2v-2h-2z"/></svg>
                    </span>
                    <span>Changing ID updates the bus address. Re-scan or select the new ID to continue.</span>
                </div>
            </div>
        </div>

        <!-- Motion Safety Limits Section -->
        <div class="config-section">
            <div class="category-title">Motion Limits</div>
            <div class="section-card">
                <div class="config-grid">
                    <div class="input-group">
                        <label for="min-angle">Min Angle</label>
                        <div class="input-wrap">
                            <input type="number" id="min-angle" bind:value={minAngle} disabled={!isConnected || activeId === null} required onchange={updateRam} />
                            <span class="input-unit">°</span>
                        </div>
                    </div>
                    <div class="input-group">
                        <label for="max-angle">Max Angle</label>
                        <div class="input-wrap">
                            <input type="number" id="max-angle" bind:value={maxAngle} disabled={!isConnected || activeId === null} required onchange={updateRam} />
                            <span class="input-unit">°</span>
                        </div>
                    </div>
                    <div class="input-group">
                        <label for="vel-lim">Velocity Limit</label>
                        <div class="input-wrap">
                            <input type="number" id="vel-lim" bind:value={maxVelocity} disabled={!isConnected || activeId === null} required onchange={updateRam} />
                            <span class="input-unit">°/s</span>
                        </div>
                    </div>
                    <div class="input-group">
                        <label for="cur-lim">Current Limit</label>
                        <div class="input-wrap">
                            <input type="number" id="cur-lim" bind:value={currentLimit} disabled={!isConnected || activeId === null} required onchange={updateRam} />
                            <span class="input-unit">mA</span>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        
        <!-- PID Position Tuning Section -->
        <div class="config-section">
            <div class="category-title">PID Tuning</div>
            <div class="section-card">
                
                <div class="pid-grid">
                    <div class="input-group">
                        <label for="kp">Kp</label>
                        <div class="input-wrap">
                            <input type="number" step="0.01" id="kp" bind:value={kp} disabled={!isConnected || activeId === null} required onchange={updateRam} />
                        </div>
                        <span class="input-hint">Proportional</span>
                    </div>
                    <div class="input-group">
                        <label for="ki">Ki</label>
                        <div class="input-wrap">
                            <input type="number" step="0.001" id="ki" bind:value={ki} disabled={!isConnected || activeId === null} required onchange={updateRam} />
                        </div>
                        <span class="input-hint">Integral</span>
                    </div>
                    <div class="input-group">
                        <label for="kd">Kd</label>
                        <div class="input-wrap">
                            <input type="number" step="0.01" id="kd" bind:value={kd} disabled={!isConnected || activeId === null} required onchange={updateRam} />
                        </div>
                        <span class="input-hint">Derivative</span>
                    </div>
                </div>
            </div>
        </div>

        <!-- Hardware Calibration Section -->
        <div class="config-section">
            <div class="category-title">Calibration</div>
            <div class="section-card">
                <div class="config-grid">
                    <div class="input-group">
                        <label for="zero-adc">Zero ADC Offset</label>
                        <div class="input-wrap">
                            <input type="number" id="zero-adc" bind:value={zeroAdc} disabled={!isConnected || activeId === null} required onchange={updateRam} />
                        </div>
                    </div>
                    <div class="input-group">
                        <label for="adc-per-360">ADC Per 360°</label>
                        <div class="input-wrap">
                            <input type="number" id="adc-per-360" bind:value={adcPer360} disabled={!isConnected || activeId === null} required onchange={updateRam} />
                        </div>
                    </div>
                </div>

                <div class="toggle-container">
                    <div class="toggle-info">
                        <span class="toggle-label">Direction Inversion</span>
                        <span class="toggle-sublabel">Reverse motor rotation direction</span>
                    </div>
                    <!-- svelte-ignore a11y_label_has_associated_control -->
                    <label class="switch">
                        <input type="checkbox" bind:checked={directionInvert} disabled={!isConnected || activeId === null} onchange={updateRam} />
                        <span class="slider round"></span>
                    </label>
                </div>
            </div>
        </div>
        
        <button 
            type="submit" 
            class="btn primary full-width flash-btn" 
            disabled={!isConnected || activeId === null}
        >
            <svg width="15" height="15" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <path d="M19 21H5a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h11l5 5v11a2 2 0 0 1-2 2z"></path>
                <polyline points="17 21 17 13 7 13 7 21"></polyline>
                <polyline points="7 3 7 8 15 8"></polyline>
            </svg>
            Write to Flash
        </button>
    </form>
</section>

<style>
    /* ── CSS Variables (scoped) ── */
    .config-view {
        --accent: #0A84FF;
        --accent-hover: #409CFF;
        --accent-glow: rgba(10, 132, 255, 0.15);
        --accent-subtle: rgba(10, 132, 255, 0.08);
        --text-main: #F5F5F7;
        --text-secondary: #A1A1A6;
        --text-muted: #86868B;
        --warning: #FF9F0A;
        --font: 'Inter', -apple-system, BlinkMacSystemFont, 'SF Pro Text', 'Segoe UI', sans-serif;
        --panel-bg: rgba(28, 28, 30, 0.72);
        --card-bg: rgba(44, 44, 46, 0.55);
        --card-border: rgba(255, 255, 255, 0.06);
        --input-bg: rgba(0, 0, 0, 0.28);
        --input-border: rgba(255, 255, 255, 0.08);
        --input-focus-bg: rgba(0, 0, 0, 0.42);
        --radius-sm: 8px;
        --radius-md: 12px;
        --radius-lg: 16px;
        --transition: 200ms cubic-bezier(0.25, 0.1, 0.25, 1);
    }



    /* ── Panel Container ── */
    .config-view {
        display: flex;
        flex-direction: column;
        gap: 0;
        height: 100%;
        font-family: var(--font);
        border-top: none;
        overflow-y: auto;
        overflow-x: hidden;
        scrollbar-width: thin;
        scrollbar-color: rgba(255,255,255,0.08) transparent;
    }

    .config-view::-webkit-scrollbar {
        width: 5px;
    }
    .config-view::-webkit-scrollbar-track {
        background: transparent;
    }
    .config-view::-webkit-scrollbar-thumb {
        background: rgba(255,255,255,0.1);
        border-radius: 10px;
    }

    /* ── Header ── */
    .config-header {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding-bottom: 1.25rem;
        margin-bottom: 0.25rem;
        border-bottom: 1px solid rgba(255, 255, 255, 0.04);
        flex-shrink: 0;
    }

    .config-header h2 {
        margin-bottom: 0;
        font-size: 1.15rem;
        font-weight: 650;
        letter-spacing: -0.02em;
        color: var(--text-main);
    }

    /* Read Button — Ghost / Text style */
    .read-btn {
        display: inline-flex;
        align-items: center;
        gap: 5px;
        padding: 6px 14px;
        font-size: 0.78rem;
        font-weight: 500;
        font-family: var(--font);
        color: var(--accent);
        background: transparent;
        border: 1px solid rgba(10, 132, 255, 0.2);
        border-radius: 100px;
        cursor: pointer;
        transition: all var(--transition);
        letter-spacing: 0.01em;
    }

    .read-btn:hover:not(:disabled) {
        background: var(--accent-subtle);
        border-color: rgba(10, 132, 255, 0.35);
    }

    .read-btn:active:not(:disabled) {
        transform: scale(0.96);
    }

    .read-btn:disabled {
        opacity: 0.3;
        cursor: not-allowed;
    }

    .read-btn svg {
        flex-shrink: 0;
        opacity: 0.85;
    }

    /* ── Form ── */
    .config-form {
        display: flex;
        flex-direction: column;
        gap: 0;
        flex: 1;
        min-height: 0;
    }

    /* ── Sections ── */
    .config-section {
        padding: 0.5rem 0 0.35rem;
    }

    /* ── Category Title — Small caps style ── */
    .category-title {
        font-size: 0.68rem;
        font-weight: 600;
        text-transform: uppercase;
        color: var(--text-muted);
        letter-spacing: 0.08em;
        margin-bottom: 0.6rem;
        padding-bottom: 0;
        border-bottom: none;
        margin-top: 0;
    }

    /* ── Section Card ── */
    .section-card {
        background: var(--card-bg);
        border: 1px solid var(--card-border);
        border-radius: var(--radius-md);
        padding: 0.85rem;
        backdrop-filter: blur(8px);
        -webkit-backdrop-filter: blur(8px);
        transition: border-color var(--transition);
    }

    .section-card:hover {
        border-color: rgba(255, 255, 255, 0.09);
    }

    /* ── Grid Layouts ── */
    .config-grid {
        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 0.75rem;
    }

    .pid-grid {
        display: grid;
        grid-template-columns: 1fr 1fr 1fr;
        gap: 0.75rem;
    }

    /* ── Input Group ── */
    .input-group {
        display: flex;
        flex-direction: column;
        gap: 0.3rem;
    }

    .input-group label {
        font-size: 0.72rem;
        color: var(--text-secondary);
        font-weight: 500;
        letter-spacing: 0.01em;
    }

    .input-wrap {
        position: relative;
        display: flex;
        align-items: center;
    }

    .input-unit {
        position: absolute;
        right: 10px;
        font-size: 0.7rem;
        color: var(--text-muted);
        font-weight: 500;
        pointer-events: none;
        opacity: 0.7;
    }

    .input-hint {
        font-size: 0.62rem;
        color: var(--text-muted);
        font-weight: 400;
        opacity: 0.7;
        margin-top: -1px;
    }

    input[type=number] {
        width: 100%;
        background: var(--input-bg);
        border: 1px solid var(--input-border);
        color: var(--text-main);
        padding: 0.5rem 0.65rem;
        border-radius: var(--radius-sm);
        font-family: var(--font);
        font-size: 0.85rem;
        font-weight: 400;
        transition: all var(--transition);
        -moz-appearance: textfield;
        appearance: textfield;
    }

    input[type=number]::-webkit-inner-spin-button,
    input[type=number]::-webkit-outer-spin-button {
        -webkit-appearance: none;
        margin: 0;
    }

    input[type=number]:hover:not(:disabled):not(:focus) {
        border-color: rgba(255, 255, 255, 0.14);
    }

    input[type=number]:focus {
        outline: none;
        border-color: var(--accent);
        background: var(--input-focus-bg);
        box-shadow: 0 0 0 3px var(--accent-glow);
    }

    input[type=number]:disabled {
        opacity: 0.3;
        cursor: not-allowed;
    }

    input[type=number]::placeholder {
        color: var(--text-muted);
        opacity: 0.5;
    }

    /* ── Toggle Switch (iOS style) ── */
    .toggle-container {
        display: flex;
        justify-content: space-between;
        align-items: center;
        margin-top: 0.75rem;
        padding-top: 0.75rem;
        border-top: 1px solid rgba(255, 255, 255, 0.04);
    }

    .toggle-info {
        display: flex;
        flex-direction: column;
        gap: 2px;
    }

    .toggle-label {
        font-size: 0.82rem;
        color: var(--text-main);
        font-weight: 500;
    }

    .toggle-sublabel {
        font-size: 0.66rem;
        color: var(--text-muted);
        font-weight: 400;
    }

    .switch {
        position: relative;
        display: inline-block;
        width: 46px;
        height: 26px;
        flex-shrink: 0;
    }

    .switch input {
        opacity: 0;
        width: 0;
        height: 0;
    }

    .slider {
        position: absolute;
        cursor: pointer;
        top: 0;
        left: 0;
        right: 0;
        bottom: 0;
        background-color: rgba(120, 120, 128, 0.32);
        transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
    }

    .slider:before {
        position: absolute;
        content: "";
        height: 22px;
        width: 22px;
        left: 2px;
        bottom: 2px;
        background-color: #fff;
        transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
        box-shadow:
            0 1px 3px rgba(0, 0, 0, 0.3),
            0 1px 1px rgba(0, 0, 0, 0.15);
    }

    input:checked + .slider {
        background-color: #30D158;
    }

    input:checked + .slider:before {
        transform: translateX(20px);
        box-shadow:
            0 1px 3px rgba(0, 0, 0, 0.25),
            0 1px 1px rgba(0, 0, 0, 0.1);
    }

    input:disabled + .slider {
        opacity: 0.35;
        cursor: not-allowed;
    }

    .slider.round {
        border-radius: 26px;
    }

    .slider.round:before {
        border-radius: 50%;
    }

    /* ── Address Section ── */
    .adr-section {
        grid-template-columns: 1fr;
    }

    /* ── Warning / Info Text ── */
    .info-text {
        display: flex;
        align-items: flex-start;
        gap: 6px;
        font-size: 0.68rem;
        color: var(--text-muted);
        line-height: 1.5;
        margin-top: 0.65rem;
        padding: 0.55rem 0.65rem;
        background: rgba(255, 159, 10, 0.05);
        border-radius: var(--radius-sm);
        border: 1px solid rgba(255, 159, 10, 0.1);
    }

    .info-text span:last-child {
        flex: 1;
    }

    .warning-marker {
        color: var(--warning);
        flex-shrink: 0;
        display: flex;
        align-items: center;
        margin-top: 1px;
    }

    /* ── Flash Button — Prominent Pill ── */
    .flash-btn {
        display: inline-flex;
        align-items: center;
        justify-content: center;
        gap: 8px;
        margin-top: 1.25rem;
        padding: 0.7rem 1.5rem;
        font-size: 0.85rem;
        font-weight: 600;
        font-family: var(--font);
        color: #fff;
        background: var(--accent);
        border: none;
        border-radius: 100px;
        cursor: pointer;
        transition: all var(--transition);
        letter-spacing: 0.01em;
        width: 100%;
        flex-shrink: 0;
    }

    .flash-btn:hover:not(:disabled) {
        background: var(--accent-hover);
        box-shadow: 0 4px 20px rgba(10, 132, 255, 0.3);
        transform: translateY(-1px);
    }

    .flash-btn:active:not(:disabled) {
        transform: translateY(0) scale(0.98);
        box-shadow: 0 2px 8px rgba(10, 132, 255, 0.25);
    }

    .flash-btn:disabled {
        opacity: 0.3;
        cursor: not-allowed;
        background: var(--accent);
    }

    .flash-btn svg {
        flex-shrink: 0;
        opacity: 0.9;
    }
</style>
