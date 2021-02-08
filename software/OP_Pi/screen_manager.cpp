#include "screen_manager.h"

#include <unistd.h>
#include <cstdio>
#include <string>
#include <string.h>
using namespace OP_Pi;
ScreenManager::ScreenManager(Daw *daw) {
    this->daw = daw;
}
void ScreenManager::Draw() {
    double gains [] = {0.5,0,0,0,0,0,0,0};
    DrawMixer(daw->bpm,daw->outputs, daw->gains);
}
void ScreenManager::DrawMixer(const int bpm,float**  outputs, float** gains) {

    DrawText(0, 5, WHITE, const_cast<char *>(std::to_string(bpm).c_str()), FONT_SIZE::MEDIUM, FONT_ALIGN::CENTER);
    DrawText(0,20,WHITE, "BPM", FONT_SIZE::TINY, FONT_ALIGN::CENTER);
    DrawRectangle(screenWidth/2-17, 2, screenWidth/2+17, 30, WHITE, false);

    for(int i=0; i<sizeof(channels)/sizeof(char*); i++){
        if(i<daw->GetNInstruments())
            DrawChannel(12+40*(i%3),38+27*(i/3), channels[i], *outputs[i], *gains[i]);
        else
            DrawChannel(12+40*(i%3),38+27*(i/3), channels[i], 0, 0);
    }
}
void ScreenManager::DrawChannel(const int x,const int y,const char* name,float output, float gain) {
    DrawText(x,y+6,WHITE,name,FONT_SIZE::BIG);
    DrawRectangle(x+20, y, x+20+mixerGainWidth, y+24, GRAY);
    DrawRectangle(x+20, y+24*(1-output), x+20+mixerGainWidth, y+24, RED);
    DrawRectangle(x+18, y+24*(1-gain), x+22+mixerGainWidth, y+24*(1-gain)+1, GREEN);

}
ScreenManagerX11::ScreenManagerX11(Daw* daw):ScreenManager(daw) {
    //this->daw = daw;
    //Create window
    display = XOpenDisplay(0);
    int s = DefaultScreen(display);
    window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, screenWidth, screenHeight, 0,
                                        BlackPixel(display, s), BlackPixel(display, s));
    XSelectInput(display, window, KeyPressMask | KeyReleaseMask | StructureNotifyMask | ExposureMask);
    XMapWindow(display, window);

    //Create Graphics context for drawing
    gc = XCreateGC(display, window, 0, 0);
    XSetForeground(display, gc, WhitePixel(display,s));

    for(;;) {
        XEvent e;
        XNextEvent(display, &e);
        if (e.type == MapNotify)
            break;
    }

    //Load fonts

    char* font_names [] = {"lucidasanstypewriter-bold-8", "lucidasanstypewriter-10", "lucidasanstypewriter-12", "lucidasanstypewriter-14", "lucidasanstypewriter-18"};

    unsigned char sizes [] = {8,10,12,14,18};

    for(int i=0; i<5;i++){
        fonts[i].font = XLoadQueryFont(display,font_names[i]);
        fonts[i].size = sizes[i];
    }
}

ScreenManagerX11::~ScreenManagerX11() {
    for(int i=0;i<5;i++){
        XUnloadFont(display, fonts[i].font->fid);
        delete fonts[i].font;
    }
    XCloseDisplay(display);
}
void ScreenManagerX11::DrawPixel(unsigned char x, unsigned char y, unsigned long color) {
    XSetForeground(display, gc, color);
    XDrawPoint(display, window, gc, x,y);
}

void ScreenManagerX11::DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,unsigned long color, bool fill) {

    XSetForeground(display, gc, color);
    if(fill)
        XFillRectangle(display, window,gc, x1,y1,x2-x1,y2-y1);
    else
        XDrawRectangle(display, window,gc, x1,y1,x2-x1,y2-y1);
}

void ScreenManagerX11::DrawText(unsigned char x, unsigned char y, unsigned long color,const char* text, FONT_SIZE size, FONT_ALIGN align) {
    if(align==FONT_ALIGN::CENTER)
        x = (screenWidth - x)/2 - XTextWidth(fonts[size].font, text, strlen(text))/2;
    y+=fonts[size].size;
    XSetFont(display,gc, fonts[size].font->fid);
    XSetForeground(display, gc, color);
    XDrawString(display,window, gc, x,y,text, strlen(text));
}
void ScreenManagerX11::Draw() {
    //XExposeEvent e;
    //XSendEvent(display, window, 1, Expose, reinterpret_cast<XEvent *>(&e));
    XClearWindow(display,window);
    ScreenManager::Draw();
    //XFlush(display);
    XSync(display, false);
    //XNextEvent(display, &event);
}

void ScreenManagerOLED::DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color, bool fill){

}

void ScreenManagerOLED::DrawPixel(unsigned char x, unsigned char y, unsigned long color) {

}

void ScreenManagerOLED::DrawText(unsigned char x, unsigned char y, unsigned long color,const char* text, FONT_SIZE size, FONT_ALIGN align) {

}
