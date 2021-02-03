#include "synth.h"
#include <iostream>
#include <math.h>
using namespace OP_Pi;

static const double PI = 3.14159265358979323846264338328;

double Synth::processSound(int frame, double seconds_offset, double sample_rate){
    double radians_per_second = pitch * 2.0 * PI;
    
    return sin((seconds_offset + frame * 1.0/sample_rate) * radians_per_second);
}