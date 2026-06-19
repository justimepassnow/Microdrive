<!-- src/components/ConsoleTerminal.svelte -->
<script>
    import { tick } from 'svelte';

    let { logs = [], onClear } = $props();
    let containerEl = $state(null);

    // Scroll to bottom when logs update
    $effect(() => {
        if (logs.length && containerEl) {
            tick().then(() => {
                containerEl.scrollTop = containerEl.scrollHeight;
            });
        }
    });
</script>

<section class="console">
    <header class="console-toolbar">
        <div class="console-title">
            <svg class="console-icon" viewBox="0 0 16 16" fill="none">
                <path d="M4 4.5L7.5 8L4 11.5" stroke="currentColor" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/>
                <path d="M8.5 11.5H12" stroke="currentColor" stroke-width="1.5" stroke-linecap="round"/>
            </svg>
            <span>Console</span>
        </div>
        <button class="clear-btn" onclick={onClear}>
            <svg class="clear-icon" viewBox="0 0 16 16" fill="none">
                <path d="M2 4h12M5.333 4V2.667a1.333 1.333 0 011.334-1.334h2.666a1.333 1.333 0 011.334 1.334V4m2 0v9.333a1.333 1.333 0 01-1.334 1.334H4.667a1.333 1.333 0 01-1.334-1.334V4h9.334z" stroke="currentColor" stroke-width="1.2" stroke-linecap="round" stroke-linejoin="round"/>
            </svg>
            Clear
        </button>
    </header>

    <div class="console-scroll" bind:this={containerEl}>
        {#if logs.length === 0}
            <div class="console-empty">
                <span class="empty-caret">▸</span>
                Console idle — awaiting transactions…
            </div>
        {:else}
            {#each logs as log}
                <div class="log-entry log-{log.type}">
                    <span class="log-time">{log.time}</span>
                    <span class="log-tag">[{log.type.toUpperCase()}]</span>
                    <span class="log-msg">{log.text}</span>
                </div>
            {/each}
        {/if}
    </div>
</section>

<style>
    /* ---- Container ---- */
    .console {
        display: flex;
        flex-direction: column;
        grid-column: 1 / -1;
        background: rgba(0, 0, 0, 0.30);
        border: 1px solid var(--panel-border);
        border-radius: 12px;
        overflow: hidden;
        backdrop-filter: blur(20px);
        -webkit-backdrop-filter: blur(20px);
    }

    /* ---- Toolbar ---- */
    .console-toolbar {
        display: flex;
        align-items: center;
        justify-content: space-between;
        padding: 8px 14px;
        background: rgba(255, 255, 255, 0.025);
        border-bottom: 1px solid rgba(255, 255, 255, 0.05);
    }

    .console-title {
        display: flex;
        align-items: center;
        gap: 6px;
        font-family: var(--font);
        font-size: 0.775rem;
        font-weight: 600;
        color: var(--text-muted);
        letter-spacing: 0.02em;
        text-transform: uppercase;
    }

    .console-icon {
        width: 14px;
        height: 14px;
        color: var(--text-muted);
        opacity: 0.7;
    }

    /* ---- Clear Button ---- */
    .clear-btn {
        display: inline-flex;
        align-items: center;
        gap: 4px;
        background: none;
        border: none;
        color: var(--text-muted);
        font-family: var(--font);
        font-size: 0.7rem;
        font-weight: 500;
        letter-spacing: 0.01em;
        padding: 4px 8px;
        border-radius: 6px;
        cursor: pointer;
        transition: color 0.2s ease, background 0.2s ease;
    }

    .clear-btn:hover {
        color: var(--text-main);
        background: rgba(255, 255, 255, 0.06);
    }

    .clear-btn:active {
        background: rgba(255, 255, 255, 0.03);
    }

    .clear-icon {
        width: 12px;
        height: 12px;
    }

    /* ---- Scrollable Log Area ---- */
    .console-scroll {
        max-height: 200px;
        overflow-y: auto;
        scroll-behavior: smooth;
        padding: 8px 14px 10px;
        display: flex;
        flex-direction: column;
        gap: 1px;
    }

    .console-scroll::-webkit-scrollbar {
        width: 5px;
    }

    .console-scroll::-webkit-scrollbar-track {
        background: transparent;
    }

    .console-scroll::-webkit-scrollbar-thumb {
        background: rgba(255, 255, 255, 0.08);
        border-radius: 4px;
    }

    .console-scroll::-webkit-scrollbar-thumb:hover {
        background: rgba(255, 255, 255, 0.14);
    }

    /* ---- Empty State ---- */
    .console-empty {
        display: flex;
        align-items: center;
        gap: 6px;
        padding: 18px 0;
        font-family: 'JetBrains Mono', 'SF Mono', 'Fira Code', 'Cascadia Code', monospace;
        font-size: 0.75rem;
        color: var(--text-muted);
        opacity: 0.5;
    }

    .empty-caret {
        color: var(--text-muted);
        opacity: 0.6;
        animation: blink-caret 1.2s steps(2) infinite;
    }

    @keyframes blink-caret {
        0%, 100% { opacity: 0.6; }
        50% { opacity: 0; }
    }

    /* ---- Log Entries ---- */
    .log-entry {
        display: flex;
        align-items: baseline;
        gap: 0;
        font-family: 'JetBrains Mono', 'SF Mono', 'Fira Code', 'Cascadia Code', monospace;
        font-size: 0.72rem;
        line-height: 1.55;
        padding: 1.5px 0;
        border-radius: 3px;
        word-break: break-all;
    }

    .log-time {
        flex-shrink: 0;
        color: rgba(255, 255, 255, 0.18);
        margin-right: 10px;
        font-size: 0.68rem;
        font-variant-numeric: tabular-nums;
    }

    .log-tag {
        flex-shrink: 0;
        margin-right: 8px;
        font-size: 0.66rem;
        letter-spacing: 0.03em;
    }

    .log-msg {
        flex: 1;
        min-width: 0;
    }

    /* ---- Log Type Colors ---- */
    .log-tx           { color: #5E9EFF; }
    .log-tx .log-tag  { color: rgba(94, 158, 255, 0.55); }

    .log-rx           { color: var(--accent); }
    .log-rx .log-tag  { color: rgba(0, 240, 255, 0.45); }

    .log-raw           { color: #FFD60A; }
    .log-raw .log-tag  { color: rgba(255, 214, 10, 0.45); }

    .log-sys           { color: var(--text-muted); }
    .log-sys .log-tag  { color: rgba(100, 116, 139, 0.5); }

    .log-error           { color: #FF453A; }
    .log-error .log-tag  { color: rgba(255, 69, 58, 0.50); }
</style>
