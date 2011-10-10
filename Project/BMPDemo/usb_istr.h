/*******************************************************************************
 * File Name          : usb_istr.h
 * Author             : Brian
 * Date               : 01-Oct-2011
 * Description        : Mass Storage demo main file
 *
 * Original version of this project comes from the STM32 USB FS dev library
 * mass storage example (V3.3.0 21-March-2011). Minor modifications were made 
 * to work with miniSTM32 board.
 */

#ifndef __USB_ISTR_H
#define __USB_ISTR_H

#include "usb_conf.h"

void USB_Istr(void);

void EP1_IN_Callback(void);
void EP2_IN_Callback(void);
void EP3_IN_Callback(void);
void EP4_IN_Callback(void);
void EP5_IN_Callback(void);
void EP6_IN_Callback(void);
void EP7_IN_Callback(void);

void EP1_OUT_Callback(void);
void EP2_OUT_Callback(void);
void EP3_OUT_Callback(void);
void EP4_OUT_Callback(void);
void EP5_OUT_Callback(void);
void EP6_OUT_Callback(void);
void EP7_OUT_Callback(void);

#ifdef CTR_CALLBACK
void CTR_Callback(void);
#endif

#ifdef DOVR_CALLBACK
void DOVR_Callback(void);
#endif

#ifdef ERR_CALLBACK
void ERR_Callback(void);
#endif

#ifdef WKUP_CALLBACK
void WKUP_Callback(void);
#endif

#ifdef SUSP_CALLBACK
void SUSP_Callback(void);
#endif

#ifdef RESET_CALLBACK
void RESET_Callback(void);
#endif

#ifdef SOF_CALLBACK
void SOF_Callback(void);
#endif

#ifdef ESOF_CALLBACK
void ESOF_Callback(void);
#endif

#endif /*__USB_ISTR_H*/

/**** END OF FILE ****/
