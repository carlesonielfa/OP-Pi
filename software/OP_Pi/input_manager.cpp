#include "input_manager.h"
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
        int currentState = (1-digitalRead(encoderPins[i][0]))*2 + 1 - digitalRead(encoderPins[i][2]);
        if(currentState == stateMachineNext[rotaryStates[i]])
            rotaryCounters[i]-=1;
        
        else if(currentState == stateMachinePrev[rotaryStates[i]])
            rotaryCounters[i]+=1;

        rotaryStates[i] = currentState;
        if(rotaryCounters[i]>=3 || rotaryCounters[i]<=-3){
            action.type = ACTION_TYPE::ENC0_ROTATE;
            action.value = (i+1) * rotaryCounters[i]/3;
            rotaryCounters[i] = 0;
        }
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

InputManagerGPIO::InputManagerGPIO() {
    // Display a keyboard

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
        //Enable pulldown/pullup
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


ACTION InputManagerKeyboard::ProcessInput() {
    ACTION action;
    if(XPending(display)>0) {
        XNextEvent(display, &event);
        for (int k = 0; k < 7; k++) {
            int keyCode = XKeysymToKeycode(display, "ZXCVBNM"[k]);
            if (event.xkey.keycode == keyCode) {
                action.value = k;
                if (event.type == KeyPress)
                    action.type = ACTION_TYPE::NOTEON;
                else if (event.type == KeyRelease)
                    action.type = ACTION_TYPE::NOTEOFF;
                break;
            }
        }
        for (int k = 0; k < 9; k++) {
            int keyCode = XKeysymToKeycode(display, "123456789"[k]);
            if (event.xkey.keycode == keyCode && event.type == KeyPress) {
                action.type=ACTION_TYPE::CHANGE_ACTIVE_INSTRUMENT;
                action.value=k;
            }
        }
        //If left shift pressed increment octave
        if (event.xkey.keycode == 50 && event.type == KeyPress) {
            action.type=ACTION_TYPE::INCREMENT_OCTAVE;
            action.value=1;
        }
        //If left control pressed decrement octave
        if (event.xkey.keycode == 37 && event.type == KeyPress) {
            action.type=ACTION_TYPE::INCREMENT_OCTAVE;
            action.value=-1;
        }
        //QUIT
        if (event.xkey.keycode == XKeysymToKeycode(display, 'q'))
            action.type = ACTION_TYPE::QUIT;

        //CHANGE VIEW
        if (event.xkey.keycode == XKeysymToKeycode(display, 'a') && event.type == KeyPress){
            action.type = ACTION_TYPE::CHANGE_VIEW;
            action.value = -1;
        }
        //If spacebar pressed toogle play
        if (event.xkey.keycode == 65 && event.type == KeyPress){
            action.type = ACTION_TYPE::PLAY;
        }

        //ROTARY ENCODER ACTIONS
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if (event.xkey.keycode == encoderKeyCodes[i][j] && event.type == KeyPress){
                    if(j==1) {
                        action.type = ACTION_TYPE::ENC_SWITCH;
                        action.value = i;
                    }
                    else{
                        action.type = static_cast<ACTION_TYPE>(ACTION_TYPE::ENC0_ROTATE + i);
                        action.value = -1+2*j/2;
                    }
                }
            }
        }
    }
    return action;
}

InputManagerKeyboard::InputManagerKeyboard(Display *display) {
    this->display = display;
    // Display a keyboard

    printf("|     |     |     |     |     |     |     |\n");
    printf("|  Z  |  X  |  C  |  V  |  B  |  N  |  M  |\n");
    printf("|_____|_____|_____|_____|_____|_____|_____|\n");
    XAutoRepeatOff(display);
}
InputManagerKeyboard::~InputManagerKeyboard() {
    XAutoRepeatOn(display);
}
