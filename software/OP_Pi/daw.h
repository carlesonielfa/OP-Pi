//
// Created by carles on 8/2/21.
//

#ifndef OP_PI_DAW_H
#define OP_PI_DAW_H
#include "instrument.h"
#include <vector>
using namespace std;
namespace OP_Pi{
    enum DAW_VIEW{
        MIXER,
        TIMELINE,
        PATTERN,
        INSTRUMENT,
        EFFECTS
    };
    class Daw{
    public:
        Daw();
        ~Daw();
        //Plays the notes of the active synth
        double PlayActiveSynth(double time, double seconds_offset);
        // Call when key is pressed
        void NoteOn(int noteNumber,double timeOn);
        // Call when key is released
        void NoteOff(int noteNumber,double timeOff);
        unsigned int GetNInstruments();
        bool SetIndexActiveInstrument(int n);
        unsigned int GetIndexActiveInstrument();
        void IncrementOctave(int increment);
        unsigned short bpm;
        float** gains;
        float** outputs;
    private:
        vector<Instrument*> instruments;
        unsigned char activeInstrument;



    };
}
#endif //OP_PI_DAW_H
