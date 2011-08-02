/**
  ******************************************************************************
  * SIOTest/main.c 
  * author: Brian
  * version: V0.1.1
  * date: 21 July 2011
  * To Do List:
  *			Documentation!
  ******************************************************************************
  * This file demonstrate the function of SIO board
  * Be sure to turn on the -D USE_MINISTM32_SIO flag in your Makefile
  ******************************************************************************
  */ 

#include "stm32f10x.h"
#include "miniSTM32.h"
#include "miniSTM32_sd.h"
#include <stdio.h>

enum{
	MENU_LED_ON = 0,
	MENU_LED_OFF,
	MENU_FLASH_READID,
	MENU_FLASH_WRITE,
	MENU_FLASH_READ,
	MENU_FLASH_ERASE,
	MENU_FLASH_ERASECHECK,
	MENU_SD_ERASE,
	MENU_SD_BLOCK,
	MENU_SD_MULTIBLOCK,
	MENU_END
};

extern volatile uint16_t u16IRQFlag;

#define READ_BUFFER_SIZE		30
#define FLASH_ADDRESS			0x10000


/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BLOCK_SIZE            512 /* Block Size in Bytes */

#define NUMBER_OF_BLOCKS      32  /* For Multi Blocks operation (Read/Write) */
#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t Buffer_Block_Tx[BLOCK_SIZE], Buffer_Block_Rx[BLOCK_SIZE];
uint8_t Buffer_MultiBlock_Tx[MULTI_BUFFER_SIZE], Buffer_MultiBlock_Rx[MULTI_BUFFER_SIZE];
volatile TestStatus EraseStatus = FAILED, TransferStatus1 = FAILED, TransferStatus2 = FAILED;
SD_Error Status = SD_OK;

/* Private function prototypes -----------------------------------------------*/
void NVIC_Configuration(void);
void SD_EraseTest(void);
void SD_SingleBlockTest(void);
void SD_MultiBlockTest(void);
void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);
TestStatus eBuffercmp(uint8_t* pBuffer, uint32_t BufferLength);


int main(void)
{
	uint16_t u16Menu=0;
	uint32_t u32FlashID = 0;

	uint8_t Tx_Buffer[] = "miniSTM32 SPI Flash Test Data";
	uint8_t Rx_Buffer[READ_BUFFER_SIZE] = {0x20};

	/* Initialize SysTick - 1msec */
	SysTick_Config(SystemCoreClock / 1000);

	/* Initialize main board peripherals */
	miniSTM32_BoardInit();
	printf("miniSTM32 mainboard initialized\n");

	/* Initialize SPI FLASH driver */
	sFLASH_Init();
	printf("serial FLASH  initialized\n");

	/* NVIC for SD */
	NVIC_Configuration();

	/* Initialize SD subsystem */
	if(SD_Init() == SD_OK)
	{
		printf("SD interface initialized\n");
	}
        

	while (1) 
	{
		if( u16IRQFlag == MAIN_BTN_EXTI_LINE ) {

			u16IRQFlag = 0;

			if( u16Menu == MENU_LED_ON ) {
				miniSTM32_LEDOn();
				printf("LED1 Turned On\n");
			}
			else if( u16Menu == MENU_LED_OFF ) {
				miniSTM32_LEDOff();
				printf("LED1 Turned Off\n");
			}
			else if( u16Menu == MENU_FLASH_READID ) {
				u32FlashID = sFLASH_ReadID();
				printf("JEDEC Flash ID: %X\n", u32FlashID);
			}
			else if( u16Menu == MENU_FLASH_WRITE ) {
				sFLASH_Erase(EBSIZE_4KB, FLASH_ADDRESS);
				sFLASH_WriteBuffer(Tx_Buffer, FLASH_ADDRESS, sizeof(Tx_Buffer));
				printf("Write Data: %s\n", Tx_Buffer);
			}
			else if( u16Menu == MENU_FLASH_READ ) {
				sFLASH_ReadBuffer(Rx_Buffer, FLASH_ADDRESS, sizeof(Rx_Buffer) - 1);
				printf("Read Back: %s\n", Rx_Buffer);
			}
			else if( u16Menu == MENU_FLASH_ERASE ) {
				sFLASH_Erase(EBSIZE_4KB, FLASH_ADDRESS);
				printf("Erase Block: Data Erased\n");
			}
			else if( u16Menu == MENU_FLASH_ERASECHECK ) {
				sFLASH_ReadBuffer(Rx_Buffer, FLASH_ADDRESS, sizeof(Rx_Buffer) - 1);
				printf("Read Data Again: %s\n", Rx_Buffer);
			}
			else if( u16Menu == MENU_SD_ERASE ) {
				SD_EraseTest();
			}
			else if( u16Menu == MENU_SD_BLOCK ) {
				SD_SingleBlockTest();
			}
			else if( u16Menu == MENU_SD_MULTIBLOCK ) {
				SD_MultiBlockTest();
			}


			if( ++u16Menu == MENU_END )
				u16Menu = 0;

		}

		/* usual household routines here */
		{
		}
	}
}
























/*
 * Brian: SD routine
 */


void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Tests the SD card erase operation.
  * @param  None
  * @retval None
  */
void SD_EraseTest(void)
{
  /*------------------- Block Erase ------------------------------------------*/
	/* Erase NumberOfBlocks Blocks of WRITE_BL_LEN(512 Bytes) */
    Status = SD_Erase(0x00, (BLOCK_SIZE * NUMBER_OF_BLOCKS));

  if (Status == SD_OK)
  {
    Status = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);

    /* Check if the Transfer is finished */
    Status = SD_WaitReadOperation();

    /* Wait until end of DMA transfer */
    while(SD_GetStatus() != SD_TRANSFER_OK);
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
  * @brief  Tests the SD card Single Blocks operations.
  * @param  None
  * @retval None
  */
void SD_SingleBlockTest(void)
{
  /*------------------- Block Read/Write --------------------------*/
  /* Fill the buffer to send */
  Fill_Buffer(Buffer_Block_Tx, BLOCK_SIZE, 0x320F);

    /* Write block of 512 bytes on address 0 */
    Status = SD_WriteBlock(Buffer_Block_Tx, 0x00, BLOCK_SIZE);
    /* Check if the Transfer is finished */
    Status = SD_WaitWriteOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);

  if (Status == SD_OK)
  {
    /* Read block of 512 bytes from address 0 */
    Status = SD_ReadBlock(Buffer_Block_Rx, 0x00, BLOCK_SIZE);
    /* Check if the Transfer is finished */
    Status = SD_WaitReadOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
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
  * @brief  Tests the SD card Multiple Blocks operations.
  * @param  None
  * @retval None
  */
void SD_MultiBlockTest(void)
{
  /*--------------- Multiple Block Read/Write ---------------------*/
  /* Fill the buffer to send */
  Fill_Buffer(Buffer_MultiBlock_Tx, MULTI_BUFFER_SIZE, 0x0);

    /* Write multiple block of many bytes on address 0 */
    Status = SD_WriteMultiBlocks(Buffer_MultiBlock_Tx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
    /* Check if the Transfer is finished */
    Status = SD_WaitWriteOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);

  if (Status == SD_OK)
  {
    /* Read block of many bytes from address 0 */
    Status = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
    /* Check if the Transfer is finished */
    Status = SD_WaitReadOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
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
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
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
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  BufferLength: size of the buffer to fill
  * @param  Offset: first value to fill on the Buffer
  * @retval None
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
  * @brief  Checks if a buffer has all its values are equal to zero.
  * @param  pBuffer: buffer to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer values are zero
  *         FAILED: At least one value from pBuffer buffer is different from zero.
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


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
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

/* END OF FILE */
