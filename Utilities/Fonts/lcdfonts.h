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

extern LCDFONT DroidSans_10;
extern LCDFONT DroidSans_12;
extern LCDFONT DroidSans_14;
extern LCDFONT DroidSans_16;
extern LCDFONT DroidSans_18;
extern LCDFONT DroidSans_20;
extern LCDFONT DroidSans_Bold_10;
extern LCDFONT DroidSans_Bold_12;
extern LCDFONT DroidSans_Bold_14;
extern LCDFONT DroidSans_Bold_16;
extern LCDFONT DroidSans_Bold_18;
extern LCDFONT DroidSans_Bold_20;
extern LCDFONT DroidSerif_10;
extern LCDFONT DroidSerif_12;
extern LCDFONT DroidSerif_14;
extern LCDFONT DroidSerif_16;
extern LCDFONT DroidSerif_18;
extern LCDFONT DroidSerif_20;
extern LCDFONT DroidSerif_Bold_10;
extern LCDFONT DroidSerif_Bold_12;
extern LCDFONT DroidSerif_Bold_14;
extern LCDFONT DroidSerif_Bold_16;
extern LCDFONT DroidSerif_Bold_18;
extern LCDFONT DroidSerif_Bold_20;
extern LCDFONT DroidSerif_Italic_10;
extern LCDFONT DroidSerif_Italic_12;
extern LCDFONT DroidSerif_Italic_14;
extern LCDFONT DroidSerif_Italic_16;
extern LCDFONT DroidSerif_Italic_18;
extern LCDFONT DroidSerif_Italic_20;
extern LCDFONT Federant_10;
extern LCDFONT Federant_12;
extern LCDFONT Federant_14;
extern LCDFONT Federant_16;
extern LCDFONT Federant_18;
extern LCDFONT Federant_20;
extern LCDFONT LiberationSans_10;
extern LCDFONT LiberationSans_12;
extern LCDFONT LiberationSans_14;
extern LCDFONT LiberationSans_16;
extern LCDFONT LiberationSans_18;
extern LCDFONT LiberationSans_20;
extern LCDFONT LiberationSerif_10;
extern LCDFONT LiberationSerif_12;
extern LCDFONT LiberationSerif_14;
extern LCDFONT LiberationSerif_16;
extern LCDFONT LiberationSerif_18;
extern LCDFONT LiberationSerif_20;
extern LCDFONT LiberationSerif_Italic_10;
extern LCDFONT LiberationSerif_Italic_12;
extern LCDFONT LiberationSerif_Italic_14;
extern LCDFONT LiberationSerif_Italic_16;
extern LCDFONT LiberationSerif_Italic_18;
extern LCDFONT LiberationSerif_Italic_20;
extern LCDFONT Ubuntu_10;
extern LCDFONT Ubuntu_12;
extern LCDFONT Ubuntu_14;
extern LCDFONT Ubuntu_16;
extern LCDFONT Ubuntu_18;
extern LCDFONT Ubuntu_20;
extern LCDFONT Ubuntu_Bold_10;
extern LCDFONT Ubuntu_Bold_12;
extern LCDFONT Ubuntu_Bold_14;
extern LCDFONT Ubuntu_Bold_16;
extern LCDFONT Ubuntu_Bold_18;
extern LCDFONT Ubuntu_Bold_20;
extern LCDFONT Ubuntu_Italic_10;
extern LCDFONT Ubuntu_Italic_12;
extern LCDFONT Ubuntu_Italic_14;
extern LCDFONT Ubuntu_Italic_16;
extern LCDFONT Ubuntu_Italic_18;
extern LCDFONT Ubuntu_Italic_20;

#ifdef __cplusplus
}
#endif
  
#endif /* __LCDFONTS_H */
 

/**** END OF FILE ****/
