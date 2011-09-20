/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
* File Name          : mass_mal.c
* Author             : MCD Application Team
* Version            : V3.3.0
* Date               : 21-March-2011
* Description        : Medium Access Layer interface
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "miniSTM32.h"
#include "miniSTM32_sdc.h"
#include "mass_mal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t Mass_Memory_Size[2];
uint32_t Mass_Block_Size[2];
uint32_t Mass_Block_Count[2];
__IO uint32_t Status = 0;

SD_CardInfo mSDCardInfo;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : MAL_Init
* Description    : Initializes the Media on the STM32
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Init(uint8_t lun)
{
  uint16_t status = MAL_OK;

  switch (lun)
  {
    case 0:
      Status = SDC_Init();
      break;
    default:
      return MAL_FAIL;
  }
  return status;
}
/*******************************************************************************
* Function Name  : MAL_Write
* Description    : Write sectors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint32_t *Writebuff, uint16_t Transfer_Length)
{

  switch (lun)
  {
    case 0:
      Status = SDC_WriteBlock((uint8_t*)Writebuff, Memory_Offset, Transfer_Length);
      if ( Status != SD_OK )
      {
        return MAL_FAIL;
      }      
	  //printf("MAL_Write:lun0:SDC_WriteBlock\n");
      break;
    default:
      return MAL_FAIL;
  }
  return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_Read
* Description    : Read sectors
* Input          : None
* Output         : None
* Return         : Buffer pointer
*******************************************************************************/
uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length)
{

  switch (lun)
  {
    case 0:
      Status = SDC_ReadBlock((uint8_t*)Readbuff, Memory_Offset, Transfer_Length);
      if ( Status != SD_OK )
      {
        return MAL_FAIL;
      }
	  //printf("MAL_Read:lun0:SDC_ReadBlock\n");
      break;
    default:
      return MAL_FAIL;
  }
  return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_GetStatus
* Description    : Get status
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_GetStatus (uint8_t lun)
{
  uint32_t DeviceSizeMul = 0, NumberOfBlocks = 0;
  SD_CSD SD_csd;

  if (lun == 0)
  {
    if (SDC_Init() == SD_OK)
    {
      SDC_GetCardInfo(&mSDCardInfo);
      SDC_SelectDeselect((uint32_t) (mSDCardInfo.RCA << 16));
      DeviceSizeMul = (mSDCardInfo.SD_csd.DeviceSizeMul + 2);

      if(mSDCardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)
      {
        Mass_Block_Count[0] = (mSDCardInfo.SD_csd.DeviceSize + 1) * 1024;
      }
      else
      {
        NumberOfBlocks  = ((1 << (mSDCardInfo.SD_csd.RdBlockLen)) / 512);
        Mass_Block_Count[0] = ((mSDCardInfo.SD_csd.DeviceSize + 1) * (1 << DeviceSizeMul) << (NumberOfBlocks/2));
      }
      Mass_Block_Size[0]  = 512;

      Status = SDC_SelectDeselect((uint32_t) (mSDCardInfo.RCA << 16)); 
      Status = SDC_EnableWideBusOperation(SDIO_BusWide_4b); 
      if ( Status != SD_OK )
      {
        return MAL_FAIL;
      }
       
	/* Brian
      Status = SDC_SetDeviceMode(SD_DMA_MODE);         
      if ( Status != SD_OK )
      {
        return MAL_FAIL;
      } 
	*/
     
      Mass_Memory_Size[0] = Mass_Block_Count[0] * Mass_Block_Size[0];
		MBD_LEDOn();

		//printf("MAL_GetStatus\n");
      return MAL_OK;

    }
  }
		MBD_LEDOn();
  return MAL_FAIL;
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
