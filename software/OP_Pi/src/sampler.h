#ifndef SAMPLER_H // include guard
#define SAMPLER_H

#include "instrument.h"
#include <sndfile.h>

namespace OP_Pi{

    struct Sample: public InstrumentDef{
        int totalFrames;     /* Used to be called samples. */
        int samplerate;
        int channels;
        float* data;
        Sample(char* filename){
            SF_INFO sfInfo;
            SNDFILE* sFile;
            name = "SAMPLE ERROR";
            if((sFile = sf_open(filename, SFM_READ, &sfInfo))==NULL)
                printf("Error opening sample\n");
            channels = sfInfo.channels;
            samplerate = sfInfo.samplerate;
            totalFrames = sfInfo.frames;
            data = new float[channels * totalFrames];
            int readCount = sf_readf_float(sFile, data, totalFrames);
            if(readCount!=totalFrames)
                printf("Error reading sample\n");
            else{
                printf("Loaded sample %s\n", filename);
                name = filename;
            }
            //printf("--------%d\n", 0.1/samplerate);

            sf_close(sFile);
            
            //delete sFile;
            env = new Envelope();
        }
        ~Sample(){
            delete data;
        }
        float GenerateSound(double time, Note n, bool &noteFinished){
            float output = getEnvelopeAmplitude(time, n);

            if (output == 0 && n.off !=0){
                noteFinished = true;
            }
            int sample = (time-n.on)*samplerate;
            //Change to stereo???
            if(sample < totalFrames){
                output*=data[2*sample];
                return output;
            }
            return 0;
            

        }
    };
    class Sampler: public Instrument
    {
    public:
        Sampler(double sampleRate, Sample *sample, unsigned short *rootNote, SCALE *scale);

        float GenerateNoteSound(double time, Note n, bool &noteFinished) override;

        ~Sampler();
        //EnvelopeADSR env;
    };
}

#endif /* SAMPLER_H */
    