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

typedef enum
{
	SIO_LED1 = 0,
	SIO_LED2 = 1
} SIO_LED_TypeDef;

typedef enum
{
	SIO_BTN1 = 0,
	SIO_BTN2 = 1
} SIO_Button_TypeDef;


#ifndef SIO_DEFINITION_OVERRIDE
#define SIO_BTN1_GPIO_PIN		GPIO_Pin_2
#define SIO_BTN1_GPIO_PORT		GPIOE
#define SIO_BTN1_GPIO_CLK		RCC_APB2Periph_GPIOE
#define SIO_BTN1_EXTI_PIN		GPIO_PinSource2
#define SIO_BTN1_EXTI_PORT		GPIO_PortSourceGPIOE
#define SIO_BTN1_EXTI_LINE		EXTI_Line2
#define SIO_BTN1_EXTI_MODE		EXTI_Mode_Interrupt
#define SIO_BTN1_EXTI_TRIG		EXTI_Trigger_Falling
#define SIO_BTN1_EXTI_IRQn		EXTI2_IRQn

#define SIO_BTN2_GPIO_PIN		GPIO_Pin_3
#define SIO_BTN2_GPIO_PORT		GPIOE
#define SIO_BTN2_GPIO_CLK		RCC_APB2Periph_GPIOE
#define SIO_BTN2_EXTI_PIN		GPIO_PinSource3
#define SIO_BTN2_EXTI_PORT		GPIO_PortSourceGPIOE
#define SIO_BTN2_EXTI_LINE		EXTI_Line3
#define SIO_BTN2_EXTI_MODE		EXTI_Mode_Interrupt
#define SIO_BTN2_EXTI_TRIG		EXTI_Trigger_Falling
#define SIO_BTN2_EXTI_IRQn		EXTI3_IRQn

#define SIO_LED1_GPIO_PIN		GPIO_Pin_4
#define SIO_LED1_GPIO_PORT		GPIOE
#define SIO_LED1_GPIO_CLK		RCC_APB2Periph_GPIOE

#define SIO_LED2_GPIO_PIN		GPIO_Pin_0
#define SIO_LED2_GPIO_PORT		GPIOB
#define SIO_LED2_GPIO_CLK		RCC_APB2Periph_GPIOB

#define SIO_PZO_GPIO_PIN		GPIO_Pin_1
#define SIO_PZO_GPIO_PORT		GPIOA
#define SIO_PZO_GPIO_CLK		RCC_APB2Periph_AFIO
#define SIO_PZO_TIMER			TIM2
#define SIO_PZO_TIMER_CLK		RCC_APB1Periph_TIM2

#define SIO_POT_GPIO_PIN		GPIO_Pin_1
#define SIO_POT_GPIO_PORT		GPIOC
#define SIO_POT_GPIO_CLK		RCC_APB2Periph_ADC1
#define SIO_POT_ADC				ADC1
#define SIO_POT_ADC_CHN			ADC_Channel_11
#endif /* SIO_DEFINTION_OVERRIDE */

#define SIO_GPIO_SPEED			GPIO_Speed_50MHz
#define PIEZO_INIT_PERIOD		(1000)
#define MIN_PIEZO_FREQ			(1000)
#define MAX_PIEZO_FREQ			(15000)

void miniSTM32_SIO_BoardInit(void);
void miniSTM32_SIO_LEDOn(SIO_LED_TypeDef Led);
void miniSTM32_SIO_LEDOff(SIO_LED_TypeDef Led);
void miniSTM32_SIO_LEDToggle(SIO_LED_TypeDef Led);
uint16_t miniSTM32_SIO_LEDGetStatus(SIO_LED_TypeDef Led);
/* maybe I can do it later
void miniSTM32_SIO_LEDPWMControl(SIO_LED_TypeDef Led, uint16_t Duty);
*/
uint16_t miniSTM32_SIO_ButtonGetState(SIO_Button_TypeDef Button);
void miniSTM32_SIO_PiezoControl(uint16_t Duty);
uint16_t miniSTM32_SIO_POTGetValue(void);


#ifdef __cplusplus
}
#endif
  
#endif /* __MINISTM32_SIO_H */
 
/* END OF FILE */

