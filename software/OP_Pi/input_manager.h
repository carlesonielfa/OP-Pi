#ifndef INPUTMANAGER_H // include guard
#define INPUTMANAGER_H

#include "instrument.h"
#include <X11/Xlib.h>
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
}

#endif /* INPUTMANAGER_H */