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
	MENU_TCH_CAL = 0,
	MENU_TCH_CHK,
	MENU_TCH_DEMO,
	MENU_END
};

/* interrupt ID from IRQ routines */
extern volatile uint16_t uIRQFlag;

extern unsigned int  HDP;
extern unsigned int  VDP;

extern volatile uint16_t uTSC_ValueX;
extern volatile uint16_t uTSC_ValueY;
extern volatile TouchStatus TSC_Status;

void Touch_Demo(void);

int main(void)
{
	uint16_t u16Menu = 0;

	/* Initialize SysTick - 1msec */
	SysTick_Config(SystemCoreClock / 1000);

	/* Initialize main board peripherals */
	MBD_Init();
	printf("miniSTM32 mainboard initialized\n");

	/* Initialize LCD */
	LCD_Init();
	LCD_BacklightOff();
	printf("LCD initialized\n");

	/* Initialize touch screen controller */
	TSC_Init();
	printf("Touch controller initialized\n");
	printf("Press the pushbutton to start\n\n");
        
	while (1) 
	{
		if( uIRQFlag == MAIN_BTN_EXTI_LINE ) {

			if( u16Menu == MENU_TCH_CAL ) {
				TSC_Calibration();
				printf("Calibration done\n");
				printf("Press the pushbutton to proceed\n");
			}
			else if( u16Menu == MENU_TCH_CHK ) {
				TSC_CheckCalibration();
			}
			else if( u16Menu == MENU_TCH_DEMO ) {
				Touch_Demo();
				printf("End of Demo\n");
				printf("Press the pushbutton to restart\n");
			}

			u16Menu++;
			if(u16Menu == MENU_END) u16Menu = MENU_TCH_CAL;

		}
		/* usual household routines here */
		{
		}
	}
}


void Touch_Demo(void)
{
	uint16_t u16Count = 0;
	uint16_t u16X, u16Y;

	LCD_BacklightOn();

	while(u16Count < 20)
	{
		printf("Waiting for touch(%d)\n", u16Count + 1);
		
		TSC_WaitForTouch();

		u16X = TSC_GetDisplayX(uTSC_ValueX, uTSC_ValueY);
		u16Y = TSC_GetDisplayY(uTSC_ValueX, uTSC_ValueY);

		LCD_DrawLine(u16X - 5, u16Y, u16X + 5, u16Y, 5, 50, 200, 50);
		LCD_DrawLine(u16X, u16Y - 5, u16X, u16Y +5, 5, 50, 200, 50);

		u16Count++;
	}

	LCD_Clear();
	LCD_BacklightOff();

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
