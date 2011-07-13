/**
  ******************************************************************************
  * SIOTest/main.c 
  * author: Brian
  * version: V0.1.0
  * date: 06 July 2011
  * To Do List:
  *		- PWM output to the piezo transducer
  *		- ADC input from the potentiometer
  *		- key debouncing algorithm (may require FreeRTOS)
  ******************************************************************************
  * This file demonstrate the function of SIO board
  * Be sure to turn on the -D USE_MINISTM32_SIO flag in your Makefile
  ******************************************************************************
  */ 

#include "stm32f10x.h"
#include "stm32_eval.h"
#include <stdio.h>

void COMPort_Init(void);
void delay_loop(void);
volatile uint32_t uIntFlag = 0;

#if 0
#ifdef __GNUC__
	/* With GCC, small printf (option LD Linker->Libraries->Small printf
	set to 'Yes') calls __io_putchar() */
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
#endif

void delay_loop(void)
{
	volatile uint32_t u32Count = 1000000L;

	while ( u32Count > 0 )
		u32Count--;
}

int main(void)
{
	uint16_t u16Freq = MIN_PIEZO_FREQ;

	/* Initialize the main board peripherals */
	COMPort_Init();
	printf("COM Port initialized\n");

	/* Initialize the extension board */
	miniSTM32_SIO_BoardInit();
	printf("SIO board initialized\n");

	while (1) {
		if( uIntFlag == 2 ) {
			miniSTM32_SIO_LEDToggle(SIO_LED1);
			printf("Key 1 is depressed.\n");
			delay_loop();	/* quick and dirty method of debouncing */
			uIntFlag = 0;
		}
		else if( uIntFlag == 3 ) {

			miniSTM32_SIO_PiezoControl( u16Freq );

			u16Freq += 1000;
			if( u16Freq > MAX_PIEZO_FREQ )
				u16Freq = MIN_PIEZO_FREQ;

			miniSTM32_SIO_LEDToggle(SIO_LED2);
			printf("Key 2 is depressed.\n");
			delay_loop();	/* quick and dirty method of debouncing */
			uIntFlag = 0;
		}
	}
}

/**
 * Initialize USART1 for debug message out
 */

void COMPort_Init(void)
{
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	STM_EVAL_COMInit(COM1, &USART_InitStructure);
}


/**
 * Retargets the C library printf function to the USART.
*/
__io_putchar(int ch)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(EVAL_COM1, (uint8_t) ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET)
	{}

	return ch;
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

#endif

/* END OF FILE */
