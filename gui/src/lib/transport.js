// src/lib/transport.js

export class SerialTransport {
    constructor(onMessage, onDisconnect, onLog) {
        this.onMessage = onMessage;       // callback for parsed JSON
        this.onDisconnect = onDisconnect; // callback for connection closed
        this.onLog = onLog;               // callback for diagnostic logs
        this.port = null;
        this.reader = null;
        this.writer = null;
        this.keepReading = true;
    }

    async connect() {
        if (!("serial" in navigator)) {
            throw new Error("Web Serial API is not supported in this browser. Please use Chrome, Edge, or Opera.");
        }
        
        this.onLog("Requesting USB Serial port permission...");
        this.port = await navigator.serial.requestPort();
        
        this.onLog("Opening serial port at 250000 baud...");
        await this.port.open({ baudRate: 250000 });
        
        const textEncoder = new TextEncoderStream();
        this.writableStreamClosed = textEncoder.readable.pipeTo(this.port.writable);
        this.writer = textEncoder.writable.getWriter();

        this.keepReading = true;
        this.readLoopPromise = this.readLoop();
        this.onLog("Web Serial connected successfully.");
    }

    async disconnect() {
        this.onLog("Disconnecting serial port...");
        this.keepReading = false;
        
        if (this.reader) {
            try {
                await this.reader.cancel();
            } catch (e) {
                // Ignore cancel errors
            }
        }

        if (this.readableStreamClosed) {
            try {
                await this.readableStreamClosed;
            } catch (e) {
                // Ignore stream close errors
            }
        }
        
        if (this.writer) {
            try {
                await this.writer.close();
            } catch (e) {
                // Ignore close errors
            }
        }

        if (this.writableStreamClosed) {
            try {
                await this.writableStreamClosed;
            } catch (e) {
                // Ignore stream close errors
            }
        }

        if (this.port) {
            try {
                await this.port.close();
            } catch (e) {
                // Ignore close errors
            }
        }
        
        this.port = null;
        this.reader = null;
        this.writer = null;
        this.readableStreamClosed = null;
        this.writableStreamClosed = null;
        this.onLog("Serial port disconnected.");
    }

    async send(dataObj) {
        if (!this.writer) {
            throw new Error("Cannot send packet: Serial port is not connected.");
        }
        const msg = JSON.stringify(dataObj) + "\n";
        await this.writer.write(msg);
    }

    async readLoop() {
        const textDecoder = new TextDecoderStream();
        this.readableStreamClosed = this.port.readable.pipeTo(textDecoder.writable);
        this.reader = textDecoder.readable.getReader();

        let buffer = "";

        try {
            while (this.keepReading) {
                const { value, done } = await this.reader.read();
                if (done) {
                    this.onLog("Serial stream completed (done).");
                    break;
                }
                if (value) {
                    buffer += value;
                    let lines = buffer.split("\n");
                    buffer = lines.pop(); // keep the last incomplete line
                    for (let line of lines) {
                        line = line.trim();
                        if (!line) continue;
                        try {
                            const obj = JSON.parse(line);
                            this.onMessage(obj);
                        } catch (e) {
                            // Print non-JSON lines as board logs (e.g. boot output)
                            this.onLog(`[BOARD-RAW] ${line}`);
                        }
                    }
                }
            }
        } catch (error) {
            this.onLog(`Serial read loop error: ${error.message}`);
        } finally {
            this.reader.releaseLock();
            this.onDisconnect();
        }
    }
}
