/*
 * timer.h
 *
 * Created: 7/12/2021 1:12:48 PM
 *  Author: MahmoudH
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "bit_handle.h"
#include "data_types.h"

typedef enum{
	TM_NORMAL,TM_CTC,TM_PHASE_PWM,TM_FAST_PWM
}Timer_Mode;

/* Tick in 1us */
void Timer_Init(Timer_Mode mode);
void Timer_Start(void);
void Timer_Stop(void);
void Timer_ResetCounters(void);

void Timer_DelayUS(u32 delay);
void Timer_DelayMS(u32 delay);

/* Set, inc, dec */
void Timer_SetDuty(u8 duty);
void Timer_DecDuty(u8 duty);
void Timer_IncDuty(u8 duty);

void Timer_SetNotif(void (*pfNotify)(void),u32 notifyTime);
#endif /* TIMER_H_ */