/*******************************************************************************
 * File Name          : mass_mal.c
 * Author             : Brian
 * Date               : 01-Oct-2011
 * Description        : Mass Storage demo main file
 *
 * Original version of this project comes from the STM32 USB FS dev library
 * mass storage example (V3.3.0 21-March-2011). Minor modifications were made 
 * to work with miniSTM32 board.
 */

#include "platform_config.h"
#include "miniSTM32_sdc.h"
#include "mass_mal.h"

uint32_t Mass_Memory_Size[2];
uint32_t Mass_Block_Size[2];
uint32_t Mass_Block_Count[2];
__IO uint32_t Status = 0;

SD_CardInfo mSDCardInfo;

/*******************************************************************************
 * Function Name  : MAL_Init
 * Description    : Initializes the Media on the STM32
 * Input          : None
 * Output         : None
 * Return         : None
 */
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
 */
uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint32_t *Writebuff, uint16_t Transfer_Length)
{
	switch (lun)
	{
		case 0:
			Status = SDC_WriteBlock((uint8_t*)Writebuff, Memory_Offset, 
				Transfer_Length);
			Status = SDC_WaitWriteOperation();
			while(SDC_GetStatus() != SD_TRANSFER_OK);

			if ( Status != SD_OK ) return MAL_FAIL;
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
 */
uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length)
{
	switch (lun)
	{
		case 0:
			Status = SDC_ReadBlock((uint8_t*)Readbuff, Memory_Offset, 
				Transfer_Length);
			Status = SDC_WaitReadOperation();
			while(SDC_GetStatus() != SD_TRANSFER_OK );

			if ( Status != SD_OK ) return MAL_FAIL;
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
 */
uint16_t MAL_GetStatus (uint8_t lun)
{
	uint32_t DeviceSizeMul = 0, NumberOfBlocks = 0;
	SD_CSD SD_csd;

	if (lun == 0)
	{
		SDC_GetCardInfo(&mSDCardInfo);
		DeviceSizeMul = (mSDCardInfo.SD_csd.DeviceSizeMul + 2);

		if(mSDCardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)
		{
			Mass_Block_Count[0] = (mSDCardInfo.SD_csd.DeviceSize + 1) * 1024;
		}
		else
		{
			NumberOfBlocks  = ((1 << (mSDCardInfo.SD_csd.RdBlockLen)) / 512);
			Mass_Block_Count[0] = ((mSDCardInfo.SD_csd.DeviceSize + 1) * 
				(1 << DeviceSizeMul) << (NumberOfBlocks/2));
		}
		Mass_Block_Size[0]  = 512;

		Mass_Memory_Size[0] = Mass_Block_Count[0] * Mass_Block_Size[0];
		MBD_LEDOn();

		return MAL_OK;

	}

	return MAL_FAIL;
}

/**** END OF FILE ****/
