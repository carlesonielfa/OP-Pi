#ifndef EFFECT_H // include guard
#define EFFECT_H

namespace OP_Pi
{
    class Effect 
    {
        public:
            virtual double applyEffect(double source)=0;
            float wet=1.0;
    };
    class EQ: public Effect{

    };
    class Reverb:public Effect{

    };
    class Delay: public Effect{

    };
    class Distortion: public Effect{

    };
}

#endif /* EFFECT_H */