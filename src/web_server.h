#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <WiFi.h>
#include <WebServer.h>
#include "dsp/dsp_core.h"

extern WebServer server;

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>ESP32-S3 DSP Control</title>
    <style>
        body { font-family: Arial, sans-serif; background-color: #121212; color: #fff; text-align: center; margin: 0; padding: 20px; }
        .card { background-color: #1e1e1e; border-radius: 15px; padding: 20px; max-width: 400px; margin: auto; box-shadow: 0 4px 10px rgba(0,0,0,0.5); }
        h2 { color: #00e676; margin-bottom: 20px; }
        .slider-group { margin: 20px 0; text-align: left; }
        label { font-size: 16px; font-weight: bold; display: block; margin-bottom: 5px; }
        input[type=range] { width: 100%; height: 8px; border-radius: 5px; background: #333; outline: none; }
        .btn { background-color: #00e676; color: #000; border: none; padding: 12px 24px; font-size: 16px; font-weight: bold; border-radius: 25px; cursor: pointer; width: 100%; margin-top: 15px; }
        .btn-mute { background-color: #ff5252; color: white; }
    </style>
</head>
<body>
    <div class="card">
        <h2>🎛️ ESP32-S3 DSP Panel</h2>
        
        <div class="slider-group">
            <label>🔊 Master Volume: <span id="volVal">80</span>%</label>
            <input type="range" id="vol" min="0" max="100" value="80" oninput="updateDSP()">
        </div>

        <div class="slider-group">
            <label>🎸 Bass: <span id="bassVal">1.0</span>x</label>
            <input type="range" id="bass" min="0" max="2" step="0.1" value="1.0" oninput="updateDSP()">
        </div>

        <div class="slider-group">
            <label>🎤 Mid: <span id="midVal">1.0</span>x</label>
            <input type="range" id="mid" min="0" max="2" step="0.1" value="1.0" oninput="updateDSP()">
        </div>

        <div class="slider-group">
            <label>🎼 Treble: <span id="trebleVal">1.0</span>x</label>
            <input type="range" id="treble" min="0" max="2" step="0.1" value="1.0" oninput="updateDSP()">
        </div>

        <button id="muteBtn" class="btn" onclick="toggleMute()">Mute / Unmute</button>
    </div>

    <script>
        let isMuted = false;

        function updateDSP() {
            let vol = document.getElementById('vol').value;
            let bass = document.getElementById('bass').value;
            let mid = document.getElementById('mid').value;
            let treble = document.getElementById('treble').value;

            document.getElementById('volVal').innerText = vol;
            document.getElementById('bassVal').innerText = bass;
            document.getElementById('midVal').innerText = mid;
            document.getElementById('trebleVal').innerText = treble;

            fetch(`/set?vol=${vol/100}&bass=${bass}&mid=${mid}&treble=${treble}&mute=${isMuted ? 1 : 0}`);
        }

        function toggleMute() {
            isMuted = !isMuted;
            document.getElementById('muteBtn').classList.toggle('btn-mute', isMuted);
            updateDSP();
        }
    </script>
</body>
</html>
)rawliteral";

inline void setupWebServer() {
    WiFi.softAP("ESP32-DSP-Audio", "12345678");

    server.on("/", []() {
        server.send(200, "text/html", INDEX_HTML);
    });

    server.on("/set", []() {
        if (server.hasArg("vol")) dspConfig.masterVolume = server.arg("vol").toFloat();
        if (server.hasArg("bass")) dspConfig.bassGain = server.arg("bass").toFloat();
        if (server.hasArg("mid")) dspConfig.midGain = server.arg("mid").toFloat();
        if (server.hasArg("treble")) dspConfig.trebleGain = server.arg("treble").toFloat();
        if (server.hasArg("mute")) dspConfig.isMuted = (server.arg("mute").toInt() == 1);
        server.send(200, "text/plain", "OK");
    });

    server.begin();
}

#endif
