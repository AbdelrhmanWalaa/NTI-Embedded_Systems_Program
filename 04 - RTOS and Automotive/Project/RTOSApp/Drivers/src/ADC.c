/*
 * ADC.c
 *
 * Created: 7/11/2021 2:12:14 PM
 *  Author: MahmoudH
 */ 
#include "ADC.h"

void ADC_Init(void){
	ADC_SelectR->Vref = ADC_VREF_VCC_INT;
	ADC_CtrlStatusR->prescalar = ADC_PRESC_128;
	ADC_CtrlStatusR->enable = 1;
}
u16 ADC_Read(ADC_Channel channel){
	ADC_SelectR->channel = channel;
	ADC_CtrlStatusR->start_conv = 1;
	while(ADC_CtrlStatusR->start_conv);
	return ADC_Data;
}
/*
ADC_Init_Struct
> presc
> ref
? channel

*/