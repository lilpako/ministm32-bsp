/*******************************************************************************
 * @file    Project/LCDDemo/stm32f10x_it.c 
 * @author  Brian
 * @version V0.2.0
 * @date    07-August-2011
 * @brief   This file provides  exceptions handler and peripherals interrupt 
 *			service routine.
 ******************************************************************************
 */

#include "stm32f10x_it.h"
#include "miniSTM32.h"

#define KEY_DEBOUNCE_DELAY		300				/* 300msec key debouncer */

extern volatile uint16_t uLCD_Delay;			/* 1msec reference counter */

volatile uint16_t uIRQFlag = 0;					/* IRQ number */
volatile uint16_t uMSecDelay = 0;				/* general purpose timer */
volatile uint16_t uKeyDebouncer = 0;			/* key debouncer timer */

void MSecTimer(uint16_t uCount)
{
	uMSecDelay = uCount;
	while(uMSecDelay);
}

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles PendSV_Handler exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
	/* System 1msec tick */
	if(uMSecDelay)
		uMSecDelay--;

	if(uLCD_Delay)
		uLCD_Delay--;

	/* Debounce timer */
	if(uKeyDebouncer)
		uKeyDebouncer--;
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/******************************************************************************/

/**
 * @brief  This function handles EXTI 10 - 15 lines.
 * @param  None
 * @retval None
 */
void EXTI15_10_IRQHandler(void)
{
	/* main board push button is depressed */
	if(EXTI_GetITStatus(MAIN_BTN_EXTI_LINE)) {

		/* wait for debounce period */
		if(uKeyDebouncer == 0){
			/* set IRQ flag for later use */
			uIRQFlag = MAIN_BTN_EXTI_LINE;
			/* start new debounce count */
			uKeyDebouncer = KEY_DEBOUNCE_DELAY;
		}
	
		/* clear the IT bit */
		EXTI_ClearITPendingBit(MAIN_BTN_EXTI_LINE);
	}
}


/* End of File */
