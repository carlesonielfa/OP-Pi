//
// Created by carles on 11/2/21.
//

#include "reverb.h"
#include "math.h"
using namespace OP_Pi;
Reverb::Reverb(int sampleRate) : Effect(sampleRate) {

}

float* Reverb::CombFilter(float* input, int nSamples, float delayInMilliSeconds, float decayFactor, float sampleRate)
{
    //Calculating delay in samples from the delay in Milliseconds. Calculated from number of samples per millisecond
    int delaySamples = (int) (delayInMilliSeconds * (sampleRate / 1000.0));

    float* combFilterSamples = new float[nSamples];
    for(int i=0; i<nSamples;i++){
        //copy output array
        combFilterSamples[i] = input[i];

        //Applying algorithm for Comb Filter
        if(i-delaySamples>0)
            combFilterSamples[i] = input[i] + decayFactor*combFilterSamples[i-delaySamples];
    }
    /*
    for (int i=0; i<nSamples; i++)
    {
        //copy output array
        combFilterSamples[i] = input[i];

        //Applying algorithm for Comb Filter
        if(i<nSamples-delaySamples)
            combFilterSamples[i+delaySamples] += (combFilterSamples[i] * decayFactor);
    }*/
    return combFilterSamples;
}
float* Reverb::AllPassFilter(float* input, int nSamples, float sampleRate)
{
    int delaySamples = (int) ((float)89.27f * (sampleRate/1000)); // Number of delay input. Calculated from number of input per millisecond
    float* allPassFilterSamples = new float[nSamples];
    float decayFactor = 0.131f;

    //Applying algorithm for All Pass Filter
    for(int i=0; i < nSamples; i++)
    {
        allPassFilterSamples[i] = input[i];

        if(i - delaySamples >= 0)
            allPassFilterSamples[i] += -decayFactor * allPassFilterSamples[i-delaySamples];

        if(i - delaySamples >= 1)
            allPassFilterSamples[i] += decayFactor * allPassFilterSamples[i+20-delaySamples];
    }


    //This is for smoothing out the input and normalizing the audio. Without implementing this, the input overflow causing clipping of audio
    float value = allPassFilterSamples[0];
    float max = 0.0f;

    for(int i=0; i < nSamples; i++)
    {
        if(abs(allPassFilterSamples[i]) > max)
            max = abs(allPassFilterSamples[i]);

        float currentValue = allPassFilterSamples[i];
        value = ((value + (currentValue - value))/max);

        allPassFilterSamples[i] = value;
    }
    return allPassFilterSamples;
}
void OP_Pi::Reverb::ApplyEffect(float *outputs, int nSamples) {
    //4 Comb Filters in parallel
    float* combFilterSamples1 = CombFilter(outputs, nSamples, delay, decay, sampleRate);
    float* combFilterSamples2 = CombFilter(outputs, nSamples, (delay - 11.73f), (decay - 0.1313f), sampleRate);
    float* combFilterSamples3 = CombFilter(outputs, nSamples, (delay + 19.31f), (decay - 0.2743f), sampleRate);
    float* combFilterSamples4 = CombFilter(outputs, nSamples, (delay - 7.97f), (decay - 0.31f), sampleRate);

    float* outputComb = new float[nSamples];
    for( int i = 0; i < nSamples; i++)
    {
        outputComb[i] = combFilterSamples1[i] + combFilterSamples2[i] + combFilterSamples3[i] + combFilterSamples4[i];
    }
    delete combFilterSamples1;
    delete combFilterSamples2;
    delete combFilterSamples3;
    delete combFilterSamples4;

    //Algorithm for Dry/Wet Mix in the output audio
    float* mixAudio = new float[nSamples];
    for(int i=0; i<nSamples; i++)
        mixAudio[i] = ((100 - wet) * outputs[i]) + (wet * outputComb[i]);
    outputs = mixAudio;
    /*
    float* allPassFilterSamples1 = AllPassFilter(mixAudio, nSamples, sampleRate);
    float* allPassFilterSamples2 = AllPassFilter(allPassFilterSamples1, nSamples, sampleRate);

    for(int i=0; i<nSamples;i++){
        instrumentOutputs[i] = allPassFilterSamples2[i];
    }
    delete mixAudio;
    delete allPassFilterSamples1;
    delete allPassFilterSamples2;*/
}
