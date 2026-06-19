<!-- src/components/ConnectionBar.svelte -->
<script>
    let { isConnected = false, isConnecting = false, onToggle } = $props();
</script>

<header class="glass-panel toolbar">
    <div class="toolbar-left">
        <div class="brand-mark">
            <!-- Minimal servo/motor icon -->
            <svg class="brand-icon" width="28" height="28" viewBox="0 0 28 28" fill="none" xmlns="http://www.w3.org/2000/svg">
                <circle cx="14" cy="14" r="10" stroke="currentColor" stroke-width="1.5" opacity="0.35"/>
                <circle cx="14" cy="14" r="5.5" stroke="currentColor" stroke-width="1.5" opacity="0.6"/>
                <circle cx="14" cy="14" r="2" fill="currentColor" opacity="0.9"/>
                <!-- Shaft tick marks -->
                <line x1="14" y1="2" x2="14" y2="5" stroke="currentColor" stroke-width="1.2" stroke-linecap="round" opacity="0.3"/>
                <line x1="14" y1="23" x2="14" y2="26" stroke="currentColor" stroke-width="1.2" stroke-linecap="round" opacity="0.3"/>
                <line x1="2" y1="14" x2="5" y2="14" stroke="currentColor" stroke-width="1.2" stroke-linecap="round" opacity="0.3"/>
                <line x1="23" y1="14" x2="26" y2="14" stroke="currentColor" stroke-width="1.2" stroke-linecap="round" opacity="0.3"/>
            </svg>
            {#if isConnected}
                <span class="status-dot active"></span>
            {:else}
                <span class="status-dot"></span>
            {/if}
        </div>

        <div class="brand-text">
            <h1 class="brand-name">μDrive</h1>
            <span class="brand-sub">Servo Controller</span>
        </div>
    </div>

    <div class="toolbar-right">
        <span class="baud-label">250,000 baud</span>

        <div class="divider"></div>

        {#if isConnected}
            <span class="conn-status connected">
                <span class="conn-dot"></span>
                Connected
            </span>
            <button class="pill-btn disconnect" onclick={onToggle} disabled={isConnecting}>
                Disconnect
            </button>
        {:else}
            <span class="conn-status disconnected">
                <span class="conn-dot"></span>
                Disconnected
            </span>
            <button class="pill-btn connect" onclick={onToggle} disabled={isConnecting}>
                {isConnecting ? 'Opening…' : 'Connect'}
            </button>
        {/if}
    </div>
</header>

<style>
    /* ── Toolbar shell ─────────────────────────────── */
    .toolbar {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding: 0.65rem 1.25rem;
        border-radius: 14px;
        min-height: 52px;
    }

    /* ── Left: brand ───────────────────────────────── */
    .toolbar-left {
        display: flex;
        align-items: center;
        gap: 0.7rem;
    }

    .brand-mark {
        position: relative;
        display: flex;
        align-items: center;
        justify-content: center;
        color: var(--text-muted);
    }

    .brand-icon {
        display: block;
        transition: color 0.3s ease;
    }

    /* Subtle green status dot overlaid bottom-right of icon */
    .status-dot {
        position: absolute;
        bottom: 0;
        right: -1px;
        width: 7px;
        height: 7px;
        border-radius: 50%;
        background: var(--text-muted);
        border: 1.5px solid var(--bg, #07090e);
        transition: background 0.4s ease;
    }
    .status-dot.active {
        background: var(--success);
    }

    .brand-text {
        display: flex;
        flex-direction: column;
        gap: 0;
    }

    .brand-name {
        font-family: var(--font);
        font-size: 1.1rem;
        font-weight: 700;
        letter-spacing: 0.3px;
        line-height: 1.15;
        color: var(--text-main);
        /* Override global h1 gradient — we want a solid white here */
        background: none;
        -webkit-background-clip: unset;
        -webkit-text-fill-color: var(--text-main);
    }

    .brand-sub {
        font-family: var(--font);
        font-size: 0.65rem;
        font-weight: 500;
        color: var(--text-muted);
        letter-spacing: 0.6px;
        text-transform: uppercase;
        line-height: 1.2;
    }

    /* ── Right: controls ───────────────────────────── */
    .toolbar-right {
        display: flex;
        align-items: center;
        gap: 0.85rem;
    }

    .baud-label {
        font-family: var(--font);
        font-size: 0.72rem;
        font-weight: 500;
        color: var(--text-muted);
        letter-spacing: 0.3px;
        opacity: 0.7;
        white-space: nowrap;
    }

    .divider {
        width: 1px;
        height: 18px;
        background: rgba(255, 255, 255, 0.08);
        flex-shrink: 0;
    }

    /* ── Connection status inline label ────────────── */
    .conn-status {
        display: flex;
        align-items: center;
        gap: 0.4rem;
        font-family: var(--font);
        font-size: 0.78rem;
        font-weight: 500;
        letter-spacing: 0.2px;
        white-space: nowrap;
    }
    .conn-status.connected {
        color: var(--success);
    }
    .conn-status.disconnected {
        color: var(--text-muted);
    }

    .conn-dot {
        width: 6px;
        height: 6px;
        border-radius: 50%;
        flex-shrink: 0;
    }
    .conn-status.connected .conn-dot {
        background: var(--success);
    }
    .conn-status.disconnected .conn-dot {
        background: var(--text-muted);
        opacity: 0.5;
    }

    /* ── Pill buttons ──────────────────────────────── */
    .pill-btn {
        font-family: var(--font);
        font-size: 0.78rem;
        font-weight: 600;
        padding: 0.4rem 1.1rem;
        border-radius: 980px; /* full pill */
        border: 1px solid transparent;
        cursor: pointer;
        white-space: nowrap;
        transition:
            background 0.25s ease,
            color 0.25s ease,
            border-color 0.25s ease,
            transform 0.15s ease,
            opacity 0.25s ease;
    }
    .pill-btn:disabled {
        opacity: 0.35;
        cursor: not-allowed;
        transform: none !important;
    }

    /* Connect (primary) */
    .pill-btn.connect {
        background: var(--accent);
        color: #04060a;
        border-color: transparent;
    }
    .pill-btn.connect:not(:disabled):hover {
        filter: brightness(1.1);
        transform: translateY(-0.5px);
    }
    .pill-btn.connect:not(:disabled):active {
        filter: brightness(0.95);
        transform: translateY(0);
    }

    /* Disconnect (danger ghost) */
    .pill-btn.disconnect {
        background: rgba(255, 42, 95, 0.08);
        color: var(--magenta);
        border-color: rgba(255, 42, 95, 0.2);
    }
    .pill-btn.disconnect:not(:disabled):hover {
        background: rgba(255, 42, 95, 0.15);
        border-color: rgba(255, 42, 95, 0.35);
        transform: translateY(-0.5px);
    }
    .pill-btn.disconnect:not(:disabled):active {
        background: rgba(255, 42, 95, 0.22);
        transform: translateY(0);
    }
</style>
