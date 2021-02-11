//
// Created by carles on 8/2/21.
//

#ifndef OP_PI_TIMELINE_H
#define OP_PI_TIMELINE_H
#include "instrument.h"
#include <vector>
namespace OP_Pi{
    struct Hit{
        Instrument* instrument;
        Note note;
        /*float noteStart;        //Note position within pattern 0-1
        float noteEnd;          //Note end within pattern 0-1
        */
    };
    class Pattern {
    public:
        void PlayPattern(double time, float* output, double nSamples, int bpm, int sampleRate); //Play looping pattern
        void AddNote(Instrument *instrument, int noteNumber, float noteStart, float noteEnd);
    private:
        //int patternNumber;
        std::vector<Hit> hits;
        const int patternLength=1; //Pattern length in bars

    };
    class Timeline{
    private:
        std::vector<std::vector<Pattern*>> patterns;     //Ordered patterns by line and by bar

    };
}


#endif //OP_PI_TIMELINE_H
