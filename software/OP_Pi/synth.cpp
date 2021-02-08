#include "synth.h"
using namespace OP_Pi;

double Osc(const double time, const double freq, const OSC_TYPE type = OSC_TYPE::SINE,
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

Synth::Synth(){
	env = EnvelopeADSR(0.2,1,0.8,1);
}

double Synth::GenerateNoteSound(double time, double seconds_offset, Note n, bool& noteFinished){

    double output;

	//Apply Envelope
	output = env.Amplitude(seconds_offset,n.on,n.off);
	if (output == 0 && n.off !=0){
		noteFinished = true;
	}
	//Apply oscillator
	output*= Osc(time, midi_to_freq(n.number), OSC_TYPE::SINE);
	
	//Apply gain
	output*=gain;
    return output;
}
