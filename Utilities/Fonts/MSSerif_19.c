/*******************************************************************************
 * @file	MSSerif_19.c
 * @author	Brian
 * @version	V0.1.0
 * @date	21-Oct-2011
 * @brief	MS Serif 19 point (17x21)
 */

#include "lcdfonts.h"

const uint8_t MSSerif_19_Table [] = {

/* ' ' */
0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '!' */
0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '"' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x00,0x66,0x00,0x66,0x00,0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '#' */
0x09,0x00,0x00,0x00,0x00,0x1b,0x00,0x1b,0x00,0x1b,0x00,0x1b,0x00,0x7f,0x80,0x36,0x00,0x36,0x00,0x36,0x00,0x36,0x00,0xff,0x00,0x6c,0x00,0x6c,0x00,0x6c,0x00,0x6c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '$' */
0x09,0x00,0x00,0x08,0x00,0x08,0x00,0x1e,0x00,0x2b,0x00,0x69,0x00,0x69,0x00,0x78,0x00,0x3c,0x00,0x1e,0x00,0x0e,0x00,0x0b,0x00,0x4b,0x00,0x4b,0x00,0x6a,0x00,0x3c,0x00,0x08,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '%' */
0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x18,0x37,0xf0,0x62,0x60,0x62,0x60,0x64,0xc0,0x39,0x80,0x01,0x80,0x03,0x38,0x06,0x64,0x06,0xc4,0x0c,0xc4,0x18,0xc8,0x18,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '&' */
0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x19,0x80,0x18,0x80,0x19,0x80,0x0f,0x00,0x0e,0x38,0x1e,0x10,0x33,0x10,0x61,0xa0,0x60,0xc0,0x60,0xc0,0x31,0xe4,0x1f,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ''' */
0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '(' */
0x06,0x00,0x00,0x08,0x00,0x18,0x00,0x10,0x00,0x30,0x00,0x30,0x00,0x20,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x20,0x00,0x30,0x00,0x30,0x00,0x10,0x00,0x18,0x00,0x08,0x00,0x00,0x00,
/* ')' */
0x06,0x00,0x00,0x40,0x00,0x60,0x00,0x20,0x00,0x30,0x00,0x30,0x00,0x10,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x10,0x00,0x30,0x00,0x30,0x00,0x20,0x00,0x60,0x00,0x40,0x00,0x00,0x00,
/* '*' */
0x09,0x00,0x00,0x00,0x00,0x08,0x00,0x2a,0x00,0x3e,0x00,0x1c,0x00,0x3e,0x00,0x2a,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '+' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x7f,0x80,0x7f,0x80,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ',' */
0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x60,0x00,0x20,0x00,0x20,0x00,0x40,0x00,0x00,0x00,0x00,0x00,
/* '-' */
0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '.' */
0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '/' */
0x05,0x00,0x00,0x00,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0xc0,0x00,0xc0,0x00,0xc0,0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '0' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x00,0x36,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x36,0x00,0x1c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '1' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x0c,0x00,0x3c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '2' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x00,0x3e,0x00,0x47,0x00,0x03,0x00,0x03,0x00,0x06,0x00,0x04,0x00,0x0c,0x00,0x18,0x00,0x10,0x00,0x21,0x00,0x7f,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '3' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x00,0x26,0x00,0x43,0x00,0x03,0x00,0x02,0x00,0x04,0x00,0x1e,0x00,0x07,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x66,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '4' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x06,0x00,0x0e,0x00,0x0e,0x00,0x16,0x00,0x16,0x00,0x26,0x00,0x26,0x00,0x7f,0x00,0x7f,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '5' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x00,0x1f,0x00,0x20,0x00,0x20,0x00,0x7c,0x00,0x7e,0x00,0x07,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x66,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '6' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0x00,0x18,0x00,0x30,0x00,0x30,0x00,0x60,0x00,0x6c,0x00,0x76,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x36,0x00,0x1c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '7' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x00,0x3f,0x00,0x46,0x00,0x06,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '8' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x00,0x36,0x00,0x63,0x00,0x63,0x00,0x72,0x00,0x3c,0x00,0x1e,0x00,0x27,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x36,0x00,0x1c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '9' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x00,0x36,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x37,0x00,0x1b,0x00,0x03,0x00,0x02,0x00,0x06,0x00,0x0c,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ':' */
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ';' */
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x60,0x00,0x20,0x00,0x20,0x00,0x40,0x00,0x00,0x00,0x00,0x00,
/* '<' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x07,0x00,0x0e,0x00,0x38,0x00,0x70,0x00,0x38,0x00,0x0e,0x00,0x07,0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '=' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x80,0x7f,0x80,0x00,0x00,0x00,0x00,0x7f,0x80,0x7f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '>' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x38,0x00,0x1c,0x00,0x07,0x00,0x03,0x80,0x07,0x00,0x1c,0x00,0x38,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '?' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x00,0x46,0x00,0x66,0x00,0x66,0x00,0x06,0x00,0x0c,0x00,0x0c,0x00,0x18,0x00,0x10,0x00,0x10,0x00,0x00,0x00,0x18,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '@' */
0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xe0,0x0e,0x38,0x18,0x0c,0x30,0x06,0x31,0xb6,0x63,0x73,0x66,0x33,0x66,0x23,0x66,0x63,0x63,0x76,0x31,0x9c,0x30,0x00,0x18,0x00,0x0e,0x18,0x03,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'A' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x06,0x00,0x0e,0x00,0x0b,0x00,0x0b,0x00,0x13,0x00,0x11,0x80,0x21,0x80,0x3f,0xc0,0x20,0xc0,0x40,0xc0,0x40,0x60,0xe0,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'B' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x00,0x30,0xc0,0x30,0x60,0x30,0x60,0x30,0x60,0x30,0xc0,0x3f,0xc0,0x30,0x60,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x60,0x7f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'C' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xa0,0x1c,0x60,0x30,0x20,0x30,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x30,0x00,0x30,0x10,0x1c,0x60,0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'D' */
0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x80,0x30,0x60,0x30,0x30,0x30,0x30,0x30,0x18,0x30,0x18,0x30,0x18,0x30,0x18,0x30,0x18,0x30,0x30,0x30,0x30,0x30,0x60,0x7f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'E' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0xc0,0x30,0x40,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x80,0x3f,0x80,0x30,0x80,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x20,0x7f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'F' */
0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0xc0,0x30,0x40,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x80,0x3f,0x80,0x30,0x80,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'G' */
0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xa0,0x1c,0x60,0x30,0x20,0x30,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x78,0x60,0x30,0x30,0x30,0x30,0x30,0x1c,0x70,0x07,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'H' */
0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x78,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x3f,0xf0,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x78,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'I' */
0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'J' */
0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0xd8,0x00,0xd8,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'K' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0xf0,0x30,0xc0,0x31,0x80,0x33,0x00,0x36,0x00,0x3e,0x00,0x3b,0x00,0x33,0x80,0x31,0x80,0x30,0xc0,0x30,0xe0,0x30,0x60,0x79,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'L' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x20,0x7f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'M' */
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x1e,0x38,0x1c,0x3c,0x3c,0x2c,0x2c,0x2c,0x2c,0x26,0x4c,0x26,0x4c,0x26,0x4c,0x23,0x8c,0x23,0x8c,0x23,0x8c,0x21,0x0c,0x71,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'N' */
0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x38,0x38,0x10,0x3c,0x10,0x2e,0x10,0x27,0x10,0x23,0x10,0x23,0x90,0x21,0xd0,0x20,0xf0,0x20,0x70,0x20,0x70,0x20,0x30,0x70,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'O' */
0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x18,0x60,0x30,0x30,0x30,0x30,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x18,0x30,0x30,0x30,0x30,0x18,0x60,0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'P' */
0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x00,0x30,0xc0,0x30,0x60,0x30,0x60,0x30,0x60,0x30,0xc0,0x3f,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'Q' */
0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x18,0x60,0x30,0x30,0x30,0x30,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x18,0x30,0x30,0x30,0x30,0x18,0x60,0x07,0x80,0x03,0x80,0x00,0xc0,0x00,0x30,0x00,0x00,0x00,0x00,
/* 'R' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x80,0x30,0xc0,0x30,0x60,0x30,0x60,0x30,0x60,0x30,0xc0,0x3f,0x80,0x31,0x80,0x30,0xc0,0x30,0xc0,0x30,0x60,0x30,0x60,0x78,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'S' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x1d,0x00,0x33,0x00,0x61,0x00,0x61,0x00,0x70,0x00,0x38,0x00,0x1e,0x00,0x07,0x00,0x03,0x80,0x41,0x80,0x41,0x80,0x63,0x00,0x5e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'T' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0xe0,0x46,0x20,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'U' */
0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x38,0x30,0x10,0x30,0x10,0x30,0x10,0x30,0x10,0x30,0x10,0x30,0x10,0x30,0x10,0x30,0x10,0x30,0x10,0x18,0x20,0x1c,0x60,0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'V' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xf0,0x60,0x60,0x60,0x40,0x30,0x40,0x30,0x80,0x30,0x80,0x19,0x00,0x19,0x00,0x0e,0x00,0x0e,0x00,0x0e,0x00,0x04,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'W' */
0x11,0x00,0x00,0x00,0x00,0x00,0x00,0xf3,0xc3,0x61,0x81,0x61,0x81,0x30,0xc2,0x30,0xc2,0x30,0xc2,0x19,0x64,0x19,0x64,0x0e,0x38,0x0e,0x38,0x0e,0x38,0x04,0x10,0x04,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'X' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0xf8,0xf0,0x30,0x60,0x18,0x40,0x1c,0x80,0x0d,0x00,0x07,0x00,0x07,0x00,0x0b,0x00,0x09,0x80,0x11,0xc0,0x20,0xc0,0x60,0x60,0xf0,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'Y' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x70,0x60,0x20,0x30,0x40,0x30,0x40,0x18,0x80,0x0d,0x00,0x0d,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'Z' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xe0,0x20,0xc0,0x00,0xc0,0x01,0x80,0x03,0x80,0x03,0x00,0x06,0x00,0x0e,0x00,0x0c,0x00,0x18,0x00,0x38,0x00,0x30,0x10,0x7f,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '[' */
0x06,0x00,0x00,0x00,0x00,0x3c,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,
/* '\' */
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0xc0,0x00,0xc0,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ']' */
0x06,0x00,0x00,0x00,0x00,0xf0,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,
/* '^' */
0x09,0x00,0x00,0x00,0x00,0x08,0x00,0x1c,0x00,0x36,0x00,0x63,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '_' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
/* '`' */
0x06,0x00,0x00,0x00,0x00,0x60,0x00,0x30,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'a' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x63,0x00,0x63,0x00,0x0f,0x00,0x33,0x00,0x63,0x00,0x63,0x00,0x6f,0x00,0x3b,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'b' */
0x0a,0x00,0x00,0x00,0x00,0x20,0x00,0xe0,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x6e,0x00,0x73,0x00,0x61,0x80,0x61,0x80,0x61,0x80,0x61,0x80,0x61,0x80,0x73,0x00,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'c' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x33,0x00,0x63,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x61,0x00,0x33,0x00,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'd' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x80,0x03,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x1d,0x80,0x33,0x80,0x61,0x80,0x61,0x80,0x61,0x80,0x61,0x80,0x61,0x80,0x33,0x80,0x1e,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'e' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x00,0x36,0x00,0x63,0x00,0x7f,0x00,0x60,0x00,0x60,0x00,0x61,0x00,0x33,0x00,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'f' */
0x05,0x00,0x00,0x00,0x00,0x38,0x00,0x68,0x00,0x60,0x00,0x60,0x00,0xf8,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'g' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x00,0x37,0x80,0x63,0x00,0x63,0x00,0x36,0x00,0x1c,0x00,0x30,0x00,0x60,0x00,0x7f,0x00,0xc3,0x80,0xc1,0x80,0xc3,0x00,0x7e,0x00,0x00,0x00,
/* 'h' */
0x09,0x00,0x00,0x00,0x00,0x20,0x00,0xe0,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x6e,0x00,0x73,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0xf3,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'i' */
0x05,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x70,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'j' */
0x05,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x70,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0xb0,0x00,0x60,0x00,0x00,0x00,
/* 'k' */
0x09,0x00,0x00,0x00,0x00,0x20,0x00,0xe0,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x6f,0x00,0x64,0x00,0x68,0x00,0x70,0x00,0x78,0x00,0x6c,0x00,0x6c,0x00,0x66,0x00,0xf7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'l' */
0x05,0x00,0x00,0x00,0x00,0x20,0x00,0xe0,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'm' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2c,0xc0,0xff,0xe0,0x66,0x60,0x66,0x60,0x66,0x60,0x66,0x60,0x66,0x60,0x66,0x60,0xf7,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'n' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6e,0x00,0xf3,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0xf3,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'o' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x23,0x00,0x61,0x80,0x61,0x80,0x61,0x80,0x61,0x80,0x61,0x80,0x31,0x00,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'p' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5e,0x00,0xf3,0x00,0x61,0x80,0x61,0x80,0x61,0x80,0x61,0x80,0x61,0x80,0x73,0x00,0x6e,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0xf0,0x00,0x00,0x00,
/* 'q' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3d,0x00,0x67,0x00,0xc3,0x00,0xc3,0x00,0xc3,0x00,0xc3,0x00,0xc3,0x00,0x67,0x00,0x3b,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x07,0x80,0x00,0x00,
/* 'r' */
0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6c,0x00,0xfc,0x00,0x64,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 's' */
0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x74,0x00,0xcc,0x00,0xc4,0x00,0x60,0x00,0x30,0x00,0x18,0x00,0x8c,0x00,0xcc,0x00,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 't' */
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x20,0x00,0x60,0x00,0xf8,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x68,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'u' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe7,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x63,0x00,0x67,0x00,0x3b,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'v' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf3,0x80,0x61,0x00,0x61,0x00,0x32,0x00,0x32,0x00,0x1c,0x00,0x1c,0x00,0x08,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'w' */
0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf7,0xb8,0x63,0x10,0x63,0x10,0x37,0xb0,0x35,0xa0,0x1c,0xe0,0x1c,0xe0,0x08,0x40,0x08,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'x' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf7,0x00,0x62,0x00,0x34,0x00,0x38,0x00,0x18,0x00,0x1c,0x00,0x2c,0x00,0x46,0x00,0xef,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'y' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf3,0x80,0x61,0x00,0x61,0x00,0x32,0x00,0x32,0x00,0x1c,0x00,0x1c,0x00,0x08,0x00,0x08,0x00,0x18,0x00,0x50,0x00,0xf0,0x00,0x60,0x00,0x00,0x00,
/* 'z' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x00,0x86,0x00,0x0c,0x00,0x18,0x00,0x30,0x00,0x60,0x00,0xc0,0x00,0xc2,0x00,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '{' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x30,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x0e,0x00,0x00,0x00,
/* '|' */
0x04,0x00,0x00,0x00,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '}' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x0c,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x70,0x00,0x00,0x00,
/* '~' */
0x09,0x00,0x00,0x00,0x00,0x39,0x00,0x7f,0x00,0x4e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

LCDFONT MSSerif_19 = {
	2,			/* widthbytes */
	21,			/* fontheight */
	MSSerif_19_Table
};

/***** END OF FILE *****/
