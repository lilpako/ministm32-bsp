/*******************************************************************************
 * @file    miniSTM32_tsc.c
 * @author  Brian
 * @version V0.2.0
 * @date    28-August-2011
 * @brief   This file provides functions to manage touch screen controller.
 * @verbatim
 *			Programming Model
 *			===================================
 *			// initialization
 *			TSC_Init();
 *			
 *			// check calibration : automatically brings up calibration  
 *			// routine(TSC_Calibration) if required.
 *			TSC_CheckCalibration();
 *
 *			// manual calibration
 *			TSC_Calibration();
 *
 *			// save calibration data
 *			TSC_SaveCalibration();
 *
 *			// wait for single touch event
 *			TSC_WaitForTouch();
 *
 *			// retrieve the value
 *			touch_x = uTSC_ValueX;
 *			touch_y = uTSC_ValueY;
 *
 *			// get screen coordinate from the touch value
 *			screen_x = TSC_GetDisplayX(touch_x, touch_y);
 *			screen_y = TSC_GetDisplayY(touch_x, touch_y);
 *
 *			// clear the flag to make ready for the next touch event
 *			TSC_Status = TOUCH_IDLE;
 *
 *			// run in the loop - continuous measurement
 *			while(1)
 *			{
 *				// touch routine should be called regularly
 *				TSC_Routine();
 *
 *				if(TSC_Status == TOUCH_MEASURED)
 *				{
 *					// get screen coordinate from the touch value
 *					screen_x = TSC_GetDisplayX(TSC_ValueX, TSC_ValueY);
 *					screen_y = TSC_GetDisplayY(TSC_ValueX, TSC_ValueY);
 *
 *					// clear the flag to catch the new touch event
 *					TSC_Status = TOUCH_IDLE;
 *				}
 *			}
 *			 
 *			// BE SURE TO REMEMBER 'uTSC_Delay' should be decreased by one
 *			// in every one millisecond. Easist way is to put the following
 *			// code in the one millisecond SysTick_Handler.
 *			void SysTick_Handler(void)
 *			{
 *				if(uTSC_Delay) uTSC_Delay--;
 *			}
 *
 */ 
  
#include "miniSTM32.h"
#include "miniSTM32_tsc.h"
#include "miniSTM32_lcd.h"
#include "miniSTM32_flash.h"

#define TSC_CMD_DUMMY			0x5A
/* 8bit, always on, differential measurement
#define TSC_CMD_MEASURE_X		0x9B	
#define TSC_CMD_MEASURE_Y		0xDB
*/
/* 8bit, power save, differential measurement
#define TSC_CMD_MEASURE_X		0x98	
#define TSC_CMD_MEASURE_Y		0xD8
*/
/* 12bit, power save, differential measurement */
#define TSC_CMD_MEASURE_X		0x90	
#define TSC_CMD_MEASURE_Y		0xD0
/* 12bit, always on, differential measurement
#define TSC_CMD_MEASURE_X		0x93	
#define TSC_CMD_MEASURE_Y		0xD3
*/

#define TSC_RAW_X_MAX			1950
#define TSC_RAW_X_MIN			10
#define TSC_RAW_Y_MAX			1950
#define TSC_RAW_Y_MIN			10

/* calibration parameters */
#define CURSOR_SIZE				10
#define RESCALE_FACTOR			1000000
#define CALPARAM_ID				0xA5A5A5A5

int32_t CParam[7] = {0};

/* some macros */
#define MED(x,y,z)				(x>y ?	(x>z ? (y>z ? y : z): x) : \
										(y>z ? (x>z ? x : z): y))
#define TSC_DELAY(x)			{uTSC_Delay = x; while(uTSC_Delay);}

volatile TouchStatus TSC_Status = TOUCH_IDLE;
volatile uint16_t uTSC_ValueX = 0;
volatile uint16_t uTSC_ValueY = 0;
volatile uint16_t uTSC_Delay = 0;

uint16_t TSC_ReadX(void);
uint16_t TSC_ReadY(void);

void TSC_Init(void)
{
	/* initialize cs and interrupt pins */
	MCU_TSCPortInit();

	/* deselect the chip */
	MAIN_TSC_CS_HIGH();

	/* initialize the SPI module */
	MCU_SPI1Init(SPI_MODE_TOUCH);
}

void TSC_Routine(void)
{
	uint16_t u16Val1, u16Val2, u16Val3, u16Val4, u16Val5, u16Val6;

	/* measuring actual x, y values : takes about 20msec */
	if(TSC_Status == TOUCH_DETECTED)
	{
		/* skip initial transient */
		TSC_DELAY(15);
		/* read x values */
		u16Val1 = TSC_ReadX();
		/* after some interval */
		TSC_DELAY(5);
		/* then read y values */
		u16Val4 = TSC_ReadY();

		/* alternatively 3 times*/
		TSC_DELAY(5);
		u16Val2 = TSC_ReadX();
		TSC_DELAY(5);
		u16Val5 = TSC_ReadY();

		TSC_DELAY(5);
		u16Val3 = TSC_ReadX();
		TSC_DELAY(5);
		u16Val6 = TSC_ReadY();

		/* taking the median value is good measure in this case */
		uTSC_ValueX = MED(u16Val1, u16Val2, u16Val3);
		uTSC_ValueY = MED(u16Val4, u16Val5, u16Val6);

		/* filter out garbage values */
		if((uTSC_ValueX > TSC_RAW_X_MAX) || (uTSC_ValueX < TSC_RAW_X_MIN) ||
			(uTSC_ValueY > TSC_RAW_Y_MAX) || (uTSC_ValueY < TSC_RAW_Y_MIN)) {

			/* discard garbage and start again */
			TSC_Status = TOUCH_IDLE;
		}
		else{
			/* proceed to the next step */
			TSC_Status = TOUCH_MEASURED;
		}
	}
}

/**
  * @brief  Returns the display y-axis coordinate corresponding to the touch.
  *         X and Y are inverted because the display is meant in Landscape
  * @param  x_touch: X coordinate of the Touch Panel
  * @param  y_touch: Y coordinate of the Touch Panel
  * @retval Xd: Coordinate X of the LCD Panel (X-axis Coordinate)
  */
uint16_t TSC_GetDisplayX(uint16_t x_touch, uint16_t y_touch)
{
  uint16_t Xd;
  float temp;

  temp = (CParam[1] * x_touch + CParam[2] * y_touch + CParam[3]) \
	/ RESCALE_FACTOR;
  Xd = (uint16_t)(temp);

  if (Xd > 60000)
  {
    /* this to avoid negative value */
    Xd = 0;
  }

  return Xd;
}

/**
  * @brief  Returns the display x-axis coordinate corresponding to the touch.
  *         X and Y are inverted because the display is meant in Landscape
  * @param  x_touch: X coordinate of the Touch Panel
  * @param  y_touch: Y coordinate of the Touch Panel
  * @retval Yd: Coordinate X of the LCD Panel (Y-axis Coordinate)
  */
uint16_t TSC_GetDisplayY(uint16_t x_touch, uint16_t y_touch)
{
  uint16_t Yd;
  float temp;

  temp = (CParam[4] * x_touch + CParam[5] * y_touch + CParam[6]) \
	/ RESCALE_FACTOR;
  Yd = (uint16_t)(temp);

  if (Yd > 60000)
  {
    /*  this to avoid negative value */
    Yd = 0;
  }

  return Yd;
}

void TSC_WaitForTouch(void)
{
	/* reset the state machine */
	TSC_Status = TOUCH_IDLE;
	/* wait for the specific state */
	while(TSC_Status != TOUCH_MEASURED) TSC_Routine();
}

void TSC_Calibration(void)
{
	LCD_BacklightOn();

	uint32_t coordinate_X1 = 0, coordinate_X2 = 0, coordinate_X3 = 0;
	uint32_t coordinate_X4 = 0, coordinate_X5 = 0;
	uint32_t coordinate_Y1 = 0, coordinate_Y2 = 0, coordinate_Y3 = 0;
	uint32_t coordinate_Y4 = 0, coordinate_Y5 = 0;
	uint16_t Xd1 = (LCD_WIDTH/2), Xd2 = (LCD_WIDTH/5), Xd3 = 4 * (LCD_WIDTH/5);
	uint16_t Xd4 = 4 * (LCD_WIDTH/5), Xd5 = (LCD_WIDTH / 5);
	uint16_t Yd1 = (LCD_HEIGHT/2), Yd2 = (LCD_HEIGHT/5), Yd3 = (LCD_HEIGHT/5);
	uint16_t Yd4 = 4 * (LCD_HEIGHT/5), Yd5 = 4 * (LCD_HEIGHT/5);
	double A = 0., B = 0., C = 0., D = 0., E = 0., F = 0.;
	double d = 0., dx1 = 0., dx2 = 0., dx3 = 0., dy1 = 0., dy2 = 0., dy3 = 0.;
	uint32_t X2_1 = 0, X2_2 = 0, X2_3 = 0, X2_4 = 0, X2_5 = 0;
	uint32_t Y2_1 = 0, Y2_2 = 0, Y2_3 = 0, Y2_4 = 0, Y2_5 = 0;
	uint32_t XxY_1 = 0, XxY_2 = 0, XxY_3 = 0, XxY_4 = 0, XxY_5 = 0;
	uint32_t XxXd_1 = 0, XxXd_2 = 0, XxXd_3 = 0, XxXd_4 = 0, XxXd_5 = 0;
	uint32_t YxXd_1 = 0, YxXd_2 = 0, YxXd_3 = 0, YxXd_4 = 0, YxXd_5 = 0;
	uint32_t XxYd_1 = 0, XxYd_2 = 0, XxYd_3 = 0, XxYd_4 = 0, XxYd_5 = 0;
	uint32_t YxYd_1 = 0, YxYd_2 = 0, YxYd_3 = 0, YxYd_4 = 0, YxYd_5 = 0;
	uint32_t alfa = 0, beta = 0, chi = 0, Kx = 0, Ky = 0, Lx = 0, Ly = 0;
	uint16_t epsilon = 0, fi = 0, Mx = 0, My = 0;

	/* center */

	LCD_DrawLine((LCD_WIDTH/2) - CURSOR_SIZE, (LCD_HEIGHT/2), \
		(LCD_WIDTH/2) + CURSOR_SIZE, (LCD_HEIGHT/2), 5, 255,150,40);
	LCD_DrawLine((LCD_WIDTH/2), (LCD_HEIGHT/2) - CURSOR_SIZE, \
		(LCD_WIDTH/2), (LCD_HEIGHT/2) + CURSOR_SIZE, 5, 255,150,40);

	TSC_WaitForTouch();

	coordinate_X1 = uTSC_ValueX;
	coordinate_Y1 = uTSC_ValueY;

	LCD_Clear();

	/* upper left corner */
	
	LCD_DrawLine((LCD_WIDTH/5) - CURSOR_SIZE, (LCD_HEIGHT/5), \
		(LCD_WIDTH/5) + CURSOR_SIZE, (LCD_HEIGHT/5), 5, 255,150,40);
	LCD_DrawLine((LCD_WIDTH/5), (LCD_HEIGHT/5) - CURSOR_SIZE, \
		(LCD_WIDTH/5), (LCD_HEIGHT/5) + CURSOR_SIZE, 5, 255,150,40);

	TSC_WaitForTouch();

	coordinate_X2 = uTSC_ValueX;
	coordinate_Y2 = uTSC_ValueY;

	LCD_Clear();

	/* upper right corner*/
	
	LCD_DrawLine((4*LCD_WIDTH/5) - CURSOR_SIZE, (LCD_HEIGHT/5), \
		(4*LCD_WIDTH/5) + CURSOR_SIZE, (LCD_HEIGHT/5), 5, 255,150,40);
	LCD_DrawLine((4*LCD_WIDTH/5), (LCD_HEIGHT/5) - CURSOR_SIZE, \
		(4*LCD_WIDTH/5), (LCD_HEIGHT/5) + CURSOR_SIZE, 5, 255,150,40);

	TSC_WaitForTouch();

	coordinate_X3 = uTSC_ValueX;
	coordinate_Y3 = uTSC_ValueY;

	LCD_Clear();

	/* lower right corner */
	
	LCD_DrawLine((4*LCD_WIDTH/5) - CURSOR_SIZE, (4*LCD_HEIGHT/5), \
		(4*LCD_WIDTH/5) + CURSOR_SIZE, (4*LCD_HEIGHT/5), 5, 255,150,40);
	LCD_DrawLine((4*LCD_WIDTH/5), (4*LCD_HEIGHT/5) - CURSOR_SIZE, \
		(4*LCD_WIDTH/5), (4*LCD_HEIGHT/5) + CURSOR_SIZE, 5, 255,150,40);

	TSC_WaitForTouch();

	coordinate_X4 = uTSC_ValueX;
	coordinate_Y4 = uTSC_ValueY;

	LCD_Clear();

	/* lower left corner */
	
	LCD_DrawLine((LCD_WIDTH/5) - CURSOR_SIZE, (4*LCD_HEIGHT/5), \
		(LCD_WIDTH/5) + CURSOR_SIZE, (4*LCD_HEIGHT/5), 5, 255,150,40);
	LCD_DrawLine((LCD_WIDTH/5), (4*LCD_HEIGHT/5) - CURSOR_SIZE, \
		(LCD_WIDTH/5), (4*LCD_HEIGHT/5) + CURSOR_SIZE, 5, 255,150,40);

	TSC_WaitForTouch();

	coordinate_X5 = uTSC_ValueX;
	coordinate_Y5 = uTSC_ValueY;

	LCD_Clear();

	X2_1 = (coordinate_X1 * coordinate_X1);
	X2_2 = (coordinate_X2 * coordinate_X2);
	X2_3 = (coordinate_X3 * coordinate_X3);
	X2_4 = (coordinate_X4 * coordinate_X4);
	X2_5 = (coordinate_X5 * coordinate_X5);
	
	Y2_1 = (coordinate_Y1 * coordinate_Y1);
	Y2_2 = (coordinate_Y2 * coordinate_Y2);
	Y2_3 = (coordinate_Y3 * coordinate_Y3);
	Y2_4 = (coordinate_Y4 * coordinate_Y4);
	Y2_5 = (coordinate_Y5 * coordinate_Y5);
	
	XxY_1 = (coordinate_X1 * coordinate_Y1);
	XxY_2 = (coordinate_X2 * coordinate_Y2);
	XxY_3 = (coordinate_X3 * coordinate_Y3);
	XxY_4 = (coordinate_X4 * coordinate_Y4);
	XxY_5 = (coordinate_X5 * coordinate_Y5);
	
	XxXd_1 = ( coordinate_X1 * Xd1 );
	XxXd_2 = ( coordinate_X2 * Xd2 );
	XxXd_3 = ( coordinate_X3 * Xd3 );
	XxXd_4 = ( coordinate_X4 * Xd4 );
	XxXd_5 = ( coordinate_X5 * Xd5 );
	
	YxXd_1 = ( coordinate_Y1 * Xd1 );
	YxXd_2 = ( coordinate_Y2 * Xd2 );
	YxXd_3 = ( coordinate_Y3 * Xd3 );
	YxXd_4 = ( coordinate_Y4 * Xd4 );
	YxXd_5 = ( coordinate_Y5 * Xd5 );
	
	XxYd_1 = ( coordinate_X1 * Yd1 );
	XxYd_2 = ( coordinate_X2 * Yd2 );
	XxYd_3 = ( coordinate_X3 * Yd3 );
	XxYd_4 = ( coordinate_X4 * Yd4 );
	XxYd_5 = ( coordinate_X5 * Yd5 );
	
	YxYd_1 = ( coordinate_Y1 * Yd1 );
	YxYd_2 = ( coordinate_Y2 * Yd2 );
	YxYd_3 = ( coordinate_Y3 * Yd3 );
	YxYd_4 = ( coordinate_Y4 * Yd4 );
	YxYd_5 = ( coordinate_Y5 * Yd5 );
	
	alfa = X2_1 + X2_2 + X2_3 + X2_4 + X2_5;
	beta = Y2_1 + Y2_2 + Y2_3 + Y2_4 + Y2_5;
	chi = XxY_1 + XxY_2 + XxY_3 + XxY_4 + XxY_5;
	epsilon = coordinate_X1 + coordinate_X2 + coordinate_X3 + coordinate_X4 + coordinate_X5;
	fi = coordinate_Y1 + coordinate_Y2 + coordinate_Y3 + coordinate_Y4 + coordinate_Y5;
	Kx = XxXd_1 + XxXd_2 + XxXd_3 + XxXd_4 + XxXd_5;
	Ky = XxYd_1 + XxYd_2 + XxYd_3 + XxYd_4 + XxYd_5;
	Lx = YxXd_1 + YxXd_2 + YxXd_3 + YxXd_4 + YxXd_5;
	Ly = YxYd_1 + YxYd_2 + YxYd_3 + YxYd_4 + YxYd_5;
	Mx = Xd1 + Xd2 + Xd3 + Xd4 + Xd5;
	My = Yd1 + Yd2 + Yd3 + Yd4 + Yd5;

	d = 5 * ( ((double)alfa * beta) - ((double)chi * chi) ) + 2 * ((double)chi * epsilon * fi) - ((double)alfa * fi * fi ) - ( (double)beta * epsilon * epsilon );
	dx1 = 5 * ( ((double)Kx * beta) - ((double)Lx * chi) ) + ((double)fi * ( ((double)Lx * epsilon) - ((double)Kx * fi) )) + ((double)Mx * ( ((double)chi * fi) - ((double)beta * epsilon) ));
	dx2 = 5 * ( ((double)Lx * alfa) - ((double)Kx * chi) ) + ((double)epsilon * ( ((double)Kx * fi) - ((double)Lx * epsilon) )) + ((double)Mx * ( ((double)chi * epsilon) - ((double)alfa * fi) ));
	dx3 = ((double)Kx * ( ((double)chi * fi) - ((double)beta * epsilon) )) + ((double)Lx * ( ((double)chi * epsilon) - ((double)alfa * fi) )) + ((double)Mx * ( ((double)alfa * beta) - ((double)chi * chi) ));
	dy1 = 5 * ( ((double)Ky * beta) - ((double)Ly * chi) ) + ((double)fi * ( ((double)Ly * epsilon) - ((double)Ky * fi) )) + ((double)My * ( ((double)chi * fi) - ((double)beta * epsilon) ));
	dy2 = 5 * ( ((double)Ly * alfa) - ((double)Ky * chi) ) + ((double)epsilon * ( ((double)Ky * fi) - ((double)Ly * epsilon) )) + ((double)My * ( ((double)chi * epsilon) - ((double)alfa * fi) ));
	dy3 = ((double)Ky * ( ((double)chi * fi) - ((double)beta * epsilon) )) + ((double)Ly * ( ((double)chi * epsilon) - ((double)alfa * fi) )) + ((double)My * ( ((double)alfa * beta) - ((double)chi * chi) ));
	
	A = dx1 / d;
	B = dx2 / d;
	C = dx3 / d;
	D = dy1 / d;
	E = dy2 / d;
	F = dy3 / d;
	
	/* convert double precision variables to int32_t */
	CParam[1] = (int32_t)(A * RESCALE_FACTOR);
	CParam[2] = (int32_t)(B * RESCALE_FACTOR);
	CParam[3] = (int32_t)(C * RESCALE_FACTOR);
	CParam[4] = (int32_t)(D * RESCALE_FACTOR);
	CParam[5] = (int32_t)(E * RESCALE_FACTOR);
	CParam[6] = (int32_t)(F * RESCALE_FACTOR);

	/* save the variables */
	TSC_SaveCalibration();

	LCD_BacklightOff();

}

void TSC_SaveCalibration(void)
{
	uint32_t Addr = SFLASH_CAPACITY - SFLASH_ERASE_BLOCK_SIZE; 

	SFL_Init();

	SFL_Erase(EBSIZE_4KB, Addr);
	CParam[0] = CALPARAM_ID;
	SFL_WriteBuffer((uint8_t*)CParam, Addr, (uint16_t)(sizeof(CParam)));

	// change spi setting again
	MCU_SPI1SetMode(SPI_MODE_TOUCH);
}

void TSC_CheckCalibration(void)
{
	uint32_t Addr = SFLASH_CAPACITY - SFLASH_ERASE_BLOCK_SIZE; 

	SFL_Init();

	SFL_ReadBuffer((uint8_t*)CParam, Addr, (uint16_t)(sizeof(CParam)));

	// change spi setting again
	MCU_SPI1SetMode(SPI_MODE_TOUCH);

	if(CParam[0] != CALPARAM_ID)
		TSC_Calibration();
}

uint16_t TSC_ReadX(void)
{
	uint16_t u16First, u16Second;

	/* select the chip */
	MAIN_TSC_CS_LOW();
	/* send the command byte */
	MCU_SPI1SendByte(TSC_CMD_MEASURE_X);
	/* read the first byte */
	u16First = (uint16_t)MCU_SPI1SendByte(TSC_CMD_DUMMY);
	/* then read the second byte */
	u16Second = (uint16_t)MCU_SPI1SendByte(TSC_CMD_DUMMY);
	/* deselect the chip */
	MAIN_TSC_CS_HIGH();

	/* construct 12bit data */
	u16First = u16First<<4;
	u16Second = u16Second>>4;
	u16First = u16First + u16Second;

	return u16First;
}

uint16_t TSC_ReadY(void)
{
	uint16_t u16First, u16Second;

	/* select the chip */
	MAIN_TSC_CS_LOW();
	/* send the command byte */
	MCU_SPI1SendByte(TSC_CMD_MEASURE_Y);
	/* read the first byte */
	u16First = (uint16_t)MCU_SPI1SendByte(TSC_CMD_DUMMY);
	/* then read the second byte */
	u16Second = (uint16_t)MCU_SPI1SendByte(TSC_CMD_DUMMY);
	/* deselect the chip */
	MAIN_TSC_CS_HIGH();

	/* construct 12bit data */
	u16First = u16First<<4;
	u16Second = u16Second>>4;
	u16First = u16First + u16Second;

	return u16First;
}

/* END OF FILE */

