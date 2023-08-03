/*
 * KPD_program.c
 *
 *   Created on: Apr 3, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *	Description: This file contains all Keypad (KPD) functions' implementation.
 */

/* HAL */
#include "KPD_Config.h"
#include "KPD_Interface.h"

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */

/* Global Array of KPD Keys */
static const u8 Glb_Au8Keys[4][4] = KPD_AU8_KEYS;

/* Global Arrays of Rows an Columns Pins */
static const u8 Glb_Au8RowsPins[4] = { KPD_U8_R1_PIN, KPD_U8_R2_PIN, KPD_U8_R3_PIN, KPD_U8_R4_PIN };
static const u8 Glb_Au8ColsPins[4] = { KPD_U8_C1_PIN, KPD_U8_C2_PIN, KPD_U8_C3_PIN, KPD_U8_C4_PIN };

/*******************************************************************************************************************************************************************/
/*
 Name: KPD_vdEnableKPD
 Input: void
 Output: void
 Description: Function to enable Keypad.
*/
vd KPD_vdEnableKPD	  ( void )
{
	/* Set the four Pins configured Output to Output, in order to enable or re-enable the KPD, therefore four Pins are Output, and the other four are Input */
	DIO_u8SetPinDirection( KPD_U8_OUTPUT_PORT, KPD_U8_OUTPUT_PIN1, DIO_U8_PIN_OUTPUT );
	DIO_u8SetPinDirection( KPD_U8_OUTPUT_PORT, KPD_U8_OUTPUT_PIN2, DIO_U8_PIN_OUTPUT );
	DIO_u8SetPinDirection( KPD_U8_OUTPUT_PORT, KPD_U8_OUTPUT_PIN3, DIO_U8_PIN_OUTPUT );
	DIO_u8SetPinDirection( KPD_U8_OUTPUT_PORT, KPD_U8_OUTPUT_PIN4, DIO_U8_PIN_OUTPUT );
}

/*******************************************************************************************************************************************************************/
/*
 Name: KPD_vdDisableKPD
 Input: void
 Output: void
 Description: Function to disable Keypad.
*/
vd KPD_vdDisableKPD	  ( void )
{
	/* Set the four Pins configured Output to Input, in order to disable the KPD, therefore all KPD pins are Input */
	DIO_u8SetPinDirection( KPD_U8_OUTPUT_PORT, KPD_U8_OUTPUT_PIN1, DIO_U8_PIN_INPUT );
	DIO_u8SetPinDirection( KPD_U8_OUTPUT_PORT, KPD_U8_OUTPUT_PIN2, DIO_U8_PIN_INPUT );
	DIO_u8SetPinDirection( KPD_U8_OUTPUT_PORT, KPD_U8_OUTPUT_PIN3, DIO_U8_PIN_INPUT );
	DIO_u8SetPinDirection( KPD_U8_OUTPUT_PORT, KPD_U8_OUTPUT_PIN4, DIO_U8_PIN_INPUT );
}

/*******************************************************************************************************************************************************************/
/*
 Name: KPD_u8GetPressedKey
 Input: Pointer to u8 ReturnedKeyValue
 Output: u8 Error or No Error
 Description: Function to check for the pressed key.
*/
u8 KPD_u8GetPressedKey( u8 *Cpy_u8ReturnedKeyValue )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
	
	/* Check 1: Pointer is not equal to NULL */
	if ( Cpy_u8ReturnedKeyValue != NULL )
	{
		u8 Loc_u8PinValue;
		u8 Loc_u8KeyFlag = KPD_U8_KEY_NOT_FOUND;
		
		/* Step 1: Update ReturnedKeyValue with the Not Pressed Key value */
		*Cpy_u8ReturnedKeyValue = KPD_U8_KEY_NOT_PRESSED;
		
		/* Loop: On Rows -> Output ( i.e.: Set Pin ) */
		for ( u8 Loc_u8RowsCounter = 0; Loc_u8RowsCounter <= 3; Loc_u8RowsCounter++ )
		{
			/* Step 2: Activate Row ( i.e. Set Pin Low ) */
			DIO_u8SetPinValue( KPD_U8_OUTPUT_PORT, Glb_Au8RowsPins[Loc_u8RowsCounter], DIO_U8_PIN_LOW );
			
			/* Loop: On Columns -> Input ( i.e. Get Pin ) */
			for ( u8 Loc_u8ColsCounter = 0; Loc_u8ColsCounter <= 3; Loc_u8ColsCounter++ )
			{
				/* Step 3: Get the value of each Key */
				DIO_u8GetPinValue( KPD_U8_INPUT_PORT, Glb_Au8ColsPins[Loc_u8ColsCounter], &Loc_u8PinValue );
				
				/* Check 1.1.1: Key is Pressed */
				if ( Loc_u8PinValue == DIO_U8_PIN_LOW )
				{
					/* Push buttons often generate spurious open/close transitions when pressed, due to mechanical and physical issues: these transitions may be read as multiple presses in a very short time fooling the program. This example demonstrates how to debounce an input, which means checking twice in a short period of time to make sure the pushbutton is definitely pressed. Without debouncing, pressing the button once may cause unpredictable results. */
					/* Delay debouncing time of the Key */
					_delay_ms(20);
					
					/* Step 4: Recheck if the Key is still Pressed */
					DIO_u8GetPinValue( KPD_U8_INPUT_PORT, Glb_Au8ColsPins[Loc_u8ColsCounter], &Loc_u8PinValue );
					
					/* This step assures releasing Key before returning the key value, to avoid returning multiple values for the same Press! */
					/* Loop: Until releasing Key ( i.e. Pin value is High ) */
					while ( Loc_u8PinValue == DIO_U8_PIN_LOW )
					{
						DIO_u8GetPinValue( KPD_U8_INPUT_PORT, Glb_Au8ColsPins[Loc_u8ColsCounter], &Loc_u8PinValue );					
					}
					
					/* Step 5: Update ReturnedKeyValue with the Pressed Key value */
					*Cpy_u8ReturnedKeyValue = Glb_Au8Keys[Loc_u8RowsCounter][Loc_u8ColsCounter];
					
					/* Step 6: Update Flag to Found */
					Loc_u8KeyFlag = KPD_U8_KEY_FOUND;
					
					/* Step 7: Break Columns loop */
					break;
				}
			}
			
			/* Step 8: Deactivate Row ( i.e. Set Pin High ) */
			DIO_u8SetPinValue( KPD_U8_OUTPUT_PORT, Glb_Au8RowsPins[Loc_u8RowsCounter], DIO_U8_PIN_HIGH );
			
			/* Check 1.1: Flag is Found */
			if ( Loc_u8KeyFlag == KPD_U8_KEY_FOUND )
			{
				/* Step 9: Break Rows loop */
				break;
			}			
		}
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