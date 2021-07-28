#include "input_manager_gpio.h"
#include <cstdio>

using namespace OP_Pi;
using namespace std;

ACTION InputManagerGPIO::ProcessInput() {
    ACTION action;

    //ENCODER SWITCHES
    
    for(int i=0;i<3;i++){
        if(digitalRead(encoderPins[i][1])==HIGH)
        {
            action.type = ACTION_TYPE::ENC_SWITCH;
            action.value = i;
            return action;
        }
    }
    
    for(int i=0;i<3;i++){
        ProcessEncoder(i);
    }

    //BUTTON MATRIX
    for(int i=0; i<5; i++){
        digitalWrite(mcpBasePin + keyPadRows[i], LOW);
        for(int j=0; j<4; j++){
            if(digitalRead(mcpBasePin + keyPadCols[j])==LOW){
                action.type = ACTION_TYPE::ENC_SWITCH;
                action.value = i*4 + j;
                digitalWrite(mcpBasePin + keyPadRows[i], HIGH);
                return action;
            }
        }
        digitalWrite(mcpBasePin + keyPadRows[i], HIGH);
    }

    return action;
}

ACTION InputManagerGPIO::ProcessEncoder(unsigned short i){
    ACTION action;
    unsigned short aState = digitalRead(encoderPins[i][0]);
    unsigned short bState = digitalRead(encoderPins[i][2]);
    unsigned short seq = (aState ^ bState) | bState << 1;
    if(seq != encoderStates[i]){
        short delta = (seq - encoderStates[i]) % 4;
        if(delta < 0)
            delta+=4;

        if(delta==1){
            counter++;
            encoderDirections[i] = 0;
        }
        else if(delta==3){
            counter--;
            encoderDirections[i] = 1;
        }
        else if(encoderDirections[i] == 0)
            counter++;
        else
            counter--;

        encoderStates[i]=seq;
    }

    return action;
}
InputManagerGPIO::InputManagerGPIO() {

    printf("Setting up GPIO. . .\n");
    if(wiringPiSetupGpio() < 0){
        printf("Error setting up GPIO\n");
    }
    
    //Setup encoder switches
    for(int i=0;i<3;i++){
        //Set A SWITCH and B as inputs
        for(int j=0; j<3; j++){
            pinMode(encoderPins[i][j], INPUT);
        }
        //Enable pulldown/pullup and interrupts
        pullUpDnControl(encoderPins[i][0], PUD_UP);
        pullUpDnControl(encoderPins[i][1], PUD_DOWN);
        pullUpDnControl(encoderPins[i][2], PUD_UP);

    }

    //Setup button matrix
    if(mcp23017Setup(mcpBasePin, 0x20) < 0){
        printf("Error setting up buttons\n");
    }
    for(int i=0; i<5; i++){
        pinMode(mcpBasePin + keyPadRows[i], OUTPUT);
        digitalWrite(mcpBasePin + keyPadRows[i], HIGH);
    }
    for(int i=0; i<4; i++){
        pinMode(mcpBasePin + keyPadCols[i], INPUT);
    }
    printf("GPIO setup done!\n");
}