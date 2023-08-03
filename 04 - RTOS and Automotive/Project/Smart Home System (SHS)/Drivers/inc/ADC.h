/*
 * ADC.h
 *
 * Created: 7/11/2021 2:11:37 PM
 *  Author: MahmoudH
 */ 


#ifndef ADC_H_
#define ADC_H_

#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "bit_handle.h"
#include "data_types.h"

typedef enum{
	ADC_PRESC_2 = 1,
	ADC_PRESC_4,
	ADC_PRESC_8,
	ADC_PRESC_16,
	ADC_PRESC_32,
	ADC_PRESC_64,
	ADC_PRESC_128
}ADC_Presc;

typedef struct{
	u8 prescalar	:3;
	u8 int_en		:1;
	u8 int_flag		:1;
	u8 auto_trig	:1;
	u8 start_conv	:1;
	u8 enable		:1;
}ADCSRA_Struct;
#define ADC_CtrlStatusR		((volatile ADCSRA_Struct*)(&ADCSRA))

typedef enum{
	ADC_VREF_External,
	ADC_VREF_VCC_INT,
	ADC_VREF_V2_56_INT = 3
}ADC_Vref;

typedef enum{
	ADC_CH0,
	ADC_CH1,
	ADC_CH2,
	ADC_CH3,
	ADC_CH4,
	ADC_CH5,
	ADC_CH6,
	ADC_CH7
}ADC_Channel;

typedef struct{
	u8 channel		:5;
	u8 adjust_left	:1;
	u8 Vref			:2;
}ADMUX_Struct;
#define ADC_SelectR		((volatile ADMUX_Struct*)(&ADMUX))

#define ADC_Data		(*((volatile u16*)(&ADC)))


void ADC_Init(void);
u16 ADC_Read(ADC_Channel channel);

#endif /* ADC_H_ */