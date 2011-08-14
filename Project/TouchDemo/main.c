/**
  ******************************************************************************
  * TouchDemo/main.c 
  * author: Brian
  * version: V0.1.1
  * date: 21 July 2011
  * To Do List:
  *			Documentation!
  ******************************************************************************
  * This file demonstrate the function of LCD board
  ******************************************************************************
  */ 

#include "stm32f10x.h"			/* CMSIS */
#include "miniSTM32.h"			/* mainboard BSP */
#include "miniSTM32_lcd.h"		/* LCD support */
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

#define VERYSHORT_DELAY	100
#define SHORT_DELAY		200
#define MEDIUM_DELAY	500
#define LONG_DELAY		1000

void Touch_Calibration(void);
void Touch_Demo(void);

int main(void)
{
	uint16_t u16Menu = 0;

	/* Initialize SysTick - 1msec */
	SysTick_Config(SystemCoreClock / 1000);

	/* Initialize main board peripherals */
	miniSTM32_BoardInit();
	printf("miniSTM32 mainboard initialized\n");

	/* Initialize LCD */
	LCD_Init();
	Backlight_Off();
	printf("LCD initialized\n");
        
	while (1) 
	{
		if( u16IRQFlag == MAIN_BTN_EXTI_LINE ) {

			u16IRQFlag = 0;

			if( u16Menu == MENU_BLT_ON ) {
				miniSTM32_LEDOn();
				Backlight_On();
				printf("Backlight Turned On\n");
			}
			else if( u16Menu == MENU_TCH_CAL ) {
				printf("Start Calibration\n");
				Touch_Calibration();
			}
			else if( u16Menu == MENU_TCH_DEMO ) {
				printf("Touch Sensor Demo\n");
				Touch_Demo();
			}
			else if( u16Menu == MENU_BLT_OFF) {
				miniSTM32_LEDOff();
				Backlight_Off();
				printf("Backlight Turned Off\n");
			}

			if( ++u16Menu == MENU_END )
				u16Menu = 0;

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
