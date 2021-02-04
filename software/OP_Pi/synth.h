#ifndef SYNTH_H // include guard
#define SYNTH_H

#include "instrument.h"
namespace OP_Pi
{
    enum OSC_TYPE{
        SINE, SQUARE, TRIANGLE, SAW, NOISE
    };

    class Synth: public Instrument
    {
        public:
            double ProcessSound(int frame, double seconds_offset, double sample_rate);
            OSC_TYPE osc_type = OSC_TYPE::SINE;
    };
}

#endif /* SYNTH_H */