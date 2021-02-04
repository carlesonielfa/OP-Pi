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
            InputManager();
            bool useKeyboard=true;
            ACTION ProcessInput();
        private:
            Display* display;
            bool GetKeyState(KeySym keySym);
            int nCurrentKey = -1;	
    };
}

#endif /* INPUTMANAGER_H */