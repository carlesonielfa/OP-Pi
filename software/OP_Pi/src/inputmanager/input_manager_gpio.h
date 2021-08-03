#ifndef INPUTMANAGERGPIO_H // include guard
#define INPUTMANAGERGPIO_H

#include "input_manager.h"
#include <wiringPi.h>
#include <mcp23017.h>
#include <cstdint>
namespace OP_Pi
{
    typedef unsigned int KeyState;
    class InputManagerGPIO: public InputManager{
    public:
        ACTION ProcessInput() override;
        explicit InputManagerGPIO();
        static InputManagerGPIO* inputManagerGPIO;
        ACTION* lastestAction;
        void ProcessEncoder(unsigned short i, ACTION_TYPE type);
        void ProcessKeyMatrix();
        KeyState upKeys = 0;
        KeyState downKeys = 0;
    private:
        //Key matrix variables
        KeyState currentState=0;
        KeyState lastState=0;
        KeyState lastValidState=0;
        unsigned int lastTimestamp=0;

        //Key number for blue buttons (change active view)
        const uint8_t viewsKeys [5] = {11, 15, 19, 3, 7};
        const uint8_t noteKeys [12] = {0, 9, 4, 13, 8, 12, 17, 16, 2, 1, 6, 5};
        const uint8_t playKey = 10;
        const uint8_t octaveUpKey = 14;
        const uint8_t octaveDownKey = 18;

        unsigned short encoderPins[3][3]={{6,26,5},{4,22,27},{12,21,20}}; //A-SWITCH-B    
        unsigned short encoderStates[3] = {2,2,2};
        bool encoderDirections[3]={0,0,0}; //0 CW 1 CCW

        unsigned short mcpBasePin = 64;
        unsigned short keyPadRows[5] = {3, 4, 0, 1, 2};
        unsigned short keyPadCols[5] = {5, 6, 7, 8};
    };
}

#endif /* INPUTMANAGER_H */