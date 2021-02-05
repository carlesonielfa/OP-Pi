#ifndef SYNTH_H // include guard
#define SYNTH_H

#include "instrument.h"
namespace OP_Pi
{
    enum OSC_TYPE{
        SINE, SQUARE, TRIANGLE, SAW, NOISE
    };
    // Represents an object that synthesizes sound and outputs it
    class Synth: public Instrument
    {
        public:
            Synth();
            double ProcessSound(double time);
            OSC_TYPE osc_type = OSC_TYPE::TRIANGLE;
    };
}

#endif /* SYNTH_H */