#include "input_manager_gpio.h"
#include <cstdio>

using namespace OP_Pi;
using namespace std;

InputManagerGPIO* InputManagerGPIO::inputManagerGPIO = nullptr;


ACTION InputManagerGPIO::ProcessInput() {
    ACTION action;
    //If we had a qeued action from the interrupts return it
    if(lastestAction!=nullptr && lastestAction->type!=ACTION_TYPE::NONE){
        action = *lastestAction;
        lastestAction=nullptr;
        return action;
    }
    //ENCODER SWITCHES
    
    /*for(int i=1;i<3;i++){
        if(digitalRead(encoderPins[i][1])==HIGH)
        {
            action.type = ACTION_TYPE::ENC_SWITCH;
            action.value = i;
            return action;
        }
    }*/
    //BUTTON MATRIX
    ProcessKeyMatrix();
    //Keys release
    if(upKeys!=0){
        for(int i=0; i< 5; i++){
            if(upKeys & 1 << viewsKeys[i]){
                action.type = ACTION_TYPE::CHANGE_VIEW;
                action.value = i;
            }
        }
        for(int i=0; i< 12; i++){
            if(upKeys & 1 << noteKeys[i]){
                action.type = ACTION_TYPE::NOTEOFF;
                action.value = i;
            }
        }
        if(upKeys & 1 << playKey){
            action.type = ACTION_TYPE::PLAY;
        }
        if(upKeys & 1 << octaveUpKey){
            action.type = ACTION_TYPE::INCREMENT_OCTAVE;
            action.value = 1;
        }
        if(upKeys & 1 << octaveDownKey){
            action.type = ACTION_TYPE::INCREMENT_OCTAVE;
            action.value = -1;
        }
    }
    if(downKeys!=0)
    {
        for(int i=0; i< 12; i++){
            if(downKeys & 1 << noteKeys[i]){
                action.type = ACTION_TYPE::NOTEON;
                action.value = i;
            }
        }
    }

    return action;
}
void InputManagerGPIO::ProcessKeyMatrix(){
    currentState = 0;
    for(uint8_t i=0; i<5; i++){
        digitalWrite(mcpBasePin + keyPadRows[i], LOW);
        delayMicroseconds(10);

        for(uint8_t j=0; j<4; j++){
            if(digitalRead(mcpBasePin + keyPadCols[j])==LOW){
                currentState |= 1 << (i*4)+j;
                //printf("keypress - %d\n", (i*4)+j);
            }
        }
        digitalWrite(mcpBasePin + keyPadRows[i], HIGH);
    }
    //DEBOUNCING
    if( lastState == currentState)
    {
        if((millis() - lastTimestamp) >= 10){
            //Detect up down changes
            downKeys = currentState & (lastValidState ^ currentState);
            upKeys = (~currentState)  & (lastValidState ^ currentState);
            lastValidState = currentState;
        }
    }
    else
        lastTimestamp = millis();
    lastState = currentState;

}

void InputManagerGPIO::ProcessEncoder(unsigned short i, ACTION_TYPE primary, ACTION_TYPE secondary){

    unsigned short aState = digitalRead(encoderPins[i][0]);
    unsigned short bState = digitalRead(encoderPins[i][2]);
    unsigned short seq = (aState ^ bState) | bState << 1;
    short delta = (seq - encoderStates[i]) % 4;
    if(delta!=0){
        if(delta < 0)
            delta+=4;
        lastestAction = new ACTION();
        if(digitalRead(encoderPins[i][1])==HIGH)
            lastestAction->type = secondary;
        else
            lastestAction->type = primary;
        if(delta==1){
            lastestAction->value = 1;
            encoderDirections[i] = 0;
        }
        else if(delta==3){
            lastestAction->value = -1;
            encoderDirections[i] = 1;
        }
        else if(encoderDirections[i] == 0)
            lastestAction->value = 1;
        else
            lastestAction->value = -1;
        //printf("Counter %i\n", counter);
        encoderStates[i]=seq;
    }
}

//void encoder0Action(void){InputManagerGPIO::inputManagerGPIO->ProcessEncoder(0, ACTION_TYPE::ENC0_ROTATE);};
void encoder1Action(void){InputManagerGPIO::inputManagerGPIO->ProcessEncoder(1, ACTION_TYPE::ENC0_ROTATE,  ACTION_TYPE::ENC1_ROTATE);};
void encoder2Action(void){InputManagerGPIO::inputManagerGPIO->ProcessEncoder(2, ACTION_TYPE::ENC2_ROTATE, ACTION_TYPE::CHANGE_ACTIVE_INSTRUMENT);};

InputManagerGPIO::InputManagerGPIO() {
    inputManagerGPIO = this;
    lastestAction = nullptr;
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
    wiringPiISR (encoderPins[1][0], INT_EDGE_BOTH, &encoder1Action);
    wiringPiISR (encoderPins[1][2], INT_EDGE_BOTH, &encoder1Action);
    wiringPiISR (encoderPins[2][0], INT_EDGE_BOTH, &encoder2Action);
    wiringPiISR (encoderPins[2][2], INT_EDGE_BOTH, &encoder2Action);

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