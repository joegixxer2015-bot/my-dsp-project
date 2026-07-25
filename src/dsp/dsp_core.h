#ifndef DSP_CORE_H
#define DSP_CORE_H

#include <Arduino.h>
#include "driver/i2s.h"

// การตั้งค่า Pin I2S สำหรับ ESP32-S3
#define I2S_BCK_PIN   4  // Bit Clock
#define I2S_LRCK_PIN  5  // Word Select / LRCK
#define I2S_DOUT1_PIN 6  // Data Out 1
#define I2S_DOUT2_PIN 7  // Data Out 2

struct DSPConfig {
    float masterVolume = 0.8f;
    float bassGain = 1.0f;
    float midGain = 1.0f;
    float trebleGain = 1.0f;
    bool isMuted = false;
};

extern DSPConfig dspConfig;

void initI2S();
void generateAudioTone();

#endif
