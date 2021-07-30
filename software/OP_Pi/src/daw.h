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
        void NoteOff(int noteIndex, double timeOff) const;
        unsigned int getNInstruments();

        bool setIndexActiveInstrument(int n);
        unsigned int getIndexActiveInstrument() const;
        Instrument* getActiveInstrument() const;
        char getOctaveCurrentInstrument() const;
        void IncrementOctave(int increment) const;
        char * getActiveInstrumentPresetName() const;
        Envelope* getInstrumentEnvelope() const;

        double TimeToBarPosition(double time) const;      //Converts from seconds to position in bar 0-1
        double BarPositionToTime(double position) const;  //Converts from position in bar 0-1 to seconds
        double getBeatDuration() const;                   //Returns beat duration in seconds
        double getBarDuration() const;                    //Returns bar duration in seconds

        void ChangeScale(int rootNote, SCALE scale);

        std::vector<Hit> getHitsInActivePattern();
        unsigned char getIndexActivePattern() const;

        void ChangeActiveView(DAW_VIEW newView);
        void ChangeActiveView();

        void EncoderRotation(unsigned char encoder, char value);
        void EncoderPressed(unsigned char encoder);
        void TogglePlay();

        double sampleRate;
        unsigned short bpm;
        float** instrumentGains;
        float** instrumentOutputs;
        DAW_VIEW activeView = DAW_VIEW::MIXER;
        float cursor;



        double latency = 0;
        bool play=false;
        string noteNames [7];
    private:
        SCALE scale;
        unsigned short rootNote;
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
