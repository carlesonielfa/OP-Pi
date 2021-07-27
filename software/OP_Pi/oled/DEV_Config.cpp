/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V2.0
* | Date        :   2019-07-08
* | Info        :   Basic version
*
******************************************************************************/
#include "DEV_Config.h"

uint32_t fd;
/*****************************************
                GPIO
*****************************************/
void DEV_Digital_Write(UWORD Pin, UBYTE Value)
{
    digitalWrite(Pin, Value);
}

UBYTE DEV_Digital_Read(UWORD Pin)
{
    UBYTE Read_value = 0;
    Read_value = digitalRead(Pin);

    return Read_value;
}

void DEV_GPIO_Mode(UWORD Pin, UWORD Mode)
{
    if(Mode == 0 || Mode == INPUT){
        pinMode(Pin, INPUT);
        pullUpDnControl(Pin, PUD_UP);
    }else{ 
        pinMode(Pin, OUTPUT);
        // printf (" %d OUT \r\n",Pin);
    }
}

/**
 * delay x ms
**/
void DEV_Delay_ms(UDOUBLE xms)
{
    delay(xms);
}


/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_ModuleInit(void)
{

    //if(wiringPiSetup() < 0)//use wiringpi Pin number table  
    if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
        printf("set wiringPi lib failed	!!! \r\n");
        return 1;
    } else {
        printf("set wiringPi lib success  !!! \r\n");
    }     
    
    wiringPiSPISetup(0,90000000);
	// wiringPiSPISetupMode(0, 90000000, 0);

    return 0;
}

void DEV_SPI_WriteByte(uint8_t Value)
{
    wiringPiSPIDataRW(0,&Value,1);
}

void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len)
{
    wiringPiSPIDataRW(0, pData, Len);
}


/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void DEV_ModuleExit(void)
{

}

