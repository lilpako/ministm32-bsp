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

/*
 * Push button
 */
typedef enum
{
	BTN_MODE_GPIO = 0,
	BTN_MODE_EXTI = 1
} ButtonMode_TypeDef;

/*
 * Push button
 */
#define MAIN_BTN_PIN					GPIO_Pin_15
#define MAIN_BTN_GPIO_PORT				GPIOB
#define MAIN_BTN_GPIO_CLK				(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define MAIN_BTN_EXTI_SRC				GPIO_PinSource15
#define MAIN_BTN_EXTI_PORT				GPIO_PortSourceGPIOB
#define MAIN_BTN_EXTI_LINE				EXTI_Line15
#define MAIN_BTN_EXTI_MODE				EXTI_Mode_Interrupt
#define MAIN_BTN_EXTI_TRIG				EXTI_Trigger_Falling
#define MAIN_BTN_EXTI_IRQn				EXTI15_10_IRQn  

/*
 * SST25VF016B SPI Flash 
 */

/* FLASH typedefs */
typedef enum{
	EBSIZE_4KB,
	EBSIZE_32KB,
	EBSIZE_64KB,
	EBSIZE_CHIP
} BlockSize_TypeDef;

/* FLASH interface pins */  
#define MAIN_FLASH_CS_PIN				GPIO_Pin_4                  /* PA.04 */
#define MAIN_FLASH_CS_GPIO_PORT			GPIOA                       /* GPIOA */
#define MAIN_FLASH_CS_GPIO_CLK			RCC_APB2Periph_GPIOA

/* FLASH macros */  
#define MAIN_FLASH_CS_LOW()				GPIO_ResetBits(MAIN_FLASH_CS_GPIO_PORT, \
	MAIN_FLASH_CS_PIN)
#define MAIN_FLASH_CS_HIGH()			GPIO_SetBits(MAIN_FLASH_CS_GPIO_PORT, \
	MAIN_FLASH_CS_PIN) 

/*
 * Micro SD Card reader
 */ 

#if 0
/* SDIO definitions */
/* SDIOCLK = HCLK, SDIO_CK = HCLK/(2 + SDIO_CLK_DIV) */
#define MAIN_SDIO_FIFO_ADDRESS		    ((uint32_t)0x40018080)
#endif


/*
 * Touch Sensor Controller interrupt and chip select
 */
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

/*
 * miniSTM32 Exported Functions
 */ 

/* board */
void mSTM_BoardInit(void);

/* LED */
void mSTM_LEDInit(void);
void mSTM_LEDOn(void);
void mSTM_LEDOff(void);
void mSTM_LEDToggle(void);

/* pushbutton */
void mSTM_PBInit(ButtonMode_TypeDef Button_Mode);
uint32_t mSTM_PBGetState(void);

/* COM port */
void mSTM_COMInit(USART_InitTypeDef* USART_InitStruct);
void mSTM_COMInit2(uint32_t Speed);

/* SPI module */
void mSTM_SPIInit(void);
void mSTM_SPISetBaudRate(uint16_t BaudRate);

/* Flash */
void mSTM_FlashPortInit(void);
uint8_t mSTM_FlashSendByte(uint8_t byte);
uint16_t mSTM_FlashSendHalfWord(uint16_t HalfWord);

#if 0
/* micro sd card */
void mSTM_SDDMATxConfig(uint32_t *BufferSRC, uint32_t BufferSize);
void mSTM_SDDMARxConfig(uint32_t *BufferDST, uint32_t BufferSize);
uint32_t mSTM_SDDMAEndOfTransferStatus(void);
#endif

/* touch sensor */
void mSTM_TSCPortInit(void);

#ifdef __cplusplus
}
#endif
  
#endif /* __MINISTM32_H */
 
/*****END OF FILE****/

