<!-- src/components/Dropdown.svelte -->
<script>
    import { onMount, onDestroy } from 'svelte';

    let { 
        value = "", 
        options = [], 
        onChange, 
        disabled = false, 
        placeholder = "Select..." 
    } = $props();

    let isOpen = $state(false);
    let containerEl = $state(null);

    let selectedLabel = $derived.by(() => {
        const found = options.find(opt => opt.value === value);
        return found ? found.label : placeholder;
    });

    function toggleDropdown(e) {
        e.stopPropagation();
        if (disabled) return;
        isOpen = !isOpen;
    }

    function selectOption(optVal) {
        isOpen = false;
        onChange(optVal);
    }

    function handleClickOutside(e) {
        if (containerEl && !containerEl.contains(e.target)) {
            isOpen = false;
        }
    }

    onMount(() => {
        window.addEventListener('click', handleClickOutside);
    });

    onDestroy(() => {
        window.removeEventListener('click', handleClickOutside);
    });
</script>

<!-- svelte-ignore a11y_click_events_have_key_events -->
<!-- svelte-ignore a11y_no_static_element_interactions -->
<div class="dropdown-container" class:disabled bind:this={containerEl}>
    <button 
        type="button" 
        class="dropdown-trigger" 
        class:open={isOpen} 
        {disabled} 
        onclick={toggleDropdown}
    >
        <span class="dropdown-text">{selectedLabel}</span>
        <svg 
            class="dropdown-chevron" 
            class:rotated={isOpen} 
            width="12" 
            height="12" 
            viewBox="0 0 24 24" 
            fill="none" 
            stroke="currentColor" 
            stroke-width="2.5" 
            stroke-linecap="round" 
            stroke-linejoin="round"
        >
            <polyline points="6 9 12 15 18 9"></polyline>
        </svg>
    </button>

    {#if isOpen}
        <div class="dropdown-menu">
            {#each options as opt}
                <button 
                    type="button" 
                    class="dropdown-item" 
                    class:selected={opt.value === value}
                    onclick={() => selectOption(opt.value)}
                >
                    {opt.label}
                    {#if opt.value === value}
                        <svg class="check-icon" width="12" height="12" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="3">
                            <polyline points="20 6 9 17 4 12"></polyline>
                        </svg>
                    {/if}
                </button>
            {/each}
        </div>
    {/if}
</div>

<style>
    .dropdown-container {
        position: relative;
        width: 100%;
        font-family: 'Inter', -apple-system, sans-serif;
    }

    .dropdown-container.disabled {
        opacity: 0.45;
        cursor: not-allowed;
    }

    .dropdown-trigger {
        width: 100%;
        display: flex;
        justify-content: space-between;
        align-items: center;
        background: rgba(0, 0, 0, 0.28);
        border: 1px solid rgba(255, 255, 255, 0.08);
        border-radius: 8px;
        padding: 0.5rem 0.8rem;
        color: #f5f5f7;
        font-size: 0.8rem;
        font-weight: 500;
        text-align: left;
        cursor: pointer;
        transition: all 0.2s cubic-bezier(0.25, 0.1, 0.25, 1);
        outline: none;
    }

    .dropdown-trigger:hover:not(:disabled) {
        border-color: rgba(255, 255, 255, 0.15);
        background: rgba(255, 255, 255, 0.02);
    }

    .dropdown-trigger:focus:not(:disabled),
    .dropdown-trigger.open {
        border-color: #0A84FF;
        box-shadow: 0 0 0 3px rgba(10, 132, 255, 0.18);
        background: rgba(0, 0, 0, 0.42);
    }

    .dropdown-trigger:disabled {
        cursor: not-allowed;
    }

    .dropdown-text {
        overflow: hidden;
        text-overflow: ellipsis;
        white-space: nowrap;
        margin-right: 0.5rem;
    }

    .dropdown-chevron {
        color: #86868b;
        transition: transform 0.25s cubic-bezier(0.25, 1, 0.5, 1), color 0.2s;
        flex-shrink: 0;
    }

    .dropdown-trigger:hover .dropdown-chevron {
        color: #f5f5f7;
    }

    .dropdown-chevron.rotated {
        transform: rotate(180deg);
        color: #0A84FF;
    }

    .dropdown-menu {
        position: absolute;
        top: calc(100% + 5px);
        left: 0;
        width: 100%;
        background: rgba(30, 30, 32, 0.92);
        backdrop-filter: blur(16px);
        -webkit-backdrop-filter: blur(16px);
        border: 1px solid rgba(255, 255, 255, 0.08);
        border-radius: 10px;
        padding: 4px;
        box-shadow: 0 8px 24px rgba(0, 0, 0, 0.4),
                    0 2px 8px rgba(0, 0, 0, 0.2);
        z-index: 100;
        max-height: 250px;
        overflow-y: auto;
        display: flex;
        flex-direction: column;
        gap: 2px;
        animation: scaleIn 0.18s cubic-bezier(0.34, 1.56, 0.64, 1);
        transform-origin: top center;
    }

    @keyframes scaleIn {
        from { opacity: 0; transform: scale(0.95) translateY(-2px); }
        to { opacity: 1; transform: scale(1) translateY(0); }
    }

    .dropdown-item {
        width: 100%;
        display: flex;
        justify-content: space-between;
        align-items: center;
        background: transparent;
        border: none;
        color: #a1a1a6;
        font-family: 'Inter', sans-serif;
        font-size: 0.78rem;
        font-weight: 500;
        padding: 0.45rem 0.65rem;
        border-radius: 6px;
        cursor: pointer;
        text-align: left;
        transition: all 0.15s ease;
    }

    .dropdown-item:hover {
        background: rgba(255, 255, 255, 0.05);
        color: #f5f5f7;
    }

    .dropdown-item.selected {
        background: rgba(10, 132, 255, 0.12);
        color: #0A84FF;
        font-weight: 600;
    }

    .check-icon {
        flex-shrink: 0;
        margin-left: 0.5rem;
    }
</style>
