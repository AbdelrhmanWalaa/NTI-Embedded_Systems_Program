/*
 * LCD_Interface.h
 *
 *   Created on: Apr 20, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Liquid Crystal Display (LCD) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *    Datasheet: https://datasheetspdf.com/pdf/746281/Topway/LMB161ABC-1/1
 *    Model No.: LMB161A - LCD
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* LCD Includes */

/* SRVL */
#include "../../SRVL/STD_TYPES/STD_TYPES.h"
#include "../../SRVL/BIT_MATH/BIT_MATH.h"
#include "../../SRVL/MCU_Config/MCU_Config.h"

/* MCAL */
#include "../../MCAL/DIO_Driver/DIO_Interface.h"

/*******************************************************************************************************************************************************************/
/* LCD Macros */

#define LCD_U8_FIRST_ELEMENT			0
#define LCD_U8_NUM_OF_DIGITS_OF_S64	    19

/* The LCD's DDRAM ( 80 locations ) is divided as the following:
 *
 * LCD Line1 ( 40 locations ): From location 0->39 ( Only 0->15 are displayed  )
 * Starting address of LCD Line1 : Dec.-> 0, Hex.-> 0x00
 *
 * LCD Line2 ( 40 locations ): From location 64->104 ( Only 64->79 are displayed  )
 * Starting address of LCD Line2 : Dec.-> 64, Hex.-> 0x40
 */
#define LCD_U8_LINE1			        1
#define LCD_U8_LINE2 		        	2

/* LCD Clear Display ( Cmnd ) */
#define LCD_U8_DISP_CLEAR 		        0b00000001

/* LCD Cursor States ( Cmnd ) */
#define LCD_U8_CURSOR_OFF		        0b00001100
#define LCD_U8_CURSOR_ON		        0b00001111

/* LCD total number of Characters to be displayed on each line */
#define LCD_U8_LINE_LOCATIONS	        39

/*******************************************************************************************************************************************************************/
/* LCD Functions' Prototypes */

vd LCD_vdInitialization  ( void );

vd LCD_vdSendCmnd	     ( u8 Cpy_u8Cmnd );
vd LCD_vdSendChar	     ( u8 Cpy_u8Char );

vd LCD_vdClearDisplay    ( void );

u8 LCD_u8GoToLocation    ( u8 Cpy_u8LineNumber, u8 Cpy_u8DisplayLocation );

u8 LCD_u8WriteString     ( u8 *Cpy_pu8String );
vd LCD_vdWriteNumber     ( s64 Cpy_s64Number );
u8 LCD_u8WriteSpecialChar( u8 Cpy_u8StoreLocation, u8 Cpy_u8LineNumber, u8 Cpy_u8DisplayLocation, u8 *Cpy_pu8SpecialChar );

/*******************************************************************************************************************************************************************/

#endif /* LCD_INTERFACE_H_ */