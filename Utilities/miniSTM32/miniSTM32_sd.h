/*******************************************************************************
 * @file	miniSTM32_sd.h
 * @author	Brian
 * @version	V0.2.0
 * @date	07-August-2011
 * @brief	This file contains public definitions and functions prototypes for
 *			miniSTM32 onboard SD card system. Most of the code came from ST
 *			standard peripheral library V3.5.0 (stm32_eval_sdio_sd.h).
 */ 

#ifndef __MINISTM32_SD_H
#define __MINISTM32_SD_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "miniSTM32.h"

/* SDIO IRQ priority level can be overridden */
#ifndef SDIO_IRQPR_PRE
	#define SDIO_IRQPR_PRE		0
#endif
#ifndef SDIO_IRQPR_SUB
	#define SDIO_IRQPR_SUB		0
#endif

/* FAT time can be overridden */
#ifndef FATTIME_YEAR
	#define FATTIME_YEAR		(2011)
	#define FATTIME_MONTH		(1)
	#define FATTIME_DATE		(1)
#endif

  
/* Uncomment the following line to select the SDIO Data transfer mode */  
/*
#define SD_POLLING_MODE                            ((uint32_t)0x00000002)
*/
#define SD_DMA_MODE                                ((uint32_t)0x00000000)

/* FatFs support */
#define FAT_SECTORSIZE			512

/**
 * @brief	SD error state
 */
typedef enum
{
  SD_CMD_CRC_FAIL                    = (1), /* Command response received (but CRC check failed) */
  SD_DATA_CRC_FAIL                   = (2), /* Data bock sent/received (CRC check Failed) */
  SD_CMD_RSP_TIMEOUT                 = (3), /* Command response timeout */
  SD_DATA_TIMEOUT                    = (4), /* Data time out */
  SD_TX_UNDERRUN                     = (5), /* Transmit FIFO under-run */
  SD_RX_OVERRUN                      = (6), /* Receive FIFO over-run */
  SD_START_BIT_ERR                   = (7), /* Start bit not detected on all data signals in widE bus mode */
  SD_CMD_OUT_OF_RANGE                = (8), /* CMD's argument was out of range.*/
  SD_ADDR_MISALIGNED                 = (9), /* Misaligned address */
  SD_BLOCK_LEN_ERR                   = (10), /* Transferred block length is not allowed for the card or the number of transferred bytes does not match the block length */
  SD_ERASE_SEQ_ERR                   = (11), /* An error in the sequence of erase command occurs.*/
  SD_BAD_ERASE_PARAM                 = (12), /* An Invalid selection for erase groups */
  SD_WRITE_PROT_VIOLATION            = (13), /* Attempt to program a write protect block */
  SD_LOCK_UNLOCK_FAILED              = (14), /* Sequence or password error has been detected in unlock command or if there was an attempt to access a locked card */
  SD_COM_CRC_FAILED                  = (15), /* CRC check of the previous command failed */
  SD_ILLEGAL_CMD                     = (16), /* Command is not legal for the card state */
  SD_CARD_ECC_FAILED                 = (17), /* Card internal ECC was applied but failed to correct the data */
  SD_CC_ERROR                        = (18), /* Internal card controller error */
  SD_GENERAL_UNKNOWN_ERROR           = (19), /* General or Unknown error */
  SD_STREAM_READ_UNDERRUN            = (20), /* The card could not sustain data transfer in stream read operation. */
  SD_STREAM_WRITE_OVERRUN            = (21), /* The card could not sustain data programming in stream mode */
  SD_CID_CSD_OVERWRITE               = (22), /* CID/CSD overwrite error */
  SD_WP_ERASE_SKIP                   = (23), /* only partial address space was erased */
  SD_CARD_ECC_DISABLED               = (24), /*!< Command has been executed without using internal ECC */
  SD_ERASE_RESET                     = (25), /* Erase sequence was cleared before executing because an out of erase sequence command was received */
  SD_AKE_SEQ_ERROR                   = (26), /* Error in sequence of authentication. */
  SD_INVALID_VOLTRANGE               = (27),
  SD_ADDR_OUT_OF_RANGE               = (28),
  SD_SWITCH_ERROR                    = (29),
  SD_SDIO_DISABLED                   = (30),
  SD_SDIO_FUNCTION_BUSY              = (31),
  SD_SDIO_FUNCTION_FAILED            = (32),
  SD_SDIO_UNKNOWN_FUNCTION           = (33),
  SD_INTERNAL_ERROR, 
  SD_NOT_CONFIGURED,
  SD_REQUEST_PENDING, 
  SD_REQUEST_NOT_APPLICABLE, 
  SD_INVALID_PARAMETER,  
  SD_UNSUPPORTED_FEATURE,  
  SD_UNSUPPORTED_HW,  
  SD_ERROR,  
  SD_OK = 0 
} SD_Error;

/** 
 * @brief  SDIO Transfer state  
 */   
typedef enum
{
  SD_TRANSFER_OK  = 0,
  SD_TRANSFER_BUSY = 1,
  SD_TRANSFER_ERROR
} SDTransferState;



SD_Error miniSTM32_SDInit(void);

SD_Error miniSTM32_SDReadBlock(uint8_t *readbuff, uint32_t ReadAddr, uint16_t BlockSize);
SD_Error miniSTM32_SDReadMultiBlocks(uint8_t *readbuff, uint32_t ReadAddr, uint16_t BlockSize, uint32_t NumberOfBlocks);
SD_Error miniSTM32_SDWriteBlock(uint8_t *writebuff, uint32_t WriteAddr, uint16_t BlockSize);
SD_Error miniSTM32_SDWriteMultiBlocks(uint8_t *writebuff, uint32_t WriteAddr, uint16_t BlockSize, uint32_t NumberOfBlocks);
SD_Error miniSTM32_SDErase(uint32_t startaddr, uint32_t endaddr);
SD_Error miniSTM32_SDWaitReadOperation(void);
SD_Error miniSTM32_SDWaitWriteOperation(void);
SDTransferState miniSTM32_SDGetStatus(void);


#ifdef __cplusplus
}
#endif

#endif /*  __MINISTM32_SD_H */

/* End of File */
