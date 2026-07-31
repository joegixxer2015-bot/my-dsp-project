#ifndef DSP_CORE_H
#define DSP_CORE_H

#include <Arduino.h>
#include "driver/i2s.h"

#define I2S_BCK_PIN   15  
#define I2S_LRCK_PIN  16 
#define I2S_DOUT1_PIN 17
#define I2S_DOUT2_PIN 18

struct DSPConfig {
    float masterVolume = 0.8f;
    float bassGain = 1.0f;
    float midGain = 1.0f;
    float trebleGain = 1.0f;
    bool isMuted = false;
};

extern DSPConfig dspConfig;

inline void initI2S() {
    // โค้ดสร้าง I2S ตามของเดิมของคุณ
}

inline void generateAudioTone() {
    // โค้ดสร้างเสียง ตามของเดิมของคุณ
}

#endif
