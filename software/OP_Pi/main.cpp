#include "input_manager_gpio.h"
#include "input_manager.h"
#include "screen_manager.h"
#include "daw.h"
#include <soundio/soundio.h>
#include <sndfile.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <signal.h>
using namespace OP_Pi;
/*
 * TODO:Task list
 * - SEQUENCER
 * - RECORD
 * - QUANTIZE
 * - RENDER
 * - TIMELINE ADD PATTERNS
 * - MODIFY INSTRUMENTS
 * - SAMPLE LOADING AND PLAYING
 * - EFFECTS
 */
static int usage(char *exe) {
    fprintf(stderr, "Usage: %s [options]\n"
            "Options:\n"
            "  [--backend dummy|alsa|pulseaudio|jack|coreaudio|wasapi]\n"
            "  [--device id]\n"
            "  [--raw]\n"
            "  [--name stream_name]\n"
            "  [--latency seconds]\n"
            "  [--sample-rate hz]\n"
            , exe);
    return 1;
}

static void write_sample_s16ne(char *ptr, double sample) {
    int16_t *buf = (int16_t *)ptr;
    double range = (double)INT16_MAX - (double)INT16_MIN;
    double val = sample * range / 2.0;
    *buf = val;
}

static void write_sample_s32ne(char *ptr, double sample) {
    int32_t *buf = (int32_t *)ptr;
    double range = (double)INT32_MAX - (double)INT32_MIN;
    double val = sample * range / 2.0;
    *buf = val;
}

static void write_sample_float32ne(char *ptr, double sample) {
    float *buf = (float *)ptr;
    *buf = sample;
}

static void write_sample_float64ne(char *ptr, double sample) {
    double *buf = (double *)ptr;
    *buf = sample;
}
static void (*write_sample)(char *ptr, double sample);

static Daw* daw;
static double seconds_offset = 0.0;
static void write_callback(struct SoundIoOutStream *outstream, int frame_count_min, int frame_count_max) {
    int sample_rate = outstream->sample_rate;
    struct SoundIoChannelArea *areas;
    int err;

    int frames_left = frame_count_max;

    for (;;) {
        int frame_count = frames_left;
        if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count))) {
            fprintf(stderr, "unrecoverable stream error: %s\n", soundio_strerror(err));
            exit(1);
        }

        if (!frame_count)
            break;

        const struct SoundIoChannelLayout *layout = &outstream->layout;

        float *outputs = new float[frame_count];

        if(daw!= nullptr)
            daw->GenerateAudio(seconds_offset, outputs, frame_count);

        for (int channel = 0; channel < layout->channel_count; channel += 1) {
            for(int i=0;i<frame_count;i++) {
                write_sample(areas[channel].ptr, outputs[i]);
                areas[channel].ptr += areas[channel].step;
            }

        }

        //seconds_offset = fmod(seconds_offset + 1.0/sample_rate * frame_count, 1.0);
        seconds_offset = seconds_offset + 1.0/sample_rate * frame_count;
        if ((err = soundio_outstream_end_write(outstream))) {
            if (err == SoundIoErrorUnderflow)
                return;
            fprintf(stderr, "unrecoverable stream error: %s\n", soundio_strerror(err));
            exit(1);
        }

        frames_left -= frame_count;
        if (frames_left <= 0)
            break;
    }
}

static void underflow_callback(struct SoundIoOutStream *outstream) {
    static int count = 0;
    fprintf(stderr, "underflow %d\n", count++);
}

//Handles ^C exit
bool quit = false;
void handler(int) {
    printf("Exiting...\n");
    quit = true;
}

int main(int argc, char **argv) {
    char *exe = argv[0];
    enum SoundIoBackend backend = SoundIoBackendNone;
    char *device_id = nullptr;
    bool raw = false;
    char *stream_name = nullptr;
    double latency = 0.0;
    int sample_rate = 48000;
    daw = new Daw(sample_rate);
    daw->bpm = 100;
    signal(SIGINT, &handler);
    InputManagerGPIO inputManager;
    ScreenManagerOLED screenManager(daw);

    for (int i = 1; i < argc; i += 1) {
        char *arg = argv[i];
        if (arg[0] == '-' && arg[1] == '-') {
            if (strcmp(arg, "--raw") == 0) {
                raw = true;
            } else {
                i += 1;
                if (i >= argc) {
                    return usage(exe);
                } else if (strcmp(arg, "--backend") == 0) {
                    if (strcmp(argv[i], "dummy") == 0) {
                        backend = SoundIoBackendDummy;
                    } else if (strcmp(argv[i], "alsa") == 0) {
                        backend = SoundIoBackendAlsa;
                    } else if (strcmp(argv[i], "pulseaudio") == 0) {
                        backend = SoundIoBackendPulseAudio;
                    } else if (strcmp(argv[i], "jack") == 0) {
                        backend = SoundIoBackendJack;
                    } else if (strcmp(argv[i], "coreaudio") == 0) {
                        backend = SoundIoBackendCoreAudio;
                    } else if (strcmp(argv[i], "wasapi") == 0) {
                        backend = SoundIoBackendWasapi;
                    } else {
                        fprintf(stderr, "Invalid backend: %s\n", argv[i]);
                        return 1;
                    }
                } else if (strcmp(arg, "--device") == 0) {
                    device_id = argv[i];
                } else if (strcmp(arg, "--name") == 0) {
                    stream_name = argv[i];
                } else if (strcmp(arg, "--latency") == 0) {
                    latency = atof(argv[i]);
                } else if (strcmp(arg, "--sample-rate") == 0) {
                    sample_rate = atoi(argv[i]);
                } else {
                    return usage(exe);
                }
            }
        } else {
            return usage(exe);
        }
    }

    struct SoundIo *soundio = soundio_create();
    if (!soundio) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    int err = (backend == SoundIoBackendNone) ?
        soundio_connect(soundio) : soundio_connect_backend(soundio, backend);

    if (err) {
        fprintf(stderr, "Unable to connect to backend: %s\n", soundio_strerror(err));
        return 1;
    }

    fprintf(stderr, "Backend: %s\n", soundio_backend_name(soundio->current_backend));

    soundio_flush_events(soundio);

    int selected_device_index = -1;
    if (device_id) {
        int device_count = soundio_output_device_count(soundio);
        for (int i = 0; i < device_count; i += 1) {
            struct SoundIoDevice *device = soundio_get_output_device(soundio, i);
            bool select_this_one = strcmp(device->id, device_id) == 0 && device->is_raw == raw;
            soundio_device_unref(device);
            if (select_this_one) {
                selected_device_index = i;
                break;
            }
        }
    } else {
        selected_device_index = soundio_default_output_device_index(soundio);
    }

    if (selected_device_index < 0) {
        fprintf(stderr, "Output device not found\n");
        return 1;
    }

    struct SoundIoDevice *device = soundio_get_output_device(soundio, selected_device_index);
    if (!device) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    fprintf(stderr, "Output device: %s\n", device->name);

    if (device->probe_error) {
        fprintf(stderr, "Cannot probe device: %s\n", soundio_strerror(device->probe_error));
        return 1;
    }

    struct SoundIoOutStream *outstream = soundio_outstream_create(device);
    if (!outstream) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    outstream->write_callback = write_callback;
    outstream->underflow_callback = underflow_callback;
    outstream->name = stream_name;
    outstream->software_latency = latency;
    outstream->sample_rate = sample_rate;

    if (soundio_device_supports_format(device, SoundIoFormatFloat32NE)) {
        outstream->format = SoundIoFormatFloat32NE;
        write_sample = write_sample_float32ne;
    } else if (soundio_device_supports_format(device, SoundIoFormatFloat64NE)) {
        outstream->format = SoundIoFormatFloat64NE;
        write_sample = write_sample_float64ne;
    } else if (soundio_device_supports_format(device, SoundIoFormatS32NE)) {
        outstream->format = SoundIoFormatS32NE;
        write_sample = write_sample_s32ne;
    } else if (soundio_device_supports_format(device, SoundIoFormatS16NE)) {
        outstream->format = SoundIoFormatS16NE;
        write_sample = write_sample_s16ne;
    } else {
        fprintf(stderr, "No suitable device format available.\n");
        return 1;
    }

    if ((err = soundio_outstream_open(outstream))) {
        fprintf(stderr, "unable to open device: %s", soundio_strerror(err));
        return 1;
    }

    fprintf(stderr, "Software latency: %f\n", outstream->software_latency);
    fprintf(stderr, "'q\\n' - quit\n");

    if (outstream->layout_error)
        fprintf(stderr, "unable to set channel layout: %s\n", soundio_strerror(outstream->layout_error));

    if ((err = soundio_outstream_start(outstream))) {
        fprintf(stderr, "unable to start device: %s\n", soundio_strerror(err));
        return 1;
    }

    daw->latency = outstream->software_latency;

    while(!quit) {
        soundio_flush_events(soundio);
        //Check input
        ACTION action = inputManager.ProcessInput();
        switch(action.type){
            case ACTION_TYPE::QUIT:
                printf("QUIT\n");
                quit=true;
                break;
            case ACTION_TYPE::NOTEON:
                daw->NoteOn(action.value, seconds_offset);
                printf("NOTE ON: %d\n",action.value);
                break;
            case ACTION_TYPE::NOTEOFF:
                daw->NoteOff(action.value, seconds_offset);
                printf("NOTE OFF: %d\n",action.value);
                break;
            case ACTION_TYPE::NONE:
                break;
            case ACTION_TYPE::CHANGE_ACTIVE_INSTRUMENT:
                daw->incrementActiveInstrument(action.value);
                printf("NEW ACTIVE INSTRUMENT: %s\n",daw->getActiveInstrumentPresetName());
                /*
                if(!daw->setIndexActiveInstrument(action.value)){
                    fprintf(stderr, "Error when selecting instrument: instrument %d not initialized\n", action.value);
                }else{
                    printf("NEW ACTIVE INSTRUMENT: %d\n",action.value);
                }*/

                break;
            case ACTION_TYPE::INCREMENT_OCTAVE:
                daw->IncrementOctave(action.value);
                printf("OCTAVE INCREMENTED: %i\n", action.value);
                break;
            case ACTION_TYPE::CHANGE_VIEW:
                if(action.value ==-1)
                    daw->ChangeActiveView();
                else
                    daw->ChangeActiveView(static_cast<DAW_VIEW>(action.value));
                printf("ACTIVE VIEW CHANGED TO: %i\n", daw->activeView);
                break;
            case ACTION_TYPE::PLAY:
                daw->TogglePlay();
                printf("PLAY TOGGLE\n");
                break;
            case ACTION_TYPE::ENC_SWITCH:
                daw->EncoderPressed(action.value);
                printf("ENCODER %i SWITCH PRESSED\n", action.value);
                break;
            case ACTION_TYPE::ENC0_ROTATE:
                daw->EncoderRotation(0,action.value);
                printf("ENCODER 0 ROTATION: %i\n", action.value);
                break;
            case ACTION_TYPE::ENC1_ROTATE:
                daw->EncoderRotation(1,action.value);
                printf("ENCODER 1 ROTATION: %i\n", action.value);
                break;
            case ACTION_TYPE::ENC2_ROTATE:
                daw->EncoderRotation(2,action.value);
                printf("ENCODER 2 ROTATION: %i\n", action.value);
                break;
            default:
                printf("Action not yet implemented %i\n", action.type);
                break;
        }
        //usleep(1000000/60);
        //Redraw scren
        screenManager.Draw();

    }

    soundio_outstream_destroy(outstream);
    soundio_device_unref(device);
    soundio_destroy(soundio);
    return 0;
}