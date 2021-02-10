#ifndef SCREENMANAGER_H // include guard
#define SCREENMANAGER_H

#include <X11/Xlib.h>
#include "daw.h"

namespace OP_Pi{

    //Color defines
    #define WHITE       0xFFFFFF
    #define RED         0xFF0000
    #define MAGENTA     0xFF00FF
    #define GREEN       0x00FF00
    #define GRAY        0xA9A9A9
    #define DARKGRAY    0x696969
    #define DARKERGRAY  0x424242
    #define CYAN        0x00FFFF
    #define YELLOW      0xFFFF00

    enum FONT_SIZE{
        TINY, //8pt
        SMALL, //10pt
        MEDIUM, //12pt
        BIG, //14pt
        HUGE,  //16pt
    };
    enum FONT_ALIGN{
        LEFT,
        CENTER,
        RIGHT,
    };
    class ScreenManager{
    public:
        ScreenManager();
        ScreenManager(Daw* daw);
        virtual void Draw();

        Daw* daw;
    protected:
        virtual void DrawPixel(unsigned char x, unsigned char y, unsigned long color)=0;
        virtual void DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color)=0;
        virtual void DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color, bool fill = true)=0;
        //Draws text and returns the text width
        virtual unsigned short DrawText(unsigned char x, unsigned char y, unsigned long color, const char* text, FONT_SIZE size, FONT_ALIGN align= FONT_ALIGN::LEFT)=0;
        unsigned char screenHeight=128;
        unsigned char screenWidth=128;
    private:
        //MIXER VIEW
        void DrawMixer(const int bpm,float** outputs, float** gains);
        void DrawChannel(unsigned char x, unsigned char y, const char* name, const float output, const float gain, bool active = false);
        const unsigned char mixerGainWidth = 6;
        //PATTERN VIEW
        void DrawPattern(unsigned char patternNumber, unsigned char activeInstrument);
        void DrawNote(unsigned char y);
        const unsigned char patternNoteHeight=11;
        //INSTRUMENT VIEW
        void DrawInstrument(unsigned char activeInstrument, short octaveOffset, float attack, float decay,
                            float sustain, float release, char *presetName="PRESET");

        char* channels [9] = {"A","B","C","D","E", "F","G","H","I"};
    };
    struct X11Font{
        XFontStruct* font;
        unsigned char size;
    };
    class ScreenManagerX11: public ScreenManager{
    public:
        ScreenManagerX11(Daw* daw);
        ~ScreenManagerX11();
        void Draw() override;
        Display* display;
    protected:
        void
        DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color) override;

    public:
        Window window;
    protected:
        void DrawPixel(unsigned char x, unsigned char y, unsigned long color) override;
        void DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,unsigned long color, bool fill = true) override;
        unsigned short
        DrawText(unsigned char x, unsigned char y, unsigned long color, const char* text, FONT_SIZE size, FONT_ALIGN align = FONT_ALIGN::LEFT) override;
    private:
        XEvent event;
        GC gc;
        X11Font fonts[4];
    };

    class ScreenManagerOLED: public ScreenManager{
    public:
        ScreenManagerOLED(Daw* daw);
    protected:
        void DrawPixel(unsigned char x, unsigned char y, unsigned long color) override;
        void DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,unsigned long color, bool fill = true) override;
        unsigned short
        DrawText(unsigned char x, unsigned char y, unsigned long color, const char* text, FONT_SIZE size, FONT_ALIGN align= FONT_ALIGN::LEFT) override;

        void DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color) override;
    };
}
#endif /* SCREENMANAGER_H */