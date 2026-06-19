<!-- src/components/TelemetryChart.svelte -->
<script>
    import { onMount } from 'svelte';

    let { sample = null } = $props();

    let canvasEl = $state(null);
    let history = []; // array of { actual, target, current }
    const MAX_POINTS = 120; // 12 seconds at 10Hz

    // Watch for new samples and draw
    $effect(() => {
        if (sample) {
            history.push({
                actual: sample.angle || 0,
                target: sample.targetAngle || 0,
                current: sample.current_ma || 0
            });
            if (history.length > MAX_POINTS) {
                history.shift();
            }
            draw();
        }
    });

    function draw() {
        if (!canvasEl) return;
        const ctx = canvasEl.getContext('2d');
        const dpr = window.devicePixelRatio || 1;
        const width = canvasEl.width / dpr;
        const height = canvasEl.height / dpr;

        // Reset scale transform and clear logical area
        ctx.setTransform(1, 0, 0, 1, 0, 0);
        ctx.scale(dpr, dpr);

        // Clear canvas — Apple dark gray
        ctx.fillStyle = '#1c1c1e';
        ctx.fillRect(0, 0, width, height);

        // Draw background grid lines (horizontal)
        ctx.strokeStyle = 'rgba(255, 255, 255, 0.06)';
        ctx.lineWidth = 1;
        
        const gridRows = 4;
        for (let i = 1; i < gridRows; i++) {
            const y = (height / gridRows) * i;
            ctx.beginPath();
            ctx.moveTo(0, y);
            ctx.lineTo(width, y);
            ctx.stroke();

            // Grid scale labels — slightly brighter
            ctx.fillStyle = 'rgba(148, 163, 184, 0.65)';
            ctx.font = '10px system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif';
            
            // Left (Angle: 0 to 360)
            ctx.textAlign = 'left';
            const angleVal = Math.round(360 - (360 / gridRows) * i);
            ctx.fillText(`${angleVal}°`, 5, y - 4);
            
            // Right (Current: 0 to 1000mA)
            ctx.textAlign = 'right';
            const curVal = Math.round(1000 - (1000 / gridRows) * i);
            ctx.fillText(`${curVal}mA`, width - 5, y - 4);
        }

        if (history.length < 2) return;

        // X coordinate spacing
        const dx = width / (MAX_POINTS - 1);

        // Helper to convert angle (0-360) to Y
        const getAngleY = (val) => {
            // map [0, 360] to [height-20, 20]
            const padding = 15;
            return height - padding - (val / 360) * (height - 2 * padding);
        };

        // Helper to convert current (0-1000mA) to Y
        const getCurrentY = (val) => {
            // map [0, 1000] to [height-20, 20]
            const padding = 15;
            const capped = Math.min(val, 1000);
            return height - padding - (capped / 1000) * (height - 2 * padding);
        };

        // 1. Draw Target Angle Line (Soft Orange Dashed)
        ctx.strokeStyle = '#FF9F0A';
        ctx.lineWidth = 1.5;
        ctx.setLineDash([4, 4]);
        ctx.beginPath();
        history.forEach((pt, idx) => {
            const x = idx * dx;
            const y = getAngleY(pt.target);
            if (idx === 0) ctx.moveTo(x, y);
            else ctx.lineTo(x, y);
        });
        ctx.stroke();
        ctx.setLineDash([]); // Reset line dash

        // 2. Draw Current Line (Soft Purple)
        ctx.strokeStyle = '#BF5AF2';
        ctx.lineWidth = 1.5;
        ctx.beginPath();
        history.forEach((pt, idx) => {
            const x = idx * dx;
            const y = getCurrentY(pt.current);
            if (idx === 0) ctx.moveTo(x, y);
            else ctx.lineTo(x, y);
        });
        ctx.stroke();

        // 3. Draw Actual Angle Line (Accent Blue with subtle shadow)
        ctx.strokeStyle = '#0A84FF';
        ctx.lineWidth = 2;
        ctx.shadowColor = 'rgba(10, 132, 255, 0.3)';
        ctx.shadowBlur = 4;
        ctx.beginPath();
        history.forEach((pt, idx) => {
            const x = idx * dx;
            const y = getAngleY(pt.actual);
            if (idx === 0) ctx.moveTo(x, y);
            else ctx.lineTo(x, y);
        });
        ctx.stroke();

        // Reset shadow for next render
        ctx.shadowBlur = 0;
    }

    onMount(() => {
        // Handle resizing or display sync if needed
        const resizeObserver = new ResizeObserver(() => {
            if (canvasEl) {
                const rect = canvasEl.parentElement.getBoundingClientRect();
                const dpr = window.devicePixelRatio || 1;
                canvasEl.width = rect.width * dpr;
                canvasEl.height = 140 * dpr;
                canvasEl.style.width = `${rect.width}px`;
                canvasEl.style.height = `140px`;
                draw();
            }
        });
        resizeObserver.observe(canvasEl.parentElement);

        return () => resizeObserver.disconnect();
    });
</script>

<div class="chart-wrapper">
    <div class="chart-legend">
        <span class="legend-item actual">
            <span class="color-dot actual"></span> Actual Position
        </span>
        <span class="legend-item target">
            <span class="color-dot target"></span> Target Position
        </span>
        <span class="legend-item current">
            <span class="color-dot current"></span> Current Draw
        </span>
    </div>
    
    <div class="canvas-container">
        <canvas bind:this={canvasEl}></canvas>
    </div>
</div>

<style>
    .chart-wrapper {
        background: rgba(28, 28, 30, 0.6);
        border: 1px solid rgba(255, 255, 255, 0.08);
        border-radius: 14px;
        padding: 0.85rem 1rem;
        display: flex;
        flex-direction: column;
        gap: 0.6rem;
        box-shadow: 0 1px 3px rgba(0, 0, 0, 0.3),
                    0 4px 12px rgba(0, 0, 0, 0.15);
    }
    .chart-legend {
        display: flex;
        justify-content: flex-start;
        gap: 1.2rem;
        font-size: 0.72rem;
        letter-spacing: 0.01em;
    }
    .legend-item {
        display: flex;
        align-items: center;
        gap: 0.4rem;
        color: var(--text-muted);
        font-weight: 500;
    }
    .color-dot {
        width: 7px;
        height: 7px;
        border-radius: 50%;
    }
    .color-dot.actual {
        background: var(--accent, #0A84FF);
        box-shadow: 0 0 4px rgba(10, 132, 255, 0.4);
    }
    .color-dot.target {
        background: var(--warning, #FF9F0A);
    }
    .color-dot.current {
        background: #BF5AF2;
    }
    
    .canvas-container {
        width: 100%;
        height: 140px;
        border-radius: 10px;
        overflow: hidden;
    }
    canvas {
        display: block;
        width: 100%;
        height: 100%;
    }
</style>
