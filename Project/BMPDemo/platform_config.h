/*******************************************************************************
 * File Name          : platform_config.h
 * Author             : Brian
 * Date               : 01-Oct-2011
 * Description        : Mass Storage demo main file
 *
 * Original version of this project comes from the STM32 USB FS dev library
 * mass storage example (V3.3.0 21-March-2011). Minor modifications were made 
 * to work with miniSTM32 board.
 */

#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

#include "stm32f10x.h"

#define USB_DISCONNECT					GPIOC  
#define USB_DISCONNECT_PIN				GPIO_Pin_13
#define RCC_APB2Periph_GPIO_DISCONNECT	RCC_APB2Periph_GPIOC

#endif /* __PLATFORM_CONFIG_H */

/**** END OF FILE ****/
