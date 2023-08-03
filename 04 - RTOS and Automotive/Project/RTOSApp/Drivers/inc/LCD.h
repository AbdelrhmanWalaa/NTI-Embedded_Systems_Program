/*
 * LCD.h
 *
 * Created: 7/8/2021 11:04:45 AM
 *  Author: MahmoudH
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "bit_handle.h"
#include "data_types.h"
#include "stdlib.h"

/* CFG Start */
#define LCD_DATA_PORT			PORTC
#define LCD_DATA_DDR			DDRC
#define LCD_DATA_MSK			0xF0

#define LCD_CTRL_PORT			PORTB
#define LCD_CTRL_DDR			DDRB
#define LCD_EN_PIN				PB0
#define LCD_RS_PIN				PB1
/* CFG End */

/* Commands */
#define CMD_CLEAR				0x01
#define CMD_ENTRY_MODE			0x06
#define CMD_DISP_ON				0x0C
#define CMD_CFG					0x28
#define CMD_FUN_SET_4BIT		0x02

typedef struct{
	u8 :4;
	u8 HN:4;
}LCD_DATA_Struct;

#define LCD_DATA_REG		(*((volatile LCD_DATA_Struct*)(&LCD_DATA_PORT)))

/* Functions */
void LCD_Init(void);
void LCD_Clear(void);
void LCD_DispChar(u8 u8Char);
void LCD_DispStr(u8* pu8Str);
/* row: 1-2  - col: 1-16 */
void LCD_DispCharXY(u8 row, u8 col, u8 u8Char);
void LCD_DispStrXY(u8 row, u8 col, u8* pu8Str);
void LCD_DispInt(u32 data);
void LCD_DispIntXY(u8 row, u8 col, u32 data);


#endif /* LCD_H_ */
