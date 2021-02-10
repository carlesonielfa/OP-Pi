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
        EFFECTS,
        ENUM_SIZE_INDICATOR, //Always last
    };
    class Daw{
    public:
        Daw(double sampleRate);
        ~Daw();
        //Plays the notes of the active synth
        void PlayActiveSynth(double time, float *outputs, int nSamples);
        // Call when key is pressed
        void NoteOn(int noteNumber,double timeOn);
        // Call when key is released
        void NoteOff(int noteNumber,double timeOff);
        unsigned int GetNInstruments();
        bool SetIndexActiveInstrument(int n);
        unsigned int GetIndexActiveInstrument();
        char GetOctaveCurrentInstrument();
        char * GetActiveInstrumentPresetName();
        Envelope* GetInstrumentEnvelope();
        void IncrementOctave(int increment);

        double sampleRate;
        unsigned short bpm;
        float** gains;
        float** outputs;
        DAW_VIEW activeView = DAW_VIEW::INSTRUMENT;
        float cursor;

    private:
        vector<Instrument*> instruments;
        unsigned char activeInstrument;
        unsigned char activePattern;



    };
}
#endif //OP_PI_DAW_H
