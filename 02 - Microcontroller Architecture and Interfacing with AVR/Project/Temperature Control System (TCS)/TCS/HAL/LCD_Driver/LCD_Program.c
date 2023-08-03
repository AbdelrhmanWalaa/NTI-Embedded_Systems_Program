/*
 * LCD_Program.c
 *
 *   Created on: Apr 20, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Liquid Crystal Display (LCD) functions' implementation.
 *    Datasheet: https://datasheetspdf.com/pdf/746281/Topway/LMB161ABC-1/1
 *    Model No.: LMB161A - LCD
 */

/* HAL */
#include "LCD_Private.h"
#include "LCD_Config.h"
#include "LCD_Interface.h"

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_vdInitialization
 Input: void
 Output: void
 Description: Function to initialize ( both 4 Bit and 8 Bit Modes ) LCD peripheral.
*/
vd LCD_vdInitialization ( void )
{
	/* Step 1: Delay more than 30 ms */
	_delay_ms(35);

	/* Check: Required LCD Mode */
	switch ( LCD_U8_MODE_SELECT )
	{
		case LCD_U8_4_BIT_MODE:

			/* Step 2: Send Function Set Control Command with 4 Bit Mode */
			LCD_vdSendCmnd( 0x02 );
			LCD_vdSendCmnd( LCD_U8_FUNC_SET_4_BIT );

		break;

		case LCD_U8_8_BIT_MODE:

			/* Step 2: Send Function Set Control Command with 8 Bit Mode */
			LCD_vdSendCmnd( LCD_U8_FUNC_SET_8_BIT );
			
		break;
	}

	/* Step 3: Delay more than 39 us */
	_delay_us(40);

	/* Step 4: Send Display On/Off control command with Display on, Cursor on, and Blink on */
	LCD_vdSendCmnd( LCD_U8_DISP_ON_OFF_CTRL );

	/* Step 5: Delay more than 39 us */
	_delay_us(40);

	/* Step 6: Send Display Clear control command */
	LCD_vdSendCmnd( LCD_U8_DISP_CLEAR );

	/* Step 7: Delay more than 1.53 ms */
	_delay_ms(2);

	/* Step 8: Send Entry Mode control command with Increment on and Shift off */
	LCD_vdSendCmnd( LCD_U8_ENTRY_MODE );
}

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_vdSendCmnd
 Input: u8 Cmnd
 Output: void
 Description: Function to send a Command to LCD through Data pins.
*/
vd LCD_vdSendCmnd		 ( u8 Cpy_u8Cmnd )
{
	/* Step 1: Set RS = 0 ( i.e. Command ) */
	DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_RS_PIN, DIO_U8_PIN_LOW );

	/* Step 2: Set RW = 0 ( i.e. Write ) */
	DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_RW_PIN, DIO_U8_PIN_LOW );

	/* Check 1: Required LCD Mode */
	switch ( LCD_U8_MODE_SELECT )
	{
		case LCD_U8_4_BIT_MODE:

			/* Check 1.1: Required Pins Location in 4-bit Mode */
			switch ( LCD_U8_DATA_PINS_LOCATION )
			{				
				/* Define Local Variable to get Port Value */
				u8 Loc_u8LCDPortValue = 0;
		
				case LCD_U8_LOWER_PORT_PINS:

					/* 
					 * Step 3: Put the Command on the Data pins 
					 */

					/* Step 3.1: Get LCD Port Value */
					DIO_u8GetPortValue( LCD_U8_DATA_PORT, &Loc_u8LCDPortValue );

					/* Step 3.2: Put the Upper nibble Command on the Data pins, without altering the rest of Port pins. */
					Loc_u8LCDPortValue = ( Loc_u8LCDPortValue & 0xF0 ) | ( Cpy_u8Cmnd >> 4 );
					DIO_u8SetPortValue( LCD_U8_DATA_PORT, Loc_u8LCDPortValue );

					/* Step 3.3: Send Enable high and delay 230 ns -> 1 us */
					DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_EN_PIN, DIO_U8_PIN_HIGH );
					_delay_us(1);

					/* Step 3.4: Send Enable low and delay 230 ns -> 1 us */
					DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_EN_PIN, DIO_U8_PIN_LOW );
					_delay_us(1);

					/* Step 3.5: Get LCD Port Value */
					DIO_u8GetPortValue( LCD_U8_DATA_PORT, &Loc_u8LCDPortValue );

					/* Step 3.6: Put the Lower nibble Command on the Data pins, without altering the rest of Port pins. */
					Loc_u8LCDPortValue = ( Loc_u8LCDPortValue & 0xF0 ) | ( Cpy_u8Cmnd & 0x0F );
					DIO_u8SetPortValue( LCD_U8_DATA_PORT, Loc_u8LCDPortValue );

				break;

				case LCD_U8_UPPER_PORT_PINS:

					/* 
					 * Step 3: Put the Command on the DATA pins 
					 */

					/* Step 3.1: Get LCD Port Value */
					DIO_u8GetPortValue( LCD_U8_DATA_PORT, &Loc_u8LCDPortValue );

					/* Step 3.2: Put the Upper nibble Command on the Data pins, without altering the rest of Port pins. */
					Loc_u8LCDPortValue = ( Loc_u8LCDPortValue & 0x0F ) | ( Cpy_u8Cmnd & 0xF0 );
					DIO_u8SetPortValue( LCD_U8_DATA_PORT, Loc_u8LCDPortValue );

					/* Step 3.3: Send Enable high and delay 230 ns -> 1 us */
					DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_EN_PIN, DIO_U8_PIN_HIGH );
					_delay_us(1);

					/* Step 3.4: Send Enable low and delay 230 ns -> 1 us */
					DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_EN_PIN, DIO_U8_PIN_LOW );
					_delay_us(1);

					/* Step 3.5: Get LCD Port Value */
					DIO_u8GetPortValue( LCD_U8_DATA_PORT, &Loc_u8LCDPortValue );

					/* Step 3.6: Put the Lower nibble Command on the Data pins, without altering the rest of Port pins. */
					Loc_u8LCDPortValue = ( Loc_u8LCDPortValue & 0x0F ) | ( Cpy_u8Cmnd << 4 );
					DIO_u8SetPortValue( LCD_U8_DATA_PORT, Loc_u8LCDPortValue );

				break;
			}			
		break;
	
		case LCD_U8_8_BIT_MODE:

			/* Step 3: Put the Command on the Data pins */
			DIO_u8SetPortValue( LCD_U8_DATA_PORT, Cpy_u8Cmnd );

		break;
	}

	/* Step 7: Send Enable high and delay 230 ns -> 1 us */
	DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_EN_PIN, DIO_U8_PIN_HIGH );
	_delay_us(1);

	/* Step 8: Send Enable low and delay 230 ns -> 1 us */
	DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_EN_PIN, DIO_U8_PIN_LOW );
	_delay_us(1);
}

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_vdSendChar
 Input: u8 Char
 Output: void
 Description: Function to send a Character to LCD through Data pins.
*/
vd LCD_vdSendChar		 ( u8 Cpy_u8Char )
{
	/* Step 1: Set RS = 1 (i.e. Data) */
	DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_RS_PIN, DIO_U8_PIN_HIGH );

	/* Step 2: Set RW = 0 (i.e. Write) */
	DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_RW_PIN, DIO_U8_PIN_LOW );

	/* Check 1: Required LCD Mode */
	switch ( LCD_U8_MODE_SELECT )
	{
		case LCD_U8_4_BIT_MODE:

			/* Check 1.1: Required Pins Location in 4-bit Mode */
			switch ( LCD_U8_DATA_PINS_LOCATION )
			{
				/* Define Local Variable to get Port Value */
				u8 Loc_u8LCDPortValue = 0;

				case LCD_U8_LOWER_PORT_PINS:

					/* 
					 * Step 3: Put the Character on the Data pins 
					 */

					/* Step 3.1: Get LCD Port Value */
					DIO_u8GetPortValue( LCD_U8_DATA_PORT, &Loc_u8LCDPortValue );

					/* Step 3.2: Put the Upper nibble Character on the Data pins, without altering the rest of Port pins. */
					Loc_u8LCDPortValue = ( Loc_u8LCDPortValue & 0xF0 ) | ( Cpy_u8Char >> 4 );
					DIO_u8SetPortValue( LCD_U8_DATA_PORT, Loc_u8LCDPortValue );

					/* Step 3.3: Send Enable high and delay 230 ns -> 1 us */
					DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_EN_PIN, DIO_U8_PIN_HIGH );
					_delay_us(1);

					/* Step 3.4: Send Enable low and delay 230 ns -> 1 us */
					DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_EN_PIN, DIO_U8_PIN_LOW );
					_delay_us(1);

					/* Step 3.5: Get LCD Port Value */
					DIO_u8GetPortValue( LCD_U8_DATA_PORT, &Loc_u8LCDPortValue );					

					/* Step 3.6: Put the Lower nibble Character on the Data pins, without altering the rest of Port pins. */
					Loc_u8LCDPortValue = ( Loc_u8LCDPortValue & 0xF0 ) | ( Cpy_u8Char & 0x0F );
					DIO_u8SetPortValue( LCD_U8_DATA_PORT, Loc_u8LCDPortValue );				

				break;

				case LCD_U8_UPPER_PORT_PINS:

					/* 
					 * Step 3: Put the Character on the DATA pins
					 */

					/* Step 3.1: Get LCD Port Value */
					DIO_u8GetPortValue( LCD_U8_DATA_PORT, &Loc_u8LCDPortValue );

					/* Step 3.2: Put the Upper nibble Character on the Data pins, without altering the rest of Port pins. */
					Loc_u8LCDPortValue = ( Loc_u8LCDPortValue & 0x0F ) | ( Cpy_u8Char & 0xF0 );
					DIO_u8SetPortValue( LCD_U8_DATA_PORT, Loc_u8LCDPortValue );

					/* Step 3.3: Send Enable high and delay 230 ns -> 1 us */
					DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_EN_PIN, DIO_U8_PIN_HIGH );
					_delay_us(1);

					/* Step 3.4: Send Enable low and delay 230 ns -> 1 us */
					DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_EN_PIN, DIO_U8_PIN_LOW );
					_delay_us(1);

					/* Step 3.5: Get LCD Port Value */
					DIO_u8GetPortValue( LCD_U8_DATA_PORT, &Loc_u8LCDPortValue );

					/* Step 3.6: Put the Lower nibble Character on the Data pins, without altering the rest of Port pins. */
					Loc_u8LCDPortValue = ( Loc_u8LCDPortValue & 0x0F ) | ( Cpy_u8Char << 4 );
					DIO_u8SetPortValue( LCD_U8_DATA_PORT, Loc_u8LCDPortValue );

				break;
			}			
		break;
	
		case LCD_U8_8_BIT_MODE:

			/* Step 3: Put the Character on the Data pins */
			DIO_u8SetPortValue( LCD_U8_DATA_PORT, Cpy_u8Char );

		break;
	}

	/* Step 4: Send Enable high and delay 230 ns -> 1 us */
	DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_EN_PIN, DIO_U8_PIN_HIGH );
	_delay_us(1);

	/* Step 5: Send Enable low and delay 230 ns -> 1 us */
	DIO_u8SetPinValue( LCD_U8_CTRL_PORT, LCD_U8_EN_PIN, DIO_U8_PIN_LOW );
	_delay_us(1);
}

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_vdClearDisplay
 Input: void
 Output: void
 Description: Function to clear LCD display screen in DDRAM.
*/
vd LCD_vdClearDisplay	 ( void )
{
	/* Step 1: Send Display Clear control command */
	LCD_vdSendCmnd( LCD_U8_DISP_CLEAR );

	/* Step 2: Delay more than 1.53 ms */
	_delay_ms(2);
}

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_u8GoToLocation
 Input: u8 LineNumber and u8 DisplayLocation
 Output: u8 Error or No Error
 Description: Function to set the Address Counter (AC) of LCD to a certain location in DDRAM.
*/
u8 LCD_u8GoToLocation	 ( u8 Cpy_u8LineNumber, u8 Cpy_u8DisplayLocation )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

	/* Check 1: LineNumber and the Location are in the valid range */
	if ( ( Cpy_u8LineNumber <= LCD_U8_LINE2 ) && ( Cpy_u8DisplayLocation <= LCD_U8_LINE_LOCATIONS ) )
	{
		/* Check 1.1: the Required LineNumber */
		switch ( Cpy_u8LineNumber )
		{
			case LCD_U8_LINE1: LCD_vdSendCmnd( LCD_U8_LOC_SET_TO_LINE1 + Cpy_u8DisplayLocation ); break;
			case LCD_U8_LINE2: LCD_vdSendCmnd( LCD_U8_LOC_SET_TO_LINE2 + Cpy_u8DisplayLocation ); break;
		}
	}
	/* Check 2: LineNumber or the Location is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong LineNumber or Location! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}

	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_u8WriteString
 Input: Pointer to u8 String
 Output: vou8 Error or No Error
 Description: Function to send an array of characters to LCD through Data pins ( From CGROM to DDRAM ).
*/
u8 LCD_u8WriteString 	 ( u8 *Cpy_pu8String )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

	/* Check 1: Pointer is not equal to NULL */
	if ( Cpy_pu8String != NULL )
	{
		/* Loop: Until the end of string */
		while ( *Cpy_pu8String != '\0' )
		{
			LCD_vdSendChar( *Cpy_pu8String );
			/* Increment String */
			Cpy_pu8String++;
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
/*
 Name: LCD_vdWriteNumber
 Input: s64 Number
 Output: void
 Description: Function to send a number ( positive or negative ) to LCD through Data pins ( From CGROM to DDRAM ).
*/
vd LCD_vdWriteNumber	 ( s64 Cpy_s64Number )
{
	u8  Loc_Au8Number[LCD_U8_NUM_OF_DIGITS_OF_S64];
	s64 Loc_s64TempNumber = 0;
	s8  Loc_s8Index = LCD_U8_FIRST_ELEMENT;

	/* Step 1: Check if the Number is negative */
	if ( Cpy_s64Number < 0 )
	{
		/* Save the Number into TempNumber */
		Loc_s64TempNumber = Cpy_s64Number;
		/* Convert the Number to positive */
		Cpy_s64Number = Cpy_s64Number - ( Cpy_s64Number * 2 );
	}

	/* Step 2: Save the Number in a reversed manner in NumberArray */
	while ( Cpy_s64Number >= 10 )
	{
		/* Use modulo 10 to get last digit, and save this digit to NumberArray */
		Loc_Au8Number[Loc_s8Index] = Cpy_s64Number % 10;

		/* Divide Number by 10 */
		Cpy_s64Number = Cpy_s64Number / 10;
		Loc_s8Index++;
	}

	/* Step 3: Put the first digit in the array when Number < 10 */
	Loc_Au8Number[Loc_s8Index] = Cpy_s64Number;

	/* Step 4: Check if the TempNumber was negative, display '-' sign before the TempNumber on LCD */
	if ( Loc_s64TempNumber < 0 )
	{
		LCD_vdSendChar( '-' );
	}

	/* Step 5: Display Number on LCD */
	while ( Loc_s8Index >= LCD_U8_FIRST_ELEMENT )
	{
		LCD_vdSendChar( Loc_Au8Number[Loc_s8Index] + '0' );
		Loc_s8Index--;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_u8WriteSpecialChar
 Input: u8 StoreLocation, u8 LineNumber, u8 DisplayLocation, and Pointer to u8 SpecialChar
 Output: u8 Error or No Error
 Description: Function to send character ( stored in array -SpecialChar- byte by byte ) and store it in CGRAM, then display it on DDRAM ( From CGRAM to DDRAM ).
*/
u8 LCD_u8WriteSpecialChar( u8 Cpy_u8StoreLocation, u8 Cpy_u8LineNumber, u8 Copy_u8DisplayLocation, u8 *Cpy_pu8SpecialChar )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

	/* Step 1: Set CGRAM in Address Counter (AC) */

	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/