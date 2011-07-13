/**
  ******************************************************************************
  * @file    miniSTM32.h
  * @author  Brian
  * @version V0.1.1 (based on STM32_EVAL version V4.5.0)
  * @date    28-June-2011
  * @brief   This file contains definitions	for miniSTM32 board's peripherals, 
  *			 i.e., led, push-button, COM port, serial EEPROM. 
  ******************************************************************************
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 
  
#ifndef __MINISTM32_H
#define __MINISTM32_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32_eval.h"

/**
  * LED
  */
#define LEDn                             1

#define LED1_PIN                         GPIO_Pin_5
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK                    RCC_APB2Periph_GPIOB  

/** 
  * Brian : The following definition is awkward but necessary
  *		   not to modify ST original definition of keys in
  *		   stm32_eval.h. In ST's key definition, the first (0)
  *		   key is dedicated to the wakeup key for all evaluation 
  *		   board.
  */
#define BUTTON_PB15						 0 

/**
  * PB15 push-button
  */
#define BUTTONn                          1

#define PB15_BUTTON_PIN                  GPIO_Pin_15
#define PB15_BUTTON_GPIO_PORT            GPIOB
#define PB15_BUTTON_GPIO_CLK             RCC_APB2Periph_GPIOB
#define PB15_BUTTON_EXTI_LINE            EXTI_Line15
#define PB15_BUTTON_EXTI_PORT_SOURCE     GPIO_PortSourceGPIOB
#define PB15_BUTTON_EXTI_PIN_SOURCE	     GPIO_PinSource15
#define PB15_BUTTON_EXTI_IRQn            EXTI15_10_IRQn  


/**
 * Definition for COM port1, connected to USART1
 */ 
#define COMn                             1

#define EVAL_COM1                        USART1
#define EVAL_COM1_CLK                    RCC_APB2Periph_USART1
#define EVAL_COM1_TX_PIN                 GPIO_Pin_9
#define EVAL_COM1_TX_GPIO_PORT           GPIOA
#define EVAL_COM1_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM1_RX_PIN                 GPIO_Pin_10
#define EVAL_COM1_RX_GPIO_PORT           GPIOA
#define EVAL_COM1_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM1_IRQn                   USART1_IRQn

/**
  * SD FLASH SDIO Interface, not tested
  */ 

#define SD_DETECT_PIN                    GPIO_Pin_11                 /* PC.11 */
#define SD_DETECT_GPIO_PORT              GPIOC                       /* GPIOC */
#define SD_DETECT_GPIO_CLK               RCC_APB2Periph_GPIOC

#define SDIO_FIFO_ADDRESS                ((uint32_t)0x40018080)
/** 
  * SDIO Intialization Frequency (400KHz max)
  */
#define SDIO_INIT_CLK_DIV                ((uint8_t)0xB2)
/** 
  * SDIO Data Transfer Frequency (25MHz max) 
  */
#define SDIO_TRANSFER_CLK_DIV            ((uint8_t)0x00)

/**
  * FLASH SPI Interface pins
  */  
#define sFLASH_SPI                       SPI1
#define sFLASH_SPI_CLK                   RCC_APB2Periph_SPI1
#define sFLASH_SPI_SCK_PIN               GPIO_Pin_5                  /* PA.05 */
#define sFLASH_SPI_SCK_GPIO_PORT         GPIOA                       /* GPIOA */
#define sFLASH_SPI_SCK_GPIO_CLK          RCC_APB2Periph_GPIOA
#define sFLASH_SPI_MISO_PIN              GPIO_Pin_6                  /* PA.06 */
#define sFLASH_SPI_MISO_GPIO_PORT        GPIOA                       /* GPIOA */
#define sFLASH_SPI_MISO_GPIO_CLK         RCC_APB2Periph_GPIOA
#define sFLASH_SPI_MOSI_PIN              GPIO_Pin_7                  /* PA.07 */
#define sFLASH_SPI_MOSI_GPIO_PORT        GPIOA                       /* GPIOA */
#define sFLASH_SPI_MOSI_GPIO_CLK         RCC_APB2Periph_GPIOA
#define sFLASH_CS_PIN                    GPIO_Pin_4                  /* PA.04 */
#define sFLASH_CS_GPIO_PORT              GPIOA                       /* GPIOA */
#define sFLASH_CS_GPIO_CLK               RCC_APB2Periph_GPIOA

/* Time constant for the delay caclulation allowing to have a millisecond 
   incrementing counter. This value should be equal to (System Clock / 1000).
   ie. if system clock = 24MHz then sEE_TIME_CONST should be 24. */
#define sEE_TIME_CONST          24 


/**
  * miniSTM32 Exported Functions : STM32_EVAL compatible
  */ 
void STM_EVAL_LEDInit(Led_TypeDef Led);
void STM_EVAL_LEDOn(Led_TypeDef Led);
void STM_EVAL_LEDOff(Led_TypeDef Led);
void STM_EVAL_LEDToggle(Led_TypeDef Led);
void STM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t STM_EVAL_PBGetState(Button_TypeDef Button);
void STM_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);
void SD_LowLevel_DeInit(void);
void SD_LowLevel_Init(void); 
void SD_LowLevel_DMA_TxConfig(uint32_t *BufferSRC, uint32_t BufferSize);
void SD_LowLevel_DMA_RxConfig(uint32_t *BufferDST, uint32_t BufferSize);
uint32_t SD_DMAEndOfTransferStatus(void);
void sFLASH_LowLevel_DeInit(void);
void sFLASH_LowLevel_Init(void); 


#ifdef __cplusplus
}
#endif
  
#endif /* __MINISTM32_H */
 
/*****END OF FILE****/

