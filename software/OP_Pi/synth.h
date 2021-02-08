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

        double dFreq = w(freq) * time + LFOAmplitude * freq * (sin(w(LFOHertz) * time));
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
        }
        double GenerateSound(const double time,double seconds_offset, Note n, bool &noteFinished) override{
            double output = env->Amplitude(seconds_offset,n.on,n.off);
            //Apply Envelope

            if (output == 0 && n.off !=0){
                noteFinished = true;
            }
            //Apply oscillator
            output*= Osc(time, midi_to_freq(n.number), OSC_TYPE::SINE);
            return output;
        }
    };
    struct SynthDefBell: public InstrumentDef{
        SynthDefBell(){
            env = new EnvelopeADSR(0.01,1,0,1);
        }
        double GenerateSound(const double time,double seconds_offset, Note n, bool &noteFinished) override{
            double output = env->Amplitude(seconds_offset,n.on,n.off);
            //Apply Envelope

            if (output == 0 && n.off !=0){
                noteFinished = true;
            }
            //Apply oscillator
            output*= Osc(time, midi_to_freq(n.number), OSC_TYPE::SINE)
                    +0.5*Osc(time, midi_to_freq(n.number+24))
                    +0.25*Osc(time, midi_to_freq(n.number+36));
            return output*0.5;
        }
    };
    struct SynthDefHarmonica: public InstrumentDef{
        SynthDefHarmonica(){
            env = new EnvelopeADSR(0.1,1,0.95,0.1);
        }
        double GenerateSound(const double time,double seconds_offset, Note n, bool &noteFinished) override{
            double output = env->Amplitude(seconds_offset,n.on,n.off);
            //Apply Envelope

            if (output == 0 && n.off !=0){
                noteFinished = true;
            }
            //Apply oscillator
            output*= Osc(time, midi_to_freq(n.number-12), OSC_TYPE::SAW)
                     + Osc(time, midi_to_freq(n.number),OSC_TYPE::SQUARE)
                     + 0.5* Osc(time, midi_to_freq(n.number+12),OSC_TYPE::SQUARE)
                     +0.05* Osc(time, midi_to_freq(n.number+24),OSC_TYPE::NOISE);
            return output*0.2;
        }
    };
    // Represents an object that synthesizes sound and outputs it
    class Synth: public Instrument
    {
    public:
        //SynthDef synth;
        Synth(InstrumentDef* instrumentDef);
        ~Synth();
        //EnvelopeADSR env;
    private:
        double GenerateNoteSound(double time, double seconds_offset, Note n, bool& noteFinished) override;
    };
}

#endif /* SYNTH_H */