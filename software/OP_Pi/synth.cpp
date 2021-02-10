#include "synth.h"
using namespace OP_Pi;


Synth::~Synth() {
    delete instrumentDef;
}
void Synth::GenerateNoteSound(double time, float *outputs, int nSamples, Note n, bool &noteFinished) {
	for(int i=0; i<nSamples; i++){
        outputs[i] += gain*instrumentDef->GenerateSound(time+1.0*i/sampleRate, n, noteFinished);
	}
}

Synth::Synth(double sampleRate, InstrumentDef *instrumentDef):Instrument(sampleRate){
    this->instrumentDef = instrumentDef;
}
