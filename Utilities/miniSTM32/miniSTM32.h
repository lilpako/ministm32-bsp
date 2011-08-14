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
 * SST25VF016B SPI Flash supported commands
 */
typedef enum{
	EBSIZE_4KB,
	EBSIZE_32KB,
	EBSIZE_64KB,
	EBSIZE_CHIP
} BlockSize_TypeDef;

/*
 * SD FLASH SDIO Interface
 */ 
#define SDIO_FIFO_ADDRESS                ((uint32_t)0x40018080)
#define SDIO_INIT_CLK_DIV                ((uint8_t)0xB2)
#define SDIO_TRANSFER_CLK_DIV            ((uint8_t)0x01)

/*
 * miniSTM32 Exported Functions
 */ 

/* board */
void miniSTM32_BoardInit(void);

/* LED */
void miniSTM32_LEDInit(void);
void miniSTM32_LEDOn(void);
void miniSTM32_LEDOff(void);
void miniSTM32_LEDToggle(void);

/* pushbutton */
void miniSTM32_PBInit(ButtonMode_TypeDef Button_Mode);
uint32_t miniSTM32_PBGetState(void);

/* COM port */
void miniSTM32_COMInit(USART_InitTypeDef* USART_InitStruct);
void miniSTM32_COMInit2(uint32_t Speed);

/* serial flash */
void miniSTM32_FlashInit(void);
uint32_t miniSTM32_FlashReadID(void);
void miniSTM32_FlashErase(BlockSize_TypeDef Size, uint32_t StartAddr);
void miniSTM32_FlashWriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByte);
void miniSTM32_FlashReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByte);

#ifdef __cplusplus
}
#endif
  
#endif /* __MINISTM32_H */
 
/*****END OF FILE****/

