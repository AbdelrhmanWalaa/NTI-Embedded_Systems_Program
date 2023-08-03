/*
 * BasicIO.c
 *
 * Created: 7/6/2021 11:02:01 AM
 *  Author: MahmoudH
 */ 
#include "BasicIO.h"
#include "bit_handle.h"

/* Leds */
void Led_Init(LED led){
	setBit(LEDS_DDR,led);	/* Out */
	Led_Off(led);			/* Default Off */
}
void Led_On(LED led){
	setBit(LEDS_PORT,led);
}
void Led_Off(LED led){
	clearBit(LEDS_PORT,led);
}
void Led_Toggle(LED led){
	toggleBit(LEDS_PORT,led);
}

void Leds_Init(u8 ledMask){
	LEDS_DDR |= ledMask;	/* Out */
	Leds_Off(ledMask);			/* Default Off */	
}
void Leds_On(u8 ledMask){
	LEDS_PORT |= ledMask;
}
void Leds_Off(u8 ledMask){
	LEDS_PORT &= ~ledMask;
}
void Leds_Toggle(u8 ledMask){
	LEDS_PORT ^= ledMask;
}

void Leds_AllInit(void){
	LEDS_DDR |= LEDS_MSK; /* Out */
	Leds_AllOff();
}
void Leds_AllOn(void){
	LEDS_PORT |= LEDS_MSK;
}
void Leds_AllOff(void){
	LEDS_PORT &= ~LEDS_MSK;
}
void Leds_AllToggle(void){
	LEDS_PORT ^= LEDS_MSK;
}

/* Buttons */
void Btn_Init(Button btn){
	BUTTONS_DDR  &= ~(1<<btn);	/* in */
	BUTTONS_PORT |=  (1<<btn);  /* Pullup */
}
Bool Btn_IsPressed(Button btn){
	return ( (BUTTONS_PINR&(1<<btn)) == 0 );
}

/* Buzzer */
void Buz_Init(void){
	BUZZER_DDR |= (1<<BUZZER_PIN);	/* Out */
	Buz_Off();						/* Default Off */	
}
void Buz_On(void){
	BUZZER_PORT |= (1<<BUZZER_PIN);
}
void Buz_Off(void){
	BUZZER_PORT &= ~(1<<BUZZER_PIN);
}
void Buz_Toggle(void){
	BUZZER_PORT ^= (1<<BUZZER_PIN);
}