//
// Created by carles on 11/2/21.
//

#ifndef OP_PI_REVERB_H
#define OP_PI_REVERB_H

#include "effect.h"
namespace OP_Pi{
    class Reverb:public Effect{
    public:
        Reverb(int sampleRate);
        float delay = 20;       // Delay of the reverb in ms 20 ...
        float decay = 0.15;     // Decay factor 0-1
        float* CombFilter(float* input, int nSamples, float delayInMilliSeconds, float decayFactor, float sampleRate);
        void ApplyEffect(float *outputs, int nSamples) override;

        float *AllPassFilter(float * input, int nSamples, float sampleRate);
    };
}


#endif //OP_PI_REVERB_H
