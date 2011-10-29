/*******************************************************************************
 *
 * @brief	Graphic routines here all assume that the coordinate of upper left 
 *			corner of the screen is (0,0), x value increases as it goes right, 
 *			and y value increases as it goes down.
 */ 

#include "miniSTM32.h"
#include "miniSTM32_lcd.h"

/* display contrller and backlight control method */
#if defined(LCD_QD024CPS25)
	#define ILI9325
	#define MCU_BLTCONTROL
#elif (defined(LCD_HSD043I9W) || defined(LCD_AT043TN13))
	#define SSD1963
	#define MCU_BLTCONTROL
#elif defined(LCD_AT070TN83)
	#define SSD1963
	#define CTR_BLTCONTROL
#endif

/* MCU backlight control port */
#define BLTCONTROL_PORT				GPIOD
#define BLTCONTROL_PIN				GPIO_Pin_13


/* FSMC use NOR(BANK1) interface with A16 as RS 
 *
 * For SSD1963
 * RS(A16) = 0 : register (8bit)
 * RS(A16) = 1 : data (16bit)
 *
 * For ILI9325
 * RS(A16) = 0: write index, read status
 * RS(A16) = 1: write control register or data, read data
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

/* SSD ILI9325 Command Code */
#define CTR_OSC_START			0x0000
#define CTR_DRV_OUTPUT1			0x0001
#define CTR_DRV_WAVE			0x0002
#define CTR_ENTRY_MODE			0x0003
#define CTR_RESIZE				0x0004
#define CTR_DISPLAY1			0x0007
#define CTR_DISPLAY2			0x0008
#define CTR_DISPLAY3			0x0009
#define CTR_DISPLAY4			0x000A
#define CTR_RGB_INTERFACE1		0x000C
#define CTR_FRM_MARKER			0x000D
#define CTR_RGB_INTERFACE2		0x000F
#define CTR_POWER1				0x0010
#define CTR_POWER2				0x0011
#define CTR_POWER3				0x0012
#define CTR_POWER4				0x0013
#define CTR_HORZ_ADDRESS		0x0020
#define CTR_VERT_ADDRESS		0x0021
#define CTR_WRITE_DATA			0x0022
#define CTR_READ_DATA			0x0022
#define CTR_POWER7				0x0029
#define CTR_FRM_COLOR			0x002B
#define CTR_GAMMA1				0x0030
#define CTR_GAMMA2				0x0031
#define CTR_GAMMA3				0x0032
#define CTR_GAMMA4				0x0035
#define CTR_GAMMA5				0x0036
#define CTR_GAMMA6				0x0037
#define CTR_GAMMA7				0x0038
#define CTR_GAMMA8				0x0039
#define CTR_GAMMA9				0x003C
#define CTR_GAMMA10				0x003D
#define CTR_HORZ_START			0x0050
#define CTR_HORZ_END			0x0051
#define CTR_VERT_START			0x0052
#define CTR_VERT_END			0x0053
#define CTR_DRV_OUTPUT2			0x0060
#define CTR_BASE_IMAGE			0x0061
#define CTR_VERT_SCROLL			0x006A
#define CTR_PIMG1_POS			0x0080
#define CTR_PIMG1_START			0x0081
#define CTR_PIMG1_END			0x0082
#define CTR_PIMG2_POS			0x0083
#define CTR_PIMG2_START			0x0084
#define CTR_PIMG2_END			0x0085
#define CTR_PANEL_INTERFACE1	0x0090
#define CTR_PANEL_INTERFACE2	0x0092
#define CTR_PANEL_INTERFACE4	0x0095
#define CTR_OTP_VCMPROGRAM		0x00A1
#define CTR_OTP_VCMSTATUS		0x00A2
#define CTR_OTP_IDKEY			0x00A5

#define CTR_UNDOCUMENTED_93		0x0093
#define CTR_UNDOCUMENTED_97		0x0097
#define CTR_UNDOCUMENTED_98		0x0098
#define CTR_UNDOCUMENTED_E3		0x00E3
#define CTR_UNDOCUMENTED_E7		0x00E7
#define CTR_UNDOCUMENTED_EF		0x00EF


/* LCD delay routine : 1 msec interval */
#define LCD_DELAY(x)			do{uLCD_Delay = x; while( uLCD_Delay);} while(0)
#define ABS(x)					((x) > 0 ? (x) : -(x))    
#define INTSWAP(x,y)			do{x ^= y; y ^= x; x ^= y;} while(0)

volatile LCDCOLOR col_fgnd = LCD_COLOR_WHITE;
volatile LCDCOLOR col_bgnd = LCD_COLOR_BLACK;
volatile uint16_t uPenWidth = 1;
volatile uint16_t uLCD_Delay = 0;
static LCDFONT *sLCDFont;


/* register control functions */
inline void LCD_WR_Control(uint16_t command);
inline void LCD_WR_Data(uint16_t val);
inline void LCD_WR_CtrData(uint16_t index, uint16_t data);

uint16_t LCD_RD_Control(uint16_t command);
uint16_t LCD_RD_Data(void);
void LCD_SetColumnPageAddr(int16_t colS, int16_t colE, int16_t pagS, int16_t pagE);

/* functions not used for now */
void LCD_SetScrollArea(uint16_t top, uint16_t scroll, uint16_t bottom);
void LCD_SetScrollStart(uint16_t line);
void LCD_SetTearingCfg(unsigned char state, unsigned char mode);


inline void LCD_WR_Control(uint16_t command)
{
	*(__IO uint16_t *) (Bank1_LCD_Ctrl) =  command;
}

inline void LCD_WR_Data(uint16_t val)
{   
	*(__IO uint16_t *) (Bank1_LCD_Data) =  val; 	
}

inline void LCD_WR_CtrData(uint16_t index, uint16_t data)
{
	*(__IO uint16_t *) (Bank1_LCD_Ctrl) =  index;
	*(__IO uint16_t *) (Bank1_LCD_Data) =  data; 	
}

uint16_t LCD_RD_Control(uint16_t command)
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


void LCD_SetColumnPageAddr(int16_t colS, int16_t colE, int16_t pagS, int16_t pagE)
{

#if defined(ILI9325)

	/* Note that this does not work if some conditions are not met */
	LCD_WR_CtrData(CTR_HORZ_START, colS);
	LCD_WR_CtrData(CTR_HORZ_END, colE);
	LCD_WR_CtrData(CTR_VERT_START, pagS);
	LCD_WR_CtrData(CTR_VERT_END, pagE);

	/* place the cursor at the starting point */
	LCD_WR_CtrData(CTR_HORZ_ADDRESS, colS);
	LCD_WR_CtrData(CTR_VERT_ADDRESS, pagS);

#elif defined(SSD1963)

	/* set column address */
	LCD_WR_Control(CMD_SET_COL_ADDRESS);
	/* start column */
	LCD_WR_Data(colS >> 8);
	LCD_WR_Data(colS & 0x00ff);
	/* end column */
	LCD_WR_Data(colE >> 8);
	LCD_WR_Data(colE & 0x00ff);

	/* set page address */
    LCD_WR_Control(CMD_SET_PAGE_ADDRESS);
	/* start page */
	LCD_WR_Data(pagS >> 8);
	LCD_WR_Data(pagS & 0x00ff);
	/* end page */
	LCD_WR_Data(pagE >> 8); 
	LCD_WR_Data(pagE & 0x00ff);

#endif

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

#if defined(ILI9325)
	/* LPL 2.4inch initialization code */

	/* initial hard reset: PE1 */
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);
	LCD_DELAY(10);

	GPIO_SetBits(GPIOE, GPIO_Pin_1);
	LCD_DELAY(50);

	/* initial sequence */
	//LCD_WR_CtrData(CTR_UNDOCUMENTED_E3, 0x3008);
	//LCD_WR_CtrData(CTR_UNDOCUMENTED_E7, 0x0012);
	//LCD_WR_CtrData(CTR_UNDOCUMENTED_EF, 0x1231);

	LCD_WR_CtrData(CTR_OSC_START, 0x0001);
	LCD_WR_CtrData(CTR_DRV_OUTPUT1, 0x0100);
	LCD_WR_CtrData(CTR_DRV_WAVE, 0x0700);
	LCD_WR_CtrData(CTR_ENTRY_MODE, 0x1030);
	LCD_WR_CtrData(CTR_RESIZE, 0x0000);
	LCD_WR_CtrData(CTR_DISPLAY2, 0x0207);
	LCD_WR_CtrData(CTR_DISPLAY3, 0x0000);
	LCD_WR_CtrData(CTR_DISPLAY4, 0x0000);
	LCD_WR_CtrData(CTR_RGB_INTERFACE1, 0x0001);
	LCD_WR_CtrData(CTR_FRM_MARKER, 0x0000);
	LCD_WR_CtrData(CTR_RGB_INTERFACE2, 0x0000);

	/* power on sequence */
	LCD_WR_CtrData(CTR_POWER1, 0x0000);
	LCD_WR_CtrData(CTR_POWER2, 0x0007);
	LCD_WR_CtrData(CTR_POWER3, 0x0000);
	LCD_WR_CtrData(CTR_POWER4, 0x0000);

	LCD_DELAY(200);
	LCD_WR_CtrData(CTR_POWER1, 0x1590);		/* SAP, BT, AP, DSTB, SLP, STB */
	LCD_WR_CtrData(CTR_POWER2, 0x0227);		/* DC, VC */

	LCD_DELAY(50);
	LCD_WR_CtrData(CTR_POWER3, 0x009C);		/* internal voltage reference */
	
	LCD_DELAY(50);
	LCD_WR_CtrData(CTR_POWER4, 0x1900);		/* VDV */
	LCD_WR_CtrData(CTR_POWER7, 0x1900);		/* VCM */
	LCD_WR_CtrData(CTR_FRM_COLOR, 0x000E);	/* frame rate */

	LCD_DELAY(50);
	LCD_WR_CtrData(CTR_HORZ_ADDRESS, 0x0000);
	LCD_WR_CtrData(CTR_VERT_ADDRESS, 0x0000);

	/* gamma curve */
	LCD_WR_CtrData(CTR_GAMMA1, 0x0007);
	LCD_WR_CtrData(CTR_GAMMA3, 0x0707);
	LCD_WR_CtrData(CTR_GAMMA3, 0x0006);
	LCD_WR_CtrData(CTR_GAMMA4, 0x0704);
	LCD_WR_CtrData(CTR_GAMMA5, 0x1F04);
	LCD_WR_CtrData(CTR_GAMMA6, 0x0004);
	LCD_WR_CtrData(CTR_GAMMA7, 0x0000);
	LCD_WR_CtrData(CTR_GAMMA8, 0x0706);
	LCD_WR_CtrData(CTR_GAMMA9, 0x0701);
	LCD_WR_CtrData(CTR_GAMMA10, 0x000F);

	/* GRAM */
	LCD_WR_CtrData(CTR_HORZ_START, 0x0000);
	LCD_WR_CtrData(CTR_HORZ_END, 0x00EF);
	LCD_WR_CtrData(CTR_VERT_START, 0x0000);
	LCD_WR_CtrData(CTR_VERT_END, 0x013F);
	LCD_WR_CtrData(CTR_DRV_OUTPUT2, 0xA700);
	LCD_WR_CtrData(CTR_BASE_IMAGE, 0x0001);
	LCD_WR_CtrData(CTR_VERT_SCROLL, 0x0000);

	/* partial display */
	LCD_WR_CtrData(CTR_PIMG1_POS, 0x0000);
	LCD_WR_CtrData(CTR_PIMG1_START, 0x0000);
	LCD_WR_CtrData(CTR_PIMG1_END, 0x0000);
	LCD_WR_CtrData(CTR_PIMG2_POS, 0x0000);
	LCD_WR_CtrData(CTR_PIMG2_START, 0x0000);
	LCD_WR_CtrData(CTR_PIMG2_END, 0x0000);

	/* panel */
	LCD_WR_CtrData(CTR_PANEL_INTERFACE1, 0x0010);
	LCD_WR_CtrData(CTR_PANEL_INTERFACE2, 0x0000);
	LCD_WR_CtrData(CTR_PANEL_INTERFACE4, 0x0110);

	LCD_WR_CtrData(CTR_UNDOCUMENTED_93, 0x0003);
	LCD_WR_CtrData(CTR_UNDOCUMENTED_97, 0x0000);
	LCD_WR_CtrData(CTR_UNDOCUMENTED_98, 0x0000);

#elif defined(SSD1963)

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
	LCD_WR_Control(CMD_SET_PLL_MN);
	LCD_WR_Data(0x0020);
	LCD_WR_Data(0x0002);
	LCD_WR_Data(CMD_DUMMY);
	
	/* enable pll */
	LCD_WR_Control(CMD_SET_PLL);
	LCD_WR_Data(0x0001);

	/* 100 usec delay for locking */
	LCD_DELAY(1);

	/* activate pll output */
	LCD_WR_Control(CMD_SET_PLL);
	LCD_WR_Data(0x0003); 

	LCD_DELAY(1);

	/* soft reset */
	LCD_WR_Control(CMD_SOFT_RESET);

	LCD_DELAY(1);

	/* set tear off */
	/* set gpio configuration */
	/* set post processing */

	/* pixel data interface (host) */
	LCD_WR_Control(CMD_SET_PIXDATA_IF_FMT);
	LCD_WR_Data(0x0003);	/* 16bit 565 */

#if defined(LCD_HSD043I9W)
	
	/* HannStar HSD043I9W */

	/* set pixel clock frequency
	 * pll frequency	: 110MHz
	 * target frequency : 9MHz
	 * LCDC_FPR			: 85793 (0x014F21)
	 */
	LCD_WR_Control(CMD_SET_PIXCLK_FREQ);
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
	LCD_WR_Control(CMD_SET_LCD_MODE);
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
	LCD_WR_Control(CMD_SET_HORIZ_PERIOD);
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
	LCD_WR_Control(CMD_SET_VERT_PERIOD);
	LCD_WR_Data(0x02);
	LCD_WR_Data(0x0C);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x0C);
	LCD_WR_Data(0x09);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x00);

	/* set address mode 
	 * flip vertical, flip horizontal
	 */
	LCD_WR_Control(CMD_SET_ADDRESS_MODE);
	LCD_WR_Data(0x03);

#elif defined(LCD_AT043TN13)

	/* Innolux AT043TN13 */

	/* set pixel clock frequency
	 * pll frequency	: 110MHz
	 * target frequency : 9MHz
	 * LCDC_FPR			: 85793 (0x014F21)
	 */
	LCD_WR_Control(CMD_SET_PIXCLK_FREQ);
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
	LCD_WR_Control(CMD_SET_LCD_MODE);
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
	LCD_WR_Control(CMD_SET_HORIZ_PERIOD);
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
	LCD_WR_Control(CMD_SET_VERT_PERIOD);
	LCD_WR_Data(0x02);
	LCD_WR_Data(0x0A);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x0C);
	LCD_WR_Data(0x09);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x00);

	/* set address mode 
	 * flip vertical, flip horizontal
	 */
	LCD_WR_Control(CMD_SET_ADDRESS_MODE);
	LCD_WR_Data(0x03);

#elif defined(LCD_AT070TN83)

	/* Innolux AT070TN83 */

	/* set pixel clock frequency
	 * pll frequency	: 110MHz
	 * target frequency : 33.3MHz
	 * LCDC_FPR			: 317433 (0x04D7F9)
	 */
	LCD_WR_Control(CMD_SET_PIXCLK_FREQ);
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
	LCD_WR_Control(CMD_SET_LCD_MODE);
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
	LCD_WR_Control(CMD_SET_HORIZ_PERIOD);
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
	LCD_WR_Control(CMD_SET_VERT_PERIOD);
	LCD_WR_Data(0x02);
	LCD_WR_Data(0x0C);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x10);
	LCD_WR_Data(0x02);
	LCD_WR_Data(0x00);
	LCD_WR_Data(0x00);

	/* set address mode */
	LCD_WR_Control(CMD_SET_ADDRESS_MODE);
	LCD_WR_Data(0x00);

#endif /* LCD_AT070TN83 */

#endif /* SSD_1963, ILI9325 */

	/* clear lcd */
	LCD_Clear(LCD_COLOR_BLACK);
}

void LCD_BacklightOn(void)
{

#if defined(MCU_BLTCONTROL)

	GPIO_SetBits(BLTCONTROL_PORT, BLTCONTROL_PIN);

#elif defined(CTR_BLTCONTROL)

	/* pwm configuration (300Hz, 100%)
	 * P1(0x06) : PWMF - PWM frequency in system clock : 6 (0x06)
	 * P2(0xFF) : PWM - PWM duty cycle : 255 (0xFF)
	 * P3(0x01) : PWM enabled, control by host : (0x01)
	 * P4(0x00) : DBC manual brightness : (0x00)
	 * P5(0x00) : DBC minimum brightness : (0x00)
	 * p6(0x00) : brightness prescaler : (0x00)
	 */

	LCD_WR_Control(CMD_SET_PWM_CONF);
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

#elif defined(CTR_BLTCONTROL)

	/* pwm configuration (300Hz, 100%)
	 * P1(0x00) : PWMF - PWM frequency in system clock : 0 (0x00)
	 * P2(0x00) : PWM - PWM duty cycle : 0 (0x00)
	 * P3(0x00) : PWM disabled, control by host : (0x01)
	 * P4(0x00) : DBC manual brightness : (0x00)
	 * P5(0x00) : DBC minimum brightness : (0x00)
	 * p6(0x00) : brightness prescaler : (0x00)
	 */

	LCD_WR_Control(CMD_SET_PWM_CONF); //set PWM for Backlight. Manual p.53
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

#if defined(ILI9325)
	LCD_WR_Control(CTR_WRITE_DATA);
#elif defined(SSD1963)
	LCD_WR_Control(CMD_WRITE_MEM_START);
#endif

	while( index < (LCD_WIDTH * LCD_HEIGHT) )
	{
		LCD_WR_Data(col);
		index++;
	}

}

void LCD_DisplayOn(void)
{
#if defined(ILI9325)
	LCD_WR_CtrData(CTR_DISPLAY1, 0x0133);
#elif defined(SSD1963)
	LCD_WR_Control(CMD_SET_DISPLAY_ON);
#endif
}

void LCD_DisplayOff(void)
{
#if defined(ILI9325)
	LCD_WR_CtrData(CTR_DISPLAY1, 0x0131);
#elif defined(SSD1963)
	LCD_WR_Control(CMD_SET_DISPLAY_OFF);
#endif
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
#if defined(ILI9325)
	LCD_WR_CtrData(CTR_HORZ_ADDRESS, x);
	LCD_WR_CtrData(CTR_VERT_ADDRESS, y);
	LCD_WR_CtrData(CTR_WRITE_DATA, col_fgnd);
#elif defined(SSD1963)
	LCD_SetColumnPageAddr(x, x, y, y);
	LCD_WR_CtrData(CMD_WRITE_MEM_START, col_fgnd);
#endif
}

/**
 * @brief	Line drawing routine based on line segment(660 msec for 640 calls).
 * @param	x1: specifies the point 1 x position.
 * @param	y1: specifies the point 1 y position.
 * @param	x2: specifies the point 2 x position.
 * @param	y2: specifies the point 2 y position.
 * @retval	None
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

void LCD_DrawRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	int16_t del = (uPenWidth)>>1;

	/* this will fix one pixel misalignment at the corner */
	if( uPenWidth & 0x1 )
	{
		LCD_DrawLine(x1, y1, x2 + del, y1);
		LCD_DrawLine(x2, y1, x2, y2 + del);
	}
	else
	{
		LCD_DrawLine(x1, y1, x2 + del - 1, y1);
		LCD_DrawLine(x2, y1, x2, y2 + del - 1);
	}
	LCD_DrawLine(x2, y2, x1 - del, y2);
	LCD_DrawLine(x1, y2, x1, y1 - del);
}

void LCD_DrawFillRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	int16_t ref_x;

#if defined(ILI9325)

	/* Due to the restriction of ILI9325, pixel by pixel drawing
	 * is required here
	 */
	int16_t ref_y;

	if(x1 > x2) INTSWAP(x1, x2);
	if(y1 > y2) INTSWAP(y1, y2);

	ref_x = x1;

	while(ref_x <= x2)
	{
		ref_y = y1;

		while(ref_y <= y2)
		{
			LCD_DrawPixel(ref_x, ref_y);
			ref_y++;
		}

		ref_x++;
	}

#elif defined(SSD1963)

	LCD_SetColumnPageAddr(x1, x2, y1, y2);
	LCD_WR_Control(CMD_WRITE_MEM_START);

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

#endif 

}

/**
 * @brief	Circle drawing routine.
 * @param	x: specifies the x position of the center.
 * @param	y: specifies the y position of the center.
 * @param	r: specifies the radius of the circle.
 * @retval	None
 */

/*
 * Mid point algorithm
 */
void LCD_DrawCircle(int16_t x, int16_t y, int16_t r)
{
	int16_t dx = 0, dy = r;
	int16_t p = 1 - r;
	int16_t dr0 = (uPenWidth)>>1;
	int16_t dr1 = (uPenWidth - 1)>>1;

	/* one pixel overlap will remove the speckles at 45 degrees */
	while(dx <= dy)
	{
		/* vertical rectangles */
		/* 4th octant */
		LCD_DrawFillRect(x + dx, y + dy - dr0, x + dx, y + dy + dr1);
		/* 5th octant */
		LCD_DrawFillRect(x - dx, y + dy - dr0, x - dx, y + dy + dr1);
		/* 1th octant */
		LCD_DrawFillRect(x + dx, y - dy - dr0, x + dx, y - dy + dr1);
		/* 8th octant */
		LCD_DrawFillRect(x - dx, y - dy - dr0, x - dx, y - dy + dr1);

		/* horizontal rectangles */
		/* 3th octant */
		LCD_DrawFillRect(x + dy - dr0, y + dx, x + dy + dr1, y + dx);
		/* 6th octant */
		LCD_DrawFillRect(x - dy - dr0, y + dx, x - dy + dr1, y + dx);
		/* 2th octant */ 
		LCD_DrawFillRect(x + dy - dr0, y - dx, x + dy + dr1, y - dx);
		/* 7th octant */
		LCD_DrawFillRect(x - dy - dr0, y - dx, x - dy + dr1, y - dx);

		dx++;

		if(p < 0)
			p = p + (dx<<1) + 1;
		else
		{
			dy--;
			p = p + ((dx-dy)<<1) + 1;
		}

		LCD_DrawFillRect(x + dx, y + dy - dr0, x + dx, y + dy + dr1);
		LCD_DrawFillRect(x - dx, y + dy - dr0, x - dx, y + dy + dr1);
		LCD_DrawFillRect(x + dx, y - dy - dr0, x + dx, y - dy + dr1);
		LCD_DrawFillRect(x - dx, y - dy - dr0, x - dx, y - dy + dr1);

		LCD_DrawFillRect(x + dy - dr0, y + dx, x + dy + dr1, y + dx);
		LCD_DrawFillRect(x - dy - dr0, y + dx, x - dy + dr1, y + dx);
		LCD_DrawFillRect(x + dy - dr0, y - dx, x + dy + dr1, y - dx);
		LCD_DrawFillRect(x - dy - dr0, y - dx, x - dy + dr1, y - dx);
	}


#if 0
	/* save the original code for future reference */
	int16_t dx = 0, dy = r;
	int16_t p = 1 - r;

	while(dx < dy)
	{
		LCD_DrawPixel(x + dx, y + dy);
		LCD_DrawPixel(x - dx, y + dy);
		LCD_DrawPixel(x + dx, y - dy);
		LCD_DrawPixel(x - dx, y - dy);

		LCD_DrawPixel(x + dy, y + dx);
		LCD_DrawPixel(x - dy, y + dx);
		LCD_DrawPixel(x + dy, y - dx);
		LCD_DrawPixel(x - dy, y - dx);

		dx++;
		if(p < 0)
			p = p + (dx<<1) + 1;
		else
		{
			dy--;
			p = p + ((dx-dy)<<1) + 1;
		}

		LCD_DrawPixel(x + dx, y + dy);
		LCD_DrawPixel(x - dx, y + dy);
		LCD_DrawPixel(x + dx, y - dy);
		LCD_DrawPixel(x - dx, y - dy);

		LCD_DrawPixel(x + dy, y + dx);
		LCD_DrawPixel(x - dy, y + dx);
		LCD_DrawPixel(x + dy, y - dx);
		LCD_DrawPixel(x - dy, y - dx);
	}
#endif
}


void LCD_DrawFillCircle(int16_t x, int16_t y, int16_t r)
{
	int16_t dx = 0, dy = r;
	int16_t p = 1 - r;

	while(dx < dy)
	{
		/* vertical filling */

		/* from 1th to 4th octant */
		LCD_DrawFillRect(x + dx, y - dy, x + dx, y + dy);
		/* from 8th to 5th octant */
		LCD_DrawFillRect(x - dx, y - dy, x - dx, y + dy);

		/* from 2th to 3th octant */
		LCD_DrawFillRect(x + dy, y - dx, x + dy, y + dx);
		/* from 7th to 6th octant */
		LCD_DrawFillRect(x - dy, y - dx, x - dy, y + dx);

		dx++;
		if(p < 0)
			p = p + (dx<<1) + 1;
		else
		{
			dy--;
			p = p + ((dx-dy)<<1) + 1;
		}

		LCD_DrawFillRect(x + dx, y - dy, x + dx, y + dy);
		LCD_DrawFillRect(x - dx, y - dy, x - dx, y + dy);

		LCD_DrawFillRect(x + dy, y - dx, x + dy, y + dx);
		LCD_DrawFillRect(x - dy, y - dx, x - dy, y + dx);
	}
}


#if 0
/*
 * Second version of Bresenham algorithm
 * no noticable advantages over mid point algorithm
 */
void LCD_DrawCircleB(int16_t x, int16_t y, int16_t r)
{
	int16_t dx = 0, dy = r;
	int16_t d = 3 - (r<<1);

	while(dx < dy)
	{
		LCD_DrawPixel(x + dx, y + dy);
		LCD_DrawPixel(x - dx, y + dy);
		LCD_DrawPixel(x + dx, y - dy);
		LCD_DrawPixel(x - dx, y - dy);

		LCD_DrawPixel(x + dy, y + dx);
		LCD_DrawPixel(x - dy, y + dx);
		LCD_DrawPixel(x + dy, y - dx);
		LCD_DrawPixel(x - dy, y - dx);

		dx++;

		if(d < 0)
			d = d + (dx<<2) + 6;
		else
		{
			dy--;
			d = d + ((dx-dy)<<2) + 10;
		}

		LCD_DrawPixel(x + dx, y + dy);
		LCD_DrawPixel(x - dx, y + dy);
		LCD_DrawPixel(x + dx, y - dy);
		LCD_DrawPixel(x - dx, y - dy);

		LCD_DrawPixel(x + dy, y + dx);
		LCD_DrawPixel(x - dy, y + dx);
		LCD_DrawPixel(x + dy, y - dx);
		LCD_DrawPixel(x - dy, y - dx);
	}
}


#endif

/**
 * @brief	Ellipse drawing routine.
 * @param	x1: specifies the point 1 x position.
 * @param	y1: specifies the point 1 y position.
 * @param	x2: specifies the point 2 x position.
 * @param	y2: specifies the point 2 y position.
 * @retval	None
 */
void LCD_DrawEllipse(int16_t x, int16_t y, int16_t rx, int16_t ry)
{

	int32_t sx = rx * rx;
	int32_t sy = ry * ry;

	int32_t dx = 0, dy = ry, p;
	int32_t px = 0, py = (sx * dy)<<1;

	int32_t dr0 = (uPenWidth)>>1;
	int32_t dr1 = (uPenWidth - 1)>>1;

	/* vertical rectangles */
	/* 2nd quadrant starting point */
	LCD_DrawFillRect(x + dx, y + dy - dr0, x + dx, y + dy + dr1);
	/* 3rd quadrant starting point */
	LCD_DrawFillRect(x - dx, y + dy - dr0, x - dx, y + dy + dr1);
	/* 1st quadrant starting point */
	LCD_DrawFillRect(x + dx, y - dy - dr0, x + dx, y - dy + dr1);
	/* 4th quadrant starting point */
	LCD_DrawFillRect(x - dx, y - dy - dr0, x - dx, y - dy + dr1);

	/* region 1 */
	p = sy - (sx * ry) + (sx>>2);

	while(px < py)
	{
		dx++;
		px = px + (sy<<1);

		if(p < 0)
			p = p + sy + px;
		else
		{
			dy--;
			py = py - (sx<<1);
			p = p + sy + px - py;
		}

		/* vertical rectangles */
		/* 4th octant */
		LCD_DrawFillRect(x + dx, y + dy - dr0, x + dx, y + dy + dr1);
		/* 5th octant */
		LCD_DrawFillRect(x - dx, y + dy - dr0, x - dx, y + dy + dr1);
		/* 1st octant */
		LCD_DrawFillRect(x + dx, y - dy - dr0, x + dx, y - dy + dr1);
		/* 8th octant */
		LCD_DrawFillRect(x - dx, y - dy - dr0, x - dx, y - dy + dr1);
	}

	/* region 2 */
	p = (sy * ((dx<<1) + 1) * ((dx<<1) + 1) + sx * ((dy<<1) - 2) * ((dy<<1) - 2) 
		- ((sx * sy)<<2))>>2;

	/* WARINING: using rx as a temporary variable here */
	rx = 0;

	while(dy > 0)
	{
		dy--;
		py = py - (sx<<1);

		if(p > 0)
			p = p + sx - py;
		else
		{
			dx++;
			px = px + (sy<<1);
			p = p + sx - py + px;
		}
	
		/* horizontal rectangles */
		/* 3rd octant */
		LCD_DrawFillRect(x + dx - dr0, y + dy, x + dx + dr1, y + dy);
		/* 6th octant */
		LCD_DrawFillRect(x - dx - dr0, y + dy, x - dx + dr1, y + dy);
		/* 2nd octant */
		LCD_DrawFillRect(x + dx - dr0, y - dy, x + dx + dr1, y - dy);
		/* 7th octant */
		LCD_DrawFillRect(x - dx - dr0, y - dy, x - dx + dr1, y - dy);


		/* this part of code is for filling small gaps between two regions */
		if( rx < dr0 )
		{
			LCD_DrawFillRect(x + dx, y + dy - dr0, x + dx, y + dy + dr1);
			LCD_DrawFillRect(x - dx, y + dy - dr0, x - dx, y + dy + dr1);
			LCD_DrawFillRect(x + dx, y - dy - dr0, x + dx, y - dy + dr1);
			LCD_DrawFillRect(x - dx, y - dy - dr0, x - dx, y - dy + dr1);
			rx++;
		}
	}

#if 0
	/* save the original code for future reference */
	int32_t sx = rx * rx;
	int32_t sy = ry * ry;

	int32_t dx = 0, dy = ry, p;
	int32_t px = 0, py = (sx * dy)<<1;

	/* 2nd quadrant */
	LCD_DrawPixel(x + dx, y + dy);
	/* 3rd quadrant */
	LCD_DrawPixel(x - dx, y + dy);
	/* 1st quadrant */
	LCD_DrawPixel(x + dx, y - dy);
	/* 4th quadrant */
	LCD_DrawPixel(x - dx, y - dy);

	/* region 1 */
	p = sy - (sx * ry) + (sx>>2);

	while(px < py)
	{
		dx++;
		px = px + (sy<<1);

		if(p < 0)
			p = p + sy + px;
		else
		{
			dy--;
			py = py - (sx<<1);
			p = p + sy + px - py;
		}

		LCD_DrawPixel(x + dx, y + dy);
		LCD_DrawPixel(x - dx, y + dy);
		LCD_DrawPixel(x + dx, y - dy);
		LCD_DrawPixel(x - dx, y - dy);
	}

	/* region 2 */
	p = (sy * ((dx<<1) + 1) * ((dx<<1) + 1) + sx * ((dy<<1) - 2) * ((dy<<1) - 2) 
		- ((sx * sy)<<2))>>2;

	while(dy > 0)
	{
		dy--;
		py = py - (sx<<1);

		if(p > 0)
			p = p + sx - py;
		else
		{
			dx++;
			px = px + (sy<<1);
			p = p + sx - py + px;
		}
	
		LCD_DrawPixel(x + dx, y + dy);
		LCD_DrawPixel(x - dx, y + dy);
		LCD_DrawPixel(x + dx, y - dy);
		LCD_DrawPixel(x - dx, y - dy);
	}

#endif

}

void LCD_DrawFillEllipse(int16_t x, int16_t y, int16_t rx, int16_t ry)
{
	int32_t sx = rx * rx;
	int32_t sy = ry * ry;

	int32_t dx = 0, dy = ry, p;
	int32_t px = 0, py = (sx * dy)<<1;

	/* vertical filling */

	/* from 1st to 2nd quadrant */
	LCD_DrawFillRect(x + dx, y - dy, x + dx, y + dy);
	/* from 4th to 3rd quadrant */
	LCD_DrawFillRect(x - dx, y - dy, x - dx, y + dy);

	/* region 1 */
	p = sy - (sx * ry) + (sx>>2);

	while(px < py)
	{
		dx++;
		px = px + (sy<<1);

		if(p < 0)
			p = p + sy + px;
		else
		{
			dy--;
			py = py - (sx<<1);
			p = p + sy + px - py;
		}

		LCD_DrawFillRect(x + dx, y - dy, x + dx, y + dy);
		LCD_DrawFillRect(x - dx, y - dy, x - dx, y + dy);
	}

	/* region 2 */
	p = (sy * ((dx<<1) + 1) * ((dx<<1) + 1) + sx * ((dy<<1) - 2) * ((dy<<1) - 2) 
		- ((sx * sy)<<2))>>2;

	while(dy > 0)
	{
		dy--;
		py = py - (sx<<1);

		if(p > 0)
			p = p + sx - py;
		else
		{
			dx++;
			px = px + (sy<<1);
			p = p + sx - py + px;
		}
	
		LCD_DrawFillRect(x + dx, y - dy, x + dx, y + dy);
		LCD_DrawFillRect(x - dx, y - dy, x - dx, y + dy);
	}
}

void LCD_DrawRawImage(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t *ptr)
{
	int16_t y0 = y1;

	LCD_SetColumnPageAddr(x1, x2, y1, y2);

#if defined(ILI9325)
	LCD_WR_Control(CTR_WRITE_DATA);
#elif defined(SSD1963)
	LCD_WR_Control(CMD_WRITE_MEM_START);
#endif
	
	while(x1 <= x2)
	{
		y1 = y0;

		while(y1 <= y2)
		{
			LCD_WR_Data(*ptr++);
			y1++;
		}
		x1++;
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

#if 0
	/* Draw 640 lines with Bresenham algorithm. This is for comparision
	 * purpose only
	 */
	if(index == 0)
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
#endif

	/* 
	 * SINGLE PIXEL WIDTH LINES: 640 lines with line segment method 
	 */
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
	/* 
	 * MULTIPIXEL WIDTH LINES: 256 (thickness 5) lines 
	 */
	else if(index == 2)
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
	/* 
	 * HOLLOW RECTANGLES : 8 rectangles with various sizes and line thickness 
	 */
	else if(index == 3)
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
	/* 
	 * HOLLOW CIRCLES : 8 circles with various sizes and line thickness 
	 */
	else if(index == 4)
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
	/*  
	 * HOLLOW ELLIPSES : 8 ellipses with various sizes and line thickness 
	 */
	else if(index == 5)
	{
		delx = (LCD_WIDTH>>4) - 8;
		dely = (LCD_HEIGHT>>4) - 5;

		/* center and radius */
		x1 = LCD_WIDTH>>1;
		y1 = LCD_HEIGHT>>1;

		x2 = LCD_WIDTH>>3;
		y2 = LCD_HEIGHT>>3;

		for(i = 0; i < 8; i++)
		{
			LCD_SetFGColor(colors[i]);

			LCD_DrawEllipse(x1, y1, x2, y2);

			uPenWidth++;

			x2 += delx;
			y2 += dely;
		}

		LCD_SetPenWidth(1);
	}
	/* 
	 * CIRCLES WITH ELLIPSE ROUINE : This is for comparison purpose only.
	 * It is not recommended to use ellipse routine for drawing circles for now.
	 */
	else if(index == 6)
	{
		dely = (LCD_HEIGHT>>4);

		/* center and radius */
		x1 = LCD_WIDTH>>1;
		y1 = LCD_HEIGHT>>1;
		y2 = LCD_HEIGHT>>2;

		for(i = 0; i < 8; i++)
		{
			LCD_SetFGColor(colors[i]);

			LCD_DrawEllipse(x1, y1, y2, y2);

			uPenWidth++;

			y2 += dely;
		}

		LCD_SetPenWidth(1);
	}
	/* 
	 * SOLID RECTANGLES : 8 color filled rectangles 
	 */
	else if(index == 7)
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

			LCD_DrawFillRect(x1, y1, x2, y2);

			x1 += delx; x2 += delx;
			y1 += dely; y2 += dely;
		}

	}
	/* 
	 * SOLID CIRCLES : 8 color filled circles 
	 */
	else if(index == 8)
	{
		delx = LCD_HEIGHT>>3;
		dely = LCD_HEIGHT>>4;

		/* center and radius */
		x1 = LCD_HEIGHT>>1;
		y1 = LCD_HEIGHT>>1;
		y2 = LCD_HEIGHT>>1;

		for(i = 0; i < 8; i++)
		{
			LCD_SetFGColor(colors[i]);

			LCD_DrawFillCircle(x1, y1, y2);

			x1 += delx;
			y2 -= dely;
		}
	}
	/* 
	 * SOLID CIRCLES WITH ELLIPSE ROUTINE : 8 color filled ellipses 
	 */
	else if(index == 9)
	{
		delx = LCD_HEIGHT>>3;
		dely = LCD_HEIGHT>>4;

		/* center and radius */
		x1 = LCD_HEIGHT>>1;
		y1 = LCD_HEIGHT>>1;
		y2 = LCD_HEIGHT>>1;

		for(i = 0; i < 8; i++)
		{
			LCD_SetFGColor(colors[i]);

			LCD_DrawFillEllipse(x1, y1, y2, y2);

			x1 += delx;
			y2 -= dely;
		}
	}
	/* 
	 * POINTS : Draw points 
	 */
	else if(index == 99)
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
	/* 
	 * COLOR CONTRAST BARS: All the other case, draw contrast color bars
	 * (7 color bar, 32 cells each) 
	 */
	else
	{
		delx = LCD_WIDTH / 32;
		dely = LCD_HEIGHT / 7;

		/* initial y positions */
		y1 = 0;
		y2 = y1 + dely - 1;

		for( i = 0; i < 7; i++ )
		{
			/* initial x positions */
			x1 = 0;
			x2 = x1 + delx - 1;

			/* prepare color bars */
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
				x1 = x2 + 1;
				x2 = x1 + delx - 1;

			}

			/* advance to the next y position */
			y1 = y2 + 2;
			y2 = y1 + dely -1;

			/* revert x position */

		}
	}

	retval = 0xFFFF - uLCD_Delay;
	uLCD_Delay = 0;

	return retval;
}

/* second version of Bresenham algorithm (1000 msec for 640 calls) 
 * slow and not easy to extend for multi-pixel thickness
 */
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


/*********************************************************************
* Function:  LCD_SetScrollArea(SHORT top, SHORT scroll, SHORT bottom)
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
void LCD_SetScrollArea(uint16_t top, uint16_t scroll, uint16_t bottom)
{
	LCD_WR_Control(CMD_SET_SCROLL_AREA);
	LCD_WR_Data(top>>8);
	LCD_WR_Data(top);
	LCD_WR_Data(scroll>>8);
	LCD_WR_Data(scroll);
	LCD_WR_Data(bottom>>8);
	LCD_WR_Data(bottom);
}

/*********************************************************************
* Function:  void  LCD_SetScrollStart(SHORT line)
*
* Overview: First, we need to define the scrolling area by LCD_SetScrollArea()
*			before using this function. 
*
* PreCondition: LCD_SetScrollArea(SHORT top, SHORT scroll, SHORT bottom)
*
* Input: line - Vertical scrolling pointer (in number of lines) as 
*		 the first display line from the Top Fixed Area defined in LCD_SetScrollArea()
*
* Output: none
*
* Note: Example -
*
*		SHORT line = 0;
*		LCD_SetScrollArea(0,272,0);
*		for(line = 0;line<272;line++) {LCD_SetScrollStart(line);DelayMs(100);}
*		
*		Code above scrolls the whole page upwards in 100ms interval 
*		with page 2 replacing the first page in scrolling
********************************************************************/
void LCD_SetScrollStart(uint16_t line)
{
	LCD_WR_Control(CMD_SET_SCROLL_START);
	LCD_WR_Data(line>>8);
	LCD_WR_Data(line);	
}

/*********************************************************************
* Function:  void  LCD_SetTearingCfg(BOOL state, BOOL mode)
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
void LCD_SetTearingCfg(unsigned char state, unsigned char mode)
{
	if(state  == 1)
	{
		LCD_WR_CtrData(CMD_SET_TEAR_ON, (mode & 0x01));
	}
	else
	{
		LCD_WR_Control(CMD_SET_TEAR_OFF);
	}
}

void LCD_SetFont(LCDFONT *pFont)
{
	sLCDFont = pFont;
}

LCDFONT *LCD_GetFont(void)
{
	return sLCDFont;
}

/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: the Line where to display the character shape.
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
  * @retval None
  */
unsigned int LCD_DrawChar(int16_t x, int16_t y, const uint8_t *ch)
{
	unsigned int i, column, k, width, line;
	uint8_t chbyte;
	
	/* font width in pixel */
	width = ch[0];

	/* pixel by pixel drawing */
#if defined(ILI9325)
	if(1)
#elif defined(SSD1963)
	if( LCD_COLOR_TRANSPARENT == col_bgnd )
#endif
	{
		i = 1;
		line = 0;
		while(line < sLCDFont->Height)
		{
			/* one line of glyph */
			column = 0;
			while(column < width)
			{
				if(column < 8)
				{
					chbyte = ch[i];	
					k = column;
				}
				else if(column < 16)
				{
					chbyte = ch[i+1];
					k = column - 8;
				}
				else if(column < 24)
				{
					chbyte = ch[i+2];
					k = column - 16;
				}
				else if(column < 32)
				{
					chbyte = ch[i+3];
					k = column - 24;
				}
				/* font data error */
				else
				{
				}
				
				if(chbyte & (0x80 >> k))
				{
				#if defined(ILI9325)
					LCD_DrawPixel(x+column, y+line);
				#elif defined(SSD1963)
					LCD_SetColumnPageAddr(x+column, x+column, y+line, y+line);
					LCD_WR_CtrData(CMD_WRITE_MEM_START, col_fgnd);
				#endif
				}
			#if defined(ILI9325)
				else
				{
					LCD_WR_CtrData(CTR_HORZ_ADDRESS, x+column);
					LCD_WR_CtrData(CTR_VERT_ADDRESS, y+line);
					LCD_WR_CtrData(CTR_WRITE_DATA, col_bgnd);
				}
			#endif

				column++;
			}
			i = i+ sLCDFont->WidthBytes;
			line++;
		}
	}
	/* block drawing : note that ILI9325 does not support this mode */
	else
	{
		/* set column page address */
		LCD_SetColumnPageAddr(x, x + width - 1, y, y + sLCDFont->Height - 1);

		/* start data transfer */
		LCD_WR_Control(CMD_WRITE_MEM_START);

		i = 1;
		line = 0;

		while(line < sLCDFont->Height)
		{
			column = 0;

			while(column < width)
			{
				if(column < 8)
				{
					chbyte = ch[i];	
					k = column;
				}
				else if(column < 16)
				{
					chbyte = ch[i+1];
					k = column - 8;
				}
				else if(column < 24)
				{
					chbyte = ch[i+2];
					k = column - 16;
				}
				else if(column < 32)
				{
					chbyte = ch[i+3];
					k = column - 24;
				}
				/* font data error */
				else
				{
				}
				
				if(chbyte & (0x80 >> k))
				{
					LCD_WR_Data(col_fgnd);
				}
				else
				{
					LCD_WR_Data(col_bgnd);
				}

				column++;
			}

			i = i + sLCDFont->WidthBytes;
			line++;
		}
	}

	return width;
}


#if 0
/**
 * @brief	Sets the Text Font.
 * @param	fonts: specifies the font to be used.
 * @retval	None
 */
void LCD_SetFont(sFONT *pFont)
{
	sLCDFont = pFont;
}

/**
 * @brief	Gets the Text Font.
 * @param	None.
 * @retval	the used font.
 */
sFONT *LCD_GetFont(void)
{
	return sLCDFont;
}

/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: the Line where to display the character shape.
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
  * @retval None
  */
unsigned int LCD_DrawChar(int16_t x, int16_t y, const uint16_t *ch)
{
	unsigned int i, j, width, flag = 1;
	
	/* fixed pitch font */
	if(sLCDFont->Width)
		width = sLCDFont->Width;
	/* proportional pitch font */
	else
		width = ch[0];

	/* set column page address */
	LCD_SetColumnPageAddr(x, x + sLCDFont->Width - 1, y, 
		y + sLCDFont->Height - 1);

	/* start data transfer */
	LCD_WR_Control(CMD_WRITE_MEM_START);

	i = 0;
	while(i < sLCDFont->Height)
	{
		j = 0;
		while(j < width)
		{
				/* 8x8 and 8x12 fonts */
			if( ((sLCDFont->Width < 12)  && (ch[i] & (0x0080 >> j))) || 
				/* 12x12 fonts */
				((sLCDFont->Width == 12) && (ch[i] & (0x8000 >> j))) || 
				/* 16x24 fonts */
				((sLCDFont->Width > 12)  && (ch[i] & (0x0001 << j))) )
			{
				LCD_WR_Data(col_fgnd);
			}
			else
			{
				LCD_WR_Data(col_bgnd);
			}
			j++;
		}
		i++;
	}

	return width;
}
#endif


/**
  * @brief  Displays one character (16dots width, 24dots height).
  * @param  Line: the Line where to display the character shape .
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..9
  * @param  Column: start column address.
  * @param  Ascii: character ascii code, must be between 0x20 and 0x7E.
  * @retval None
  */
unsigned int LCD_DisplayChar(int16_t x, int16_t y, uint8_t asc)
{
	unsigned int index = 0;
	asc -= 32;

	// find the font data location
	while( asc > 0 )
	{
		index += (sLCDFont->Height)*(sLCDFont->WidthBytes) + 1;
		asc--;
	}

	return LCD_DrawChar(x, y, &sLCDFont->table[index]);
}


/**
  * @brief  Displays a maximum of 20 char on the LCD.
  * @param  Line: the Line where to display the character shape .
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..9
  * @param  *ptr: pointer to string to display on LCD.
  * @retval None
  */
void LCD_DisplayStringLine(int16_t x, int16_t y, uint8_t *pstr)
{
	unsigned int width;

	/* Send the string character by character on lCD */
	while ((*pstr != 0) )
	{
		/* Display one character on LCD */
		width = LCD_DisplayChar(x, y, *pstr);

		/* proceed to next character position */
		x += width;

		/* point on the next character */
		pstr++;
	}
}


#if defined(STM32_GL_COMPATIBILITY)
/**
  * @brief  Displays a bitmap picture loaded in the internal Flash.
  * @param  BmpAddress: Bmp picture address in the internal Flash.
  * @retval None
  */
void LCD_WriteBMP(int16_t x, int16_t y, uint32_t BmpAddress)
{
	uint32_t index, width, height;
	uint32_t i,j;

	/* Get bitmap data address offset */
	index = *(__IO uint16_t *) (BmpAddress + 10);
	index |= (*(__IO uint16_t *) (BmpAddress + 12)) << 16;

	BmpAddress += index;

	/* Get bitmap width and height */
	width = *(__IO uint16_t *) (BmpAddress + 18);
	width |= (*(__IO uint16_t *) (BmpAddress + 20)) << 16;
	height = *(__IO uint16_t *) (BmpAddress + 22);
	height |= (*(__IO uint16_t *) (BmpAddress + 24)) << 16;

	/* use index as end of line padding counter */
	index = (width & 1);

	/* TODO: check the size of bitmap here */
	LCD_SetColumnPageAddr(x, x + width, y, y + height);

#if defined(ILI9325)
	LCD_WR_Control(CTR_WRITE_DATA);
#elif defind(SSD1963)
	LCD_WR_Control(CMD_WRITE_MEM_START);
#endif

	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			LCD_WR_Data(*(__IO uint16_t *)BmpAddress);
			BmpAddress += 2;
		}

		/* there are padding bytes at the end of the line */
		if(index) BmpAddress += 2;
	}
}
#endif /* STM32_GL_COMPATIBILITY */

#if 0
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
#endif

/*****END OF FILE****/
