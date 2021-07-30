#ifndef SCREENMANAGER_H // include guard
#define SCREENMANAGER_H

#include <X11/Xlib.h>
#include "../daw.h"
//#include "oled_driver.h"
//#include "lcdgfx.h"
#include <lcdgfx.h>
#include <stdio.h>
#include <stdlib.h>


namespace OP_Pi{

    //Color defines
    //#define COLOR     RGB565
    //#define COLOR     24bitRGB

    #define BLACK       0x0000
    //#define BLACK     0X000000

    #define BLUE        0x001F

    #define RED         0xF800

    #define GREEN       0x07E0
    //#define GREEN     0x00FF00

    #define CYAN        0x07FF
    //#define CYAN      0x00FFFF
    
    #define MAGENTA  0xF81F
    //#define MAGENTA     0xFF00FF

    #define YELLOW  0xFFE0
    //#define YELLOW      0xFFFF00

    #define WHITE   0xFFFF
    //#define WHITE       0xFFFFFF

    #define GRAY        0xA534
    //#define GRAY        0xA9A9A9
    
    #define DARKGRAY    0x632C
    //#define DARKGRAY    0x696969

    #define DARKERGRAY  0x4208
    //#define DARKERGRAY  0x424242   
    
    #define DIAL0COLOR  CYAN
    #define DIAL1COLOR  MAGENTA
    #define DIAL2COLOR  YELLOW

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
        void Refresh();
        static void Draw();

        Daw* daw;
    protected:
        virtual void DrawPixel(unsigned char x, unsigned char y, unsigned long color)=0;
        virtual void DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color)=0;
        virtual void DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color, bool fill = true)=0;
        //Draws text and returns the text width
        virtual unsigned short DrawText(unsigned char x, unsigned char y, unsigned long color, string text, FONT_SIZE size, FONT_ALIGN align= FONT_ALIGN::LEFT)=0;

    private:
        //MIXER VIEW
        void DrawMixer(const int bpm,float** outputs, float** gains);
        void DrawChannel(unsigned char x, unsigned char y, string name, const float output, const float gain, bool active = false);
        const unsigned char mixerGainWidth = 6;
        //PATTERN VIEW
        void DrawPattern(unsigned char patternNumber, unsigned char activeInstrument);
        void DrawNoteRow(unsigned char y, string noteName);
        const unsigned char patternRowHeight=12;
        //INSTRUMENT VIEW
        void DrawInstrument(unsigned char activeInstrument, short octaveOffset, float attack, float decay,
                            float sustain, float release, char *presetName="PRESET");

        char* channels [9] = {"A","B","C","D","E", "F","G","H","I"};
    };
    //ScreenManager* screenManager;
    const unsigned char screenHeight=128;
    const unsigned char screenWidth=128;
    struct X11Font{
        XFontStruct* font;
        unsigned char size;
    };
    class ScreenManagerX11: public ScreenManager{
    public:
        explicit ScreenManagerX11(Daw* daw);
        ~ScreenManagerX11();
        static void Draw();
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
        DrawText(unsigned char x, unsigned char y, unsigned long color, string text, FONT_SIZE size, FONT_ALIGN align = FONT_ALIGN::LEFT) override;
    private:
        XEvent event;
        GC gc;
        X11Font fonts[4];
    };


    class ScreenManagerOLED: public ScreenManager{
    public:
        ScreenManagerOLED(Daw* daw);
        ~ScreenManagerOLED();
        static bool DrawCallback();
        static void Draw();
    protected:
        const uint8_t* fonts[4];
        unsigned short fontSizes[4];
        DisplaySSD1351_128x128x16_SPI* display;
        NanoEngine16<DisplaySSD1351_128x128x16_SPI>* engine;
        void DrawPixel(unsigned char x, unsigned char y, unsigned long color) override;
        void DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,unsigned long color, bool fill = true) override;
        unsigned short
        DrawText(unsigned char x, unsigned char y, unsigned long color, string text, FONT_SIZE size, FONT_ALIGN align= FONT_ALIGN::LEFT) override;

        void DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color) override;
    };
}
#endif /* SCREENMANAGER_H */