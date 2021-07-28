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
    
    for(int i=1;i<2;i++){
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
    int newState = (1-digitalRead(encoderPins[i][0]))*2 + 1 - digitalRead(encoderPins[i][2]);
    //printf("%i \n",newState);
    //printf("%i \n",digitalRead(encoderPins[i][2]));
    if(newState == stateMachineNext[encoderStates[i]])
        encoderDirections[i]=1;
        if(newState==0){
            action.type = ACTION_TYPE::ENC0_ROTATE;
            action.value = (i+1) * (2 *encoderDirections[i]-1);
        }

    
    else if(newState == stateMachinePrev[encoderStates[i]])
        encoderDirections[i]=0;
        if(newState==0){
            action.type = ACTION_TYPE::ENC0_ROTATE;
            action.value = (i+1) * (2*encoderDirections[i]-1);
        }

    encoderStates[i] = newState;
    return action;
} 
void InputManagerGPIO::TransitionOcurred(){
    bool aState = 0;//digitalRead(encoderPins[1][0]);
    bool bState = 0;//digitalRead(encoderPins[1][2]);
    unsigned short seq = (aState ^ bState) | bState << 1;
    printf("%i \n", seq);
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
        if(wiringPiISR(encoderPins[i][0], INT_EDGE_BOTH, &TransitionOcurred)<0){
            printf("Error setting encoder interrupt\n");
        }

        pullUpDnControl(encoderPins[i][1], PUD_DOWN);

        pullUpDnControl(encoderPins[i][2], PUD_UP);
        if(wiringPiISR(encoderPins[i][2], INT_EDGE_BOTH, &TransitionOcurred)<0){
            printf("Error setting encoder interrupt\n");
        }
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