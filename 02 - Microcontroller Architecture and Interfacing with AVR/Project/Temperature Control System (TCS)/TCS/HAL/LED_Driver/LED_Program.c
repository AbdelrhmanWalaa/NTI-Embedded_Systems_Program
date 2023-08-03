/*
 * LED_Program.c
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Light Emitting Diode (LED) functions' implementation.
 */

/* HAL */
#include "LED_Config.h"
#include "LED_Interface.h"

/*******************************************************************************************************************************************************************/
/*
 Name: LED_u8SetLEDPin
 Input: u8 LedId and u8 Operation
 Output: u8 Error or No Error
 Description: Function to switch LED on, off, or toggle.
*/
u8 LED_u8SetLEDPin ( u8 Cpy_u8LEDId, u8 Cpy_u8Operation )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
		
	/* Check 1: LEDId and Operation are in the valid range */
	if ( ( Cpy_u8Operation <= LED_U8_TOGGLE ) && ( Cpy_u8LEDId <= LED_U8_7 ) )
	{
		/* Check 1.1: Required Operation */
		switch ( Cpy_u8Operation )
		{
			case LED_U8_ON:
				/* Check 1.1.1: Required LEDId */
				switch ( Cpy_u8LEDId )
				{
					case LED_U8_0: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_0_PIN, DIO_U8_PIN_HIGH ); break;
					case LED_U8_1: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_1_PIN, DIO_U8_PIN_HIGH );	break;
					case LED_U8_2: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_2_PIN, DIO_U8_PIN_HIGH );	break;
					case LED_U8_3: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_3_PIN, DIO_U8_PIN_HIGH );	break;
					case LED_U8_4: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_4_PIN, DIO_U8_PIN_HIGH );	break;
					case LED_U8_5: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_5_PIN, DIO_U8_PIN_HIGH );	break;
					case LED_U8_6: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_6_PIN, DIO_U8_PIN_HIGH );	break;
					case LED_U8_7: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_7_PIN, DIO_U8_PIN_HIGH );	break;
				}				
			break;
			
			case LED_U8_OFF:
				/* Check 1.1.2: Required LEDId */
				switch ( Cpy_u8LEDId )
				{
					case LED_U8_0: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_0_PIN, DIO_U8_PIN_LOW ); break;
					case LED_U8_1: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_1_PIN, DIO_U8_PIN_LOW ); break;
					case LED_U8_2: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_2_PIN, DIO_U8_PIN_LOW ); break;
					case LED_U8_3: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_3_PIN, DIO_U8_PIN_LOW ); break;
					case LED_U8_4: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_4_PIN, DIO_U8_PIN_LOW ); break;
					case LED_U8_5: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_5_PIN, DIO_U8_PIN_LOW ); break;
					case LED_U8_6: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_6_PIN, DIO_U8_PIN_LOW ); break;
					case LED_U8_7: DIO_u8SetPinValue( LED_U8_PORT, LED_U8_7_PIN, DIO_U8_PIN_LOW ); break;
				}				
			break;
			
			case LED_U8_TOGGLE:
				/* Check 1.1.3: Required LEDId */
				switch ( Cpy_u8LEDId )
				{
					case LED_U8_0: DIO_u8TogglePinValue( LED_U8_PORT, LED_U8_0_PIN ); break;
					case LED_U8_1: DIO_u8TogglePinValue( LED_U8_PORT, LED_U8_1_PIN ); break;
					case LED_U8_2: DIO_u8TogglePinValue( LED_U8_PORT, LED_U8_2_PIN ); break;
					case LED_U8_3: DIO_u8TogglePinValue( LED_U8_PORT, LED_U8_3_PIN ); break;
					case LED_U8_4: DIO_u8TogglePinValue( LED_U8_PORT, LED_U8_4_PIN ); break;
					case LED_U8_5: DIO_u8TogglePinValue( LED_U8_PORT, LED_U8_5_PIN ); break;
					case LED_U8_6: DIO_u8TogglePinValue( LED_U8_PORT, LED_U8_6_PIN ); break;
					case LED_U8_7: DIO_u8TogglePinValue( LED_U8_PORT, LED_U8_7_PIN ); break;
				}
			break;
		}
	}
	/* Check 2: LEDId or Operation is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong LEDId or Operation! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}
		
	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: LED_u8SetLEDPort
 Input: u8 Operation
 Output: u8 Error or No Error
 Description: Function to switch LEDs on, off, or toggle.
*/
u8 LED_u8SetLEDPort( u8 Cpy_u8Operation )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
		
	/* Check 1: Operation is in the valid range */
	if ( Cpy_u8Operation <= LED_U8_TOGGLE )
	{
		/* Check 1.1: Required Operation */
		switch ( Cpy_u8Operation )
		{
			case LED_U8_ON    : DIO_u8SetPortValue   ( LED_U8_PORT, DIO_U8_PORT_HIGH ); break;
			case LED_U8_OFF   : DIO_u8SetPortValue   ( LED_U8_PORT, DIO_U8_PORT_LOW  ); break;
			case LED_U8_TOGGLE: DIO_u8TogglePortValue( LED_U8_PORT );					break;
		}
	}
	/* Check 2: Operation is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong Operation! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}
		
	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/