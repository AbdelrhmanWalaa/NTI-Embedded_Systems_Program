/*
 * Ext_Int.h
 *
 * Created: 7/6/2021 1:45:36 PM
 *  Author: MahmoudH
 */ 


#ifndef EXT_INT_H_
#define EXT_INT_H_

#define F_CPU	8000000UL

#include <avr/io.h>
#include "BasicIO.h"
#include "util/delay.h"
#include "avr/interrupt.h"

typedef enum{
	EXT_INT0 = 6, EXT_INT1 = 7, EXT_INT2 = 5
}EXT_INT;

typedef enum{
	EDGE_RISING = 3, EDGE_FALLING = 2, EDGE_ANY_CHANGE = 1, EDGE_LOW_LEVEL = 0
}EDGE; 
void Ext_Int_Init(EXT_INT ext_int, EDGE edge, void (*pfApp)(void));

#endif /* EXT_INT_H_ */