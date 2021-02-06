#ifndef SYNTH_H // include guard
#define SYNTH_H

#include "instrument.h"
#include "sound_utils.h"
#include <math.h>
namespace OP_Pi
{
    enum OSC_TYPE{
        SINE, SQUARE, TRIANGLE, SAW, NOISE
    };
    struct SynthDef: public InstrumentDef
	{
		SynthDef(){
            env = new EnvelopeADSR();
        }
		//double GenerateSound(const double time, Note n, bool &noteFinished){return 0};
        
	};
    // Represents an object that synthesizes sound and outputs it
    class Synth: public Instrument
    {
        public:
            //SynthDef synth;
            Synth();
            EnvelopeADSR env;
        protected:
            virtual double GenerateNoteSound(double time, double seconds_offset, Note n, bool& noteFinished);
    };
}

#endif /* SYNTH_H */