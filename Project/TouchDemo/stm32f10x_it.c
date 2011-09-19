/*******************************************************************************
 * @file    Project/TouchDemo/stm32f10x_it.c 
 * @author  Brian
 * @version V0.2.0
 * @date    07-August-2011
 * @brief   This file provides  exceptions handler and peripherals interrupt 
 *			service routine.
 ******************************************************************************
 */

#include "stm32f10x_it.h"
#include "miniSTM32.h"
#include "miniSTM32_tsc.h"

#define KEY_DEBOUNCE_DELAY		300				/* 300msec key debouncer */
#define TSC_DEBOUNCE_DELAY		300				/* 300msec key debouncer */

extern volatile uint16_t uTSC_Delay;			/* 1msec reference counter */
extern volatile uint16_t uLCD_Delay;			/* 1msec reference counter */
extern volatile TouchStatus TSC_Status;			/* touch sensor status */

volatile uint16_t uIRQFlag = 0;					/* IRQ number */
volatile uint16_t uKeyDebouncer = 0;			/* pushbutton debouncer */
volatile uint16_t uTSCDebouncer = 0;			/* touch screen debouncer */

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
	/* System 1msec ticks */
	if(uTSC_Delay)
		uTSC_Delay--;

	if(uLCD_Delay)
		uLCD_Delay--;

	/* Debounce timers */
	if(uKeyDebouncer)
		uKeyDebouncer--;

	if(uTSCDebouncer)
		uTSCDebouncer--;
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/******************************************************************************/

/**
 * @brief  This function handles EXTI 5 - 9 lines.
 * @param  None
 * @retval None
 */
void EXTI9_5_IRQHandler(void)
{

	/* touch screen controller interrupt */
	if(EXTI_GetITStatus(MAIN_TSC_INT_EXTI_LINE)) {
		/* wait for debounce period */
		if(uTSCDebouncer == 0) {

			/* set touch detected flag */
			if(TSC_Status == TOUCH_IDLE) TSC_Status = TOUCH_DETECTED;

			/* set IRQ flag for later use */
			uIRQFlag = MAIN_TSC_INT_EXTI_LINE;
			/* start new debounce count */
			uTSCDebouncer = TSC_DEBOUNCE_DELAY;

		}

		EXTI_ClearITPendingBit(MAIN_TSC_INT_EXTI_LINE);
	}
}


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
