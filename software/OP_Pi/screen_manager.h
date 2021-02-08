#ifndef SCREENMANAGER_H // include guard
#define SCREENMANAGER_H

#include <X11/Xlib.h>
#include "daw.h"

namespace OP_Pi{

    //Color defines
    #define WHITE   0xFFFFFF
    #define RED     0xFF0000
    #define GREEN   0x00FF00
    #define GRAY    0xBEBEBE
    #define CYAN    0x00FFFF

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
        virtual void DrawPixel(unsigned char x, unsigned char y, unsigned long color)=0;
        virtual void DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color, bool fill = true)=0;
        virtual void DrawText(unsigned char x, unsigned char y, unsigned long color,const char* text, FONT_SIZE size, FONT_ALIGN align= FONT_ALIGN::LEFT)=0;
        Daw* daw;
    protected:
        unsigned char screenHeight=128;
        unsigned char screenWidth=128;
    private:
        void DrawMixer(const int bpm,float** outputs, float** gains);
        void DrawChannel(int x, int y,const char* name, const float output, const float gain);
        unsigned char mixerGainWidth = 6;
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
        void DrawPixel(unsigned char x, unsigned char y, unsigned long color) override;
        void DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,unsigned long color, bool fill = true) override;
        void DrawText(unsigned char x, unsigned char y, unsigned long color,const char* text, FONT_SIZE size, FONT_ALIGN align = FONT_ALIGN::LEFT) override;
        Display* display;
    private:
        Window window;
        GC gc;
        X11Font fonts[4];
    };

    class ScreenManagerOLED: public ScreenManager{
    public:
        ScreenManagerOLED(Daw* daw);
        void DrawPixel(unsigned char x, unsigned char y, unsigned long color) override;
        void DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,unsigned long color, bool fill = true) override;
        void DrawText(unsigned char x, unsigned char y, unsigned long color,const char* text, FONT_SIZE size, FONT_ALIGN align= FONT_ALIGN::LEFT) override;
    };
}
#endif /* SCREENMANAGER_H */