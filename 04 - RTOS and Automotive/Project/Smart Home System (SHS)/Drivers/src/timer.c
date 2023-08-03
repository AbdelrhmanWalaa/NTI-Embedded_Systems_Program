/*
* timer.c
*
* Created: 7/12/2021 1:13:04 PM
*  Author: MahmoudH
*/
#include "timer.h"

volatile static u32 overflows = 0;
volatile static u32 calcOverflows = 0;
void (*volatile notifier)(void);

/* Tick in 1us */
void Timer_Init(Timer_Mode mode){
	Timer_Stop();
	switch(mode){
		case TM_NORMAL:
		clearBit(TCCR0,WGM00);
		clearBit(TCCR0,WGM01);
		setBit(TIMSK,TOIE0); /* enable timer0 overflow int */
		sei();
		break;
		case TM_CTC:
		clearBit(TCCR0,WGM00);
		setBit(TCCR0,WGM01);
		/* Toggle OC0 pin */
		setBit(TCCR0,COM00);
		clearBit(TCCR0,COM01);
		/* OC0 Pin Out */
		setBit(DDRB,PB3);
		/* Set OCR */
		OCR0 = 127;
		Timer_Start();
		break;
		case TM_PHASE_PWM:
		setBit(TCCR0,WGM00);
		clearBit(TCCR0,WGM01);
		/* clear OC0 pin at upcount  match and set on downcount match*/
		clearBit(TCCR0,COM00);
		setBit(TCCR0,COM01);
		/* OC0 Pin Out */
		setBit(DDRB,PB3);
		/* Set OCR */
		OCR0 = 127;
		Timer_Start();
		break;
		case TM_FAST_PWM:
		setBit(TCCR0,WGM00);
		setBit(TCCR0,WGM01);
		/* set OC0 pin at bot and clear on match*/
		clearBit(TCCR0,COM00);
		setBit(TCCR0,COM01);
		/* OC0 Pin Out */
		setBit(DDRB,PB3);
		/* Set OCR */
		OCR0 = 127;
		Timer_Start();
		break;
		default:
		break;
	}
}
void Timer_Start(void){
	clearBits(TCCR0,((1<<CS00)|(1<<CS02)));
	setBit(TCCR0,CS01);
}
void Timer_Stop(void){
	clearBits(TCCR0,((1<<CS00)|(1<<CS01)|(1<<CS02)));
}
void Timer_ResetCounters(void){
	overflows	= 0;
	TCNT0		= 0;
}

void Timer_DelayUS(u32 delay){
	Timer_Stop();
	Timer_ResetCounters();
	Timer_Start();
	while( (overflows*256UL+ TCNT0 + 1) < (delay) );
}
void Timer_DelayMS(u32 delay){
	Timer_Stop();
	Timer_ResetCounters();
	Timer_Start();
	while( (overflows*256UL+ TCNT0 + 1) < (delay*1000UL) );
}
void Timer_SetDuty(u8 duty){
	if (duty >= 100)
	{
		OCR0 = 0xFF;
	}
	else{
		OCR0 = (0xFFUL*duty)/100;
	}
}
void Timer_DecDuty(u8 duty){
	if(OCR0 >= 0xFF*(duty/100.0)){
		OCR0 -= 0xFF*(duty/100.0);
	}
	else{
		OCR0 = 0x00;
	}
}
void Timer_IncDuty(u8 duty){
	if(OCR0 + 0xFF*(duty/100.0) <= 0xFF){
		OCR0 += 0xFF*(duty/100.0);
		}else{
		OCR0 = 0xFF;
	}
}

void Timer_SetNotif(void (*pfNotify)(void),u32 notifyTime){
	Timer_Init(TM_NORMAL);
	notifier = pfNotify;
	//TCNT0 = 256 - ((notifyTime*1000UL)%256 -1);
	overflows = 0;
	calcOverflows = (notifyTime*1000UL)/256;// +1;
	Timer_Start();
}


ISR(TIMER0_OVF_vect){
	overflows++;
	if(overflows == calcOverflows){
		notifier();
		Timer_Stop();
	}
}