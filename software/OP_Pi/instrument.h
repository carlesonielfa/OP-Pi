#ifndef INSTRUMENT_H // include guard
#define INSTRUMENT_H

#include "sound_utils.h"
#include <stdio.h>
#include <string>
#include <mutex>
#include <algorithm>
#include <vector>
#include "effect.h"
#include "eq.h"
#include "sound_utils.h"
namespace OP_Pi
{
    struct Note
	{
		int index;		// Midi note number
		double on;	// Time note was activated
		double off;	// Time note was deactivated
		bool active;
		unsigned short* rootNote;
		SCALE* scale;
		Note(int index, double on, double off, unsigned short* rootNote, SCALE* scale)
		: index(index), on(on), off(off), rootNote(rootNote), scale(scale){
		    active= true;
		}
		Note(unsigned short* rootNote, SCALE* scale):rootNote(rootNote), scale(scale)
		{
            index = 0;
			on = 0.0;
			off = 0.0;
			active = false;
		}
		int getNumber(){
		    return getNoteInScale(*rootNote,*scale,index);
		}
	};

    //For removing notes that are no longer playing
    typedef bool(*lambda)(Note const& item);
    template<class T>
    void safe_remove(T &v, lambda f)
    {
        auto n = v.begin();
        while (n != v.end())
            if (!f(*n))
                n = v.erase(n);
            else
                ++n;
    }
    class Envelope
	{
        public:
		    virtual double Amplitude(const double time, const double timeOn, const double timeOff) {return 1.0;};
	};
    class EnvelopeADSR : public Envelope
	{
        public:
            double attackTime;
            double decayTime;
            double sustainAmplitude;
            double releaseTime;
            double startAmplitude;

            EnvelopeADSR()
            {
                attackTime = 0.1;
                decayTime = 0.1;
                sustainAmplitude = 1.0;
                releaseTime = 0.2;
                startAmplitude = 1.0;
            }
            EnvelopeADSR(double attackTime, double decayTime, double sustainAmplitude, double releaseTime)
            {
                this->attackTime = attackTime;
                this->decayTime = decayTime;
                this->sustainAmplitude = sustainAmplitude;
                this->releaseTime = releaseTime;
                startAmplitude = 1.0;
            }

            virtual double Amplitude(const double time, const double timeOn, const double timeOff)
            {
                double amp = 0.0;
                double releaseAmplitude = 0.0;
                if (timeOn > timeOff ||  (time >= timeOn && time < timeOff)) // Note is on
                {
                    double lifeTime = time - timeOn;

                    if (lifeTime <= attackTime)
                        amp = (lifeTime / attackTime) * startAmplitude;

                    if (lifeTime > attackTime && lifeTime <= (attackTime + decayTime))
                        amp = ((lifeTime - attackTime) / decayTime) * (sustainAmplitude - startAmplitude) + startAmplitude;

                    if (lifeTime > (attackTime + decayTime))
                        amp = sustainAmplitude;
                }
                else // Note is off
                {
                    double lifeTime = timeOff - timeOn;

                    if (lifeTime <= attackTime)
                        releaseAmplitude = (lifeTime / attackTime) * startAmplitude;

                    if (lifeTime > attackTime && lifeTime <= (attackTime + decayTime))
                        releaseAmplitude = ((lifeTime - attackTime) / decayTime) * (sustainAmplitude - startAmplitude) + startAmplitude;

                    if (lifeTime > (attackTime + decayTime))
                        releaseAmplitude = sustainAmplitude;

                    amp = ((time - timeOff) / releaseTime) * (0.0 - releaseAmplitude) + releaseAmplitude;
                }

                // Amplitude should not be negative
                if (amp <= 0.01)
                    amp = 0.0;

                return amp;
            }
	};
    struct InstrumentDef
	{
		Envelope* env;
		char* name="PRESET";
		virtual float GenerateSound(double time, Note n, bool &noteFinished) = 0;
        ~InstrumentDef(){
            delete env;
        }
        float getEnvelopeAmplitude(double time, Note n) const{
            return  env->Amplitude(time,n.on,n.off);
        }

	};
    // Abstract class that represents an oject that plays sounds
    // It contains an ADSR envelope and basic sound output methods
    class Instrument
    {
        public:
            Instrument(int sampleRate, unsigned short *rootNote, SCALE *scale);
            ~Instrument();
            // Call when key is pressed
            void NoteOn(int noteIndex, double timeOn);

            // Call when key is released
            void NoteOff(int noteIndex, double timeOff);

            //virtual double ProcessSound(int frame, double seconds_offset, double sample_rate) = 0;
            
            void PlayNotes(double time, float *outputs, int nSamples);
            virtual float GenerateNoteSound(double time, Note n, bool &noteFinished)=0;
            void GenerateNoteSounds(double time, float *outputs, int nSamples, Note n, bool &noteFinished);
            char* GetPresetName();
            Envelope* GetEnvelope();
            float lastOutput = 0;
            float gain=0.5;
            char octave=0;
            unsigned short* rootNote;
            SCALE *scale;
            int sampleRate;
        protected:
            void ApplyEffects(float *outputs, int nSamples);
            InstrumentDef* instrumentDef;
            std::vector<Effect*> effects;
        private:
            std::vector<Note> vecNotes;
            std::mutex muxNotes;



    };
}

#endif /* INSTRUMENT_H */