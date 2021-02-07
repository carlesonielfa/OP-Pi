#include "input_manager.h"
#include <stdio.h>

using namespace OP_Pi;
using namespace std;

ACTION InputManagerKeyboard::ProcessInput() {
    ACTION action;
    bool bKeyPressed = false;
    XNextEvent(display, &event);

    for (int k = 0; k < 16; k++)
    {
        int keyCode = XKeysymToKeycode(display, "ZSXCFVGBNJMK\xbcL\xbe\xbf"[k]);
        if(event.xkey.keycode==keyCode){
            action.value = 60+k;
            if(event.type==KeyPress)
                action.type = ACTION_TYPE::NOTEON;
            else if(event.type==KeyRelease)
                action.type = ACTION_TYPE::NOTEOFF;
            break;
        }
    }
    if(event.xkey.keycode==XKeysymToKeycode(display, 'q'))
        action.type=ACTION_TYPE::QUIT;

    return action;
}

InputManagerKeyboard::InputManagerKeyboard(Display* display) {
    this->display = display;
    // Display a keyboard
    printf("|   |   |   |   |   | |   |   |   |   | |   | |   |   |   |\n");
    printf("|   | S |   |   | F | | G |   |   | J | | K | | L |   |   |\n");
    printf("|   |___|   |   |___| |___|   |   |___| |___| |___|   |   |__\n");
    printf("|     |     |     |     |     |     |     |     |     |     |\n");
    printf("|  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |\n");
    printf("|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
}
