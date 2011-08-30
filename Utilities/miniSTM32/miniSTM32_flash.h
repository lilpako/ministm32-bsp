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

#define FLASH_SST25VF106				1

#ifdef FLASH_SST25VF106
#define SFLASH_JEDEC_ID					(0xBF2541)
#define SFLASH_CAPACITY					(2*1024*1024)
#define SFLASH_ERASE_BLOCK_SIZE			(4*1024)
#endif // FLASH_SST25VF106

/* FLASH typedefs */
typedef enum{
	EBSIZE_4KB,
	EBSIZE_32KB,
	EBSIZE_64KB,
	EBSIZE_CHIP
} BlockSize_TypeDef;

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
