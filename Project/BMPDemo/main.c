/*******************************************************************************
 * File Name          : main.c
 * Author             : Brian
 * Date               : 01-Oct-2011
 *
 */

#include "stm32f10x.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"

#include "miniSTM32.h"
#include "miniSTM32_lcd.h"
#include "ff.h"
#include <stdio.h>

#define ABS(x)					((x) > 0 ? (x) : -(x))    



/* demo menu list */
enum{
	MENU_INTRO = 0,		/* display introduction of demo */
	MENU_DRAWBMP,		/* read bmp file and draw one by one */
	MENU_END			/* end of demo: restart */
};

/* interrupt ID from IRQ routines */
extern volatile uint16_t uIRQFlag;
extern void MSecTimer(uint16_t uCount);

void DisplayBMPFile(void);
void DrawFile(TCHAR* fname);

int main(void)
{
	uint16_t u16Menu = 0;

	/* Initialize SysTick - 1msec resolution */
	SysTick_Config(SystemCoreClock / 1000);

	/* initialize USB FS device layer */
	Set_System();
	Set_USBClock();

	USB_Interrupts_Config();
	USB_Init();

	while (bDeviceState != CONFIGURED);

	/* USB subsystem is successfully configured */
	printf("...USB mass storage device initialized.\n");

	LCD_Init();
	printf("...LCD initialized.\n\n");
	LCD_DisplayOn();
	LCD_BacklightOn();

	printf("Press the pushbutton to start demo.\n\n");

	while (1)
	{
		/* main menu controlled by pushbutton interrupt */
		if( uIRQFlag == MAIN_BTN_EXTI_LINE ) {

			/* clear button interrupt flag */
			uIRQFlag = 0;

			if( u16Menu == MENU_INTRO) {
				printf(
">>> Copy several BMP files on the drive, whose image fit in the LCD.\n");
				printf(
">>> After the copy, press the pushbutton to proceed.\n");
				printf(
">>> Note that only files in the root directory will be displayed.\n\n");
			}
			else if( u16Menu == MENU_DRAWBMP ) {
				DisplayBMPFile();
			}
			if( ++u16Menu == MENU_END )
			{
				printf("\nEnd of demo. Press the pushbutton to restart...\n\n\n");
				u16Menu = 0;
			}
		}
	}
}


void DisplayBMPFile(void)
{
	FRESULT rc;				/* Result code */
	FATFS fatfs;			/* File system object */
	DIR dir;				/* Directory object */
	FILINFO fno;			/* File information object */

	uint16_t i;

	uint16_t x = LCD_WIDTH>>3;
	uint16_t y = LCD_HEIGHT - (LCD_HEIGHT>>4);

	/* Register volume work area (never fails) */
	f_mount(0, &fatfs);		

	/* open dir */
	rc = f_opendir(&dir, "");
	if (rc) return;

	/* enumerate files */
	while(1) 
	{
		rc = f_readdir(&dir, &fno);	

		/* end of dir */
		if (rc || !fno.fname[0]) break;

		/* entry is not a dir */
		if (!(fno.fattrib & AM_DIR))
		{
			i = 0;
			while( (fno.fname[i] != 0x00) || i < 13 )
			{
				if( fno.fname[i] == '.' )
				{
					i++;

					/* BMP file found */
					if( (fno.fname[i++] == 'B') &&
						(fno.fname[i++] == 'M') &&
						(fno.fname[i] == 'P'))
					{
						LCD_Clear(LCD_COLOR_BLACK);
						printf("%s\n",fno.fname);
						DrawFile(fno.fname);

						/* print file name */
						LCD_SetFont(&MSSerif_19);
						LCD_SetFGColor(LCD_COLOR_RED);
						LCD_SetBGColor(LCD_COLOR_YELLOW);
						LCD_DisplayStringLine(x, y,fno.fname);

						/* 3sec delay */
						MSecTimer(3000);
						break;
					}
				}
				i++;
			}

		}
	}
}

/* 
 * Usually these functions are not exposed for public use. But in some cases,
 * you can make your code more efficient with these low level functions.
 */
extern inline void LCD_WR_Control(uint16_t command);
extern inline void LCD_WR_Data(uint16_t val);
extern void LCD_SetColumnPageAddr(int16_t cS, int16_t cE, int16_t pS, int16_t pE);

#define BMP_PIXEL_DATA_OFFSET				0x0A
#define BMP_IMAGE_WIDTH						0x12
#define BMP_IMAGE_HEIGHT					0x16
#define BMP_BIT_PER_PIXEL					0x1C
#define BMP_IMAGE_SIZE						0x22

FRESULT rc;
BYTE buff[512];
FIL fil;
UINT br;
uint16_t i, j;
uint32_t dwidth;
int32_t width, height;

#define END_OF_DATA						1
#define READ_ERROR						2

/* quick and dirty inline functions for indices handling */
inline uint8_t inci(void)
{
	i++;

	/* reaches the end of buffer */
	if(i == br)
	{
		/* last data block */
		if(br < 512)
		{
			f_close(&fil);
			return END_OF_DATA;
		}

		/* read next block */
		rc = f_read(&fil, buff, sizeof(buff), &br);

		/* read error of any kind */
		if(rc) 
		{
			f_close(&fil);
			return READ_ERROR;
		}

		/* reset index */
		i = 0;
	}

	return 0;
}

inline uint8_t incj(void)
{
	uint8_t k;

	j++;

	if((j == width) && (j < dwidth))
	{
		/* skip padding data */
		while( j < dwidth )
		{
			k = inci();
			if(k) return k;

			j++;
		}

		/* reset index */
		j = 0;
	}

	return 0;
}

void DrawFile(TCHAR *fname)
{
	int16_t x, y;
	uint16_t bpp;
	uint32_t offset, size;
	LCDCOLOR col;
	uint8_t u8save[3];

	rc = f_open(&fil, fname, FA_READ);
	if(rc) return;

	/* bitmap file header and DIB header in the first block */
	rc = f_read(&fil, buff, sizeof(buff), &br);
	if(rc) goto end;

	/* get image information */

	i = BMP_PIXEL_DATA_OFFSET;
	offset = buff[i++];
	offset += (buff[i++]<<8);
	offset += (buff[i++]<<16);
	offset += (buff[i]<<24);

	i = BMP_IMAGE_WIDTH;
	width = buff[i++];
	width += (buff[i++]<<8);
	width += (buff[i++]<<16);
	width += (buff[i]<<24);

	i = BMP_IMAGE_HEIGHT;
	height = buff[i++];
	height += (buff[i++]<<8);
	height += (buff[i++]<<16);
	height += (buff[i]<<24);

	i = BMP_BIT_PER_PIXEL;
	bpp = buff[i++];
	bpp += (buff[i]<<8);

	i = BMP_IMAGE_SIZE;
	size = buff[i++];
	size += (buff[i++]<<8);
	size += (buff[i++]<<16);
	size += (buff[i]<<24);

#if defined(LCD_QD024CPS25)
	/* TODO: put something here */

#else
	/* bitmap orientation */
	LCD_WR_Control(0x0036);		/* CMD_SET_ADDRESS_MODE */

	/* bottom-up bitmap */
	if( height > 0 )
	{
		LCD_WR_Data(0x80);
	}
	/* top-down bitmap */
	else
	{
		LCD_WR_Data(0x00);
	}
#endif

	width = ABS(width);
	height = ABS(height);

	if((width > LCD_WIDTH) || (height > LCD_HEIGHT))
	{
		printf(" --- image size exceeds limit: %d x %d pixels\n", LCD_WIDTH, LCD_HEIGHT);
		goto end;
	}

	/* image centering */
	x = (LCD_WIDTH - width)>>1;
	y = (LCD_HEIGHT - height)>>1;

	/* set viewport */
	LCD_SetColumnPageAddr(x, x + width - 1, y, y + height - 1 );

	/* start data transfer */
#if defined(LCD_QD024CPS25)
	LCD_WR_Control(0x0022); /* CTR_WRITE_DATA */
#else
	LCD_WR_Control(0x002C); /* CMD_WRITE_MEM_START */
#endif

	/* calculate image data width in bytes */
	if(bpp == 16)	
	{
		width = 2 * width;
		dwidth = size / height;
	}
	else if(bpp == 24)
	{
		width = 3 * width;
		dwidth = size / height;
	}
	else if(bpp == 32)
	{
		width = 4 * width;
		dwidth = size / height / 4;
	}
	else
	{
		printf(" --- unsupported format\n");
		goto end;
	}

	/* pointing the start position of the image data */
	while( offset > 512 )
	{
		rc = f_read(&fil, buff, sizeof(buff), &br);
		if(rc) goto end;
		offset -= 512;
	}

	/* i for indexing buff data */
	i = offset;

	/* j for tracking data padding at the line ending */
	j = 0;

	while(1)
	{
		u8save[0] = buff[i];
		if(inci()) goto end;
		if(incj()) goto end;

		u8save[1] = buff[i];
		if(inci()) goto end;
		if(incj()) goto end;

		if(bpp == 16)
		{
			col = u8save[0] + (u8save[1]<<8);	
		}
		else
		{
			u8save[2] = buff[i];
			if(inci()) goto end;
			if(incj()) goto end;

			col = LCD_COLOR(u8save[2], u8save[1], u8save[0]);

			if(bpp == 32)
			{
				if(inci()) goto end;
				if(incj()) goto end;
			}

		}

		LCD_WR_Data(col);
	}

end:

#if defined(LCD_QD024CPS25)
	/* TODO: put something here */
#else
	/* revert address mode */
	LCD_WR_Control(0x0036);		/* CMD_SET_ADDRESS_MODE */
	LCD_WR_Data(0x00);
#endif

	return;
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
