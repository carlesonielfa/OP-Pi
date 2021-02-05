#include "instrument.h"
using namespace OP_Pi;

//Envelope
void Instrument::NoteOn(double timeOn)
{
    triggerOnTime = timeOn;
    noteOn = true;
}
// Call when key is released
void Instrument::NoteOff(double timeOff)
{
    triggerOffTime = timeOff;
    noteOn = false;
}
// Get the correct amplitude at the requested point in time
double Instrument::GetAmplitudeEnvelope(double time)
{
    double amplitude = 0.0;
    double lifeTime = time - triggerOnTime;

    if (noteOn)
    {
        if (lifeTime <= attackTime)
        {
            // In attack Phase - approach max amplitude
            amplitude = (lifeTime / attackTime) * startAmplitude;
        }

        if (lifeTime > attackTime && lifeTime <= (attackTime + decayTime))
        {
            // In decay phase - reduce to sustained amplitude
            amplitude = ((lifeTime - attackTime) / decayTime) * (sustainAmplitude - startAmplitude) + startAmplitude;
        }

        if (lifeTime > (attackTime + decayTime))
        {
            // In sustain phase - dont change until note released
            amplitude = sustainAmplitude;
        }
    }
    else
    {
        // Note has been released, so in release phase
        amplitude = ((time - triggerOffTime) / releaseTime) * (0.0 - sustainAmplitude) + sustainAmplitude;
    }

    // Amplitude should not be negative
    if (amplitude <= 0.0001){
        amplitude = 0.0;
    }

    return amplitude;
}


void Instrument::SetPitch(double new_pitch){
    pitch = new_pitch;
};
double Instrument::GetPitch(){
    return pitch;
};
void Instrument::SetGain(double new_gain){
    gain = new_gain;
    if(gain>1){
        fprintf(stderr, "Tried to assign gain bigger than 1");
        gain = 1;
    }
    else if(gain<0){
        fprintf(stderr, "Tried to assign gain smaller than 0");
        gain = 0;  
    }
                            
};
float Instrument::GetGain(){
    return gain;
};
            