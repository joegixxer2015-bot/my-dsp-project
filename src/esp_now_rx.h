#ifndef ESP_NOW_RX_H
#define ESP_NOW_RX_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "dsp/dsp_core.h"

typedef struct struct_message {
    int volume;       
    bool buttonState; 
} struct_message;

inline void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
    struct_message receivedData;
    memcpy(&receivedData, incomingData, sizeof(receivedData));

    dspConfig.masterVolume = receivedData.volume / 100.0f;
    
    if (receivedData.buttonState) {
        dspConfig.isMuted = !dspConfig.isMuted;
    }

    Serial.printf("ESP-NOW Recv -> Vol: %d%%, Mute: %s\n", 
                  receivedData.volume, dspConfig.isMuted ? "YES" : "NO");
}

inline void setupESPNow() {
    WiFi.mode(WIFI_AP_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_recv_cb((esp_now_recv_cb_t)OnDataRecv);
    Serial.println("ESP-NOW Receiver Ready!");
}

#endif
