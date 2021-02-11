//
// Created by carles on 8/2/21.
//

#include "timeline.h"
using namespace OP_Pi;

void Pattern::PlayPattern(double time, float *output, double nSamples, int bpm, int sampleRate) {
    //TODO: Fix sound cutting in loop
    time = fmod(time, 4*60.0/bpm);
    for(Hit h:hits){
        bool noteFinished = false;
        h.instrument->GenerateNoteSounds(time,output,nSamples,h.note,noteFinished);
    }
}

void Pattern::AddNote(Instrument *instrument, int noteNumber, float noteStart, float noteEnd) {
    Hit h {instrument, Note{noteNumber,noteStart,noteEnd}};
    hits.push_back(h);

}
