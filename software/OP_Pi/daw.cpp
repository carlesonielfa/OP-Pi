//
// Created by carles on 8/2/21.
//
#include "daw.h"
#include "synth.h"
using namespace OP_Pi;
Daw::Daw(double sampleRate) {
    this->sampleRate = sampleRate;
    instruments.push_back(new Synth(sampleRate,new SynthDefSine()));
    instruments.push_back(new Synth(sampleRate,new SynthDefBell()));
    instruments.push_back(new Synth(sampleRate,new SynthDefHarmonica()));
    outputs = new float*[instruments.size()];
    gains = new float*[instruments.size()];
    for(int i = 0; i<instruments.size(); i++){
        gains[i] = &instruments[i]->gain;
        outputs[i] = &instruments[i]->lastOutput;
    }
    activeInstrument = 0;
}
Daw::~Daw() {
    for(Instrument* i: instruments){
        delete i;
    }
}
void Daw::PlayActiveSynth(double time, float *outputs, int nSamples) {
    instruments[activeInstrument]->PlayNotes(time, outputs, nSamples);
}

void Daw::NoteOn(int noteNumber, double timeOn) {
    return instruments[activeInstrument]->NoteOn(noteNumber,timeOn);
}

void Daw::NoteOff(int noteNumber, double timeOff) {
    return instruments[activeInstrument]->NoteOff(noteNumber,timeOff);
}

unsigned int Daw::GetNInstruments() {
    return instruments.size();
}

bool Daw::SetIndexActiveInstrument(int n) {
    if(n<instruments.size()){
        activeInstrument = n;
        return true;
    }
    else
        return false;
}

unsigned int Daw::GetIndexActiveInstrument() {
    return activeInstrument;
}

void Daw::IncrementOctave(int increment) {
    instruments[activeInstrument]->octave+=increment;
}

char Daw::GetOctaveCurrentInstrument() {
    return instruments[activeInstrument]->octave;
}

Envelope *Daw::GetInstrumentEnvelope() {
    return instruments[activeInstrument]->GetEnvelope();
}

char * Daw::GetActiveInstrumentPresetName() {
    return instruments[activeInstrument]->GetPresetName();
}

