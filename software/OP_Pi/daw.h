//
// Created by carles on 8/2/21.
//

#ifndef OP_PI_DAW_H
#define OP_PI_DAW_H
#include "instrument.h"
#include "timeline.h"
#include <vector>
using namespace std;
namespace OP_Pi{
    enum DAW_VIEW{
        MIXER,
        TIMELINE,
        PATTERN,
        INSTRUMENT,
        EFFECTS,
        DAW_VIEW_SIZE_INDICATOR, //Always last
    };
    class Daw{
    public:
        Daw(double sampleRate);
        ~Daw();

        void GenerateAudio(double time, float *outputs, int nSamples);
        // Call when key is pressed
        void NoteOn(int noteIndex, double timeOn);
        // Call when key is released
        void NoteOff(int noteIndex, double timeOff);
        unsigned int getNInstruments();

        bool setIndexActiveInstrument(int n);
        unsigned int getIndexActiveInstrument() const;
        char getOctaveCurrentInstrument();
        char * getActiveInstrumentPresetName();
        Envelope* getInstrumentEnvelope();
        void IncrementOctave(int increment);

        double TimeToBarPosition(double time);      //Converts from seconds to position in bar 0-1
        double BarPositionToTime(double position);  //Converts from position in bar 0-1 to seconds
        double getBeatDuration();                   //Returns beat duration in seconds
        double getBarDuration();                    //Returns bar duration in seconds

        std::vector<Hit> getHitsInActivePattern();

        double sampleRate;
        unsigned short bpm;
        float** instrumentGains;
        float** instrumentOutputs;
        DAW_VIEW activeView = DAW_VIEW::INSTRUMENT;
        float cursor;
        SCALE scale=SCALE::MAJOR;
        unsigned short rootNote = 64;
        double latency = 0;
        bool play=false;
    private:
        vector<Instrument*> instruments;
        vector<Pattern*> patterns;
        unsigned char activeInstrument;
        unsigned char activePattern;

        //Plays the notes of the active synth
        void PlayActiveSynth(double time, float *outputs, int nSamples);
        //Play patter
        void PlayPattern(double time, float *outputs, int nSamples);


    };
}
#endif //OP_PI_DAW_H
