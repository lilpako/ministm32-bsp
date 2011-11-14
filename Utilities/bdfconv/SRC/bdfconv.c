/**
	\file		bdfconv.c
	\author		Sungjune Lee
	\version	V0.2.0
	\date		12-Nov-2011
	\brief		stm32-bsp font data file generation utility.
	\note
				This utility converts a Adobe BDF file to a font data file for stm32-bsp
				as a form of c source file.  To use this utility, run:

					bdfconf.c font.bdf
				
				The name of the generated file (and its structure) is constructed as
					
					FamilyName_Spacing_WeightName_Slant_Size

				for example DejaVuSans_Mono_Bold_Italic_24. 'Normal' and 'Medium' are 
				omitted in the WeightName for convenience. One good place to shop good
				and free fonts is

					http://www.google.com/webfonts

				Note that otf2bdf utility convert an OpenType font to a BDF font using 
				the Freetype2 renderer. When generating BDF file, it is recommended to
				defind the character code range(0x20 - 0x7E), i.e. 
				
					otf2bdf -p 17 -l '32_126' DejaVuSans.ttf -o DejaVuSans17.bdf

				Otherwise the FONTBOUNDINGBOX value often becomes unnecessarly big.
				In that case one may have to adjust the FONTBOUNDINGBOX manually.
				Usually, the widest glype in the range is 'W'(0x57), so compare value 
				of the FONTBOUNDINGBOX and the value of BBX of 'W' and replace the 
				first value of FONTBOUNDINGBOX with the first value of BBX of 'W', 
				if the FONTBOUNDINGBOX values are not appropriate.

				For Windows bitmap fonts(FON), one can use FontForge and for X11 
				bitmap fonts, one can use pcf2bdf to convert those to BDF fonts. 
				bdfresize utility might be also useful.

				Some limitations should be addressed. Due to the rendering algorithm, 
				font space is slightly wider than it should be espcially in italic
				fonts. And, the maximum pixel width of glype is limited to 32.

	\todo
	\remarks	© Sungjune Lee 2011
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define STR_LEN				500
#define KEY_LEN				100
#define VAL_LEN				400
#define PXL_LEN				10
#define FNT_LEN				100
#define FCE_LEN				100
#define BMP_LEN				40

#define PITCH_FIXED			1
#define PITCH_PROP			2
#define PITCH_UNKNOWN		99

#define SLANT_REGULAR		1
#define SLANT_ITALIC		2
#define SLANT_UNKNOWN		99

/*
#define DEBUG_OUT
*/

char *bdf_version =	"2.1";
FILE *ifp = NULL, *ofp = NULL;

int	FBBx, FBBy, Xoff, Yoff;					/* FONTBOUNDINGBOX	*/
int	spacing = 0;							/* SPACING			*/
int slant = SLANT_REGULAR;					/* SLANT			*/
int widthbytes;

char pixelsize[PXL_LEN] = "x";				/* PIXELSIZE		*/
char pointsize[PXL_LEN] = "x";				/* SIZE				*/
char weightname[FNT_LEN] = "Unknown";		/* FONT_NAME		*/
char familyname[FCE_LEN] = "Unknown";		/* FAMILY_NAME		*/
char dataname[FCE_LEN];						/* internal use		*/

int	encoding;								/* ENCODING			*/
int	dwx0, dwy0;								/* DWIDTH			*/
int	BBw, BBh, BBxoff0x, BByoff0y;			/* BBX				*/

uint32_t bmp_data[BMP_LEN], bmp_idx;		/* BITMAP DATA		*/

int open_output_file(void);
int save_data(int flag);

void main(int argc, char *argv[])
{
	char	str[STR_LEN];
	char	key[KEY_LEN];
	char	val[VAL_LEN];
	int		i, j;
	int		glyph_decode = 0;
	int		bitmap_decode = 0;

	if( argc != 2)
	{
		printf("Usage:bdfconf BDF_File_To_Convert\n");
		return;
	}

	ifp = fopen(argv[1], "r");

	if(!ifp)
	{
		printf("Error: file open %s\n", argv[1]);
		return;
	}

	bmp_idx = 0;

	/* BDF file decoding loop */
	while(fgets(str, STR_LEN, ifp))
	{
		/* retrieve keyword and value for each line */
		if(sscanf(str, "%s", key) == 0) continue;
		strcpy(val, (str + strlen(key) + 1));

		/* version */
		if(strcmp(key,"STARTFONT") == 0)
		{
			sscanf(val, "%s", str);

			/* only BDF version 2.1 is supported*/
			if(strcmp(str, bdf_version))
			{
				printf("Error: BDF file version is not 2.1\n");
				break;
			}
		}

		/* size */
		else if(strcmp(key, "SIZE") == 0)
		{
			sscanf(val, "%s", pointsize);
		#ifdef DEBUG_OUT
			printf("Font Size: %s\n", pointsize);
		#endif
		}

		/* fond bounding box */
		else if(strcmp(key, "FONTBOUNDINGBOX") == 0)
		{
			sscanf(val, "%d %d %d %d", &FBBx, &FBBy, &Xoff, &Yoff);
		}

		/* family name */
		else if(strcmp(key, "FAMILY_NAME") == 0)
		{
			i = 0; j = 0;
			while(val[i] != '\"') i++;
			i++;
			while((val[i] != '\"') && (val[i] != 0x00))
				familyname[j++] = val[i++];
			familyname[j] = 0x00;

		#ifdef DEBUG_OUT
			printf("Family Name: %s\n", familyname);
		#endif
		}

		/* weight name */
		else if(strcmp(key, "WEIGHT_NAME") == 0)
		{
			i = 0; j = 0;
			while(val[i] != '\"') i++;
			i++;
			while((val[i] != '\"') && (val[i] != 0x00))
				weightname[j++] = val[i++];
			weightname[j] = 0x00;

		#ifdef DEBUG_OUT
			printf("Weight Name: %s\n", weightname);
		#endif
		}
		/* slant */
		else if(strcmp(key, "SLANT") == 0)
		{
			sscanf(val, "%s", str);
			if(strcmp(str, "\"R\"") == 0)
			{
				slant = SLANT_REGULAR;
			}
			else if(strcmp(str, "\"I\"") == 0)
			{
				slant = SLANT_ITALIC;
			}
			else
			{
				slant = SLANT_UNKNOWN;
			}

		#ifdef DEBUG_OUT
			printf("Slant: %s\n", str);
		#endif
		}

		/* pixelsize */
		else if(strcmp(key, "PIXEL_SIZE") == 0)
		{
			sscanf(val, "%s", pixelsize);

			if(open_output_file())
			{
				if(ifp) fclose(ifp);
				return;
			}

		#ifdef DEBUG_OUT
			printf("Pixel Size: %s\n", pixelsize);
		#endif
		}

		/* spacing */
		else if(strcmp(key, "SPACING") == 0)
		{
			sscanf(val, "%s", str);
			if(strcmp(str, "\"P\"") == 0)
			{
				spacing = PITCH_PROP;
			}
			else if(strcmp(str, "\"F\"") == 0)
			{
				spacing = PITCH_FIXED;
			}
			else
			{
				spacing = PITCH_UNKNOWN;
			}

		#ifdef DEBUG_OUT
			printf("Spacing: %s\n", str);
		#endif
		}

		/* start of glyph data */
		else if(strcmp(key, "STARTCHAR") == 0)
		{
			glyph_decode = 1;
		}

		/* end of glyph data */
		else if(strcmp(key, "ENDCHAR") == 0)
		{
			glyph_decode = 0;
			bitmap_decode = 0;
			
			if((encoding >= 0x20) && (encoding < 0x7e))
				save_data(0);
			else if(encoding == 0x7e)
				save_data(1);

			bmp_idx = 0;
		}

		/* encoding */
		else if(strcmp(key, "ENCODING") == 0)
		{
			sscanf(val, "%d", &encoding);
		}

		/* dwidth */
		else if(strcmp(key, "DWIDTH") == 0)
		{
			sscanf(val, "%d %d", &dwx0, &dwy0);
		}

		/* bbx */
		else if(strcmp(key, "BBX") == 0)
		{
			sscanf(val, "%d %d %d %d", &BBw, &BBh, &BBxoff0x, &BByoff0y);
		}

		/* bitmap */
		else if(strcmp(key, "BITMAP") == 0)
		{
			bitmap_decode = 1;
		}

		/* bitmap data */
		else if(bitmap_decode)
		{
			if(sscanf(key, "%x", &(bmp_data[bmp_idx])))
				bmp_idx++;
		}
	}

	if(ifp) fclose(ifp);

	if(ofp) 
	{
		fprintf(ofp, "\n");
		fprintf(ofp, "};\n\n");
		fprintf(ofp, "LCDFONT %s = {\n", dataname);
		fprintf(ofp, "\t%d,\t\t\t/* widthbytes */\n", widthbytes);
		fprintf(ofp, "\t%d,\t\t\t/* fontheight */\n", FBBy);
		fprintf(ofp, "\t%s_Table\n", dataname);
		fprintf(ofp, "};\n\n");
		fprintf(ofp, "/***** END OF FILE *****/\n");
		fclose(ofp);
	}
}


int open_output_file(void)
{
	int i, j;
	char fname[100];
	
	/* construct data name */

	/* eliminate space characters */
	i = j = 0;
	while(familyname[i] != 0x00)
		if(familyname[i] == 0x20) i++;
		else dataname[j++] = familyname[i++];

	/* add spacing */
	if(spacing == PITCH_FIXED )
	{
		dataname[j++] = '_';
		dataname[j++] = 'M';
		dataname[j++] = 'o';
		dataname[j++] = 'n';
		dataname[j++] = 'o';
	}

	/* add weight name */
	if((strcmp(weightname, "Normal")) && (strcmp(weightname, "Medium")))
	{
		dataname[j++] = '_';
		i = 0;
		while(weightname[i] != 0x00)
			if(weightname[i] == 0x20) i++;
			else dataname[j++] = weightname[i++];
	}

	/* add slant */
	if(slant == SLANT_ITALIC )
	{
		dataname[j++] = '_';
		dataname[j++] = 'I';
		dataname[j++] = 't';
		dataname[j++] = 'a';
		dataname[j++] = 'l';
		dataname[j++] = 'i';
		dataname[j++] = 'c';
	}

	/* add point size */
	dataname[j++] = '_';
	i = 0;
	while(pointsize[i] != 0x00)
		if(pointsize[i] == 0x20) i++;
		else dataname[j++] = pointsize[i++];
	
	dataname[j] = 0x00;

	/* construct file name */
	i = 0;
	while(dataname[i] != 0x00)
		fname[i] = dataname[i++];
	
	fname[i++] = '.';
	fname[i++] = 'c';
	fname[i] = 0x00;

	printf("Filename:%s\n", fname);

	ofp = fopen(fname, "w+");

	if(ofp == NULL) return;

	/* widthbyte */
	if((FBBx-1) <= 8) widthbytes = 1;
	else if((FBBx-1) <= 16) widthbytes = 2;
	else if((FBBx-1) <= 24) widthbytes = 3;
	else if((FBBx-1) <= 32) widthbytes = 4;
	else
	{
		/* Font size is too big to fit into 32bit data structure */
#if 0
		printf("Error: Font size is too big. FBBx = %d.\n", FBBx);

		widthbytes = 0;	
		fclose(ofp);
		ofp = NULL;

		return -1;
#else
		printf("Warning: Font bounding box is too big. FBBx = %d.\n", FBBx);
		widthbytes = 4;
#endif
	}

	/* write initial part of the output file */
	fprintf(ofp, "/*******************************************************************************\n"); 
	fprintf(ofp, " * @file\t%s\n",fname);
	fprintf(ofp, " * @author\tBrian\n");
	fprintf(ofp, " * @version\tV0.1.0\n");
	fprintf(ofp, " * @date\t21-Oct-2011\n");
	fprintf(ofp, " * @brief\t%s %s point (%dx%d)\n", familyname, pointsize, FBBx, FBBy);
	fprintf(ofp, " */\n\n");
	fprintf(ofp, "#include \"lcdfonts.h\"\n\n");
	fprintf(ofp, "const uint8_t %s_Table [] = {\n", dataname);

	return 0;
}

int save_data(int flag)
{
	int i, j, k, l;
	int px_h, px_v;
	uint8_t u8Data;

	if(ofp == NULL) return;
	
	/* x margin in pixel from the leftmost position */
	px_v = -Xoff + BBxoff0x;

	/* y margin in pixel from the topmost position */
	px_h = FBBy + Yoff - BByoff0y - BBh;

	/* character code */
	fprintf(ofp, "\n/* \'%c\' */\n", encoding);

#if defined(DEBUG_OUT)
	/* for debug purpose only */
	fprintf(ofp, "BBw:%d, BBh:%d, BBofx:%d, BBofy:%d\n", BBw, BBh, BBxoff0x, BByoff0y);
	fprintf(ofp, "px_v:%d, px_h:%d\n", px_v, px_h);
	j = 0;
	while(j < bmp_idx)
		fprintf(ofp, "%04x.", bmp_data[j++]);
	fprintf(ofp, "\n");

#endif /* DEBUG_OUT */

	/* actual font data width */
	if( dwx0 > (px_v + BBw) )
		fprintf(ofp, "0x%02x,", dwx0);
	else
		fprintf(ofp, "0x%02x,", px_v + BBw);

	/* fill the leading horizontal blank lines*/
	i = 0;
	while( i < px_h )
	{
		l = 0;
		while(l < widthbytes)
		{
			fprintf(ofp, "0x%02x,", 0);
			l++;
		}

		i++;
	}

	/* determine the width of BITMAP data */
	if(BBw <=8) k = 24;
	else if(BBw <= 16) k = 16;
	else if(BBw <= 24) k = 8;
	else if(BBw <= 32) k = 0;
	/* TODO: error: font data too big */
	else
	{
		printf("Error: BITMAP data is too big. BBw = %d.\n", BBw);
		return -1;
	}

	/* fill actual data */

	j = 0;
	while( j < BBh )
	{
		/* align the BITMAP data to the leftmost bit of 32bit */
		bmp_data[j] = bmp_data[j] << k;

		/* compensate leading zero columns */
		bmp_data[j] = bmp_data[j]>>px_v;

		/* write data into uint8_t string */
		l = 0;
		while(l < widthbytes)
		{
			u8Data = (bmp_data[j]>>(8*(3-l)))& 0xFF;

			if( flag && (l == (widthbytes-1)) && (j == (FBBy-1)))
				fprintf(ofp, "0x%02x", u8Data);
			else
				fprintf(ofp, "0x%02x,", u8Data);
			l++;
		}

		j++;
		i++;
	}

	/* fill the trailing horozontal blank lines */
	while( i < FBBy )
	{
		l = 0;
		while(l < widthbytes)
		{
			/* erase the trailing comma at the very end of the data */
			if( flag && (l == (widthbytes-1)) && (i == (FBBy-1)))
				fprintf(ofp, "0x%02x", 0);
			else
				fprintf(ofp, "0x%02x,", 0);
			l++;
		}
		i++;
	}

	return 0;
}
