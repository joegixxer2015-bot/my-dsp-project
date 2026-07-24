#ifndef DSP_CORE_H
#define DSP_CORE_H

#include <Arduino.h>

struct DSPSettings {
    float mainVolume = 0.8f;
    float gainBass   = 0.0f;
    float gainMid    = 0.0f;
    float gainHigh   = 0.0f;
};

extern DSPSettings dspConfig;

void initDSP();
void processDSP();

#endif
