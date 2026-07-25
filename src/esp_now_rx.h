#ifndef ESP_NOW_RX_H
#ifndef ESP_NOW_RX_H
#define ESP_NOW_RX_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "dsp/dsp_core.h"

// โครงสร้างข้อมูลต้องตรงกับตัวส่ง (ESP32-C3)
typedef struct struct_message {
    int volume;       // 0 - 100
    bool buttonState; // true = Mute, false = Unmute
} struct_message;

inline void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
    struct_message receivedData;
    memcpy(&receivedData, incomingData, sizeof(receivedData));

    // นำค่าที่รับได้จาก ESP32-C3 ไปอัปเดตระดับเสียง DSP ทันที
    dspConfig.masterVolume = receivedData.volume / 100.0f;
    
    if (receivedData.buttonState) {
        dspConfig.isMuted = !dspConfig.isMuted; // สลับสถานะ Mute
    }

    Serial.printf("ESP-NOW Recv -> Vol: %d%%, Mute: %s\n", 
                  receivedData.volume, dspConfig.isMuted ? "YES" : "NO");
}

inline void setupESPNow() {
    WiFi.mode(WIFI_AP_STA); // เปิดทั้ง AP (ให้ Web UI ใช้) และ STA (ให้ ESP-NOW ใช้)

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_recv_cb(OnDataRecv);
    Serial.println("ESP-NOW Receiver Ready!");
}

#endif
