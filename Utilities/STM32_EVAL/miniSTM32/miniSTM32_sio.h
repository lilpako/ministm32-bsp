/**
  ******************************************************************************
  * miniSTM32_sio.h
  * Brian
  * V0.1.0
  * 06-July-2011
  * This file contains definitions for the simple I/O extension board
  * 
  * Connection pinout
  *
  *		miniSTM32				SIO
  *		1 (3V)					1 (3V3)
  *		2 (PE2)					2 (BTN01)
  *		3 (PE3)					3 (BTN02)
  *		5 (PE4)					4 (LED01)
  *		10 (PB0/TIM3_CH3)		5 (LED02)
  *		13 (PA1/TIM2_CH2)		6 (PIEZO)
  *		9 (PC1/ADC123_IN11)		7 (POTENTIOMETER)
  *		8 (GND)					8 (GND)
  *
  ******************************************************************************
  */ 
  
#ifndef __MINISTM32_SIO_H
#define __MINISTM32_SIO_H

#ifdef __cplusplus
 extern "C" {
#endif 

/****************************************************************************
  * MINISTM32 Exported Functions : Depends on each extension board
  */

/**
  * Simpile I/O extension board consists of 
  *		- Two push button switch input (floating)
  *		- Two GPIO controlled LED
  *		- One PWM controlled piezo transducer
  *		- One potentiometer input
  */
#define SIO_BTN1		1
#define SIO_BTN2		2
#define SIO_LED1		1
#define SIO_LED2		2

#define MIN_PIEZO_FREQ			(1000)
#define MAX_PIEZO_FREQ			(15000)

void miniSTM32_SIO_BoardInit(void);
void miniSTM32_SIO_LEDControl(uint16_t Led, uint16_t Flag);
void miniSTM32_SIO_LEDToggle(uint16_t Led);
uint16_t miniSTM32_SIO_LEDGetStatus(uint16_t Led);
/* maybe I can do it later
void miniSTM32_SIO_LEDPWMControl(uint16_t Led, uint16_t Duty);
*/
uint16_t miniSTM32_SIO_ButtonGetState(uint16_t Button);
void miniSTM32_SIO_PiezoControl(uint16_t Duty);
uint16_t miniSTM32_SIO_POTGetValue(void);


#ifdef __cplusplus
}
#endif
  
#endif /* __MINISTM32_SIO_H */
 
/* END OF FILE */

