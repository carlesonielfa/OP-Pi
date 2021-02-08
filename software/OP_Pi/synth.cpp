#include "synth.h"
using namespace OP_Pi;


Synth::Synth(InstrumentDef* instrumentDef){
    this->instrumentDef = instrumentDef;
}
Synth::~Synth() {
    delete instrumentDef;
}
double Synth::GenerateNoteSound(double time, double seconds_offset, Note n, bool& noteFinished){
    double output = instrumentDef->GenerateSound(time,seconds_offset,n,noteFinished);
	//Apply gain
	output*=gain;
    return output;
}
