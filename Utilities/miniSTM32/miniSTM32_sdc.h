/*******************************************************************************
 * @file	miniSTM32_sdc.h
 * @author	Brian
 * @version	V0.2.0
 * @date	17-August-2011
 * @brief	This file contains public definitions and functions prototypes for
 *			miniSTM32 onboard SD card system. Most of the code came from ST
 *			standard peripheral library V3.5.0 (stm32_eval_sdio_sd.h).
 */ 

#ifndef __MINISTM32_SD_H
#define __MINISTM32_SD_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

/**
 * @brief	SD error state
 */
typedef enum
{
  SD_CMD_CRC_FAIL			= (1), /* Command response received with CRC error */
  SD_DATA_CRC_FAIL			= (2), /* Data sent/received with CRC error */
  SD_CMD_RSP_TIMEOUT		= (3), /* Command response timeout */
  SD_DATA_TIMEOUT			= (4), /* Data time out */
  SD_TX_UNDERRUN			= (5), /* Transmit FIFO under-run */
  SD_RX_OVERRUN				= (6), /* Receive FIFO over-run */
  SD_START_BIT_ERR			= (7), /* Start bit not detected in wide bus mode */
  SD_CMD_OUT_OF_RANGE		= (8), /* CMD's argument was out of range.*/
  SD_ADDR_MISALIGNED		= (9), /* Misaligned address */
  SD_BLOCK_LEN_ERR			= (10), /* Transferred block length error */
  SD_ERASE_SEQ_ERR			= (11), /* error in the sequence of erase command */
  SD_BAD_ERASE_PARAM		= (12), /* An Invalid selection for erase groups */
  SD_WRITE_PROT_VIOLATION	= (13), /* Attempt to write to a protect block */
  SD_LOCK_UNLOCK_FAILED		= (14), /* error in unlock/lock command */
  SD_COM_CRC_FAILED			= (15), /* CRC check of the command failed */
  SD_ILLEGAL_CMD			= (16), /* Command is not legal for the card state */
  SD_CARD_ECC_FAILED		= (17), /* ECC was failed to correct the data */
  SD_CC_ERROR				= (18), /* Internal card controller error */
  SD_GENERAL_UNKNOWN_ERROR	= (19), /* General or Unknown error */
  SD_STREAM_READ_UNDERRUN	= (20), /* Error in stream read operation. */
  SD_STREAM_WRITE_OVERRUN	= (21), /* Error in stream program operation */
  SD_CID_CSD_OVERWRITE		= (22), /* CID/CSD overwrite error */
  SD_WP_ERASE_SKIP			= (23), /* only partial address space was erased */
  SD_CARD_ECC_DISABLED		= (24), /* Command has been executed without ECC */
  SD_ERASE_RESET			= (25), /* Out of erase sequence command */
  SD_AKE_SEQ_ERROR			= (26), /* Error in sequence of authentication. */
  SD_INVALID_VOLTRANGE		= (27),
  SD_ADDR_OUT_OF_RANGE		= (28),
  SD_SWITCH_ERROR			= (29),
  SD_SDIO_DISABLED			= (30),
  SD_SDIO_FUNCTION_BUSY		= (31),
  SD_SDIO_FUNCTION_FAILED	= (32),
  SD_SDIO_UNKNOWN_FUNCTION	= (33),
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


/** 
 * @brief  SD Card States 
 */   
typedef enum
{
  SD_CARD_READY				= ((uint32_t)0x00000001),
  SD_CARD_IDENTIFICATION	= ((uint32_t)0x00000002),
  SD_CARD_STANDBY			= ((uint32_t)0x00000003),
  SD_CARD_TRANSFER			= ((uint32_t)0x00000004),
  SD_CARD_SENDING			= ((uint32_t)0x00000005),
  SD_CARD_RECEIVING			= ((uint32_t)0x00000006),
  SD_CARD_PROGRAMMING		= ((uint32_t)0x00000007),
  SD_CARD_DISCONNECTED		= ((uint32_t)0x00000008),
  SD_CARD_ERROR				= ((uint32_t)0x000000FF)
} SDCardState;


SD_Error mSTM_SDInit(void);
SD_Error mSTM_SDReadBlock(uint8_t *Buff, uint32_t Addr, uint16_t BlockSize);
SD_Error mSTM_SDReadMultiBlocks(uint8_t *Buff, uint32_t Addr, uint16_t BlockSize, uint32_t NumberOfBlocks);
SD_Error mSTM_SDWriteBlock(uint8_t *Buff, uint32_t Addr, uint16_t BlockSize);
SD_Error mSTM_SDWriteMultiBlocks(uint8_t *Buff, uint32_t Addr, uint16_t BlockSize, uint32_t NumberOfBlocks);
SD_Error mSTM_SDErase(uint32_t StartAddr, uint32_t EndAddr);
SD_Error mSTM_SDWaitReadOperation(void);
SD_Error mSTM_SDWaitWriteOperation(void);
SDTransferState mSTM_SDGetStatus(void);
SD_Error mSTM_SDProcessIRQSrc(void);
SD_Error mSTM_SDSetBlockSize(uint32_t BlockSize);


#ifdef __cplusplus
}
#endif

#endif /*  __MINISTM32_SD_H */

/* End of File */
