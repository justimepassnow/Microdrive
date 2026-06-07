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

<div class="glass-panel console-panel">
    <div class="console-header">
        <h3>Diagnostic Console</h3>
        <button class="btn small secondary" onclick={onClear}>Clear Logs</button>
    </div>
    
    <div class="console-body" bind:this={containerEl}>
        {#if logs.length === 0}
            <div class="empty-state">Console idle. Awaiting transactions...</div>
        {:else}
            {#each logs as log}
                <div class="log-line {log.type}">
                    <span class="time">{log.time}</span>
                    <span class="prefix">[{log.type.toUpperCase()}]</span>
                    <span class="text">{log.text}</span>
                </div>
            {/each}
        {/if}
    </div>
</div>

<style>
    .console-panel {
        display: flex;
        flex-direction: column;
        gap: 0.8rem;
        height: 250px;
        grid-column: 1 / -1; /* spans full layout width */
    }
    .console-header {
        display: flex;
        justify-content: space-between;
        align-items: center;
    }
    .console-header h3 {
        margin-bottom: 0;
    }
    .console-body {
        flex: 1;
        background: rgba(0, 0, 0, 0.45);
        border: 1px solid rgba(255, 255, 255, 0.05);
        border-radius: 8px;
        padding: 0.8rem 1rem;
        font-family: 'Courier New', Courier, monospace;
        font-size: 0.85rem;
        overflow-y: auto;
        display: flex;
        flex-direction: column;
        gap: 0.3rem;
    }
    .log-line {
        line-height: 1.4;
        word-break: break-all;
    }
    .time {
        color: var(--text-muted);
        margin-right: 0.5rem;
    }
    .prefix {
        font-weight: bold;
        margin-right: 0.5rem;
    }
    
    /* Type styles */
    .log-line.tx { color: #A5B4FC; }          /* Outgoing JSON blue-purple */
    .log-line.rx { color: var(--accent); }     /* Incoming JSON cyan */
    .log-line.raw { color: #FCD34D; }         /* MicroPython print logs yellow */
    .log-line.sys { color: var(--text-muted); } /* Internal logs gray */
    .log-line.error { color: var(--danger); }  /* Errors red */
</style>
