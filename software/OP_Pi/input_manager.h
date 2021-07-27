#ifndef INPUTMANAGER_H // include guard
#define INPUTMANAGER_H

#include "instrument.h"
#include <X11/Xlib.h>
#include <wiringPi.h>
#include <mcp23017.h>

namespace OP_Pi
{
    enum ACTION_TYPE
    {   
        NONE,
        QUIT,
        NOTEON,
        NOTEOFF,
        CHANGE_ACTIVE_INSTRUMENT,//TODO: Change for colored encoders
        INCREMENT_OCTAVE,
        CHANGE_VIEW,
        PLAY,
        ENC_SWITCH,
        ENC0_ROTATE,
        ENC1_ROTATE,
        ENC2_ROTATE,
    };
    struct ACTION{
        ACTION_TYPE type = ACTION_TYPE::NONE;
        short value = 0;
    };
    class InputManager
    {
        public:
            virtual ACTION ProcessInput() = 0;
    };

    class InputManagerKeyboard: public InputManager{
    public:
        ACTION ProcessInput() override;
        explicit InputManagerKeyboard(Display *display);
        ~InputManagerKeyboard();
    private:
        //WER TYU IOP
        unsigned short encoderKeyCodes[3][3]={{25,26,27},{28,29,30},{31,32,33}}; //COUNTERCLOCKWISE-SWITCH-CLOCKWISE
        XEvent event;
        Display* display;
    };

    class InputManagerGPIO: public InputManager{
    public:
        ACTION ProcessInput() override;
        explicit InputManagerGPIO();
    private:
        
        unsigned short encoderPins[3][3]={{6,26,19},{4,22,27},{12,21,20}}; //A-SWITCH-B
        unsigned short rotaryStates[3] = {0,0,0};
        short rotaryCounters[3] = {0,0,0};
        unsigned short stateMachineNext[4] = {1,3,0,2};
        unsigned short stateMachinePrev[4] = {2,0,3,1};

        unsigned short mcpBasePin = 64;
        unsigned short keyPadRows[5] = {3, 4, 0, 1, 2};
        unsigned short keyPadCols[5] = {5, 6, 7, 8};
    };
}

#endif /* INPUTMANAGER_H */