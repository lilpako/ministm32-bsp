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
#include "miniSTM32_tsc.h"

#define TSC_CMD_DUMMY			0x5A
/* 8bit, always on, differential measurement */
//#define TSC_CMD_MEASURE_X		0x9B	
//#define TSC_CMD_MEASURE_Y		0xDB
/* 8bit, power down, differential measurement */
//#define TSC_CMD_MEASURE_X		0x98	
//#define TSC_CMD_MEASURE_Y		0xD8
/* 12bit, power down, differential measurement */
//#define TSC_CMD_MEASURE_X		0x90	
//#define TSC_CMD_MEASURE_Y		0xD0
/* 12bit, always on, differential measurement */
#define TSC_CMD_MEASURE_X		0x93	
#define TSC_CMD_MEASURE_Y		0xD3
#define TSC_RAW_X_MAX			1950
#define TSC_RAW_Y_MIN			2

volatile TouchStatus TStatus = TOUCH_IDLE;
volatile uint16_t TSC_Value_X;
volatile uint16_t TSC_Value_Y;

uint16_t mSTM_TSCRead_X(void);
uint16_t mSTM_TSCRead_Y(void);

extern void MsecDelay( uint16_t u16Delay );

void TSCInit(void)
{
	/* initialize cs and int pins */
	mSTM_TSCPortInit();

	/* deselect the chip */
	MAIN_TSC_CS_HIGH();

	/* initialize the SPI module */
	mSTM_SPIInit(SPI_MODE_TOUCH);
}

void TouchRoutine(void)
{
	if(TStatus == TOUCH_DETECTED)
	{
		// measure x
		TSC_Value_X = mSTM_TSCRead_X();
		MsecDelay(1);
		TStatus = TOUCH_X_MEASURED;
	}
	else if(TStatus == TOUCH_X_MEASURED)
	{
		// measure y
		TSC_Value_Y = mSTM_TSCRead_Y();

		// filter out garbage values
		if((TSC_Value_X > TSC_RAW_X_MAX) ||
			(TSC_Value_Y < TSC_RAW_Y_MIN)) {
			TStatus = TOUCH_IDLE;
		}
		else{
			TStatus = TOUCH_Y_MEASURED;
		}
	}
	else if(TStatus == TOUCH_Y_MEASURED)
	{
		// calibrate
		TStatus = TOUCH_CALIBRATED;
	}
}

void TSCRead(void)
{
	TSC_Value_X = mSTM_TSCRead_X();

	TSC_Value_Y = mSTM_TSCRead_Y();
	TSC_Value_Y = mSTM_TSCRead_Y();

/*
	uint16_t u16First, u16Second;

	MAIN_TSC_CS_LOW();

	mSTM_SPISendByte(TSC_CMD_MEASURE_X);

	u16First = (uint16_t)mSTM_SPISendByte(TSC_CMD_DUMMY);
	u16First = u16First<<4;
	u16Second = (uint16_t)mSTM_SPISendByte(TSC_CMD_MEASURE_Y);
	u16Second = u16Second>>4;

	TSC_Value_X = u16First + u16Second;

	u16First = (uint16_t)mSTM_SPISendByte(TSC_CMD_DUMMY);
	u16First = u16First<<4;
	u16Second = (uint16_t)mSTM_SPISendByte(TSC_CMD_DUMMY);
	u16Second = u16Second>>4;

	TSC_Value_Y = u16First + u16Second;

	MAIN_TSC_CS_HIGH();

*/
}

void TSCCalibrate(void)
{
}

uint16_t mSTM_TSCRead_X(void)
{
	uint16_t u16First, u16Second;

	MAIN_TSC_CS_LOW();
	mSTM_SPISendByte(TSC_CMD_MEASURE_X);
	u16First = (uint16_t)mSTM_SPISendByte(TSC_CMD_DUMMY);
	u16Second = (uint16_t)mSTM_SPISendByte(TSC_CMD_DUMMY);
	MAIN_TSC_CS_HIGH();

	u16First = u16First<<4;
	u16Second = u16Second>>4;
	u16First = u16First + u16Second;

	return u16First;
}

uint16_t mSTM_TSCRead_Y(void)
{
	uint16_t u16First, u16Second;

	MAIN_TSC_CS_LOW();
	mSTM_SPISendByte(TSC_CMD_MEASURE_Y);
	u16First = (uint16_t)mSTM_SPISendByte(TSC_CMD_DUMMY);
	u16Second = (uint16_t)mSTM_SPISendByte(TSC_CMD_DUMMY);
	MAIN_TSC_CS_HIGH();

	u16First = u16First<<4;
	u16Second = u16Second>>4;
	u16First = u16First + u16Second;

	return u16First;
}
/* END OF FILE */

