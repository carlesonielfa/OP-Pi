#ifndef SYNTH_H // include guard
#define SYNTH_H

#include "instrument.h"
#include "sound_utils.h"
#include <math.h>
namespace OP_Pi
{
    enum OSC_TYPE{
        SINE, SQUARE, TRIANGLE, SAW, NOISE
    };

    static double Osc(const double time, const double freq, const OSC_TYPE type = OSC_TYPE::SINE,
               const double LFOHertz = 0.0, const double LFOAmplitude = 0.0)
    {

        double dFreq = W(freq) * time + LFOAmplitude * freq * (sin(W(LFOHertz) * time));
        switch (type)
        {
            case OSC_TYPE::SINE: // Sine wave bewteen -1 and +1
                return sin(dFreq);

            case OSC_TYPE::SQUARE: // Square wave between -1 and +1
                return sin(dFreq) > 0 ? 1.0 : -1.0;

            case OSC_TYPE::TRIANGLE: // Triangle wave between -1 and +1
                return asin(sin(dFreq)) * (2.0 / PI);
            case OSC_TYPE::SAW:
                return (2.0 / PI) * (freq * PI * fmod(time, 1.0 / freq) - (PI / 2.0));

            case OSC_TYPE::NOISE:
                return 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;

            default:
                return 0.0;
        }
    };
    struct SynthDefSine: public InstrumentDef{
        SynthDefSine(){
            env = new EnvelopeADSR(0.2,1,0.8,1);
            name = "SINE";
        }
        float GenerateSound(double time,Note n, bool &noteFinished) override{
            //Apply Envelope
            float output = getEnvelopeAmplitude(time, n);

            if (output == 0 && n.off !=0){
                noteFinished = true;
            }
            //Apply oscillator
            output*= Osc(time, midiToFreq(n.getNumber()), OSC_TYPE::SINE);
            return output;
        }
    };
    struct SynthDefBell: public InstrumentDef{
        SynthDefBell(){
            env = new EnvelopeADSR(0.01,1,0,1);
            name = "BELL";
        }
        float GenerateSound(double time, Note n, bool &noteFinished) override{
            //Apply Envelope
            float output = getEnvelopeAmplitude(time, n);
            //If volume is zero and note has been released stop sound
            if (output == 0 && n.off !=0)
                noteFinished = true;
            //Apply oscillator
            output*= Osc(time, midiToFreq(n.getNumber()), OSC_TYPE::SINE)
                     +0.5*Osc(time, midiToFreq(n.getNumber() + 24))
                     +0.25*Osc(time, midiToFreq(n.getNumber() + 36));

            return output*0.5;
        }
    };
    struct SynthDefHarmonica: public InstrumentDef{
        SynthDefHarmonica(){
            env = new EnvelopeADSR(0.1,1,0.95,0.1);
            name = "HARMONICA";
        }
        float GenerateSound(double time, Note n, bool &noteFinished) override{
            double output = getEnvelopeAmplitude(time, n);
            //Apply Envelope

            if (output == 0 && n.off !=0){
                noteFinished = true;
            }
            //Apply oscillator
            output*= Osc(time, midiToFreq(n.getNumber() - 12), OSC_TYPE::SAW)
                     + Osc(time, midiToFreq(n.getNumber()), OSC_TYPE::SQUARE)
                     + 0.5* Osc(time, midiToFreq(n.getNumber() + 12), OSC_TYPE::SQUARE)
                     +0.05* Osc(time, midiToFreq(n.getNumber() + 24), OSC_TYPE::NOISE);
            return output*0.2;
        }
    };
    // Represents an object that synthesizes sound and instrumentOutputs it
    class Synth: public Instrument
    {
    public:
        Synth(double sampleRate, InstrumentDef *instrumentDef, unsigned short *rootNote, SCALE *scale);

        float GenerateNoteSound(double time, Note n, bool &noteFinished) override;

        ~Synth();
        //EnvelopeADSR env;
    };
}

#endif /* SYNTH_H */