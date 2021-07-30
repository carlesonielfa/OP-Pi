#ifndef INPUTMANAGER_KEYBOARD_H // include guard
#define INPUTMANAGER_KEYBOARD_H

#include <X11/Xlib.h>
#include "input_manager.h"

namespace OP_Pi
{
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