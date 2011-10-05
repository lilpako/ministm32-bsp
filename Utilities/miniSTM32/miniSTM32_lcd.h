/*******************************************************************************
 *
 */ 

#ifndef __MINISTM32_LCD_H
#define __MINISTM32_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"

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
void LCD_DrawEllipseRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void LCD_DrawFillRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void LCD_DrawFillCircle(int16_t x, int16_t y, int16_t r);
void LCD_DrawFillEllipseRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2);

#if defined(LCD_TEST)
uint16_t LCD_DrawTestPattern(unsigned int index);
/* Bresenham algorithm for speed comparision */
void LCD_DrawLineB(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
#endif /* LCD_TEST */

/* functions and definitions for stm32 gui lib compatibility */
#define LCD_DIR_HORIZONTAL			0x0000
#define LCD_DIR_VERTICAL			0x0001
#define GL_SetTextColor				LCD_SetFGColor
#define GL_SetBackColor				LCD_SetBGColor
#define GL_Clear					LCD_Clear
#define GL_LCD_Init					LCD_Init


#if 0

// st graphic library functions

extern __IO uint16_t          GL_TextColor;
extern __IO uint16_t          GL_BackColor;

void GL_SetTextColor(__IO uint16_t TextColor);
void GL_SetBackColor(__IO uint16_t BackColor);
void GL_Clear(uint16_t Color);
void GL_LCD_Init(void);



void GL_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction);
void GL_LCD_DrawCharTransparent(uint16_t Xpos, uint16_t Ypos, const uint16_t *c); /* 16bit char */
void GL_LCD_DisplayChar(uint16_t Line, uint16_t Column, uint8_t Ascii, GL_bool Trasparent_Flag);
void GL_DisplayAdjStringLine(uint16_t Line, uint16_t Column, uint8_t *ptr, GL_bool Transparent_Flag);
void GL_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Height, uint16_t Width);
void GL_LCD_DrawRect(uint8_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width);
void GL_LCD_DrawCircle(uint8_t Xpos, uint16_t Ypos, uint16_t Radius);
void GL_DrawBMP(uint8_t* ptrBitmap);
void GL_SetFont(uint8_t uFont);
void GL_BackLightSwitch(uint8_t u8_State);
void GL_BUSConfig(GL_BusType busType);
void GL_LCD_SPIConfig(void);
void GL_LCD_FSMCConfig(void);
void GL_LCD_WindowModeDisable(void);
void LCD_PutPixel(uint16_t Xpos, uint16_t Ypos, uint16_t Color, uint8_t PixelSpec);
void LCD_FillArea(uint16_t Xpos_Init, uint16_t Ypos_Init, uint16_t Height, uint16_t Width, uint16_t color);
uint16_t LCD_GetPixel(uint16_t Xpos, uint16_t Ypos);
void GL_LCD_DrawChar(uint8_t Xpos, uint16_t Ypos, const uint16_t *c);
void GL_LCD_CtrlLinesWrite(GPIO_TypeDef* GPIOx, uint16_t CtrlPins, GL_SignalActionType BitVal);
uint16_t GL_LCD_ReadRAM(void);
void LCD_WriteRAMWord(uint16_t RGB_Code);
void LCD_Change_Direction(LCD_Direction_TypeDef Direction);
void LCD_WriteChar(uint16_t Xpos, uint16_t Ypos, const uint16_t *c);
void LCD_PrintChar(uint16_t Line, uint16_t Column, uint8_t Ascii);
void LCD_PrintStringLine(uint16_t Line, uint16_t Column, uint8_t *ptr);
void LCD_DrawMonoBMP(const uint8_t *Pict, uint16_t Xpos_Init, uint16_t Ypos_Init, uint16_t Height, uint16_t Width);
void LCD_DrawColorBMP(uint8_t* ptrBitmap, uint16_t Xpos_Init, uint16_t Ypos_Init, uint16_t Height, uint16_t Width);






















void LCD_DeInit(void);  
void LCD_SetColors(__IO uint16_t _TextColor, __IO uint16_t _BackColor); 
void LCD_GetColors(__IO uint16_t *_TextColor, __IO uint16_t *_BackColor);
void LCD_SetTextColor(__IO uint16_t Color);
void LCD_SetBackColor(__IO uint16_t Color);
void LCD_ClearLine(uint8_t Line);
void LCD_Clear(uint16_t Color);
void LCD_SetCursor(uint8_t Xpos, uint16_t Ypos);
void LCD_DrawChar(uint8_t Xpos, uint16_t Ypos, const uint16_t *c);
void LCD_DisplayChar(uint8_t Line, uint16_t Column, uint8_t Ascii);
void LCD_SetFont(sFONT *fonts);
sFONT *LCD_GetFont(void);
void LCD_DisplayStringLine(uint8_t Line, uint8_t *ptr);
void LCD_SetDisplayWindow(uint8_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width);
void LCD_WindowModeDisable(void);
void LCD_DrawLine(uint8_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction);
void LCD_DrawRect(uint8_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width);
void LCD_DrawCircle(uint8_t Xpos, uint16_t Ypos, uint16_t Radius);
void LCD_DrawMonoPict(const uint32_t *Pict);
void LCD_WriteBMP(uint32_t BmpAddress);
void LCD_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void LCD_PolyLine(pPoint Points, uint16_t PointCount);
void LCD_PolyLineRelative(pPoint Points, uint16_t PointCount);
void LCD_ClosedPolyLine(pPoint Points, uint16_t PointCount);
void LCD_ClosedPolyLineRelative(pPoint Points, uint16_t PointCount);
void LCD_FillPolyLine(pPoint Points, uint16_t PointCount);
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
uint16_t LCD_ReadReg(uint8_t LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
uint16_t LCD_ReadRAM(void);
void LCD_PowerOn(void);
void LCD_CtrlLinesConfig(void);
void LCD_FSMCConfig(void);


#endif

#ifdef __cplusplus
}
#endif

#endif /* __MINISTM32_LCD_H */
  
/****END OF FILE****/
