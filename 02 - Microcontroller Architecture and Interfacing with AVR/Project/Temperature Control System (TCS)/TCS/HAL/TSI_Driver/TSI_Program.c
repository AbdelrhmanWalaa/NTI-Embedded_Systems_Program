/*
 * TSI_Program.c
 *
 *   Created on: Aug 11, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Temperature Sensor Interface (TSI) functions' implementation.
 *	  Datasheet: https://datasheetspdf.com/pdf/49860/NationalSemiconductor/LM35/1
 *    Model No.: LM35 - TSI
 */

/* HAL */
#include "TSI_Config.h"
#include "TSI_Interface.h"

/*******************************************************************************************************************************************************************/
/*
 Name: TSI_u8GetTemperature
 Input: Pointer to u16 ReturnedTemperatureValue
 Output: u8 Error or No Error
 Description: Function to Get Temperature Value.
*/
u8 TSI_u8GetTemperature( u16 *Cpy_pu16ReturnedTemperatureValue )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

	/* Check 1: Pointer is not equal to NULL */
	if ( Cpy_pu16ReturnedTemperatureValue != NULL )
	{
		u16 Loc_u16DigitalValue, Loc_u16AnalogValue;

		/* Step 1: Select ADC Channel and Start Conversion */
		ADC_u8StartConversion( TSI_U8_CHANNEL_SELECT );
		
		/* Step 2: Get Digital Value after Conversion ends */
		ADC_u8GetDigitalValue( ADC_U8_POLLING_MODE, &Loc_u16DigitalValue );

		/* Step 3: Convert Digital Value into Analog Value */
		/* Rule 1: Analog Value = Digital Value * StepSize */
		/* Rule 2: StepSize = Vref / 2 ^ resolution = 5V / 2 ^ 10 */
		/* Notes : In order to avoid floating numbers -> 5V = 5000mV
		 * 		   In order to avoid overflow in GPRs ( inside processor ) registers -> Cast the product to Unsigned Long ( UL ) or ( u32 ).
		 * 		   Cast the result to u16 ( DataType of the Analog Value ), however this is handled by the Compiler.
		 */
		Loc_u16AnalogValue = ( u16 ) ( ( Loc_u16DigitalValue * 5000UL ) / 1024 );

		/* Step 4: Calculate Temperature Value */
		/* Rule 3: Temperature of 1 degree Celsius = 10 milliVolts */
		*Cpy_pu16ReturnedTemperatureValue = Loc_u16AnalogValue / 10;
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, Pointer is NULL! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}

	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/