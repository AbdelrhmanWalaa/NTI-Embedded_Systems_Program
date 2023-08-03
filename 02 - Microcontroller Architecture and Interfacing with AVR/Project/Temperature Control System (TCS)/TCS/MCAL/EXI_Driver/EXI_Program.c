/*
 * EXI_Program.c
 *
 *     Created on: Apr 25, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all External Interrupt (EXI) functions' implementation, and ISR functions' prototypes and implementation.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */
 
/* MCAL */
#include "EXI_Private.h"
#include "EXI_Interface.h"

/*******************************************************************************************************************************************************************/

/* Declaration and Initialization */

/* Global Array of 3 Pointers to Functions ( because we have 3 External Interrupts ), these functions ( in APP Layer ) which those 3 Pointers will hold their addresses; are having void input arguments and void return type. */
static void ( *Glb_ApfINTInterrupstAction[3] ) ( void ) = { NULL, NULL, NULL };

/*******************************************************************************************************************************************************************/
/*
 Name: EXI_u8EnablePIE
 Input: u8 InterruptId and u8 SenseControl
 Output: u8 Error or No Error
 Description: Function to enable and configure Peripheral Interrupt Enable (PIE), by setting relevant bit for each interrupt in GICR register,
 	 	 	  then configuring Sense Control in MCUCR (case interrupt 0 or 1) or MCUCSR (case interrupt 2) registers.
*/
u8 EXI_u8EnablePIE     ( u8 Cpy_u8InterruptId, u8 Cpy_u8SenseControl )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
	
	/* Check 1: InterruptId and the Sense Control are in the valid range */
	if ( ( Cpy_u8InterruptId <= EXI_U8_INT2 ) && ( Cpy_u8SenseControl <= EXI_U8_SENSE_RISING_EDGE ) )
	{
		/* Check 1.1: Required InterruptId */
		switch ( Cpy_u8InterruptId )
		{
			case EXI_U8_INT0:
				/* Enable Interrupt 0 */
				SET_BIT( EXI_U8_GICR_REG, EXI_U8_INT0_BIT );

				/* Check 1.1.1: Required SenseControl */
				switch ( Cpy_u8SenseControl )
				{
					case EXI_U8_SENSE_LOW_LEVEL		: CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC00_BIT ); CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC01_BIT ); break;
					case EXI_U8_SENSE_LOGICAL_CHANGE: SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC00_BIT ); CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC01_BIT ); break;
					case EXI_U8_SENSE_FALLING_EDGE	: CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC00_BIT ); SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC01_BIT ); break;
					case EXI_U8_SENSE_RISING_EDGE	: SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC00_BIT ); SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC01_BIT ); break;
				}
			break;

			case EXI_U8_INT1:
				/* Enable Interrupt 1 */
				SET_BIT( EXI_U8_GICR_REG, EXI_U8_INT1_BIT );

				/* Check 1.1.2: Required SenseControl */
				switch( Cpy_u8SenseControl)
				{
					case EXI_U8_SENSE_LOW_LEVEL		: CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC10_BIT ); CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC11_BIT ); break;
					case EXI_U8_SENSE_LOGICAL_CHANGE: SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC10_BIT ); CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC11_BIT ); break;
					case EXI_U8_SENSE_FALLING_EDGE	: CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC10_BIT ); SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC11_BIT ); break;
					case EXI_U8_SENSE_RISING_EDGE	: SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC10_BIT ); SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC11_BIT ); break;

				}
			break;

			case EXI_U8_INT2:
				/* Enable Interrupt 2 */
				SET_BIT( EXI_U8_GICR_REG, EXI_U8_INT2_BIT );

				/* Check 1.1.3: Required SenseControl */
				switch( Cpy_u8SenseControl )
				{
					case EXI_U8_SENSE_FALLING_EDGE: CLR_BIT( EXI_U8_MCUCSR_REG, EXI_U8_ISC2_BIT ); break;
					case EXI_U8_SENSE_RISING_EDGE :	SET_BIT( EXI_U8_MCUCSR_REG, EXI_U8_ISC2_BIT ); break;
				}
			break;
		}
	}
	/* Check 2: InterruptId or the Sense Control is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong InterruptId or Sense Control! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: EXI_u8DisablePIE
 Input: u8 InterruptId
 Output: u8 Error or No Error
 Description: Function to disable Peripheral Interrupt Enable (PIE), by clearing relevant bit for each interrupt in GICR register.
*/
u8 EXI_u8DisablePIE    ( u8 Cpy_u8InterruptId )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
	
	/* Check 1: InterruptId is in the valid range */
	if ( Cpy_u8InterruptId <= EXI_U8_INT2 )
	{
		/* Check 1.1: Required InterruptId */
		switch ( Cpy_u8InterruptId )
		{
			case EXI_U8_INT0: CLR_BIT( EXI_U8_GICR_REG, EXI_U8_INT0_BIT ); break;
			case EXI_U8_INT1: CLR_BIT( EXI_U8_GICR_REG, EXI_U8_INT1_BIT ); break;
			case EXI_U8_INT2: CLR_BIT( EXI_U8_GICR_REG, EXI_U8_INT2_BIT ); break;
		}
	}
	/* Check 2: InterruptId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong InterruptId! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: EXI_u8SetCallBack
 Input: u8 InterruptId and Pointer to Function that takes void and returns void
 Output: u8 Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function of the passed Interrupt ( InterruptId ),
 	 	 	  the address is passed through a pointer to function ( INTInterruptAction ), and then pass this address to ISR function.
*/
u8 EXI_u8INTSetCallBack( u8 Cpy_u8InterruptId, void ( *Cpy_pfINTInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

	/* Check 1: InterruptId is in the valid range, and Pointer to Function is not equal to NULL */
	if( ( Cpy_u8InterruptId <= EXI_U8_INT2 ) && ( Cpy_pfINTInterruptAction != NULL ) )
	{
		/* Store the passed address of function ( in APP Layer ) through pointer to function ( INTInterruptAction ) into Global Array of Pointers to Functions ( INTInterruptsAction ) in the passed index ( InterruptId ). */
		Glb_ApfINTInterrupstAction[Cpy_u8InterruptId] = Cpy_pfINTInterruptAction;
	}
	/* Check 2: InterruptId is not in the valid range, or Pointer to Function is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong InterruptId, or Pointer to Function is NULL! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/

/* ISR functions' prototypes of External Interrupt Request 0 ( INT0 ), External Interrupt Request 1 ( INT1 ), and External Interrupt Request 2 ( INT2 ) respectively */
void __vector_1( void )		__attribute__((signal));
void __vector_2( void )		__attribute__((signal));
void __vector_3( void )		__attribute__((signal));

/*******************************************************************************************************************************************************************/

/* ISR function implementation of INT0 */
void __vector_1( void )
{
	/* Check: INT0 index of the Global Array is not equal to NULL */
	if ( Glb_ApfINTInterrupstAction[EXI_U8_INT0] != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( INTInterruptsAction ) */
		Glb_ApfINTInterrupstAction[EXI_U8_INT0]();
	}	
}

/*******************************************************************************************************************************************************************/

/* ISR function implementation of INT1 */
void __vector_2( void )
{
	/* Check: INT1 index of the Global Array is not equal to NULL */
	if( Glb_ApfINTInterrupstAction[EXI_U8_INT1] != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( INTInterruptsAction ) */
		Glb_ApfINTInterrupstAction[EXI_U8_INT1]();
	}	
}

/*******************************************************************************************************************************************************************/

/* ISR function implementation of INT2 */
void __vector_3( void )
{
	/* Check: INT2 index of the Global Array is not equal to NULL */
	if( Glb_ApfINTInterrupstAction[EXI_U8_INT2] != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( INTInterruptsAction ) */
		Glb_ApfINTInterrupstAction[EXI_U8_INT2]();
	}	
}

/*******************************************************************************************************************************************************************/