/*******************************************************************************
 *
 */ 

#include "miniSTM32.h"
#include "miniSTM32_lcd.h"

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


/* FSMC use NOR(BANK1) interface with A16 as RS 
 * RS(A16) = 0 : register (8bit)
 * RS(A16) = 1 : data (16bit)
*/
#define Bank1_LCD_Ctrl			((uint32_t)0x60000000) 
#define Bank1_LCD_Data			((uint32_t)0x60020000)


/* SSD 1963 Command Code */

#define CMD_NOP 				0x0000
#define CMD_SOFT_RESET			0x0001
#define CMD_GET_PWR_MODE 		0x000A
#define CMD_GET_ADDR_MODE		0x000B
#define CMD_GET_PIXEL_FMT		0x000C
#define CMD_GET_DISPLAY_MODE 	0x000D
#define CMD_GET_SIGNAL_MODE		0x000E
#define CMD_RESERVED_1			0x000F

#define CMD_ENTER_SLEEP			0x0010
#define CMD_EXIT_SLEEP			0x0011
#define CMD_ENTER_PARTIAL		0x0012
#define CMD_ENTER_NORMAL		0x0013

#define CMD_EXIT_INVERT			0x0020
#define CMD_ENTER_INVERT		0x0021
#define CMD_SET_GAMMA_CURVE		0x0026
#define CMD_SET_DISPLAY_OFF		0x0028
#define CMD_SET_DISPLAY_ON		0x0029
#define CMD_SET_COL_ADDRESS		0x002A
#define CMD_SET_PAGE_ADDRESS	0x002B
#define CMD_WRITE_MEM_START		0x002C
#define CMD_READ_MEM_START		0x002E

#define CMD_SET_PARTIAL_AREA	0x0030
#define CMD_SET_SCROLL_AREA		0x0033
#define CMD_SET_TEAR_OFF		0x0034
#define CMD_SET_TEAR_ON			0x0035
#define CMD_SET_ADDRESS_MODE	0x0036
#define CMD_SET_SCROLL_START	0x0037
#define CMD_EXIT_IDLE_MODE		0x0038
#define CMD_ENTER_IDLE_MODE		0x0039
#define CMD_SET_PIXEL_FMT		0x003A
#define CMD_WRITE_MEM_CONT		0x003C
#define CMD_READ_MEM_CONT		0x003E

#define CMD_SET_TEAR_SCANLINE	0x0044
#define CMD_GET_SCANLINE		0x0045

#define CMD_READ_DDB			0x00A1
#define CMD_RESERVED_2			0x00A8

#define CMD_SET_LCD_MODE		0x00B0
#define CMD_GET_LCD_MODE		0x00B1
#define CMD_SET_HORIZ_PERIOD	0x00B4
#define CMD_GET_HORIZ_PERIOD	0x00B5
#define CMD_SET_VERT_PERIOD		0x00B6
#define CMD_GET_VERT_PERIOD		0x00B7
#define CMD_SET_GPIO_CONF		0x00B8
#define CMD_GET_GPIO_CONF		0x00B9
#define CMD_SET_GPIO_VAL		0x00BA
#define CMD_GET_GPIO_STATUS		0x00BB
#define CMD_SET_POST_PROC		0x00BC
#define CMD_GET_POST_PROC		0x00BD
#define CMD_SET_PWM_CONF		0x00BE
#define CMD_GET_PWM_CONF		0x00BF

#define CMD_SET_LCD_GEN0		0x00C0
#define CMD_GET_LCD_GEN0		0x00C1
#define CMD_SET_LCD_GEN1		0x00C2
#define CMD_GET_LCD_GEN1		0x00C3
#define CMD_SET_LCD_GEN2		0x00C4
#define CMD_GET_LCD_GEN2		0x00C5
#define CMD_SET_LCD_GEN3		0x00C6
#define CMD_GET_LCD_GEN3		0x00C7
#define CMD_SET_GPIO0_ROP		0x00C8
#define CMD_GET_GPIO0_ROP		0x00C9
#define CMD_SET_GPIO1_ROP		0x00CA
#define CMD_GET_GPIO1_ROP		0x00CB
#define CMD_SET_GPIO2_ROP		0x00CC
#define CMD_GET_GPIO2_ROP		0x00CD
#define CMD_SET_GPIO3_ROP		0x00CE
#define CMD_GET_GPIO3_ROP		0x00CF

#define CMD_SET_DBC_CONF		0x00D0
#define CMD_GET_DBC_CONF		0x00D1
#define CMD_SET_DBC_THRESH		0x00D4
#define CMD_GET_DBC_THRESH		0x00D5

#define CMD_SET_PLL				0x00E0
#define CMD_SET_PLL_MN			0x00E2
#define CMD_GET_PLL_MN			0x00E3
#define CMD_GET_PLL_STATUS		0x00E4
#define CMD_SET_DEEP_SLEEP		0x00E5
#define CMD_SET_PIXCLK_FREQ		0x00E6
#define CMD_GET_PIXCLK_FREQ		0x00E7
#define CMD_RESERVED_3			0x00E8
#define CMD_RESERVED_4			0x00E9

#define CMD_SET_PIXDATA_IF_FMT	0x00F0
#define CMD_GET_PIXDATA_IF_FMT	0x00F1
#define CMD_RESERVED_5			0x00FF
#define CMD_DUMMY				0x00A5

/* LCD delay routine : 1 msec interval */
#define LCD_DELAY(x)			do{uLCD_Delay = x; while( uLCD_Delay);} while(0)
#define ABS(x)					((x) > 0 ? (x) : -(x))    
#define INTSWAP(x,y)			do{x ^= y; y ^= x; x ^= y;} while(0)

volatile LCDCOLOR col_fgnd = LCD_COLOR_WHITE;
volatile LCDCOLOR col_bgnd = LCD_COLOR_BLACK;
volatile uint16_t uPenWidth = 1;
volatile uint16_t uLCD_Delay = 0;

void LCD_WR_REG(uint16_t command);
void LCD_WR_Data(uint16_t val);
uint16_t LCD_RD_REG(uint16_t command);
uint16_t LCD_RD_Data(void);
void LCD_SetColumnPageAddr(uint16_t colS, uint16_t colE, uint16_t pageS, uint16_t pageE);
















typedef struct _POINT
{
	int x;
	int y;
} POINT, *PPOINT;

typedef struct _RECT
{
 	int left;
	int top;
	int right;
	int bottom;
} RECT, *PRECT;



/*
unsigned long color1 = 0;
*/


void LCD_Test(void);

void lcd_wr_pixel(unsigned int a, unsigned int b, unsigned int e);
unsigned char *num_pub(unsigned int a);

// PiXCLe Primitives Declarations
void LCD_DrawCheckerPattern(short blue, short green, short red);
void LCD_DrawBackground(short blue, short green, short red);
void LCD_DrawRectangle(int x1, int y1, int x2, int y2, short blue, short green, short red);
//void LCD_DrawLine(int x1, int y1, int x2, int y2, int width, short red, short green, short blue);
//void LCD_DrawPixel(unsigned int a, unsigned int b, unsigned int e);
void LCD_Test_BlackToWhite(void);
void SetLCDStartPixelLineAddress(int x1,int y1, int x2, int y2);


// TODO update colour array comments and names
unsigned int color[] = {0xf800,0x07e0,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xf81f};

unsigned int LCD_RD_data(void);
extern void Delay(__IO uint32_t nCount);

void SetScrollArea(unsigned int top, unsigned int scroll, unsigned int bottom);
void SetScrollStart(unsigned int line);
void SetTearingCfg(unsigned char state, unsigned char mode);


















//	Write a command to the LCD Register
void LCD_WR_REG(uint16_t command)
{
	*(__IO uint16_t *) (Bank1_LCD_Ctrl) =  command;
}

// 	Read a value from an LCD Register
uint16_t LCD_RD_REG(uint16_t command)
{
	 *(__IO uint16_t *) (Bank1_LCD_Ctrl) =  command;

	return *(__IO uint16_t *) (Bank1_LCD_Data);
}


uint16_t LCD_RD_Data(void)
{
	unsigned int a = 0;
	//a = (*(__IO uint16_t *) (Bank1_LCD_Data)); 	//Dummy
	//a =  *(__IO uint16_t *) (Bank1_LCD_Data);  	//H
	//a = a<<8;
	a = *(__IO uint16_t *) (Bank1_LCD_Data); //L

	return(a);	
}

//	Write a pixel in the display. The address counter is incremented by
// 	this command.
void LCD_WR_Data(uint16_t val)
{   
	*(__IO uint16_t *) (Bank1_LCD_Data) =  val; 	
}


// 	Initialize the SSD1963 LCD
// 	PLL == Phase Lock Loop
//	Registers get selected with LCD-WR_REG and then the required data is written
// 	to it with LCD-WR_Data.
void LCD_Init(void)
{ 

	/* port setting */
	MCU_LCDPortInit();

	/* FSMC setting */
	MCU_FSMCInit();

	/* initial hard reset: PE1 */
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);
	LCD_DELAY(1);
	GPIO_SetBits(GPIOE, GPIO_Pin_1);
	LCD_DELAY(1);

	/* setup system clock */

	/* set pll parameters
	 * target system clock	: 110MHz
	 * crystal frequency	: 10MHz
	 * VCO range			: 250MHz - 800MHz
	 * multiplier			: 33 (M = 0x20)
	 * divider				: 3 (N = 0x02)
	 */
	LCD_WR_REG(CMD_SET_PLL_MN);
	LCD_WR_Data(0x0020);
	LCD_WR_Data(0x0002);
	LCD_WR_Data(CMD_DUMMY);
	
	/* enable pll */
	LCD_WR_REG(CMD_SET_PLL);
	LCD_WR_Data(0x0001);

	/* 100 usec delay for locking */
	LCD_DELAY(1);

	/* activate pll output */
	LCD_WR_REG(CMD_SET_PLL);
	LCD_WR_Data(0x0003); 

	LCD_DELAY(1);

	/* soft reset */
	LCD_WR_REG(CMD_SOFT_RESET);

	LCD_DELAY(1);

	/* set tear off */
	/* set gpio configuration */
	/* set post processing */

	/* pixel data interface (host) */
	LCD_WR_REG(CMD_SET_PIXDATA_IF_FMT);
	LCD_WR_Data(0x0003);	/* 16bit 565 */

#if defined(LCD_HSD043I9W)
	
	/* HannStar HSD043I9W */

	/* set pixel clock frequency
	 * pll frequency	: 110MHz
	 * target frequency : 9MHz
	 * LCDC_FPR			: 85793 (0x014F21)
	 */
	LCD_WR_REG(CMD_SET_PIXCLK_FREQ);
	LCD_WR_Data(0x0001);
	LCD_WR_Data(0x004F);
	LCD_WR_Data(0x0021);

	/* set lcd mode 
	 * P1(0x14): data 18bit, dithering, dclk rising edge, hsync low, vsync low
	 * P2(0x00): TFT mode
	 * P3(0x01): HDP 479(0x1DF)
	 * P4(0xDF): HDP 479(0x1DF)
	 * P5(0x01): VDP 271(0x10F)
	 * P6(0x0F): VDP 271(0x10F)
	 * P7(0x00): RGB sequence don't care
	 *
	 */
	LCD_WR_REG(CMD_SET_LCD_MODE);
	LCD_WR_Data(0x14);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x01);
	LCD_WR_Data(0xDF);
	LCD_WR_Data(0x01);
	LCD_WR_Data(0x0F);
	LCD_WR_Data(0X00);

	/* set horizontal timing
	 * P1(0x02): HT - horizontal period : th-1 = 524 (0x20D)
	 * P2(0x0D): HT - horizontal period : th-1 = 524 (0x20D)
	 * P3(0x00): HPS - hsync width + front pouch : Thpw + Thfb = 41 (0x33)
	 * P4(0x33): HPS - hsync width + front pouch : Thpw + Thfb = 41 (0x33)
	 * P5(0x28): HPW - horizontal sync pulse width : Thpw -1 = 40 (0x28)
	 * P6(0x00): LPS - horizontal sync pulse location : 0 (0x00)
	 * P7(0x00): LPS - horizontal sync pulse location : 0 (0x00)
	 * P8(0x00): horizontal sync pulse subpixel start position(LPSPP) : N/A
	 */
	LCD_WR_REG(CMD_SET_HORIZ_PERIOD);
	LCD_WR_Data(0x0002);
	LCD_WR_Data(0x000D);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0033);
	LCD_WR_Data(0x0028);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);

	/* set vertical timing
	 * P1(0x02): VT - vertical period : tV-1 = 287 (0x20C)
	 * P2(0x0C): VT - vertical period : tV-1 = 287 (0x20C)
	 * P3(0x00): VPS - vsync width + front poch : Tvpw + Tvfp = 12 (0x0C)
	 * P4(0x0C): VPS - vsync width + front poch : Tvpw + Tvfp = 12 (0x0C)
	 * P5(0x09): VPW - vertical sync pulse width : Tvpw-1 = 9 (0x09)
	 * P6(0x00): FPS - vertical sync pulse location : 0 (0x00)
	 * P7(0x00): FPS - vertical sync pulse location : 0 (0x00)
	 */
	LCD_WR_REG(CMD_SET_VERT_PERIOD);
	LCD_WR_Data(0x02);
	LCD_WR_Data(0x0C);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x0C);
	LCD_WR_Data(0x09);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x00);

#elif defined(LCD_AT043TN13)

	/* Innolux AT043TN13 */

	/* set pixel clock frequency
	 * pll frequency	: 110MHz
	 * target frequency : 9MHz
	 * LCDC_FPR			: 85793 (0x014F21)
	 */
	LCD_WR_REG(CMD_SET_PIXCLK_FREQ);
	LCD_WR_Data(0x0001);
	LCD_WR_Data(0x004F);
	LCD_WR_Data(0x0021);

	/* set lcd mode 
	 * P1(0x10): data 18bit, dithering, dclk falling edge, hsync low, vsync low
	 * P2(0x00): TFT mode
	 * P3(0x01): HDP 479(0x1DF)
	 * P4(0xDF): HDP 479(0x1DF)
	 * P5(0x01): VDP 271(0x10F)
	 * P6(0x0F): VDP 271(0x10F)
	 * P7(0x00): RGB sequence don't care
	 *
	 */
	LCD_WR_REG(CMD_SET_LCD_MODE);
	LCD_WR_Data(0x10);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x01);
	LCD_WR_Data(0xDF);
	LCD_WR_Data(0x01);
	LCD_WR_Data(0x0F);
	LCD_WR_Data(0X00);

	/* set horizontal timing
	 * P1(0x02): HT - horizontal period : th-1 = 524 (0x20D)
	 * P2(0x0D): HT - horizontal period : th-1 = 524 (0x20D)
	 * P3(0x00): HPS - hsync width + front pouch : thp + thb = 41 (0x33)
	 * P4(0x33): HPS - hsync width + front pouch : thp + thb = 41 (0x33)
	 * P5(0x28): HPW - horizontal sync pulse width : thb -1 = 40 (0x28)
	 * P6(0x00): LPS - horizontal sync pulse location : 0 (0x00)
	 * P7(0x00): LPS - horizontal sync pulse location : 0 (0x00)
	 * P8(0x00): horizontal sync pulse subpixel start position(LPSPP) : N/A
	 */
	LCD_WR_REG(CMD_SET_HORIZ_PERIOD);
	LCD_WR_Data(0x0002);
	LCD_WR_Data(0x000D);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0033);
	LCD_WR_Data(0x0028);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);

	/* set vertical timing
	 * P1(0x02): VT - vertical period : tv-1 = 285 (0x20A)
	 * P2(0x0A): VT - vertical period : tv-1 = 285 (0x20A)
	 * P3(0x00): VPS - vsync width + front poch : Tvpw + Tvfp = 12 (0x0C)
	 * P4(0x0C): VPS - vsync width + front poch : Tvpw + Tvfp = 12 (0x0C)
	 * P5(0x09): VPW - vertical sync pulse width : Tvpw-1 = 9 (0x09)
	 * P6(0x00): FPS - vertical sync pulse location : 0 (0x00)
	 * P7(0x00): FPS - vertical sync pulse location : 0 (0x00)
	 */
	LCD_WR_REG(CMD_SET_VERT_PERIOD);
	LCD_WR_Data(0x02);
	LCD_WR_Data(0x0A);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x0C);
	LCD_WR_Data(0x09);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x00);

#elif defined(LCD_AT070TN83)

	/* Innolux AT070TN83 */

	/* set pixel clock frequency
	 * pll frequency	: 110MHz
	 * target frequency : 33.3MHz
	 * LCDC_FPR			: 317433 (0x04D7F9)
	 */
	LCD_WR_REG(CMD_SET_PIXCLK_FREQ);
	LCD_WR_Data(0x0004);
	LCD_WR_Data(0x00D7);
	LCD_WR_Data(0x00F9);

	/* set lcd mode 
	 * P1(0x10): data 18bit, dithering, dclk falling edge, hsync low, vsync low
	 * P2(0x00): TFT mode
	 * P3(0x03): HDP 799(0x31F)
	 * P4(0x1F): HDP 799(0x31F)
	 * P5(0x01): VDP 479(0x1DF)
	 * P6(0xDF): VDP 479(0x1DF)
	 * P7(0x00): RGB sequence don't care
	 *
	 */
	LCD_WR_REG(CMD_SET_LCD_MODE);
	LCD_WR_Data(0x10);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x03);
	LCD_WR_Data(0x1F);
	LCD_WR_Data(0x01);
	LCD_WR_Data(0xDF);
	LCD_WR_Data(0X00);

	/* set horizontal timing
	 * P1(0x03): HT - horizontal period : tHP+tHW-1 = 975 (0x3CF)
	 * P2(0xCF): HT - horizontal period : tHP+tHW-1 = 975 (0x3CF)
	 * P3(0x00): HPS - hsync width + front pouch : tHW + tHFP = 88 (0x58)
	 * P4(0x58): HPS - hsync width + front pouch : tHW + tHFP = 88 (0x58)
	 * P5(0x2F): HPW - horizontal sync pulse width : tHW -1 = 47 (0x2F)
	 * P6(0x00): LPS - horizontal sync pulse location : 0 (0x00)
	 * P7(0x00): LPS - horizontal sync pulse location : 0 (0x00)
	 * P8(0x00): horizontal sync pulse subpixel start position(LPSPP) : N/A
	 */
	LCD_WR_REG(CMD_SET_HORIZ_PERIOD);
	LCD_WR_Data(0x0003);
	LCD_WR_Data(0x00CF);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0058);
	LCD_WR_Data(0x002F);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);

	/* set vertical timing
	 * P1(0x02): VT - vertical period : tVP-1 = 524 (0x20C)
	 * P2(0x0C): VT - vertical period : tVP-1 = 524 (0x20C)
	 * P3(0x00): VPS - vsync width + front poch : tVW + tVFP = 16 (0x10)
	 * P4(0x10): VPS - vsync width + front poch : tVW + tVFP = 16 (0x10)
	 * P5(0x02): VPW - vertical sync pulse width : tVW-1 = 2 (0x02)
	 * P6(0x00): FPS - vertical sync pulse location : 0 (0x00)
	 * P7(0x00): FPS - vertical sync pulse location : 0 (0x00)
	 */
	LCD_WR_REG(CMD_SET_VERT_PERIOD);
	LCD_WR_Data(0x02);
	LCD_WR_Data(0x0C);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x10);
	LCD_WR_Data(0x02);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x00);

#endif /* LCD_AT070TN83 */

	/* set address mode */
	LCD_WR_REG(CMD_SET_ADDRESS_MODE);
	LCD_WR_Data(0x00);

	/* clear lcd */
	LCD_Clear(LCD_COLOR_BLACK);
}

void LCD_BacklightOn(void)
{

#if defined(MCU_BLTCONTROL)

	GPIO_SetBits(BLTCONTROL_PORT, BLTCONTROL_PIN);

#elif defined(SSD1963_BLTCONTROL)

	/* pwm configuration (300Hz, 100%)
	 * P1(0x06) : PWMF - PWM frequency in system clock : 6 (0x06)
	 * P2(0xFF) : PWM - PWM duty cycle : 255 (0xFF)
	 * P3(0x01) : PWM enabled, control by host : (0x01)
	 * P4(0x00) : DBC manual brightness : (0x00)
	 * P5(0x00) : DBC minimum brightness : (0x00)
	 * p6(0x00) : brightness prescaler : (0x00)
	 */

	LCD_WR_REG(CMD_SET_PWM_CONF);
	LCD_WR_Data(0x0006);
	LCD_WR_Data(0x00FF);
	LCD_WR_Data(0x0001);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);

#endif /* LCD_AT070TN83 */

}

void LCD_BacklightOff(void)
{
#if defined(MCU_BLTCONTROL)

	GPIO_ResetBits(BLTCONTROL_PORT, BLTCONTROL_PIN);

#elif defined(SSD1963_BLTCONTROL)

	/* pwm configuration (300Hz, 100%)
	 * P1(0x00) : PWMF - PWM frequency in system clock : 0 (0x00)
	 * P2(0x00) : PWM - PWM duty cycle : 0 (0x00)
	 * P3(0x00) : PWM disabled, control by host : (0x01)
	 * P4(0x00) : DBC manual brightness : (0x00)
	 * P5(0x00) : DBC minimum brightness : (0x00)
	 * p6(0x00) : brightness prescaler : (0x00)
	 */

	LCD_WR_REG(CMD_SET_PWM_CONF); //set PWM for Backlight. Manual p.53
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);

#endif /* LCD_AT070TN83 */
}

//
//	Clear the LCD display by zeroing each pixel using
//	a double loop.
//	The LCD is HDP+1 x VDP+1
//
void LCD_Clear(LCDCOLOR col)
{
	uint32_t index = 0;

	LCD_SetColumnPageAddr(0, LCD_WIDTH-1, 0, LCD_HEIGHT-1);
	LCD_WR_REG(CMD_WRITE_MEM_START);

	while( index < (LCD_WIDTH * LCD_HEIGHT) )
	{
		LCD_WR_Data(col);
		index++;
	}
}



void LCD_DisplayOn(void)
{
	LCD_WR_REG(CMD_SET_DISPLAY_ON);
}

void LCD_DisplayOff(void)
{
	LCD_WR_REG(CMD_SET_DISPLAY_OFF);
}

void LCD_SetFGColor(LCDCOLOR col)
{
	col_fgnd = col;
}

void LCD_SetBGColor(LCDCOLOR col)
{
	col_bgnd = col;
}

void LCD_SetPenWidth(uint16_t w)
{
	uPenWidth = w;
}

uint16_t LCD_GetPenWidth(void)
{
	return uPenWidth;
}

void LCD_SetColors(LCDCOLOR fgcol, LCDCOLOR bgcol)
{
	LCD_SetFGColor(fgcol);
	LCD_SetBGColor(bgcol);
}

void LCD_GetColors(LCDCOLOR *pfgcol, LCDCOLOR *pbgcol)
{
	*pfgcol = col_fgnd;
	*pbgcol = col_bgnd;
}

void LCD_DrawPixel(int16_t x, int16_t y)
{
	LCD_SetColumnPageAddr(x, x, y, y);
	LCD_WR_REG(CMD_WRITE_MEM_START);
	LCD_WR_Data(col_fgnd);
}

/**
 * @brief	Line drawing algorithm based on line segment(660 msec for 640 calls).
 * @param	x1: specifies the point 1 x position.
 * @param	y1: specifies the point 1 y position.
 * @param	x2: specifies the point 2 x position.
 * @param	y2: specifies the point 2 y position.
 * @retval	None
 * @brief	This algorithm assumes that the coordinate of upper left corner of
 *			the screen is (0,0), x value increases as it goes right, and
 *			y value increases as it goes down.
 */

void LCD_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{

	int16_t dx = x2 - x1;
	int16_t dy = y2 - y1;

	int16_t s0, s1, ln, sh, num;
	int16_t a0 = uPenWidth>>1;
	int16_t a1 = uPenWidth - (uPenWidth>>1) - 1;

	/* 2,3,6,7 octant */
	if( ABS(dx) > ABS(dy) )
	{
		/* swapping is required */
		if(dx < 0)
		{
			INTSWAP(x1, x2);
			INTSWAP(y1, y2);
		}
		dx = x2 - x1;
		dy = y2 - y1;

		/* horizontal line (y1 = y2) */
		if(dy == 0)
		{
			LCD_DrawFillRect(x1, y1 - a0, x2, y1 + a1);
			return;
		}
		else if(dy < 0)
		{
			s1 = -1; 
			sh = -dy;
		}
		else if(dy > 0)
		{
			s1 = 1;
			sh = dy;
		}

		num = dx >> 1;
		s0 = x1;

		while(x1 < x2)
		{
			num += sh;
			if(!(num < dx))
			{
				LCD_DrawFillRect(s0, y1 - a0, x1, y1 + a1);
				num -= dx;
				s0 = x1;
				y1 += s1;
			}
			x1++;
		}

		/* line ending */
//		if( s0 < x2 ) 
			LCD_DrawFillRect(s0, y2 - a0, x2, y2 + a1);
	}
	/* 1,4,5,8 octant */
	else
	{
		/* SWAP is required */
		if(dy < 0)
		{
			INTSWAP(x1, x2);
			INTSWAP(y1, y2);
		}

		dx = x2 - x1;
		dy = y2 - y1;

		/* vertical line (x1 = x2)*/
		if(dx == 0)
		{
			LCD_DrawFillRect(x1 - a0, y1, x2 + a1, y2);
			return;
		}
		else if(dx < 0)
		{
			s1 = -1; 
			sh = -dx;
		}
		else if(dx > 0)
		{
			s1 = 1; 
			sh = dx;
		}

		num = dy >> 1;

		s0 = y1;

		while(y1 < y2)
		{
			num += sh;
			if(!(num < dy))
			{
				LCD_DrawFillRect(x1 - a0, s0, x1 + a1, y1);
				num -= dy;
				s0 = y1;
				x1 += s1;
			}
			y1++;
		}
		/* line ending */
//		if( s0 < y2 ) 
			LCD_DrawFillRect(x2 - a0, s0, x2 + a1, y2);
	}
}

#if defined(LCD_TEST)
/* second version of Bresenham algorithm (1000 msec for 640 calls) */
void LCD_DrawLineB(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	int16_t dx = x2 - x1;
	int16_t dy = y2 - y1;
	int16_t sx1 = 0, sy1 = 0, sx2 =0, sy2 = 0;
	int16_t ln, sh, num;

	if(dx < 0) 
	{
		sx1 = -1; 
		sx2 = -1;
	} 
	else if(dx > 0) 
	{
		sx1 = 1; 
		sx2 = 1;
	}

	if(dy < 0) 
		sy1 = -1; 
	else if(dy > 0) 
		sy1 = 1;

	ln = ABS(dx); 
	sh = ABS(dy);

	if( !(ln > sh) )
	{
		ln = ABS(dy); 
		sh = ABS(dx);

		if(dy < 0) sy2 = -1; 
		else if(dy > 0) sy2 = 1;

		sx2 = 0;
	}

	num = ln >> 1;

	for(dx = 0; dx <= ln; dx++)
	{
		LCD_DrawPixel(x1, y1);
		num += sh;

		if(!(num < ln))
		{
			num -= ln;
			x1 += sx1;
			y1 += sy1;
		}
		else
		{
			x1 += sx2;
			y1 += sy2;
		}
	}

#if 0
/* first version of Bresenham algorithm */
	int16_t dx = ABS(x2 - x1), sx = x1 < x2 ? 1 :-1;
	int16_t dy = -ABS(y2 - y1), sy = y1 < y2 ? 1 : -1;
	int16_t err = dx + dy, e2;
	
	/* FIXME : 2 vertical lines */
	while(1)
	{
		LCD_DrawPixel(x1, y1);
		if((x1 == x2) && (y1 == y2)) break;

		e2 = err * 2;

		if(e2 >= dy)
		{
			err += dy;
			x1 += sx;
		}

		if(e2 <= dx)
		{
			err += dx;
			y1 += sy;
		}
	}
#endif
}
#endif /* LCD_TEST */

/**
 * @brief	Besenham circle drawing algorithm.
 * @param	x: specifies the x position of the center.
 * @param	y: specifies the y position of the center.
 * @param	r: specifies the radius of the circle.
 * @retval	None
 */
void LCD_DrawCircle(int16_t x, int16_t y, int16_t r)
{
	int16_t xt, yt, err, r0, r1, rx;

	r0 = r - (uPenWidth>>1);
	r1 = r + (uPenWidth>>1);

	for(rx = r0; rx <= r1; rx++)
	{
		r = rx;
		xt = -r;
		yt = 0;
		err = 2 - (r<<1);

		do{
			/* first quadrant */
			LCD_DrawPixel(x - xt, y + yt);
			/* second quadrant */
			LCD_DrawPixel(x - yt, y - xt);
			/* third quadrant */
			LCD_DrawPixel(x + xt, y - yt);
			/* forth quadrant */
			LCD_DrawPixel(x + yt, y + xt);

			r = err;

			if( r > xt ) err += ((++xt)<<1) + 1;
			if( r <= yt ) err += ((++yt)<<1) + 1;
		
		} while(xt < 0);
	}
}


/**
 * @brief	Besenham ellipse drawing algorithm.
 * @param	x1: specifies the point 1 x position.
 * @param	y1: specifies the point 1 y position.
 * @param	x2: specifies the point 2 x position.
 * @param	y2: specifies the point 2 y position.
 * @retval	None
 */
void LCD_DrawEllipseRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	int16_t a = ABS(x2 - x1), b = ABS(y2 - y1), b1 = b & 1;
	int32_t dx = 4*(1 - a)*b*b, dy = 4*(b1 + 1)*a*a;
	int32_t err = dx + dy + b1*a*a, e2;

	if(x1 > x2)
	{
		x1 = x2;
		x2 += a;
	}
	if(y1 > y2) y1 = y2;

	y1 += (b + 1)/2;
	y2 = y1 - b1;
	a *= 8 * a;
	b1 = 8 * b * b;
	
	do{
		LCD_DrawPixel(x2, y1);
		LCD_DrawPixel(x1, y1);
		LCD_DrawPixel(x1, y2);
		LCD_DrawPixel(x2, y2);

		e2 = 2 * err;
		if(e2 >= dx)
		{
			x1++; 
			x2--;
			err += dx += b1;
		}
		if(e2 <= dy)
		{
			y1++;
			y2--;
			err += dy += a;
		}
	} while(x1 <= x2);

	while((y1 - y2) < b)
	{
		LCD_DrawPixel(x1 - 1, y1);
		LCD_DrawPixel(x2 + 1, y1++);
		LCD_DrawPixel(x1 - 1, y2);
		LCD_DrawPixel(x2 + 1, y2--);
	}
}

#if defined(LCD_TEST) 

uint16_t LCD_DrawTestPattern(unsigned int index)
{
	uint16_t i, j;
	uint16_t retval;
	int16_t x1, y1, x2, y2, delx, dely;

	uint16_t dif_red, dif_green, dif_blue;
	uint16_t col_red, col_green, col_blue;

	LCDCOLOR col;
	LCDCOLOR colors[8]={
		LCD_COLOR_RED,
		LCD_COLOR_GREEN,
		LCD_COLOR_BLUE,
		LCD_COLOR_MAGENTA,
		LCD_COLOR_CYAN,
		LCD_COLOR_YELLOW,
		LCD_COLOR_GREY,
		LCD_COLOR_WHITE};

	/* black background */
	LCD_Clear(col_bgnd);
	LCD_SetBGColor(LCD_COLOR_BLACK);

	/* milisecond counter start */
	uLCD_Delay = 0xFFFF;

	/* draw 640 lines with Bresenham algorithm */
	if(index == 1)
	{
		delx = LCD_WIDTH / 16;
		dely = LCD_HEIGHT / 8;

		/* lines between vertical points */
		LCD_SetFGColor(LCD_COLOR_GREEN);
		x1 = delx;
		x2 = LCD_WIDTH - delx;
		y1 = dely;

		for( i = 1; i < 8; i++ )
		{
			y2 = dely;

			for( j = 1; j < 8; j++ )
			{
				LCD_DrawLineB(x1, y1, x2, y2);
				LCD_DrawLineB(x2, y2, x1, y1);
				y2 += dely;
			}

			y1 += dely;
		}

		/* lines between horizontal points */
		LCD_SetFGColor(LCD_COLOR_BLUE);
		y1 = dely;
		y2 = LCD_HEIGHT - dely;
		x1 = delx;

		for( i = 1; i < 16; i++ )
		{
			x2 = delx;

			for( j = 1; j < 16; j++ )
			{
				LCD_DrawLineB(x1, y1, x2, y2);
				LCD_DrawLineB(x2, y2, x1, y1);
				
				x2 += delx;
			}

			x1 += delx;
		}
	}
	/* draw 640 lines with line segment method */
	else if(index == 2)
	{
		delx = LCD_WIDTH / 16;
		dely = LCD_HEIGHT / 8;

		/* lines between vertical points */
		LCD_SetFGColor(LCD_COLOR_GREEN);
		x1 = delx;
		x2 = LCD_WIDTH - delx;
		y1 = dely;

		for( i = 1; i < 8; i++ )
		{
			y2 = dely;

			for( j = 1; j < 8; j++ )
			{
				LCD_DrawLine(x1, y1, x2, y2);
				LCD_DrawLine(x2, y2, x1, y1);
				y2 += dely;
			}

			y1 += dely;
		}

		/* lines between horizontal points */
		LCD_SetFGColor(LCD_COLOR_BLUE);
		y1 = dely;
		y2 = LCD_HEIGHT - dely;
		x1 = delx;

		for( i = 1; i < 16; i++ )
		{
			x2 = delx;

			for( j = 1; j < 16; j++ )
			{
				LCD_DrawLine(x1, y1, x2, y2);
				LCD_DrawLine(x2, y2, x1, y1);
				x2 += delx;
			}

			x1 += delx;
		}
	}
	/* draw 256 lines with thickness 5 */
	else if(index == 3)
	{
		delx = LCD_WIDTH / 8;
		dely = LCD_HEIGHT / 8;

		LCD_SetPenWidth(5);
		/* lines between vertical points */
		LCD_SetFGColor(LCD_COLOR_GREEN);
		x1 = delx;
		x2 = LCD_WIDTH - delx;
		y1 = dely;

		for( i = 1; i < 8; i++ )
		{
			y2 = dely;

			for( j = 1; j < 8; j++ )
			{
				LCD_DrawLine(x1, y1, x2, y2);
				LCD_DrawLine(x2, y2, x1, y1);
				y2 += dely;
			}

			y1 += dely;
		}

		/* lines between horizontal points */
		LCD_SetFGColor(LCD_COLOR_BLUE);
		y1 = dely;
		y2 = LCD_HEIGHT - dely;
		x1 = delx;

		for( i = 1; i < 8; i++ )
		{
			x2 = delx;

			for( j = 1; j < 8; j++ )
			{
				LCD_DrawLine(x1, y1, x2, y2);
				LCD_DrawLine(x2, y2, x1, y1);
				x2 += delx;
			}

			x1 += delx;
		}

		LCD_SetPenWidth(1);
	}
	/* draw 8 rectangles with various sizes and line thickness */
	else if(index == 4)
	{
		delx = LCD_WIDTH>>4;
		dely = LCD_HEIGHT>>4;
		/* upper left corner of the first rectangle */
		x1 = 0; y1 = 0;	
		/* lower right corner of the first rectangle */
		x2 = LCD_WIDTH>>1; y2 = LCD_HEIGHT>>1;

		for(i = 0; i < 8; i++)
		{
			LCD_SetFGColor(colors[i]);

			LCD_DrawRect(x1, y1, x2, y2);

			uPenWidth++;

			x1 += delx; x2 += delx;
			y1 += dely; y2 += dely;
		}

		LCD_SetPenWidth(1);
	}
	/* draw 8 circles with various sizes and line thickness */
	else if(index == 5)
	{
		dely = LCD_HEIGHT>>4;

		/* center and radius */
		x1 = LCD_WIDTH>>1;
		y1 = LCD_HEIGHT>>1;
		y2 = LCD_HEIGHT>>2;

		for(i = 0; i < 8; i++)
		{
			LCD_SetFGColor(colors[i]);

			LCD_DrawCircle(x1, y1, y2);

			uPenWidth++;

			y2 += dely;
		}

		LCD_SetPenWidth(1);
	}
	/* draw 8 ellipses with various sizes and line thickness */
	else if(index == 6)
	{

		dely = LCD_HEIGHT>>4;

		/* center and radius */
		x1 = LCD_WIDTH>>1;
		y1 = LCD_HEIGHT>>1;
		y2 = LCD_HEIGHT>>2;

		for(i = 0; i < 8; i++)
		{
			LCD_SetFGColor(colors[i]);

			LCD_DrawCircle(x1, y1, y2);

			uPenWidth++;

			y2 += dely;
		}

		LCD_SetPenWidth(1);

	}
	/* draw color filled rectangles */
	else if(index == 7)
	{
		LCD_SetFGColor(LCD_COLOR_BLUE);
		LCD_DrawFillRect(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);
	}
	/* draw color filled circles */
	else if(index == 8)
	{
		LCD_SetFGColor(LCD_COLOR_RED);
		LCD_DrawCircle((LCD_WIDTH>>1), (LCD_HEIGHT>>1) - 1, (LCD_HEIGHT>>1) - 1);
	}
	/* draw color filled ellipses */
	else if(index == 9)
	{
	}
	/* draw points */
	else if(index == 10)
	{
		LCD_SetFGColor(LCD_COLOR_RED);

		x1 = x2 = LCD_WIDTH / 8;
		y1 = y2 = LCD_HEIGHT / 8;

		for( i = 0; i < 7; i++)
		{
			x1 = x2;

			for( j = 0; j < 7; j++ )
			{
				LCD_DrawPixel(x1, y1);
				x1 += x2;
			}

			y1 += y2;
		}

	}
	/* all the other case: contrast color bar(7 color bar, 32 cells each) */
	else
	{
		delx = 	LCD_WIDTH / 32;
		dely = LCD_HEIGHT / 7;

		/* initial y positions */
		y1 = 0;
		y2 = y1 + dely;

		for( i = 0; i < 7; i++ )
		{
			/* initial x positions */
			x1 = 0;
			x2 = x1 + delx;

			if(i == 0)
			{
				/* blue color bar */
				dif_red = 0x00;
				dif_green = 0x00;
				dif_blue = ((0xFF)>>5);
			}
			else if(i == 1)
			{
				/* green color bar */
				dif_red = 0x00;
				dif_green = ((0xFF)>>5);
				dif_blue = 0x00;
			}
			else if(i == 2)
			{
				/* cyan color bar */
				dif_red = 0x00;
				dif_green = ((0xFF)>>5);
				dif_blue = ((0xFF)>>5);
			}
			else if(i == 3)
			{
				/* red color bar */
				dif_red = ((0xFF)>>5);
				dif_green = 0x00;
				dif_blue = 0x00;
			}
			else if(i == 4)
			{
				/* magenta color bar */
				dif_red = ((0xFF)>>5);
				dif_green = 0x00;
				dif_blue = ((0xFF)>>5);
			}
			else if(i == 5)
			{
				/* yellow color bar */
				dif_red = ((0xFF)>>5);
				dif_green = ((0xFF)>>5);
				dif_blue = 0x00;
			}
			else if(i == 6)
			{
				/* white color bar */
				dif_red = ((0xFF)>>5);
				dif_green = ((0xFF)>>5);
				dif_blue = ((0xFF)>>5);
			}

			/* initial color value */
			col_red = dif_red;
			col_green = dif_green;
			col_blue = dif_blue;

			for( j = 0; j < 32; j++ )
			{
				LCD_SetFGColor(LCD_COLOR(col_red, col_green, col_blue));
				LCD_DrawFillRect(x1, y1 , x2, y2);

				/* next color value */
				col_red += dif_red;	
				col_green += dif_green;
				col_blue += dif_blue;

				/* next x position */
				x1 = x2 ;
				x2 = x1 + delx;

			}

			/* advance to the next y position */
			y1 = y2;
			y2 = y2 + dely;

			/* revert x position */

		}
	}

	retval = 0xFFFF - uLCD_Delay;
	uLCD_Delay = 0;

	return retval;
}

#endif /* LCD_TEST */

void LCD_SetColumnPageAddr(uint16_t colS, uint16_t colE, uint16_t pageS, uint16_t pageE)
{
	/* set column address */
	LCD_WR_REG(CMD_SET_COL_ADDRESS);
	/* start column */
	LCD_WR_Data(colS >> 8);
	LCD_WR_Data(colS & 0x00ff);
	/* end column */
	LCD_WR_Data(colE >> 8);
	LCD_WR_Data(colE & 0x00ff);

	/* set page address */
    LCD_WR_REG(CMD_SET_PAGE_ADDRESS);
	/* start page */
	LCD_WR_Data(pageS >> 8);
	LCD_WR_Data(pageS & 0x00ff);
	/* end page */
	LCD_WR_Data(pageE >> 8); 
	LCD_WR_Data(pageE & 0x00ff);
}


void LCD_DrawRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	LCD_DrawLine(x1, y1, x1, y2);
	LCD_DrawLine(x1, y1, x2, y1);
	LCD_DrawLine(x2, y1, x2, y2);
	LCD_DrawLine(x1, y2, x2, y2);
}

void LCD_DrawFillRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	int16_t ref_x;
	LCD_SetColumnPageAddr(x1, x2, y1, y2);
	LCD_WR_REG(CMD_WRITE_MEM_START);

	ref_x = x1;
	while(y1 <= y2)
	{
		while(x1 <= x2)
		{
			LCD_WR_Data(col_fgnd);
			x1++;
		}
		y1++;
		x1 = ref_x;
	}
}


































//
//	Set the LCD start line and pixel rectangular region for writing
//	Note the alignment of the 4.3" display on the STM32 board results
//	in the display being inverted. Hence the coordinates are inverted and flipped.
//	so (0,0) is the TLCorner.
//
void SetLCDStartPixelLineAddress(int pixel_x1, int line_y1, int pixel_x2, int line_y2)
{
	// Invert and flip the coordinates
	//pixel_x1 = HDP + pixel_x1 - pixel_x2;
	//pixel_x2 = HDP - pixel_x1;

	//line_y1 = VDP - line_y1 - line_y2;
	//line_y2 = VDP - line_y1;
				  	
   	// Set the start column and page addresses. These are written as four
	// sequential 8 bit values. 
	LCD_WR_REG(CMD_SET_COL_ADDRESS); // Manual p.29	
	LCD_WR_Data(pixel_x1 >> 8);	// start column high byte    
	LCD_WR_Data(pixel_x1 & 0x00ff);	// start column low byte

	// HDP = horizontal data pixel eg 479.
	LCD_WR_Data(pixel_x2 >> 8);  	// end column # high byte	    
	LCD_WR_Data(pixel_x2 & 0x00ff); // end column # low byte

    LCD_WR_REG(CMD_SET_PAGE_ADDRESS); // Manual p.29	
	LCD_WR_Data(line_y1 >> 8);	// start row high byte     
	LCD_WR_Data(line_y1 & 0x00ff);	// start row low byte

	// VDP = vertical data pixel eg 271
	LCD_WR_Data(line_y2 >> 8);  	// end row high byte	    
	LCD_WR_Data(line_y2 & 0x00ff);  // end row low byte

	// Set writing to commence
	LCD_WR_REG(CMD_WRITE_MEM_START);

	return;
} 


//
//	Display LCD Test utility function
// 
// 	Check the LCD dimensions and draw colour | Inverse colour checker
// 	board pattern.
//
void LCD_DrawCheckerPattern(short blue, short green, short red)
{
    unsigned int lineWidth = LCD_WIDTH,height = LCD_HEIGHT, w;
	unsigned short rgb666_1  =  0;
	unsigned short rgb666_2  =  0;
	int check_x = 10;
	int check_y = 8;

	// Convert the R,G,B values into RGB666
	rgb666_1  =  red<<12;
	rgb666_1 |=  green<<6;
	rgb666_1 |=  blue;

	rgb666_2 = !rgb666_1;


	SetLCDStartPixelLineAddress(0,0,lineWidth-1,height-1);

	while(lineWidth--)
	{
	    for(w  =  0;w < height;w++)
		{    
          	LCD_WR_Data(rgb666_1);
		}
	}

}



//	PiXCLe command primitive PARTIALLY TESTED
// 	Draws a line from between two coordinates, using a Pen width and colour
//	Needs to work out the addresses where the line is to be drawn. Does not 
//	take in to account anti-aliasing
/*
void LCD_DrawLine(int x1, int y1, int x2, int y2, int width, short red, short green, short blue)
{
	// For now, just do vertical or horizongtal lines. Diagonals come later.
 	int lineWidth  =  x2 - x1 + 1, w;
	int height  =  y2 - y1 + 1 + width;
	unsigned short rgb666  =  0;

	// Convert the R,G,B values into RGB666
	rgb666  =  red<<12;
	rgb666 |=  green<<6;
	rgb666 |=  blue;

	SetLCDStartPixelLineAddress(x1,y1,x2,y2);

	// TODO: sort code to draw diagonals, of required width, and anti-aliased.

	while(lineWidth--)
	{
	    for(w = 0;w < height;w++)
		{   
          	LCD_WR_Data(rgb666);
		}
	}

}
*/

// PiXCLe command primitive PARTIALLY TESTED
// Draws an ellipse (or circle) within the bounding rectangle. Use the trig functions to 
// decide if a rectangle coord is within the ellipse or not. Look at the distance from
// the center to the coord.
// if Sqr((x-x0)/a) + Sqr((y-y0)/b) <=1 then (x,y) point lies inside ellipse
// if ellipse is defined by bounding rectangle, then
// x0 = (x1+x2) / 2
// y0 = (y1+y2) / 2
// a = (x2-x1) / 2
// b = (y2-y1) / 2

void LCD_DrawEllipse(int x1, int y1, int x2, int y2, short red, short green, short blue)
{  	

	double x0, y0, a,b, dtest;
	int x, y, dummy;
 	int lineWidth;
	int height;
	unsigned short rgb666  =  0;

	lineWidth  =  x2 - x1 + 1;
	height  =  y2 - y1 + 1;


	// Convert the R,G,B values into RGB666
	rgb666  =  red<<12;
	rgb666 |=  green<<6;
	rgb666 |=  blue;


	SetLCDStartPixelLineAddress(x1,y1,x2,y2);

	// This is drawing in the [x1,y1] to [x2,y2] region
	x0 = (x1+x2) / 2;
	y0 = (y1+y2) / 2;
	a = (x2-x1) / 2;
	b = (y2-y1) / 2;
	a = a*a;
	b = b*b;

	for(y = y1;y < y1 + height; y++)
	{
		for(x = x1; x < x1 + lineWidth; x++)
		{   
			// Test if the point is in the ellipse and draw it
			dtest =	((x-x0)*(x-x0)/a + (y-y0)*(y-y0)/b);
			if (1.0 > dtest)
          		LCD_WR_Data(rgb666);
			else // increment the counter without writing
			{	
				LCD_WR_Data(0); // TODO: just incr the counter
			}
		}
	}

}

// PiXCLe command primitive PARTIALLY TESTED
void LCD_DrawRectangle(int x1, int y1, int x2, int y2, short red, short green, short blue)
{
	int lineWidth  =  x2 - x1 + 1, w;
	int height  =  y2 - y1 + 1;
	unsigned short rgb666  =  0;

	// Convert the R,G,B values into RGB666
	rgb666  =  red<<12;
	rgb666 |=  green<<6;
	rgb666 |=  blue;


	SetLCDStartPixelLineAddress(x1,y1,x2,y2);

	// The 4.3" LCD is 480x272. The 7.0" LCD is 800x480. 
	// Clip the rectangle to the screen.
	while(lineWidth--)
	{
	    for(w = 0;w < height;w++)
		{   
          	LCD_WR_Data(rgb666);
		}
	}

}

// PiXCLe command primitive
void LCD_Test_BlackToWhite(void)
{
    unsigned int lineWidth  =  LCD_WIDTH,height  =  LCD_HEIGHT, w;
	unsigned short rgb888  =  0;
	unsigned int width = LCD_WIDTH, counter = 0;

	// Write the whole screen
	SetLCDStartPixelLineAddress(0,0,lineWidth-1,height-1);

	// This double loop writes the vertical pixels, not lines at a time.
	// The address register increments on each call to LCD_WR_Data 
	while(lineWidth--)
	{
	    for(w = 0;w < height;w++)
		{   
			// Write a single 24 bit RGB pixel. The pixel address counter updates.
          	LCD_WR_Data(rgb888);
			if (0 == ++counter%width)
				rgb888 += 64;
				
		}
	}
}

// PiXCLe command primitive
void LCD_DrawBackground(short blue, short green, short red)
{
    unsigned int lineWidth  =  LCD_WIDTH,height  =  LCD_HEIGHT, w;
	unsigned short rgb666  =  0;

	SetLCDStartPixelLineAddress(0,0,lineWidth-1,height-1);
	
	// Convert the R,G,B values into RGB666
	rgb666  =  blue<<12;
	rgb666 |=  green<<6;
	rgb666 |=  red;
	// The 4.3" LCD is 480x272
	while(lineWidth--)
	{
	    for(w = 0;w < height;w++)
		{   
			// Write a single pixel.
          	LCD_WR_Data(rgb666);
		}
	}
}

//	Tests the LCD
void LCD_Test(void)
{
	unsigned int  temp = 0;
	//unsigned char *p;
	unsigned long n;
	//	unsigned int line = 0;
    


	//LCD_WR_REG(CMD_SET_PLL); // irrelevent here
	n = 0;
	
#if 0

	LCD_WR_REG(CMD_SET_COL_ADDRESS);	
	LCD_WR_Data(0);	    
	LCD_WR_Data(0);
	LCD_WR_Data(HDP>>8);	    
	LCD_WR_Data(HDP&0x00ff);

	LCD_WR_REG(CMD_SET_PAGE_ADDRESS);	
	LCD_WR_Data(0);	    
	LCD_WR_Data(0);
	LCD_WR_Data(VDP>>8);	    
	LCD_WR_Data(VDP&0x00ff);
	LCD_WR_REG(0x002c);
	
#endif
	
	while(n<261120)
	{
		     //while(1){

		//	temp = (uint16_t)( a2[n]<<8)+a2[n+1];
			temp = 0xf800;
			  //temp++;	
			LCD_WR_Data(temp);
		//	if(n<125000)
		//	LCD_WR_Data(0x07e0);
		//	else
		//	 LCD_WR_Data(0x001f);
		
			n = n+2;
			// }
			 //LCD_WR_Data(color1);
 	}

	
  // SetScrollArea(0,480,0);
  // for(line = 0;line<480;line++) 
  // {
  // SetScrollStart(line);
  // Delay(0xffff);
  // }


	//Delay(0xafffff);
	/*
    lcd_wr_zf(0,0,239,319,870,color1,1,&zf3[0]);  
	p = num_pub((color1/10000));
	lcd_wr_zf(0,30,23,61,96,color1,0,p);  
	
	p = num_pub((color1%10000)/1000);
	lcd_wr_zf(24,30,47,61,96,color1,0,p);
	
	p = num_pub(((color1%10000)%1000)/100);
	lcd_wr_zf(48,30,71,61,96,color1,0,p);

	p = num_pub((((color1%10000)%1000)%100)/10);
	lcd_wr_zf(72,30,95,61,96,color1,0,p);

	p = num_pub((color1%10));
	lcd_wr_zf(96,30,119,61,96,color1,0,p);

	color1++; 
	if(color1 = =65536) color1 = 0; */ 
	//Delay(0xaffff);			
}

/*
 * Brian : comment out for now
//
//	Delay for specified period.
//	All this does run two loops that increment their counters.
//	The 'a' loop increments to 1000, suggesting this is us or 
//	clock cycles. The ARM apparently uses mostly 1 clock per instruction.
void delay_time(unsigned int i)
{
    unsigned int a;
    unsigned int b;
    for(b = 0;b<i;b++)
    	for(a = 0;a<1000;a++);

}
*/

/*********************************************************************
* Function:  SetScrollArea(SHORT top, SHORT scroll, SHORT bottom)
*
* PreCondition: none
*
* Input: top - Top Fixed Area in number of lines from the top
*				of the frame buffer
*		 scroll - Vertical scrolling area in number of lines
*		 bottom - Bottom Fixed Area in number of lines
*
* Output: none
*
* Side Effects: none
*
* Overview:
*
* Note: Reference: section 9.22 Set Scroll Area, SSD1963 datasheet Rev0.20
********************************************************************/
void SetScrollArea(unsigned int top, unsigned int scroll, unsigned int bottom)
{


//	WriteCommand(CMD_SET_SCROLL_AREA);
//	CS_LAT_BIT  =  0;
	LCD_WR_REG(0x33);
	LCD_WR_Data(top>>8);
	LCD_WR_Data(top);
	LCD_WR_Data(scroll>>8);
	LCD_WR_Data(scroll);
	LCD_WR_Data(bottom>>8);
	LCD_WR_Data(bottom);
//	CS_LAT_BIT  =  1;	
}

/*********************************************************************
* Function:  void  SetScrollStart(SHORT line)
*
* Overview: First, we need to define the scrolling area by SetScrollArea()
*			before using this function. 
*
* PreCondition: SetScrollArea(SHORT top, SHORT scroll, SHORT bottom)
*
* Input: line - Vertical scrolling pointer (in number of lines) as 
*		 the first display line from the Top Fixed Area defined in SetScrollArea()
*
* Output: none
*
* Note: Example -
*
*		SHORT line = 0;
*		SetScrollArea(0,272,0);
*		for(line = 0;line<272;line++) {SetScrollStart(line);DelayMs(100);}
*		
*		Code above scrolls the whole page upwards in 100ms interval 
*		with page 2 replacing the first page in scrolling
********************************************************************/
void SetScrollStart(unsigned int line)
{

//	LCD_WR_REG(0x002A);	
//    LCD_WR_Data(0);	  
//	LCD_WR_REG(CMD_SET_SCROLL_START);
	LCD_WR_REG(0x37);
//	CS_LAT_BIT  =  0;
	LCD_WR_Data(line>>8);
	LCD_WR_Data(line);	
//	CS_LAT_BIT  =  1;
}

/*********************************************************************
* Function:  void  SetTearingCfg(BOOL state, BOOL mode)
*
* Overview: This function enable/disable tearing effect
*
* PreCondition: none
*
* Input: 	BOOL state -	1 to enable
*							0 to disable
*			BOOL mode -		0:  the tearing effect output line consists
*								of V-blanking information only
*							1:	the tearing effect output line consists
*								of both V-blanking and H-blanking info.
* Output: none
*
* Note:
********************************************************************/
void SetTearingCfg(unsigned char state, unsigned char mode)
{


	if(state  == 1)
	{
		LCD_WR_REG(0x35);
		//CS_LAT_BIT  =  0;
		LCD_WR_Data(mode&0x01);
		//CS_LAT_BIT  =  1;
	}
	else
	{
		LCD_WR_REG(0x34);
	}


}



#if 0
typedef struct
{
  __IO uint16_t LCD_REG;
  __IO uint16_t LCD_RAM;
} LCD_TypeDef;

/* Note: LCD /CS is CE1 - Bank 1 of NOR/SRAM Bank 1~4 */
#define LCD_BASE           ((uint32_t)(0x60000000 | 0x00000000))
#define LCD                ((LCD_TypeDef *) LCD_BASE)

#define MAX_POLY_CORNERS   200
#define POLY_Y(Z)          ((int32_t)((Points + Z)->X))
#define POLY_X(Z)          ((int32_t)((Points + Z)->Y))                                
#define ABS(X)  ((X) > 0 ? (X) : -(X))    

static sFONT *LCD_Currentfonts;
/* Global variables to set the written text color */
static  __IO uint16_t TextColor = 0x0000, BackColor = 0xFFFF;
static void PutPixel(int16_t x, int16_t y);
static void LCD_PolyLineRelativeClosed(pPoint Points, uint16_t PointCount, uint16_t Closed);


/**
  * @brief  Sets the Text Font.
  * @param  fonts: specifies the font to be used.
  * @retval None
  */
void LCD_SetFont(sFONT *fonts)
{
  LCD_Currentfonts = fonts;
}

/**
  * @brief  Gets the Text Font.
  * @param  None.
  * @retval the used font.
  */
sFONT *LCD_GetFont(void)
{
  return LCD_Currentfonts;
}

/**
  * @brief  Clears the selected line.
  * @param  Line: the Line to be cleared.
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..n
  * @retval None
  */
void LCD_ClearLine(uint8_t Line)
{
  uint16_t refcolumn = LCD_PIXEL_WIDTH - 1;
  /* Send the string character by character on lCD */
  while (((refcolumn + 1)&0xFFFF) >= LCD_Currentfonts->Width)
  {
    /* Display one character on LCD */
    LCD_DisplayChar(Line, refcolumn, ' ');
    /* Decrement the column position by 16 */
    refcolumn -= LCD_Currentfonts->Width;
  }
}


/**
  * @brief  Clears the hole LCD.
  * @param  Color: the color of the background.
  * @retval None
  */
void LCD_Clear(uint16_t Color)
{
  uint32_t index = 0;
  
  LCD_SetCursor(0x00, 0x013F); 
  LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
  for(index = 0; index < 76800; index++)
  {
    LCD->LCD_RAM = Color;
  }  
}


/**
  * @brief  Sets the cursor position.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position. 
  * @retval None
  */
void LCD_SetCursor(uint8_t Xpos, uint16_t Ypos)
{
  LCD_WriteReg(LCD_REG_32, Xpos);
  LCD_WriteReg(LCD_REG_33, Ypos);
}


/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: the Line where to display the character shape.
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
  * @retval None
  */
void LCD_DrawChar(uint8_t Xpos, uint16_t Ypos, const uint16_t *c)
{
  uint32_t index = 0, i = 0;
  uint8_t Xaddress = 0;
   
  Xaddress = Xpos;
  
  LCD_SetCursor(Xaddress, Ypos);
  
  for(index = 0; index < LCD_Currentfonts->Height; index++)
  {
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    for(i = 0; i < LCD_Currentfonts->Width; i++)
    {
      if((((c[index] & ((0x80 << ((LCD_Currentfonts->Width / 12 ) * 8 ) ) >> i)) == 0x00) &&(LCD_Currentfonts->Width <= 12))||
        (((c[index] & (0x1 << i)) == 0x00)&&(LCD_Currentfonts->Width > 12 )))

      {
        LCD_WriteRAM(BackColor);
      }
      else
      {
        LCD_WriteRAM(TextColor);
      }
    }
    Xaddress++;
    LCD_SetCursor(Xaddress, Ypos);
  }
}


/**
  * @brief  Displays one character (16dots width, 24dots height).
  * @param  Line: the Line where to display the character shape .
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..9
  * @param  Column: start column address.
  * @param  Ascii: character ascii code, must be between 0x20 and 0x7E.
  * @retval None
  */
void LCD_DisplayChar(uint8_t Line, uint16_t Column, uint8_t Ascii)
{
  Ascii -= 32;
  LCD_DrawChar(Line, Column, &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height]);
}


/**
  * @brief  Displays a maximum of 20 char on the LCD.
  * @param  Line: the Line where to display the character shape .
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..9
  * @param  *ptr: pointer to string to display on LCD.
  * @retval None
  */
void LCD_DisplayStringLine(uint8_t Line, uint8_t *ptr)
{
  uint16_t refcolumn = LCD_PIXEL_WIDTH - 1;

  /* Send the string character by character on lCD */
  while ((*ptr != 0) & (((refcolumn + 1) & 0xFFFF) >= LCD_Currentfonts->Width))
  {
    /* Display one character on LCD */
    LCD_DisplayChar(Line, refcolumn, *ptr);
    /* Decrement the column position by 16 */
    refcolumn -= LCD_Currentfonts->Width;
    /* Point on the next character */
    ptr++;
  }
}


/**
  * @brief  Sets a display window
  * @param  Xpos: specifies the X buttom left position.
  * @param  Ypos: specifies the Y buttom left position.
  * @param  Height: display window height.
  * @param  Width: display window width.
  * @retval None
  */
void LCD_SetDisplayWindow(uint8_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width)
{
  /* Horizontal GRAM Start Address */
  if(Xpos >= Height)
  {
    LCD_WriteReg(LCD_REG_80, (Xpos - Height + 1));
  }
  else
  {
    LCD_WriteReg(LCD_REG_80, 0);
  }
  /* Horizontal GRAM End Address */
  LCD_WriteReg(LCD_REG_81, Xpos);
  /* Vertical GRAM Start Address */
  if(Ypos >= Width)
  {
    LCD_WriteReg(LCD_REG_82, (Ypos - Width + 1));
  }  
  else
  {
    LCD_WriteReg(LCD_REG_82, 0);
  }
  /* Vertical GRAM End Address */
  LCD_WriteReg(LCD_REG_83, Ypos);
  LCD_SetCursor(Xpos, Ypos);
}


/**
  * @brief  Disables LCD Window mode.
  * @param  None
  * @retval None
  */
void LCD_WindowModeDisable(void)
{
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);
  LCD_WriteReg(LCD_REG_3, 0x1018);    
}


/**
  * @brief  Displays a line.
  * @param Xpos: specifies the X position.
  * @param Ypos: specifies the Y position.
  * @param Length: line length.
  * @param Direction: line direction.
  *   This parameter can be one of the following values: Vertical or Horizontal.
  * @retval None
  */
void LCD_DrawLine(uint8_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction)
{
  uint32_t i = 0;
  
  LCD_SetCursor(Xpos, Ypos);
  if(Direction == LCD_DIR_HORIZONTAL)
  {
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    for(i = 0; i < Length; i++)
    {
      LCD_WriteRAM(TextColor);
    }
  }
  else
  {
    for(i = 0; i < Length; i++)
    {
      LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
      LCD_WriteRAM(TextColor);
      Xpos++;
      LCD_SetCursor(Xpos, Ypos);
    }
  }
}


/**
  * @brief  Displays a rectangle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Height: display rectangle height.
  * @param  Width: display rectangle width.
  * @retval None
  */
void LCD_DrawRect(uint8_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width)
{
  LCD_DrawLine(Xpos, Ypos, Width, LCD_DIR_HORIZONTAL);
  LCD_DrawLine((Xpos + Height), Ypos, Width, LCD_DIR_HORIZONTAL);
  
  LCD_DrawLine(Xpos, Ypos, Height, LCD_DIR_VERTICAL);
  LCD_DrawLine(Xpos, (Ypos - Width + 1), Height, LCD_DIR_VERTICAL);
}


/**
  * @brief  Displays a circle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Radius
  * @retval None
  */
void LCD_DrawCircle(uint8_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;/* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
    LCD_SetCursor(Xpos + CurX, Ypos + CurY);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);
    LCD_SetCursor(Xpos + CurX, Ypos - CurY);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);
    LCD_SetCursor(Xpos - CurX, Ypos + CurY);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);
    LCD_SetCursor(Xpos - CurX, Ypos - CurY);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);
    LCD_SetCursor(Xpos + CurY, Ypos + CurX);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);
    LCD_SetCursor(Xpos + CurY, Ypos - CurX);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);
    LCD_SetCursor(Xpos - CurY, Ypos + CurX);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);
    LCD_SetCursor(Xpos - CurY, Ypos - CurX);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}


/**
  * @brief  Displays a monocolor picture.
  * @param  Pict: pointer to the picture array.
  * @retval None
  */
void LCD_DrawMonoPict(const uint32_t *Pict)
{
  uint32_t index = 0, i = 0;
  LCD_SetCursor(0, (LCD_PIXEL_WIDTH - 1));
  LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
  for(index = 0; index < 2400; index++)
  {
    for(i = 0; i < 32; i++)
    {
      if((Pict[index] & (1 << i)) == 0x00)
      {
        LCD_WriteRAM(BackColor);
      }
      else
      {
        LCD_WriteRAM(TextColor);
      }
    }
  }
}


/**
  * @brief  Displays a bitmap picture loaded in the internal Flash.
  * @param  BmpAddress: Bmp picture address in the internal Flash.
  * @retval None
  */
void LCD_WriteBMP(uint32_t BmpAddress)
{
  uint32_t index = 0, size = 0;
  /* Read bitmap size */
  size = *(__IO uint16_t *) (BmpAddress + 2);
  size |= (*(__IO uint16_t *) (BmpAddress + 4)) << 16;
  /* Get bitmap data address offset */
  index = *(__IO uint16_t *) (BmpAddress + 10);
  index |= (*(__IO uint16_t *) (BmpAddress + 12)) << 16;
  size = (size - index)/2;
  BmpAddress += index;
  /* Set GRAM write direction and BGR = 1 */
  /* I/D=00 (Horizontal : decrement, Vertical : decrement) */
  /* AM=1 (address is updated in vertical writing direction) */
  LCD_WriteReg(LCD_REG_3, 0x1008);
 
  LCD_WriteRAM_Prepare();
 
  for(index = 0; index < size; index++)
  {
    LCD_WriteRAM(*(__IO uint16_t *)BmpAddress);
    BmpAddress += 2;
  }
 
  /* Set GRAM write direction and BGR = 1 */
  /* I/D = 01 (Horizontal : increment, Vertical : decrement) */
  /* AM = 1 (address is updated in vertical writing direction) */
  LCD_WriteReg(LCD_REG_3, 0x1018);
}

/**
  * @brief  Displays a full rectangle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Height: rectangle height.
  * @param  Width: rectangle width.
  * @retval None
  */
void LCD_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  LCD_SetTextColor(TextColor);

  LCD_DrawLine(Xpos, Ypos, Width, LCD_DIR_HORIZONTAL);
  LCD_DrawLine((Xpos + Height), Ypos, Width, LCD_DIR_HORIZONTAL);
  
  LCD_DrawLine(Xpos, Ypos, Height, LCD_DIR_VERTICAL);
  LCD_DrawLine(Xpos, (Ypos - Width + 1), Height, LCD_DIR_VERTICAL);

  Width -= 2;
  Height--;
  Ypos--;

  LCD_SetTextColor(BackColor);

  while(Height--)
  {
    LCD_DrawLine(++Xpos, Ypos, Width, LCD_DIR_HORIZONTAL);    
  }

  LCD_SetTextColor(TextColor);
}

/**
  * @brief  Displays a full circle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Radius
  * @retval None
  */
void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;    /* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  
  D = 3 - (Radius << 1);

  CurX = 0;
  CurY = Radius;
  
  LCD_SetTextColor(BackColor);

  while (CurX <= CurY)
  {
    if(CurY > 0) 
    {
      LCD_DrawLine(Xpos - CurX, Ypos + CurY, 2*CurY, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(Xpos + CurX, Ypos + CurY, 2*CurY, LCD_DIR_HORIZONTAL);
    }

    if(CurX > 0) 
    {
      LCD_DrawLine(Xpos - CurY, Ypos + CurX, 2*CurX, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(Xpos + CurY, Ypos + CurX, 2*CurX, LCD_DIR_HORIZONTAL);
    }
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }

  LCD_SetTextColor(TextColor);
  LCD_DrawCircle(Xpos, Ypos, Radius);
}


/**
  * @brief  Displays an polyline (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_PolyLine(pPoint Points, uint16_t PointCount)
{
  int16_t X = 0, Y = 0;

  if(PointCount < 2)
  {
    return;
  }

  while(--PointCount)
  {
    X = Points->X;
    Y = Points->Y;
    Points++;
    LCD_DrawUniLine(X, Y, Points->X, Points->Y);
  }
}

/**
  * @brief  Displays an relative polyline (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @param  Closed: specifies if the draw is closed or not.
  *           1: closed, 0 : not closed.
  * @retval None
  */
static void LCD_PolyLineRelativeClosed(pPoint Points, uint16_t PointCount, uint16_t Closed)
{
  int16_t X = 0, Y = 0;
  pPoint First = Points;

  if(PointCount < 2)
  {
    return;
  }  
  X = Points->X;
  Y = Points->Y;
  while(--PointCount)
  {
    Points++;
    LCD_DrawUniLine(X, Y, X + Points->X, Y + Points->Y);
    X = X + Points->X;
    Y = Y + Points->Y;
  }
  if(Closed)
  {
    LCD_DrawUniLine(First->X, First->Y, X, Y);
  }  
}

/**
  * @brief  Displays a closed polyline (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_ClosedPolyLine(pPoint Points, uint16_t PointCount)
{
  LCD_PolyLine(Points, PointCount);
  LCD_DrawUniLine(Points->X, Points->Y, (Points+PointCount-1)->X, (Points+PointCount-1)->Y);
}

/**
  * @brief  Displays a relative polyline (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_PolyLineRelative(pPoint Points, uint16_t PointCount)
{
  LCD_PolyLineRelativeClosed(Points, PointCount, 0);
}

/**
  * @brief  Displays a closed relative polyline (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_ClosedPolyLineRelative(pPoint Points, uint16_t PointCount)
{
  LCD_PolyLineRelativeClosed(Points, PointCount, 1);
}


/**
  * @brief  Displays a  full polyline (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_FillPolyLine(pPoint Points, uint16_t PointCount)
{
  /*  public-domain code by Darel Rex Finley, 2007 */
  uint16_t  nodes = 0, nodeX[MAX_POLY_CORNERS], pixelX = 0, pixelY = 0, i = 0,
  j = 0, swap = 0;
  uint16_t  IMAGE_LEFT = 0, IMAGE_RIGHT = 0, IMAGE_TOP = 0, IMAGE_BOTTOM = 0;

  IMAGE_LEFT = IMAGE_RIGHT = Points->X;
  IMAGE_TOP= IMAGE_BOTTOM = Points->Y;

  for(i = 1; i < PointCount; i++)
  {
    pixelX = POLY_X(i);
    if(pixelX < IMAGE_LEFT)
    {
      IMAGE_LEFT = pixelX;
    }
    if(pixelX > IMAGE_RIGHT)
    {
      IMAGE_RIGHT = pixelX;
    }
    
    pixelY = POLY_Y(i);
    if(pixelY < IMAGE_TOP)
    { 
      IMAGE_TOP = pixelY;
    }
    if(pixelY > IMAGE_BOTTOM)
    {
      IMAGE_BOTTOM = pixelY;
    }
  }
  
  LCD_SetTextColor(BackColor);  

  /*  Loop through the rows of the image. */
  for (pixelY = IMAGE_TOP; pixelY < IMAGE_BOTTOM; pixelY++) 
  {  
    /* Build a list of nodes. */
    nodes = 0; j = PointCount-1;

    for (i = 0; i < PointCount; i++) 
    {
      if (POLY_Y(i)<(double) pixelY && POLY_Y(j)>=(double) pixelY || POLY_Y(j)<(double) pixelY && POLY_Y(i)>=(double) pixelY) 
      {
        nodeX[nodes++]=(int) (POLY_X(i)+((pixelY-POLY_Y(i))*(POLY_X(j)-POLY_X(i)))/(POLY_Y(j)-POLY_Y(i))); 
      }
      j = i; 
    }
  
    /* Sort the nodes, via a simple "Bubble" sort. */
    i = 0;
    while (i < nodes-1) 
    {
      if (nodeX[i]>nodeX[i+1]) 
      {
        swap = nodeX[i]; 
        nodeX[i] = nodeX[i+1]; 
        nodeX[i+1] = swap; 
        if(i)
        {
          i--; 
        }
      }
      else 
      {
        i++;
      }
    }
  
    /*  Fill the pixels between node pairs. */
    for (i = 0; i < nodes; i+=2) 
    {
      if(nodeX[i] >= IMAGE_RIGHT) 
      {
        break;
      }
      if(nodeX[i+1] > IMAGE_LEFT) 
      {
        if (nodeX[i] < IMAGE_LEFT)
        {
          nodeX[i]=IMAGE_LEFT;
        }
        if(nodeX[i+1] > IMAGE_RIGHT)
        {
          nodeX[i+1] = IMAGE_RIGHT;
        }
        LCD_SetTextColor(BackColor);
        LCD_DrawLine(pixelY, nodeX[i+1], nodeX[i+1] - nodeX[i], LCD_DIR_HORIZONTAL);
        LCD_SetTextColor(TextColor);
        PutPixel(pixelY, nodeX[i+1]);
        PutPixel(pixelY, nodeX[i]);
        /* for (j=nodeX[i]; j<nodeX[i+1]; j++) PutPixel(j,pixelY); */
      }
    }
  } 

  /* draw the edges */
  LCD_SetTextColor(TextColor);
}


/**
  * @brief  Displays a pixel.
  * @param  x: pixel x.
  * @param  y: pixel y.  
  * @retval None
  */
static void PutPixel(int16_t x, int16_t y)
{ 
  if(x < 0 || x > 239 || y < 0 || y > 319)
  {
    return;  
  }
  LCD_DrawLine(x, y, 1, LCD_DIR_HORIZONTAL);
}

#endif

/*****END OF FILE****/
