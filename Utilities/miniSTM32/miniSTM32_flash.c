/*******************************************************************************
 * @file    miniSTM32_flash.c
 * @author  Brian
 * @version V0.1.1
 * @date    14-July-2011
 * @brief   This file provides:
 *         - set of firmware functions to manage SPI serial flash
 *			 
 */ 
  
#include "miniSTM32.h"
#include "stm32f10x_spi.h"

/*
 * SST25VF016B SPI Flash supported commands
 */
#define SFLASH_WIP_FLAG					0x01

#define SFLASH_DUMMY_BYTE				0xA5
#define SFLASH_BP_ALL					0x1C	/* all block  */
#define SFLASH_BP_NONE					0x00	/* no block   */
#define SFLASH_BP_32					0x04	/* upper 1/32 */
#define SFLASH_BP_16					0x08	/* upper 1/16 */
#define SFLASH_BP_8						0x0C	/* upper 1/8  */
#define SFLASH_BP_4						0x10	/* upper 1/4  */
#define SFLASH_BP_2						0x14	/* upper 1/2  */

#define SFLASH_SST25VF016_ID			0xBF2541

#define SFLASH_CMD_RD25M				0x03
#define SFLASH_CMD_RD80M				0x0B
#define SFLASH_CMD_ER04K				0x20
#define SFLASH_CMD_ER32K				0x52
#define SFLASH_CMD_ER64K				0xD8
#define SFLASH_CMD_ERCHIP				0x60
#define SFLASH_CMD_WRBYTE				0x02
#define SFLASH_CMD_WRAAIW				0xAD
#define SFLASH_CMD_RDSR					0x05
#define SFLASH_CMD_EWSR					0x50
#define SFLASH_CMD_WRSR					0x01
#define SFLASH_CMD_WREN					0x06
#define SFLASH_CMD_WRDI					0x04
#define SFLASH_CMD_RDID					0x90
#define SFLASH_CMD_JEDEC				0x9F
#define SFLASH_CMD_EBSY					0x70
#define SFLASH_CMD_DBSY					0x80


/* private functions */
void SFL_WriteEnable(void);
void SFL_WriteDisable(void);
void SFL_WaitForWriteEnd(void);
void SFL_WriteByte(uint8_t Byte, uint32_t WriteAddr);
uint8_t SFL_ReadRegister(void);
void SFL_WriteRegister(uint8_t RegData);


/*
 * @brief  Enables the write access to the FLASH.
 * @param  None
 * @retval None
 */
void SFL_WriteEnable(void)
{
	/* select the chip */
	MAIN_FLASH_CS_LOW();

	/* send WREN command */
	MCU_SPI1SendByte(SFLASH_CMD_WREN);

	/* deselect the chip */
	MAIN_FLASH_CS_HIGH();
}

void SFL_WriteDisable(void)
{
	/* select the chip */
	MAIN_FLASH_CS_LOW();

	/* send WRDI command */
	MCU_SPI1SendByte(SFLASH_CMD_WRDI);

	/* deselect the chip */
	MAIN_FLASH_CS_HIGH();
}

/*
 * @brief  Polls the status of the Write In Progress (WIP) flag in the FLASH's
 *         status register and loop until write opertaion has completed.
 * @param  None
 * @retval None
 */
void SFL_WaitForWriteEnd(void)
{
	uint8_t flashstatus = 0;

	/*!< Select the FLASH: Chip Select low */
	MAIN_FLASH_CS_LOW();

	/*!< Send "Read Status Register" instruction */
	MCU_SPI1SendByte(SFLASH_CMD_RDSR);

	/*!< Loop as long as the memory is busy with a write cycle */
	do
	{
		/*!< Send a dummy byte to generate the clock needed by the FLASH
		and put the value of the status register in FLASH_Status variable */
		flashstatus = MCU_SPI1SendByte(SFLASH_DUMMY_BYTE);

	}
	while ((flashstatus & SFLASH_WIP_FLAG) == SET); /* Write in progress */

	/*!< Deselect the FLASH: Chip Select high */
	MAIN_FLASH_CS_HIGH();
}



void SFL_WriteByte(uint8_t Byte, uint32_t WriteAddr)
{
	SFL_WriteEnable();

	/* chip select */
	MAIN_FLASH_CS_LOW();
	
	/* command byte */
	MCU_SPI1SendByte(SFLASH_CMD_WRBYTE);
	
	/* 3bytes of address */
	MCU_SPI1SendByte((WriteAddr & 0xFF0000) >> 16);
	MCU_SPI1SendByte((WriteAddr & 0xFF00) >> 8);
	MCU_SPI1SendByte(WriteAddr & 0xFF);
	
	/* data byte */
	MCU_SPI1SendByte(Byte);

	/* chip deselect */
	MAIN_FLASH_CS_HIGH();

	/* wait the end of flash writing */
	SFL_WaitForWriteEnd();
}



uint8_t SFL_ReadRegister(void)
{
	uint8_t u8Data;

	/*!< Select the FLASH: Chip Select low */
	MAIN_FLASH_CS_LOW();

	/*!< Send "RDID " instruction */
	MCU_SPI1SendByte(SFLASH_CMD_RDSR);

	u8Data = MCU_SPI1SendByte(SFLASH_DUMMY_BYTE);

	MAIN_FLASH_CS_HIGH();

	return u8Data;
}

void SFL_WriteRegister(uint8_t RegData)
{
	MAIN_FLASH_CS_LOW();
	MCU_SPI1SendByte(SFLASH_CMD_EWSR);
	MAIN_FLASH_CS_HIGH();

	/* do we need delay here ? */

	MAIN_FLASH_CS_LOW();
	MCU_SPI1SendByte(SFLASH_CMD_WRSR);
	MCU_SPI1SendByte(RegData);
	MAIN_FLASH_CS_HIGH();
}


/**
 * @brief	This function initializes the peripherals for the SPI FLASH.
 * @param	None
 * @retval	None
 */
void SFL_Init(void)
{
	/* initialize cs pin */
	MCU_SFLPortInit();
    
	/* deselect the chip */
	MAIN_FLASH_CS_HIGH();

	/* intialize the SPI module */
	MCU_SPI1Init(SPI_MODE_FLASH);

	/* disable block protection */
	SFL_WriteRegister( SFLASH_BP_NONE );
}

/*
 * @brief  Reads FLASH identification.
 * @param  None
 * @retval FLASH identification
 */
uint32_t SFL_ReadID(void)
{
	uint32_t u32Temp = 0, u32TempX;

	/* Select the FLASH: Chip Select low */
	MAIN_FLASH_CS_LOW();

	/* Send "RDID " instruction */
	MCU_SPI1SendByte(SFLASH_CMD_JEDEC);

	/* Read a byte from the FLASH */
	u32TempX = MCU_SPI1SendByte(SFLASH_DUMMY_BYTE);
	u32Temp += (u32TempX << 16);

	u32TempX = MCU_SPI1SendByte(SFLASH_DUMMY_BYTE);
	u32Temp += (u32TempX << 8);

	u32TempX = MCU_SPI1SendByte(SFLASH_DUMMY_BYTE);
	u32Temp += u32TempX;

	/* Deselect the FLASH: Chip Select high */
	MAIN_FLASH_CS_HIGH();

	return u32Temp;
}


void SFL_Erase(BlockSize_TypeDef Size, uint32_t StartAddr)
{
	uint8_t u8CmdByte;

	if(Size == EBSIZE_4KB)
	{
		u8CmdByte = SFLASH_CMD_ER04K;
	}
	else if(Size == EBSIZE_32KB)
	{
		u8CmdByte = SFLASH_CMD_ER32K;
	}
	else if(Size == EBSIZE_64KB)
	{
		u8CmdByte = SFLASH_CMD_ER64K;
	}
	else if(Size == EBSIZE_CHIP)
	{
		u8CmdByte = SFLASH_CMD_ERCHIP;
	}
	else
	{
		return;
	}
	/*!< Send write enable instruction */
	SFL_WriteEnable();

	/*!< Select the FLASH: Chip Select low */
	MAIN_FLASH_CS_LOW();
	/*!< Send Sector Erase instruction */
	MCU_SPI1SendByte(u8CmdByte);

	if( u8CmdByte != SFLASH_CMD_ERCHIP )
	{
		/*!< Send SectorAddr high nibble address byte */
		MCU_SPI1SendByte((StartAddr & 0xFF0000) >> 16);
		/*!< Send SectorAddr medium nibble address byte */
		MCU_SPI1SendByte((StartAddr & 0xFF00) >> 8);
		/*!< Send SectorAddr low nibble address byte */
		MCU_SPI1SendByte(StartAddr & 0xFF);
	}
	/*!< Deselect the FLASH: Chip Select high */
	MAIN_FLASH_CS_HIGH();

	/*!< Wait the end of Flash writing */
	SFL_WaitForWriteEnd();
}


void SFL_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByte)
{
	uint16_t u16Index = 0;

	SFL_WriteEnable();

	/* chip select */
	MAIN_FLASH_CS_LOW();

	/* command byte */
	MCU_SPI1SendByte(SFLASH_CMD_WRAAIW);

	/* 3 bytes of address */
	MCU_SPI1SendByte((WriteAddr & 0xFF0000) >> 16);
	MCU_SPI1SendByte((WriteAddr & 0xFF00) >> 8);
	MCU_SPI1SendByte(WriteAddr & 0xFF);

	/* the first 2 data bytes */
	MCU_SPI1SendByte(pBuffer[u16Index++]);
	MCU_SPI1SendByte(pBuffer[u16Index++]);

	/* chip deselect */
	MAIN_FLASH_CS_HIGH();

	SFL_WaitForWriteEnd();

	while( u16Index < (NumByte-1) )
	{
		/* chip select */
		MAIN_FLASH_CS_LOW();

		/* command byte */
		MCU_SPI1SendByte(SFLASH_CMD_WRAAIW);

		/* first data byte */
		MCU_SPI1SendByte(pBuffer[u16Index++]);

		/* second data byte */
		/* fill the last byte if the NumByte is odd */
		if( u16Index == (NumByte -1) )
		{
			MCU_SPI1SendByte(0xFF);
		}
		else
		{
			MCU_SPI1SendByte(pBuffer[u16Index++]);
		}

		/* chip deselect */
		MAIN_FLASH_CS_HIGH();

		SFL_WaitForWriteEnd();
	}

	/* chip select */
	MAIN_FLASH_CS_LOW();

	/* command byte */
	MCU_SPI1SendByte(SFLASH_CMD_WRDI);

	/* chip deselect */
	MAIN_FLASH_CS_HIGH();

	SFL_WaitForWriteEnd();

}


/*
 * @brief  Reads a block of data from the FLASH.
 * @param  pBuffer: pointer to the buffer that receives the data read from the FLASH.
 * @param  ReadAddr: FLASH's internal address to read from.
 * @param  NumByteToRead: number of bytes to read from the FLASH.
 * @retval None
 */
void SFL_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByte)
{
	/*!< Select the FLASH: Chip Select low */
	MAIN_FLASH_CS_LOW();

	/*!< Send "Read from Memory " instruction */
#ifdef FLASH_HIGHSPEED_READ
	MCU_SPI1SendByte(SFLASH_CMD_RD80M);
#else
	MCU_SPI1SendByte(SFLASH_CMD_RD25M);
#endif // FLASH_HIGHSPEED_READ

	/*!< Send ReadAddr high nibble address byte to read from */
	MCU_SPI1SendByte((ReadAddr & 0xFF0000) >> 16);
	/*!< Send ReadAddr medium nibble address byte to read from */
	MCU_SPI1SendByte((ReadAddr& 0xFF00) >> 8);
	/*!< Send ReadAddr low nibble address byte to read from */
	MCU_SPI1SendByte(ReadAddr & 0xFF);

#ifdef FLASH_HIGHSPEED_READ
	/* additional dummy byte folling the 3byte address */
	MCU_SPI1SendByte(SFLASH_DUMMY_BYTE);
#endif // FLASH HIGHSPEED_READ

	while (NumByte--) /*!< while there is data to be read */
	{
		/*!< Read a byte from the FLASH */
		*pBuffer = MCU_SPI1SendByte(SFLASH_DUMMY_BYTE);
		/*!< Point to the next location where the byte read will be saved */
		pBuffer++;
	}

	/*!< Deselect the FLASH: Chip Select high */
	MAIN_FLASH_CS_HIGH();
}


/* END OF FILE */

