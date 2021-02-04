#include "synth.h"
#include <math.h>
using namespace OP_Pi;

static const double PI = 3.14159265358979323846264338328;

double Synth::ProcessSound(int frame, double seconds_offset, double sample_rate){
    double output = 0.0;
    double dTime = seconds_offset + frame * 1.0/sample_rate;
    double w = pitch * 2.0 * PI;
    switch (osc_type)
	{
	case OSC_TYPE::SINE: // Sine wave bewteen -1 and +1
		return sin(w * dTime);

	case OSC_TYPE::SQUARE: // Square wave between -1 and +1
		return sin(w * dTime) > 0 ? 1.0 : -1.0;

	case OSC_TYPE::TRIANGLE: // Triangle wave between -1 and +1
		return asin(sin(w * dTime)) * (2.0 / PI);

	case OSC_TYPE::SAW: // Saw wave
	{
		/*
        double dOutput = 0.0;

		for (double n = 1.0; n < 40.0; n++)
			dOutput += (sin(n * w(pitch) * dTime)) / n;

		return dOutput * (2.0 / PI);
        */

        return (2.0 / PI) * (pitch * PI * fmod(dTime, 1.0 / pitch) - (PI / 2.0));
	}
	case OSC_TYPE::NOISE: // Pseudorandom noise
		return 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;
	}
    //double radians_per_second = pitch * 2.0 * PI;
    //return gain * sin((seconds_offset + frame * 1.0/sample_rate) * radians_per_second);
    return output*gain;
}