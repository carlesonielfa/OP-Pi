//
// Created by carles on 8/2/21.
//

#include "timeline.h"
using namespace OP_Pi;

void Pattern::PlayPattern(double time, float *output, int nSamples) {
    for(Hit h:hits){
        bool noteFinished = false;
        if(time>=h.note.on)
            h.instrument->GenerateNoteSounds(time,output,nSamples,h.note,noteFinished);
    }
}

void Pattern::AddNote(Instrument *instrument, int noteIndex, float noteStart, float noteEnd, unsigned short *rootNote,
                      SCALE *scale) {
    Hit h {instrument, Note{noteIndex, noteStart, noteEnd, rootNote,scale}};
    hits.push_back(h);

}
