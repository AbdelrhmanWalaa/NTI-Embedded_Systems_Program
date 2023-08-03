/*
 * LCD_Private.h
 *
 *   Created on: Apr 20, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Liquid Crystal Display (LCD) important locations and commands.
 *    Datasheet: https://datasheetspdf.com/pdf/746281/Topway/LMB161ABC-1/1
 *    Model No.: LMB161A - LCD
 */

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* LCD Important Locations */

/* Set DDRAM address in address counter:
 *
 * Command: Bin. -> ( 0b1 + location ), Hex. -> ( 0x80 + location )
 * LCD Line1: 0x80 + 0x00 = 0x80
 * LCD Line2: 0x80 + 0x40 = 0xC0
 */
#define LCD_U8_LOC_SET_TO_LINE1			0x80
#define LCD_U8_LOC_SET_TO_LINE2			0xC0

/*******************************************************************************************************************************************************************/

#endif /* LCD_PRIVATE_H_ */