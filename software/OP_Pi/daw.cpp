//
// Created by carles on 8/2/21.
//
#include "daw.h"
#include "synth.h"
using namespace OP_Pi;
Daw::Daw(){
    Instrument* synth = new Synth();
    instruments.push_back(synth);
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
double Daw::PlayActiveSynth(double time, double seconds_offset) {
    return instruments[activeInstrument]->PlayNotes(time,seconds_offset);
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
