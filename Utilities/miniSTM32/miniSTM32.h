/**
  ******************************************************************************
  * @file    miniSTM32.h
  * @author  Brian
  * @version V0.1.1 (based on STM32_EVAL version V4.5.0)
  * @date    28-June-2011
  * @brief   This file contains definitions	for miniSTM32 board's peripherals, 
  *			 i.e., led, push-button, COM port, serial EEPROM. 
  ******************************************************************************
  */ 
  
#ifndef __MINISTM32_H
#define __MINISTM32_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"

/*
 * LED
 */


#define MAIN_LED_PIN					GPIO_Pin_5
#define MAIN_LED_GPIO_PORT				GPIOB
#define MAIN_LED_GPIO_CLK				RCC_APB2Periph_GPIOB

/*
 * Push button
 */

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


/*
 * COM port
 */ 

#define MAIN_COM_USART					USART1
#define MAIN_COM_CLK					RCC_APB2Periph_USART1
#define MAIN_COM_TX_PIN					GPIO_Pin_9
#define MAIN_COM_TX_GPIO_PORT			GPIOA
#define MAIN_COM_TX_GPIO_CLK			RCC_APB2Periph_GPIOA
#define MAIN_COM_RX_PIN					GPIO_Pin_10
#define MAIN_COM_RX_GPIO_PORT			GPIOA
#define MAIN_COM_RX_GPIO_CLK			RCC_APB2Periph_GPIOA
#define MAIN_COM_IRQn					USART1_IRQn
#define MAIN_COM_USART_CLK				(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO)

/*
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


/*
 * SST25VF016B SPI Flash supported commands
 */


#define sFLASH_WIP_FLAG					0x01

#define sFLASH_DUMMY_BYTE				0xA5
#define sFLASH_BP_ALL					0x1C	/* all block  */
#define sFLASH_BP_NONE					0x00	/* no block   */
#define sFLASH_BP_32					0x04	/* upper 1/32 */
#define sFLASH_BP_16					0x08	/* upper 1/16 */
#define sFLASH_BP_8						0x0C	/* upper 1/8  */
#define sFLASH_BP_4						0x10	/* upper 1/4  */
#define sFLASH_BP_2						0x14	/* upper 1/2  */

#define sFLASH_SST25VF016_ID			0xBF2541

#define sFLASH_CMD_RD25M				0x03
#define sFLASH_CMD_RD80M				0x0B
#define sFLASH_CMD_ER04K				0x20
#define sFLASH_CMD_ER32K				0x52
#define sFLASH_CMD_ER64K				0xD8
#define sFLASH_CMD_ERCHIP				0x60
#define sFLASH_CMD_WRBYTE				0x02
#define sFLASH_CMD_WRAAIW				0xAD
#define sFLASH_CMD_RDSR					0x05
#define sFLASH_CMD_EWSR					0x50
#define sFLASH_CMD_WRSR					0x01
#define sFLASH_CMD_WREN					0x06
#define sFLASH_CMD_WRDI					0x04
#define sFLASH_CMD_RDID					0x90
#define sFLASH_CMD_JEDEC				0x9F
#define sFLASH_CMD_EBSY					0x70
#define sFLASH_CMD_DBSY					0x80

#define sFLASH_CS_LOW()					GPIO_ResetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)
#define sFLASH_CS_HIGH()				GPIO_SetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)   

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

void miniSTM32_BoardInit(void);

void miniSTM32_LEDInit(void);
void miniSTM32_LEDOn(void);
void miniSTM32_LEDOff(void);
void miniSTM32_LEDToggle(void);

void miniSTM32_PBInit(ButtonMode_TypeDef Button_Mode);
uint32_t miniSTM32_PBGetState(void);

void miniSTM32_COMInit(USART_InitTypeDef* USART_InitStruct);
void miniSTM32_COMInit2(uint32_t Speed);

void sFLASH_Init(void);
void sFLASH_DeInit(void);
uint8_t sFLASH_SendByte(uint8_t byte);
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord);
void sFLASH_WriteEnable(void);
void sFLASH_WriteDisable(void);
void sFLASH_WaitForWriteEnd(void);
void sFLASH_Erase(BlockSize_TypeDef Size, uint32_t StartAddr);
void sFLASH_WriteByte(uint8_t Byte, uint32_t WriteAddr);
void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByte);
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByte);
uint32_t sFLASH_ReadID(void);
uint8_t sFLASH_ReadRegister(void);
void sFLASH_WriteRegister(uint8_t RegData);

void SD_LowLevel_DeInit(void);
void SD_LowLevel_Init(void); 
void SD_LowLevel_DMA_TxConfig(uint32_t *BufferSRC, uint32_t BufferSize);
void SD_LowLevel_DMA_RxConfig(uint32_t *BufferDST, uint32_t BufferSize);
uint32_t SD_DMAEndOfTransferStatus(void);

#ifdef __cplusplus
}
#endif
  
#endif /* __MINISTM32_H */
 
/*****END OF FILE****/

