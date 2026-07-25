#include <Arduino.h>
#include "dsp/dsp_core.h"
#include "web_server.h"
#include "esp_now_rx.h"

// 1. ประกาศสร้าง Instance ตัวแปร dspConfig ตรงนี้ (สำคัญมาก!)
DSPConfig dspConfig;

// 2. ประกาศ WebServer
WebServer server(80);

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("--- ESP32-S3 DSP & ESP-NOW Initializing ---");

    initI2S();          // สั่งเปิดระบบเสียง 4 Channels
    setupWebServer();   // สั่งเปิดระบบ Web UI ผ่าน Wi-Fi
    setupESPNow();      // สั่งเปิดระบบรับค่าไร้สาย ESP-NOW จาก C3

    // พิมพ์ MAC Address ของ S3 ออกมาทาง Serial Monitor
    Serial.print("ESP32-S3 MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void loop() {
    server.handleClient(); // รันระบบ Web UI
    
    if (!dspConfig.isMuted) {
        generateAudioTone(); // รันระบบประมวลผลเสียง DSP
    }
}
