/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
* File Name          : usb_desc.h
* Author             : MCD Application Team
* Version            : V3.3.0
* Date               : 21-March-2011
* Description        : Descriptor Header for Device Firmware Upgrade (DFU)
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_H
#define __USB_DESC_H

#include "stm32f10x.h"

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define DFU_SIZ_DEVICE_DESC            18
#define DFU_SIZ_CONFIG_DESC				27

#define DFU_SIZ_STRING_LANGID           4
#define DFU_SIZ_STRING_VENDOR           38
#define DFU_SIZ_STRING_PRODUCT          20
#define DFU_SIZ_STRING_SERIAL           26
#define DFU_SIZ_STRING_INTERFACE0       96    /* Flash Bank 0 */


extern  uint8_t DFU_DeviceDescriptor[DFU_SIZ_DEVICE_DESC];
extern  uint8_t DFU_ConfigDescriptor[DFU_SIZ_CONFIG_DESC];
extern  uint8_t DFU_StringLangId     [DFU_SIZ_STRING_LANGID];
extern  uint8_t DFU_StringVendor     [DFU_SIZ_STRING_VENDOR];
extern  uint8_t DFU_StringProduct    [DFU_SIZ_STRING_PRODUCT];
extern  uint8_t DFU_StringSerial     [DFU_SIZ_STRING_SERIAL];
extern  uint8_t DFU_StringInterface0 [DFU_SIZ_STRING_INTERFACE0];

#define bMaxPacketSize0             0x40     /* bMaxPacketSize0 = 64 bytes   */

#define wTransferSize               0x0400   /* wTransferSize   = 1024 bytes */
/* bMaxPacketSize0 <= wTransferSize <= 32kbytes */
#define wTransferSizeB0             0x00
#define wTransferSizeB1             0x04

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* External variables --------------------------------------------------------*/

#endif /* __USB_DESC_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/




