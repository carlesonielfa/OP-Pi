#ifndef INPUTMANAGERGPIO_H // include guard
#define INPUTMANAGERGPIO_H

#include "input_manager.h"
#include <wiringPi.h>
#include <mcp23017.h>

namespace OP_Pi
{
    
    class InputManagerGPIO: public InputManager{
    public:
        ACTION ProcessInput() override;
        explicit InputManagerGPIO();
    private:
        int counter = 0;
        ACTION ProcessEncoder(unsigned short i);


        unsigned short encoderPins[3][3]={{6,26,5},{4,22,27},{12,21,20}}; //A-SWITCH-B    
        unsigned short encoderStates[3] = {2,2,2};
        bool encoderDirections[3]={0,0,0}; //0 CW 1 CCW

        unsigned short mcpBasePin = 64;
        unsigned short keyPadRows[5] = {3, 4, 0, 1, 2};
        unsigned short keyPadCols[5] = {5, 6, 7, 8};
    };
}

#endif /* INPUTMANAGER_H */