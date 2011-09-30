/*******************************************************************************
 * @file	Project/FMathDemo/main.c 
 * @author	Brian
 * @version	V0.2.0
 * @date	21 July 2011
 * @brief	This file demonstrate the function of FixMath routines
 */ 

#include "stm32f10x.h"				/* CMSIS */
#include "miniSTM32.h"				/* mainboard BSP */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

#include "fixmath.h"

/* demo menu list */
enum{
	MENU_FMATH_DEMO1 = 0,
	MENU_END
};

/* interrupt ID from IRQ routines */
extern volatile uint16_t uIRQFlag;
extern volatile uint32_t uSysTick;

void FixMathDemo(void);

int main(void) 
{
	uint16_t u16Menu=0;

	/* Initialize SysTick : 1msec */
	SysTick_Config(SystemCoreClock/1000);

	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* initialize main board peripherals */
	MBD_Init();
	printf("main board initialized\n");

	while(1)
	{
		/* main menu controlled by pushbutton interrupt */
		if( uIRQFlag == MAIN_BTN_EXTI_LINE ) {

			/* clear button interrupt flag */
			uIRQFlag = 0;

			if( u16Menu == MENU_FMATH_DEMO1 ) {
				FixMathDemo();
			}

			if( ++u16Menu == MENU_END )
				u16Menu = 0;

		}

		/* usual household routine goes here */
		{
		}

	}
}


void FixMathDemo()
{
	volatile uint32_t fix_duration = 0;
	volatile uint32_t flt_duration = 0;

	volatile uint32_t args = (1 <<  6);
	volatile uint32_t iter = (1 <<  4);
	volatile uint32_t pass = (1 <<  6);

	volatile uint32_t i,j,k;

	volatile fix16_t fix_args[args];
	volatile fix16_t fix_result[args];
	volatile fix16_t fix_error = 0;

	volatile float flt_args[args];
	volatile float flt_result[args];

    printf("FixMath test start...\n");

	/* initialize random number generator */
	srand(time(NULL));

	for(k = 0; k < pass; k++) {
		
		for(i = 0; i < args; i++)
			fix_args[i] = (rand() ^ (rand() << 16));

		for(i = 0; i < args; i++)
			flt_args[i] = fix16_to_float(fix_args[i]);

		/* start systick counter */
		uSysTick = 1;

		for(i = 0; i < iter; i++) {
			for(j = 0; j < args; j++)
				fix_result[j] = fix16_atan(fix_args[j]);
		}

		/* get the systick counter value */
		fix_duration += uSysTick; uSysTick = 0;

		/* start systick counter */
		uSysTick = 1;

		for(i = 0; i < iter; i++) {
			for(j = 0; j < args; j++)
				flt_result[j] = atanf(flt_args[j]);
		}

		/* get the systick counter value */
		flt_duration += uSysTick; uSysTick = 0;

		for(i = 0; i < args; i++)
			fix_error += abs(fix16_from_float(flt_result[i]) - fix_result[i]);

	}

	printf("Floating Point ATAN: %d msec\n", flt_duration);
	printf("Fixed Point ATAN: %d msec\n", fix_duration);
	printf("Difference: %d msec\n", (flt_duration - fix_duration));
	printf("Error: %f %%\n", ((fix16_to_dbl(fix_error) * 100.0) / (args * pass)));

}

