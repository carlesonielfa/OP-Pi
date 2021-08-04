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
    patterns.push_back(new Pattern);
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
    patterns[activePattern]->PlayPattern(time, outputs, nSamples);
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
    getActiveInstrument()->NoteOn(noteIndex, timeOn);
    //TODO Check if we are recording
    if(activeView==DAW_VIEW::PATTERN){
        patterns[activePattern]->AddNote(getActiveInstrument(), noteIndex,
                                            BarPositionToTime(cursor),
                                            BarPositionToTime(cursor)+0.5,
                                            &rootNote, &scale);
    }

}

void Daw::NoteOff(int noteIndex, double timeOff) const {
    getActiveInstrument()->NoteOff(noteIndex, timeOff);
}

unsigned int Daw::getNInstruments() {
    return instruments.size();
}

bool Daw::incrementActiveInstrument(int delta) {
    int n = (activeInstrument + delta) % instruments.size();
    if(n < 0)
        n+=instruments.size();
    return setIndexActiveInstrument(n);
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

void Daw::IncrementOctave(int increment) const {
    getActiveInstrument()->octave+=increment;
}

short Daw::getOctaveCurrentInstrument() const {
    return getActiveInstrument()->octave;
}

Envelope *Daw::getInstrumentEnvelope() const {
    return getActiveInstrument()->GetEnvelope();
}

char * Daw::getActiveInstrumentPresetName() const {
    return getActiveInstrument()->GetPresetName();
}

double Daw::TimeToBarPosition(double time) const {
    time = fmod(time,4*60.0/bpm);
    return time/(4*60.0/bpm);
}

double Daw::BarPositionToTime(double position) const {
    return position*getBarDuration();
}

double Daw::getBeatDuration() const {
    return 60.0/bpm;
}

double Daw::getBarDuration() const {
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

void Daw::EncoderRotation(unsigned char encoder, short value) {
    switch(activeView){
        case DAW_VIEW::PATTERN: {
            //Move cursor to next division
            //TODO fix cursor <0
            float division = 1.0 / 16;
            if (encoder == 0) {
                float progressInDivision = fmod(cursor, division);
                if (progressInDivision != 0){
                    cursor -= progressInDivision;
                    cursor += value>0 ? division:0;
                }
                else
                    cursor += value*division;
                cursor = fmod(cursor,1);
            }
            //Change active pattern
            else if(encoder==1){
                activePattern = fmod(activePattern+value,patterns.size());
            }
            break;
        }
        case DAW_VIEW::MIXER:
            //Change bpm
            if(encoder==0){
                bpm = bpm + value;           
            }
            //Change active instrument gain
            if(encoder==1)
                instruments[activeInstrument]->setGain(instruments[activeInstrument]->gain+value*0.05);
            break;
        case DAW_VIEW::INSTRUMENT:
            //Change active instrument preset
            if(encoder==0)
            {
                //TODO: Change active instrument preset
            }
            //Change cursor position
            if(encoder==1)
            {
                cursor = fmod(cursor+value,4);
            }
            //Change envelope values
            if(encoder==2)
            {
                //TODO: Work with any envelope
                EnvelopeADSR* env = static_cast<EnvelopeADSR*>(instruments[activeInstrument]->GetEnvelope());
                //Attack
                if(cursor==0)
                    env->attackTime+=value*0.01;
                //Decay
                else if(cursor==1)
                    env->decayTime+=value*0.01;
                else if(cursor==2)
                    env->sustainAmplitude+=value*0.01;
                else if(cursor==3)
                    env->releaseTime+=value*0.01;

            }
            break;
    }
}

void Daw::EncoderPressed(unsigned char encoder) {

}

Instrument* Daw::getActiveInstrument() const {
    return instruments[activeInstrument];
}

unsigned char Daw::getIndexActivePattern() const {
    return activePattern;
}




