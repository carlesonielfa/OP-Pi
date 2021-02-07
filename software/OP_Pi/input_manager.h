#ifndef INPUTMANAGER_H // include guard
#define INPUTMANAGER_H

#include "instrument.h"
#include <X11/Xlib.h>
namespace OP_Pi
{
    enum ACTION_TYPE
    {   
        NONE = 0, 
        QUIT = 1, 
        NOTEON = 2,
        NOTEOFF = 3,
    };
    struct ACTION{
        ACTION_TYPE type = ACTION_TYPE::NONE;
        unsigned char value = 0;
    };
    class InputManager
    {
        public:
            virtual ACTION ProcessInput() = 0;
    };

    class InputManagerKeyboard: public InputManager{
    public:
        ACTION ProcessInput() override;
        InputManagerKeyboard(Display* display);
    private:
        XEvent event;
        Display* display;
    };
}

#endif /* INPUTMANAGER_H */