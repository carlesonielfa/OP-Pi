#ifndef SOUNDUTILS_H // include guard
#define SOUNDUTILS_H

#include <math.h>
namespace OP_Pi{
    static const double PI = 3.14159265358979323846264338328;

    static double midi_to_freq(unsigned char midi_note){
        return exp2((midi_note - 69)/12.0)*440.0;
    };
    static unsigned char freq_to_midi(double freq){
        return (unsigned char)(69+lrint(12*log2(freq/440.0)));
    };

    // Scale to Frequency conversion

    const int SCALE_DEFAULT = 0;

    static double scale(const int nNoteID, const int nScaleID = SCALE_DEFAULT)
    {
        switch (nScaleID)
        {
        case SCALE_DEFAULT: default:
            return 8 * pow(1.0594630943592952645618252949463, nNoteID);
        }		
    };

    // Converts frequency (Hz) to angular velocity
	static double w(const double dHertz)
	{
		return dHertz * 2.0 * PI;
	};
}

#endif /* SOUNDUTILS_H */