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
#define TSC_CMD_MEASURE_X		0x90	
#define TSC_CMD_MEASURE_Y		0xD0
/* 12bit, always on, differential measurement */
//#define TSC_CMD_MEASURE_X		0x93	
//#define TSC_CMD_MEASURE_Y		0xD3

#define TSC_RAW_X_MAX			1950
#define TSC_RAW_X_MIN			10
#define TSC_RAW_Y_MAX			1950
#define TSC_RAW_Y_MIN			10

#define MED(x,y,z)				(x>y ?	(x>z ? (y>z ? y : z): x) : \
										(y>z ? (x>z ? x : z): y))

volatile TouchStatus TStatus = TOUCH_IDLE;
volatile uint16_t TSC_Value_X;
volatile uint16_t TSC_Value_Y;

uint16_t TSC_ReadX(void);
uint16_t TSC_ReadY(void);

extern void MsecDelay( uint16_t u16Delay );

void TSCInit(void)
{
	/* initialize cs and int pins */
	MCU_TSCPortInit();

	/* deselect the chip */
	MAIN_TSC_CS_HIGH();

	/* initialize the SPI module */
	MCU_SPI1Init(SPI_MODE_TOUCH);
}

void TouchRoutine(void)
{
	uint16_t u16Val1, u16Val2, u16Val3, u16Val4, u16Val5, u16Val6;

	/* measuring actual x, y values : takes about 20msec */
	if(TStatus == TOUCH_DETECTED)
	{
		/* pass initial transient */
		MsecDelay(10);
		/* read x values */
		u16Val1 = TSC_ReadX();
		/* with some interval */
		MsecDelay(2);
		/* then read y values */
		u16Val4 = TSC_ReadY();
		/* alternatively 3 times*/
		MsecDelay(2);
		u16Val2 = TSC_ReadX();
		MsecDelay(2);
		u16Val5 = TSC_ReadY();
		MsecDelay(2);
		u16Val3 = TSC_ReadX();
		MsecDelay(2);
		u16Val6 = TSC_ReadY();

		/* take median value */
		TSC_Value_X = MED(u16Val1, u16Val2, u16Val3);
		TSC_Value_Y = MED(u16Val4, u16Val5, u16Val6);

		/* filter out garbage values */
		if((TSC_Value_X > TSC_RAW_X_MAX) || (TSC_Value_X < TSC_RAW_X_MIN) ||
			(TSC_Value_Y > TSC_RAW_Y_MAX) || (TSC_Value_Y < TSC_RAW_Y_MIN)) {

			/* discard garbage and start again */
			TStatus = TOUCH_IDLE;
		}
		else{
			/* proceed to the next step */
			TStatus = TOUCH_MEASURED;
		}
	}
	/* calibrate the value */
	else if(TStatus == TOUCH_MEASURED)
	{
		TStatus = TOUCH_CALIBRATED;
	}
}


void TSCCalibrate(void)
{
}

uint16_t TSC_ReadX(void)
{
	uint16_t u16First, u16Second;

	MAIN_TSC_CS_LOW();
	MCU_SPI1SendByte(TSC_CMD_MEASURE_X);
	u16First = (uint16_t)MCU_SPI1SendByte(TSC_CMD_DUMMY);
	u16Second = (uint16_t)MCU_SPI1SendByte(TSC_CMD_DUMMY);
	MAIN_TSC_CS_HIGH();

	u16First = u16First<<4;
	u16Second = u16Second>>4;
	u16First = u16First + u16Second;

	return u16First;
}

uint16_t TSC_ReadY(void)
{
	uint16_t u16First, u16Second;

	MAIN_TSC_CS_LOW();
	MCU_SPI1SendByte(TSC_CMD_MEASURE_Y);
	u16First = (uint16_t)MCU_SPI1SendByte(TSC_CMD_DUMMY);
	u16Second = (uint16_t)MCU_SPI1SendByte(TSC_CMD_DUMMY);
	MAIN_TSC_CS_HIGH();

	u16First = u16First<<4;
	u16Second = u16Second>>4;
	u16First = u16First + u16Second;

	return u16First;
}
/* END OF FILE */

