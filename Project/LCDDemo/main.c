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

/**
 * @brief	Test output to LCD
 * @param	None
 * @retval	None
 */

#if 0

/* delay parameters */
#define VERYSHORT_DELAY	50
#define SHORT_DELAY		100
#define MEDIUM_DELAY	500
#define LONG_DELAY		1000

void TestLCD(void)
{

    int j, k, x1, y1, x2, y2, width, height;
	int red,green,blue;
 	unsigned int active=0;
 	unsigned char maindisppic=0;

	LCD_DisplayOn();
	LCD_BacklightOn();

// 	LCD_Test(active);

	//Delay(0xaffff);
	//Delay(0xafffff);
	//Delay(0xafffff);
	//Delay(0xafffff);

	LCD_Clear(0);

	LCD_DrawBackground(255,255,0); //yellow
	/*
	 * Brian : replace with MSecTimer()
	Delay(0x989680);
	 */
	MSecTimer(MEDIUM_DELAY);

	LCD_Test_BlackToWhite();

	// Draw some 10x10 corner squares
	LCD_DrawRectangle(0,0,10,10, 255,255,255);	// TLC white
	LCD_DrawRectangle((LCD_WIDTH-1)-10,0,(LCD_WIDTH-1),10, 255,255,255);	// TRC white
	LCD_DrawRectangle(0,(LCD_HEIGHT-1)-10,10,(LCD_HEIGHT-1), 255,255,255);	// white
	LCD_DrawRectangle((LCD_WIDTH-1)-10,(LCD_HEIGHT-1)-10,(LCD_WIDTH-1),(LCD_HEIGHT-1), 255,255,255);	// white

	// 
	LCD_DrawRectangle(10,10,50,136, 0,0,255); // blue
	/*
	 * Brian : replace with MSecTimer()
	Delay(0x50000);
	 */
	MSecTimer(SHORT_DELAY);
	LCD_DrawRectangle(430,130,470,256, 255,180,0); // orange
	/*
	 * Brian : replace with MSecTimer()
	Delay(0x50000);
	 */
	MSecTimer(SHORT_DELAY);

	LCD_DrawRectangle(60,20,100,146, 0,255,0); // green
	/*
	 * Brian : replace with MSecTimer()
	Delay(0x50000);
	 */
	MSecTimer(SHORT_DELAY);

	LCD_DrawRectangle(110,30,150,156, 255,0,0);	// red
	/*
	 * Brian : replace with MSecTimer()
	Delay(0x50000);
	 */
	MSecTimer(SHORT_DELAY);

 	LCD_DrawRectangle(160,40,200,166, 255,255,0);	// yellow
	/*
	 * Brian : replace with MSecTimer()
	Delay(0x50000);
	 */
	MSecTimer(SHORT_DELAY);
 	
	LCD_DrawRectangle(210,50,250,176, 255,0,255);	// magenta
	/*
	 * Brian : replace with MSecTimer()
	Delay(0x50000);
	 */
	MSecTimer(SHORT_DELAY);
 	
	LCD_DrawRectangle(260,60,300,186, 0,255,255);	// cyan
	/*
	 * Brian : replace with MSecTimer()
	Delay(0x50000);
	 */
	MSecTimer(SHORT_DELAY);

 	LCD_DrawRectangle(310,70,350,196, 255,255,255);	// white
	/*
	 * Brian : replace with MSecTimer()
	Delay(0x50000);
	 */
	MSecTimer(SHORT_DELAY);


	// Make a loop to draw some arbitrary rectangles in arbitrary RGB 
	// colours in the screen area.
	red = 100;
	green = 120;
	blue = 140;

	
	for (j = 1; j <= 100; j++)
	{
	   x1 = rand()%(LCD_WIDTH-1); 
	   y1 = rand()%(LCD_HEIGHT-1); 
	   width = rand()%130;
	   height = rand()% 210;
	   LCD_DrawRectangle(x1,y1,x1 + width,y1 + height, red, green, blue);
	   red += 8;
	   green += 4;
	   blue += 2;
	   if (red > 255) red = 100;
	   if (green > 255) green = 120;
	   if (blue > 255) blue = 140;
	   
	/*
	 * Brian : replace with MSecTimer()
	   Delay(0x80000);
	 */
		MSecTimer(SHORT_DELAY);

	}
	

	LCD_DrawEllipse(40,40,200,200, 255,0,0);

	LCD_DrawEllipse(210,160,400,230, 0,255,180);
	

	/*
	 * Brian : replace with MSecTimer()
	Delay(0x989680);
	*/		
	MSecTimer(MEDIUM_DELAY);
	LCD_DrawBackground(0,0,0); //black

	x1 = 40;
	y1 = 40;
    red = 32;
	green = 32;
	blue = 32;
	for (k = 0; k < 32; k++)
	{  
		x2 = x1 + 12;
		y2 = y1 + 16;
	   	LCD_DrawRectangle(x1, y1, x2, y2, red, green, 0);
  	   	LCD_DrawRectangle(x1, y1+20, x2, y2+20, red, 0, 0);
 	   	LCD_DrawRectangle(x1, y1+40, x2, y2+40, 0, 0, blue);

	   	x1 += 12;
		red--;
		green --;
		blue--;
	}


	// Draw lines round the edges
	LCD_DrawLine(0,0,(LCD_WIDTH-1),0,3,255,150,40);  	// top
	LCD_DrawLine(0,(LCD_HEIGHT-1),(LCD_WIDTH-1),(LCD_HEIGHT-1),3,255,150,40); // bottom

	LCD_DrawLine(0,0,0,(LCD_HEIGHT-1),3,255,150,40);	 // left
	LCD_DrawLine((LCD_WIDTH-1),0,(LCD_WIDTH-1),(LCD_HEIGHT-1),3,255,150,40); // right
	

	

	// Flash the blue LED (V2) on and off, waiting about 500ms each time.
	  for (k = 0; k < 5; k++)
	  {
	  	GPIO_SetBits(GPIOB, GPIO_Pin_5 );
	/*
	 * Brian : replace with MSecTimer()
		Delay(0x2dc620); // about 500 ms
	 */
		MSecTimer(VERYSHORT_DELAY);
	  	GPIO_ResetBits(GPIOB, GPIO_Pin_5 );
	/*
	 * Brian : replace with MSecTimer()
	 	Delay(0x2dc620); // about 500 ms
	 */
		MSecTimer(VERYSHORT_DELAY);
	  }
	
	  GPIO_WriteBit(GPIOD, GPIO_Pin_13,Bit_RESET);	//LCD Backlight OFF
	  GPIO_WriteBit(GPIOD, GPIO_Pin_13,Bit_SET);	//LCD Backlight ON
	  // Next two lines are equivalent to the two above
	  GPIO_ResetBits(GPIOD, GPIO_Pin_13 ); 			//LCD Backlight OFF
	  GPIO_SetBits(GPIOD, GPIO_Pin_13 ); 		  	//LCD Backlight ON

	 // Draw a series of background colours
	 
		LCD_DrawBackground(0,0,0); //black
	/*
	 * Brian : replace with MSecTimer()
		Delay(0x989680);
	 */
	MSecTimer(MEDIUM_DELAY);
		LCD_DrawBackground(255,0,0); //red
	/*
	 * Brian : replace with MSecTimer()
		Delay(0x989680);
	 */
	MSecTimer(MEDIUM_DELAY);
		LCD_DrawBackground(0,255,0); //green
	/*
	 * Brian : replace with MSecTimer()
		Delay(0x989680);
	 */
	MSecTimer(MEDIUM_DELAY);
		LCD_DrawBackground(0,0,255); //blue
	/*
	 * Brian : replace with MSecTimer()
		Delay(0x989680);
	 */
	MSecTimer(MEDIUM_DELAY);
 		LCD_DrawBackground(0,255,255); //cyan
	/*
	 * Brian : replace with MSecTimer()
		Delay(0x989680);
	 */
	MSecTimer(MEDIUM_DELAY);
		LCD_DrawBackground(255,0,255); //magenta
	/*
	 * Brian : replace with MSecTimer()
		Delay(0x989680);
	 */
	MSecTimer(MEDIUM_DELAY);
		LCD_DrawBackground(255,255,0); //yellow
	/*
	 * Brian : replace with MSecTimer()
		Delay(0x989680);
	 */
	MSecTimer(MEDIUM_DELAY);
		LCD_DrawBackground(255,255,255); //white
	/*
	 * Brian : replace with MSecTimer()
		Delay(0x989680);
	 */
	MSecTimer(MEDIUM_DELAY);
	
	// Loop to just draw low order bits
	for (k = 0; k < 32; k++)
	{
	   LCD_DrawBackground(0, 0, k); // increment blue to max
	/*
	 * Brian : replace with MSecTimer()
	   Delay(0x50000);
	 */
		MSecTimer(SHORT_DELAY);
	} 

	/*
	 * Brian : replace with MSecTimer()
	Delay(0x989680);
	 */
	MSecTimer(MEDIUM_DELAY);
	

	for (k = 0; k < 32; k++)
	{
	   LCD_DrawBackground(0, k, 0); // increment green to max
	/*
	 * Brian : replace with MSecTimer()
	   Delay(0x50000);
	 */
		MSecTimer(SHORT_DELAY);
	} 

	/*
	 * Brian : replace with MSecTimer()
	Delay(0x989680);
	 */
	MSecTimer(MEDIUM_DELAY);
	
	for (k = 0; k < 32; k++)
	{
	   LCD_DrawBackground(k, 0, 0); // increment red	to max
	/*
	 * Brian : replace with MSecTimer()
	   Delay(0x50000);
	 */
//		MSecTimer(VERYSHORT_DELAY);
	} 


	LCD_BacklightOff();
	LCD_DisplayOff();
	
  	// End test code
}

#endif


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
