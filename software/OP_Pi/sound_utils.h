#include <math.h>
static double midi_to_freq(unsigned char midi_note){
    return exp2((midi_note - 69)/12.0)*440.0;
}
static unsigned char freq_to_midi(double freq){
    return (unsigned char)(69+lrint(12*log2(freq/440.0)));
}