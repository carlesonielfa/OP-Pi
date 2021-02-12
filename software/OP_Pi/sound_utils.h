#ifndef SOUNDUTILS_H // include guard
#define SOUNDUTILS_H

#include <math.h>
namespace OP_Pi{
    static const double PI = 3.14159265358979323846264338328;

    static double midiToFreq(unsigned char midi_note){
        return exp2((midi_note - 69)/12.0)*440.0;
    };
    static unsigned char freqToMidi(double freq){
        return (unsigned char)(69+lrint(12*log2(freq/440.0)));
    };

    enum SCALE{
        MAJOR,
        MINOR,
        MELODIC_MINOR,
        MELODIC_MAJOR,
        SCALE_SIZE_INDICATOR, //Always last
    };
    static unsigned char scales [SCALE::SCALE_SIZE_INDICATOR][7]={
        {0, 2, 4, 5, 7, 9, 11},
        {0, 2, 3, 5, 7, 8, 10},
    };
    static int getNoteInScale(int root, SCALE scale,int index){
        char octave = index/7;
        index = fmod(index,7);
        if(index<0) {
            index = 7 + index;
            octave-=1;
        }

        return 12*octave+root+scales[scale][index];
    }
    /*static int getIndexInScale(int root, SCALE scale, int midiNote){

        for(int i=0; i<7; i++){
            if(root+scales[scale][i] == midiNote)
                return i;
        }
    }*/
    // Converts frequency (Hz) to angular velocity
	static double W(const double dHertz)
	{
		return dHertz * 2.0 * PI;
	};
}

#endif /* SOUNDUTILS_H */