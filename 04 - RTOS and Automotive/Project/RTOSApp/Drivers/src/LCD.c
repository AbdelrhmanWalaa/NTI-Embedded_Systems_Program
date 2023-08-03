/*
* LCD.c
*
* Created: 7/8/2021 11:04:59 AM
*  Author: MahmoudH
*/
#include "LCD.h"

/* Locals */
static void LCD_SendCMD(u8 u8CMD);
static void LCD_SendData(u8 u8Data);
static void LCD_GoToXY(u8 row, u8 col);
static void LCD_Latch(void);

/* Functions */
void LCD_Init(void){
	/* Out */
	setBits(LCD_DATA_DDR, LCD_DATA_MSK);
	setBit(LCD_CTRL_DDR, LCD_RS_PIN);
	setBit(LCD_CTRL_DDR, LCD_EN_PIN);
	_delay_ms(100);
	LCD_SendCMD(CMD_FUN_SET_4BIT);	/* Required: to set 4Bit operation */			
	LCD_SendCMD(CMD_CFG);			/* Full CFG */		
	LCD_SendCMD(CMD_DISP_ON);
	LCD_SendCMD(CMD_ENTRY_MODE);
	LCD_Clear();
}
void LCD_Clear(void){
	LCD_SendCMD(CMD_CLEAR);
	_delay_ms(5);
}
void LCD_DispChar(u8 u8Char){
	LCD_SendData(u8Char);
}
void LCD_DispStr(u8* pu8Str){
	u8 ind = 0;
	while(pu8Str[ind]){
		LCD_SendData(pu8Str[ind]);
		ind++;
	}
}
/* row: 1-2  - col: 1-16 */
void LCD_DispCharXY(u8 row, u8 col, u8 u8Char){
	LCD_GoToXY(row,col);
	LCD_DispChar(u8Char);
}
void LCD_DispStrXY(u8 row, u8 col, u8* pu8Str){
	LCD_GoToXY(row,col);
	LCD_DispStr(pu8Str);
}

static void LCD_SendCMD(u8 u8CMD){
	/* RS = 0 */
	clearBit(LCD_CTRL_PORT, LCD_RS_PIN);
	/* upload most 4 bits and then latch */
	LCD_DATA_REG.HN = (u8CMD>>4);
	LCD_Latch();
	/* upload least 4 bits and then latch */
	LCD_DATA_REG.HN = u8CMD;
	LCD_Latch();
	/* delay 40 us */
	_delay_us(40);
}
static void LCD_SendData(u8 u8Data){
	/* RS = 1 */
	setBit(LCD_CTRL_PORT, LCD_RS_PIN);
	/* upload most 4 bits and then latch */
	LCD_DATA_REG.HN = (u8Data>>4);
	LCD_Latch();
	/* upload least 4 bits and then latch */
	LCD_DATA_REG.HN = u8Data;
	LCD_Latch();
	/* delay 40 us */
	_delay_us(40);
}
static void LCD_GoToXY(u8 row, u8 col){
	if (row == 1)
	{
		LCD_SendCMD((0x00|0x80) + col -1);
	}
	else
	{
		LCD_SendCMD((0x40|0x80) + col -1);
	}
}
static void LCD_Latch(void){
	setBit(LCD_CTRL_PORT, LCD_EN_PIN);
	clearBit(LCD_CTRL_PORT, LCD_EN_PIN);
}
void LCD_DispInt(u32 data){
	u8 dataStr[11] = {0};
	itoa(data,dataStr,10);
	LCD_DispStr(dataStr);
}
void LCD_DispIntXY(u8 row, u8 col, u32 data){
	LCD_GoToXY(row,col);
	LCD_DispInt(data);
}
