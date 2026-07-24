#ifndef DSP_CORE_H
#define DSP_CORE_H

#include <Arduino.h>
#include "driver/i2s.h"

// การตั้งค่า Pin I2S สำหรับ ESP32-S3
#define I2S_BCK_PIN   4  // Bit Clock (ต่อขนานเข้า PCM5102A ทั้ง 2 ตัว)
#define I2S_LRCK_PIN  5  // Word Select / LRCK (ต่อขนานเข้า PCM5102A ทั้ง 2 ตัว)
#define I2S_DOUT1_PIN 6  // Data Out 1 (เข้า PCM5102A ตัวที่ 1 - CH1/CH2)
#define I2S_DOUT2_PIN 7  // Data Out 2 (เข้า PCM5102A ตัวที่ 2 - CH3/CH4)

struct DSPSettings {
    float mainVolume = 0.8f;
    float gainBass   = 0.0f;
    float gainMid    = 0.0f;
    float gainHigh   = 0.0f;
};

extern DSPSettings dspConfig;

void initI2S();
void generateAudioTone();

#endif
