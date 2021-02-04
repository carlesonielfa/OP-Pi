#include "input_manager.h"
using namespace OP_Pi;


ACTION InputManager::processInput(){
    ACTION action;

    if(useKeyboard){
        int c = getc(stdin);
        if (c == 'q') {
            action.type=ACTION_TYPE::QUIT;
        } else if (c == 'z'){
            //TODO: change to midi note number
            action.type=ACTION_TYPE::NOTEON;
            action.value=440;
        } else if (c=='x'){
            //TODO: change to midi note number
            action.type=ACTION_TYPE::NOTEON;
            action.value=220;
        }
    }
    return action; 
}