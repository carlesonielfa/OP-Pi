#include "screen_manager.h"

#include <unistd.h>
using namespace OP_Pi;
void ScreenManager::Draw() {
    DrawRectangle(0,0,64,128, RED);
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

void ScreenManagerX11::DrawText() {

}
void ScreenManagerX11::Draw() {
    ScreenManager::Draw();
    XFlush(display);
}

void ScreenManagerOLED::DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color){

}

void ScreenManagerOLED::DrawPixel(unsigned char x, unsigned char y, unsigned long color) {

}

void ScreenManagerOLED::DrawText() {

}
