<!-- src/components/CalibrationWizard.svelte -->
<script>
    import { onMount } from 'svelte';

    let { 
        isConnected = false, 
        activeId = null, 
        telemetry = {}, 
        config = null, 
        sendCommand,
        onRead,
        onClose,
        addLog
    } = $props();

    // Wizard Step State
    // Steps:
    // 0: Welcome / Intro
    // 1: Bus Addressing (ID Configuration)
    // 2: Potentiometer Calibration Mode (Keep vs Manual)
    // 3: Manual Calibration - Lock 0°
    // 4: Manual Calibration - Lock 90°
    // 5: Manual Calibration - Review & Verify
    // 6: Motion safety limits (Min/Max Angle, Speed, Current)
    // 7: PID Position Controller Tuning
    // 8: Final Review & Write to Flash
    // 9: Success & Completed
    let step = $state(0);
    
    // Mode selection for calibration: 'keep' or 'calibrate'
    let calMode = $state('keep'); 

    // Wizard form state variables
    let wizardId = $state(0);
    let zeroAdc = $state(0);
    let adcPer360 = $state(4096);
    let directionInvert = $state(false);
    let minAngle = $state(0);
    let maxAngle = $state(280);
    let maxVelocity = $state(300);
    let currentLimit = $state(500);
    let kp = $state(5.0);
    let ki = $state(0.0);
    let kd = $state(0.1);

    // Live variables during manual calibration locking
    let lockedAdc0 = $state(null);
    let lockedAdc90 = $state(null);
    let isSaving = $state(false);

    // Computed values
    let calculatedAdc360 = $derived.by(() => {
        if (lockedAdc0 === null || lockedAdc90 === null) return 0;
        return Math.abs(lockedAdc90 - lockedAdc0) * 4;
    });

    // Populate working variables from device configuration cache
    $effect(() => {
        if (config) {
            wizardId = config.servo_id ?? activeId ?? 0;
            zeroAdc = config.zero_adc ?? 0;
            adcPer360 = config.adc_per_360 ?? 4096;
            directionInvert = config.direction_invert ?? false;
            minAngle = config.min_angle ?? 0;
            maxAngle = config.max_angle ?? 280;
            maxVelocity = config.max_velocity ?? 300;
            currentLimit = config.current_limit ?? 500;
            kp = config.kp ?? 5.0;
            ki = config.ki ?? 0.0;
            kd = config.kd ?? 0.1;
        } else if (activeId !== null) {
            wizardId = activeId;
        }
    });

    function handleNext() {
        if (step === 1) {
            // Bus Addressing -> Pot Mode Selection
            step = 2;
        } else if (step === 2) {
            if (calMode === 'keep') {
                // Skip calibration -> Motion Limits
                step = 6;
            } else {
                // Start Manual Calibration
                startManualCal();
            }
        } else if (step === 5) {
            // Manual Cal Review -> Motion Limits
            step = 6;
        } else if (step === 6) {
            // Motion Limits -> PID Tuning
            step = 7;
        } else if (step === 7) {
            // PID Tuning -> Final Review
            step = 8;
        }
    }

    function handleBack() {
        if (step === 1) {
            step = 0;
        } else if (step === 2) {
            step = 1;
        } else if (step === 3) {
            step = 2;
        } else if (step === 4) {
            step = 3;
        } else if (step === 5) {
            step = 4;
        } else if (step === 6) {
            if (calMode === 'keep') {
                step = 2;
            } else {
                step = 5;
            }
        } else if (step === 7) {
            step = 6;
        } else if (step === 8) {
            step = 7;
        }
    }

    function handleCancel() {
        if (step >= 3 && step <= 5) {
            addLog('sys', `Configuration Wizard cancelled. Restoring cached config to RAM...`);
            // Re-read flash config to override RAM changes made during calibration
            sendCommand({ cmd: 'read_config', id: activeId });
        }
        onClose();
    }

    // Manual calibration setup
    function startManualCal() {
        if (!isConnected || activeId === null) return;
        addLog('sys', `Starting Manual Pot Calibration. Disarming motor, loading 1:1 scale to RAM...`);
        
        // 1:1 scale trick (zero=0, scale=360) so angle telemetry matches raw ADC
        sendCommand({ 
            cmd: 'configure', 
            id: activeId, 
            params: { zero_adc: 0, adc_per_360: 360, ram_only: true } 
        });
        
        // Disarm/clear error to allow free rotation
        sendCommand({ cmd: 'clear_error', id: activeId });
        
        lockedAdc0 = null;
        lockedAdc90 = null;
        step = 3;
    }

    function handleLock0() {
        lockedAdc0 = telemetry.angle;
        addLog('sys', `Locked 0° point. Raw ADC: ${lockedAdc0}`);
        step = 4;
    }

    function handleLock90() {
        lockedAdc90 = telemetry.angle;
        addLog('sys', `Locked 90° point. Raw ADC: ${lockedAdc90}`);
        
        // Populate calibration variables from locked values
        zeroAdc = lockedAdc0;
        adcPer360 = calculatedAdc360;
        step = 5;
    }

    async function handleSave() {
        if (!isConnected || activeId === null) return;
        isSaving = true;
        
        addLog('sys', `Writing complete configuration to Flash for ID ${activeId}...`);
        
        const params = {
            servo_id: parseInt(wizardId, 10),
            zero_adc: parseInt(zeroAdc, 10),
            adc_per_360: parseInt(adcPer360, 10),
            direction_invert: directionInvert,
            min_angle: parseInt(minAngle, 10),
            max_angle: parseInt(maxAngle, 10),
            max_velocity: parseInt(maxVelocity, 10),
            current_limit: parseInt(currentLimit, 10),
            kp: parseFloat(kp),
            ki: parseFloat(ki),
            kd: parseFloat(kd),
            ram_only: false
        };

        sendCommand({
            cmd: 'configure',
            id: activeId,
            params
        });

        // Small timeout to allow write-to-flash, then move to success step
        setTimeout(() => {
            isSaving = false;
            step = 9;
        }, 1000);
    }

    function handleFinish() {
        // Reload final flash settings into application state
        onRead();
        onClose();
    }
</script>

<div class="cal-wizard glass-subpanel">
    <div class="panel-header">
        <h3>Configuration Wizard</h3>
        {#if step > 0 && step < 9}
            <span class="step-indicator">
                Step {step === 1 ? '1' : step === 2 ? '2' : step >= 3 && step <= 5 ? '2 (Cal)' : step === 6 ? '3' : step === 7 ? '4' : '5'} of 5
            </span>
        {/if}
    </div>

    <!-- Step Progress Milestone Tracker (only visible in wizard body) -->
    {#if step > 0 && step < 9}
        <div class="steps-progress">
            <div class="step-milestone" class:active={step === 1} class:done={step > 1}>
                <div class="step-node">1</div>
                <span class="step-lbl">Bus</span>
            </div>
            <div class="step-line" class:active={step >= 2}></div>
            
            <div class="step-milestone" class:active={step >= 2 && step <= 5} class:done={step > 5}>
                <div class="step-node">2</div>
                <span class="step-lbl">Cal</span>
            </div>
            <div class="step-line" class:active={step >= 6}></div>
            
            <div class="step-milestone" class:active={step === 6} class:done={step > 6}>
                <div class="step-node">3</div>
                <span class="step-lbl">Limits</span>
            </div>
            <div class="step-line" class:active={step >= 7}></div>
            
            <div class="step-milestone" class:active={step === 7} class:done={step > 7}>
                <div class="step-node">4</div>
                <span class="step-lbl">PID</span>
            </div>
            <div class="step-line" class:active={step >= 8}></div>
            
            <div class="step-milestone" class:active={step === 8}>
                <div class="step-node">✓</div>
                <span class="step-lbl">Save</span>
            </div>
        </div>
    {/if}

    <!-- STEP 0: Welcome -->
    {#if step === 0}
        <div class="wizard-body">
            <h4 class="title">Servo Setup & Tuning Wizard</h4>
            <p class="description">
                This guided wizard will take you step-by-step through configuring your actuator's bus parameters, physical potentiometer calibration, safe operational limits, and PID feedback gains.
            </p>
            
            {#if activeId === 0}
                <div class="alert-box warning">
                    <span class="alert-icon">⚠️</span>
                    <span class="alert-text">
                        <strong>Default ID 0 Detected:</strong> This servo is running on default factory settings. We highly recommend assigning a unique bus address to prevent network collisions.
                    </span>
                </div>
            {:else}
                <div class="alert-box note">
                    <span class="alert-icon">ℹ️</span>
                    <span class="alert-text">
                        <strong>Reconfiguration Mode:</strong> Existing configuration variables have been pre-populated. You may run through this wizard to adjust specific groups while keeping others intact.
                    </span>
                </div>
            {/if}
            
            <div class="actions">
                <button class="btn primary" onclick={() => step = 1} disabled={!isConnected || activeId === null}>
                    Begin Configuration
                </button>
                <button class="btn secondary" onclick={onClose}>
                    Close
                </button>
            </div>
        </div>

    <!-- STEP 1: Bus Addressing -->
    {:else if step === 1}
        <div class="wizard-body">
            <h4 class="title">Step 1: Bus Addressing</h4>
            <p class="description">
                Configure the communication node ID for this servo on the serial control bus.
            </p>
            
            <div class="form-container">
                <div class="input-group full-width-input">
                    <label for="wiz-servo-id">New Servo Node ID</label>
                    <div class="input-wrap">
                        <input type="number" id="wiz-servo-id" min="0" max="127" bind:value={wizardId} placeholder="e.g. 1" />
                    </div>
                    <span class="input-hint">Valid address range: 0–127. Each servo on a shared bus must have a unique ID.</span>
                </div>
            </div>

            {#if wizardId === 0}
                <div class="alert-box danger">
                    <span class="alert-icon">⚠️</span>
                    <span class="alert-text">
                        Using ID 0 is not recommended for final deployment. Address conflict risks will arise if another unconfigured servo is added to the bus.
                    </span>
                </div>
            {/if}
            
            <div class="actions">
                <button class="btn primary" onclick={handleNext} disabled={wizardId === null || wizardId < 0 || wizardId > 127}>
                    Next Step
                </button>
                <button class="btn secondary" onclick={handleCancel}>
                    Cancel
                </button>
            </div>
        </div>

    <!-- STEP 2: Calibration Mode Selection -->
    {:else if step === 2}
        <div class="wizard-body">
            <h4 class="title">Step 2: Potentiometer Calibration</h4>
            <p class="description">
                Select whether you wish to recalibrate the potentiometer mapping. 
            </p>

            <div class="cal-mode-selection">
                <!-- svelte-ignore a11y_click_events_have_key_events -->
                <!-- svelte-ignore a11y_no_static_element_interactions -->
                <div class="mode-card" class:active={calMode === 'keep'} onclick={() => calMode = 'keep'}>
                    <div class="mode-icon">💾</div>
                    <div class="mode-details">
                        <span class="mode-title">Keep Current Calibration</span>
                        <p class="mode-desc">Retain existing pot zero offsets and scaling. Highly recommended if physical mounting is unchanged.</p>
                    </div>
                </div>

                <!-- svelte-ignore a11y_click_events_have_key_events -->
                <!-- svelte-ignore a11y_no_static_element_interactions -->
                <div class="mode-card" class:active={calMode === 'calibrate'} onclick={() => calMode = 'calibrate'}>
                    <div class="mode-icon">🔧</div>
                    <div class="mode-details">
                        <span class="mode-title">Perform Manual Calibration</span>
                        <p class="mode-desc">Disarms the motor allowing you to rotate the output shaft freely by hand to lock reference angles.</p>
                    </div>
                </div>
            </div>

            {#if calMode === 'keep'}
                <div class="keep-summary-box">
                    <div class="mini-grid">
                        <div class="mini-card">
                            <span class="c-lbl">Zero ADC</span>
                            <span class="c-val">{zeroAdc}</span>
                        </div>
                        <div class="mini-card">
                            <span class="c-lbl">ADC per 360°</span>
                            <span class="c-val">{adcPer360}</span>
                        </div>
                    </div>
                    <div class="toggle-container cal-invert-toggle">
                        <div class="toggle-info">
                            <span class="toggle-label">Direction Inversion</span>
                            <span class="toggle-sublabel">Reverse rotation direction</span>
                        </div>
                        <!-- svelte-ignore a11y_label_has_associated_control -->
                        <label class="switch">
                            <input type="checkbox" bind:checked={directionInvert} />
                            <span class="slider round"></span>
                        </label>
                    </div>
                </div>
            {/if}
            
            <div class="actions">
                <button class="btn primary" onclick={handleNext}>
                    Next Step
                </button>
                <button class="btn secondary" onclick={handleBack}>
                    Back
                </button>
                <button class="btn secondary" onclick={handleCancel}>
                    Cancel
                </button>
            </div>
        </div>

    <!-- STEP 3: Manual Calibration - Lock 0° -->
    {:else if step === 3}
        <div class="wizard-body">
            <h4 class="title">Set 0° Reference Position</h4>
            <p class="description">
                Manually rotate the servo output shaft to your desired <strong>0° (reference)</strong> index point.
            </p>

            <div class="live-adc-display">
                <span class="label">Live Raw ADC Value</span>
                <span class="value">{telemetry.angle}</span>
                <div class="adc-bar-bg">
                    <div class="adc-bar-fill" style="width: {(telemetry.angle / 4095) * 100}%"></div>
                </div>
            </div>
            
            <div class="actions">
                <button class="btn primary" onclick={handleLock0}>
                    Lock 0° Position
                </button>
                <button class="btn secondary" onclick={handleBack}>
                    Back
                </button>
                <button class="btn secondary danger-hover" onclick={handleCancel}>
                    Cancel
                </button>
            </div>
        </div>

    <!-- STEP 4: Manual Calibration - Lock 90° -->
    {:else if step === 4}
        <div class="wizard-body">
            <h4 class="title">Set 90° Reference Position</h4>
            <p class="description">
                Rotate the servo shaft exactly <strong>90° forward</strong> (clockwise) from the 0° point.
            </p>

            <div class="locked-badge">
                <span class="badge-label">Locked 0° ADC:</span>
                <span class="badge-val">{lockedAdc0}</span>
            </div>

            <div class="live-adc-display">
                <span class="label">Live Raw ADC Value</span>
                <span class="value">{telemetry.angle}</span>
                <div class="adc-bar-bg">
                    <div class="adc-bar-fill" style="width: {(telemetry.angle / 4095) * 100}%"></div>
                </div>
                <span class="diff-hint">
                    Delta from 0°: <strong class:positive={telemetry.angle - lockedAdc0 >= 0}>{telemetry.angle - lockedAdc0}</strong> ADC ticks
                </span>
            </div>
            
            <div class="actions">
                <button class="btn primary" onclick={handleLock90} disabled={Math.abs(telemetry.angle - lockedAdc0) < 10}>
                    Lock 90° Position
                </button>
                <button class="btn secondary" onclick={handleBack}>
                    Back
                </button>
                <button class="btn secondary danger-hover" onclick={handleCancel}>
                    Cancel
                </button>
            </div>
        </div>

    <!-- STEP 5: Manual Calibration - Review -->
    {:else if step === 5}
        <div class="wizard-body">
            <h4 class="title">Verify Manual Pot Calibration</h4>
            <p class="description">
                Review the calculated potentiometer scaling variables before proceeding.
            </p>

            <div class="metrics-summary">
                <div class="summary-card">
                    <span class="card-lbl">Zero ADC (0°)</span>
                    <span class="card-val">{zeroAdc}</span>
                </div>
                <div class="summary-card">
                    <span class="card-lbl">ADC per 360°</span>
                    <span class="card-val" class:warning-text={adcPer360 === 0}>{adcPer360}</span>
                </div>
            </div>

            {#if adcPer360 === 0}
                <div class="alert-box danger">
                    <span class="alert-icon">⚠️</span>
                    <span class="alert-text">
                        Error: Potentiometer ADC delta is zero. Potentiometer might be disconnected or broken.
                    </span>
                </div>
            {/if}

            <div class="toggle-container cal-invert-toggle">
                <div class="toggle-info">
                    <span class="toggle-label">Direction Inversion</span>
                    <span class="toggle-sublabel">Reverse motor rotation direction</span>
                </div>
                <!-- svelte-ignore a11y_label_has_associated_control -->
                <label class="switch">
                    <input type="checkbox" bind:checked={directionInvert} />
                    <span class="slider round"></span>
                </label>
            </div>
            
            <div class="actions">
                <button class="btn primary" onclick={handleNext} disabled={adcPer360 === 0}>
                    Next Step
                </button>
                <button class="btn secondary" onclick={handleBack}>
                    Back
                </button>
                <button class="btn secondary danger-hover" onclick={handleCancel}>
                    Cancel
                </button>
            </div>
        </div>

    <!-- STEP 6: Motion Safety Limits -->
    {:else if step === 6}
        <div class="wizard-body">
            <h4 class="title">Step 3: Motion Safety Limits</h4>
            <p class="description">
                Establish operational travel boundaries, maximum velocity, and current draw thresholds.
            </p>
            
            <div class="limits-grid">
                <div class="input-group">
                    <label for="wiz-min-angle">Min Safe Angle Limit</label>
                    <div class="input-wrap">
                        <input type="number" id="wiz-min-angle" bind:value={minAngle} />
                        <span class="input-unit">°</span>
                    </div>
                </div>
                <div class="input-group">
                    <label for="wiz-max-angle">Max Safe Angle Limit</label>
                    <div class="input-wrap">
                        <input type="number" id="wiz-max-angle" bind:value={maxAngle} />
                        <span class="input-unit">°</span>
                    </div>
                </div>
                <div class="input-group">
                    <label for="wiz-vel-lim">Max Velocity Limit</label>
                    <div class="input-wrap">
                        <input type="number" id="wiz-vel-lim" bind:value={maxVelocity} />
                        <span class="input-unit">°/s</span>
                    </div>
                </div>
                <div class="input-group">
                    <label for="wiz-cur-lim">Peak Current Limit</label>
                    <div class="input-wrap">
                        <input type="number" id="wiz-cur-lim" bind:value={currentLimit} />
                        <span class="input-unit">mA</span>
                    </div>
                </div>
            </div>
            
            <div class="actions">
                <button class="btn primary" onclick={handleNext}>
                    Next Step
                </button>
                <button class="btn secondary" onclick={handleBack}>
                    Back
                </button>
                <button class="btn secondary" onclick={handleCancel}>
                    Cancel
                </button>
            </div>
        </div>

    <!-- STEP 7: PID Position Tuning -->
    {:else if step === 7}
        <div class="wizard-body">
            <h4 class="title">Step 4: PID Position Tuning</h4>
            <p class="description">
                Adjust position feedback loop gains. Higher values make responsiveness snappier but risk mechanical vibrations.
            </p>
            
            <div class="pid-grid">
                <div class="input-group">
                    <label for="wiz-kp">Kp (Proportional)</label>
                    <div class="input-wrap">
                        <input type="number" step="0.05" id="wiz-kp" bind:value={kp} />
                    </div>
                    <span class="input-hint">Response force</span>
                </div>
                <div class="input-group">
                    <label for="wiz-ki">Ki (Integral)</label>
                    <div class="input-wrap">
                        <input type="number" step="0.001" id="wiz-ki" bind:value={ki} />
                    </div>
                    <span class="input-hint">Static accuracy</span>
                </div>
                <div class="input-group">
                    <label for="wiz-kd">Kd (Derivative)</label>
                    <div class="input-wrap">
                        <input type="number" step="0.01" id="wiz-kd" bind:value={kd} />
                    </div>
                    <span class="input-hint">Damping/Braking</span>
                </div>
            </div>
            
            <div class="actions">
                <button class="btn primary" onclick={handleNext}>
                    Review Configuration
                </button>
                <button class="btn secondary" onclick={handleBack}>
                    Back
                </button>
                <button class="btn secondary" onclick={handleCancel}>
                    Cancel
                </button>
            </div>
        </div>

    <!-- STEP 8: Review & Write to Flash -->
    {:else if step === 8}
        <div class="wizard-body">
            <h4 class="title">Step 5: Review & Save to Flash</h4>
            <p class="description">
                Verify the operational parameters before uploading them to the non-volatile EEPROM/Flash.
            </p>
            
            <div class="review-table">
                <div class="review-row">
                    <span class="r-lbl">Servo Address</span>
                    <span class="r-val" class:highlight-address={wizardId !== activeId}>
                        {activeId} ➔ <strong>ID {wizardId}</strong>
                    </span>
                </div>
                <div class="review-row">
                    <span class="r-lbl">Pot Calibration</span>
                    <span class="r-val">Zero: {zeroAdc} ADC | Scale: {adcPer360} ADC/360°</span>
                </div>
                <div class="review-row">
                    <span class="r-lbl">Direction Inversion</span>
                    <span class="r-val">{directionInvert ? 'REVERSED (Inverted)' : 'NORMAL'}</span>
                </div>
                <div class="review-row">
                    <span class="r-lbl">Travel Boundaries</span>
                    <span class="r-val">{minAngle}° to {maxAngle}°</span>
                </div>
                <div class="review-row">
                    <span class="r-lbl">Velocity Limit</span>
                    <span class="r-val">{maxVelocity} °/s</span>
                </div>
                <div class="review-row">
                    <span class="r-lbl">Current Limit</span>
                    <span class="r-val">{currentLimit} mA</span>
                </div>
                <div class="review-row">
                    <span class="r-lbl">PID Gains</span>
                    <span class="r-val">Kp: {kp} | Ki: {ki} | Kd: {kd}</span>
                </div>
            </div>
            
            <div class="actions">
                <button class="btn primary flash-save-btn" onclick={handleSave} disabled={isSaving}>
                    {#if isSaving}
                        <span class="spinner-mini"></span> Writing to Flash...
                    {:else}
                        <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                            <path d="M19 21H5a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h11l5 5v11a2 2 0 0 1-2 2z"></path>
                            <polyline points="17 21 17 13 7 13 7 21"></polyline>
                        </svg>
                        Save & Write to Flash
                    {/if}
                </button>
                <button class="btn secondary" onclick={handleBack} disabled={isSaving}>
                    Back
                </button>
                <button class="btn secondary" onclick={handleCancel} disabled={isSaving}>
                    Cancel
                </button>
            </div>
        </div>

    <!-- STEP 9: Success completed -->
    {:else if step === 9}
        <div class="wizard-body success-body">
            <div class="success-icon-wrap">
                <svg class="success-checkmark" viewBox="0 0 52 52">
                    <circle class="checkmark-circle" cx="26" cy="26" r="25" fill="none"/>
                    <path class="checkmark-check" fill="none" d="M14.1 27.2l7.1 7.2 16.7-16.8"/>
                </svg>
            </div>
            
            <h4 class="title text-center">Wizard Completed!</h4>
            <p class="description text-center">
                Servo variables saved to persistent memory. Actuator control is operational with your customized configuration parameters.
            </p>

            {#if wizardId !== activeId}
                <div class="alert-box success-alert text-center">
                    Note: The servo is now active on <strong>ID {wizardId}</strong>. The sidebar has been updated to reflect the new address.
                </div>
            {/if}

            <div class="actions center-actions">
                <button class="btn primary" onclick={handleFinish}>
                    Finish & Exit Setup
                </button>
            </div>
        </div>
    {/if}
</div>

<style>
    /* ── Setup Wizard Core ── */
    .cal-wizard {
        display: flex;
        flex-direction: column;
        gap: 1.25rem;
        --accent: #0A84FF;
        --success: #30D158;
        --warning: #FF9F0A;
        --danger: #FF453A;
        --text-main: #F5F5F7;
        --text-secondary: #A1A1A6;
        --text-muted: #86868B;
        --font: 'Inter', -apple-system, BlinkMacSystemFont, 'SF Pro Text', sans-serif;
    }
    
    .panel-header {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding-bottom: 0.8rem;
        border-bottom: 1px solid rgba(255, 255, 255, 0.06);
    }

    .step-indicator {
        font-size: 0.72rem;
        font-weight: 600;
        color: var(--text-secondary);
        background: rgba(255, 255, 255, 0.05);
        padding: 0.15rem 0.5rem;
        border-radius: 6px;
    }

    /* ── Progress Milestone Tracker ── */
    .steps-progress {
        display: flex;
        align-items: center;
        justify-content: space-between;
        margin-bottom: 0.45rem;
        padding: 0 0.5rem;
    }
    .step-milestone {
        display: flex;
        flex-direction: column;
        align-items: center;
        gap: 0.35rem;
    }
    .step-node {
        width: 26px;
        height: 26px;
        border-radius: 50%;
        background: rgba(255, 255, 255, 0.04);
        border: 1.5px solid rgba(255, 255, 255, 0.1);
        color: var(--text-muted);
        display: flex;
        align-items: center;
        justify-content: center;
        font-size: 0.75rem;
        font-weight: 700;
        transition: all 0.3s ease;
        z-index: 2;
    }
    .step-milestone.active .step-node {
        border-color: var(--accent);
        color: #fff;
        background: rgba(10, 132, 255, 0.15);
        box-shadow: 0 0 8px rgba(10, 132, 255, 0.3);
    }
    .step-milestone.done .step-node {
        border-color: var(--success);
        background: rgba(48, 209, 88, 0.15);
        color: var(--success);
    }
    .step-lbl {
        font-size: 0.62rem;
        font-weight: 600;
        color: var(--text-muted);
        text-transform: uppercase;
        letter-spacing: 0.05em;
        transition: color 0.3s;
    }
    .step-milestone.active .step-lbl {
        color: var(--text-main);
    }
    .step-milestone.done .step-lbl {
        color: var(--success);
    }
    .step-line {
        flex: 1;
        height: 2px;
        background: rgba(255, 255, 255, 0.08);
        margin: 0 0.5rem;
        transform: translateY(-8px);
        transition: background 0.3s ease;
        z-index: 1;
    }
    .step-line.active {
        background: var(--accent);
    }

    /* ── Wizard Body ── */
    .wizard-body {
        display: flex;
        flex-direction: column;
        gap: 1.1rem;
        animation: fadeIn 0.25s ease-out;
    }
    @keyframes fadeIn {
        from { opacity: 0; transform: translateY(4px); }
        to { opacity: 1; transform: translateY(0); }
    }

    .title {
        font-size: 1.05rem;
        font-weight: 650;
        color: var(--text-main);
        letter-spacing: -0.01em;
        margin: 0;
    }
    .description {
        font-size: 0.82rem;
        color: var(--text-secondary);
        line-height: 1.45;
        margin: 0;
    }

    /* ── Mode Selection Cards ── */
    .cal-mode-selection {
        display: flex;
        flex-direction: column;
        gap: 0.75rem;
        margin-top: 0.1rem;
    }
    .mode-card {
        background: rgba(255, 255, 255, 0.02);
        border: 1px solid rgba(255, 255, 255, 0.06);
        border-radius: 10px;
        padding: 0.9rem 1.1rem;
        display: flex;
        gap: 0.95rem;
        cursor: pointer;
        transition: all 0.2s ease;
        align-items: center;
    }
    .mode-card:hover {
        background: rgba(255, 255, 255, 0.04);
        border-color: rgba(255, 255, 255, 0.12);
    }
    .mode-card.active {
        background: rgba(10, 132, 255, 0.06);
        border-color: var(--accent);
        box-shadow: 0 0 10px rgba(10, 132, 255, 0.12);
    }
    .mode-icon {
        font-size: 1.5rem;
        user-select: none;
    }
    .mode-details {
        display: flex;
        flex-direction: column;
        gap: 0.15rem;
    }
    .mode-title {
        font-size: 0.88rem;
        font-weight: 600;
        color: var(--text-main);
    }
    .mode-desc {
        font-size: 0.74rem;
        color: var(--text-muted);
        margin: 0;
        line-height: 1.35;
    }

    /* ── Keep Calibration Mode Summary ── */
    .keep-summary-box {
        background: rgba(0, 0, 0, 0.15);
        border: 1px solid rgba(255, 255, 255, 0.04);
        border-radius: 10px;
        padding: 0.85rem;
        display: flex;
        flex-direction: column;
        gap: 0.75rem;
    }
    .mini-grid {
        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 0.65rem;
    }
    .mini-card {
        background: rgba(255, 255, 255, 0.02);
        border: 1px solid rgba(255, 255, 255, 0.04);
        border-radius: 8px;
        padding: 0.6rem 0.8rem;
        display: flex;
        flex-direction: column;
        gap: 0.1rem;
    }
    .c-lbl {
        font-size: 0.62rem;
        color: var(--text-muted);
        text-transform: uppercase;
        letter-spacing: 0.04em;
    }
    .c-val {
        font-size: 1.05rem;
        font-weight: 700;
        font-family: monospace;
        color: var(--accent);
    }

    /* ── Live Display & Lock Badges ── */
    .live-adc-display {
        background: rgba(0, 0, 0, 0.2);
        border: 1px solid rgba(255, 255, 255, 0.05);
        border-radius: 10px;
        padding: 0.9rem 1.1rem;
        display: flex;
        flex-direction: column;
        gap: 0.45rem;
    }
    .live-adc-display .label {
        font-size: 0.68rem;
        font-weight: 600;
        color: var(--text-muted);
        text-transform: uppercase;
        letter-spacing: 0.05em;
    }
    .live-adc-display .value {
        font-family: monospace;
        font-size: 2.1rem;
        font-weight: 700;
        color: var(--warning);
        line-height: 1.1;
    }
    .adc-bar-bg {
        width: 100%;
        height: 6px;
        background: rgba(255, 255, 255, 0.06);
        border-radius: 3px;
        overflow: hidden;
    }
    .adc-bar-fill {
        height: 100%;
        background: var(--warning);
        border-radius: 3px;
        transition: width 0.08s linear;
    }
    .diff-hint {
        font-size: 0.7rem;
        color: var(--text-muted);
        margin-top: 2px;
    }
    .diff-hint strong {
        color: var(--danger);
    }
    .diff-hint strong.positive {
        color: var(--success);
    }

    .locked-badge {
        display: inline-flex;
        align-items: center;
        gap: 0.4rem;
        background: rgba(255, 255, 255, 0.04);
        border: 1px solid rgba(255, 255, 255, 0.08);
        padding: 0.35rem 0.75rem;
        border-radius: 8px;
        font-size: 0.75rem;
        align-self: flex-start;
    }
    .badge-label {
        color: var(--text-muted);
    }
    .badge-val {
        color: var(--text-main);
        font-weight: 600;
        font-family: monospace;
    }

    /* ── Metrics Summary ── */
    .metrics-summary {
        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 0.75rem;
    }
    .summary-card {
        background: rgba(255, 255, 255, 0.03);
        border: 1px solid rgba(255, 255, 255, 0.05);
        border-radius: 10px;
        padding: 0.75rem 1rem;
        display: flex;
        flex-direction: column;
        gap: 0.2rem;
    }
    .card-lbl {
        font-size: 0.65rem;
        color: var(--text-muted);
        text-transform: uppercase;
        letter-spacing: 0.05em;
    }
    .card-val {
        font-size: 1.25rem;
        font-weight: 700;
        font-family: monospace;
        color: var(--accent);
    }
    .warning-text {
        color: var(--danger);
    }

    /* ── Alert Boxes ── */
    .alert-box {
        display: flex;
        gap: 0.6rem;
        padding: 0.7rem 0.9rem;
        border-radius: 10px;
        font-size: 0.78rem;
        line-height: 1.45;
    }
    .alert-box.note {
        background: rgba(10, 132, 255, 0.06);
        border: 1px solid rgba(10, 132, 255, 0.15);
        color: #64D2FF;
    }
    .alert-box.warning {
        background: rgba(255, 159, 10, 0.06);
        border: 1px solid rgba(255, 159, 10, 0.15);
        color: #FFD60A;
    }
    .alert-box.danger {
        background: rgba(255, 69, 58, 0.06);
        border: 1px solid rgba(255, 69, 58, 0.15);
        color: var(--danger);
    }
    .alert-box.success-alert {
        background: rgba(48, 209, 88, 0.06);
        border: 1px solid rgba(48, 209, 88, 0.15);
        color: #30D158;
    }
    .alert-icon {
        font-size: 0.95rem;
        line-height: 1;
        flex-shrink: 0;
    }
    .alert-text {
        flex: 1;
    }

    /* ── Form Containers & Inputs ── */
    .form-container {
        display: flex;
        flex-direction: column;
        gap: 0.85rem;
        background: rgba(255, 255, 255, 0.01);
        border: 1px solid rgba(255, 255, 255, 0.04);
        padding: 1.1rem;
        border-radius: 12px;
    }
    .limits-grid {
        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 0.85rem;
        background: rgba(255, 255, 255, 0.01);
        border: 1px solid rgba(255, 255, 255, 0.04);
        padding: 1.1rem;
        border-radius: 12px;
    }
    .pid-grid {
        display: grid;
        grid-template-columns: 1fr 1fr 1fr;
        gap: 0.75rem;
        background: rgba(255, 255, 255, 0.01);
        border: 1px solid rgba(255, 255, 255, 0.04);
        padding: 1.1rem;
        border-radius: 12px;
    }
    .input-group {
        display: flex;
        flex-direction: column;
        gap: 0.35rem;
    }
    .input-group label {
        font-size: 0.72rem;
        color: var(--text-secondary);
        font-weight: 550;
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
        pointer-events: none;
        font-weight: 500;
    }
    .input-hint {
        font-size: 0.62rem;
        color: var(--text-muted);
        margin-top: 1px;
    }
    input[type=number] {
        width: 100%;
        background: rgba(0, 0, 0, 0.28);
        border: 1px solid rgba(255, 255, 255, 0.08);
        color: var(--text-main);
        padding: 0.5rem 0.65rem;
        border-radius: 8px;
        font-size: 0.85rem;
        font-family: var(--font), sans-serif;
        transition: all 0.2s ease;
    }
    input[type=number]:focus {
        outline: none;
        border-color: var(--accent);
        box-shadow: 0 0 0 3px rgba(10, 132, 255, 0.15);
        background: rgba(0, 0, 0, 0.42);
    }
    
    /* ── Toggle Switch (iOS style) ── */
    .toggle-container {
        display: flex;
        justify-content: space-between;
        align-items: center;
    }
    .cal-invert-toggle {
        padding-top: 0.25rem;
        margin-top: 0.1rem;
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
        width: 44px;
        height: 24px;
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
        height: 20px;
        width: 20px;
        left: 2px;
        bottom: 2px;
        background-color: #fff;
        transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
        box-shadow: 0 1px 3px rgba(0, 0, 0, 0.3);
    }
    input:checked + .slider {
        background-color: #30D158;
    }
    input:checked + .slider:before {
        transform: translateX(20px);
    }
    .slider.round {
        border-radius: 24px;
    }
    .slider.round:before {
        border-radius: 50%;
    }

    /* ── Review Table ── */
    .review-table {
        background: rgba(0, 0, 0, 0.2);
        border: 1px solid rgba(255, 255, 255, 0.05);
        border-radius: 12px;
        padding: 0.5rem 1rem;
        display: flex;
        flex-direction: column;
    }
    .review-row {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding: 0.7rem 0;
        border-bottom: 1px solid rgba(255, 255, 255, 0.04);
    }
    .review-row:last-child {
        border-bottom: none;
    }
    .r-lbl {
        font-size: 0.78rem;
        color: var(--text-secondary);
        font-weight: 500;
    }
    .r-val {
        font-size: 0.82rem;
        color: var(--text-main);
        font-weight: 600;
    }
    .highlight-address {
        color: var(--warning);
    }

    /* ── Actions & Buttons ── */
    .actions {
        display: flex;
        gap: 0.65rem;
        margin-top: 0.5rem;
    }
    .actions button {
        flex: 1;
        padding: 0.65rem 1rem;
        font-size: 0.82rem;
    }
    .danger-hover:hover {
        background: rgba(255, 69, 58, 0.08) !important;
        border-color: rgba(255, 69, 58, 0.2) !important;
        color: var(--danger) !important;
    }
    .flash-save-btn {
        flex: 1.5 !important;
        display: flex;
        align-items: center;
        justify-content: center;
        gap: 0.45rem;
    }

    /* ── Spinner ── */
    .spinner-mini {
        width: 12px;
        height: 12px;
        border: 2px solid rgba(255, 255, 255, 0.2);
        border-top-color: #fff;
        border-radius: 50%;
        animation: spin 0.8s linear infinite;
        display: inline-block;
    }
    @keyframes spin {
        to { transform: rotate(360deg); }
    }

    /* ── Success Body ── */
    .success-body {
        align-items: center;
        text-align: center;
        padding: 1.5rem 0;
    }
    .success-icon-wrap {
        margin-bottom: 0.5rem;
    }
    .text-center {
        text-align: center;
    }
    .center-actions {
        justify-content: center;
        width: 100%;
        max-width: 240px;
        margin: 0.75rem auto 0;
    }

    /* ── Checkmark Animation ── */
    .success-checkmark {
        width: 58px;
        height: 58px;
        border-radius: 50%;
        display: block;
        stroke-width: 2.5;
        stroke: var(--success);
        stroke-miterlimit: 10;
        box-shadow: inset 0 0 0 var(--success);
        animation: fillCheckmark .4s ease-in-out .4s forwards, scaleCheckmark .3s ease-in-out .9s both;
        margin: 0 auto;
    }
    .checkmark-circle {
        stroke-dasharray: 166;
        stroke-dashoffset: 166;
        stroke-width: 2.5;
        stroke-miterlimit: 10;
        stroke: var(--success);
        fill: none;
        animation: strokeCheckmark .6s cubic-bezier(0.65, 0, 0.45, 1) forwards;
    }
    .checkmark-check {
        transform-origin: 50% 50%;
        stroke-dasharray: 48;
        stroke-dashoffset: 48;
        stroke: var(--success);
        animation: strokeCheckmark .3s cubic-bezier(0.65, 0, 0.45, 1) .8s forwards;
    }

    @keyframes strokeCheckmark {
        100% { stroke-dashoffset: 0; }
    }
    @keyframes fillCheckmark {
        100% { box-shadow: inset 0 0 0 30px rgba(48, 209, 88, 0.05); }
    }
    @keyframes scaleCheckmark {
        0%, 100% { transform: none; }
        50% { transform: scale3d(1.1, 1.1, 1); }
    }
</style>
