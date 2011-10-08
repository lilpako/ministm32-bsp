/*******************************************************************************
 *
 */ 

#ifndef __MINISTM32_LCD_H
#define __MINISTM32_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"
#include "fonts.h"

/* LCD type definition (default) */
#if (!defined(LCD_HSD043I9W) && !defined(LCD_AT043TN13) && !defined(LCD_AT070TN83))
//	#define LCD_HSD043I9W			/* HannStar 4.3 inch */
	#define LCD_AT043TN13			/* Innolux 4.3 inch */
//	#define LCD_AT070TN83			/* Innolux 7.0 inch */
#endif

/* LCD size definition */
#if (defined(LCD_HSD043I9W) || defined(LCD_AT043TN13))
	#define LCD_WIDTH				(480)
	#define LCD_HEIGHT				(272)
#elif defined(LCD_AT070TN83)
	#define LCD_WIDTH				(800)
	#define LCD_HEIGHT				(480)
#endif


/* LCD color (RGB565) */
#define LCD_COLOR_WHITE				0xFFFF
#define LCD_COLOR_BLACK				0x0000
#define LCD_COLOR_GREY				0xF7DE
#define LCD_COLOR_RED				0xF800
#define LCD_COLOR_GREEN				0x07E0
#define LCD_COLOR_BLUE				0x001F
#define LCD_COLOR_MAGENTA			0xF81F
#define LCD_COLOR_CYAN				0x7FFF
#define LCD_COLOR_YELLOW			0xFFE0
#define LCD_COLOR(R, G, B)			((((R)& 0x00F8) << 8) | \
									(((G) & 0x00FC) << 3) | \
									(((B) & 0x00F8) >> 3))  

typedef uint16_t LCDCOLOR;

void LCD_Init(void);
void LCD_BacklightOn(void);
void LCD_BacklightOff(void);
void LCD_Clear(LCDCOLOR x);

void LCD_DisplayOn(void);
void LCD_DisplayOff(void);

void LCD_SetFGColor(LCDCOLOR col);
void LCD_SetBGColor(LCDCOLOR col);
void LCD_SetColors(LCDCOLOR fgcol, LCDCOLOR bgcol);
void LCD_GetColors(LCDCOLOR *pfgcol, LCDCOLOR *pbgcol);
void LCD_SetPenWidth(uint16_t w);
uint16_t LCD_GetPenWidth(void);

void LCD_DrawPixel(int16_t x, int16_t y);
void LCD_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void LCD_DrawRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void LCD_DrawCircle(int16_t x, int16_t y, int16_t r);
void LCD_DrawEllipse(int16_t x, int16_t y, int16_t rx, int16_t ry);
void LCD_DrawFillRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void LCD_DrawFillCircle(int16_t x, int16_t y, int16_t r);
void LCD_DrawFillEllipse(int16_t x, int16_t y, int16_t rx, int16_t ry);

/* functions from STM32 peripheral library */
void LCD_SetFont(sFONT *pFont);
sFONT* LCD_GetFont(void);
void LCD_DrawChar(int16_t x, int16_t y, const uint16_t *ch);
void LCD_DisplayChar(int16_t x, int16_t y, uint8_t asc);
void LCD_DisplayStringLine(int16_t x, int16_t y, uint8_t *pstr);
void LCD_WriteBMP(int16_t x, int16_t y, uint32_t BmpAddress);

#if defined(LCD_TEST)
uint16_t LCD_DrawTestPattern(unsigned int index);
/* Bresenham algorithm for speed comparision */
void LCD_DrawLineB(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
#endif /* LCD_TEST */



/* functions and definitions for STM32 gui library compatibility */
#if defined(STM32_GL_COMPATIBILITY)
#define LCD_DIR_HORIZONTAL			0x0000
#define LCD_DIR_VERTICAL			0x0001
#define GL_SetTextColor				LCD_SetFGColor
#define GL_SetBackColor				LCD_SetBGColor
#define GL_Clear					LCD_Clear
#define GL_LCD_Init					LCD_Init
#endif /* STM32_GL_COMPATIBILITY */


#ifdef __cplusplus
}
#endif

#endif /* __MINISTM32_LCD_H */
  
/****END OF FILE****/
