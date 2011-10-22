/*******************************************************************************
 * @file		Project/LCDDemo/main.c 
 * @author		Brian
 * @version		V0.2.0
 * @date		21 July 2011
 * @brief		This file demonstrate the function of LCD board
 */ 

#include "stm32f10x.h"			/* CMSIS */
#include "miniSTM32.h"			/* mainboard BSP */
#include "miniSTM32_lcd.h"		/* LCD support */
#include <stdio.h>

/* demo menu list */
enum{
	MENU_LCD_TEST1 = 0,
	MENU_LCD_TEST2,
	MENU_LCD_TEST3,
	MENU_LCD_TEST4,
	MENU_LCD_TEST5,
	MENU_LCD_TEST6,
	MENU_LCD_TEST7,
	MENU_LCD_TEST8,
	MENU_LCD_TEST9,
	MENU_LCD_TESTX,
	MENU_END
};

/* interrupt ID from IRQ routine */
extern volatile uint16_t uIRQFlag;


#if 0 /* OBSOLETE */
void TestLCD(void);
#endif

/**
 * @brief	Main program
 * @param	None
 * @retval	None: no exit point
 */
int main(void)
{
	uint16_t u16Menu=0;
	uint16_t uVal;

	/* Initialize SysTick - 1msec resolution */
	SysTick_Config(SystemCoreClock / 1000);

	/* Initialize main board peripherals */
	MBD_Init();
	printf("miniSTM32 mainboard initialized.\n");

	/* Initialize LCD support */
	LCD_Init();
	LCD_Clear(LCD_COLOR_BLACK);
	LCD_DisplayOn();
	printf("LCD initialized.\n");
	LCD_BacklightOn();
	printf("\n\nPress the button to start demo.\n\n");

	while (1) 
	{
		/* main menu controlled by pushbutton interrupt */
		if( uIRQFlag == MAIN_BTN_EXTI_LINE ) {

			/* clear button interrupt flag */
			uIRQFlag = 0;

			if( u16Menu == MENU_LCD_TEST1 ) {
				printf("Drawing 640 lines                          ---> %d msec\n",
					LCD_DrawTestPattern(1));
			}
			else if( u16Menu == MENU_LCD_TEST2 ) {
				printf("Drawing 256 lines(pen width 5)             ---> %d msec\n",
					LCD_DrawTestPattern(2));
			}
			else if( u16Menu == MENU_LCD_TEST3 ) {
				printf("Drawing 8 rectangles(various pen width)    ---> %d msec\n",
					LCD_DrawTestPattern(3));
			}
			else if( u16Menu == MENU_LCD_TEST4 ) {
				printf("Drawing 8 circles(various pen width)       ---> %d msec\n",
					LCD_DrawTestPattern(4));
			}
			else if( u16Menu == MENU_LCD_TEST5 ) {
				printf("Drawing 8 ellipses(various pen width)      ---> %d msec\n",
					LCD_DrawTestPattern(5));
			}
			else if( u16Menu == MENU_LCD_TEST6 ) {
				printf("Drawing circles with ellipse routine       ---> %d msec\n",
					LCD_DrawTestPattern(6));
			}
			else if( u16Menu == MENU_LCD_TEST7 ) {
				printf("Drawing 8 solid rectangles                 ---> %d msec\n",
					LCD_DrawTestPattern(7));
			}
			else if( u16Menu == MENU_LCD_TEST8 ) {
				printf("Drawing 8 solid circles                    ---> %d msec\n",
					LCD_DrawTestPattern(8));
			}
			else if( u16Menu == MENU_LCD_TEST9 ) {
				printf("Drawing solid circles with ellipse routine ---> %d msec\n",
					LCD_DrawTestPattern(9));
			}
			else if( u16Menu == MENU_LCD_TESTX ) {
				printf("Drawing color contrast bars                ---> %d msec\n",
					LCD_DrawTestPattern(0));
			}

			/* at the end of menu, restart all over */
			if( ++u16Menu == MENU_END )
			{
				printf("\n\nEnd of Demo: Press the button to restart... \n\n\n");
				u16Menu = 0;
			}

		}

		/* usual household routine goes here */
		{
		}
	}
}


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
