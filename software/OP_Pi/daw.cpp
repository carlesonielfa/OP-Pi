//
// Created by carles on 8/2/21.
//
#include "daw.h"
#include "synth.h"
using namespace OP_Pi;
Daw::Daw(double sampleRate) {
    this->sampleRate = sampleRate;
    instruments.push_back(new Synth(sampleRate, new SynthDefSine(), nullptr, nullptr));
    instruments.push_back(new Synth(sampleRate, new SynthDefBell(), nullptr, nullptr));
    instruments.push_back(new Synth(sampleRate, new SynthDefHarmonica(), nullptr, nullptr));
    instrumentOutputs = new float*[instruments.size()];
    instrumentGains = new float*[instruments.size()];
    for(int i = 0; i<instruments.size(); i++){
        instrumentGains[i] = &instruments[i]->gain;
        instrumentOutputs[i] = &instruments[i]->lastOutput;
    }
    activeInstrument = 0;
    patterns.push_back(new Pattern);
    //patterns[0]->AddNote(instruments[0],60,1,1.5);
    patterns[0]->AddNote(instruments[2], 63, 0, (60.0 / 100), nullptr, nullptr);
    patterns[0]->AddNote(instruments[2], 60, 60.0 / 100, 2 * (60.0 / 100), nullptr, nullptr);
    patterns[0]->AddNote(instruments[2], 71, 2 * (60.0 / 100), 3 * (60.0 / 100), nullptr, nullptr);
    patterns[0]->AddNote(instruments[2], 67, 3 * (60.0 / 100), 4 * (60.0 / 100), nullptr, nullptr);
}
Daw::~Daw() {
    for(Instrument* i: instruments){
        delete i;
    }
}
void Daw::PlayActiveSynth(double time, float *outputs, int nSamples) {
    instruments[activeInstrument]->PlayNotes(time, outputs, nSamples);
}

void Daw::PlayPattern(double time, float *outputs, int nSamples) {
    patterns[activePattern]->PlayPattern(time, outputs, nSamples, bpm);
}
void Daw::GenerateAudio(double time, float *outputs, int nSamples) {
    //Play active synth
    PlayActiveSynth(time, outputs, nSamples);

    //Play active pattern
    if(activeView==DAW_VIEW::PATTERN) {
        PlayPattern(fmod(time,4*60.0/bpm), outputs, nSamples);

        //Cursor shows play progress in current beat
        cursor = TimeToBarPosition(time);
    }

}


void Daw::NoteOn(int noteIndex, double timeOn) {
    return instruments[activeInstrument]->NoteOn(noteIndex, timeOn, &rootNote, &scale);
}

void Daw::NoteOff(int noteIndex, double timeOff) {
    return instruments[activeInstrument]->NoteOff(noteIndex, timeOff);
}

unsigned int Daw::getNInstruments() {
    return instruments.size();
}

bool Daw::setIndexActiveInstrument(int n) {
    if(n<instruments.size()){
        activeInstrument = n;
        return true;
    }
    else
        return false;
}

unsigned int Daw::getIndexActiveInstrument() const {
    return activeInstrument;
}

void Daw::IncrementOctave(int increment) {
    instruments[activeInstrument]->octave+=increment;
}

char Daw::getOctaveCurrentInstrument() {
    return instruments[activeInstrument]->octave;
}

Envelope *Daw::getInstrumentEnvelope() {
    return instruments[activeInstrument]->GetEnvelope();
}

char * Daw::getActiveInstrumentPresetName() {
    return instruments[activeInstrument]->GetPresetName();
}

double Daw::TimeToBarPosition(double time) {
    time = fmod(time,4*60.0/bpm);
    return time/=4*60.0/bpm;;
}

double Daw::BarPositionToTime(double position) {
    return position*getBarDuration();
}

double Daw::getBeatDuration() {
    return 60.0/bpm;
}

double Daw::getBarDuration() {
    return 4*getBeatDuration();
}

std::vector<Hit> Daw::getHitsInActivePattern() {
    return patterns[activePattern]->hits;
}




