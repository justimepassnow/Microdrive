<!-- src/components/ConnectionBar.svelte -->
<script>
    let { isConnected = false, isConnecting = false, onToggle } = $props();
</script>

<header class="glass-panel connection-header">
    <div class="brand">
        <div class="logo-orb" class:connected={isConnected}></div>
        <div class="brand-text">
            <h1>Servo Control</h1>
            <span class="sub-brand">Desktop Console</span>
        </div>
    </div>
    
    <div class="connection-group">
        <span class="baud-badge">250,000 Baud</span>
        {#if isConnected}
            <span class="status-badge connected">Connected</span>
            <button class="btn danger" onclick={onToggle} disabled={isConnecting}>
                Disconnect
            </button>
        {:else}
            <span class="status-badge disconnected">Disconnected</span>
            <button class="btn primary" onclick={onToggle} disabled={isConnecting}>
                {isConnecting ? 'Opening Port...' : 'Connect USB'}
            </button>
        {/if}
    </div>
</header>

<style>
    .connection-header {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding: 1rem 2rem;
        border-radius: 16px;
    }
    .brand-text {
        display: flex;
        flex-direction: column;
    }
    .sub-brand {
        font-size: 0.75rem;
        color: var(--text-muted);
        text-transform: uppercase;
        letter-spacing: 2px;
        margin-top: -2px;
    }
    .logo-orb {
        transition: all 0.5s ease;
    }
    .logo-orb.connected {
        background: var(--success);
        box-shadow: 0 0 15px var(--success);
    }
    .baud-badge {
        font-size: 0.8rem;
        color: var(--text-muted);
        background: rgba(255, 255, 255, 0.04);
        padding: 0.3rem 0.8rem;
        border-radius: 6px;
        border: 1px solid rgba(255, 255, 255, 0.05);
        font-weight: 500;
    }
</style>
