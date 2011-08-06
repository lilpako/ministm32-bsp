/*
  ******************************************************************************
  */ 

#include "miniSTM32_lcd.h"
#include "stm32f10x_fsmc.h"
#include "fonts.c"

/* FSMC use NOR(BANK1) interface with A16 as RS */
#define Bank1_LCD_Ctrl    ((uint32_t)0x60000000) // display controller Register ADDR
#define Bank1_LCD_Data    ((uint32_t)0x60020000) // display controller Data ADDR

// SSD 1963 Command Table, see manual p.20

#define CMD_NOP 				0x0000
#define CMD_SOFT_RESET			0x0001
#define CMD_GET_PWR_MODE 		0x000A
#define CMD_GET_ADDR_MODE		0x000B
#define CMD_GET_PIXEL_FMT		0x000C
#define CMD_GET_DISPLAY_MODE 	0x000D
#define CMD_GET_SIGNAL_MODE		0x000E
#define CMD_RESERVED_1			0x000F

// Operation modes
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

unsigned long color1 = 0;

extern volatile uint16_t u16SysTick;
extern void MsecDelay(uint16_t u16Delay);
void LCD_Reset(void);
void LCD_CtrlLinesConfig(void);
void LCD_FSMCConfig(void);

//void MUC_Init();
void LCD_WR_REG(unsigned int command);
unsigned int LCD_RD_REG(unsigned int command);
void LCD_WR_CMD(unsigned int index, unsigned int val);

unsigned int LCD_RD_Data(void);
void LCD_WR_Data(unsigned int val);
void LCD_WR_Data_8(unsigned int val);
void LCD_Test(void);

//void lcd_wr_zf(unsigned int a, unsigned int b, unsigned int a1,unsigned int b1, unsigned int d,unsigned int e, unsigned char g, unsigned char *f); 
void lcd_wr_pixel(unsigned int a, unsigned int b, unsigned int e);
unsigned char *num_pub(unsigned int a);
void LCD_Clear(unsigned int);

// PiXCLe Primitives Declarations
void LCD_DrawCheckerPattern(short blue, short green, short red);
void LCD_DrawBackground(short blue, short green, short red);
void LCD_DrawRectangle(int x1, int y1, int x2, int y2, short blue, short green, short red);
void LCD_DrawLine(int x1, int y1, int x2, int y2, int width, short red, short green, short blue);
void LCD_DrawPixel(unsigned int a, unsigned int b, unsigned int e);
void LCD_Test_BlackToWhite(void);
void SetLCDStartPixelLineAddress(int x1,int y1, int x2, int y2);


// TODO update colour array comments and names
unsigned int color[] = {0xf800,0x07e0,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xf81f};
//=====================================================================================

//	Controller Registers

//=====================================================================================

//
//	 SSD1963 Register Values for the 7.0" 800x480 display
//
/*
unsigned int  HDP = 799; 
unsigned int  HT = 850;
unsigned int  HPS = 51;
unsigned int  LPS = 3;
unsigned char HPW = 48;

unsigned int  VDP = 479;
unsigned int  VT = 530;
unsigned int  VPS = 50;
unsigned int  FPS = 30;
unsigned char VPW = 3;
*/

/*
//
//	 SSD1963 Register Values for the 4.3" 480x272 display
//
unsigned int  HDP = 479;
unsigned int  HT = 525;
unsigned int  HPS = 25;
unsigned int  LPS = 0;
unsigned char HPW = 2;

unsigned int  VDP = 271;
unsigned int  VT = 286;
unsigned int  VPS = 8;
unsigned int  FPS = 0;
unsigned char VPW = 1;

//
//	 SSD1963 Register Values for an alternate 4.3" 480x272 display
//	 Model is unknown, may be the display with the flaw fixed.
//
unsigned int  HDP = 479; // width, 0-indexed
unsigned int  HT = 499;
unsigned int  HPS = 20;
unsigned int  LPS = 3;
unsigned char HPW = 17;

unsigned int  VDP = 271; // height, 0-indexed
unsigned int  VT = 291;
unsigned int  VPS = 20;
unsigned int  FPS = 17;
unsigned char   VPW = 3;
 
*/

//
//	 SSD1963 Register Values for the 4.3" 400x272 display
//
//
//		HDP == Horizontal Data Pixels
//		HT  == Horizontal Timing
//		HPS == Horizontal per ?
//		LPS == ? Lines Per ?
//		HPW == Horizontal per ?
//
//		VDP == Vertical Data Pixels
//		VT 	== Vertical Timing
//		VPS == Vertical per ? 
//		FPS == Frames per ?
//		VPW == Vertical 
//

unsigned int  HDP = 479; // width, 0-indexed
unsigned int  HT = 531;  // horizontal timing
unsigned int  HPS = 43;
unsigned int  LPS = 8;
unsigned char HPW = 1;	// horizontal pulse width

unsigned int  VDP = 271; // height, 0-indexed
unsigned int  VT = 288;	 // vertical timing
unsigned int  VPS = 12;
unsigned int  FPS = 4;
unsigned char VPW = 10;	// vertical pulse width


//=====================================================================================
// These extern's do not exist in any other sample code. Original purpose is unknown.
// Assume these can be removed.
extern unsigned char zm9[];
extern unsigned char zm8[];
extern unsigned char zm7[];
extern unsigned char zm6[];
extern unsigned char zm5[];
extern unsigned char zm4[];
extern unsigned char zm3[];
extern unsigned char zm2[];
extern unsigned char zm1[];
extern unsigned char zm0[];

extern unsigned char a1[];
extern unsigned char a2[];

extern unsigned char zf2[];
extern unsigned char zf3[];	

unsigned int LCD_RD_data(void);
extern void LCD_Reset(void);
extern void Delay(__IO uint32_t nCount);


/*
 * Brian : replaced by MsecDelay()
void delay_time(unsigned int i);
 */
void SetScrollArea(unsigned int top, unsigned int scroll, unsigned int bottom);
void SetScrollStart(unsigned int line);
void SetTearingCfg(unsigned char state, unsigned char mode);





//	Write a command to the LCD Register
void LCD_WR_REG(unsigned int command)
{
	*(__IO uint16_t *) (Bank1_LCD_Ctrl) =  command;
}

// 	Read a value from an LCD Register
unsigned int LCD_RD_REG(unsigned int command)
{
	 *(__IO uint16_t *) (Bank1_LCD_Ctrl) =  command;

	return *(__IO uint16_t *) (Bank1_LCD_Data);
}

// The Bank1_LCD_Ctrl is the register where the start 
// address in a line is written.
void LCD_WR_CMD(unsigned int index, unsigned int val)
{	
	*(__IO uint16_t *) (Bank1_LCD_Ctrl) =  index;	
	*(__IO uint16_t *) (Bank1_LCD_Data) =  val;
}

unsigned int LCD_RD_Data(void)
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
void LCD_WR_Data(unsigned int val)
{   
	*(__IO uint16_t *) (Bank1_LCD_Data) =  val; 	
}

void LCD_WR_Data_8(unsigned int val)
{
	*(__IO uint16_t *) (Bank1_LCD_Data) =  val;
}


// 	Initialize the SSD1963 LCD
// 	PLL == Phase Lock Loop
//	Registers get selected with LCD-WR_REG and then the required data is written
// 	to it with LCD-WR_Data.
void LCD_Init(void)
{ 

	/* 
	 * Brian : merge port setting routine here
	 */

	/* port setting */
	LCD_CtrlLinesConfig();
	/* FSMC setting */
	LCD_FSMCConfig();
	/* initial reset */
	LCD_Reset();

	// Set up the Phase Lock Loop circuits. This only has to be done once.
	LCD_WR_REG(CMD_SET_PLL_MN); // PLL multiplier, set PLL clock to 120M
	LCD_WR_Data(0x0023); // Divider N = 0x36 for 6.5MHz, 0x23 for 10MHz crystal
	LCD_WR_Data(0x0002); // Multiplier M = 2
	LCD_WR_Data(0x0004); // dummy value, can be anything
	
	LCD_WR_REG(CMD_SET_PLL);  	// PLL enable
	LCD_WR_Data(0x0001);  // Use PLL output as system clock

	/*
	 * Brian : use MsecDelay()
	delay_time(1); // this is 100 us, allows the PLL to stabilize
	 */
	MsecDelay(1);

	LCD_WR_REG(CMD_SET_PLL);
	LCD_WR_Data(0x0003); // SSD1963 is switched to PLL output after PLL has stabilized.
	/*
	 * Brian : use MsecDelay()
	delay_time(5); // this is 500 us, allows the PLL to stabilize
	 */
	MsecDelay(1);

	LCD_WR_REG(CMD_SOFT_RESET); // software reset, see SSD1963 manual p.20 Command Table.
	/*
	 * Brian : use MsecDelay()
	delay_time(5); // this is 500 us,
	 */
	MsecDelay(1);
	LCD_WR_REG(CMD_SET_PIXCLK_FREQ);	//PLL setting for PCLK, depends on LCD resolution

	// For the 7.0" LCD
	//	LCD_WR_Data(0x0003);
	//	LCD_WR_Data(0x0033);
	//	LCD_WR_Data(0x0033);

	// For the alternate 4.3" LCD
	// LCD_WR_Data(0x0000);
	// LCD_WR_Data(0x00b4);
	// LCD_WR_Data(0x00e7);

	// For the 4.3" LCD
	LCD_WR_Data(0x0001);
	LCD_WR_Data(0x0048);
	LCD_WR_Data(0x009e);


	LCD_WR_REG(CMD_SET_LCD_MODE);	// LCD SPECIFICATION
	// We have to write 7 parameter values. Various bit values are
	// set. See manual p.43.
	LCD_WR_Data(0x0000);  // 18 bit, FRC dithering off, TFT dithering on, other stuff
	 
	LCD_WR_Data(0x0000);  // LFRAME signal polarities

	LCD_WR_Data((HDP>>8)&0X00FF);  // 2 entries for Set HDP Horizontal Display Panel size
	LCD_WR_Data(HDP&0X00FF);

    LCD_WR_Data((VDP>>8)&0X00FF);  // 2 entries for Set VDP
	LCD_WR_Data(VDP&0X00FF);

    LCD_WR_Data(0x0000); // Even line RGB sequence 000 == RGB

	LCD_WR_REG(CMD_SET_HORIZ_PERIOD);	//HSYNC
	LCD_WR_Data((HT>>8)&0X00FF);  //Set HT
	LCD_WR_Data(HT&0X00FF);
	LCD_WR_Data((HPS>>8)&0X00FF);  //Set HPS
	LCD_WR_Data(HPS&0X00FF);
	LCD_WR_Data(HPW);			   //Set HPW
	LCD_WR_Data((LPS>>8)&0X00FF);  //Set HPS
	LCD_WR_Data(LPS&0X00FF);
	LCD_WR_Data(0x0000);

	LCD_WR_REG(CMD_SET_VERT_PERIOD); //VSYNC
	LCD_WR_Data((VT>>8)&0X00FF);   //Set VT
	LCD_WR_Data(VT&0X00FF);
	LCD_WR_Data((VPS>>8)&0X00FF);  //Set VPS
	LCD_WR_Data(VPS&0X00FF);
	LCD_WR_Data(VPW);			   //Set VPW
	LCD_WR_Data((FPS>>8)&0X00FF);  //Set FPS
	LCD_WR_Data(FPS&0X00FF);

	LCD_WR_REG(CMD_SET_GPIO_VAL);
	// Set various bit values, see manual p.49
	LCD_WR_Data(0x000F);    //GPIO[3:0] out 1

	LCD_WR_REG(CMD_SET_GPIO_CONF);
	LCD_WR_Data(0x0007);    //GPIO3 = input, GPIO[2:0] = output
	LCD_WR_Data(0x0001);    //GPIO0 normal

	LCD_WR_REG(CMD_SET_ADDRESS_MODE); //rotation, see p.18
	LCD_WR_Data(0x0000);
//	LCD_WR_Data(0x0060);


	LCD_WR_REG(CMD_SET_PIXDATA_IF_FMT); //pixel data interface
	LCD_WR_Data(0x0003);


	/*
	 * Brian : use MsecDelay();
	delay_time(5); // 5 ms
	 */
	MsecDelay(5);

	LCD_Clear(0);
	LCD_WR_REG(CMD_SET_DISPLAY_ON); //display on

	LCD_WR_REG(CMD_SET_PWM_CONF); //set PWM for Backlight. Manual p.53
	// 6 parameters to be set
	LCD_WR_Data(0x0006); // PWM Freq 
	//LCD_WR_Data(0x0008);
	LCD_WR_Data(0x0080); // PWM period
	//LCD_WR_Data(0x00f0);
	
	LCD_WR_Data(0x0001); // PWM controlled by host, PWM enabled
	LCD_WR_Data(0x00f0); // brightness level 0x00 - 0xFF
	LCD_WR_Data(0x0000); // minimum brightness level =  0x00 - 0xFF
	LCD_WR_Data(0x0000); // brightness prescalar 0x0 - 0xF

	LCD_WR_REG(CMD_SET_DBC_CONF); // Dynamic Backlight Config thresholding
	LCD_WR_Data(0x000d); // 0001101. == Enabled, Agressive mode

	Backlight_On();
 
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
    unsigned int lineWidth = HDP + 1,height = VDP + 1, w;
	unsigned short rgb666_1  =  0;
	unsigned short rgb666_2  =  0;
	int check_x = 10;
	int check_y = 8;

	// Convert the R,G,B values into RGB666
	rgb666_1  =  red<<12;
	rgb666_1 |=  green<<6;
	rgb666_1 |=  blue;

	rgb666_2 = !rgb666_1;


	SetLCDStartPixelLineAddress(0,0,HDP,VDP);

	while(lineWidth--)
	{
	    for(w  =  0;w < height;w++)
		{    
          	LCD_WR_Data(rgb666_1);
		}
	}

}

//
//	Clear the LCD display by zeroing each pixel using
//	a double loop.
//	The LCD is HDP+1 x VDP+1
//
void LCD_Clear(unsigned int pixelValue)
{
    unsigned int lineWidth = HDP + 1,height = VDP + 1, w;
	uint16_t uPixel = pixelValue;

	// Set the start column and page addresses
	SetLCDStartPixelLineAddress(0,0,HDP,VDP);
	
	// The 4.3" LCD is 480x272. When the SSD1963 frame buffer is read or written
	// the "address counter" increments or decrements depending on the frame buffer
	// settings (SSD 1963 manual, p.18).
	while(lineWidth--)
	{
	    for(w  =  0;w < height;w++)
		{    
          	LCD_WR_Data(uPixel);
		}
	}
}


//	PiXCLe command primitive PARTIALLY TESTED
// 	Draws a line from between two coordinates, using a Pen width and colour
//	Needs to work out the addresses where the line is to be drawn. Does not 
//	take in to account anti-aliasing
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
    unsigned int lineWidth  =  HDP + 1,height  =  VDP + 1, w;
	unsigned short rgb888  =  0;
	unsigned int width = HDP + 1, counter = 0;

	// Write the whole screen
	SetLCDStartPixelLineAddress(0,0,HDP,VDP);

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
    unsigned int lineWidth  =  HDP + 1,height  =  VDP + 1, w;
	unsigned short rgb666  =  0;

	SetLCDStartPixelLineAddress(0,0,HDP,VDP);
	
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
    

	//LCD_WR_CMD(0x20, 0xa4);
    //LCD_WR_CMD(0x21,0x07);

	/*	  2.4" 320x240 LCD command values
	LCD_WR_CMD(0,0x00,0xa4);
	LCD_WR_CMD(0,0x01,0x07);
	LCD_WR_CMD(0,0x02,0);        //0-239
	LCD_WR_CMD(1,0x03,0);        //0-319
	
    LCD_WR_CMD(0,0x04,239);      //0-239
	LCD_WR_CMD(1,0x05,319);      //0-319
	 */
	

	//LCD_WR_REG(CMD_SET_PLL); // irrelevent here
	n = 0;
	
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
	
	
	while(n<261120)
	{
		     //while(1){

		//	temp = (uint16_t)( a2[n]<<8)+a2[n+1];
			temp = 0xf800;
			  //temp++;	
			  //LCD_WR_CMD(0x20, 0xa4);			
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


void LCD_Reset(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);
	MsecDelay(1);
	GPIO_SetBits(GPIOE, GPIO_Pin_1);
	MsecDelay(1);
}


void LCD_CtrlLinesConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable FSMC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | 
						RCC_APB2Periph_GPIOB | 
						RCC_APB2Periph_GPIOD | 
						RCC_APB2Periph_GPIOE | 
						RCC_APB2Periph_AFIO, ENABLE);

	/* FSMC output - port D */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |	/* PD0  - FSMC D02 */
								GPIO_Pin_1 |	/* PD1  - FSMC D03 */
								GPIO_Pin_4 |	/* PD4  - FSMC nOE */
								GPIO_Pin_5 |	/* PD5  - FSMC nWE */
								GPIO_Pin_7 |	/* PD7  - FSMC nE1 */
                                GPIO_Pin_8 |	/* PD8  - FSMC D13 */
								GPIO_Pin_9 |	/* PD9  - FSMC D14 */
								GPIO_Pin_10 |	/* PD10 - FSMC D15 */
								GPIO_Pin_11 |	/* PD11 - FSMC A16 */
								GPIO_Pin_14 |	/* PD14 - FSMC D00 */
                                GPIO_Pin_15;	/* PD15 - FSMC D01 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* FSMC output - port E */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |	/* PE7  - FSMC D04 */
								GPIO_Pin_8 |	/* PE8  - FSMC D05 */
								GPIO_Pin_9 |	/* PE9  - FSMC D06 */
								GPIO_Pin_10 |	/* PE10 - FSMC D07 */
								GPIO_Pin_11 |	/* PE11 - FSMC D08 */
                                GPIO_Pin_12 |	/* PE12 - FSMC D09 */
								GPIO_Pin_13 |	/* PE13 - FSMC D10 */
								GPIO_Pin_14 |	/* PE14 - FSMC D11 */
                                GPIO_Pin_15;	/* PE15 - FSMC D12 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* SPI output - port A */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |	/* PA5  - SPI1 SCK  */
								GPIO_Pin_7; 	/* PA7  - SPI1 MOSI */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* SPI input - port A */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	/* PA6  - SPI1 MISO */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Backlight(GPIO output) - port D */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	/* PD13 - BACKLIGHT */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* LCD reset(GPIO output) - port E */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	/* PE1  - LCD RESET */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* ADS7843 interrupt(GPIO input) - port B */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	/* PB6  - TCH INTR  */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* ADS7843 CS(GPIO output) - port B */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	/* PB7  - TCH CS    */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void LCD_FSMCConfig(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  p;

	p.FSMC_AddressSetupTime = 0;			/* 0 - 0xF  */
	p.FSMC_AddressHoldTime = 1;				/* 1 - 0xF  */
	p.FSMC_DataSetupTime = 1;				/* 1 - 0xFF */
	p.FSMC_BusTurnAroundDuration = 0;		/* 0 - 0xF  */
	p.FSMC_CLKDivision = 1;					/* 1 - 0xF  */
	p.FSMC_DataLatency = 0;					/* 0 - 0xF  */
	p.FSMC_AccessMode = FSMC_AccessMode_B;	/* NOR      */

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  
	
	/* BANK 1 (of NOR/SRAM Bank) is enabled */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}


void Backlight_On(void)
{
	GPIO_SetBits(GPIOD, GPIO_Pin_13);
}

void Backlight_Off(void)
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_13);
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
  
#ifndef USE_Delay
static void delay(vu32 nCount);
#endif /* USE_Delay*/
static void PutPixel(int16_t x, int16_t y);
static void LCD_PolyLineRelativeClosed(pPoint Points, uint16_t PointCount, uint16_t Closed);
















void LCD_DeInit(void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< LCD Display Off */
  LCD_DisplayOff();

  /* BANK 4 (of NOR/SRAM Bank 1~4) is disabled */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
  
  /*!< LCD_SPI DeInit */
  FSMC_NORSRAMDeInit(FSMC_Bank1_NORSRAM4);
   
  /* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
     PD.10(D15), PD.14(D0), PD.15(D1) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  /* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
     PE.14(D11), PE.15(D12) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  /* Set PF.00(A0 (RS)) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  /* Set PG.12(NE4 (LCD/CS)) as alternate function push pull - CE3(LCD /CS) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_Init(GPIOG, &GPIO_InitStructure); 
}











/**
  * @brief  Sets the LCD Text and Background colors.
  * @param  _TextColor: specifies the Text Color.
  * @param  _BackColor: specifies the Background Color.
  * @retval None
  */
void LCD_SetColors(__IO uint16_t _TextColor, __IO uint16_t _BackColor)
{
  TextColor = _TextColor; 
  BackColor = _BackColor;
}

/**
  * @brief  Gets the LCD Text and Background colors.
  * @param  _TextColor: pointer to the variable that will contain the Text 
            Color.
  * @param  _BackColor: pointer to the variable that will contain the Background 
            Color.
  * @retval None
  */
void LCD_GetColors(__IO uint16_t *_TextColor, __IO uint16_t *_BackColor)
{
  *_TextColor = TextColor; *_BackColor = BackColor;
}

/**
  * @brief  Sets the Text color.
  * @param  Color: specifies the Text color code RGB(5-6-5).
  * @retval None
  */
void LCD_SetTextColor(__IO uint16_t Color)
{
  TextColor = Color;
}


/**
  * @brief  Sets the Background color.
  * @param  Color: specifies the Background color code RGB(5-6-5).
  * @retval None
  */
void LCD_SetBackColor(__IO uint16_t Color)
{
  BackColor = Color;
}

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
  * @brief  Displays an uni line (between two points).
  * @param  x1: specifies the point 1 x position.
  * @param  y1: specifies the point 1 y position.
  * @param  x2: specifies the point 2 x position.
  * @param  y2: specifies the point 2 y position.
  * @retval None
  */
void LCD_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    PutPixel(x, y);             /* Draw the current pixel */
    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  }
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
  * @brief  Writes to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @param  LCD_RegValue: value to write to the selected register.
  * @retval None
  */
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  LCD->LCD_REG = LCD_Reg;
  /* Write 16-bit Reg */
  LCD->LCD_RAM = LCD_RegValue;
}


/**
  * @brief  Reads the selected LCD Register.
  * @param  LCD_Reg: address of the selected register.
  * @retval LCD Register Value.
  */
uint16_t LCD_ReadReg(uint8_t LCD_Reg)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = LCD_Reg;
  /* Read 16-bit Reg */
  return (LCD->LCD_RAM);
}


/**
  * @brief  Prepare to write to the LCD RAM.
  * @param  None
  * @retval None
  */
void LCD_WriteRAM_Prepare(void)
{
  LCD->LCD_REG = LCD_REG_34;
}


/**
  * @brief  Writes to the LCD RAM.
  * @param  RGB_Code: the pixel color in RGB mode (5-6-5).
  * @retval None
  */
void LCD_WriteRAM(uint16_t RGB_Code)
{
  /* Write 16-bit GRAM Reg */
  LCD->LCD_RAM = RGB_Code;
}


/**
  * @brief  Reads the LCD RAM.
  * @param  None
  * @retval LCD RAM Value.
  */
uint16_t LCD_ReadRAM(void)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = LCD_REG_34; /* Select GRAM Reg */
  /* Read 16-bit Reg */
  return LCD->LCD_RAM;
}


/**
  * @brief  Power on the LCD.
  * @param  None
  * @retval None
  */
void LCD_PowerOn(void)
{
/* Power On sequence ---------------------------------------------------------*/
  LCD_WriteReg(LCD_REG_16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  LCD_WriteReg(LCD_REG_17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
  LCD_WriteReg(LCD_REG_18, 0x0000); /* VREG1OUT voltage */
  LCD_WriteReg(LCD_REG_19, 0x0000); /* VDV[4:0] for VCOM amplitude*/
  _delay_(20);                 /* Dis-charge capacitor power voltage (200ms) */
  LCD_WriteReg(LCD_REG_16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  LCD_WriteReg(LCD_REG_17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
  _delay_(5);                  /* Delay 50 ms */
  LCD_WriteReg(LCD_REG_18, 0x0139); /* VREG1OUT voltage */
  _delay_(5);                  /* Delay 50 ms */
  LCD_WriteReg(LCD_REG_19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
  LCD_WriteReg(LCD_REG_41, 0x0013); /* VCM[4:0] for VCOMH */
  _delay_(5);                  /* Delay 50 ms */
  LCD_WriteReg(LCD_REG_7, 0x0173);  /* 262K color and display ON */
}


/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void LCD_DisplayOn(void)
{
  /* Display On */
  LCD_WriteReg(LCD_REG_7, 0x0173); /* 262K color and display ON */
}


/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void LCD_DisplayOff(void)
{
  /* Display Off */
  LCD_WriteReg(LCD_REG_7, 0x0); 
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

#ifndef USE_Delay
/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void delay(vu32 nCount)
{
  vu32 index = 0; 
  for(index = (34000 * nCount); index != 0; index--)
  {
  }
}
#endif /* USE_Delay*/

#endif

/*****END OF FILE****/
