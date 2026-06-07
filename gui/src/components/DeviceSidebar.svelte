<!-- src/components/DeviceSidebar.svelte -->
<script>
    let { 
        isConnected = false, 
        isScanning = false, 
        servos = [], 
        activeId = null, 
        onScan, 
        onSelect 
    } = $props();
</script>

<aside class="glass-panel sidebar">
    <div class="sidebar-header">
        <h2>Bus Devices</h2>
        <span class="count-badge">{servos.length} Online</span>
    </div>
    
    <div class="device-controls">
        <button 
            class="btn secondary full-width-btn" 
            disabled={!isConnected || isScanning}
            onclick={onScan}
        >
            {isScanning ? 'Scanning (0-127)...' : 'Scan Servo Bus'}
        </button>
    </div>
    
    <ul class="device-list">
        {#if isScanning}
            <li class="empty-state pulse">Scanning serial bus...</li>
        {:else if !isConnected}
            <li class="empty-state">Connect USB to scan</li>
        {:else if servos.length === 0}
            <li class="empty-state">No servos found. Scan to discover.</li>
        {:else}
            {#each servos as id}
                <!-- svelte-ignore a11y_click_events_have_key_events -->
                <!-- svelte-ignore a11y_no_noninteractive_element_interactions -->
                <li 
                    class="device-item" 
                    class:active={activeId === id}
                    onclick={() => onSelect(id)}
                >
                    <div class="device-info">
                        <div class="device-status-dot"></div>
                        <span class="device-name">Servo Node</span>
                    </div>
                    <span class="device-id">ID {id}</span>
                </li>
            {/each}
        {/if}
    </ul>
</aside>

<style>
    .sidebar {
        height: 100%;
        display: flex;
        flex-direction: column;
        gap: 1rem;
    }
    .sidebar-header {
        display: flex;
        justify-content: space-between;
        align-items: center;
        margin-bottom: 0.5rem;
    }
    .sidebar-header h2 {
        margin-bottom: 0;
    }
    .count-badge {
        font-size: 0.75rem;
        color: var(--accent);
        background: rgba(0, 240, 255, 0.08);
        padding: 0.2rem 0.6rem;
        border-radius: 10px;
        border: 1px solid rgba(0, 240, 255, 0.15);
        font-weight: 600;
    }
    .full-width-btn {
        width: 100%;
    }
    .device-list {
        display: flex;
        flex-direction: column;
        gap: 0.5rem;
        overflow-y: auto;
        flex: 1;
        list-style: none;
    }
    .device-item {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding: 0.8rem 1rem;
        background: rgba(0,0,0,0.2);
        border-radius: 10px;
        cursor: pointer;
        border: 1px solid rgba(255,255,255,0.03);
        transition: all 0.2s ease;
    }
    .device-item:hover {
        background: rgba(255,255,255,0.04);
        border-color: rgba(255,255,255,0.08);
        transform: translateX(2px);
    }
    .device-item.active {
        border-color: var(--accent);
        background: rgba(0, 240, 255, 0.06);
        box-shadow: 0 0 15px rgba(0, 240, 255, 0.03);
    }
    .device-info {
        display: flex;
        align-items: center;
        gap: 0.6rem;
    }
    .device-status-dot {
        width: 6px;
        height: 6px;
        border-radius: 50%;
        background: var(--accent);
        box-shadow: 0 0 8px var(--accent);
    }
    .device-name {
        font-size: 0.9rem;
        font-weight: 500;
    }
    .device-id {
        font-size: 0.8rem;
        color: var(--text-muted);
        font-weight: 600;
    }
    .pulse {
        animation: pulse-txt 1.5s infinite;
    }
    @keyframes pulse-txt {
        0% { opacity: 0.6; }
        50% { opacity: 1; }
        100% { opacity: 0.6; }
    }
</style>
