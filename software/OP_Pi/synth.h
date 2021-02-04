#ifndef SYNTH_H // include guard
#define SYNTH_H

#include "instrument.h"
namespace OP_Pi
{
    class Synth: public Instrument
    {
        public:
            double processSound(int frame, double seconds_offset, double sample_rate);
    };
}

#endif /* SYNTH_H */