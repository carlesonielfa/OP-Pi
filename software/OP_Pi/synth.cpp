#include "synth.h"
#include "reverb.h"

using namespace OP_Pi;

Synth::Synth(double sampleRate, InstrumentDef *instrumentDef, unsigned short *rootNote, SCALE *scale)
        : Instrument(sampleRate, rootNote, scale) {
    this->instrumentDef = instrumentDef;

    //TODO Remove hardcoded effect
    /*EQ* eq = new EQ(sampleRate);
    eq->setFrequency(10000);
    eq->setQ(1);
    eq->setGain(-12);*/
    //effects.push_back(eq);
    //effects.push_back(new Reverb(sampleRate));
}
Synth::~Synth() {
    delete instrumentDef;
}

float Synth::GenerateNoteSound(double time, Note n, bool &noteFinished) {
    return gain*instrumentDef->GenerateSound(time, n, noteFinished);
}


