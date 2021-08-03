#include "screen_manager.h"

#include <string>
#include <utility>


using namespace OP_Pi;
ScreenManager* screenManager = nullptr; 
ScreenManager::ScreenManager(Daw *daw) {
    this->daw = daw;
}
void ScreenManager::Draw() {
    if(screenManager==nullptr)
        printf("Screen manager not initalized");


    Daw* daw = screenManager->daw;
    switch (daw->activeView) {
        case DAW_VIEW::MIXER:
            screenManager->DrawMixer(daw->bpm, daw->instrumentOutputs, daw->instrumentGains);
            break;
        case DAW_VIEW::PATTERN:
            screenManager->DrawPattern(daw->getIndexActivePattern(), daw->getIndexActiveInstrument());
            break;
        case DAW_VIEW::INSTRUMENT: {
            auto env = (EnvelopeADSR *) daw->getInstrumentEnvelope();
            screenManager->DrawInstrument(daw->getIndexActiveInstrument(),
                           daw->getOctaveCurrentInstrument(),
                           env->attackTime, env->decayTime, env->sustainAmplitude, env->releaseTime,
                           daw->getActiveInstrumentPresetName());
            break;
        }
        default:
            //View not implemented
            screenManager->DrawText(0,screenHeight/2-28,WHITE,"VIEW", FONT_SIZE::SMALL,FONT_ALIGN::CENTER);
            screenManager->DrawText(0,screenHeight/2-14,WHITE,"NOT", FONT_SIZE::SMALL,FONT_ALIGN::CENTER);
            screenManager->DrawText(0,screenHeight/2,WHITE,"IMPLEMENTED", FONT_SIZE::SMALL,FONT_ALIGN::CENTER);
            break;
    }
}
void ScreenManager::DrawMixer(const int bpm,float**  outputs, float** gains) {

    DrawText(0, 5, WHITE, to_string(bpm), FONT_SIZE::MEDIUM, FONT_ALIGN::CENTER);
    DrawText(0,20,DIAL0COLOR, "BPM", FONT_SIZE::TINY, FONT_ALIGN::CENTER);
    DrawRectangle(screenWidth/2-17, 2, screenWidth/2+17, 30, DIAL0COLOR, false);

    for(int i=0; i<sizeof(channels)/sizeof(char*); i++){
        if(i< daw->getNInstruments())
            DrawChannel(12+40*(i%3),38+27*(i/3), channels[i], *outputs[i], *gains[i], i==
                                                                                      daw->getIndexActiveInstrument());
        else
            DrawChannel(12+40*(i%3),38+27*(i/3), channels[i], 0, 0);
    }
}
void ScreenManager::DrawChannel(unsigned char x, unsigned char y, string name, const float output, const float gain, bool active) {

    DrawText(x,y+6,active ? WHITE : DARKGRAY,std::move(name),FONT_SIZE::BIG);
    DrawRectangle(x+20, y, x+20+mixerGainWidth, y+24, GRAY);
    DrawRectangle(x+20, y+24*(1-output), x+20+mixerGainWidth, y+24, RED);
    DrawRectangle(x+18, y+24*(1-gain), x+22+mixerGainWidth, y+24*(1-gain)+1, DIAL1COLOR);

}

void ScreenManager::DrawPattern(unsigned char patternNumber, unsigned char activeInstrument) {
    //Draw Header
    unsigned short w1;
    DrawText(10,10, WHITE,"INSTRUMENT ",FONT_SIZE::SMALL);
    w1 = DrawText(screenWidth-24,17, WHITE, channels[activeInstrument],FONT_SIZE::BIG);
    DrawRectangle(screenWidth-30, 9, screenWidth-18+w1, 28+10, DARKGRAY, false);
    unsigned short w0 = DrawText(10,28, DIAL1COLOR,"PATTERN ",FONT_SIZE::SMALL);
    DrawText(10+w0-1,28, DIAL1COLOR, std::to_string(patternNumber),FONT_SIZE::SMALL);


    unsigned short notesStart = (screenHeight - patternRowHeight) * 7;
    unsigned short xBarStart = 24;
    //1 BAR per pattern, 4 beats per bar 4 step per beat, 4 divisions per step
    unsigned short xPosLine;
    for(int i=0; i<=16;i++){
        //Draw beats and steps
        xPosLine = xBarStart + i*(screenWidth - xBarStart) / 16;
        DrawLine(xPosLine, notesStart, xPosLine, screenHeight-1,i % 4 == 0 ? DARKGRAY : DARKERGRAY);
    }

    //Draw note row
    for(int i=0; i<7;i++){
        DrawNoteRow((screenHeight - patternRowHeight) * 7 + i * patternRowHeight,daw->noteNames[6-i]);
    }
    //Draw Cursor
    unsigned short xCursor = xBarStart + daw->cursor * (screenWidth - xBarStart);
    DrawLine(xCursor,notesStart-4,xCursor, screenHeight-1,DIAL0COLOR);

    //Draw Pattern notes
    unsigned short noteRow;
    for(Hit h: daw->getHitsInActivePattern()){
        if(h.instrument==daw->getActiveInstrument()){
            noteRow = (screenHeight - patternRowHeight) * 7 + (6 - h.note.index) * patternRowHeight;
            DrawRectangle(xBarStart + daw->TimeToBarPosition(h.note.on) * (screenWidth - xBarStart),
                          noteRow + 2,
                          xBarStart + daw->TimeToBarPosition(h.note.off) * (screenWidth - xBarStart)-2,
                          noteRow + patternRowHeight - 2,
                          GRAY);
        }
    }
}
void ScreenManager::DrawNoteRow(unsigned char y, string noteName){
    DrawRectangle(0,y+1,23, y + patternRowHeight - 1,WHITE);
    DrawText(1,y+2,BLACK, std::move(noteName),FONT_SIZE::TINY);
    DrawLine(24,y,screenWidth-1,y,DARKGRAY);
}

void ScreenManager::DrawInstrument(unsigned char activeInstrument, short octaveOffset, float attack, float decay,
                                   float sustain, float release, char *presetName) {

    //Draw letter active instrument
    DrawText(10,16, WHITE,"INSTRUMENT ",FONT_SIZE::SMALL);
    unsigned short w1 = DrawText(screenWidth-24,17, WHITE, channels[activeInstrument],FONT_SIZE::BIG);
    DrawRectangle(screenWidth-30, 9, screenWidth-18+w1, 28+10, DARKGRAY, false);

    //Draw octave and sign
    string octaveOffsetString = std::to_string(octaveOffset);
    w1 = DrawText(10,30, GRAY, "OCTAVE", FONT_SIZE::TINY);
    if(octaveOffset==0)
        octaveOffsetString = " "+octaveOffsetString;
    if(octaveOffset>0)
        octaveOffsetString = "+"+octaveOffsetString;
    DrawText(10+w1+8,30, GRAY, octaveOffsetString, FONT_SIZE::TINY);

    //Draw Preset name
    DrawText(0,50, DIAL0COLOR, presetName, FONT_SIZE::SMALL,FONT_ALIGN::CENTER);

    //Draw Envelope
    float totalTime = attack+decay+release;
    float sustainTime = totalTime*0.3;
    totalTime= totalTime+sustainTime;

    unsigned short frameXStart = 11;
    unsigned short frameXEnd = screenWidth-11;
    unsigned short frameYStart = 67;
    unsigned short frameYEnd = screenHeight-11;
    unsigned short frameWidth = frameXEnd-frameXStart;
    unsigned short frameHeight = frameYEnd-frameYStart;
    DrawRectangle(frameXStart-1,frameYStart-1, frameXEnd+1, frameYEnd+1, GRAY, false);
    //Attack
    DrawLine(frameXStart,
             frameXEnd,
             frameXStart+frameWidth*attack/totalTime,
             frameYStart,
             daw->cursor==0? DIAL1COLOR : WHITE);
    //Decay
    DrawLine(frameXStart+frameWidth*attack/totalTime,
             frameYStart,
             frameXStart+frameWidth*((attack+decay)/totalTime),
             frameYStart+frameHeight*(1-sustain),
             daw->cursor==1? DIAL1COLOR : WHITE);
    //Sustain
    DrawLine(frameXStart+frameWidth*(attack+decay)/totalTime,
             frameYStart+frameHeight*(1-sustain),
             frameXStart+frameWidth*((attack+decay+sustainTime)/totalTime),
             frameYStart+frameHeight*(1-sustain),
             daw->cursor==2? DIAL1COLOR : WHITE);
    //Release
    DrawLine(frameXStart+frameWidth*(attack+decay+sustainTime)/totalTime,
             frameYStart+frameHeight*(1-sustain),
             frameXStart+frameWidth*1,//(attack+decay+sustainTime+decay)/totalTime,
             frameYEnd,
             daw->cursor==3? DIAL1COLOR : WHITE);


}

ScreenManagerX11::ScreenManagerX11(Daw* daw):ScreenManager(daw) {
    //this->daw = daw;
    //Create window
    display = XOpenDisplay(nullptr);
    int s = DefaultScreen(display);
    window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, screenWidth, screenHeight, 0,
                                        BlackPixel(display, s), BlackPixel(display, s));
    XSelectInput(display, window, KeyPressMask | KeyReleaseMask | StructureNotifyMask | ExposureMask);
    XMapWindow(display, window);

    //Create Graphics context for drawing
    gc = XCreateGC(display, window, 0, nullptr);
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
unsigned short ScreenManagerX11::DrawText(unsigned char x, unsigned char y, unsigned long color, string text, FONT_SIZE size, FONT_ALIGN align) {
    unsigned short textWidth = XTextWidth(fonts[size].font, text.c_str(), text.length());
    if(align==FONT_ALIGN::CENTER) {
        x = (screenWidth - x) / 2 - textWidth / 2;
    }
    y += fonts[size].size;

    XSetFont(display,gc, fonts[size].font->fid);
    XSetForeground(display, gc, color);
    XDrawString(display,window, gc, x,y,text.c_str(), text.length());
    return  textWidth;
}
void ScreenManagerX11::Draw() {
    //XExposeEvent e;
    //XSendEvent(display, window, 1, Expose, reinterpret_cast<XEvent *>(&e));
    Display* d= dynamic_cast<ScreenManagerX11*>(screenManager)->display;
    XClearWindow(d, dynamic_cast<ScreenManagerX11*>(screenManager)->window);
    ScreenManager::Draw();
    //XFlush(display);
    XSync(d, false);
    //XNextEvent(display, &event);
}
void ScreenManagerX11::DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,
                                unsigned long color) {
    XSetForeground(display, gc, color);
    XDrawLine(display,window,gc,x1,y1,x2,y2);
}


ScreenManagerOLED::ScreenManagerOLED(Daw* daw):ScreenManager(daw) {
    printf("Started Screen\n");
    screenManager = this;
    fonts[0] = ssd1306xled_font5x7;
    fontSizes[0] = 5;
    fonts[1] = ssd1306xled_font6x8;
    fontSizes[1] = 6;
    fonts[2] = ssd1306xled_font8x16;
    fontSizes[2] = 8;
    fonts[3] = ssd1306xled_font8x16;
    fontSizes[3] = 8;
    display = new DisplaySSD1351_128x128x16_SPI(25, {-1, 0, 24, 0, -1, -1});
    
    engine = new NanoEngine16<DisplaySSD1351_128x128x16_SPI> (*display);
    display->begin();
    display->getInterface().setRotation(2);
    engine->drawCallback( ScreenManagerOLED::DrawCallback );
    engine->begin();

}
void ScreenManagerOLED::DrawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned long color, bool fill){
    engine->getCanvas().setColor(color);
    if(fill)
        engine->getCanvas().fillRect(x1,y1,x2,y2);
    else
        engine->getCanvas().drawRect(x1,y1,x2,y2);
}
void ScreenManagerOLED::DrawPixel(unsigned char x, unsigned char y, unsigned long color) {
    engine->getCanvas().setColor(color);
    engine->getCanvas().putPixel(x,y);
}
unsigned short ScreenManagerOLED::DrawText(unsigned char x, unsigned char y, unsigned long color, string text, FONT_SIZE size, FONT_ALIGN align) {
    engine->getCanvas().setFixedFont(fonts[size]);
    unsigned short textWidth = fontSizes[size]*text.length();
    if(align==FONT_ALIGN::CENTER) {
        x = (screenWidth - x) / 2 - textWidth / 2;
    }
    //y += 6/2;

    engine->getCanvas().setColor(color);
    engine->getCanvas().printFixed(x, y, text.c_str());
    return textWidth;
}
void ScreenManagerOLED::DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,
                                 unsigned long color) {
    engine->getCanvas().setColor(color);
    engine->getCanvas().drawLine(x1,y1,x2,y2);
}
void ScreenManagerOLED::Draw(){
    auto engine = dynamic_cast<ScreenManagerOLED*>(screenManager)->engine;
    engine->refresh();
    engine->display();
    lcd_delay(20);
}
bool ScreenManagerOLED::DrawCallback(){

    auto canvas = dynamic_cast<ScreenManagerOLED*>(screenManager)->engine->getCanvas();
    canvas.clear();
    ScreenManager::Draw();
    //delay(5);
    delayMicroseconds(5);
    return true;
}
ScreenManagerOLED::~ScreenManagerOLED() {
    //engine->end();
    delete engine;
    display->clear();
    display->end();
    delete display;
    printf("Display terminated\n");
}
