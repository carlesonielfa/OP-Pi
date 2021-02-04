#include "input_manager.h"
#include <stdio.h>

using namespace OP_Pi;
using namespace std;
bool InputManager::GetKeyState(KeySym keySym)
{  
    if(display == NULL)
    {
        return false;
    }
    char szKey[32];
    int iKeyCodeToFind = XKeysymToKeycode(display, keySym);
    
    XQueryKeymap(display, szKey);
    
    return szKey[iKeyCodeToFind / 8] & (1 << (iKeyCodeToFind % 8));
}
InputManager::InputManager(){
    //Open display to process keypresses
    if(useKeyboard){
        display = XOpenDisplay(0);
        // Display a keyboard
	    printf("|   |   |   |   |   | |   |   |   |   | |   | |   |   |   |\n");
        printf("|   | S |   |   | F | | G |   |   | J | | K | | L |   |   |\n");
        printf("|   |___|   |   |___| |___|   |   |___| |___| |___|   |   |__\n");
		printf("|     |     |     |     |     |     |     |     |     |     |\n");
		printf("|  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |\n");
		printf("|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
    }
}
ACTION InputManager::ProcessInput(){
    ACTION action;

    if(useKeyboard){
        bool bKeyPressed = false;

        for (int k = 0; k < 16; k++)
		{
			if (GetKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe\xbf"[k])))
			{
				if (nCurrentKey != k)
				{					
					//dFrequencyOutput = dOctaveBaseFrequency * pow(d12thRootOf2, k);
					//envelope.NoteOn(sound.GetTime());
					//printf("Note On : %d\n",k);
                    nCurrentKey = k;
                    action.type = ACTION_TYPE::NOTEON;
                    action.value = 60+nCurrentKey;
                    		
                    return action;
				}

				bKeyPressed = true;
			}
		}

		if (!bKeyPressed)
		{	
			if (nCurrentKey != -1)
			{
				//printf("Note Off: %d\n", nCurrentKey);
                action.type = ACTION_TYPE::NOTEOFF;
                action.value = 60+nCurrentKey;
				nCurrentKey = -1;
                return action;
			}
		}
        if(GetKeyState('q')){
            action.type = ACTION_TYPE::QUIT;
        }
    }
    return action; 
}