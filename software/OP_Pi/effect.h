#ifndef EFFECT_H // include guard
#define EFFECT_H

namespace OP_Pi
{
    class Effect 
    {

    public:
        Effect(int sampleRate);
        virtual void ApplyEffect(float *outputs, int nSamples) =0;
        float wet=1.0;
    protected:
        int sampleRate;
    };

    class Reverb:public Effect{

    };
    class Delay: public Effect{

    };
    class Distortion: public Effect{

    };
}

#endif /* EFFECT_H */