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
        CHANGE_ACTIVE_INSTRUMENT,
        INCREMENT_OCTAVE,
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
        InputManagerKeyboard(Display *display);
        ~InputManagerKeyboard();
    private:
        XEvent event;
        Display* display;
    };
}

#endif /* INPUTMANAGER_H */