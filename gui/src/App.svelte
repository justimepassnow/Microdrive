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

    // Reactive Application State (Svelte 5 Runes)
    let isConnected = $state(false);
    let isConnecting = $state(false);
    let isScanning = $state(false);
    
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
            <div class="header-row">
                <h2>
                    Live Telemetry 
                    {#if activeServoId !== null}
                        <span class="accent-text">ID {activeServoId}</span>
                    {:else}
                        <span class="text-muted">(--)</span>
                    {/if}
                </h2>
                {#if activeServoId !== null && isConnected}
                    <div class="live-indicator">
                        <div class="dot" class:active={flashLiveDot}></div> 
                        Poll Rate: 10Hz
                    </div>
                {/if}
            </div>

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
        padding: 0.2rem 0.5rem;
        font-size: 0.75rem;
        border-radius: 4px;
        width: 100%;
    }
    .state-val.yielding {
        color: var(--warning);
        animation: textGlowPulseWarning 1.5s infinite;
    }
    @keyframes textGlowPulseWarning {
        0% { filter: drop-shadow(0 0 1px var(--warning-glow)); opacity: 1; }
        50% { filter: drop-shadow(0 0 6px var(--warning-glow)); opacity: 0.85; }
        100% { filter: drop-shadow(0 0 1px var(--warning-glow)); opacity: 1; }
    }
</style>
