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

#define START_X			15		/* text start point x */
#define START_Y			20		/* text start point y */
#define	LINE_SEP		15		/* line separation */

/* demo menu list */
enum{
	MENU_FONT_TEST1 = 0,
	MENU_FONT_TEST2,
	MENU_FONT_TEST3,
	MENU_FONT_TEST4,
	MENU_END
};

/* interrupt ID from IRQ routine */
extern volatile uint16_t uIRQFlag;
void NVIC_Relocate(void);

/**
 * @brief	Main program
 * @param	None
 * @retval	None: no exit point
 */
int main(void)
{
	uint16_t u16Menu = 0;
	uint16_t uVal;

	NVIC_Relocate();

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

			/* droid family fonts */

			if( u16Menu == MENU_FONT_TEST1 ) {
				uVal = START_Y;
				LCD_Clear(LCD_COLOR_BLACK);
				LCD_SetFGColor(LCD_COLOR_YELLOW);
				LCD_SetBGColor(LCD_COLOR(40,40,80));

			/* 2.4inch LCD has not enough space to draw long string */
			#if defined(LCD_QD024CPS25)

				LCD_SetFont(&DroidSans_18);
				LCD_DisplayStringLine(START_X, uVal, "Droid Sans 18 point");

				uVal += DroidSans_18.Height + LINE_SEP;
				LCD_SetFont(&DroidSans_Bold_18); 
				LCD_DisplayStringLine(START_X, uVal, "Droid Sans Bold 18 pt");

				uVal += DroidSans_Bold_18.Height + LINE_SEP;
				LCD_SetFont(&DroidSerif_18); 
				LCD_DisplayStringLine(START_X, uVal, "Droid Serif 18 point");

				uVal += DroidSerif_18.Height + LINE_SEP;
				LCD_SetFont(&DroidSerif_Bold_18); 
				LCD_DisplayStringLine(START_X, uVal, "Droid Serif Bold 18 pt");

				uVal += DroidSerif_Bold_18.Height + LINE_SEP;
				LCD_SetFont(&DroidSerif_Italic_18); 
				LCD_DisplayStringLine(START_X, uVal, "Droid Serif Italic 18");

			#else

				LCD_SetFont(&DroidSans_18);
				LCD_DisplayStringLine(START_X, uVal, "Droid Sans 18 point");

				uVal += DroidSans_18.Height + LINE_SEP;
				LCD_SetFont(&DroidSans_Bold_18); 
				LCD_DisplayStringLine(START_X, uVal, "Droid Sans Bold 18 point");

				uVal += DroidSans_Bold_18.Height + LINE_SEP;
				LCD_SetFont(&DroidSerif_18); 
				LCD_DisplayStringLine(START_X, uVal, "Droid Serif 18 point");

				uVal += DroidSerif_18.Height + LINE_SEP;
				LCD_SetFont(&DroidSerif_Bold_18); 
				LCD_DisplayStringLine(START_X, uVal, "Droid Serif Bold 18 point");

				uVal += DroidSerif_Bold_18.Height + LINE_SEP;
				LCD_SetFont(&DroidSerif_Italic_18); 
				LCD_DisplayStringLine(START_X, uVal, "Droid Serif Italic 18 point");

			#endif
			}

			/* liberation family fonts, federant font */

			else if( u16Menu == MENU_FONT_TEST2 ) {
				uVal = START_Y;
				LCD_Clear(LCD_COLOR_BLACK);
				LCD_SetFGColor(LCD_COLOR_YELLOW);
				LCD_SetBGColor(LCD_COLOR(40,40,80));

			/* 2.4inch LCD has not enough space to draw long string */
			#if defined(LCD_QD024CPS25)

				LCD_SetFont(&LiberationSans_18);
				LCD_DisplayStringLine(START_X, uVal, "Liberation Sans 18 point");

				uVal += LiberationSans_18.Height + LINE_SEP;
				LCD_SetFont(&LiberationSerif_18); 
				LCD_DisplayStringLine(START_X, uVal, "Liberation Serif 18 point");

				uVal += LiberationSerif_18.Height + LINE_SEP;
				LCD_SetFont(&LiberationSerif_Italic_18); 
				LCD_DisplayStringLine(START_X, uVal, "Liberation Serif Italic 18");

				uVal += LiberationSerif_Italic_18.Height + LINE_SEP;
				LCD_SetFont(&Federant_18); 
				LCD_DisplayStringLine(START_X, uVal, "Federant 18 point");

			#else

				LCD_SetFont(&LiberationSans_18);
				LCD_DisplayStringLine(START_X, uVal, "Liberation Sans 18 point");

				uVal += LiberationSans_18.Height + LINE_SEP;
				LCD_SetFont(&LiberationSerif_18); 
				LCD_DisplayStringLine(START_X, uVal, "Liberation Serif 18 point");

				uVal += LiberationSerif_18.Height + LINE_SEP;
				LCD_SetFont(&LiberationSerif_Italic_18); 
				LCD_DisplayStringLine(START_X, uVal, "Liberation Serif Italic 18 point");

				uVal += LiberationSerif_Italic_18.Height + LINE_SEP;
				LCD_SetFont(&Federant_18); 
				LCD_DisplayStringLine(START_X, uVal, "Federant 18 point");

			#endif
			}

			/* Ubuntu family fonts */

			else if( u16Menu == MENU_FONT_TEST3 ) {
				uVal = START_Y;
				LCD_Clear(LCD_COLOR_BLACK);
				LCD_SetFGColor(LCD_COLOR_YELLOW);
				LCD_SetBGColor(LCD_COLOR(40,40,80));
			
			/* 2.4inch LCD has not enough space to draw long string */
			#if defined(LCD_QD024CPS25)

				LCD_SetFont(&Ubuntu_18);
				LCD_DisplayStringLine(START_X, uVal, "Ubuntu 18 point");

				uVal += Ubuntu_18.Height + LINE_SEP;
				LCD_SetFont(&Ubuntu_Bold_18); 
				LCD_DisplayStringLine(START_X, uVal, "Ubuntu Bold 18 point");

				uVal += Ubuntu_Bold_18.Height + LINE_SEP;
				LCD_SetFont(&Ubuntu_Italic_18); 
				LCD_DisplayStringLine(START_X, uVal, "Ubuntu Italic 18");

			#else

				LCD_SetFont(&Ubuntu_18);
				LCD_DisplayStringLine(START_X, uVal, "Ubuntu 18 point");

				uVal += Ubuntu_18.Height + LINE_SEP;
				LCD_SetFont(&Ubuntu_Bold_18); 
				LCD_DisplayStringLine(START_X, uVal, "Ubuntu Bold 18 point");

				uVal += Ubuntu_Bold_18.Height + LINE_SEP;
				LCD_SetFont(&Ubuntu_Italic_18); 
				LCD_DisplayStringLine(START_X, uVal, "Ubuntu Italic 18 point");

			#endif
			}

			/* various size of droid sans */

			else if( u16Menu == MENU_FONT_TEST4 ) {
				uVal = START_Y;
				LCD_Clear(LCD_COLOR_BLACK);
				LCD_SetFGColor(LCD_COLOR_YELLOW);
				LCD_SetBGColor(LCD_COLOR(40,40,80));

				LCD_SetFont(&DroidSans_10);
				LCD_DisplayStringLine(START_X, uVal, "DroidSans 10 point");

				uVal += DroidSans_10.Height + LINE_SEP;
				LCD_SetFont(&DroidSans_12); 
				LCD_DisplayStringLine(START_X, uVal, "DroidSans 12 point");

				uVal += DroidSans_12.Height + LINE_SEP;
				LCD_SetFont(&DroidSans_14); 
				LCD_DisplayStringLine(START_X, uVal, "DroidSans 14 point");

				uVal += DroidSans_14.Height + LINE_SEP;
				LCD_SetFont(&DroidSans_16); 
				LCD_DisplayStringLine(START_X, uVal, "DroidSans 16 point");

				uVal += DroidSans_16.Height + LINE_SEP;
				LCD_SetFont(&DroidSans_18); 
				LCD_DisplayStringLine(START_X, uVal, "DroidSans 18 point");

				uVal += DroidSans_18.Height + LINE_SEP;
				LCD_SetFont(&DroidSans_20); 
				LCD_DisplayStringLine(START_X, uVal, "DroidSans 20 point");

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

void NVIC_Relocate(void)
{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x6800);
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
