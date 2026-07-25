#include <Arduino.h>
#include "dsp/dsp_core.h"
#include "web_server.h"
#include "esp_now_rx.h"

// ตัวแปรระดับ Global ประกาศครั้งเดียวที่นี่
DSPConfig dspConfig;
WebServer server(80);

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("--- ESP32-S3 DSP & ESP-NOW Initializing ---");

    initI2S();          
    setupWebServer();   
    setupESPNow();      

    Serial.print("ESP32-S3 MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void loop() {
    server.handleClient();
    
    if (!dspConfig.isMuted) {
        generateAudioTone();
    }
}
