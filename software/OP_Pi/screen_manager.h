#ifndef SCREENMANAGER_H // include guard
#define SCREENMANAGER_H

#include <X11/Xlib.h>
namespace OP_Pi{

    //Color defines
    #define WHITE   0xFFFFFF
    #define RED     0xFF0000
    #define GREEN   0x00FF00
    #define GRAY    0xBEBEBE
    #define CYAN    0x00FFFF

    class ScreenManager{
    public:
        virtual void Draw();
        virtual void DrawPixel(unsigned char x, unsigned char y, unsigned long color)=0;
        virtual void DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color)=0;
        virtual void DrawText()=0;
        void DrawMixer();

    protected:
        unsigned char screenHeight=128;
        unsigned char screenWidth=128;
    };

    class ScreenManagerX11: public ScreenManager{
    public:
        ScreenManagerX11();
        ~ScreenManagerX11();
        void Draw() override;
        void DrawPixel(unsigned char x, unsigned char y, unsigned long color) override;
        void DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,unsigned long color) override;
        void DrawText() override;
        Display* display;
    private:
        Window window;
        GC gc;
    };

    class ScreenManagerOLED: public ScreenManager{
    public:
        ScreenManagerOLED();
        void DrawPixel(unsigned char x, unsigned char y, unsigned long color) override;
        void DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,unsigned long color) override;
        void DrawText() override;
    };
}
#endif /* SCREENMANAGER_H */