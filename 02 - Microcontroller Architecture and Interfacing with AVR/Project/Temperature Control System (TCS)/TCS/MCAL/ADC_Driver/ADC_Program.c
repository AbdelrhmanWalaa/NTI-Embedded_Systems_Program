/*
 * ADC_Program.c
 *
 *     Created on: Apr 28, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Successive Approximation Analog to Digital Converter (SAADC) functions' implementation, and ISR functions' prototypes and implementation.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

/* MCAL */
#include "ADC_Private.h"
#include "ADC_Config.h"
#include "ADC_Interface.h"

/*******************************************************************************************************************************************************************/

/* Declaration and Initialization */

/* Global Pointer to Function, this function ( in APP Layer ) which this Pointer will hold its address; is having void input arguments and void return type. */
static void ( *Glb_pfADCInterruptAction ) ( void ) = NULL;

/*******************************************************************************************************************************************************************/
/*
 Name: ADC_vdInitialization
 Input: void
 Output: void
 Description: Function to Initialize ADC peripheral.
*/
vd ADC_vdInitialization ( void )
{
	/* Step 1: Select ADC Voltage Reference ( Vref ) */	
	switch ( ADC_U8_VREF_SELECT )
	{
		/* Case 1: Vref = AREF */
		case ADC_U8_AREF_VOLT    : CLR_BIT( ADC_U8_ADMUX_REG, ADC_U8_REFS0_BIT ); CLR_BIT( ADC_U8_ADMUX_REG, ADC_U8_REFS1_BIT ); break;
		/* Case 2: Vref = AVCC */
		case ADC_U8_AVCC_VOLT    : SET_BIT( ADC_U8_ADMUX_REG, ADC_U8_REFS0_BIT ); CLR_BIT( ADC_U8_ADMUX_REG, ADC_U8_REFS1_BIT ); break;
		/* Case 3: Vref = Internal ( 2.56 volts ) */
		case ADC_U8_INTERNAL_VOLT: SET_BIT( ADC_U8_ADMUX_REG, ADC_U8_REFS0_BIT ); SET_BIT( ADC_U8_ADMUX_REG, ADC_U8_REFS1_BIT ); break;
	}

	/* Step 2: ADC Right or Left Adjust */
	switch ( ADC_U8_RESULT_ADJUST )
	{
		/* Case 1: Right Adjust */
		case ADC_U8_RIGHT_ADJUST: CLR_BIT( ADC_U8_ADMUX_REG, ADC_U8_ADLAR_BIT ); break;
		/* Case 2: LEFT Adjust */
		case ADC_U8_LEFT_ADJUST : SET_BIT( ADC_U8_ADMUX_REG, ADC_U8_ADLAR_BIT ); break;
	}

	/* Step 3: ADC Auto Trigger Enable */
	switch ( ADC_U8_AUTO_TRIGGER_ENABLE )
	{
		/* Case 1: Disable Auto Trigger */
		case ADC_U8_RIGHT_ADJUST: CLR_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADATE_BIT ); break;
		/* Case 2: Enable Auto Trigger */
		case ADC_U8_LEFT_ADJUST : SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADATE_BIT ); break;
	}

	/* Note: Case Auto Trigger is Disabled, This Selection will have no effect. */
	/* Select ADC Auto Trigger Source */
	switch ( ADC_U8_AUTO_TRIGGER_SOURCE )
	{
		/* Case 1: Trigger Source -> Free Running mode */
		case ADC_U8_FREE_RUNNING_MODE    : CLR_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS0_BIT ); CLR_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS1_BIT ); CLR_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS2_BIT ); break;
		/* Case 2: Trigger Source -> Analog Comparator */
		case ADC_U8_ANALOG_COMPARATOR    : SET_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS0_BIT ); CLR_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS1_BIT ); CLR_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS2_BIT ); break;
		/* Case 3: Trigger Source -> External Interrupt Request 0 */
		case ADC_U8_EXI_REQUEST_0        : CLR_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS0_BIT ); SET_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS1_BIT ); CLR_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS2_BIT ); break;
		/* Case 4: Trigger Source -> Timer/Counter0 Compare Match */
		case ADC_U8_TMR_0_COMPARE_MATCH  : SET_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS0_BIT ); SET_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS1_BIT ); CLR_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS2_BIT ); break;
		/* Case 5: Trigger Source -> Timer/Counter0 Overflow */
		case ADC_U8_TMR_0_OVERFLOW       : CLR_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS0_BIT ); CLR_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS1_BIT ); SET_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS2_BIT ); break;
		/* Case 6: Trigger Source -> Timer/Counter Compare Match B */
		case ADC_U8_TMR_1_COMPARE_MATCH_B: SET_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS0_BIT ); CLR_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS1_BIT ); SET_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS2_BIT ); break;
		/* Case 7: Trigger Source -> Timer/Counter1 Overflow */
		case ADC_U8_TMR_1_OVERFLOW       : CLR_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS0_BIT ); SET_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS1_BIT ); SET_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS2_BIT ); break;
		/* Case 8: Trigger Source -> Timer/Counter1 Capture Event */
		case ADC_U8_TMR_1_CAPTURE_EVENT  : SET_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS0_BIT ); SET_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS1_BIT ); SET_BIT( ADC_U8_SFIOR_REG, ADC_U8_ADTS2_BIT ); break;
	}

	/* Step 4: ADC Conversion Complete Interrupt Enable */
	switch ( ADC_U8_CC_INTERRUPT_ENABLE )
	{
		/* Case 1: Disable Conversion Complete Interrupt */
		case ADC_U8_CC_INTERRUPT_DISABLED: CLR_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADIE_BIT ); break;
		/* Case 2: Enable Conversion Complete Interrupt */
		case ADC_U8_CC_INTERRUPT_ENABLED : SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADIE_BIT ); break;
	}

	/* Step 5: Select Prescaler */
	/* Note: By default, the successive approximation circuitry requires an input clock frequency between 50 kHz and 200 kHz to get maximum resolution. Therefore, to get this frequency: FCPU / Prescaler -> 8 MHz / 64 = 125 kHz */
	switch ( ADC_U8_PRESCALER_SELECT )
	{
		/* Case 1: Division Factor = 2 */
		case ADC_U8_DIVISION_FACTOR_2  : SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS0_BIT ); CLR_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS1_BIT ); CLR_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS2_BIT ); break;
		/* Case 2: Division Factor = 4 */
		case ADC_U8_DIVISION_FACTOR_4  : CLR_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS0_BIT ); SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS1_BIT ); CLR_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS2_BIT ); break;
		/* Case 3: Division Factor = 8 */
		case ADC_U8_DIVISION_FACTOR_8  : SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS0_BIT ); SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS1_BIT ); CLR_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS2_BIT ); break;
		/* Case 4: Division Factor = 16 */
		case ADC_U8_DIVISION_FACTOR_16 : CLR_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS0_BIT ); CLR_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS1_BIT ); SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS2_BIT ); break;
		/* Case 5: Division Factor = 32 */
		case ADC_U8_DIVISION_FACTOR_32 : SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS0_BIT ); CLR_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS1_BIT ); SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS2_BIT ); break;
		/* Case 6: Division Factor = 64 */
		case ADC_U8_DIVISION_FACTOR_64 : CLR_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS0_BIT ); SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS1_BIT ); SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS2_BIT ); break;
		/* Case 7: Division Factor = 128 */
		case ADC_U8_DIVISION_FACTOR_128: SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS0_BIT ); SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS1_BIT ); SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADPS2_BIT ); break;
	}

	/* Step 6: Enable ADC */
	SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADEN_BIT );
}

/*******************************************************************************************************************************************************************/
/*
 Name: ADC_u8StartConversion
 Input: u8 ChannelId
 Output: u8 Error or No Error
 Description: Function to Start Analog to Digital Conversion.
*/
u8 ADC_u8StartConversion( u8 Cpy_u8ChannelId )
{	
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

	/* Check 1: ChannelId is in the valid range */
	if ( Cpy_u8ChannelId <= ADC_U8_CHANNEL_31 )
	{
		/* Step 1: Place the passed Channel into the ADMUX register in the 5 LSBs ( MUX4:0 ) */
		/* Important Note 1: In order to place the right channel in the ADMUX register, we have to clear the 5 LSBs ( MUX4:0 ) and reserve the 3 MSBs by using logical AND */
		ADC_U8_ADMUX_REG &= 0b11100000;
		/* Important Note 2: In order to avoid altering the 3 MSBs, and since the ChannelId is passed in 8 bits not 5 bits, we have to use logical OR. */
		ADC_U8_ADMUX_REG |= Cpy_u8ChannelId;

		/* Step 2: Start Conversion */
		SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADSC_BIT );
	}
	/* Check 2: ChannelId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong ChannelId! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}

	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: ADC_u8GetDigitalValue
 Input: u8 InterruptionMode and Pointer to u16 ReturnedDigitalValue
 Output: u8 Error or No Error
 Description: Function to Get the Digital value using both Polling and Interrupt Modes.
*/
u8 ADC_u8GetDigitalValue( u8 Cpy_u8InterruptionMode, u16 *Cpy_pu16ReturnedDigitalValue )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

	/* Check 1: InterruptionMode is in the valid range, and Pointer is not equal to NULL */
	if ( ( Cpy_u8InterruptionMode <= ADC_U8_CC_INT_MODE ) && ( Cpy_pu16ReturnedDigitalValue != NULL ) )
	{
		/* Check 1.1: Required InterruptionMode */
        switch ( Cpy_u8InterruptionMode )
        {
			case ADC_U8_POLLING_MODE:
			{
				u16 Loc_u16TimeOutCounter = 0;

				/* Step 1: Wait ( Poll ) until the conversion ends ( i.e. until Flag ( ADIF ) = 1 ), taking into consideration TimeOutCounter */
				while ( ( GET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADIF_BIT ) == 0 ) && ( Loc_u16TimeOutCounter < ADC_U16_TIME_OUT_MAX_VALUE ) )
				{
					Loc_u16TimeOutCounter++;
				}

				/* Check 1.1.1: Conversion ends ( i.e. Flag ( ADIF ) = 1 ) */
				if ( ( GET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADIF_BIT ) != 0 ) )
				{
					/* Step 2: Clear the flag ( ADIF ) by writing logical one, because this is Polling method. */
					SET_BIT( ADC_U8_ADCSRA_REG, ADC_U8_ADIF_BIT );

					/* Step 3: Get the digital value from the ADC register -> ( ADCH register + ADCL register ). */
					*Cpy_pu16ReturnedDigitalValue = ADC_U16_ADC_REG;
				}
				/* Check 1.1.2: Conversion doesn't end ( i.e. TimeOutCounter reached Max value ). */
				else
				{
					/* Update error state = NOK, TimeOutCounter reached Max value! */
					Loc_u8ErrorState = STD_TYPES_NOK;
				}
			}
			break;

			case ADC_U8_CC_INT_MODE:

				/* Get the digital value from the ADC register -> ( ADCH register + ADCL register ). */
				*Cpy_pu16ReturnedDigitalValue = ADC_U16_ADC_REG;

			break;
		}
	}
	/* Check 2: InterruptionMode is not in the valid range, or Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong InterruptionMode or Pointer is NULL! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}

	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: ADC_u8ADCSetCallBack
 Input: Pointer to Function that takes void and returns void
 Output: u8 Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( ADCInterruptAction ), and then pass this address to ISR function.
*/
u8 ADC_u8ADCSetCallBack ( void ( *Cpy_pfADCInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

	/* Check 1: Pointer to Function is not equal to NULL */
	if( Cpy_pfADCInterruptAction != NULL )
	{
		/* Store the passed address of function ( in APP Layer ) through pointer to function ( ADCInterruptAction ) into Global Pointer to Function ( ADCInterruptAction ). */
		Glb_pfADCInterruptAction = Cpy_pfADCInterruptAction;
	}
	/* Check 2: Pointer to Function is equal to NULL */
	else
	{
		/* Update error state = NOK, Pointer to Function is NULL! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/

/* ISR function prototype of ADC Conversion Complete ( ADC ) */
void __vector_16( void )	__attribute__((signal));

/*******************************************************************************************************************************************************************/

/* ISR function implementation of ADC */
void __vector_16( void )
{
	/* Check: Global Pointer to Function is not equal to NULL */
	if ( Glb_pfADCInterruptAction != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Pointer to Function ( ADCInterruptAction ) */
		Glb_pfADCInterruptAction();
	}
}

/*******************************************************************************************************************************************************************/