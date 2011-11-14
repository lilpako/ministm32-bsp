/*******************************************************************************
 * @file	Federant_10.c
 * @author	Brian
 * @version	V0.1.0
 * @date	21-Oct-2011
 * @brief	Federant 10 point (15x15)
 */

#include "lcdfonts.h"

const uint8_t Federant_10_Table [] = {

/* ' ' */
0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '!' */
0x04,0x00,0x00,0x00,0x00,0x70,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '"' */
0x05,0x00,0x00,0x28,0x00,0x28,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '#' */
0x09,0x00,0x00,0x1b,0x00,0x12,0x00,0x12,0x00,0x3f,0x80,0x12,0x00,0x12,0x00,0x3f,0x80,0x12,0x00,0x12,0x00,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '$' */
0x08,0x04,0x00,0x1e,0x00,0x30,0x00,0x30,0x00,0x18,0x00,0x0c,0x00,0x0c,0x00,0x06,0x00,0x02,0x00,0x03,0x00,0x3e,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '%' */
0x0d,0x00,0x40,0x3c,0x40,0x24,0x40,0x24,0x80,0x24,0x80,0x25,0x78,0x3d,0x48,0x02,0x48,0x02,0x48,0x04,0x48,0x04,0x78,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '&' */
0x0a,0x06,0x00,0x1a,0x00,0x12,0x00,0x1c,0x00,0x08,0x00,0x3c,0x00,0x66,0x40,0x63,0x80,0x37,0x00,0x39,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ''' */
0x03,0x00,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '(' */
0x05,0x08,0x00,0x10,0x00,0x10,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x20,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x10,0x00,0x10,0x00,0x08,0x00,0x00,0x00,0x00,0x00,
/* ')' */
0x04,0x40,0x00,0x20,0x00,0x20,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x10,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x20,0x00,0x20,0x00,0x40,0x00,0x00,0x00,0x00,0x00,
/* '*' */
0x07,0x08,0x00,0x2a,0x00,0x1c,0x00,0x1c,0x00,0x2a,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '+' */
0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x3e,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ',' */
0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x20,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '-' */
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '.' */
0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '/' */
0x06,0x04,0x00,0x0c,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x18,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00,0x00,0x00,
/* '0' */
0x08,0x1e,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '1' */
0x06,0x00,0x00,0x78,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x1c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '2' */
0x08,0x00,0x00,0x1e,0x00,0x33,0x00,0x33,0x00,0x32,0x00,0x06,0x00,0x04,0x00,0x08,0x00,0x1b,0x00,0x33,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '3' */
0x08,0x00,0x00,0x1e,0x00,0x33,0x00,0x33,0x00,0x32,0x00,0x0e,0x00,0x03,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '4' */
0x08,0x00,0x00,0x06,0x00,0x0e,0x00,0x0e,0x00,0x16,0x00,0x16,0x00,0x26,0x00,0x26,0x00,0x7f,0x00,0x06,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '5' */
0x08,0x00,0x00,0x3e,0x00,0x20,0x00,0x20,0x00,0x3e,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x33,0x00,0x33,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '6' */
0x08,0x1e,0x00,0x30,0x00,0x30,0x00,0x3e,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '7' */
0x07,0x00,0x00,0x3e,0x00,0x66,0x00,0x64,0x00,0x04,0x00,0x0c,0x00,0x08,0x00,0x18,0x00,0x18,0x00,0x10,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '8' */
0x08,0x00,0x00,0x1e,0x00,0x33,0x00,0x33,0x00,0x32,0x00,0x1e,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x32,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '9' */
0x08,0x00,0x00,0x1e,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x3f,0x00,0x03,0x00,0x03,0x00,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ':' */
0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ';' */
0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x20,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '<' */
0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x08,0x00,0x30,0x00,0x30,0x00,0x18,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '=' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '>' */
0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x10,0x00,0x0c,0x00,0x0c,0x00,0x18,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '?' */
0x08,0x00,0x00,0x00,0x00,0x1e,0x00,0x33,0x00,0x32,0x00,0x36,0x00,0x0c,0x00,0x08,0x00,0x08,0x00,0x00,0x00,0x0c,0x00,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '@' */
0x0c,0x00,0x00,0x00,0x00,0x1f,0xc0,0x30,0x60,0x30,0x60,0x33,0xe0,0x36,0x60,0x36,0x60,0x36,0x60,0x37,0xf0,0x30,0x00,0x30,0x00,0x3f,0x80,0x00,0x00,0x00,0x00,
/* 'A' */
0x0a,0x00,0x00,0x7f,0x00,0x01,0x80,0x31,0x80,0x31,0x80,0x3f,0x80,0x31,0x80,0x31,0x80,0x31,0x80,0x31,0x80,0x39,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'B' */
0x09,0x00,0x00,0x7f,0x00,0x01,0x80,0x31,0x80,0x31,0x00,0x3f,0x00,0x31,0x80,0x31,0x80,0x31,0x80,0x31,0x80,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'C' */
0x09,0x00,0x00,0x00,0x00,0x1f,0x80,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x3f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'D' */
0x0b,0x00,0x00,0x1f,0xc0,0x00,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x1f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'E' */
0x08,0x7f,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x3e,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'F' */
0x08,0x00,0x00,0x7f,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x3e,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x60,0x00,0x00,0x00,
/* 'G' */
0x0a,0x00,0x00,0x00,0x00,0x1f,0x80,0x30,0x00,0x30,0x00,0x37,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x3f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'H' */
0x0b,0x00,0x00,0x71,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x3f,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x38,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'I' */
0x05,0x00,0x00,0x70,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'J' */
0x05,0x00,0x00,0x38,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x70,0x00,0x00,0x00,
/* 'K' */
0x0a,0x00,0x00,0x71,0xc0,0x31,0x80,0x31,0x80,0x31,0x80,0x3f,0x00,0x32,0x00,0x33,0x00,0x33,0x00,0x31,0x80,0x39,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'L' */
0x08,0x00,0x00,0x70,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'M' */
0x0f,0x7f,0xfc,0x31,0x8c,0x31,0x8c,0x31,0x8c,0x31,0x8c,0x31,0x8c,0x31,0x8c,0x31,0x8c,0x31,0x8c,0x39,0xce,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'N' */
0x0b,0x00,0x00,0x7f,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x38,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'O' */
0x0a,0x00,0x00,0x1f,0x80,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x3f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'P' */
0x09,0x7f,0x00,0x01,0x80,0x31,0x80,0x31,0x80,0x31,0x80,0x3f,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'Q' */
0x0a,0x00,0x00,0x1f,0x80,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x3f,0xc0,0x00,0xc0,0x00,0xc0,0x00,0xc0,0x00,0x00,
/* 'R' */
0x0a,0x00,0x00,0x7f,0x00,0x01,0x80,0x31,0x80,0x31,0x80,0x3f,0x00,0x36,0x00,0x33,0x00,0x33,0x00,0x31,0x80,0x39,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'S' */
0x08,0x00,0x00,0x1e,0x00,0x30,0x00,0x30,0x00,0x18,0x00,0x0c,0x00,0x0c,0x00,0x06,0x00,0x03,0x00,0x03,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'T' */
0x08,0x00,0x00,0x3f,0x00,0x4c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'U' */
0x0b,0x00,0x00,0x70,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x3f,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'V' */
0x0a,0x00,0x00,0x00,0x00,0x71,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x3f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'W' */
0x0e,0x00,0x00,0x73,0x9c,0x31,0x8c,0x31,0x8c,0x31,0x8c,0x31,0x8c,0x31,0x8c,0x31,0x8c,0x31,0x8c,0x31,0x8c,0x3f,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'X' */
0x0a,0x00,0x00,0x00,0x00,0x70,0x80,0x31,0x00,0x1a,0x00,0x0a,0x00,0x0c,0x00,0x0c,0x00,0x0e,0x00,0x13,0x00,0x23,0x00,0x21,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'Y' */
0x0a,0x00,0x00,0x70,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x3f,0xc0,0x00,0xc0,0x00,0xc0,0x3f,0x80,0x00,0x00,
/* 'Z' */
0x08,0x00,0x00,0x3f,0x00,0x03,0x00,0x06,0x00,0x06,0x00,0x0c,0x00,0x0c,0x00,0x18,0x00,0x38,0x00,0x30,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '[' */
0x05,0x38,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x38,0x00,0x00,0x00,0x00,0x00,
/* '\' */
0x06,0x60,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x18,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x0c,0x00,0x04,0x00,0x00,0x00,0x00,0x00,
/* ']' */
0x04,0x70,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x70,0x00,0x00,0x00,0x00,0x00,
/* '^' */
0x07,0x00,0x00,0x08,0x00,0x14,0x00,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '_' */
0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x00,
/* '`' */
0x04,0x00,0x00,0x60,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'a' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x00,0x03,0x00,0x03,0x00,0x3f,0x00,0x33,0x00,0x33,0x00,0x3f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'b' */
0x08,0x00,0x00,0x70,0x00,0x30,0x00,0x30,0x00,0x3f,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'c' */
0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x32,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'd' */
0x09,0x00,0x00,0x07,0x00,0x03,0x00,0x03,0x00,0x1f,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x3f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'e' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x33,0x00,0x33,0x00,0x3e,0x00,0x30,0x00,0x30,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'f' */
0x05,0x00,0x00,0x18,0x00,0x30,0x00,0x30,0x00,0x78,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x60,0x00,0x00,0x00,
/* 'g' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x3f,0x00,0x03,0x00,0x03,0x00,0x3e,0x00,
/* 'h' */
0x09,0x00,0x00,0x70,0x00,0x30,0x00,0x30,0x00,0x3f,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'i' */
0x05,0x30,0x00,0x30,0x00,0x00,0x00,0x70,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'j' */
0x04,0x30,0x00,0x30,0x00,0x00,0x00,0x70,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0xe0,0x00,0x00,0x00,0x00,0x00,
/* 'k' */
0x08,0x00,0x00,0x70,0x00,0x30,0x00,0x30,0x00,0x3e,0x00,0x33,0x00,0x33,0x00,0x3e,0x00,0x34,0x00,0x36,0x00,0x33,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'l' */
0x05,0x00,0x00,0x70,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'm' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0xf0,0x33,0x30,0x33,0x30,0x33,0x30,0x33,0x30,0x33,0x30,0x33,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'n' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'o' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'p' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x3e,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x00,0x00,
/* 'q' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x3f,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x00,0x00,
/* 'r' */
0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0x00,0x36,0x00,0x36,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 's' */
0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x60,0x00,0x30,0x00,0x30,0x00,0x18,0x00,0x0c,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 't' */
0x05,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x78,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'u' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x3f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'v' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'w' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x70,0x33,0x30,0x33,0x30,0x33,0x30,0x33,0x30,0x33,0x30,0x3f,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'x' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x72,0x00,0x34,0x00,0x1c,0x00,0x08,0x00,0x1c,0x00,0x26,0x00,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'y' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x3f,0x00,0x03,0x00,0x03,0x00,0x3e,0x00,
/* 'z' */
0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0x00,0x0c,0x00,0x18,0x00,0x10,0x00,0x30,0x00,0x60,0x00,0x7c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '{' */
0x05,0x18,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x60,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
/* '|' */
0x03,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00,0x00,0x00,
/* '}' */
0x06,0x30,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x0c,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x30,0x00,0x00,0x00,0x00,0x00,
/* '~' */
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x19,0x00,0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

LCDFONT Federant_10 = {
	2,			/* widthbytes */
	15,			/* fontheight */
	Federant_10_Table
};

/***** END OF FILE *****/
