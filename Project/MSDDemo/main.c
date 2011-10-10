/*******************************************************************************
 * File Name          : main.c
 * Author             : Brian
 * Date               : 01-Oct-2011
 * Description        : Mass Storage demo main file
 *
 * Original version of this project comes from the STM32 USB FS dev library
 * mass storage example (V3.3.0 21-March-2011). Minor modifications were made 
 * to work with miniSTM32 board.
 */

#include "stm32f10x.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"

/*******************************************************************************
 * Function Name  : main.
 * Description    : Main routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 */
int main(void)
{
  Set_System();
  Set_USBClock();
  Led_Config();
  USB_Interrupts_Config();
  USB_Init();
  while (bDeviceState != CONFIGURED);

  USB_Configured_LED();

  while (1)
  {}
}

#ifdef USE_FULL_ASSERT
/*******************************************************************************
 * Function Name  : assert_failed
 * Description    : Reports the name of the source file and the source line number
 *                  where the assert_param error has occurred.
 * Input          : - file: pointer to the source file name
 *                  - line: assert_param error line source number
 * Output         : None
 * Return         : None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/**** END OF FILE ****/
