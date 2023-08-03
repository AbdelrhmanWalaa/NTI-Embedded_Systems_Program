/*
* Ext_int.c
*
* Created: 7/6/2021 1:46:13 PM
*  Author: MahmoudH
*/
#include "Ext_Int.h"

void (*callbacks[3])(void);

void Ext_Int_Init(EXT_INT ext_int, EDGE edge,void (*pfApp)(void)){
	/* Configure Ext Int */
	switch (ext_int)
	{
		case EXT_INT0:
		MCUCR	&= ~0b00000011;
		MCUCR	|=  edge;
		callbacks[0] = pfApp;
		GICR	|= (1<<INT0);
		break;
		case EXT_INT1:
		MCUCR	&= ~0b00001100;
		MCUCR	|=  (edge<<2);
		callbacks[1] = pfApp;
		GICR	|= (1<<INT1);
		break;
		case EXT_INT2:
		if (edge == EDGE_RISING)
		{
			MCUCSR |= (1<<ISC2);
		}else if (edge == EDGE_FALLING){
			MCUCSR &= ~(1<<ISC2);			
		}
		else{
			return;
		}
		callbacks[2] = pfApp;
		GICR	|= (1<<INT2);
		break;
	}	
	sei();	
}

ISR(INT0_vect){
	callbacks[0]();
}
ISR(INT1_vect){
	callbacks[1]();
}
ISR(INT2_vect){
	callbacks[2]();
}