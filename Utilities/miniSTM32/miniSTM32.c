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

/* serial flash */
uint8_t sFLASH_SendByte(uint8_t byte);
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord);
void sFLASH_WriteEnable(void);
void sFLASH_WriteDisable(void);
void sFLASH_WaitForWriteEnd(void);
void sFLASH_WriteByte(uint8_t Byte, uint32_t WriteAddr);
uint8_t sFLASH_ReadRegister(void);
void sFLASH_WriteRegister(uint8_t RegData);

/* sdcard*/
void SD_LowLevel_DeInit(void);
void SD_LowLevel_Init(void); 
void SD_LowLevel_DMA_TxConfig(uint32_t *BufferSRC, uint32_t BufferSize);
void SD_LowLevel_DMA_RxConfig(uint32_t *BufferDST, uint32_t BufferSize);
uint32_t SD_DMAEndOfTransferStatus(void);


/**
 * @brief	Initialize main board
 * @param	None
 * @retval	None
 */

void miniSTM32_BoardInit(void)
{
	/* Initialize LED */
	miniSTM32_LEDInit();

	/* Initialize push buttons */
	miniSTM32_PBInit(BTN_MODE_EXTI);

	/* Initialize COM port */
	miniSTM32_COMInit2(115200);
}


void miniSTM32_LEDInit(void)
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

void miniSTM32_PBInit(ButtonMode_TypeDef Button_Mode)
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

void miniSTM32_COMInit2(uint32_t Speed)
{
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = Speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	miniSTM32_COMInit( &USART_InitStructure );
}


void miniSTM32_COMInit(USART_InitTypeDef* USART_InitStruct)
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

void miniSTM32_LEDOn(void)
{
  MAIN_LED_GPIO_PORT->BSRR = MAIN_LED_PIN;     
}

/*
 * This function turns the LED Off.
 */
void miniSTM32_LEDOff(void)
{
  MAIN_LED_GPIO_PORT->BRR = MAIN_LED_PIN;    
}

/*
 * This function toggles the LED.
 */
void miniSTM32_LEDToggle(void)
{
  MAIN_LED_GPIO_PORT->ODR ^= MAIN_LED_PIN;
}


/*
 * This function returns the selected Button state.
 */
uint32_t miniSTM32_PBGetState(void)
{
  return GPIO_ReadInputDataBit(MAIN_BTN_GPIO_PORT, MAIN_BTN_PIN);
}



/*
 ******************************************************************************
 */ 

/*
 * This function initializes the peripherals used by the SPI FLASH driver.
 */
void miniSTM32_FlashInit(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/*!< sFLASH_SPI_CS_GPIO, sFLASH_SPI_MOSI_GPIO, sFLASH_SPI_MISO_GPIO 
	and sFLASH_SPI_SCK_GPIO Periph clock enable */
	RCC_APB2PeriphClockCmd(sFLASH_CS_GPIO_CLK | sFLASH_SPI_MOSI_GPIO_CLK | 
		sFLASH_SPI_MISO_GPIO_CLK | sFLASH_SPI_SCK_GPIO_CLK, ENABLE);

	/*!< sFLASH_SPI Periph clock enable */
	RCC_APB2PeriphClockCmd(sFLASH_SPI_CLK, ENABLE);
  
	/*!< Configure sFLASH_SPI pins: SCK */
	GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure sFLASH_SPI pins: MOSI */
	GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MOSI_PIN;
	GPIO_Init(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure sFLASH_SPI pins: MISO */
	GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_Init(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
  
	/*!< Configure sFLASH_CS_PIN pin: sFLASH Card CS pin */
	GPIO_InitStructure.GPIO_Pin = sFLASH_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);

    
	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();

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
	/* SPI clock: PCLK2/4 = 18MHz */
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(sFLASH_SPI, &SPI_InitStructure);

	/*!< Enable the sFLASH_SPI  */
	SPI_Cmd(sFLASH_SPI, ENABLE);

	/* disable block protection */
	sFLASH_WriteRegister( sFLASH_BP_NONE );
}


/*
 * @brief  Sends a byte through the SPI interface and return the byte received
 *         from the SPI bus.
 * @param  byte: byte to send.
 * @retval The value of the received byte.
 */
uint8_t sFLASH_SendByte(uint8_t byte)
{
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);

	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(sFLASH_SPI, byte);

	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);

	/*!< Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(sFLASH_SPI);
}

/*
 * @brief  Sends a Half Word through the SPI interface and return the Half Word
 *         received from the SPI bus.
 * @param  HalfWord: Half Word to send.
 * @retval The value of the received Half Word.
 */
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord)
{
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);

	/*!< Send Half Word through the sFLASH peripheral */
	SPI_I2S_SendData(sFLASH_SPI, HalfWord);

	/*!< Wait to receive a Half Word */
	while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);

	/*!< Return the Half Word read from the SPI bus */
	return SPI_I2S_ReceiveData(sFLASH_SPI);
}

/*
 * @brief  Enables the write access to the FLASH.
 * @param  None
 * @retval None
 */
void sFLASH_WriteEnable(void)
{
	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();

	/*!< Send "Write Enable" instruction */
	sFLASH_SendByte(sFLASH_CMD_WREN);

	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();
}

void sFLASH_WriteDisable(void)
{
	sFLASH_CS_LOW();
	sFLASH_SendByte(sFLASH_CMD_WRDI);
	sFLASH_CS_HIGH();
}

/*
 * @brief  Polls the status of the Write In Progress (WIP) flag in the FLASH's
 *         status register and loop until write opertaion has completed.
 * @param  None
 * @retval None
 */
void sFLASH_WaitForWriteEnd(void)
{
	uint8_t flashstatus = 0;

	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();

	/*!< Send "Read Status Register" instruction */
	sFLASH_SendByte(sFLASH_CMD_RDSR);

	/*!< Loop as long as the memory is busy with a write cycle */
	do
	{
		/*!< Send a dummy byte to generate the clock needed by the FLASH
		and put the value of the status register in FLASH_Status variable */
		flashstatus = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

	}
	while ((flashstatus & sFLASH_WIP_FLAG) == SET); /* Write in progress */

	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();
}


void miniSTM32_FlashErase(BlockSize_TypeDef Size, uint32_t StartAddr)
{
	uint8_t u8CmdByte;

	if(Size == EBSIZE_4KB)
	{
		u8CmdByte = sFLASH_CMD_ER04K;
	}
	else if(Size == EBSIZE_32KB)
	{
		u8CmdByte = sFLASH_CMD_ER32K;
	}
	else if(Size == EBSIZE_64KB)
	{
		u8CmdByte = sFLASH_CMD_ER64K;
	}
	else if(Size == EBSIZE_CHIP)
	{
		u8CmdByte = sFLASH_CMD_ERCHIP;
	}
	else
	{
		return;
	}
	/*!< Send write enable instruction */
	sFLASH_WriteEnable();

	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();
	/*!< Send Sector Erase instruction */
	sFLASH_SendByte(u8CmdByte);

	if( u8CmdByte != sFLASH_CMD_ERCHIP )
	{
		/*!< Send SectorAddr high nibble address byte */
		sFLASH_SendByte((StartAddr & 0xFF0000) >> 16);
		/*!< Send SectorAddr medium nibble address byte */
		sFLASH_SendByte((StartAddr & 0xFF00) >> 8);
		/*!< Send SectorAddr low nibble address byte */
		sFLASH_SendByte(StartAddr & 0xFF);
	}
	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();

	/*!< Wait the end of Flash writing */
	sFLASH_WaitForWriteEnd();
}


void sFLASH_WriteByte(uint8_t Byte, uint32_t WriteAddr)
{
	sFLASH_WriteEnable();

	/* chip select */
	sFLASH_CS_LOW();
	
	/* command byte */
	sFLASH_SendByte(sFLASH_CMD_WRBYTE);
	
	/* 3bytes of address */
	sFLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
	sFLASH_SendByte((WriteAddr & 0xFF00) >> 8);
	sFLASH_SendByte(WriteAddr & 0xFF);
	
	/* data byte */
	sFLASH_SendByte(Byte);

	/* chip deselect */
	sFLASH_CS_HIGH();

	/* wait the end of flash writing */
	sFLASH_WaitForWriteEnd();
}


void miniSTM32_FlashWriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByte)
{
	uint16_t u16Index = 0;

	sFLASH_WriteEnable();

	/* chip select */
	sFLASH_CS_LOW();

	/* command byte */
	sFLASH_SendByte(sFLASH_CMD_WRAAIW);

	/* 3 bytes of address */
	sFLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
	sFLASH_SendByte((WriteAddr & 0xFF00) >> 8);
	sFLASH_SendByte(WriteAddr & 0xFF);

	/* the first 2 data bytes */
	sFLASH_SendByte(pBuffer[u16Index++]);
	sFLASH_SendByte(pBuffer[u16Index++]);

	/* chip deselect */
	sFLASH_CS_HIGH();

	sFLASH_WaitForWriteEnd();

	while( u16Index < (NumByte-1) )
	{
		/* chip select */
		sFLASH_CS_LOW();

		/* command byte */
		sFLASH_SendByte(sFLASH_CMD_WRAAIW);

		/* first data byte */
		sFLASH_SendByte(pBuffer[u16Index++]);

		/* second data byte */
		/* fill the last byte if the NumByte is odd */
		if( u16Index == (NumByte -1) )
		{
			sFLASH_SendByte(0xFF);
		}
		else
		{
			sFLASH_SendByte(pBuffer[u16Index++]);
		}

		/* chip deselect */
		sFLASH_CS_HIGH();

		sFLASH_WaitForWriteEnd();
	}

	/* chip select */
	sFLASH_CS_LOW();

	/* command byte */
	sFLASH_SendByte(sFLASH_CMD_WRDI);

	/* chip deselect */
	sFLASH_CS_HIGH();

	sFLASH_WaitForWriteEnd();

}


/*
 * @brief  Reads a block of data from the FLASH.
 * @param  pBuffer: pointer to the buffer that receives the data read from the FLASH.
 * @param  ReadAddr: FLASH's internal address to read from.
 * @param  NumByteToRead: number of bytes to read from the FLASH.
 * @retval None
 */
void miniSTM32_FlashReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByte)
{
	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();

	/*!< Send "Read from Memory " instruction */
#ifdef FLASH_HIGHSPEED_READ
	sFLASH_SendByte(sFLASH_CMD_RD80M);
#else
	sFLASH_SendByte(sFLASH_CMD_RD25M);
#endif // FLASH_HIGHSPEED_READ

	/*!< Send ReadAddr high nibble address byte to read from */
	sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
	/*!< Send ReadAddr medium nibble address byte to read from */
	sFLASH_SendByte((ReadAddr& 0xFF00) >> 8);
	/*!< Send ReadAddr low nibble address byte to read from */
	sFLASH_SendByte(ReadAddr & 0xFF);

#ifdef FLASH_HIGHSPEED_READ
	/* additional dummy byte folling the 3byte address */
	sFLASH_SendByte(sFLASH_DUMMY_BYTE);
#endif // FLASH HIGHSPEED_READ

	while (NumByte--) /*!< while there is data to be read */
	{
		/*!< Read a byte from the FLASH */
		*pBuffer = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
		/*!< Point to the next location where the byte read will be saved */
		pBuffer++;
	}

	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();
}


/*
 * @brief  Reads FLASH identification.
 * @param  None
 * @retval FLASH identification
 */
uint32_t miniSTM32_FlashReadID(void)
{
	uint32_t u32Temp = 0, u32TempX;

	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();

	/*!< Send "RDID " instruction */
	sFLASH_SendByte(sFLASH_CMD_JEDEC);

	/*!< Read a byte from the FLASH */
	u32TempX = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	u32Temp += (u32TempX << 16);

	u32TempX = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	u32Temp += (u32TempX << 8);

	u32TempX = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	u32Temp += u32TempX;

	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();

	return u32Temp;
}

uint8_t sFLASH_ReadRegister(void)
{
	uint8_t u8Data;

	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();

	/*!< Send "RDID " instruction */
	sFLASH_SendByte(sFLASH_CMD_RDSR);

	u8Data = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

	sFLASH_CS_HIGH();

	return u8Data;
}

void sFLASH_WriteRegister(uint8_t RegData)
{
	sFLASH_CS_LOW();
	sFLASH_SendByte(sFLASH_CMD_EWSR);
	sFLASH_CS_HIGH();

	/* do we need delay here ? */

	sFLASH_CS_LOW();
	sFLASH_SendByte(sFLASH_CMD_WRSR);
	sFLASH_SendByte(RegData);
	sFLASH_CS_HIGH();
}


/**
  * This function deinitializes the SDIO interface.
  * 
  */
void SD_LowLevel_DeInit(void)
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
void SD_LowLevel_Init(void)
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
void SD_LowLevel_DMA_TxConfig(uint32_t *BufferSRC, uint32_t BufferSize)
{

  DMA_InitTypeDef DMA_InitStructure;

  DMA_ClearFlag(DMA2_FLAG_TC4 | DMA2_FLAG_TE4 | DMA2_FLAG_HT4 | DMA2_FLAG_GL4);

  /*!< DMA2 Channel4 disable */
  DMA_Cmd(DMA2_Channel4, DISABLE);

  /*!< DMA2 Channel4 Config */
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SDIO_FIFO_ADDRESS;
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
void SD_LowLevel_DMA_RxConfig(uint32_t *BufferDST, uint32_t BufferSize)
{
  DMA_InitTypeDef DMA_InitStructure;

  DMA_ClearFlag(DMA2_FLAG_TC4 | DMA2_FLAG_TE4 | DMA2_FLAG_HT4 | DMA2_FLAG_GL4);

  /*!< DMA2 Channel4 disable */
  DMA_Cmd(DMA2_Channel4, DISABLE);

  /*!< DMA2 Channel4 Config */
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SDIO_FIFO_ADDRESS;
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
uint32_t SD_DMAEndOfTransferStatus(void)
{
  return (uint32_t)DMA_GetFlagStatus(DMA2_FLAG_TC4);
}



/* END OF FILE */

