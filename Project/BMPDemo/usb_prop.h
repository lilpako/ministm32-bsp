/*******************************************************************************
 * File Name          : usb_prop.h
 * Author             : Brian
 * Date               : 01-Oct-2011
 * Description        : Mass Storage demo main file
 *
 * Original version of this project comes from the STM32 USB FS dev library
 * mass storage example (V3.3.0 21-March-2011). Minor modifications were made 
 * to work with miniSTM32 board.
 */

#ifndef __usb_prop_H
#define __usb_prop_H

#define Mass_Storage_GetConfiguration          NOP_Process
/* #define Mass_Storage_SetConfiguration          NOP_Process*/
#define Mass_Storage_GetInterface              NOP_Process
#define Mass_Storage_SetInterface              NOP_Process
#define Mass_Storage_GetStatus                 NOP_Process
/* #define Mass_Storage_ClearFeature              NOP_Process*/
#define Mass_Storage_SetEndPointFeature        NOP_Process
#define Mass_Storage_SetDeviceFeature          NOP_Process
/*#define Mass_Storage_SetDeviceAddress          NOP_Process*/

/* MASS Storage Requests*/
#define GET_MAX_LUN                0xFE
#define MASS_STORAGE_RESET         0xFF
#define LUN_DATA_LENGTH            1

void MASS_init(void);
void MASS_Reset(void);
void Mass_Storage_SetConfiguration(void);
void Mass_Storage_ClearFeature(void);
void Mass_Storage_SetDeviceAddress (void);
void MASS_Status_In (void);
void MASS_Status_Out (void);
RESULT MASS_Data_Setup(uint8_t);
RESULT MASS_NoData_Setup(uint8_t);
RESULT MASS_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *MASS_GetDeviceDescriptor(uint16_t );
uint8_t *MASS_GetConfigDescriptor(uint16_t);
uint8_t *MASS_GetStringDescriptor(uint16_t);
uint8_t *Get_Max_Lun(uint16_t Length);

#endif /* __usb_prop_H */

/**** END OF FILE ****/
