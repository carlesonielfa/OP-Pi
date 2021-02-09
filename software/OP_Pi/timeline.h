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
        Note n;
        float noteStart;
        float noteLength;
    };
    class Pattern {
        int patternNumber;
        std::vector<Hit> hits;
        float patternStart;
        float patternLength;
    };
}


#endif //OP_PI_TIMELINE_H
