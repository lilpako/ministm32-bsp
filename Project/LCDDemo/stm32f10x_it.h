/*******************************************************************************
 * @file    Project/LCDDemo/stm32f10x_it.h 
 * @author	Brian
 * @version	V0.2.0
 * @date    07-August-2011
 * @brief   This file contains the headers of the interrupt handlers.
 */

#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

#include "stm32f10x.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void EXTI15_10_IRQHandler(void);	/* pushbutton interrupt handler */

#endif /* __STM32F10x_IT_H */

/* End of File */
