/*******************************************************************************
 * @file		Project/FontDemo/main.c 
 * @author		Brian
 * @version		V0.1.0
 * @date		21 Oct 2011
 * @brief		This file demonstrate the font drawing functions on LCD
 */ 

#include "stm32f10x.h"			/* CMSIS */
#include "miniSTM32.h"			/* mainboard BSP */
#include "miniSTM32_lcd.h"		/* LCD support */
#include "lcdfonts.h"
#include <stdio.h>

#define START_X			20		/* text start point x */
#define START_Y			20		/* text start point y */
#define	LINE_SEP		20		/* line separation */

/* demo menu list */
enum{
	MENU_FONT_TEST1 = 0,
	MENU_FONT_TEST2,
	MENU_FONT_TEST3,
	MENU_END
};

/* interrupt ID from IRQ routine */
extern volatile uint16_t uIRQFlag;

/**
 * @brief	Main program
 * @param	None
 * @retval	None: no exit point
 */
int main(void)
{
	uint16_t u16Menu = 0;
	uint16_t uVal;

	/* Initialize SysTick - 1msec resolution */
	SysTick_Config(SystemCoreClock / 1000);

	/* Initialize main board peripherals */
	MBD_Init();
	printf("miniSTM32 mainboard initialized.\n");

	/* Initialize LCD support */
	LCD_Init();
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

			/* Microsoft Sans Serif 11 pitch */

			if( u16Menu == MENU_FONT_TEST1 ) {
				uVal = START_Y;
				LCD_Clear(LCD_COLOR_BLACK);
			
				LCD_SetFont(&MSSansSerif_11);
				LCD_SetFGColor(LCD_COLOR_YELLOW);
				LCD_SetBGColor(LCD_COLOR(40,40,80));

				LCD_DisplayStringLine(START_X, uVal, "Microsoft Sans Serif 11 point");

				LCD_SetFont(&MSSansSerif_13); 
				uVal += MSSansSerif_11.Height + LINE_SEP;
				LCD_DisplayStringLine(START_X, uVal, "Microsoft Sans Serif 13 point");

				LCD_SetFont(&MSSansSerif_16);
				uVal += MSSansSerif_13.Height + LINE_SEP;
				LCD_DisplayStringLine(START_X, uVal, "Microsoft Sans Serif 16 point");

				LCD_SetFont(&MSSansSerif_19);
				uVal += MSSansSerif_16.Height + LINE_SEP;
				LCD_DisplayStringLine(START_X, uVal, "Microsoft Sans Serif 19 point");

				LCD_SetFont(&MSSansSerif_24);
				uVal += MSSansSerif_19.Height + LINE_SEP;
				LCD_DisplayStringLine(START_X, uVal, "Microsoft Sans Serif 24 point");

				LCD_SetFont(&MSSansSerif_32);
				uVal += MSSansSerif_24.Height + LINE_SEP;
				LCD_DisplayStringLine(START_X, uVal, "Microsoft Sans Serif 32 point");
			}
			else if( u16Menu == MENU_FONT_TEST2 ) {
				uVal = START_Y;
				LCD_Clear(LCD_COLOR_BLACK);
			
				LCD_SetFont(&MSSerif_11);
				LCD_SetFGColor(LCD_COLOR_YELLOW);
				LCD_SetBGColor(LCD_COLOR(40,40,80));

				LCD_DisplayStringLine(START_X, uVal, "Microsoft Serif 11 point");

				LCD_SetFont(&MSSerif_13); 
				uVal += MSSerif_11.Height + LINE_SEP;
				LCD_DisplayStringLine(START_X, uVal, "Microsoft Serif 13 point");

				LCD_SetFont(&MSSerif_16);
				uVal += MSSerif_13.Height + LINE_SEP;
				LCD_DisplayStringLine(START_X, uVal, "Microsoft Serif 16 point");

				LCD_SetFont(&MSSerif_19);
				uVal += MSSerif_16.Height + LINE_SEP;
				LCD_DisplayStringLine(START_X, uVal, "Microsoft Serif 19 point");

				LCD_SetFont(&MSSerif_24);
				uVal += MSSerif_19.Height + LINE_SEP;
				LCD_DisplayStringLine(START_X, uVal, "Microsoft Serif 24 point");

				LCD_SetFont(&MSSerif_32);
				uVal += MSSerif_24.Height + LINE_SEP;
				LCD_DisplayStringLine(START_X, uVal, "Microsoft Serif 32 point");
			}
			else if( u16Menu == MENU_FONT_TEST3 ) {
				uVal = START_Y;
				LCD_Clear(LCD_COLOR_BLACK);
			
				LCD_SetFont(&Terminal_12);
				LCD_SetFGColor(LCD_COLOR_YELLOW);
				LCD_SetBGColor(LCD_COLOR(40,40,80));

				LCD_DisplayStringLine(START_X, uVal, "Microsoft Terminal 12 point");

				LCD_SetFont(&Terminal_16); 
				uVal += Terminal_12.Height + LINE_SEP;
				LCD_DisplayStringLine(START_X, uVal, "Microsoft Terminal 16 point");

				LCD_SetFont(&Terminal_20);
				uVal += Terminal_16.Height + LINE_SEP;
				LCD_DisplayStringLine(START_X, uVal, "Microsoft Terminal 20 point");

				LCD_SetFont(&Terminal_23);
				uVal += Terminal_20.Height + LINE_SEP;
				LCD_DisplayStringLine(START_X, uVal, "Microsoft Terminal 23 point");
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
