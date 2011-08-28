/*
 ******************************************************************************
 * miniSTM32_flash.h
 * Brian
 * 14-July-2011
 * This file contains definitions for miniSTM32 serial flash access
 ******************************************************************************
 */ 
  
#ifndef __MINISTM32_FLASH_H
#define __MINISTM32_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif 

void SFL_Init(void);
uint32_t SFL_ReadID(void);
void SFL_Erase(BlockSize_TypeDef Size, uint32_t StartAddr);
void SFL_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByte);
void SFL_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByte);

#ifdef __cplusplus
}
#endif
  
#endif /* __MINISTM32_FLASH_H */
 
/*****END OF FILE****/
