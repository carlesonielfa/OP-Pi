#include "screen_manager.h"

#include <unistd.h>
#include <cstdio>
#include <string.h>

using namespace OP_Pi;
void ScreenManager::Draw() {
    DrawText(0,0,WHITE, "128", FONT_SIZE::HUGE, FONT_ALIGN::CENTER);
    DrawText(0,20,WHITE, "BPM", FONT_SIZE::TINY, FONT_ALIGN::CENTER);

}
ScreenManagerX11::ScreenManagerX11() {
    //Create window
    display = XOpenDisplay(0);
    int s = DefaultScreen(display);
    window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, screenWidth, screenHeight, 0,
                                        BlackPixel(display, s), BlackPixel(display, s));
    XSelectInput(display, window, KeyPressMask | KeyReleaseMask | StructureNotifyMask);
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
    XCloseDisplay(display);
}
void ScreenManagerX11::DrawPixel(unsigned char x, unsigned char y, unsigned long color) {
    XSetForeground(display, gc, color);
    XDrawPoint(display, window, gc, x,y);
}

void ScreenManagerX11::DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,unsigned long color) {
    XSetForeground(display, gc, color);
    XFillRectangle(display, window,gc, x1,y1,x2-x1,y2-y1);
}

void ScreenManagerX11::DrawText(unsigned char x, unsigned char y, unsigned long color, char* text, FONT_SIZE size, FONT_ALIGN align) {
    if(align==FONT_ALIGN::CENTER)
        x = (screenWidth - x)/2 - fonts[size].size*strlen(text)/2;
    y+=fonts[size].size;
    XSetFont(display,gc, fonts[size].font->fid);
    XSetForeground(display, gc, color);
    XDrawString(display,window, gc, x,y,text, strlen(text));
}
void ScreenManagerX11::Draw() {
    ScreenManager::Draw();
    XFlush(display);
}

void ScreenManagerOLED::DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color){

}

void ScreenManagerOLED::DrawPixel(unsigned char x, unsigned char y, unsigned long color) {

}

void ScreenManagerOLED::DrawText(unsigned char x, unsigned char y, unsigned long color, char* text, FONT_SIZE size, FONT_ALIGN align) {

}
