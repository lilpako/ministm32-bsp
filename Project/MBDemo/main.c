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
#include <stdio.h>

enum{
	MENU_LED_ON = 0,
	MENU_LED_OFF,
	MENU_READ_FLASHID,
	MENU_WRITE_FLASHDATA,
	MENU_READ_FLASHDATA,
	MENU_ERASE_FLASHDATA,
	MENU_REREAD_FLASHDATA,
	MENU_END
};


extern volatile uint16_t u16IRQFlag;


#define READ_BUFFER_SIZE		30
#define FLASH_ADDRESS			0x10000

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
			else if( u16Menu == MENU_READ_FLASHID ) {
				u32FlashID = sFLASH_ReadID();
				printf("JEDEC Flash ID: %X\n", u32FlashID);
			}
			else if( u16Menu == MENU_WRITE_FLASHDATA ) {
				sFLASH_Erase(EBSIZE_4KB, FLASH_ADDRESS);
				sFLASH_WriteBuffer(Tx_Buffer, FLASH_ADDRESS, sizeof(Tx_Buffer));
				printf("Write Data: %s\n", Tx_Buffer);
			}
			else if( u16Menu == MENU_READ_FLASHDATA ) {
				sFLASH_ReadBuffer(Rx_Buffer, FLASH_ADDRESS, sizeof(Rx_Buffer) - 1);
				printf("Read Back: %s\n", Rx_Buffer);
			}
			else if( u16Menu == MENU_ERASE_FLASHDATA ) {
				sFLASH_Erase(EBSIZE_4KB, FLASH_ADDRESS);
				printf("Erase Block: Data Erased\n");
			}
			else if( u16Menu == MENU_REREAD_FLASHDATA ) {
				sFLASH_ReadBuffer(Rx_Buffer, FLASH_ADDRESS, sizeof(Rx_Buffer) - 1);
				printf("Read Data Again: %s\n", Rx_Buffer);
			}


			if( ++u16Menu == MENU_END )
				u16Menu = 0;

		}

		/* usual household routines here */
		{
		}
	}
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
