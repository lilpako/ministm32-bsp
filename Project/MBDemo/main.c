/*******************************************************************************
 * @file	Project/MBDemo/main.c 
 * @author	Brian
 * @version	V0.2.0
 * @date	21 July 2011
 * @brief	This file demonstrate the function of main board peripherals:
 *			- push button
 *			- LED(blue)
 *			- serial FLASH memory
 *			- micro SD card
 *			You can find separate project for LCD and touch screen sensor demo.
 */ 

/*
 * Do not run SD FAT test with SD RAW test at the same time.
 * RAW test will destroy your SD partition information.
 * If you want raw read/write test, uncomment the following line
 * otherwise FAT test will be performed.
 *
#define SD_TEST_RAW			1
 */

#include "stm32f10x.h"			/* CMSIS */
#include "miniSTM32.h"			/* mainboard BSP */
#include "miniSTM32_sd.h"		/* SDIO - SD support */
#include "miniSTM32_flash.h"
#include <stdio.h>

/*
#define SD_TEST_RAW
*/
#if !defined(SD_TEST_RAW)
#include "ff.h"					/* FatFs support */
#endif

/* demo menu list */
enum{
	MENU_LED_ON = 0,
	MENU_LED_OFF,
	MENU_FLASH_READID,
	MENU_FLASH_WRITE,
	MENU_FLASH_READ,
	MENU_FLASH_ERASE,
	MENU_FLASH_ERASECHECK,
#ifdef SD_TEST_RAW
	MENU_SD_ERASE,
	MENU_SD_BLOCK,
	MENU_SD_MULTIBLOCK,
#else
	MENU_FAT_TEST,
#endif // SD_TEST_RAW
	MENU_END
};

/* interrupt ID from IRQ routines */
extern volatile uint16_t u16IRQFlag;

/* sflash demo parameters */
#define READ_BUFFER_SIZE		30
#define FLASH_ADDRESS			0x10000

/* sd demo typedef */
typedef enum {
	FAILED = 0, 
	PASSED = !FAILED
} TestStatus;

/* sd demo parameters */
#define BLOCK_SIZE				512 /* Block Size in Bytes */
#define NUMBER_OF_BLOCKS		32  /* For Multi Blocks operation (Read/Write) */
#define MULTI_BUFFER_SIZE		(BLOCK_SIZE * NUMBER_OF_BLOCKS)

/* sd demo variables */
uint8_t Buffer_Block_Tx[BLOCK_SIZE];
uint8_t Buffer_Block_Rx[BLOCK_SIZE];
uint8_t Buffer_MultiBlock_Tx[MULTI_BUFFER_SIZE];
uint8_t Buffer_MultiBlock_Rx[MULTI_BUFFER_SIZE];
volatile TestStatus EraseStatus = FAILED;
volatile TestStatus TransferStatus1 = FAILED;
volatile TestStatus TransferStatus2 = FAILED;
SD_Error Status = SD_OK;

/* sd demo function prototypes */
void SD_EraseTest(void);
void SD_SingleBlockTest(void);
void SD_MultiBlockTest(void);
void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);
TestStatus eBuffercmp(uint8_t* pBuffer, uint32_t BufferLength);

/* FAT demo function prototypes */
TestStatus FAT_Test(void);

/**
 * @brief	Main program
 * @param	None
 * @retval	None
 */
int main(void)
{
	uint16_t u16Menu=0;
	uint32_t u32FlashID = 0;

	uint8_t Tx_Buffer[] = "miniSTM32 SPI Flash Test Data";
	uint8_t Rx_Buffer[READ_BUFFER_SIZE] = {0x20};

	/* Initialize SysTick - 1msec resolution */
	SysTick_Config(SystemCoreClock / 1000);

	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* Initialize main board peripherals */
	mSTM_BoardInit();
	printf("miniSTM32 mainboard initialized\n");

	/* Initialize SPI FLASH driver */
	FlashInit();
	printf("serial FLASH  initialized\n");

#ifdef SD_TEST_RAW
	/* Initialize SD subsystem : for FAT test it is automatic */
	if(mSTM_SDInit() == SD_OK)
	{
		printf("SD interface initialized\n");
	}
#endif
        
	while (1) 
	{
		/* main menu controlled by pushbutton interrupt */
		if( u16IRQFlag == MAIN_BTN_EXTI_LINE ) {

			/* clear button interrupt flag */
			u16IRQFlag = 0;

			if( u16Menu == MENU_LED_ON ) {
				mSTM_LEDOn();
				printf("LED1 Turned On\n");
			}
			else if( u16Menu == MENU_LED_OFF ) {
				mSTM_LEDOff();
				printf("LED1 Turned Off\n");
			}
			else if( u16Menu == MENU_FLASH_READID ) {
				u32FlashID = FlashReadID();
				printf("JEDEC Flash ID: %X\n", u32FlashID);
			}
			else if( u16Menu == MENU_FLASH_WRITE ) {
				FlashErase(EBSIZE_4KB, FLASH_ADDRESS);
				FlashWriteBuffer(Tx_Buffer, FLASH_ADDRESS, sizeof(Tx_Buffer));
				printf("FLASH Write Data: %s\n", Tx_Buffer);
			}
			else if( u16Menu == MENU_FLASH_READ ) {
				FlashReadBuffer(Rx_Buffer, FLASH_ADDRESS, sizeof(Rx_Buffer) - 1);
				printf("FLASH Read Back: %s\n", Rx_Buffer);
			}
			else if( u16Menu == MENU_FLASH_ERASE ) {
				FlashErase(EBSIZE_4KB, FLASH_ADDRESS);
				printf("FLASH Erase Block: Data Erased\n");
			}
			else if( u16Menu == MENU_FLASH_ERASECHECK ) {
				FlashReadBuffer(Rx_Buffer, FLASH_ADDRESS, sizeof(Rx_Buffer) - 1);
				printf("FLASH Read Data Again: %s\n", Rx_Buffer);
			}

#ifdef SD_TEST_RAW
			else if( u16Menu == MENU_SD_ERASE ) {
				SD_EraseTest();
			}
			else if( u16Menu == MENU_SD_BLOCK ) {
				SD_SingleBlockTest();
			}
			else if( u16Menu == MENU_SD_MULTIBLOCK ) {
				SD_MultiBlockTest();
			}
#else
			else if( u16Menu == MENU_FAT_TEST ) {
				if(FAT_Test() == PASSED)
					printf("FAT Test Passed\n");
				else
					printf("FAT Test Failed\n");;
			}
#endif // SD_TEST_RAW

			if( ++u16Menu == MENU_END )
				u16Menu = 0;

		}

		/* usual household routine goes here */
		{
		}
	}
}


#ifdef SD_TEST_RAW
/**
 * @brief	Test the SD card erase operations.
 * @param	None
 * @retval	None
 */
void SD_EraseTest(void)
{
	/* Erase NumberOfBlocks Blocks of WRITE_BL_LEN(512 Bytes) */
    Status = mSTM_SDErase(0x00, (BLOCK_SIZE * NUMBER_OF_BLOCKS));

	if (Status == SD_OK)
	{
		Status = mSTM_SDReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);

		/* Check if the Transfer is finished */
		Status = mSTM_SDWaitReadOperation();

		/* Wait until end of DMA transfer */
		while(mSTM_SDGetStatus() != SD_TRANSFER_OK);
	}

	/* Check the correctness of erased blocks */
	if (Status == SD_OK)
	{
		EraseStatus = eBuffercmp(Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE);
	}
  
	if(EraseStatus == PASSED)
	{
		printf("SD_EraseTest(): passed\n");
	}
	else
	{
		printf("SD_EraseTest(): failed\n");
	}
}

/**
 * @brief	Tests the SD card Single Blocks operations.
 * @param	None
 * @retval	None
 */
void SD_SingleBlockTest(void)
{
	/* Fill the buffer to send */
	Fill_Buffer(Buffer_Block_Tx, BLOCK_SIZE, 0x320F);

	/* Write block of 512 bytes on address 0 */
	Status = mSTM_SDWriteBlock(Buffer_Block_Tx, 0x00, BLOCK_SIZE);

	/* Check if the Transfer is finished */
	Status = mSTM_SDWaitWriteOperation();
	while(mSTM_SDGetStatus() != SD_TRANSFER_OK);
	
	if (Status == SD_OK)
	{
		/* Read block of 512 bytes from address 0 */
		Status = mSTM_SDReadBlock(Buffer_Block_Rx, 0x00, BLOCK_SIZE);

		/* Check if the Transfer is finished */
		Status = mSTM_SDWaitReadOperation();
		while(mSTM_SDGetStatus() != SD_TRANSFER_OK);
	}

	/* Check the correctness of written data */
	if (Status == SD_OK)
	{
		TransferStatus1 = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, BLOCK_SIZE);
	}
	
	if(TransferStatus1 == PASSED)
	{
		printf("SD_SingleBlockTest(): passed\n");
	}
	else
	{
		printf("SD_SingleBlockTest(): failed\n");
	}
}

/**
 * @brief	Tests the SD card Multiple Blocks operations.
 * @param	None
 * @retval	None
 */
void SD_MultiBlockTest(void)
{
	/* Fill the buffer to send */
	Fill_Buffer(Buffer_MultiBlock_Tx, MULTI_BUFFER_SIZE, 0x0);
	
	/* Write multiple block of many bytes on address 0 */
	Status = mSTM_SDWriteMultiBlocks(Buffer_MultiBlock_Tx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);

	/* Check if the Transfer is finished */
	Status = mSTM_SDWaitWriteOperation();
	while(mSTM_SDGetStatus() != SD_TRANSFER_OK);
	
	if (Status == SD_OK)
	{
		/* Read block of many bytes from address 0 */
		Status = mSTM_SDReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
		/* Check if the Transfer is finished */
		Status = mSTM_SDWaitReadOperation();
		while(mSTM_SDGetStatus() != SD_TRANSFER_OK);
	}
	
	/* Check the correctness of written data */
	if (Status == SD_OK)
	{
		TransferStatus2 = Buffercmp(Buffer_MultiBlock_Tx, Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE);
	}
	
	if(TransferStatus2 == PASSED)
	{
		printf("SD_MultiBlockTest(): passed\n");
	}
	else
	{
		printf("SD_MultiBlockTest(): failed\n");
	}
}

/**
 * @brief	Compares two buffers.
 * @param	pBuffer1, pBuffer2: buffers to be compared.
 * @param	BufferLength: buffer's length
 * @retval	PASSED: pBuffer1 identical to pBuffer2
 *			FAILED: pBuffer1 differs from pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
{
	while (BufferLength--)
	{
		if (*pBuffer1 != *pBuffer2)
		{
			return FAILED;
		}
	
		pBuffer1++;
		pBuffer2++;
	}
	
	return PASSED;
}

/**
 * @brief	Fills buffer with user predefined data.
 * @param	pBuffer: pointer on the Buffer to fill
 * @param	BufferLength: size of the buffer to fill
 * @param	Offset: first value to fill on the Buffer
 * @retval	None
 */
void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset)
{
	uint16_t index = 0;
	
	/* Put in global buffer same values */
	for (index = 0; index < BufferLength; index++)
	{
		pBuffer[index] = index + Offset;
	}
}

/**
 * @brief	Checks if a buffer has all its values are equal to zero.
 * @param	pBuffer: buffer to be compared.
 * @param	BufferLength: buffer's length
 * @retval	PASSED: pBuffer values are zero
 *			FAILED: At least one value from pBuffer buffer is different from zero.
 */
TestStatus eBuffercmp(uint8_t* pBuffer, uint32_t BufferLength)
{
	while (BufferLength--)
	{
		/* In some SD Cards the erased state is 0xFF, in others it's 0x00 */
		if ((*pBuffer != 0xFF) && (*pBuffer != 0x00))
		{
			return FAILED;
		}
	
		pBuffer++;
	}
	
	return PASSED;
}

#else // SD_TEST_RAW

/**
 * @brief	Test read/write FAT volume
 * @param	None
 * @retval	PASSED: All the test was passed.
 *			FAILED: At least one test was failed.
 */
TestStatus FAT_Test (void)
{
	FRESULT rc;				/* Result code */
	FATFS fatfs;			/* File system object */
	FIL fil;				/* File object */
	DIR dir;				/* Directory object */
	FILINFO fno;			/* File information object */
	UINT bw, br, i;
	BYTE buff[512];

	uint32_t u32index;

	/* Register volume work area (never fails) */
	f_mount(0, &fatfs);		

	printf("\nOpen a test file (message.txt).\n");
	rc = f_open(&fil, "MESSAGE.TXT", FA_READ);
	if (rc) return FAILED;

	printf("\nType the file content.\n");
	for (;;) {
		/* Read a chunk of file */
		rc = f_read(&fil, buff, sizeof(buff), &br);	

		/* Error or end of file */
		if (rc || !br) break;			

		for (i = 0; i < br; i++)		
			/* Type the data */
			putchar(buff[i]);
	}
	if (rc) return FAILED;

	printf("\nClose the file.\n");
	rc = f_close(&fil);
	if (rc) return FAILED;

	printf("\nCreate a new file (hello.txt).\n");
	rc = f_open(&fil, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
	if (rc) return FAILED;

	printf("\nWrite a text data. (Hello world!)\n");
	rc = f_write(&fil, "Hello world!\r\n", 700, &bw);
	if (rc) return FAILED;
	printf("%u bytes written.\n", bw);

	printf("\nClose the file.\n");
	rc = f_close(&fil);
	if (rc) return FAILED;

	printf("\nOpen root directory.\n");
	rc = f_opendir(&dir, "");
	if (rc) return FAILED;

	printf("\nDirectory listing...\n");
	for (;;) {
		rc = f_readdir(&dir, &fno);	
		if (rc || !fno.fname[0]) break;
		if (fno.fattrib & AM_DIR)
			printf("   <dir>  %s\n", fno.fname);
		else
			printf("%8lu  %s\n", fno.fsize, fno.fname);
	}
	if (rc) return FAILED;

	return PASSED;
}

#endif // SD_TEST_RAW

#ifdef  USE_FULL_ASSERT

/**
 * @brief	Reports the name of the source file and the source line number
 *			where the assert_param error has occurred.
 * @param	file: pointer to the source file name
 * @param	line: assert_param error line source number
 * @retval	None
 */
void assert_failed(uint8_t* file, uint32_t line)
{ 
	/* User can add his own implementation to report the file name and line number,
	ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}

#endif // USE_FULL_ASSERT

/* End of File */
