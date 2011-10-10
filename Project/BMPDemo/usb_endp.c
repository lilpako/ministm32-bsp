/*******************************************************************************
 * File Name          : usb_endp.c
 * Author             : Brian
 * Date               : 01-Oct-2011
 * Description        : Mass Storage demo main file
 *
 * Original version of this project comes from the STM32 USB FS dev library
 * mass storage example (V3.3.0 21-March-2011). Minor modifications were made 
 * to work with miniSTM32 board.
 */

#include "usb_lib.h"
#include "usb_bot.h"
#include "usb_istr.h"

/*******************************************************************************
 * Function Name  : EP1_IN_Callback
 * Description    : EP1 IN Callback Routine
 * Input          : None.
 * Output         : None.
 * Return         : None.
 */
void EP1_IN_Callback(void)
{
	Mass_Storage_In();
}

/*******************************************************************************
 * Function Name  : EP2_OUT_Callback.
 * Description    : EP2 OUT Callback Routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 */
void EP2_OUT_Callback(void)
{
	Mass_Storage_Out();
}

/**** END OF FILE ****/
