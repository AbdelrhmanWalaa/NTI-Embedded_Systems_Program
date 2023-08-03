/*
 * seg.c
 *
 * Created: 7/7/2021 10:05:50 AM
 *  Author: MahmoudH
 */ 
#include "seg.h"

const u8 numbers[] = {
	NUM_0, NUM_1, NUM_2, NUM_3,
	NUM_4, NUM_5, NUM_6, NUM_7,
	NUM_8, NUM_9, NUM_DOT
};

void Seg_Init(void){
	/* Out */
	setAllBits(SEG_DATA_DDR);
	setBits(SEG_DIG_DDR,SEG_DIG_MSK);
	/* Default */
	setAllBits(SEG_DATA_PORT);
	clearBits(SEG_DIG_PORT,SEG_DIG_MSK);
}
/* 
	Dig:		1-4
	Value:		0-9 and '.'
 */
void Seg_Display(u8 segDIG, u8 segValue){
	/* Select Digit to write */
	setBit(SEG_DIG_PORT, SEG_DIG_START_NUM + segDIG - 1);
	/* apply data value */
	if (segValue == '.')
	{
		SEG_DATA_PORT = numbers[10];
	}
	else{
		SEG_DATA_PORT = numbers[segValue];
	}
	/* wait for 1 ms */
	_delay_ms(1);
	/* UnSelect the Digit */	
	clearBit(SEG_DIG_PORT, SEG_DIG_START_NUM + segDIG - 1);	
}