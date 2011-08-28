/*******************************************************************************
 * @file    Project/SIODemo/stm32f10x_it.c 
 * @author  Brian
 * @version V0.2.0
 * @date    07-August-2011
 * @brief   This file provides  exceptions handler and peripherals interrupt 
 *			service routine.
 ******************************************************************************
 */

#include "stm32f10x_it.h"
#include "miniSTM32_sio.h"

#define DEBOUNCE_DELAY		300			/* 300msec key debouncer */

volatile uint16_t IRQFlag = 0;			/* IRQ number : set by IRQ handler */
volatile uint16_t LEDOffTimer = 0;		/* LED auto turn-off timer */
volatile uint16_t u16Debouncer = 0;		/* key debouncer timer */


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

	/* Debounce timer */
	if(u16Debouncer)
		u16Debouncer--;

	/* LED Flasher timer */
	if(LEDOffTimer)
		LEDOffTimer--;
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/******************************************************************************/


/**
 * @brief	This function handles push button 1 interrupt.
 * @param	None
 * @retval	None
 */
void EXTI2_IRQHandler(void)
{
	/* only accept key input after debuncing dead zone */
	if(u16Debouncer == 0){
		/* set IRQ flag for later use */
		IRQFlag = 2;
		/* start new debounce count */
		u16Debouncer = DEBOUNCE_DELAY;
	}
	
	/* clear the IT bit */
	EXTI_ClearITPendingBit(SIO_BTN1_EXTI_LINE);
}

/**
 * @brief	This function handles push button 2 interrupt.
 * @param	None
 * @retval	None
 */
void EXTI3_IRQHandler(void)
{
	/* only accept key input after debuncing dead zone */
	if(u16Debouncer == 0){
		/* set IRQ flag for later use */
		IRQFlag = 3;
		/* start new debounce count */
		u16Debouncer = DEBOUNCE_DELAY;
	}

	/* clear the IT bit */
	EXTI_ClearITPendingBit(SIO_BTN2_EXTI_LINE);
}

/* End of File */
