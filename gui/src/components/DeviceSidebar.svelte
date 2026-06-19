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
        <h2 class="sidebar-title">Devices</h2>
        <span class="count-badge">
            <span class="count-dot"></span>
            {servos.length}
        </span>
    </div>
    
    <div class="device-controls">
        <button 
            class="btn secondary scan-btn" 
            disabled={!isConnected || isScanning}
            onclick={onScan}
        >
            {#if isScanning}
                <span class="scan-spinner"></span>
                Scanning…
            {:else}
                <svg class="scan-icon" width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                    <circle cx="11" cy="11" r="8"/>
                    <line x1="21" y1="21" x2="16.65" y2="16.65"/>
                </svg>
                Scan Bus
            {/if}
        </button>
    </div>
    
    <ul class="device-list">
        {#if isScanning}
            <li class="empty-state">
                <span class="empty-icon pulse">📡</span>
                <span class="empty-text">Scanning serial bus…</span>
                <span class="empty-sub">Addresses 0–127</span>
            </li>
        {:else if !isConnected}
            <li class="empty-state">
                <span class="empty-icon">🔌</span>
                <span class="empty-text">No Connection</span>
                <span class="empty-sub">Connect USB to scan for servos</span>
            </li>
        {:else if servos.length === 0}
            <li class="empty-state">
                <span class="empty-icon">🔍</span>
                <span class="empty-text">No Devices</span>
                <span class="empty-sub">Scan to discover servos on the bus</span>
            </li>
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
    /* ── Sidebar Container ── */
    .sidebar {
        height: 100%;
        display: flex;
        flex-direction: column;
        gap: 0;
        padding: 1.25rem;
    }

    /* ── Header ── */
    .sidebar-header {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding-bottom: 1rem;
        margin-bottom: 0.75rem;
        border-bottom: 1px solid var(--panel-border);
    }
    .sidebar-title {
        margin-bottom: 0;
        font-size: 0.8rem;
        font-weight: 700;
        text-transform: uppercase;
        letter-spacing: 1.2px;
        color: var(--text-muted);
    }

    /* ── Count Badge (minimal) ── */
    .count-badge {
        display: flex;
        align-items: center;
        gap: 0.35rem;
        font-size: 0.75rem;
        font-weight: 600;
        color: var(--text-muted);
        font-variant-numeric: tabular-nums;
    }
    .count-dot {
        width: 6px;
        height: 6px;
        border-radius: 50%;
        background: var(--success);
        flex-shrink: 0;
    }

    /* ── Scan Button (pill) ── */
    .device-controls {
        margin-bottom: 0.75rem;
    }
    .scan-btn {
        width: 100%;
        display: flex;
        align-items: center;
        justify-content: center;
        gap: 0.5rem;
        border-radius: 20px;
        padding: 0.6rem 1rem;
        font-size: 0.8rem;
        font-weight: 600;
        letter-spacing: 0.3px;
        text-transform: none;
    }
    .scan-icon {
        opacity: 0.7;
        flex-shrink: 0;
    }

    /* Scanning spinner */
    .scan-spinner {
        width: 14px;
        height: 14px;
        border: 2px solid rgba(255, 255, 255, 0.15);
        border-top-color: var(--text-main);
        border-radius: 50%;
        animation: spin 0.8s linear infinite;
        flex-shrink: 0;
    }
    @keyframes spin {
        to { transform: rotate(360deg); }
    }

    /* ── Device List ── */
    .device-list {
        display: flex;
        flex-direction: column;
        gap: 2px;
        overflow-y: auto;
        flex: 1;
        list-style: none;
        padding: 0;
        margin: 0;
    }

    /* ── Device Item (macOS sidebar row) ── */
    .device-item {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding: 0.55rem 0.75rem;
        background: transparent;
        border-radius: 8px;
        cursor: pointer;
        border: none;
        transition: background-color 0.15s ease;
        user-select: none;
    }
    .device-item:hover {
        background: rgba(255, 255, 255, 0.05);
    }
    .device-item.active {
        background: color-mix(in srgb, var(--accent) 12%, transparent);
    }
    .device-item.active .device-name {
        color: var(--accent);
    }
    .device-item.active .device-id {
        color: color-mix(in srgb, var(--accent) 60%, var(--text-muted));
    }
    .device-item.active .device-status-dot {
        background: var(--accent);
        box-shadow: 0 0 6px color-mix(in srgb, var(--accent) 50%, transparent);
    }

    /* ── Device Row Content ── */
    .device-info {
        display: flex;
        align-items: center;
        gap: 0.6rem;
        min-width: 0;
    }
    .device-status-dot {
        width: 6px;
        height: 6px;
        border-radius: 50%;
        background: var(--success);
        flex-shrink: 0;
    }
    .device-name {
        font-size: 0.85rem;
        font-weight: 500;
        color: var(--text-main);
        white-space: nowrap;
        overflow: hidden;
        text-overflow: ellipsis;
    }
    .device-id {
        font-size: 0.72rem;
        color: var(--text-muted);
        font-weight: 600;
        font-variant-numeric: tabular-nums;
        letter-spacing: 0.3px;
        flex-shrink: 0;
        margin-left: 0.5rem;
    }

    /* ── Empty States ── */
    .empty-state {
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        text-align: center;
        padding: 2.5rem 1rem;
        gap: 0.4rem;
        flex: 1;
    }
    .empty-icon {
        font-size: 1.75rem;
        line-height: 1;
        margin-bottom: 0.25rem;
        opacity: 0.8;
    }
    .empty-text {
        font-size: 0.85rem;
        font-weight: 600;
        color: var(--text-main);
        opacity: 0.7;
    }
    .empty-sub {
        font-size: 0.75rem;
        color: var(--text-muted);
        max-width: 180px;
        line-height: 1.4;
    }

    /* ── Pulse animation ── */
    .pulse {
        animation: pulse-txt 1.8s ease-in-out infinite;
    }
    @keyframes pulse-txt {
        0% { opacity: 0.5; }
        50% { opacity: 1; }
        100% { opacity: 0.5; }
    }
</style>
