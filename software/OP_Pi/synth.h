#ifndef SYNTH_H // include guard
#define SYNTH_H

#include <soundio/soundio.h>
namespace OP_Pi
{
    class Synth
    {
        public:
            double processSound(int frame, double seconds_offset, double sample_rate);
            double pitch = 440.0;
    };
}

#endif /* SYNTH_H */