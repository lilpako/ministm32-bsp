/*******************************************************************************
 * @file    miniSTM32.c
 * @author  Brian
 * @version V0.1.1
 * @date    28-June-2011
 * @brief   This file provides:
 *         - set of firmware functions to manage Leds, push-button and COM ports
 *         - low level initialization functions for SD card (on SDIO), SPI serial
 *           flash (sFLASH)
 *			 
 */ 
  
#include "miniSTM32.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_fsmc.h"
#include "stm32f10x_usart.h"

/*
 * LED
 */
#define MAIN_LED_PIN					GPIO_Pin_5
#define MAIN_LED_GPIO_PORT				GPIOB
#define MAIN_LED_GPIO_CLK				RCC_APB2Periph_GPIOB

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
 * SPI 1 for serial flash and touch sensor
 */
#define MAIN_SPI01						SPI1
#define MAIN_SPI01_CLK					RCC_APB2Periph_SPI1
#define MAIN_SPI01_SCK_PIN				GPIO_Pin_5                  /* PA.05 */
#define MAIN_SPI01_SCK_GPIO_PORT		GPIOA                       /* GPIOA */
#define MAIN_SPI01_SCK_GPIO_CLK			RCC_APB2Periph_GPIOA
#define MAIN_SPI01_MISO_PIN				GPIO_Pin_6                  /* PA.06 */
#define MAIN_SPI01_MISO_GPIO_PORT		GPIOA                       /* GPIOA */
#define MAIN_SPI01_MISO_GPIO_CLK		RCC_APB2Periph_GPIOA
#define MAIN_SPI01_MOSI_PIN				GPIO_Pin_7                  /* PA.07 */
#define MAIN_SPI01_MOSI_GPIO_PORT		GPIOA                       /* GPIOA */
#define MAIN_SPI01_MOSI_GPIO_CLK		RCC_APB2Periph_GPIOA


/**
 * @brief	Initialize essential parts of the main board.
 * @param	None
 * @retval	None
 */

void MBD_Init(void)
{
	/* Initialize LED */
	MBD_LEDInit();

	/* Initialize push buttons */
	MBD_PBInit(BTN_MODE_EXTI);

	/* Initialize COM port */
	MBD_COMInit(115200);
}

void MBD_LEDInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable the GPIO Clock */
	RCC_APB2PeriphClockCmd(MAIN_LED_GPIO_CLK, ENABLE);

	/* Configure the GPIO_LED pin */
	GPIO_InitStructure.GPIO_Pin = MAIN_LED_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MAIN_LED_GPIO_PORT, &GPIO_InitStructure);
}

void MBD_PBInit(ButtonMode_TypeDef Button_Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the GPIO Clock */
	RCC_APB2PeriphClockCmd(MAIN_BTN_GPIO_CLK, ENABLE);
	/* Configure the BTN1 pin */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = MAIN_BTN_PIN;
	GPIO_Init(MAIN_BTN_GPIO_PORT, &GPIO_InitStructure);

	if(Button_Mode == BTN_MODE_EXTI)
	{
		/* Connect the BTN1 pin to EXTI line */
		GPIO_EXTILineConfig(MAIN_BTN_EXTI_PORT, MAIN_BTN_EXTI_SRC);

		/* Configure BTN1 EXTI line */
		EXTI_InitStructure.EXTI_Line = MAIN_BTN_EXTI_LINE;
		EXTI_InitStructure.EXTI_Mode = MAIN_BTN_EXTI_MODE;
		EXTI_InitStructure.EXTI_Trigger = MAIN_BTN_EXTI_TRIG;  
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
		/* clear pending bit before enabling interrupt */
		EXTI_ClearITPendingBit(MAIN_BTN_EXTI_LINE);

		/* Enable and set Button EXTI Interrupt to the lowest priority */
		NVIC_InitStructure.NVIC_IRQChannel = MAIN_BTN_EXTI_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

		NVIC_Init(&NVIC_InitStructure); 
	}
}

/*
 * @brief	Initialize the main board COM port
 * @param	Speed: baud rate
 * @retval	None
 */
void MBD_COMInit(uint32_t Speed)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(MAIN_COM_TX_GPIO_CLK | MAIN_COM_RX_GPIO_CLK | 
		MAIN_COM_USART_CLK, ENABLE);

	/* Configure COM Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = MAIN_COM_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MAIN_COM_TX_GPIO_PORT, &GPIO_InitStructure);

	/* Configure COM Rx as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = MAIN_COM_RX_PIN;
	GPIO_Init(MAIN_COM_RX_GPIO_PORT, &GPIO_InitStructure);

	/* Configure USART module */
	USART_InitStructure.USART_BaudRate = Speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Initialize USART module */
	USART_Init(MAIN_COM_USART, &USART_InitStructure);

	/* Enable USART */
	USART_Cmd(MAIN_COM_USART, ENABLE);
}

/*
 * @brief	Retargets the C library printf function to the USART.
 * @param	ch : character to be printed
 * @retval	ch : character printed
 */
__io_putchar(int ch)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(MAIN_COM_USART, (uint8_t) ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(MAIN_COM_USART, USART_FLAG_TC) == RESET) {}

	return ch;
}

void MBD_LEDOn(void)
{
  MAIN_LED_GPIO_PORT->BSRR = MAIN_LED_PIN;     
}

/*
 * This function turns the LED Off.
 */
void MBD_LEDOff(void)
{
  MAIN_LED_GPIO_PORT->BRR = MAIN_LED_PIN;    
}

/*
 * This function toggles the LED.
 */
void MBD_LEDToggle(void)
{
  MAIN_LED_GPIO_PORT->ODR ^= MAIN_LED_PIN;
}


/*
 * This function returns the selected Button state.
 */
uint32_t MBD_PBGetState(void)
{
  return GPIO_ReadInputDataBit(MAIN_BTN_GPIO_PORT, MAIN_BTN_PIN);
}


void MCU_SPI1Init(SPIMode_TypeDef SPI_Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* check if MAIN_SPI01 is enabled already */
	if((MAIN_SPI01->CR1 & 0x0040) == 0)
	{
		/* enable MAIN_SPI01 related clocks */
		RCC_APB2PeriphClockCmd(MAIN_SPI01_CLK | MAIN_SPI01_SCK_GPIO_CLK | 
			MAIN_SPI01_MISO_GPIO_CLK | MAIN_SPI01_MOSI_GPIO_CLK, ENABLE);
  
		/* Configure MAIN_SPI01 pins: SCK */
		GPIO_InitStructure.GPIO_Pin = MAIN_SPI01_SCK_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(MAIN_SPI01_SCK_GPIO_PORT, &GPIO_InitStructure);

		/* Configure MAIN_SPI01 pins: MOSI */
		GPIO_InitStructure.GPIO_Pin = MAIN_SPI01_MOSI_PIN;
		GPIO_Init(MAIN_SPI01_MOSI_GPIO_PORT, &GPIO_InitStructure);

		/* Configure MAIN_SPI01 pins: MISO */
		GPIO_InitStructure.GPIO_Pin = MAIN_SPI01_MISO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
		GPIO_Init(MAIN_SPI01_MISO_GPIO_PORT, &GPIO_InitStructure);
	}

	MCU_SPI1SetMode( SPI_Mode );

	/* Enable the MAIN_SPI01  */
	SPI_Cmd(MAIN_SPI01, ENABLE);
}


void MCU_SPI1SetMode(SPIMode_TypeDef SPI_Mode)
{
	SPI_InitTypeDef  SPI_InitStructure;

	/* SPI configuration */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;

	/* SPI Mode 0: CPOL=0, CPHA=0 */
	/*
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	*/

	/* SPI Mode 3: CPOL=1, CPHA=1 */
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;

	/* Separate CS control */
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	/* SPI baud rate */
	if( SPI_Mode == SPI_MODE_FLASH )
	{
		SPI_InitStructure.SPI_BaudRatePrescaler = MAIN_FLASH_SPI_BAUD;
	}
	else if( SPI_Mode == SPI_MODE_TOUCH )
	{
		SPI_InitStructure.SPI_BaudRatePrescaler = MAIN_TOUCH_SPI_BAUD;
	}

	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(MAIN_SPI01, &SPI_InitStructure);

}

void MCU_SFLPortInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* MAIN_SPI01 related GPIO clock clock enable */
	RCC_APB2PeriphClockCmd(MAIN_FLASH_CS_GPIO_CLK, ENABLE);

	/* Configure MAIN_FLASH_CS_PIN pin: sFLASH Card CS pin */
	GPIO_InitStructure.GPIO_Pin = MAIN_FLASH_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(MAIN_FLASH_CS_GPIO_PORT, &GPIO_InitStructure);
}


/*
 * @brief  Sends a byte through the SPI interface and return the byte received
 *         from the SPI bus.
 * @param  Byte: byte to send.
 * @retval The value of the received byte.
 */
uint8_t MCU_SPI1SendByte(uint8_t Byte)
{
	/* Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(MAIN_SPI01, SPI_I2S_FLAG_TXE) == RESET);

	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(MAIN_SPI01, Byte);

	/* Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(MAIN_SPI01, SPI_I2S_FLAG_RXNE) == RESET);

	/* Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(MAIN_SPI01);
}

/*
 * @brief  Sends a Half Word through the SPI interface and return the Half Word
 *         received from the SPI bus.
 * @param  HalfWord: Half Word to send.
 * @retval The value of the received Half Word.
 */
uint16_t MCU_SPI1SendHalfWord(uint16_t HalfWord)
{
	/* Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(MAIN_SPI01, SPI_I2S_FLAG_TXE) == RESET);

	/* Send Half Word through the sFLASH peripheral */
	SPI_I2S_SendData(MAIN_SPI01, HalfWord);

	/* Wait to receive a Half Word */
	while (SPI_I2S_GetFlagStatus(MAIN_SPI01, SPI_I2S_FLAG_RXNE) == RESET);

	/* Return the Half Word read from the SPI bus */
	return SPI_I2S_ReceiveData(MAIN_SPI01);
}

void MCU_LCDPortInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable FSMC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | 
						RCC_APB2Periph_GPIOE | 
						RCC_APB2Periph_AFIO, ENABLE);

	/* FSMC output - port D */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |	/* PD0  - FSMC D02 */
								GPIO_Pin_1 |	/* PD1  - FSMC D03 */
								GPIO_Pin_4 |	/* PD4  - FSMC nOE */
								GPIO_Pin_5 |	/* PD5  - FSMC nWE */
								GPIO_Pin_7 |	/* PD7  - FSMC nE1 */
                                GPIO_Pin_8 |	/* PD8  - FSMC D13 */
								GPIO_Pin_9 |	/* PD9  - FSMC D14 */
								GPIO_Pin_10 |	/* PD10 - FSMC D15 */
								GPIO_Pin_11 |	/* PD11 - FSMC A16 */
								GPIO_Pin_14 |	/* PD14 - FSMC D00 */
                                GPIO_Pin_15;	/* PD15 - FSMC D01 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* FSMC output - port E */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |	/* PE7  - FSMC D04 */
								GPIO_Pin_8 |	/* PE8  - FSMC D05 */
								GPIO_Pin_9 |	/* PE9  - FSMC D06 */
								GPIO_Pin_10 |	/* PE10 - FSMC D07 */
								GPIO_Pin_11 |	/* PE11 - FSMC D08 */
                                GPIO_Pin_12 |	/* PE12 - FSMC D09 */
								GPIO_Pin_13 |	/* PE13 - FSMC D10 */
								GPIO_Pin_14 |	/* PE14 - FSMC D11 */
                                GPIO_Pin_15;	/* PE15 - FSMC D12 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* Backlight(GPIO output) - port D */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	/* PD13 - BACKLIGHT */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* LCD reset(GPIO output) - port E */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	/* PE1  - LCD RESET */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/*
 * set FSMC for LCD controller
 *	mcu clock		: 72MHz
 *	controller clock: 110MHz
 *	memory type		: NOR
 *	access mode		: NOR - OE toggling (reference manual RM0008 p.503)
 */
void MCU_FSMCInit(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  pr, pw;

	/* read timing */
	pr.FSMC_AccessMode = FSMC_AccessMode_C;		/* Mode C   */
	pr.FSMC_AddressSetupTime = 0;				/* 0 - 0xF  */
	pr.FSMC_AddressHoldTime = 1;				/* 1 - 0xF  */
	pr.FSMC_DataSetupTime = 2;					/* 1 - 0xFF */
	pr.FSMC_BusTurnAroundDuration = 0;			/* 0 - 0xF  */
	pr.FSMC_CLKDivision = 1;					/* 1 - 0xF  */
	pr.FSMC_DataLatency = 0;					/* 0 - 0xF  */

	/* write timining */
	pw.FSMC_AccessMode = FSMC_AccessMode_C;		/* Mode C   */
	pw.FSMC_AddressSetupTime = 0;				/* 0 - 0xF  */
	pw.FSMC_AddressHoldTime = 1;				/* 1 - 0xF  */
	pw.FSMC_DataSetupTime = 2;					/* 1 - 0xFF */
	pw.FSMC_BusTurnAroundDuration = 0;			/* 0 - 0xF  */
	pw.FSMC_CLKDivision = 1;					/* 1 - 0xF  */
	pw.FSMC_DataLatency = 0;					/* 0 - 0xF  */

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &pr;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &pw;

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  
	
	/* BANK 1 (of NOR/SRAM Bank) is enabled */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}

void MCU_TSCPortInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the GPIO Clock */
	RCC_APB2PeriphClockCmd(MAIN_TSC_INT_GPIO_CLK | MAIN_TSC_CS_GPIO_CLK, ENABLE);

	/* Configure the TSC_CS pin */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = MAIN_TSC_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MAIN_TSC_CS_GPIO_PORT, &GPIO_InitStructure);

	/* Deselect the controller */
	MAIN_TSC_CS_HIGH();

	/* Configure the TSC_INT pin */
	/*
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	*/
	/* As recommended by the data sheet, put 40K internel pull-down */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = MAIN_TSC_INT_PIN;
	GPIO_Init(MAIN_TSC_INT_GPIO_PORT, &GPIO_InitStructure);

	/* Connect the TSC_INT pin to EXTI line */
	GPIO_EXTILineConfig(MAIN_TSC_INT_EXTI_PORT, MAIN_TSC_INT_EXTI_SRC);

	/* Configure TSC_INT EXTI line */
	EXTI_InitStructure.EXTI_Line = MAIN_TSC_INT_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = MAIN_TSC_INT_EXTI_MODE;
	EXTI_InitStructure.EXTI_Trigger = MAIN_TSC_INT_EXTI_TRIG;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* clear pending bit before enabling interrupt */
	EXTI_ClearITPendingBit(MAIN_TSC_INT_EXTI_LINE);

	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = MAIN_TSC_INT_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure); 
}

/* END OF FILE */

