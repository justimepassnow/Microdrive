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
            class="btn secondary small-btn" 
            disabled={!isConnected || activeId === null}
            onclick={onRead}
        >
            Read Config
        </button>
    </div>
    
    <form onsubmit={handleSubmit}>
        <div class="category-title">Bus Addressing</div>
        <div class="config-grid adr-section">
            <div class="input-group">
                <label for="servo-id">Servo ID (0-127)</label>
                <input type="number" min="0" max="127" id="servo-id" bind:value={servoId} disabled={!isConnected || activeId === null} required onchange={updateRam} />
            </div>
            <div class="info-text">
                <span class="warning-marker">⚠️ Note:</span> Changing ID updates the bus address. Re-scan or select the new ID to continue.
            </div>
        </div>

        <div class="category-title">Motion Safety Limits</div>
        <div class="config-grid">
            <div class="input-group">
                <label for="min-angle">Min Angle (°)</label>
                <input type="number" id="min-angle" bind:value={minAngle} disabled={!isConnected || activeId === null} required onchange={updateRam} />
            </div>
            <div class="input-group">
                <label for="max-angle">Max Angle (°)</label>
                <input type="number" id="max-angle" bind:value={maxAngle} disabled={!isConnected || activeId === null} required onchange={updateRam} />
            </div>
            <div class="input-group">
                <label for="vel-lim">Velocity Limit (°/s)</label>
                <input type="number" id="vel-lim" bind:value={maxVelocity} disabled={!isConnected || activeId === null} required onchange={updateRam} />
            </div>
            <div class="input-group">
                <label for="cur-lim">Current Limit (mA)</label>
                <input type="number" id="cur-lim" bind:value={currentLimit} disabled={!isConnected || activeId === null} required onchange={updateRam} />
            </div>
        </div>
        
        <div class="category-title">PID Position Tuning</div>
        <div class="pid-grid">
            <div class="input-group">
                <label for="kp">Proportional (Kp)</label>
                <input type="number" step="0.01" id="kp" bind:value={kp} disabled={!isConnected || activeId === null} required onchange={updateRam} />
            </div>
            <div class="input-group">
                <label for="ki">Integral (Ki)</label>
                <input type="number" step="0.001" id="ki" bind:value={ki} disabled={!isConnected || activeId === null} required onchange={updateRam} />
            </div>
            <div class="input-group">
                <label for="kd">Derivative (Kd)</label>
                <input type="number" step="0.01" id="kd" bind:value={kd} disabled={!isConnected || activeId === null} required onchange={updateRam} />
            </div>
        </div>

        <div class="category-title">Hardware Calibration</div>
        <div class="config-grid">
            <div class="input-group">
                <label for="zero-adc">Zero ADC Offset</label>
                <input type="number" id="zero-adc" bind:value={zeroAdc} disabled={!isConnected || activeId === null} required onchange={updateRam} />
            </div>
            <div class="input-group">
                <label for="adc-per-360">ADC Per 360°</label>
                <input type="number" id="adc-per-360" bind:value={adcPer360} disabled={!isConnected || activeId === null} required onchange={updateRam} />
            </div>
        </div>

        <div class="toggle-container">
            <span class="toggle-label">Direction Inversion</span>
            <!-- svelte-ignore a11y_label_has_associated_control -->
            <label class="switch">
                <input type="checkbox" bind:checked={directionInvert} disabled={!isConnected || activeId === null} onchange={updateRam} />
                <span class="slider round"></span>
            </label>
        </div>
        
        <button 
            type="submit" 
            class="btn primary full-width" 
            disabled={!isConnected || activeId === null}
        >
            Write settings to Flash
        </button>
    </form>
</section>

<style>
    .config-view {
        display: flex;
        flex-direction: column;
        gap: 1rem;
        height: 100%;
        border-top: 2px solid var(--accent); /* Glowing indicator */
    }
    .config-header {
        display: flex;
        justify-content: space-between;
        align-items: center;
        margin-bottom: 0.5rem;
    }
    .config-header h2 {
        margin-bottom: 0;
    }
    .small-btn {
        padding: 0.4rem 1rem;
        font-size: 0.85rem;
    }
    .category-title {
        font-size: 0.72rem;
        font-weight: 700;
        text-transform: uppercase;
        color: var(--text-muted);
        letter-spacing: 1.5px;
        margin-top: 1rem;
        margin-bottom: 0.6rem;
        border-bottom: 1px solid rgba(255,255,255,0.03);
        padding-bottom: 0.3rem;
    }
    .config-grid {
        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 0.8rem;
    }
    .pid-grid {
        display: grid;
        grid-template-columns: 1fr 1fr 1fr;
        gap: 0.8rem;
    }
    .input-group {
        display: flex;
        flex-direction: column;
        gap: 0.3rem;
    }
    .input-group label {
        font-size: 0.75rem;
        color: var(--text-muted);
        font-weight: 500;
    }
    input[type=number] {
        width: 100%;
        background: rgba(0,0,0,0.35);
        border: 1px solid rgba(255,255,255,0.06);
        color: var(--text-main);
        padding: 0.5rem;
        border-radius: 6px;
        font-family: var(--font);
        font-size: 0.9rem;
        transition: border-color 0.2s, background 0.2s;
    }
    input[type=number]:focus {
        outline: none;
        border-color: var(--accent);
        background: rgba(0,0,0,0.5);
    }
    input[type=number]:disabled {
        opacity: 0.35;
        cursor: not-allowed;
    }

    /* Premium Toggle Switch */
    .toggle-container {
        display: flex;
        justify-content: space-between;
        align-items: center;
        margin-top: 1.2rem;
        background: rgba(0,0,0,0.25);
        padding: 0.8rem 1rem;
        border-radius: 8px;
        border: 1px solid rgba(255,255,255,0.03);
    }
    .toggle-label {
        font-size: 0.85rem;
        color: var(--text-main);
        font-weight: 500;
    }
    .switch {
        position: relative;
        display: inline-block;
        width: 44px;
        height: 22px;
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
        background-color: rgba(255,255,255,0.08);
        transition: .3s;
        border: 1px solid rgba(255,255,255,0.05);
    }
    .slider:before {
        position: absolute;
        content: "";
        height: 14px;
        width: 14px;
        left: 3px;
        bottom: 3px;
        background-color: var(--text-muted);
        transition: .3s;
    }
    input:checked + .slider {
        background-color: rgba(0, 240, 255, 0.15);
        border-color: var(--accent);
    }
    input:checked + .slider:before {
        background-color: var(--accent);
        transform: translateX(22px);
        box-shadow: 0 0 8px var(--accent);
    }
    input:disabled + .slider {
        opacity: 0.4;
        cursor: not-allowed;
    }
    .slider.round {
        border-radius: 22px;
    }
    .slider.round:before {
        border-radius: 50%;
    }
    
    .adr-section {
        align-items: center;
    }
    .info-text {
        font-size: 0.72rem;
        color: var(--text-muted);
        line-height: 1.35;
        padding-top: 0.8rem;
    }
    .warning-marker {
        color: var(--warning);
        font-weight: 700;
    }
</style>
