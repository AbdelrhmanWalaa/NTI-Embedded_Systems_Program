/*
 * TWI.c
 *
 * Created: 7/25/2021 1:27:20 PM
 *  Author: MahmoudH
 */ 
#include "TWI.h"

static void TWI_Wait(void);


void TWI_Init(u32 scl){
	TWBR = ((F_CPU/scl) - 16)/2;
	TWCR |= (1<<TWEN);
}
Bool TWI_Start(void){
	Bool result = FALSE;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	TWI_Wait();
	if((TWSR&0xF8) == SC_START){
		result = TRUE;
	}
	return result;
}
Bool TWI_Restart(void){
	Bool result = FALSE;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	TWI_Wait();
	if((TWSR&0xF8) == SC_RESTART){
		result = TRUE;
	}
	return result;	
}
void TWI_Stop(void){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
static void TWI_Wait(void){
	while( !(TWCR&(1<<TWINT)) );
}

Bool TWI_Write(u8 u8Byte, u8 sCode){
	Bool result = FALSE;
	TWDR = u8Byte;
	TWCR = (1<<TWINT) | (1<<TWEN);
	TWI_Wait();
	if((TWSR&0xF8) == sCode){
		result = TRUE;
	}
	return result;
}
Bool TWI_Read(u8* pu8Byte, u8 sCode){
	Bool result = FALSE;
	TWCR = (1<<TWINT) | (1<<TWEN);
	if((TWSR&0xF8) == SC_MR_DATA_ACK){
		TWCR |= (1<<TWEA);
	}
	TWI_Wait();
	if((TWSR&0xF8) == sCode){
		(*pu8Byte) = TWDR;
		result = TRUE;
	}
	return result;
}