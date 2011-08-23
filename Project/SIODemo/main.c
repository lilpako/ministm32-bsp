/*******************************************************************************
 * @file	Project/SIODemo/main.c 
 * @author	Brian
 * @version	V0.1.1
 * @date	21 July 2011
 * @brief	This file demonstrate the function of SIO board
 ******************************************************************************
 */ 

#include "stm32f10x.h"
#include "miniSTM32.h"
#include "miniSTM32_sio.h"
#include <stdio.h>

extern volatile uint16_t u16IRQFlag;		/* IRQ number for your reference */
extern volatile uint16_t u16LEDFlasher;		/* LED auto turn-off duration */

/* demo menu list */
enum menuItem{
	menuFirst = 0,
	menuLED = 0,
	menuPIEZO,
	menuPOT,
	menuLast
	};

/* menu string */
char* menuString[] = {
	"(1) LED On//OFF Control\n", \
	"(2) Piezo Buzzer Frequency Control\n", \
	"(3) Potentiometer Readout\n"
};


/**
 * @brief	Main program
 * @param	None
 * @retval	None: no exit point
 */
int main(void)
{
	uint16_t u16Freq = MIN_PIEZO_FREQ;	/* pwn frequency of piezo drive */
	uint16_t u16Menu = menuFirst;		/* menu index */
	uint16_t u16Value;					/* general use */

	/* Initialize SysTick - 1msec */
	SysTick_Config(SystemCoreClock / 1000);

	/* Initialize peripherals */
	mSTM_COMInit(115200);
	printf("COM Port initialized\n");

	/* Initialize the extension board */
	mSTM_SIO_BoardInit();
	printf("SIO board initialized\n");

	/* First menu item */
	printf(menuString[u16Menu]);

	while (1) 
	{
		/* IRQ2: menu selection button pressed */
		if( u16IRQFlag == 2 ) 
		{
			u16IRQFlag = 0;
			
			u16Menu++;
			if(u16Menu == menuLast)
				u16Menu = menuFirst;

			printf(menuString[u16Menu]);

			/* flash LED1 once */
			mSTM_SIO_LEDOn(SIO_LED1);
			/* after 300msec it will turn off */
			u16LEDFlasher = 300;

			/* it would be nice to turn off LED and Piezo
			 * when you change the menu 
			 */
			{
				mSTM_SIO_LEDOff(SIO_LED2);
				mSTM_SIO_PiezoControl( 0 );
			}
		}
		/* IRQ3: menu execution button pressed */
		else if( u16IRQFlag == 3 ) 
		{
			u16IRQFlag = 0;
			
			if(u16Menu == menuLED) 
			{
				mSTM_SIO_LEDToggle(SIO_LED2);

				/* now read the LED status back */
				if(mSTM_SIO_LEDGetStatus(SIO_LED2))
					printf(" ---LED ON\n");
				else
					printf(" ---LED OFF\n");
			}
			else if(u16Menu == menuPIEZO) 
			{
				mSTM_SIO_PiezoControl( u16Freq );
				printf(" ---%dHz\n", u16Freq);

				/* increse the frequency automatically */
				u16Freq += 1000;

				if( u16Freq > MAX_PIEZO_FREQ )
					u16Freq = MIN_PIEZO_FREQ;
			}
			else if(u16Menu == menuPOT) 
			{
				u16Value = mSTM_SIO_POTGetValue();
				printf(" ---%d\n", u16Value);
			}
		}

		/* usual household routines */
		{
			/* turn off the LED1 after some time */
			if( u16LEDFlasher == 0)
				mSTM_SIO_LEDOff(SIO_LED1);
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

/* End of File */
