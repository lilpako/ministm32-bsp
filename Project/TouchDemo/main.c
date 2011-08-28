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
extern volatile uint16_t uIRQFlag;

extern unsigned int  HDP;
extern unsigned int  VDP;

extern volatile uint16_t uTSC_ValueX;
extern volatile uint16_t uTSC_ValueY;
extern volatile TouchStatus TSC_Status;

void Touch_Calibration(void);
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
	TSCInit();
	printf("Touch controller initialized\n\n");
        
	while (1) 
	{
		if( uIRQFlag == MAIN_BTN_EXTI_LINE ) {

			printf("Button pressed\n");
			uIRQFlag = 0;
			TSC_Status = TOUCH_DETECTED;

		}

		else if(TSC_Status == TOUCH_CALIBRATED)
		{
			printf("Touch detected: %d, %d\n", uTSC_ValueX, uTSC_ValueY);	
			TSC_Status = TOUCH_IDLE;

		}
		/* usual household routines here */
		{
			TouchRoutine();
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
