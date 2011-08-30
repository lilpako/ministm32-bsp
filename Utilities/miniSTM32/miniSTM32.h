/*
 ******************************************************************************
 * miniSTM32.h
 * Brian
 * (based on STM32_EVAL version V4.5.0)
 * 28-June-2011
 * This file contains definitions	for miniSTM32 board's peripherals, 
 *	i.e., led, push-button, COM port, serial EEPROM. 
 ******************************************************************************
 */ 
  
#ifndef __MINISTM32_H
#define __MINISTM32_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"

/* Push button */
typedef enum
{
	BTN_MODE_GPIO = 0,
	BTN_MODE_EXTI = 1
} ButtonMode_TypeDef;

#define MAIN_BTN_PIN					GPIO_Pin_15
#define MAIN_BTN_GPIO_PORT				GPIOB
#define MAIN_BTN_GPIO_CLK				(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define MAIN_BTN_EXTI_SRC				GPIO_PinSource15
#define MAIN_BTN_EXTI_PORT				GPIO_PortSourceGPIOB
#define MAIN_BTN_EXTI_LINE				EXTI_Line15
#define MAIN_BTN_EXTI_MODE				EXTI_Mode_Interrupt
#define MAIN_BTN_EXTI_TRIG				EXTI_Trigger_Falling
#define MAIN_BTN_EXTI_IRQn				EXTI15_10_IRQn  

/* SPI mode */
typedef enum
{
	SPI_MODE_FLASH = 0,
	SPI_MODE_TOUCH = 1
} SPIMode_TypeDef;

/* FLASH SPI baudrate : PCLK2/4 = 18MHz */
#define MAIN_FLASH_SPI_BAUD				SPI_BaudRatePrescaler_4;
/* Touch Controler SPI baudrate : PCLK2/43 = 1.125MHz */
#define MAIN_TOUCH_SPI_BAUD				SPI_BaudRatePrescaler_64;

/* FLASH interface pins */  
#define MAIN_FLASH_CS_PIN				GPIO_Pin_4                  /* PA.04 */
#define MAIN_FLASH_CS_GPIO_PORT			GPIOA                       /* GPIOA */
#define MAIN_FLASH_CS_GPIO_CLK			RCC_APB2Periph_GPIOA

/* FLASH macros */  
#define MAIN_FLASH_CS_LOW()				GPIO_ResetBits(MAIN_FLASH_CS_GPIO_PORT, \
	MAIN_FLASH_CS_PIN)
#define MAIN_FLASH_CS_HIGH()			GPIO_SetBits(MAIN_FLASH_CS_GPIO_PORT, \
	MAIN_FLASH_CS_PIN) 

/* Touch Sensor Controller interrupt and chip select */
#define MAIN_TSC_INT_PIN				GPIO_Pin_6
#define MAIN_TSC_INT_GPIO_PORT			GPIOB
#define MAIN_TSC_INT_GPIO_CLK			RCC_APB2Periph_GPIOB
#define MAIN_TSC_INT_EXTI_SRC			GPIO_PinSource6
#define MAIN_TSC_INT_EXTI_PORT			GPIO_PortSourceGPIOB
#define MAIN_TSC_INT_EXTI_LINE			EXTI_Line6
#define MAIN_TSC_INT_EXTI_MODE			EXTI_Mode_Interrupt
#define MAIN_TSC_INT_EXTI_TRIG			EXTI_Trigger_Falling
#define MAIN_TSC_INT_EXTI_IRQn			EXTI9_5_IRQn

#define MAIN_TSC_CS_PIN					GPIO_Pin_7
#define MAIN_TSC_CS_GPIO_PORT			GPIOB
#define MAIN_TSC_CS_GPIO_CLK			RCC_APB2Periph_GPIOB

#define MAIN_TSC_CS_LOW()				GPIO_ResetBits(MAIN_TSC_CS_GPIO_PORT, \
	MAIN_TSC_CS_PIN)
#define MAIN_TSC_CS_HIGH()				GPIO_SetBits(MAIN_TSC_CS_GPIO_PORT, \
	MAIN_TSC_CS_PIN) 

/* set EXTI interrupt mask */
#define EXTI_SetMask(x)					(EXTI->IMR = EXTI->IMR & (~x))
/* clear EXTI interrupt mask */
#define EXTI_ClearMask(x)				(EXTI->IMR = EXTI->IMR | (x))

/*
 * miniSTM32 Exported Functions
 */ 

/* Mainboard: board */
void MBD_Init(void);

/* Mainboard: LED */
void MBD_LEDInit(void);
void MBD_LEDOn(void);
void MBD_LEDOff(void);
void MBD_LEDToggle(void);

/* Mainboard: pushbutton */
void MBD_PBInit(ButtonMode_TypeDef Button_Mode);
uint32_t MBD_PBGetState(void);

/* Mainboard: COM port */
void MBD_COMInit(uint32_t Speed);

/* MCU: serial flash interface */
void MCU_SFLPortInit(void);

/* MCU: SPI module */
void MCU_SPI1Init(SPIMode_TypeDef SPI_Mode);
void MCU_SPI1SetMode(SPIMode_TypeDef SPI_Mode);
uint8_t MCU_SPI1SendByte(uint8_t Byte);
uint16_t MCU_SPI1SendHalfWord(uint16_t HalfWord);

/* MCU: LCD controller interface */
void MCU_LCDPortInit(void);
void MCU_FSMCInit(void);

/* MCU: touch screen controller interface */
void MCU_TSCPortInit(void);

#ifdef __cplusplus
}
#endif
  
#endif /* __MINISTM32_H */
 
/*****END OF FILE****/

