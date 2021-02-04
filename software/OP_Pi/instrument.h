#ifndef INSTRUMENT_H // include guard
#define INSTRUMENT_H
#include <stdio.h>
namespace OP_Pi
{
    class Instrument
    {
        public:
            virtual double processSound(int frame, double seconds_offset, double sample_rate) = 0;
            void setPitch(double new_pitch){
                pitch = new_pitch;
            };
            double getPitch(){
                return pitch;
            };
            void setGain(double new_gain){
                gain = new_gain;
                if(gain>1){
                    fprintf(stderr, "Tried to assign gain bigger than 1");
                    gain = 1;
                }
                else if(gain<0){
                    fprintf(stderr, "Tried to assign gain smaller than 0");
                    gain = 0;  
                }
                                      
            };
            float getGain(){
                return gain;
            };
            
        protected:
            double pitch=220.0;
            float gain=0.5;

    };
}

#endif /* INSTRUMENT_H */