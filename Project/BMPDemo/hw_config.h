/*******************************************************************************
 * File Name          : hw_config.h
 * Author             : Brian
 * Date               : 01-Oct-2011
 *
 * Original version of this project comes from the STM32 USB FS dev library
 * mass storage example (V3.3.0 21-March-2011). Minor modifications were made 
 * to work with miniSTM32 board.
 */

#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

#include "stm32f10x.h"

#define BULK_MAX_PACKET_SIZE  0x00000040

void Set_System(void);
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);
void Get_SerialNum(void);
void MAL_Config(void);
void USB_Disconnect_Config(void);

#endif  /*__HW_CONFIG_H*/

/*** END OF FILE ****/
