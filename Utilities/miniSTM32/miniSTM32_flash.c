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
void mSTM_FlashWriteEnable(void);
void mSTM_FlashWriteDisable(void);
void mSTM_FlashWaitForWriteEnd(void);
void mSTM_FlashWriteByte(uint8_t Byte, uint32_t WriteAddr);
uint8_t mSTM_FlashReadRegister(void);
void mSTM_FlashWriteRegister(uint8_t RegData);


/*
 * @brief  Enables the write access to the FLASH.
 * @param  None
 * @retval None
 */
void mSTM_FlashWriteEnable(void)
{
	/* select the chip */
	MAIN_FLASH_CS_LOW();

	/* send WREN command */
	mSTM_SPISendByte(SFLASH_CMD_WREN);

	/* deselect the chip */
	MAIN_FLASH_CS_HIGH();
}

void mSTM_FlashWriteDisable(void)
{
	/* select the chip */
	MAIN_FLASH_CS_LOW();

	/* send WRDI command */
	mSTM_SPISendByte(SFLASH_CMD_WRDI);

	/* deselect the chip */
	MAIN_FLASH_CS_HIGH();
}

/*
 * @brief  Polls the status of the Write In Progress (WIP) flag in the FLASH's
 *         status register and loop until write opertaion has completed.
 * @param  None
 * @retval None
 */
void mSTM_FlashWaitForWriteEnd(void)
{
	uint8_t flashstatus = 0;

	/*!< Select the FLASH: Chip Select low */
	MAIN_FLASH_CS_LOW();

	/*!< Send "Read Status Register" instruction */
	mSTM_SPISendByte(SFLASH_CMD_RDSR);

	/*!< Loop as long as the memory is busy with a write cycle */
	do
	{
		/*!< Send a dummy byte to generate the clock needed by the FLASH
		and put the value of the status register in FLASH_Status variable */
		flashstatus = mSTM_SPISendByte(SFLASH_DUMMY_BYTE);

	}
	while ((flashstatus & SFLASH_WIP_FLAG) == SET); /* Write in progress */

	/*!< Deselect the FLASH: Chip Select high */
	MAIN_FLASH_CS_HIGH();
}



void mSTM_FlashWriteByte(uint8_t Byte, uint32_t WriteAddr)
{
	mSTM_FlashWriteEnable();

	/* chip select */
	MAIN_FLASH_CS_LOW();
	
	/* command byte */
	mSTM_SPISendByte(SFLASH_CMD_WRBYTE);
	
	/* 3bytes of address */
	mSTM_SPISendByte((WriteAddr & 0xFF0000) >> 16);
	mSTM_SPISendByte((WriteAddr & 0xFF00) >> 8);
	mSTM_SPISendByte(WriteAddr & 0xFF);
	
	/* data byte */
	mSTM_SPISendByte(Byte);

	/* chip deselect */
	MAIN_FLASH_CS_HIGH();

	/* wait the end of flash writing */
	mSTM_FlashWaitForWriteEnd();
}



uint8_t mSTM_FlashReadRegister(void)
{
	uint8_t u8Data;

	/*!< Select the FLASH: Chip Select low */
	MAIN_FLASH_CS_LOW();

	/*!< Send "RDID " instruction */
	mSTM_SPISendByte(SFLASH_CMD_RDSR);

	u8Data = mSTM_SPISendByte(SFLASH_DUMMY_BYTE);

	MAIN_FLASH_CS_HIGH();

	return u8Data;
}

void mSTM_FlashWriteRegister(uint8_t RegData)
{
	MAIN_FLASH_CS_LOW();
	mSTM_SPISendByte(SFLASH_CMD_EWSR);
	MAIN_FLASH_CS_HIGH();

	/* do we need delay here ? */

	MAIN_FLASH_CS_LOW();
	mSTM_SPISendByte(SFLASH_CMD_WRSR);
	mSTM_SPISendByte(RegData);
	MAIN_FLASH_CS_HIGH();
}


/*
 * This function initializes the peripherals used by the SPI FLASH driver.
 */
void FlashInit(void)
{
	mSTM_FlashPortInit();
    
	/* Deselect the FLASH: Chip Select high */
	MAIN_FLASH_CS_HIGH();

	mSTM_SPIInit(SPI_MODE_FLASH);

	/* disable block protection */
	mSTM_FlashWriteRegister( SFLASH_BP_NONE );
}

/*
 * @brief  Reads FLASH identification.
 * @param  None
 * @retval FLASH identification
 */
uint32_t FlashReadID(void)
{
	uint32_t u32Temp = 0, u32TempX;

	/* Select the FLASH: Chip Select low */
	MAIN_FLASH_CS_LOW();

	/* Send "RDID " instruction */
	mSTM_SPISendByte(SFLASH_CMD_JEDEC);

	/* Read a byte from the FLASH */
	u32TempX = mSTM_SPISendByte(SFLASH_DUMMY_BYTE);
	u32Temp += (u32TempX << 16);

	u32TempX = mSTM_SPISendByte(SFLASH_DUMMY_BYTE);
	u32Temp += (u32TempX << 8);

	u32TempX = mSTM_SPISendByte(SFLASH_DUMMY_BYTE);
	u32Temp += u32TempX;

	/* Deselect the FLASH: Chip Select high */
	MAIN_FLASH_CS_HIGH();

	return u32Temp;
}


void FlashErase(BlockSize_TypeDef Size, uint32_t StartAddr)
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
	mSTM_FlashWriteEnable();

	/*!< Select the FLASH: Chip Select low */
	MAIN_FLASH_CS_LOW();
	/*!< Send Sector Erase instruction */
	mSTM_SPISendByte(u8CmdByte);

	if( u8CmdByte != SFLASH_CMD_ERCHIP )
	{
		/*!< Send SectorAddr high nibble address byte */
		mSTM_SPISendByte((StartAddr & 0xFF0000) >> 16);
		/*!< Send SectorAddr medium nibble address byte */
		mSTM_SPISendByte((StartAddr & 0xFF00) >> 8);
		/*!< Send SectorAddr low nibble address byte */
		mSTM_SPISendByte(StartAddr & 0xFF);
	}
	/*!< Deselect the FLASH: Chip Select high */
	MAIN_FLASH_CS_HIGH();

	/*!< Wait the end of Flash writing */
	mSTM_FlashWaitForWriteEnd();
}


void FlashWriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByte)
{
	uint16_t u16Index = 0;

	mSTM_FlashWriteEnable();

	/* chip select */
	MAIN_FLASH_CS_LOW();

	/* command byte */
	mSTM_SPISendByte(SFLASH_CMD_WRAAIW);

	/* 3 bytes of address */
	mSTM_SPISendByte((WriteAddr & 0xFF0000) >> 16);
	mSTM_SPISendByte((WriteAddr & 0xFF00) >> 8);
	mSTM_SPISendByte(WriteAddr & 0xFF);

	/* the first 2 data bytes */
	mSTM_SPISendByte(pBuffer[u16Index++]);
	mSTM_SPISendByte(pBuffer[u16Index++]);

	/* chip deselect */
	MAIN_FLASH_CS_HIGH();

	mSTM_FlashWaitForWriteEnd();

	while( u16Index < (NumByte-1) )
	{
		/* chip select */
		MAIN_FLASH_CS_LOW();

		/* command byte */
		mSTM_SPISendByte(SFLASH_CMD_WRAAIW);

		/* first data byte */
		mSTM_SPISendByte(pBuffer[u16Index++]);

		/* second data byte */
		/* fill the last byte if the NumByte is odd */
		if( u16Index == (NumByte -1) )
		{
			mSTM_SPISendByte(0xFF);
		}
		else
		{
			mSTM_SPISendByte(pBuffer[u16Index++]);
		}

		/* chip deselect */
		MAIN_FLASH_CS_HIGH();

		mSTM_FlashWaitForWriteEnd();
	}

	/* chip select */
	MAIN_FLASH_CS_LOW();

	/* command byte */
	mSTM_SPISendByte(SFLASH_CMD_WRDI);

	/* chip deselect */
	MAIN_FLASH_CS_HIGH();

	mSTM_FlashWaitForWriteEnd();

}


/*
 * @brief  Reads a block of data from the FLASH.
 * @param  pBuffer: pointer to the buffer that receives the data read from the FLASH.
 * @param  ReadAddr: FLASH's internal address to read from.
 * @param  NumByteToRead: number of bytes to read from the FLASH.
 * @retval None
 */
void FlashReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByte)
{
	/*!< Select the FLASH: Chip Select low */
	MAIN_FLASH_CS_LOW();

	/*!< Send "Read from Memory " instruction */
#ifdef FLASH_HIGHSPEED_READ
	mSTM_SPISendByte(SFLASH_CMD_RD80M);
#else
	mSTM_SPISendByte(SFLASH_CMD_RD25M);
#endif // FLASH_HIGHSPEED_READ

	/*!< Send ReadAddr high nibble address byte to read from */
	mSTM_SPISendByte((ReadAddr & 0xFF0000) >> 16);
	/*!< Send ReadAddr medium nibble address byte to read from */
	mSTM_SPISendByte((ReadAddr& 0xFF00) >> 8);
	/*!< Send ReadAddr low nibble address byte to read from */
	mSTM_SPISendByte(ReadAddr & 0xFF);

#ifdef FLASH_HIGHSPEED_READ
	/* additional dummy byte folling the 3byte address */
	mSTM_SPISendByte(SFLASH_DUMMY_BYTE);
#endif // FLASH HIGHSPEED_READ

	while (NumByte--) /*!< while there is data to be read */
	{
		/*!< Read a byte from the FLASH */
		*pBuffer = mSTM_SPISendByte(SFLASH_DUMMY_BYTE);
		/*!< Point to the next location where the byte read will be saved */
		pBuffer++;
	}

	/*!< Deselect the FLASH: Chip Select high */
	MAIN_FLASH_CS_HIGH();
}


/* END OF FILE */

