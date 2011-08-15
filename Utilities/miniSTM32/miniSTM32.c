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
#include "stm32f10x_sdio.h"
#include "stm32f10x_spi.h"
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
 * SPI 1 : serial flash and touch sensor
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
 * @brief	Initialize main board
 * @param	None
 * @retval	None
 */

void mSTM_BoardInit(void)
{
	/* Initialize LED */
	mSTM_LEDInit();

	/* Initialize push buttons */
	mSTM_PBInit(BTN_MODE_EXTI);

	/* Initialize COM port */
	mSTM_COMInit2(115200);

	/* initialize SPI module */
	mSTM_SPIInit();
}


void mSTM_LEDInit(void)
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

void mSTM_PBInit(ButtonMode_TypeDef Button_Mode)
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

		/* Enable and set Button EXTI Interrupt to the lowest priority */
		NVIC_InitStructure.NVIC_IRQChannel = MAIN_BTN_EXTI_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

		NVIC_Init(&NVIC_InitStructure); 
	}
}

void mSTM_COMInit2(uint32_t Speed)
{
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = Speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	mSTM_COMInit( &USART_InitStructure );
}


void mSTM_COMInit(USART_InitTypeDef* USART_InitStruct)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(MAIN_COM_TX_GPIO_CLK | MAIN_COM_RX_GPIO_CLK | 
		MAIN_COM_USART_CLK, ENABLE);

	/* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = MAIN_COM_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MAIN_COM_TX_GPIO_PORT, &GPIO_InitStructure);

	/* Configure USART Rx as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = MAIN_COM_RX_PIN;
	GPIO_Init(MAIN_COM_RX_GPIO_PORT, &GPIO_InitStructure);

	/* USART configuration */
	USART_Init(MAIN_COM_USART, USART_InitStruct);
    
	/* Enable USART */
	USART_Cmd(MAIN_COM_USART, ENABLE);
}

/*
 * Retargets the C library printf function to the USART.
 */
__io_putchar(int ch)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(MAIN_COM_USART, (uint8_t) ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(MAIN_COM_USART, USART_FLAG_TC) == RESET)
	{}

	return ch;
}

void mSTM_LEDOn(void)
{
  MAIN_LED_GPIO_PORT->BSRR = MAIN_LED_PIN;     
}

/*
 * This function turns the LED Off.
 */
void mSTM_LEDOff(void)
{
  MAIN_LED_GPIO_PORT->BRR = MAIN_LED_PIN;    
}

/*
 * This function toggles the LED.
 */
void mSTM_LEDToggle(void)
{
  MAIN_LED_GPIO_PORT->ODR ^= MAIN_LED_PIN;
}


/*
 * This function returns the selected Button state.
 */
uint32_t mSTM_PBGetState(void)
{
  return GPIO_ReadInputDataBit(MAIN_BTN_GPIO_PORT, MAIN_BTN_PIN);
}


void mSTM_SPIInit()
{
	SPI_InitTypeDef  SPI_InitStructure;

	/* check SPE bit of SPI_CR1 */
	/* return if SPI module is already turned on */
	if(MAIN_SPI01->CR1 & 0x0040) return;

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
	/* SPI clock for sFLASH: PCLK2/4 = 18MHz */
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	/* SPI clock for Touch Sensor: PCLK2/32 = 2.25MHz */
	/*
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	*/
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(MAIN_SPI01, &SPI_InitStructure);

	/* Enable the MAIN_SPI01  */
	SPI_Cmd(MAIN_SPI01, ENABLE);
}

void mSTM_SPI_SetBaudRate(uint16_t BaudRate)
{
	if(IS_SPI_BAUDRATE_PRESCALER(BaudRate))
	{
		MAIN_SPI01->CR1;
	}
}

void mSTM_FlashPortInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* sFLASH_SPI_CS_GPIO, sFLASH_SPI_MOSI_GPIO, sFLASH_SPI_MISO_GPIO 
	and sFLASH_SPI_SCK_GPIO Periph clock enable */
	RCC_APB2PeriphClockCmd(MAIN_FLASH_CS_GPIO_CLK | MAIN_SPI01_MOSI_GPIO_CLK | 
		MAIN_SPI01_MISO_GPIO_CLK | MAIN_SPI01_SCK_GPIO_CLK, ENABLE);

	/* MAIN_SPI01 Periph clock enable */
	RCC_APB2PeriphClockCmd(MAIN_SPI01_CLK, ENABLE);
  
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
  
	/* Configure MAIN_FLASH_CS_PIN pin: sFLASH Card CS pin */
	GPIO_InitStructure.GPIO_Pin = MAIN_FLASH_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(MAIN_FLASH_CS_GPIO_PORT, &GPIO_InitStructure);

}


/*
 * @brief  Sends a byte through the SPI interface and return the byte received
 *         from the SPI bus.
 * @param  byte: byte to send.
 * @retval The value of the received byte.
 */
uint8_t mSTM_FlashSendByte(uint8_t byte)
{
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(MAIN_SPI01, SPI_I2S_FLAG_TXE) == RESET);

	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(MAIN_SPI01, byte);

	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(MAIN_SPI01, SPI_I2S_FLAG_RXNE) == RESET);

	/*!< Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(MAIN_SPI01);
}

/*
 * @brief  Sends a Half Word through the SPI interface and return the Half Word
 *         received from the SPI bus.
 * @param  HalfWord: Half Word to send.
 * @retval The value of the received Half Word.
 */
uint16_t mSTM_FlashSendHalfWord(uint16_t HalfWord)
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

void mSTM_SDIOInit(uint8_t ClockDiv, uint32_t BusWide)
{
	SDIO_InitTypeDef SDIO_InitStructure;

	SDIO_InitStructure.SDIO_ClockDiv = ClockDiv; 
	SDIO_InitStructure.SDIO_ClockEdge = SDIO_ClockEdge_Rising;
	SDIO_InitStructure.SDIO_ClockBypass = SDIO_ClockBypass_Disable;
	SDIO_InitStructure.SDIO_ClockPowerSave = SDIO_ClockPowerSave_Disable;
	SDIO_InitStructure.SDIO_BusWide = BusWide;
	SDIO_InitStructure.SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Disable;
	SDIO_Init(&SDIO_InitStructure);

}

/**
  * This function deinitializes the SDIO interface.
  * 
  */
void mSTM_SDPortDeInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /*!< Disable SDIO Clock */
  SDIO_ClockCmd(DISABLE);
  
  /*!< Set Power State to OFF */
  SDIO_SetPowerState(SDIO_PowerState_OFF);

  /*!< DeInitializes the SDIO peripheral */
  SDIO_DeInit();
  
  /*!< Disable the SDIO AHB Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SDIO, DISABLE);

  /*!< Configure PC.08, PC.09, PC.10, PC.11, PC.12 pin: D0, D1, D2, D3, CLK pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /*!< Configure PD.02 CMD line */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/**
  * This function initializes the SD Card and put it into StandBy State (Ready for 
  *         data transfer).
  */
void mSTM_SDPortInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /*!< GPIOC and GPIOD Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);

  /*!< Configure PC.08, PC.09, PC.10, PC.11, PC.12 pin: D0, D1, D2, D3, CLK pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /*!< Configure PD.02 CMD line */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /*!< Enable the SDIO AHB Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SDIO, ENABLE);

  /*!< Enable the DMA2 Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
}

/**
  * This function configures the DMA2 Channel4 for SDIO Tx request.
  *		BufferSRC: pointer to the source buffer
  *		BufferSize: buffer size
  */
void mSTM_SDDMATxConfig(uint32_t *BufferSRC, uint32_t BufferSize)
{

  DMA_InitTypeDef DMA_InitStructure;

  DMA_ClearFlag(DMA2_FLAG_TC4 | DMA2_FLAG_TE4 | DMA2_FLAG_HT4 | DMA2_FLAG_GL4);

  /*!< DMA2 Channel4 disable */
  DMA_Cmd(DMA2_Channel4, DISABLE);

  /*!< DMA2 Channel4 Config */
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)MAIN_SDIO_FIFO_ADDRESS;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)BufferSRC;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = BufferSize / 4;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA2_Channel4, &DMA_InitStructure);

  /*!< DMA2 Channel4 enable */
  DMA_Cmd(DMA2_Channel4, ENABLE);  
}

/**
  * This function configures the DMA2 Channel4 for SDIO Rx request.
  *		BufferDST: pointer to the destination buffer
  *		BufferSize: buffer size
  */
void mSTM_SDDMARxConfig(uint32_t *BufferDST, uint32_t BufferSize)
{
  DMA_InitTypeDef DMA_InitStructure;

  DMA_ClearFlag(DMA2_FLAG_TC4 | DMA2_FLAG_TE4 | DMA2_FLAG_HT4 | DMA2_FLAG_GL4);

  /*!< DMA2 Channel4 disable */
  DMA_Cmd(DMA2_Channel4, DISABLE);

  /*!< DMA2 Channel4 Config */
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)MAIN_SDIO_FIFO_ADDRESS;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)BufferDST;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = BufferSize / 4;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA2_Channel4, &DMA_InitStructure);

  /*!< DMA2 Channel4 enable */
  DMA_Cmd(DMA2_Channel4, ENABLE); 
}

/**
  * This function returns the DMA End Of Transfer Status.
  */
uint32_t mSTM_SDDMAEndOfTransferStatus(void)
{
  return (uint32_t)DMA_GetFlagStatus(DMA2_FLAG_TC4);
}



/* END OF FILE */

