#ifndef INPUTMANAGER_H // include guard
#define INPUTMANAGER_H

#include "instrument.h"

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
        int value = 0;
    };
    class InputManager
    {
        public:
            bool useKeyboard=true;
            ACTION processInput();
    };
}

#endif /* INPUTMANAGER_H */