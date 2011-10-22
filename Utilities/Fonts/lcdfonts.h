/*******************************************************************************
 * @file    lcdfonts.h
 * @author  Brian
 * @version V0.1.0
 * @date    21-Oct-2011
 * @brief   Header for fonts
 */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCDFONTS_H
#define __LCDFONTS_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

typedef struct _lcdfont
{    
  uint8_t WidthBytes;		/* number of bytes for a row */
  uint8_t Height;
  const uint8_t *table;
} LCDFONT;

extern LCDFONT MSSansSerif_11;
extern LCDFONT MSSansSerif_13;
extern LCDFONT MSSansSerif_16;
extern LCDFONT MSSansSerif_19;
extern LCDFONT MSSansSerif_24;
extern LCDFONT MSSansSerif_32;

extern LCDFONT MSSerif_11;
extern LCDFONT MSSerif_13;
extern LCDFONT MSSerif_16;
extern LCDFONT MSSerif_19;
extern LCDFONT MSSerif_24;
extern LCDFONT MSSerif_32;

extern LCDFONT Terminal_12;
extern LCDFONT Terminal_16;
extern LCDFONT Terminal_20;
extern LCDFONT Terminal_23;
extern LCDFONT Terminal_28;

#ifdef __cplusplus
}
#endif
  
#endif /* __LCDFONTS_H */
 

/**** END OF FILE ****/
