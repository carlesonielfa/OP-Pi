#ifndef INPUTMANAGER_H // include guard
#define INPUTMANAGER_H

namespace OP_Pi
{
    enum ACTION_TYPE
    {   
        NONE,
        QUIT,
        NOTEON,
        NOTEOFF,
        CHANGE_ACTIVE_INSTRUMENT,//TODO: Change for colored encoders
        INCREMENT_OCTAVE,
        CHANGE_VIEW,
        PLAY,
        ENC_SWITCH,
        ENC0_ROTATE,
        ENC1_ROTATE,
        ENC2_ROTATE,
    };
    struct ACTION{
        ACTION_TYPE type = ACTION_TYPE::NONE;
        short value = 0;
    };
    class InputManager
    {
        public:
            virtual ACTION ProcessInput() = 0;
    };

}

#endif /* INPUTMANAGER_H */