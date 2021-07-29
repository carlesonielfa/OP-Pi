#include "oled_driver.h"

#define swap(a, b) { uint16_t t = a; a = b; b = t; }
uint8_t color_byte[2],color_fill_byte[2];

uint8_t oled_cs = 8;
uint8_t oled_dc = 24;
uint8_t oled_rst= 25;

void OLED_CS(uint8_t x) {
  digitalWrite(oled_cs, x);
}

void OLED_DC(uint8_t x) {
  digitalWrite(oled_dc, x);
}

void OLED_RST(uint8_t x)  {
  digitalWrite(oled_rst, x);
}

void Set_Color(uint16_t color)  {
  color_byte[0] = (uint8_t)(color >> 8);
  color_byte[1] = (uint8_t)(color & 0x00ff);
}


void Set_FillColor(uint16_t color)  {
  color_fill_byte[0] = (uint8_t)(color >> 8);
  color_fill_byte[1] = (uint8_t)(color & 0x00ff);
}


void Write_Command(uint8_t cmd)  {
  
  OLED_CS(0);
  
  
  uint8_t read_data;

  OLED_DC(0);
  
  wiringPiSPIDataRW(0,&cmd,1);
  
  OLED_CS(1);
}


void Write_Data(uint8_t dat) {
  
  OLED_CS(0);
  

  OLED_DC(1);
  
  wiringPiSPIDataRW(0,&dat,1);
  
  OLED_CS(1);
  
}


void RAM_Address(void)  {
  
  Write_Command(0x15);
  Write_Data(0x00);
  Write_Data(0x7f);

  Write_Command(0x75);
  Write_Data(0x00);
  Write_Data(0x7f);
}



void Clear_Screen(void)  {
  
  int i,j;
  
  uint8_t clear_byte[] = {0x00, 0x00};
  RAM_Address();
  Write_Command(0x5C);
  for(i=0;i<128;i++)  {
    for(j=0;j<128;j++)  {
      Write_Data(clear_byte[0]);//RAM data clear
      Write_Data(clear_byte[1]);
    }
  }
}
  

void Fill_Color(uint16_t color)  {
  
  int i,j;
  RAM_Address();
  Write_Command(0x5C);
  Set_Color(color);
  for(i = 0; i < 128; i++)  {
    for(j = 0; j < 128; j++)  {
      Write_Data(color_byte[0]);
      Write_Data(color_byte[1]);
    }
  }
}


void Set_Coordinate(uint16_t x, uint16_t y)  {

  if((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT)) 
    return;
  //Set x and y coordinate
  Write_Command(SSD1351_CMD_SETCOLUMN);
  Write_Data(x);
  Write_Data(SSD1351_WIDTH-1);
  Write_Command(SSD1351_CMD_SETROW);
  Write_Data(y);
  Write_Data(SSD1351_HEIGHT-1);
  Write_Command(SSD1351_CMD_WRITERAM);
}


void Set_Address(uint8_t column, uint8_t row)  {
  
  Write_Command(SSD1351_CMD_SETCOLUMN);  
  Write_Data(column);	//X start 
  Write_Data(column);	//X end 
  Write_Command(SSD1351_CMD_SETROW); 
  Write_Data(row);	//Y start 
  Write_Data(row+7);	//Y end 
  Write_Command(SSD1351_CMD_WRITERAM); 
}


void Write_text(uint8_t dat) {
  
  uint8_t i;
  
  for(i=0;i<8;i++)  {
    if (dat & 0x01) {
      Write_Data(color_byte[0]);
      Write_Data(color_byte[1]);
    }
    else  {
      Write_Data(0x00);
      Write_Data(0x00);
    }
    dat >>= 1;
  }
}


void Invert(uint8_t v) {
  
  if (v)
    Write_Command(SSD1351_CMD_INVERTDISPLAY);
  else
    Write_Command(SSD1351_CMD_NORMALDISPLAY);
}


void Draw_Pixel(int16_t x, int16_t y)
{
  // Bounds check.
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT)) return;
  if ((x < 0) || (y < 0)) return;
  
  Set_Address(x, y);
  
  // transfer data
  Write_Data(color_byte[0]);
  Write_Data(color_byte[1]);  
}
  
void DEV_GPIO_Mode(uint16_t Pin, uint16_t Mode)
{
    if(Mode == 0 || Mode == INPUT){
        pinMode(Pin, INPUT);
        pullUpDnControl(Pin, PUD_UP);
    }else{ 
        pinMode(Pin, OUTPUT);
        // printf (" %d OUT \r\n",Pin);
    }
}

int Device_Init(void) {

    if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
        printf("wiringPi setup failed\r\n");
        return 1;
    } else {
        printf("wiringPi setup success\r\n");
    }

    wiringPiSPISetup(0,90000000);
    //GPIO config
    DEV_GPIO_Mode(26, 1);
    DEV_GPIO_Mode(oled_rst, 1);
    DEV_GPIO_Mode(oled_dc,  1);
    DEV_GPIO_Mode(oled_cs,  1);


    OLED_RST(1);
    OLED_DC(1);
    OLED_CS(1);

    wiringPiSPISetupMode(0, 9000000, 0);


    OLED_CS(0);

    OLED_RST(0);
    delay(500);
    OLED_RST(1);
    delay(500);

    Write_Command(0xfd);	// command lock
    Write_Data(0x12);
    Write_Command(0xfd);	// command lock
    Write_Data(0xB1);

    Write_Command(0xae);	// display off
    Write_Command(0xa4); 	// Normal Display mode

    Write_Command(0x15);	//set column address
    Write_Data(0x00);     //column address start 00
    Write_Data(0x7f);     //column address end 95
    Write_Command(0x75);	//set row address
    Write_Data(0x00);     //row address start 00
    Write_Data(0x7f);     //row address end 63	

    Write_Command(0xB3);
    Write_Data(0xF1);

    Write_Command(0xCA);	
    Write_Data(0x7F);

    Write_Command(0xa0);  //set re-map & data format
    Write_Data(0x74);     //Horizontal address increment

    Write_Command(0xa1);  //set display start line
    Write_Data(0x00);     //start 00 line

    Write_Command(0xa2);  //set display offset
    Write_Data(0x00);

    Write_Command(0xAB);	
    Write_Command(0x01);	

    Write_Command(0xB4);	
    Write_Data(0xA0);	  
    Write_Data(0xB5);  
    Write_Data(0x55);    

    Write_Command(0xC1);	
    Write_Data(0xC8);	
    Write_Data(0x80);
    Write_Data(0xC0);

    Write_Command(0xC7);	
    Write_Data(0x0F);

    Write_Command(0xB1);	
    Write_Data(0x32);

    Write_Command(0xB2);	
    Write_Data(0xA4);
    Write_Data(0x00);
    Write_Data(0x00);

    Write_Command(0xBB);	
    Write_Data(0x17);

    Write_Command(0xB6);
    Write_Data(0x01);

    Write_Command(0xBE);
    Write_Data(0x05);

    Write_Command(0xA6);

    Clear_Screen();
    Write_Command(0xaf);	 //display on

    return 0;
}


// Draw a horizontal line ignoring any screen rotation.
void Draw_FastHLine(int16_t x, int16_t y, int16_t length) {
  // Bounds check
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
    return;
  // X bounds check
  if (x+length > SSD1351_WIDTH) {
    length = SSD1351_WIDTH - x - 1;
  }
  if (length < 0)
    return;
  // set location
  Write_Command(SSD1351_CMD_SETCOLUMN);
  Write_Data(x);
  Write_Data(x+length-1);
  Write_Command(SSD1351_CMD_SETROW);
  Write_Data(y);
  Write_Data(y);
  // fill!
  Write_Command(SSD1351_CMD_WRITERAM);

  for (uint16_t i=0; i < length; i++)
  {
    Write_Data(color_byte[0]);
    Write_Data(color_byte[1]);
  }
}
  
  // Draw a vertical line ignoring any screen rotation.
void Draw_FastVLine(int16_t x, int16_t y, int16_t length)  {
  // Bounds check
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
    return;
  // X bounds check
  if (y+length > SSD1351_HEIGHT) {
    length = SSD1351_HEIGHT - y - 1;
  }
  if (length < 0)
    return;

  // set location
  Write_Command(SSD1351_CMD_SETCOLUMN);
  Write_Data(x);
  Write_Data(x);
  Write_Command(SSD1351_CMD_SETROW);
  Write_Data(y);
  Write_Data(y+length-1);
  // fill!
  Write_Command(SSD1351_CMD_WRITERAM);  
    
  for (uint16_t i=0; i < length; i++)
  {
    Write_Data(color_byte[0]);
    Write_Data(color_byte[1]);
  }
}

void Draw_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
  // Update in subclasses if desired!
  if(x0 == x1)  {
    if(y0 > y1) swap(y0, y1);
    Draw_FastVLine(x0, y0, y1 - y0 + 1);
  } 
  else if(y0 == y1) {
    if(x0 > x1)
      swap(x0, x1);
    Draw_FastHLine(x0, y0, x1 - x0 + 1);
  }
  else
    Write_Line(x0, y0, x1, y1);
}


void Write_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1)  {
    
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    
  if (steep)  {
    swap(x0, y0);
    swap(x1, y1);
  }
  if (x0 > x1)  {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if(y0 < y1) {
    ystep = 1;
  } 
  else  {
    ystep = -1;
  }

  for(; x0<=x1; x0++) {
    if(steep)
      Draw_Pixel(y0, x0);
    else
      Draw_Pixel(x0, y0);
    err -= dy;
      
    if(err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}


// Draw a rectangle
void Draw_Rect(int16_t x, int16_t y, int16_t w, int16_t h) {
  Draw_FastHLine(x, y, w);
  Draw_FastHLine(x, y+h-1, w);
  Draw_FastVLine(x, y, h);
  Draw_FastVLine(x+w-1, y, h);
}


/**************************************************************************/
/*!
    @brief  Draws a filled rectangle using HW acceleration
*/
/**************************************************************************/
void Fill_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {

  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
  return;
  // Y bounds check
  if (y+h > SSD1351_HEIGHT) {
    h = SSD1351_HEIGHT - y - 1;
  }
  // X bounds check
  if (x+w > SSD1351_WIDTH)  {
    w = SSD1351_WIDTH - x - 1;
  }
  // set location
  Write_Command(SSD1351_CMD_SETCOLUMN);
  Write_Data(x);
  Write_Data(x+w-1);
  Write_Command(SSD1351_CMD_SETROW);
  Write_Data(y);
  Write_Data(y+h-1);
  // fill!
  Write_Command(SSD1351_CMD_WRITERAM);  
  
  for (uint16_t i=0; i < w*h; i++) {
    Write_Data(color_fill_byte[0]);
    Write_Data(color_fill_byte[1]);
  }
}


void Fill_Circle(int16_t x0, int16_t y0, int16_t r) {
  
  Draw_FastVLine(x0, y0-r, 2*r+1);
  FillCircle_Helper(x0, y0, r, 3, 0);
}


// Used to do circles and roundrects
void FillCircle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t corner, int16_t delta)  {

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while(x<y)  {
    if(f >= 0)  {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    if(corner & 0x1)  {
      Draw_FastVLine(x0+x, y0-y, 2*y+1+delta);
      Draw_FastVLine(x0+y, y0-x, 2*x+1+delta);
    }
    if(corner & 0x2)  {
      Draw_FastVLine(x0-x, y0-y, 2*y+1+delta);
      Draw_FastVLine(x0-y, y0-x, 2*x+1+delta);
    }
  }
}


// Draw a circle outline
void Draw_Circle(int16_t x0, int16_t y0, int16_t r) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  Draw_Pixel(x0  , y0+r);
  Draw_Pixel(x0  , y0-r);
  Draw_Pixel(x0+r, y0  );
  Draw_Pixel(x0-r, y0  );

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    Draw_Pixel(x0 + x, y0 + y);
    Draw_Pixel(x0 - x, y0 + y);
    Draw_Pixel(x0 + x, y0 - y);
    Draw_Pixel(x0 - x, y0 - y);
    Draw_Pixel(x0 + y, y0 + x);
    Draw_Pixel(x0 - y, y0 + x);
    Draw_Pixel(x0 + y, y0 - x);
    Draw_Pixel(x0 - y, y0 - x);
    }
}


// Draw a rounded rectangle
void Draw_RoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r) {
    // smarter version
    Draw_FastHLine(x+r  , y    , w-2*r); // Top
    Draw_FastHLine(x+r  , y+h-1, w-2*r); // Bottom
    Draw_FastVLine(x    , y+r  , h-2*r); // Left
    Draw_FastVLine(x+w-1, y+r  , h-2*r); // Right
    // draw four corners
    DrawCircle_Helper(x+r    , y+r    , r, 1);
    DrawCircle_Helper(x+w-r-1, y+r    , r, 2);
    DrawCircle_Helper(x+w-r-1, y+h-r-1, r, 4);
    DrawCircle_Helper(x+r    , y+h-r-1, r, 8);
}


void DrawCircle_Helper( int16_t x0, int16_t y0, int16_t r, uint8_t corner) {
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    if (corner & 0x4) {
      Draw_Pixel(x0 + x, y0 + y);
      Draw_Pixel(x0 + y, y0 + x);
    }
    if (corner & 0x2) {
      Draw_Pixel(x0 + x, y0 - y);
      Draw_Pixel(x0 + y, y0 - x);
    }
    if (corner & 0x8) {
      Draw_Pixel(x0 - y, y0 + x);
      Draw_Pixel(x0 - x, y0 + y);
    }
    if (corner & 0x1) {
      Draw_Pixel(x0 - y, y0 - x);
      Draw_Pixel(x0 - x, y0 - y);
    }
  }
}


// Draw a triangle
void Draw_Triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)  {
  Draw_Line(x0, y0, x1, y1);
  Draw_Line(x1, y1, x2, y2);
  Draw_Line(x2, y2, x0, y0);
}



