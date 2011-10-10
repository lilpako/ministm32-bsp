/*******************************************************************************
 * File Name          : stm32f10x_it.h
 * Author             : Brian
 * Date               : 01-Oct-2011
 * Description        : This file contains the headers of the interrupt handlers.
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

void USB_HP_CAN1_TX_IRQHandler(void);
void USB_LP_CAN1_RX0_IRQHandler(void);

void SDIO_IRQHandler(void);

void MSecTimer(uint16_t uCount);
					 
#endif /* __STM32F10x_IT_H */

/**** END OF FILE ****/

