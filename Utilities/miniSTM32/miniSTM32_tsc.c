/*******************************************************************************
 * @file    miniSTM32_tsc.c
 * @author  Brian
 * @version V0.1.0
 * @date    14-August-2011
 * @brief   This file provides:
 *         - set of firmware functions to manage touch screen controller
 *			 
 */ 
  
#include "miniSTM32.h"

/* 8bit, always on, differential measurement */
#define TSC_CMD_MEASURE_X		0x9B	
#define TSC_CMD_MEASURE_Y		0xDB
#define TSC_CMD_DUMMY			0x5A

volatile uint16_t TSC_Value_X;
volatile uint16_t TSC_Value_Y;


void TSCInit(void)
{
	/* initialize cs and int pins */
	mSTM_TSCPortInit();

	/* deselect the chip */
	MAIN_TSC_CS_HIGH();

	/* initialize the SPI module */
	mSTM_SPIInit(SPI_MODE_TOUCH);
}

uint16_t TSCRead(void)
{
}

uint16_t TSCCalibrate(void)
{
}

void mSTM_TSCRead_X(void)
{
	uint16_t u16Value;

	MAIN_TSC_CS_LOW();
	mSTM_SPISendByte(TSC_CMD_MEASURE_X);
	u16Value = (uint16_t)mSTM_SPISendByte(TSC_CMD_DUMMY);
	MAIN_TSC_CS_HIGH();

	return u16Value;
}

void mSTM_TSCRead_Y(void)
{
	uint16_t u16Value;

	MAIN_TSC_CS_LOW();
	mSTM_SPISendByte(TSC_CMD_MEASURE_Y);
	u16Value = (uint16_t)mSTM_SPISendByte(TSC_CMD_DUMMY);
	MAIN_TSC_CS_HIGH();

	return u16Value;
}
/* END OF FILE */

