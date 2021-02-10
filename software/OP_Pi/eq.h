//
// Created by carles on 10/2/21.
//
#include "effect.h"
#ifndef OP_PI_EQ_H
#define OP_PI_EQ_H
namespace OP_Pi{
    class EQ: public Effect{
    public:
        EQ(int sampleRate);
        void ApplyEffect(float *outputs, int nSamples) override;

        float getFrequency() const;
        void setFrequency(float jFrequency);

        float getGain() const;
        void setGain(float jdBGain);

        float getQ() const;
        void setQ(float jQ);
    private:
        void CalcCoeffs(float f, float g, float q); // Compute biquad coefficients.
        void CalcFreq(float f);               // Convert 20 Hz... 20 kHz --> 0.0...1.0
        void CalcGain(float g);               // Convert -12 dB...+12 dB --> 0.0...1.0
        void CalcQ(float g);                  // Convert 0.33... 12.0 --> 0.0...1.0
    protected:
        float fFrequency;           //    0.0 ... 1.0          Internal
        float fdBGain;              //    0.0 ... 1.0          parameter
        float fQ;                   //    0.0 ... 1.0          format

        float jFrequency;           //  20 Hz ...  20 kHz      GUI
        float jdBGain;              // -12 dB ... +12 dB       parameter
        float jQ;                   //   0.33 ...  12          format.

        float xnm1;                 // x[n-1]
        float xnm2;                 // x[n-2]
        float ynm1;                 // y[n-1]
        float ynm2;                 // y[n-2]

        float a0, a1, a2, b0, b1, b2;             // The biquad coefficients.
    };
}


#endif //OP_PI_EQ_H
