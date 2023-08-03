/*
 * seg.h
 *
 * Created: 7/7/2021 10:05:35 AM
 *  Author: MahmoudH
 */ 


#ifndef SEG_H_
#define SEG_H_

#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "bit_handle.h"
#include "data_types.h"

/* Common Anode 7Seg with 4-Digits */
/* CFG Start */
#define SEG_DATA_PORT		PORTB
#define SEG_DATA_DDR		DDRB

#define SEG_DIG_PORT		PORTC
#define SEG_DIG_DDR			DDRC
#define SEG_DIG_MSK			0xF0
#define SEG_DIG_START_NUM	4

#define NUM_0				0xC0
#define NUM_1				0xF9
#define NUM_2				0xA4
#define NUM_3				0xB0
#define NUM_4				0x99
#define NUM_5				0x92
#define NUM_6				0x82
#define NUM_7				0xF8
#define NUM_8				0x80
#define NUM_9				0x90
#define NUM_DOT				0x7F

/* CFG End */

void Seg_Init(void);
void Seg_Display(u8 segDIG, u8 segValue);

#endif /* SEG_H_ */