#ifndef INSTRUMENT_H // include guard
#define INSTRUMENT_H
#include <stdio.h>
namespace OP_Pi
{
    // Abstract class that represents an oject that plays sounds
    // It contains an ADSR envelope and basic sound output methods
    class Instrument
    {
        public:
            //ADSR Envelope
            float attackTime = 0.100;
            float decayTime = 0.01;
            float startAmplitude = 1.0;
            float sustainAmplitude = 0.8;
            float releaseTime = 0.200;

            // Call when key is pressed
            void NoteOn(double timeOn);

            // Call when key is released
            void NoteOff(double timeOff);

            //virtual double ProcessSound(int frame, double seconds_offset, double sample_rate) = 0;
            virtual double ProcessSound(double time) = 0;

            void SetPitch(double new_pitch);
            double GetPitch();
            void SetGain(double new_gain);
            float GetGain();
        protected:
            double GetAmplitudeEnvelope(double time);
            bool noteOn = false;
        private:
            float triggerOffTime = 0.0;
            float triggerOnTime = 0.0;
            double pitch=440;
            float gain=0.5;

    };
}

#endif /* INSTRUMENT_H */