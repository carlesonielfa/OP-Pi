//
// Created by carles on 8/2/21.
//
#include "daw.h"
#include "synth.h"
using namespace OP_Pi;
Daw::Daw(double sampleRate) {
    this->sampleRate = sampleRate;

    //Create Initial instruments
    instruments.push_back(new Synth(sampleRate, new SynthDefSine(), &rootNote, &scale));
    instruments.push_back(new Synth(sampleRate, new SynthDefBell(), &rootNote, &scale));
    instruments.push_back(new Synth(sampleRate, new SynthDefHarmonica(), &rootNote, &scale));
    instrumentOutputs = new float*[instruments.size()];
    instrumentGains = new float*[instruments.size()];
    for(int i = 0; i<instruments.size(); i++){
        instrumentGains[i] = &instruments[i]->gain;
        instrumentOutputs[i] = &instruments[i]->lastOutput;
    }
    activeInstrument = 0;

    ChangeScale(60,SCALE::MINOR);

    //Pattern tests
    patterns.push_back(new Pattern);
    //patterns[0]->AddNote(instruments[2], 6, 0, (60.0 / 100), &rootNote, &scale);
    patterns[0]->AddNote(instruments[2], 2, 60.0 / 100, 2 * (60.0 / 100), &rootNote, &scale);
    patterns[0]->AddNote(instruments[2], 0, 2 * (60.0 / 100), 3 * (60.0 / 100), &rootNote, &scale);
    //patterns[0]->AddNote(instruments[2], 4, 3 * (60.0 / 100), 4 * (60.0 / 100)-0.01, &rootNote, &scale);
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
    if(activeView==DAW_VIEW::PATTERN && play) {
        PlayPattern(fmod(time,4*60.0/bpm), outputs, nSamples);

        //Cursor shows play progress in current beat
        cursor = TimeToBarPosition(time-latency);
    }

}


void Daw::NoteOn(int noteIndex, double timeOn) {
    return instruments[activeInstrument]->NoteOn(noteIndex, timeOn);
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
    return time/=4*60.0/bpm;
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

void Daw::ChangeScale(int rootNote, SCALE scale){
    this->rootNote = rootNote;
    this->scale = scale;
    getNamesInScale(noteNames, rootNote, scale);
}

void Daw::ChangeActiveView(DAW_VIEW newView) {
    activeView=newView;
    cursor=0;
}

void Daw::ChangeActiveView() {
    ChangeActiveView(static_cast<DAW_VIEW>((activeView + 1) % DAW_VIEW::DAW_VIEW_SIZE_INDICATOR));
}

void Daw::TogglePlay() {
    play = !play;
    //TODO: Add code for computing time offset
}




