#ifndef EFFECT_H // include guard
#define EFFECT_H

namespace OP_Pi
{
    class Effect 
    {

    public:
        Effect(int sampleRate);
        virtual void ApplyEffect(float *outputs, int nSamples) =0;
        float wet=0.5;
    protected:
        int sampleRate;
    };

    class Delay: public Effect{

    };
    class Distortion: public Effect{

    };
}

#endif /* EFFECT_H */