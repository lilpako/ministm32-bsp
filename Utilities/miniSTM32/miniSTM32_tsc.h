/*
 ******************************************************************************
 * miniSTM32_tsc.h
 * Brian
 * 14-July-2011
 * This file contains definitions for miniSTM32 touch screen controller
 ******************************************************************************
 */ 
  
#ifndef __MINISTM32_TSC_H
#define __MINISTM32_TSC_H

#ifdef __cplusplus
 extern "C" {
#endif 

typedef enum{
	TOUCH_IDLE = 0,
	TOUCH_DETECTED,
	TOUCH_MEASURED
} TouchStatus;

void TSC_Init(void);
void TSC_Routine(void);
void TSC_Calibration(void);
void TSC_WaitForTouch(void);
void TSC_SaveCalibration(void);
void TSC_CheckCalibration(void);
uint16_t TSC_GetDisplayX(uint16_t x_touch, uint16_t y_touch);
uint16_t TSC_GetDisplayY(uint16_t x_touch, uint16_t y_touch);

#ifdef __cplusplus
}
#endif
  
#endif /* __MINISTM32_TSC_H */
 
/*****END OF FILE****/
