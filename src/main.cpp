#include <Arduino.h>
#include <WiFi.h>
#include "dsp/dsp_core.h"
#include "web_server.h"
#include "esp_now_rx.h"

// ตัวแปรระดับ Global ประกาศครั้งเดียวที่นี่
DSPConfig dspConfig;
WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- ESP32-S3 DSP & ESP-NOW Initializing ---");

  // 1. ตั้งค่าและเปิด Wi-Fi AP + Station ก่อนเสมอ (เพื่อความชัวร์เรื่อง Wi-Fi และ ESP-NOW)
  WiFi.mode(WIFI_AP_STA);
  bool apStatus = WiFi.softAP("ESP32-DSP-Audio", "12345678");
  if (apStatus) {
    Serial.println("Wi-Fi AP Started: ESP32-DSP-Audio");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("Wi-Fi AP Failed to start!");
  }

  // 2. เรียกใช้ WebServer และ ESP-NOW
  setupWebServer();
  setupESPNow();

  // 3. แสดง MAC Address
  Serial.print("ESP32-S3 MAC Address: ");
  Serial.println(WiFi.macAddress());

  // 4. เริ่มระบบ I2S (ใส่ try/check ป้องกันเครื่องดับถ้าไม่ได้ต่ออุปกรณ์)
  Serial.println("Initializing I2S Hardware...");
  initI2S();
  Serial.println("System Ready!");
}

void loop() {
  server.handleClient();

  if (!dspConfig.isMuted) {
    generateAudioTone();
  }
}
