/*
 ******************************************************************************  
 */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MINISTM32_LCD_H
#define __MINISTM32_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"

/* LCD type definition */
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

/* backlight control */

#if (defined(LCD_HSD043I9W) || defined(LCD_AT043TN13))
	/* backlight controlled by MCU */
	#define MCU_BLTCONTROL
#elif defined(LCD_AT070TN83)
	/* backlight controlled by display controller */
	#define SSD1963_BLTCONTROL
#endif

/* MCU backlight control port */
#define BLTCONTROL_PORT				GPIOD
#define BLTCONTROL_PIN				GPIO_Pin_13


/* LCD color (RGB565) */
#define LCD_COLOR_WHITE				0xFFFF
#define LCD_COLOR_BLACK				0x0000
#define LCD_COLOR_GREY				0xF7DE
#define LCD_COLOR_BLUE				0x001F
#define LCD_COLOR_RED				0xF800
#define LCD_COLOR_MAGENTA			0xF81F
#define LCD_COLOR_GREEN				0x07E0
#define LCD_COLOR_CYAN				0x7FFF
#define LCD_COLOR_YELLOW			0xFFE0
#define LCD_COLOR(R, G, B)			((((R)& 0x00F8) << 8) | \
									(((G) & 0x00FC) << 3) | \
									(((B) & 0x00F8) >> 3))  

typedef uint16_t	LCDCOLOR;

void LCD_Init(void);
void LCD_BacklightOn(void);
void LCD_BacklightOff(void);

void LCD_DisplayOn(void);
void LCD_DisplayOff(void);

void LCD_DrawColorBars(void);
void LCD_Clear(LCDCOLOR x);


#if 0




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
