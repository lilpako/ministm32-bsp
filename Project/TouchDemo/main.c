/*******************************************************************************
 * TouchDemo/main.c 
 * author: Brian
 * version: V0.1.1
 * date: 21 July 2011
 */ 

#include "stm32f10x.h"			/* CMSIS */
#include "miniSTM32.h"			/* mainboard BSP */
#include "miniSTM32_lcd.h"		/* LCD support */
#include "miniSTM32_tsc.h"		/* touch screen controller */
#include <stdio.h>

/* demo menu list */
enum{
	MENU_BLT_ON = 0,
	MENU_TCH_CAL,
	MENU_TCH_DEMO,
	MENU_BLT_OFF,
	MENU_END
};

/* interrupt ID from IRQ routines */
extern volatile uint16_t u16IRQFlag;
extern void MsecDelay( uint16_t u16Delay );

extern unsigned int  HDP;
extern unsigned int  VDP;

void Touch_Calibration(void);
void Touch_Demo(void);

int main(void)
{
	uint16_t u16Menu = 0;
	uint16_t u16Value = 0;

	/* Initialize SysTick - 1msec */
	SysTick_Config(SystemCoreClock / 1000);

	/* Initialize main board peripherals */
	mSTM_BoardInit();
	printf("miniSTM32 mainboard initialized\n");

	/* Initialize LCD */
	mSTM_LCDInit();
	mSTM_BLTOff();
	printf("LCD initialized\n");

	/* Initialize touch screen controller */
	TSCInit();
	printf("Touch controller initialized\n\n");
        
	while (1) 
	{
		if( u16IRQFlag == MAIN_BTN_EXTI_LINE ) {

			u16IRQFlag = 0;

/*
			if( u16Menu == MENU_BLT_ON ) {
				mSTM_LEDOn();
				mSTM_BLTOn();
				printf("Backlight Turned On\n");
			}
			else if( u16Menu == MENU_TCH_CAL ) {
				printf("Start Calibration\n");
				Touch_Calibration();
			}
			else if( u16Menu == MENU_TCH_DEMO ) {
				printf("Touch Controller Demo\n");
				Touch_Demo();
			}
			else if( u16Menu == MENU_BLT_OFF) {
				mSTM_LEDOff();
				mSTM_BLTOff();
				printf("Backlight Turned Off\n");
			}

			if( ++u16Menu == MENU_END )
				u16Menu = 0;

*/

			u16Value = mSTM_TSCRead_X();
			printf("mSTM_TSCRead_X : %d\n", u16Value);
			u16Value = mSTM_TSCRead_Y();
			printf("mSTM_TSCRead_Y : %d\n\n", u16Value);
		}

		else if( u16IRQFlag == MAIN_TSC_INT_EXTI_LINE ) {
			u16IRQFlag = 0;
			printf("Screen touch detected\n");
		}
		/* usual household routines here */
		{
		}
	}
}

void Touch_Calibration(void)
{
}

void Touch_Demo(void)
{
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
