#include "sampler.h"

using namespace OP_Pi;



Sampler::Sampler(double sampleRate, Sample *sample, unsigned short *rootNote, SCALE *scale)
        : Instrument(sampleRate, rootNote, scale) {
    //this->instrumentDef = instrumentDef;

    //TODO Remove hardcoded effect
    /*EQ* eq = new EQ(sampleRate);
    eq->setFrequency(10000);
    eq->setQ(1);
    eq->setGain(-12);*/
    //effects.push_back(eq);
    //effects.push_back(new Reverb(sampleRate));
}
Sampler::~Sampler(){
    delete sample;
}