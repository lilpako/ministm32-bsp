/*******************************************************************************
 * File Name          : memory.h
 * Author             : Brian
 * Date               : 01-Oct-2011
 * Description        : Mass Storage demo main file
 *
 * Original version of this project comes from the STM32 USB FS dev library
 * mass storage example (V3.3.0 21-March-2011). Minor modifications were made 
 * to work with miniSTM32 board.
 */

#ifndef __memory_H
#define __memory_H

#include "stm32f10x.h"
 
#define TXFR_IDLE     0
#define TXFR_ONGOING  1

void Write_Memory (uint8_t lun, uint32_t Memory_Offset, uint32_t Transfer_Length);
void Read_Memory (uint8_t lun, uint32_t Memory_Offset, uint32_t Transfer_Length);

#endif /* __memory_H */

/**** END OF FILE ****/
