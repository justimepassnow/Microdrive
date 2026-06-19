<!-- src/App.svelte -->
<script>
    import { onDestroy } from 'svelte';
    import { SerialTransport } from './lib/transport.js';
    import ConnectionBar from './components/ConnectionBar.svelte';
    import DeviceSidebar from './components/DeviceSidebar.svelte';
    import ControlDial from './components/ControlDial.svelte';
    import ConfigPanel from './components/ConfigPanel.svelte';
    import TelemetryChart from './components/TelemetryChart.svelte';
    import ConsoleTerminal from './components/ConsoleTerminal.svelte';
    import CalibrationWizard from './components/CalibrationWizard.svelte';
    import StepTestPanel from './components/StepTestPanel.svelte';

    // Reactive Application State (Svelte 5 Runes)
    let isConnected = $state(false);
    let isConnecting = $state(false);
    let isScanning = $state(false);
    let activeTab = $state('telemetry');
    
    let servos = $state([]);
    let activeServoId = $state(null);
    let config = $state(null);
    let telemetry = $state({
        angle: 0,
        current_ma: 0,
        is_moving: false,
        is_holding: false,
        overcurrent: false,
        stall: false
    });
    
    let targetAngle = $state(90);
    let targetVelocity = $state(0);
    let targetCurrent = $state(0);
    let logs = $state([]);
    let isArmed = $state(false);
    
    let transport = null;
    let pollInterval = null;
    let flashLiveDot = $state(false);

    // Logging utility with millisecond timestamps
    function addLog(type, text) {
        const now = new Date();
        const hrs = String(now.getHours()).padStart(2, '0');
        const mins = String(now.getMinutes()).padStart(2, '0');
        const secs = String(now.getSeconds()).padStart(2, '0');
        const ms = String(now.getMilliseconds()).padStart(3, '0');
        const timeStr = `${hrs}:${mins}:${secs}.${ms}`;
        
        logs = [...logs, { time: timeStr, type, text }];
        
        // Cap local logs history at 200 items
        if (logs.length > 200) {
            logs = logs.slice(logs.length - 200);
        }
    }

    // Toggle Web Serial connection
    async function toggleConnection() {
        if (!transport) {
            isConnecting = true;
            addLog('sys', 'Initializing Web Serial communication...');
            try {
                transport = new SerialTransport(
                    (msg) => handleMessage(msg),
                    () => handleDisconnect(),
                    (txt) => {
                        let logType = 'sys';
                        if (txt.startsWith('[BOARD-RAW]')) {
                            logType = 'raw';
                            txt = txt.replace('[BOARD-RAW]', '').trim();
                        } else if (txt.includes('error') || txt.includes('failed')) {
                            logType = 'error';
                        }
                        addLog(logType, txt);
                    }
                );
                await transport.connect();
                isConnected = true;
                addLog('sys', 'Connection established at 250000 baud.');
            } catch (err) {
                addLog('error', `Connection failed: ${err.message}`);
                alert(`Serial Error: ${err.message}`);
                transport = null;
                isConnected = false;
            } finally {
                isConnecting = false;
            }
        } else {
            await disconnectTransport();
        }
    }

    async function disconnectTransport() {
        stopPolling();
        if (transport) {
            try {
                await transport.disconnect();
            } catch (e) {
                // Ignore disconnect errors
            }
            transport = null;
        }
        handleDisconnect();
    }

    // Handle physical disconnect or error closures
    function handleDisconnect() {
        isConnected = false;
        isScanning = false;
        activeServoId = null;
        config = null;
        servos = [];
        telemetry = { angle: 0, current_ma: 0, is_moving: false, overcurrent: false, stall: false };
        stopPolling();
        addLog('sys', 'Dashboard status reset (Disconnected).');
    }

    // Receive JSON packets from the MicroPython proxy
    function handleMessage(msg) {
        // Log transaction
        if (msg.res === 'error') {
            addLog('error', `Error response: ${msg.msg}`);
            return;
        }

        // Print incoming packets to Console
        addLog('rx', JSON.stringify(msg));

        if (msg.res === 'scan') {
            servos = msg.data;
            isScanning = false;
            addLog('sys', `Discovery completed. Found ${servos.length} online servo node(s).`);
        } else if (msg.res === 'poll') {
            telemetry = msg.data;
            // Pulse live status dot
            flashLiveDot = true;
            setTimeout(() => flashLiveDot = false, 60);
        } else if (msg.res === 'read_config') {
            config = msg.data;
            // Sync slider limits with safe angle bounds
            if (config.min_angle !== undefined) {
                targetAngle = Math.max(config.min_angle, Math.min(targetAngle, config.max_angle));
            }
            addLog('sys', `Servo config downloaded successfully.`);
        } else if (msg.res === 'ack') {
            addLog('sys', `Ack received for: ${msg.cmd}`);
            if (msg.cmd === 'configure' && msg.new_id !== undefined && msg.new_id !== msg.id) {
                const oldId = msg.id;
                const newId = msg.new_id;
                addLog('sys', `Servo ID successfully migrated from ID ${oldId} to ID ${newId}. Updating session...`);
                
                // Update sidebar list, active servo selection, cached configuration, and restart polling
                servos = servos.map(id => id === oldId ? newId : id);
                activeServoId = newId;
                startPolling();
                if (config) {
                    config.servo_id = newId;
                }
            }
        }
    }

    // Send command helper
    function sendCommand(data) {
        if (!transport || !isConnected) return;
        try {
            transport.send(data);
            addLog('tx', JSON.stringify(data));
        } catch (e) {
            addLog('error', `Failed to transmit packet: ${e.message}`);
        }
    }

    // Trigger Scan
    function scanBus() {
        if (!isConnected) return;
        servos = [];
        isScanning = true;
        addLog('sys', 'Broadcasting discovery ping (IDs 0-253) at 250000 baud...');
        sendCommand({ cmd: 'scan' });
    }

    // Select active servo node
    function selectServo(id) {
        if (!isConnected) return;
        stopPolling();
        activeServoId = id;
        config = null;
        telemetry = { angle: 0, current_ma: 0, is_moving: false, is_holding: false, overcurrent: false, stall: false };
        isArmed = true;
        targetCurrent = 0;
        
        addLog('sys', `Activating Servo Node ID ${id}...`);
        sendCommand({ cmd: 'read_config', id });
        
        if (id === 0) {
            activeTab = 'calibration';
            addLog('sys', `Servo Node ID 0 (factory default) selected. Redirecting to Configuration Wizard.`);
        }
        
        // Start live telemetry polling at 10Hz
        startPolling();
    }

    // 10Hz telemetric loops
    function startPolling() {
        stopPolling();
        pollInterval = setInterval(() => {
            if (activeServoId !== null && isConnected) {
                sendCommand({ cmd: 'poll', id: activeServoId });
            }
        }, 100);
    }

    function stopPolling() {
        if (pollInterval) {
            clearInterval(pollInterval);
            pollInterval = null;
        }
    }

    // Movement command dispatcher
    function sendMove(angle, velocity, current) {
        if (activeServoId === null || !isConnected) return;
        isArmed = true;
        sendCommand({
            cmd: 'move',
            id: activeServoId,
            angle: parseInt(angle, 10),
            velocity: parseInt(velocity, 10),
            current: parseInt(current || 0, 10)
        });
    }

    // Write parameters to Flash
    function writeConfig(params) {
        if (activeServoId === null || !isConnected) return;
        if (params.ram_only) {
            addLog('sys', `Applying RAM-only configuration to ID ${activeServoId}...`);
        } else {
            addLog('sys', `Uploading new configuration to flash for ID ${activeServoId}...`);
        }
        sendCommand({
            cmd: 'configure',
            id: activeServoId,
            params
        });
    }

    // Clear hardware faults
    function clearFault() {
        if (activeServoId === null || !isConnected) return;
        isArmed = false;
        addLog('sys', `Sending PID reset and error clear command to ID ${activeServoId}...`);
        sendCommand({ cmd: 'clear_error', id: activeServoId });
    }

    function disarmMotor() {
        if (activeServoId === null || !isConnected) return;
        isArmed = false;
        addLog('sys', `Disarming Motor ID ${activeServoId} (allowing free rotation)...`);
        sendCommand({ cmd: 'clear_error', id: activeServoId });
    }

    function clearConsoleLogs() {
        logs = [];
        addLog('sys', 'Console log cleared.');
    }

    // Cleanup timers
    onDestroy(() => {
        stopPolling();
    });
</script>

<div class="app-container">
    <!-- Header Connection Bar -->
    <ConnectionBar 
        {isConnected} 
        {isConnecting} 
        onToggle={toggleConnection} 
    />

    <main class="dashboard">
        <!-- Sidebar Device discovery -->
        <DeviceSidebar 
            {isConnected} 
            {isScanning} 
            {servos} 
            activeId={activeServoId} 
            onScan={scanBus} 
            onSelect={selectServo} 
        />

        <!-- Main Telemetry & Control Panel -->
        <section class="glass-panel main-view">
            <div class="header-row" style="display: flex; justify-content: space-between; align-items: center; margin-bottom: 1.25rem; flex-wrap: wrap; gap: 0.8rem;">
                <div class="tabs-header">
                    <button class="tab-btn" class:active={activeTab === 'telemetry'} onclick={() => activeTab = 'telemetry'}>
                        <svg width="13" height="13" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                            <rect x="3" y="3" width="18" height="18" rx="2" ry="2"></rect>
                            <line x1="9" y1="3" x2="9" y2="21"></line>
                            <line x1="15" y1="3" x2="15" y2="21"></line>
                            <line x1="3" y1="9" x2="21" y2="9"></line>
                            <line x1="3" y1="15" x2="21" y2="15"></line>
                        </svg>
                        Telemetry & Control
                    </button>
                    <button class="tab-btn" class:active={activeTab === 'steptest'} onclick={() => activeTab = 'steptest'} disabled={activeServoId === null || !isConnected}>
                        <svg width="13" height="13" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                            <path d="M3 3v18h18"></path>
                            <path d="M18.7 8l-5.1 5.2-2.8-2.7L7 14.3"></path>
                        </svg>
                        Step Response
                    </button>
                    <button class="tab-btn" class:active={activeTab === 'calibration'} onclick={() => activeTab = 'calibration'} disabled={activeServoId === null || !isConnected}>
                        <svg width="13" height="13" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                            <path d="M14.7 6.3a1 1 0 0 0 0 1.4l1.6 1.6a1 1 0 0 0 1.4 0l3.77-3.77a6 6 0 0 1-7.94 7.94l-6.91 6.91a2.12 2.12 0 0 1-3-3l6.91-6.91a6 6 0 0 1 7.94-7.94l-3.76 3.76z"></path>
                        </svg>
                        Configuration Wizard
                    </button>
                </div>

                {#if activeServoId !== null && isConnected}
                    <div class="live-indicator">
                        <div class="dot" class:active={flashLiveDot}></div> 
                        Poll Rate: 10Hz
                    </div>
                {/if}
            </div>

            {#if activeTab === 'telemetry'}
                <!-- Telemetry Cards -->
                <div class="metrics-grid">
                    <div class="metric-card">
                        <span class="label">Current Angle</span>
                        <div class="value">{isConnected && activeServoId !== null ? telemetry.angle : 0}°</div>
                    </div>
                    
                    <div class="metric-card">
                        <span class="label">Current Draw</span>
                        <div class="value">
                            {isConnected && activeServoId !== null ? telemetry.current_ma : 0} 
                            <small>mA</small>
                        </div>
                    </div>
                    
                    <div class="metric-card">
                        <span class="label">Servo State</span>
                        {#if isConnected && activeServoId !== null}
                            {#if telemetry.is_holding}
                                <div class="value state-val yielding">YIELDING</div>
                            {:else if telemetry.is_moving}
                                <div class="value state-val moving">MOVING</div>
                            {:else}
                                <div class="value state-val">IDLE</div>
                            {/if}
                        {:else}
                            <div class="value state-val">IDLE</div>
                        {/if}
                    </div>
                    
                    <div class="metric-card">
                        <span class="label">Health Status</span>
                        {#if isConnected && activeServoId !== null && (telemetry.overcurrent || telemetry.stall)}
                            <div class="value health-val fault">FAULT</div>
                            <button class="btn small danger clear-fault-btn" onclick={clearFault}>
                                Clear Fault
                            </button>
                        {:else}
                            <div class="value health-val ok">OK</div>
                        {/if}
                    </div>
                </div>

                <!-- Custom Interactive Dial Position Controller & Speedometer -->
                <ControlDial 
                    {isConnected} 
                    actualAngle={telemetry.angle} 
                    bind:targetAngle 
                    bind:targetVelocity 
                    bind:targetCurrent
                    actualCurrent={telemetry.current_ma}
                    currentLimit={config?.current_limit || 500}
                    {isArmed}
                    onMove={sendMove} 
                    onDisarm={disarmMotor}
                />

                <!-- Custom HTML Canvas rolling telemetry plot -->
                {#if activeServoId !== null && isConnected}
                    <TelemetryChart 
                        sample={{ 
                            angle: telemetry.angle, 
                            targetAngle: targetAngle, 
                            current_ma: telemetry.current_ma 
                        }} 
                    />
                {/if}
            {:else if activeTab === 'steptest'}
                <StepTestPanel 
                    {isConnected}
                    activeId={activeServoId}
                    {telemetry}
                    {config}
                    {sendCommand}
                    {addLog}
                    bind:targetVelocity
                    bind:targetCurrent
                />
            {:else if activeTab === 'calibration'}
                <CalibrationWizard 
                    {isConnected}
                    activeId={activeServoId}
                    {telemetry}
                    {config}
                    {sendCommand}
                    onRead={() => sendCommand({ cmd: 'read_config', id: activeServoId })}
                    onClose={() => activeTab = 'telemetry'}
                    {addLog}
                />
            {/if}
        </section>

        <!-- Configuration Settings Panel -->
        <ConfigPanel 
            {isConnected} 
            activeId={activeServoId} 
            {config} 
            onRead={() => sendCommand({ cmd: 'read_config', id: activeServoId })} 
            onWrite={writeConfig} 
        />

    </main>

    <!-- Scrolling diagnostic terminal log -->
    <ConsoleTerminal 
        {logs} 
        onClear={clearConsoleLogs} 
    />
</div>

<style>
    .clear-fault-btn {
        margin-top: 0.4rem;
        padding: 0.3rem 0.8rem;
        font-size: 0.75rem;
        border-radius: var(--radius-pill, 100px);
        width: 100%;
    }
    .state-val.yielding {
        color: var(--warning);
        animation: subtlePulseWarning 2s ease-in-out infinite;
    }
    @keyframes subtlePulseWarning {
        0%, 100% { opacity: 1; }
        50% { opacity: 0.6; }
    }

    /* Tabs & Indicators styling */
    .tabs-header {
        display: flex;
        align-items: center;
        gap: 0.3rem;
        background: rgba(0, 0, 0, 0.22);
        padding: 3.5px;
        border-radius: 10px;
        border: 1px solid rgba(255, 255, 255, 0.05);
    }
    .tab-btn {
        background: transparent;
        border: none;
        color: var(--text-secondary);
        font-family: var(--font);
        font-size: 0.76rem;
        font-weight: 600;
        padding: 0.45rem 0.9rem;
        border-radius: 8px;
        cursor: pointer;
        display: inline-flex;
        align-items: center;
        gap: 0.4rem;
        transition: all 0.2s ease;
    }
    .tab-btn:hover:not(:disabled) {
        color: var(--text-main);
        background: rgba(255, 255, 255, 0.04);
    }
    .tab-btn.active {
        background: var(--accent);
        color: #fff;
        box-shadow: 0 2px 10px rgba(10, 132, 255, 0.25);
    }
    .tab-btn:disabled {
        opacity: 0.35;
        cursor: not-allowed;
    }
    .live-indicator {
        display: flex;
        align-items: center;
        gap: 0.45rem;
        font-size: 0.72rem;
        color: var(--text-muted);
        background: rgba(255, 255, 255, 0.03);
        padding: 0.35rem 0.75rem;
        border-radius: 20px;
        border: 1px solid rgba(255, 255, 255, 0.05);
        user-select: none;
    }
    .dot {
        width: 6px;
        height: 6px;
        border-radius: 50%;
        background: rgba(48, 209, 88, 0.2);
        transition: all 0.08s linear;
    }
    .dot.active {
        background: var(--success);
        box-shadow: 0 0 8px var(--success);
    }
</style>
