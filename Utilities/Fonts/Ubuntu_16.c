/*******************************************************************************
 * @file	Ubuntu_16.c
 * @author	Brian
 * @version	V0.1.0
 * @date	21-Oct-2011
 * @brief	Ubuntu 16 point (21x21)
 */

#include "lcdfonts.h"

const uint8_t Ubuntu_16_Table [] = {

/* ' ' */
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '!' */
0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '"' */
0x09,0x19,0x80,0x00,0x19,0x80,0x00,0x19,0x80,0x00,0x19,0x80,0x00,0x19,0x80,0x00,0x19,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '#' */
0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0c,0x00,0x03,0x0c,0x00,0x03,0x1c,0x00,0x06,0x18,0x00,0x3f,0xfe,0x00,0x3f,0xfe,0x00,0x06,0x18,0x00,0x0e,0x38,0x00,0x0c,0x30,0x00,0x3f,0xfe,0x00,0x3f,0xfe,0x00,0x0c,0x30,0x00,0x1c,0x60,0x00,0x18,0x60,0x00,0x18,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '$' */
0x0c,0x03,0x00,0x00,0x03,0x00,0x00,0x0f,0xe0,0x00,0x1f,0xe0,0x00,0x38,0x20,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x38,0x00,0x00,0x1e,0x00,0x00,0x07,0x80,0x00,0x01,0xe0,0x00,0x00,0x70,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x20,0x70,0x00,0x3f,0xe0,0x00,0x1f,0xc0,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,
/* '%' */
0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x03,0x00,0x1f,0x86,0x00,0x39,0xce,0x00,0x30,0xcc,0x00,0x30,0xd8,0x00,0x30,0xd8,0x00,0x39,0xf7,0x80,0x1f,0xff,0xc0,0x0f,0x7c,0xe0,0x00,0xd8,0x60,0x00,0xd8,0x60,0x01,0x98,0x60,0x03,0x9c,0xe0,0x03,0x0f,0xc0,0x06,0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '&' */
0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x07,0xe0,0x00,0x0e,0x30,0x00,0x0c,0x30,0x00,0x0c,0x30,0x00,0x0e,0x60,0x00,0x07,0xc0,0x00,0x07,0x00,0x00,0x1d,0x86,0x00,0x38,0xc6,0x00,0x30,0x6c,0x00,0x30,0x38,0x00,0x38,0x18,0x00,0x1f,0xfc,0x00,0x0f,0xc6,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ''' */
0x05,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '(' */
0x08,0x01,0x00,0x00,0x03,0x00,0x00,0x06,0x00,0x00,0x04,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x08,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x08,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x04,0x00,0x00,0x06,0x00,0x00,0x03,0x00,0x00,0x01,0x00,0x00,
/* ')' */
0x07,0x40,0x00,0x00,0x60,0x00,0x00,0x30,0x00,0x00,0x10,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x08,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x08,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x10,0x00,0x00,0x30,0x00,0x00,0x60,0x00,0x00,0x40,0x00,0x00,
/* '*' */
0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x32,0x60,0x00,0x3f,0xe0,0x00,0x02,0x00,0x00,0x0d,0x80,0x00,0x1d,0xc0,0x00,0x08,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '+' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x3f,0xf0,0x00,0x3f,0xf0,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ',' */
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x10,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,
/* '-' */
0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x00,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '.' */
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '/' */
0x0a,0x00,0xc0,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0xc0,0x00,0x00,
/* '0' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x00,0x0f,0xc0,0x00,0x1c,0xe0,0x00,0x18,0x60,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x18,0x60,0x00,0x1c,0xe0,0x00,0x0f,0xc0,0x00,0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '1' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x00,0x03,0x80,0x00,0x0f,0x80,0x00,0x1f,0x80,0x00,0x19,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '2' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x00,0x1f,0xc0,0x00,0x18,0xe0,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0xc0,0x00,0x01,0xc0,0x00,0x03,0x80,0x00,0x07,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x18,0x00,0x00,0x1f,0xf0,0x00,0x1f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '3' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x00,0x00,0x3f,0x80,0x00,0x11,0xc0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x01,0xc0,0x00,0x07,0x80,0x00,0x07,0x80,0x00,0x00,0xc0,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x20,0xe0,0x00,0x3f,0xc0,0x00,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '4' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0x01,0xc0,0x00,0x03,0xc0,0x00,0x07,0xc0,0x00,0x06,0xc0,0x00,0x0c,0xc0,0x00,0x18,0xc0,0x00,0x18,0xc0,0x00,0x30,0xc0,0x00,0x3f,0xf0,0x00,0x3f,0xf0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '5' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0xc0,0x00,0x0f,0xc0,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x1f,0x00,0x00,0x1f,0xc0,0x00,0x01,0xc0,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x20,0xe0,0x00,0x3f,0xc0,0x00,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '6' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xe0,0x00,0x07,0xe0,0x00,0x0e,0x00,0x00,0x1c,0x00,0x00,0x18,0x00,0x00,0x37,0xc0,0x00,0x3f,0xe0,0x00,0x30,0x70,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x38,0x30,0x00,0x18,0x60,0x00,0x1f,0xe0,0x00,0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '7' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xf0,0x00,0x3f,0xf0,0x00,0x00,0x20,0x00,0x00,0x60,0x00,0x00,0xc0,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '8' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xc0,0x00,0x1f,0xe0,0x00,0x38,0x70,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x3c,0x60,0x00,0x1e,0xe0,0x00,0x07,0x80,0x00,0x1d,0xe0,0x00,0x10,0x70,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x38,0x70,0x00,0x1f,0xe0,0x00,0x0f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '9' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x00,0x1f,0xe0,0x00,0x18,0x60,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x38,0x30,0x00,0x1f,0xf0,0x00,0x0f,0xf0,0x00,0x00,0x70,0x00,0x00,0x60,0x00,0x00,0xe0,0x00,0x03,0xc0,0x00,0x1f,0x80,0x00,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ':' */
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ';' */
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x10,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,
/* '<' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x01,0xf0,0x00,0x0f,0xc0,0x00,0x3e,0x00,0x00,0x30,0x00,0x00,0x3e,0x00,0x00,0x0f,0xc0,0x00,0x01,0xf0,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '=' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xf0,0x00,0x3f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xf0,0x00,0x3f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '>' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x1e,0x00,0x00,0x0f,0xc0,0x00,0x01,0xf0,0x00,0x00,0x30,0x00,0x01,0xf0,0x00,0x0f,0xc0,0x00,0x1e,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '?' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x00,0x3f,0x80,0x00,0x23,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x03,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '@' */
0x15,0x00,0x00,0x00,0x00,0xfe,0x00,0x03,0xff,0x80,0x07,0x81,0xc0,0x0e,0x00,0x60,0x1c,0x00,0x30,0x18,0x3f,0x30,0x38,0xff,0x18,0x30,0xc3,0x18,0x31,0x83,0x18,0x31,0x83,0x18,0x31,0x83,0x18,0x31,0x83,0x18,0x30,0xc3,0x30,0x38,0xff,0xf0,0x18,0x3d,0xe0,0x1c,0x00,0x00,0x0e,0x00,0x00,0x07,0x80,0x00,0x03,0xff,0x00,0x00,0x7f,0x00,
/* 'A' */
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xc0,0x00,0x01,0xc0,0x00,0x03,0x60,0x00,0x03,0x60,0x00,0x06,0x30,0x00,0x06,0x30,0x00,0x06,0x30,0x00,0x0c,0x18,0x00,0x0c,0x18,0x00,0x1f,0xfc,0x00,0x1f,0xfc,0x00,0x38,0x0e,0x00,0x30,0x06,0x00,0x30,0x06,0x00,0x60,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'B' */
0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xe0,0x00,0x1f,0xf0,0x00,0x18,0x38,0x00,0x18,0x18,0x00,0x18,0x18,0x00,0x18,0x38,0x00,0x1f,0xe0,0x00,0x1f,0xf0,0x00,0x18,0x1c,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x18,0x1c,0x00,0x1f,0xf8,0x00,0x1f,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'C' */
0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xf8,0x00,0x07,0xfc,0x00,0x0e,0x0c,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x38,0x00,0x00,0x18,0x00,0x00,0x0e,0x04,0x00,0x07,0xfc,0x00,0x03,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'D' */
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xe0,0x00,0x1f,0xf8,0x00,0x18,0x1c,0x00,0x18,0x0e,0x00,0x18,0x06,0x00,0x18,0x03,0x00,0x18,0x03,0x00,0x18,0x03,0x00,0x18,0x03,0x00,0x18,0x03,0x00,0x18,0x06,0x00,0x18,0x0e,0x00,0x18,0x1c,0x00,0x1f,0xf8,0x00,0x1f,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'E' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xf0,0x00,0x1f,0xf0,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x1f,0xf0,0x00,0x1f,0xf0,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x1f,0xf8,0x00,0x1f,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'F' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xf0,0x00,0x1f,0xf0,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x1f,0xe0,0x00,0x1f,0xe0,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'G' */
0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xf8,0x00,0x07,0xfc,0x00,0x0e,0x08,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x0c,0x00,0x30,0x0c,0x00,0x38,0x0c,0x00,0x18,0x0c,0x00,0x1e,0x0c,0x00,0x0f,0xfc,0x00,0x03,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'H' */
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x06,0x00,0x18,0x06,0x00,0x18,0x06,0x00,0x18,0x06,0x00,0x18,0x06,0x00,0x18,0x06,0x00,0x1f,0xfe,0x00,0x1f,0xfe,0x00,0x18,0x06,0x00,0x18,0x06,0x00,0x18,0x06,0x00,0x18,0x06,0x00,0x18,0x06,0x00,0x18,0x06,0x00,0x18,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'I' */
0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'J' */
0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x00,0xc0,0x00,0x21,0xc0,0x00,0x7f,0x80,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'K' */
0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x1c,0x00,0x18,0x38,0x00,0x18,0x70,0x00,0x18,0xe0,0x00,0x19,0xc0,0x00,0x1b,0x80,0x00,0x1f,0x00,0x00,0x1e,0x00,0x00,0x1f,0x80,0x00,0x1b,0xc0,0x00,0x19,0xe0,0x00,0x18,0x70,0x00,0x18,0x38,0x00,0x18,0x1c,0x00,0x18,0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'L' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x1f,0xf0,0x00,0x1f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'M' */
0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x01,0x80,0x1c,0x03,0x80,0x1c,0x03,0x80,0x1e,0x07,0x80,0x1e,0x07,0x80,0x1b,0x0d,0x80,0x3b,0x0d,0xc0,0x31,0x98,0xc0,0x31,0x98,0xc0,0x30,0x90,0xc0,0x30,0xf0,0xc0,0x30,0xf0,0xc0,0x30,0x60,0xc0,0x30,0x00,0xc0,0x30,0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'N' */
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x06,0x00,0x1c,0x06,0x00,0x1e,0x06,0x00,0x1f,0x06,0x00,0x1b,0x06,0x00,0x19,0x86,0x00,0x18,0xc6,0x00,0x18,0xe6,0x00,0x18,0x66,0x00,0x18,0x36,0x00,0x18,0x1e,0x00,0x18,0x1e,0x00,0x18,0x0e,0x00,0x18,0x06,0x00,0x18,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'O' */
0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xf0,0x00,0x07,0xfc,0x00,0x0e,0x0e,0x00,0x18,0x03,0x00,0x18,0x03,0x00,0x30,0x01,0x80,0x30,0x01,0x80,0x30,0x01,0x80,0x30,0x01,0x80,0x30,0x01,0x80,0x18,0x03,0x00,0x18,0x03,0x00,0x0e,0x0e,0x00,0x07,0xfc,0x00,0x01,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'P' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xc0,0x00,0x1f,0xf0,0x00,0x18,0x38,0x00,0x18,0x18,0x00,0x18,0x18,0x00,0x18,0x18,0x00,0x18,0x38,0x00,0x1f,0xf0,0x00,0x1f,0xc0,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'Q' */
0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xf0,0x00,0x07,0xfc,0x00,0x0e,0x0e,0x00,0x18,0x03,0x00,0x18,0x03,0x00,0x30,0x01,0x80,0x30,0x01,0x80,0x30,0x01,0x80,0x30,0x01,0x80,0x30,0x01,0x80,0x18,0x03,0x00,0x18,0x03,0x00,0x0e,0x0e,0x00,0x07,0xfc,0x00,0x01,0xf0,0x00,0x00,0x60,0x00,0x00,0x38,0x00,0x00,0x1e,0x00,0x00,0x06,0x00,
/* 'R' */
0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xe0,0x00,0x1f,0xf8,0x00,0x18,0x1c,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x18,0x1c,0x00,0x1f,0xf8,0x00,0x1f,0xe0,0x00,0x18,0x70,0x00,0x18,0x30,0x00,0x18,0x18,0x00,0x18,0x1c,0x00,0x18,0x0e,0x00,0x18,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'S' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0xc0,0x00,0x1f,0xe0,0x00,0x38,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x38,0x00,0x00,0x1e,0x00,0x00,0x0f,0xc0,0x00,0x01,0xe0,0x00,0x00,0x70,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x30,0x70,0x00,0x3f,0xe0,0x00,0x1f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'T' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0xf8,0x00,0x7f,0xf8,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'U' */
0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x18,0x0c,0x00,0x1c,0x1c,0x00,0x0e,0x38,0x00,0x0f,0xf8,0x00,0x03,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'V' */
0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x0c,0x00,0x70,0x18,0x00,0x30,0x18,0x00,0x30,0x18,0x00,0x38,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x0c,0x60,0x00,0x0c,0x60,0x00,0x0c,0xc0,0x00,0x06,0xc0,0x00,0x07,0xc0,0x00,0x07,0x80,0x00,0x03,0x80,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'W' */
0x15,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x38,0x18,0x18,0x38,0x30,0x18,0x38,0x30,0x18,0x6c,0x30,0x18,0x6c,0x30,0x18,0x6c,0x30,0x1c,0xc6,0x70,0x0c,0xc6,0x60,0x0d,0x83,0x60,0x0d,0x83,0x60,0x0f,0x83,0xe0,0x07,0x01,0xc0,0x07,0x01,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'X' */
0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x0e,0x00,0x18,0x0c,0x00,0x0c,0x18,0x00,0x06,0x30,0x00,0x06,0x30,0x00,0x03,0x60,0x00,0x01,0xc0,0x00,0x01,0xc0,0x00,0x01,0xc0,0x00,0x03,0x60,0x00,0x06,0x30,0x00,0x0e,0x38,0x00,0x0c,0x18,0x00,0x18,0x0c,0x00,0x38,0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'Y' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x18,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x18,0x60,0x00,0x1c,0xe0,0x00,0x0c,0xc0,0x00,0x07,0x80,0x00,0x07,0x80,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'Z' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xf8,0x00,0x3f,0xf8,0x00,0x00,0x38,0x00,0x00,0x70,0x00,0x00,0xe0,0x00,0x00,0xc0,0x00,0x01,0x80,0x00,0x03,0x00,0x00,0x07,0x00,0x00,0x0e,0x00,0x00,0x0c,0x00,0x00,0x18,0x00,0x00,0x38,0x00,0x00,0x3f,0xf8,0x00,0x3f,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '[' */
0x08,0x1f,0x00,0x00,0x1f,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x1f,0x00,0x00,0x1f,0x00,0x00,
/* '\' */
0x0a,0xc0,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x00,0xc0,0x00,
/* ']' */
0x07,0x7c,0x00,0x00,0x7c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x7c,0x00,0x00,0x7c,0x00,0x00,
/* '^' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x03,0x80,0x00,0x06,0xc0,0x00,0x06,0xc0,0x00,0x0c,0x60,0x00,0x18,0x30,0x00,0x38,0x38,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '_' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0xf0,0x00,0x7f,0xf0,0x00,
/* '`' */
0x08,0x10,0x00,0x00,0x38,0x00,0x00,0x1c,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'a' */
0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x00,0x00,0x1f,0x80,0x00,0x01,0xc0,0x00,0x00,0xc0,0x00,0x0f,0xc0,0x00,0x1f,0xc0,0x00,0x38,0xc0,0x00,0x30,0xc0,0x00,0x30,0xc0,0x00,0x38,0xc0,0x00,0x1f,0xc0,0x00,0x0f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'b' */
0x0d,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x1b,0xc0,0x00,0x1f,0xf0,0x00,0x1c,0x30,0x00,0x18,0x38,0x00,0x18,0x18,0x00,0x18,0x18,0x00,0x18,0x18,0x00,0x18,0x18,0x00,0x18,0x38,0x00,0x18,0x70,0x00,0x1f,0xe0,0x00,0x1f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'c' */
0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xe0,0x00,0x0f,0xe0,0x00,0x1c,0x00,0x00,0x38,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x38,0x00,0x00,0x1c,0x00,0x00,0x0f,0xe0,0x00,0x07,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'd' */
0x0d,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x07,0xb0,0x00,0x1f,0xf0,0x00,0x18,0x70,0x00,0x38,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x38,0x30,0x00,0x1c,0x30,0x00,0x0f,0xf0,0x00,0x07,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'e' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xc0,0x00,0x0f,0xe0,0x00,0x18,0x60,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x3f,0xf0,0x00,0x3f,0xf0,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x18,0x00,0x00,0x0f,0xe0,0x00,0x07,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'f' */
0x09,0x07,0x80,0x00,0x0f,0x80,0x00,0x1c,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x1f,0x80,0x00,0x1f,0x80,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'g' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xf0,0x00,0x0f,0xf0,0x00,0x1c,0x30,0x00,0x38,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x38,0x30,0x00,0x1c,0x30,0x00,0x1f,0xf0,0x00,0x07,0xf0,0x00,0x00,0x30,0x00,0x10,0x70,0x00,0x1f,0xe0,0x00,0x1f,0xc0,0x00,
/* 'h' */
0x0d,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x1f,0xc0,0x00,0x1f,0xe0,0x00,0x18,0x70,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'i' */
0x06,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'j' */
0x06,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x38,0x00,0x00,0xf0,0x00,0x00,0xe0,0x00,0x00,
/* 'k' */
0x0c,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x70,0x00,0x18,0xe0,0x00,0x19,0xc0,0x00,0x1b,0x80,0x00,0x1f,0x00,0x00,0x1f,0x00,0x00,0x1f,0x80,0x00,0x1b,0x80,0x00,0x19,0xc0,0x00,0x18,0xe0,0x00,0x18,0x60,0x00,0x18,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'l' */
0x07,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x1e,0x00,0x00,0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'm' */
0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xcf,0x80,0x1f,0xff,0xc0,0x18,0x70,0xe0,0x18,0x30,0x60,0x18,0x30,0x60,0x18,0x30,0x60,0x18,0x30,0x60,0x18,0x30,0x60,0x18,0x30,0x60,0x18,0x30,0x60,0x18,0x30,0x60,0x18,0x30,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'n' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xc0,0x00,0x1f,0xe0,0x00,0x18,0x70,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'o' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xc0,0x00,0x0f,0xe0,0x00,0x1c,0x70,0x00,0x38,0x38,0x00,0x30,0x18,0x00,0x30,0x18,0x00,0x30,0x18,0x00,0x30,0x18,0x00,0x38,0x38,0x00,0x1c,0x70,0x00,0x0f,0xe0,0x00,0x07,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'p' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xc0,0x00,0x1f,0xe0,0x00,0x18,0x70,0x00,0x18,0x38,0x00,0x18,0x18,0x00,0x18,0x18,0x00,0x18,0x18,0x00,0x18,0x18,0x00,0x18,0x38,0x00,0x1c,0x30,0x00,0x1f,0xf0,0x00,0x1b,0xc0,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,
/* 'q' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xf0,0x00,0x0f,0xf0,0x00,0x1c,0x30,0x00,0x38,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x38,0x30,0x00,0x18,0x70,0x00,0x1f,0xf0,0x00,0x07,0xb0,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,
/* 'r' */
0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x80,0x00,0x1f,0x80,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 's' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x80,0x00,0x1f,0x80,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x38,0x00,0x00,0x1f,0x00,0x00,0x0f,0x80,0x00,0x01,0xc0,0x00,0x00,0xc0,0x00,0x20,0xc0,0x00,0x3f,0x80,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 't' */
0x09,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x1f,0x80,0x00,0x1f,0x80,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x0f,0x80,0x00,0x0f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'u' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x18,0x30,0x00,0x1c,0x30,0x00,0x0f,0xf0,0x00,0x07,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'v' */
0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x60,0x60,0x00,0x30,0xc0,0x00,0x30,0xc0,0x00,0x30,0xc0,0x00,0x19,0x80,0x00,0x19,0x80,0x00,0x19,0x80,0x00,0x0f,0x00,0x00,0x0f,0x00,0x00,0x0f,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'w' */
0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0xc0,0x60,0x60,0xc0,0x30,0xe1,0x80,0x30,0xe1,0x80,0x30,0xb1,0x80,0x31,0xb1,0x80,0x19,0xb3,0x00,0x1b,0x1b,0x00,0x1b,0x1b,0x00,0x0e,0x1e,0x00,0x0e,0x0e,0x00,0x0e,0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'x' */
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x70,0x00,0x30,0x60,0x00,0x18,0xc0,0x00,0x0d,0x80,0x00,0x0f,0x80,0x00,0x07,0x00,0x00,0x07,0x00,0x00,0x0f,0x80,0x00,0x1d,0xc0,0x00,0x18,0xc0,0x00,0x30,0x60,0x00,0x70,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 'y' */
0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x30,0x60,0x00,0x30,0xc0,0x00,0x30,0xc0,0x00,0x18,0xc0,0x00,0x19,0x80,0x00,0x19,0x80,0x00,0x0d,0x80,0x00,0x0d,0x80,0x00,0x0f,0x00,0x00,0x07,0x00,0x00,0x07,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x7c,0x00,0x00,0x78,0x00,0x00,
/* 'z' */
0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xc0,0x00,0x3f,0xc0,0x00,0x01,0xc0,0x00,0x01,0x80,0x00,0x03,0x00,0x00,0x06,0x00,0x00,0x0e,0x00,0x00,0x0c,0x00,0x00,0x18,0x00,0x00,0x38,0x00,0x00,0x3f,0xc0,0x00,0x3f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* '{' */
0x08,0x07,0x00,0x00,0x0f,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x1c,0x00,0x00,0x38,0x00,0x00,0x3c,0x00,0x00,0x1c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x0f,0x00,0x00,0x07,0x00,0x00,
/* '|' */
0x06,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,
/* '}' */
0x07,0x70,0x00,0x00,0x78,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x1c,0x00,0x00,0x0e,0x00,0x00,0x1e,0x00,0x00,0x1c,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x78,0x00,0x00,0x70,0x00,0x00,
/* '~' */
0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0x18,0x00,0x1f,0x38,0x00,0x39,0xf0,0x00,0x30,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

LCDFONT Ubuntu_16 = {
	3,			/* widthbytes */
	21,			/* fontheight */
	Ubuntu_16_Table
};

/***** END OF FILE *****/
