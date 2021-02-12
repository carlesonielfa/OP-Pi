#include "input_manager.h"
#include <stdio.h>

using namespace OP_Pi;
using namespace std;

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
        if (event.xkey.keycode == XKeysymToKeycode(display, 'q'))
            action.type = ACTION_TYPE::QUIT;
        if (event.xkey.keycode == XKeysymToKeycode(display, 'u') && event.type == KeyPress){
            action.type = ACTION_TYPE::CHANGE_VIEW;
            action.value = -1;
        }
        //If spacebar pressed toogle play
        if (event.xkey.keycode == 65 && event.type == KeyPress){
            action.type = ACTION_TYPE::PLAY;
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
