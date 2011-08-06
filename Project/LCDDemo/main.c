/**
  ******************************************************************************
  * LCDDemo/main.c 
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
#include "miniSTM32_lcd.h"		/* SDIO - SD support */
#include <stdio.h>

/* demo menu list */
enum{
	MENU_LED_ON = 0,
	MENU_LED_OFF,
	MENU_LCD_TEST,
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

void TestLCD(void);

int main(void)
{
	uint16_t u16Menu=0;

	/* Initialize SysTick - 1msec */
	SysTick_Config(SystemCoreClock / 1000);

	/* Initialize main board peripherals */
	miniSTM32_BoardInit();
	printf("miniSTM32 mainboard initialized\n");

	/* Initialize LCD */
	LCD_Init();
	printf("LCD initialized\n");

        
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
			else if( u16Menu == MENU_LCD_TEST ) {
				TestLCD();
				printf("LCD test finished\n");
			}

			if( ++u16Menu == MENU_END )
				u16Menu = 0;

		}

		/* usual household routines here */
		{
		}
	}
}

void TestLCD(void)
{

    int j, k, x1, y1, x2, y2, width, height;
	int red,green,blue;
 	unsigned int active=0;
 	unsigned char maindisppic=0;

 	LCD_Test(active);

	//Delay(0xaffff);
	//Delay(0xafffff);
	//Delay(0xafffff);
	//Delay(0xafffff);

	LCD_Clear(0);
	LCD_DrawBackground(255,255,0); //yellow
	/*
	 * Brian : replace with MsecDelay()
	Delay(0x989680);
	 */
	MsecDelay(MEDIUM_DELAY);

	LCD_Test_BlackToWhite();

	// Draw some 10x10 corner squares
	LCD_DrawRectangle(0,0,10,10, 255,255,255);	// TLC white
	LCD_DrawRectangle(HDP-10,0,HDP,10, 255,255,255);	// TRC white
	LCD_DrawRectangle(0,VDP-10,10,VDP, 255,255,255);	// white
	LCD_DrawRectangle(HDP-10,VDP-10,HDP,VDP, 255,255,255);	// white

	// 
	LCD_DrawRectangle(10,10,50,136, 0,0,255); // blue
	/*
	 * Brian : replace with MsecDelay()
	Delay(0x50000);
	 */
	MsecDelay(SHORT_DELAY);
	LCD_DrawRectangle(430,130,470,256, 255,180,0); // orange
	/*
	 * Brian : replace with MsecDelay()
	Delay(0x50000);
	 */
	MsecDelay(SHORT_DELAY);

	LCD_DrawRectangle(60,20,100,146, 0,255,0); // green
	/*
	 * Brian : replace with MsecDelay()
	Delay(0x50000);
	 */
	MsecDelay(SHORT_DELAY);

	LCD_DrawRectangle(110,30,150,156, 255,0,0);	// red
	/*
	 * Brian : replace with MsecDelay()
	Delay(0x50000);
	 */
	MsecDelay(SHORT_DELAY);

 	LCD_DrawRectangle(160,40,200,166, 255,255,0);	// yellow
	/*
	 * Brian : replace with MsecDelay()
	Delay(0x50000);
	 */
	MsecDelay(SHORT_DELAY);
 	
	LCD_DrawRectangle(210,50,250,176, 255,0,255);	// magenta
	/*
	 * Brian : replace with MsecDelay()
	Delay(0x50000);
	 */
	MsecDelay(SHORT_DELAY);
 	
	LCD_DrawRectangle(260,60,300,186, 0,255,255);	// cyan
	/*
	 * Brian : replace with MsecDelay()
	Delay(0x50000);
	 */
	MsecDelay(SHORT_DELAY);

 	LCD_DrawRectangle(310,70,350,196, 255,255,255);	// white
	/*
	 * Brian : replace with MsecDelay()
	Delay(0x50000);
	 */
	MsecDelay(SHORT_DELAY);


	// Make a loop to draw some arbitrary rectangles in arbitrary RGB 
	// colours in the screen area.
	red = 100;
	green = 120;
	blue = 140;

	
	for (j = 1; j <= 100; j++)
	{
	   x1 = rand()%HDP; 
	   y1 = rand()%VDP; 
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
	 * Brian : replace with MsecDelay()
	   Delay(0x80000);
	 */
		MsecDelay(SHORT_DELAY);

	}
	

	LCD_DrawEllipse(40,40,200,200, 255,0,0);

	LCD_DrawEllipse(210,160,400,230, 0,255,180);
	

	/*
	 * Brian : replace with MsecDelay()
	Delay(0x989680);
	*/		
	MsecDelay(MEDIUM_DELAY);
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
	LCD_DrawLine(0,0,HDP,0,3,255,150,40);  	// top
	LCD_DrawLine(0,VDP,HDP,VDP,3,255,150,40); // bottom

	LCD_DrawLine(0,0,0,VDP,3,255,150,40);	 // left
	LCD_DrawLine(HDP,0,HDP,VDP,3,255,150,40); // right
	

	

	// Flash the blue LED (V2) on and off, waiting about 500ms each time.
	  for (k = 0; k < 5; k++)
	  {
	  	GPIO_SetBits(GPIOB, GPIO_Pin_5 );
	/*
	 * Brian : replace with MsecDelay()
		Delay(0x2dc620); // about 500 ms
	 */
		MsecDelay(VERYSHORT_DELAY);
	  	GPIO_ResetBits(GPIOB, GPIO_Pin_5 );
	/*
	 * Brian : replace with MsecDelay()
	 	Delay(0x2dc620); // about 500 ms
	 */
		MsecDelay(VERYSHORT_DELAY);
	  }
	
	  GPIO_WriteBit(GPIOD, GPIO_Pin_13,Bit_RESET);	//LCD Backlight OFF
	  GPIO_WriteBit(GPIOD, GPIO_Pin_13,Bit_SET);	//LCD Backlight ON
	  // Next two lines are equivalent to the two above
	  GPIO_ResetBits(GPIOD, GPIO_Pin_13 ); 			//LCD Backlight OFF
	  GPIO_SetBits(GPIOD, GPIO_Pin_13 ); 		  	//LCD Backlight ON

	 // Draw a series of background colours
	 
		LCD_DrawBackground(0,0,0); //black
	/*
	 * Brian : replace with MsecDelay()
		Delay(0x989680);
	 */
	MsecDelay(MEDIUM_DELAY);
		LCD_DrawBackground(255,0,0); //red
	/*
	 * Brian : replace with MsecDelay()
		Delay(0x989680);
	 */
	MsecDelay(MEDIUM_DELAY);
		LCD_DrawBackground(0,255,0); //green
	/*
	 * Brian : replace with MsecDelay()
		Delay(0x989680);
	 */
	MsecDelay(MEDIUM_DELAY);
		LCD_DrawBackground(0,0,255); //blue
	/*
	 * Brian : replace with MsecDelay()
		Delay(0x989680);
	 */
	MsecDelay(MEDIUM_DELAY);
 		LCD_DrawBackground(0,255,255); //cyan
	/*
	 * Brian : replace with MsecDelay()
		Delay(0x989680);
	 */
	MsecDelay(MEDIUM_DELAY);
		LCD_DrawBackground(255,0,255); //magenta
	/*
	 * Brian : replace with MsecDelay()
		Delay(0x989680);
	 */
	MsecDelay(MEDIUM_DELAY);
		LCD_DrawBackground(255,255,0); //yellow
	/*
	 * Brian : replace with MsecDelay()
		Delay(0x989680);
	 */
	MsecDelay(MEDIUM_DELAY);
		LCD_DrawBackground(255,255,255); //white
	/*
	 * Brian : replace with MsecDelay()
		Delay(0x989680);
	 */
	MsecDelay(MEDIUM_DELAY);
	
	// Loop to just draw low order bits
	for (k = 0; k < 32; k++)
	{
	   LCD_DrawBackground(0, 0, k); // increment blue to max
	/*
	 * Brian : replace with MsecDelay()
	   Delay(0x50000);
	 */
		MsecDelay(SHORT_DELAY);
	} 

	/*
	 * Brian : replace with MsecDelay()
	Delay(0x989680);
	 */
	MsecDelay(MEDIUM_DELAY);
	

	for (k = 0; k < 32; k++)
	{
	   LCD_DrawBackground(0, k, 0); // increment green to max
	/*
	 * Brian : replace with MsecDelay()
	   Delay(0x50000);
	 */
		MsecDelay(SHORT_DELAY);
	} 

	/*
	 * Brian : replace with MsecDelay()
	Delay(0x989680);
	 */
	MsecDelay(MEDIUM_DELAY);
	
	for (k = 0; k < 32; k++)
	{
	   LCD_DrawBackground(k, 0, 0); // increment red	to max
	/*
	 * Brian : replace with MsecDelay()
	   Delay(0x50000);
	 */
		MsecDelay(SHORT_DELAY);
	} 
	
  	// End test code
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
