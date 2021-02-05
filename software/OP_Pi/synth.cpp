#include "synth.h"
#include <math.h>
using namespace OP_Pi;

static const double PI = 3.14159265358979323846264338328;
Synth::Synth(){
	SetPitch(0);
}
double Synth::ProcessSound(double time){
    double output = 0.0;
    double w = GetPitch() * 2.0 * PI;
	
	switch (osc_type)
	{
		case OSC_TYPE::SINE: // Sine wave bewteen -1 and +1
			output=sin(w * time);
			break;
		case OSC_TYPE::SQUARE: // Square wave between -1 and +1
			output=sin(w * time) > 0 ? 1.0 : -1.0;
			break;
		case OSC_TYPE::TRIANGLE: // Triangle wave between -1 and +1
			output=asin(sin(w * time)) * (2.0 / PI);
			break;
		case OSC_TYPE::SAW: // Saw wave
		{
			/*
			double dOutput = 0.0;

			for (double n = 1.0; n < 40.0; n++)
				dOutput += (sin(n * w * time)) / n;

			return dOutput * (2.0 / PI);
			*/

			output=(2.0 / PI) * (GetPitch() * PI * fmod(time, 1.0 / GetPitch()) - (PI / 2.0));
			break;
		}
		case OSC_TYPE::NOISE: // Pseudorandom noise
			output= 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;
			break;
	}
	//Apply envelope and time
	output*=GetAmplitudeEnvelope(time)*GetGain();
    return output;
}