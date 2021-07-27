#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_
/***********************************************************************************************************************
			------------------------------------------------------------------------
			|\\\																///|
			|\\\					Hardware interface							///|
			------------------------------------------------------------------------
***********************************************************************************************************************/

#include <wiringPi.h>
#include <wiringPiSPI.h>


#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>


/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t


/*------------------------------------------------------------------------------------------------------*/


uint8_t DEV_ModuleInit(void);
void    DEV_ModuleExit(void);

void I2C_Write_Byte(uint8_t value, uint8_t Cmd);

void DEV_GPIO_Mode(UWORD Pin, UWORD Mode);
void DEV_Digital_Write(UWORD Pin, UBYTE Value);
UBYTE DEV_Digital_Read(UWORD Pin);
void DEV_Delay_ms(UDOUBLE xms);

void DEV_SPI_WriteByte(UBYTE Value);
void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len);

#endif
