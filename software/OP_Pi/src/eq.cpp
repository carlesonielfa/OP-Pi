//
// Created by carles on 10/2/21.
//

#include "eq.h"
#include <math.h>
float OP_Pi::EQ::getFrequency() const {
    return jFrequency;
}

void OP_Pi::EQ::setFrequency(float jFrequency) {
    EQ::jFrequency = jFrequency;
    CalcFreq(jFrequency);
}

float OP_Pi::EQ::getGain() const {
    return jdBGain;
}

void OP_Pi::EQ::setGain(float jdBGain) {
    EQ::jdBGain = jdBGain;
    CalcGain(jdBGain);
}

float OP_Pi::EQ::getQ() const {
    return jQ;
}

void OP_Pi::EQ::setQ(float jQ) {
    EQ::jQ = jQ;
    CalcQ(jQ);
}

void OP_Pi::EQ::CalcCoeffs(float f, float g, float q) {
    float A, omega, cs, sn, alpha;            // Intermediate variables.
    A     = pow(10,g/40.0f);
    omega = (2 * M_PI * f) / sampleRate;      // M_PI macro holds value of pi.
    sn    = sin(omega);
    cs    = cos(omega);
    alpha = sn / (2.0*q);
    b0    =  1 + (alpha * A);                 // The filter coefficients.
    b1    = -2 * cs;b2    =  1 - (alpha * A);
    a0    =  1 + (alpha / (float)A);
    a1    = -2 * cs;a2    =  1 - (alpha / (float)A);
}

void OP_Pi::EQ::CalcFreq(float jf) {
    // Convert 20 Hz... 20 kHz --> 0.0...1.0
    // Maybe linear conversion isn't ideal
    fFrequency = (jf-20)/(20000-20);
    if(fFrequency>1)
        fFrequency=1;
    else if(fFrequency<0)
        fFrequency=0;
    CalcCoeffs(fFrequency,fdBGain,fQ);
}

void OP_Pi::EQ::CalcGain(float jg) {
    // Convert -12 dB...+12 dB --> 0.0...1.0
    fdBGain = (jg-(-12))/(12-(-12));
    if(fdBGain>1)
        fdBGain=1;
    else if(fdBGain<0)
        fdBGain=0;
    CalcCoeffs(fFrequency,fdBGain,fQ);
}

void OP_Pi::EQ::CalcQ(float jg) {
    // Convert 0.33... 12.0 --> 0.0...1.0
    fQ = (jg-0.33)/(12-0.33);
    if(fQ>1)
        fQ=1;
    else if(fQ<0)
        fQ=0;
    CalcCoeffs(fFrequency,fdBGain,fQ);
}

void OP_Pi::EQ::ApplyEffect(float *outputs, int nSamples) {
    float xn,yn;
    for(int i=0; i<nSamples;i++){
        xn = outputs[i];
        yn = (b0*xn + b1*xnm1 + b2*xnm2 - a1*ynm1 - a2*ynm2)/a0;   // Biquad equation

        xnm2 = xnm1;             // Shift x[n-1] to x[n-2].
        xnm1 = xn;               // Shift x[n]   to x[n-1].
        ynm2 = ynm1;             // Shift y[n-1] to y[n-2]
        ynm1 = yn;               // Shift y[n]   to y[n-1].

        outputs[i] =yn;
    }
}

OP_Pi::EQ::EQ(int sampleRate) : Effect(sampleRate) {

}
