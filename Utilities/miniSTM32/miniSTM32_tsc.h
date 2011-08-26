/*
 ******************************************************************************
 * miniSTM32_tsc.h
 * Brian
 * 14-July-2011
 * This file contains definitions for miniSTM32 touch screen controller
 ******************************************************************************
 */ 
  
#ifndef __MINISTM32_FLASH_H
#define __MINISTM32_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif 

typedef enum{
	TOUCH_IDLE = 0,
	TOUCH_DETECTED,
	TOUCH_X_MEASURED,
	TOUCH_Y_MEASURED,
	TOUCH_CALIBRATED
} TouchStatus;

void TSCInit(void);
/*
void TSCRead(void);
*/
void TSCCalibrate(void);
void TouchRoutine(void);


#ifdef __cplusplus
}
#endif
  
#endif /* __MINISTM32_FLASH_H */
 
/*****END OF FILE****/
