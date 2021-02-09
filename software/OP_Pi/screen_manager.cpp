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
    switch (daw->activeView) {
        case DAW_VIEW::MIXER:
            DrawMixer(daw->bpm,daw->outputs, daw->gains);
            break;
        case DAW_VIEW::PATTERN:
            DrawPattern(0,daw->GetIndexActiveInstrument());
            break;
    }

}
void ScreenManager::DrawMixer(const int bpm,float**  outputs, float** gains) {

    DrawText(0, 5, WHITE, const_cast<char *>(std::to_string(bpm).c_str()), FONT_SIZE::MEDIUM, FONT_ALIGN::CENTER);
    DrawText(0,20,CYAN, "BPM", FONT_SIZE::TINY, FONT_ALIGN::CENTER);
    DrawRectangle(screenWidth/2-17, 2, screenWidth/2+17, 30, CYAN, false);

    for(int i=0; i<sizeof(channels)/sizeof(char*); i++){
        if(i<daw->GetNInstruments())
            DrawChannel(12+40*(i%3),38+27*(i/3), channels[i], *outputs[i], *gains[i], i==daw->GetIndexActiveInstrument());
        else
            DrawChannel(12+40*(i%3),38+27*(i/3), channels[i], 0, 0);
    }
}
void ScreenManager::DrawChannel(unsigned char x, unsigned char y, const char* name, const float output, const float gain, bool active) {

    DrawText(x,y+6,active ? WHITE : DARKGRAY,name,FONT_SIZE::BIG);
    DrawRectangle(x+20, y, x+20+mixerGainWidth, y+24, GRAY);
    DrawRectangle(x+20, y+24*(1-output), x+20+mixerGainWidth, y+24, RED);
    DrawRectangle(x+18, y+24*(1-gain), x+22+mixerGainWidth, y+24*(1-gain)+1, MAGENTA);

}

void ScreenManager::DrawPattern(unsigned char patternNumber, unsigned char activeInstrument) {
    //Draw Header
    unsigned short w1;
    DrawText(10,10, CYAN,"INSTRUMENT ",FONT_SIZE::SMALL);
    w1 = DrawText(screenWidth-24,17, CYAN, channels[activeInstrument],FONT_SIZE::BIG);
    DrawRectangle(screenWidth-30, 9, screenWidth-18+w1, 28+10, WHITE, false);
    unsigned short w0 = DrawText(10,28, WHITE,"PATTERN ",FONT_SIZE::SMALL);
    DrawText(10+w0-1,28, MAGENTA, std::to_string(patternNumber).c_str(),FONT_SIZE::SMALL);


    unsigned short notesStart = (screenHeight-patternNoteHeight)*7;
    unsigned short xBarStart = 12;
    //1 BAR per pattern, 4 beats per bar 4 step per beat, 4 divisons per step
    unsigned short xPosLine=0;
    for(int i=0; i<=16;i++){
        //Draw beats and steps
        xPosLine = xBarStart + i*(screenWidth - xBarStart) / 16;
        DrawLine(xPosLine, notesStart, xPosLine, screenHeight-1,i % 4 == 0 ? DARKGRAY : DARKERGRAY);
    }

    for(int i=0; i<7;i++){
        DrawNote((screenHeight-patternNoteHeight)*7+i*patternNoteHeight);
    }
    //Draw Cursor
    unsigned short xcursor = xBarStart + daw->cursor * (screenWidth - xBarStart);
    DrawLine(xcursor,notesStart-4,xcursor, screenHeight-1,YELLOW);

}
void ScreenManager::DrawNote(unsigned char y){
    DrawRectangle(0,y+1,12, y + patternNoteHeight-1,WHITE);
    DrawLine(12,y,screenWidth-1,y,DARKGRAY);
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

    char* font_names [] = {"lucidasanstypewriter-bold-8", "lucidasanstypewriter-10", "lucidasanstypewriter-12", "lucidasanstypewriter-14", "lucidasanstypewriter-24"};
    //char* font_names [] = {"-urw-nimbus mono l-regular-o-normal--0-0-0-0-p-0-iso8859-15", "-urw-nimbus mono l-regular-o-normal--0-0-0-0-p-0-iso8859-15", "lucidasanstypewriter-12", "lucidasanstypewriter-14", "lucidasanstypewriter-24"};

    unsigned char sizes [] = {8,10,12,14,24};

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

unsigned short ScreenManagerX11::DrawText(unsigned char x, unsigned char y, unsigned long color, const char* text, FONT_SIZE size, FONT_ALIGN align) {
    unsigned short textWidth = XTextWidth(fonts[size].font, text, strlen(text));
    if(align==FONT_ALIGN::CENTER) {
        x = (screenWidth - x) / 2 - textWidth / 2;
    }
    y += fonts[size].size;

    XSetFont(display,gc, fonts[size].font->fid);
    XSetForeground(display, gc, color);
    XDrawString(display,window, gc, x,y,text, strlen(text));
    return  textWidth;
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

void ScreenManagerX11::DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,
                                unsigned long color) {
    XSetForeground(display, gc, color);
    XDrawLine(display,window,gc,x1,y1,x2,y2);
}

void ScreenManagerOLED::DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color, bool fill){

}

void ScreenManagerOLED::DrawPixel(unsigned char x, unsigned char y, unsigned long color) {

}

unsigned short
ScreenManagerOLED::DrawText(unsigned char x, unsigned char y, unsigned long color, const char* text, FONT_SIZE size, FONT_ALIGN align) {

}

void ScreenManagerOLED::DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,
                                 unsigned long color) {

}
