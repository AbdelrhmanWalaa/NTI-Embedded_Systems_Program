/*
 * DCM_Program.c
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Direct Current Motor (DCM) functions' implementation.
 *    Datasheet: https://datasheetspdf.com/pdf/917207/KYSAN/RF-300CA-11440/1
 *    Model No.: RF-300CA-11440 - DCM 
 */

/* HAL */
#include "DCM_Config.h"
#include "DCM_Interface.h"

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */

/* Global Variable ( Flag ) to be altered when DCM rotating direction is changed. */
u8 Glb_u8DCMDirection = DCM_U8_CLOCKWISE_DIRECTION;

/*******************************************************************************************************************************************************************/
/*
 Name: DCM_vdRotateDCMInOneDirection
 Input: u16 RotateSpeed
 Output: u8 Error or No Error
 Description: Function to Rotate DCM in One Direction only.
*/
u8 DCM_u8RotateDCMInOneDirection ( u16 Cpy_u16RotateSpeed )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
		
	/* Check 1: RotateSpeed is in the valid range */
	if ( Cpy_u16RotateSpeed <= DCM_U16_TOP_SPEED )
	{
		/* Check 1.1: Required RotateMode */
		switch ( DCM_U8_ROT_MODE_SELECT )
		{
			case DCM_U8_NORMAL_MODE:
				DIO_u8SetPinValue( DCM_U8_CTRL_PORT, DCM_U8_CTRL_PIN , DIO_U8_PIN_HIGH );
			break;
				
			case DCM_U8_SPEED_MODE :
				/* Step 1: Set Rotate Speed */
				TMR_u8SetCompareMatchValue( DCM_U8_ONE_DIR_TMR, TMR_U8_NO_CHANNEL, Cpy_u16RotateSpeed );		
				/* Step 2: Start Rotating Counter Clockwise */
				TMR_u8EnableCOMPPin( DCM_U8_ONE_DIR_TMR, TMR_U8_NO_CHANNEL, TMR_U8_CLR_OCR_PIN );
			break;
		}	
	}
	/* Check 2: RotateSpeed is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong RotateSpeed! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}

	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DCM_u8RotateDCMInTwoDirections
 Input: u8 RotateDirection and u16 RotateSpeed
 Output: u8 Error or No Error
 Description: Function to Rotate DCM into both Clockwise and Counter Clockwise Directions.
*/
u8 DCM_u8RotateDCMInTwoDirections( u8 Cpy_u8RotateDirection, u16 Cpy_u16RotateSpeed )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
	
	/* Check 1: RotateDirection and RotateSpeed are in the valid range */
	if ( ( Cpy_u8RotateDirection <= DCM_U8_COUNTER_CLOCKWISE_DIRECTION ) && ( Cpy_u16RotateSpeed <= DCM_U16_TOP_SPEED ) )
	{
		/* Check 1.1: Required RotateMode */
		switch ( DCM_U8_ROT_MODE_SELECT )
		{
			case DCM_U8_NORMAL_MODE:
				/* Check 1.1.1: Required RotateDirection */
				switch( Cpy_u8RotateDirection )
				{
					case DCM_U8_CLOCKWISE_DIRECTION:
						DIO_u8SetPinValue( DCM_U8_CTRL_PORT, DCM_U8_CCW_CTRL_PIN, DIO_U8_PIN_LOW  );
						DIO_u8SetPinValue( DCM_U8_CTRL_PORT, DCM_U8_CW_CTRL_PIN , DIO_U8_PIN_HIGH );
					break;
					
					case DCM_U8_COUNTER_CLOCKWISE_DIRECTION:
						DIO_u8SetPinValue( DCM_U8_CTRL_PORT, DCM_U8_CW_CTRL_PIN , DIO_U8_PIN_LOW  );
						DIO_u8SetPinValue( DCM_U8_CTRL_PORT, DCM_U8_CCW_CTRL_PIN, DIO_U8_PIN_HIGH );
					break;
				}
			break;
				
			case DCM_U8_SPEED_MODE :
				/* Check 1.1.2: Required RotateDirection */
				switch( Cpy_u8RotateDirection )
				{
					case DCM_U8_CLOCKWISE_DIRECTION:						
						/* Step 1: Stop Rotating Counter Clockwise */
						TMR_u8DisableCOMPPin( DCM_U8_TWO_DIR_TMR, DCM_U8_CCW_CTRL_CHANNEL );
						/* Step 2: Set Rotate Speed */
						TMR_u8SetCompareMatchValue( DCM_U8_TWO_DIR_TMR, DCM_U8_CW_CTRL_CHANNEL, Cpy_u16RotateSpeed );
						/* Step 3: Start Rotating Clockwise */
						TMR_u8EnableCOMPPin( DCM_U8_TWO_DIR_TMR, DCM_U8_CW_CTRL_CHANNEL, TMR_U8_CLR_OCR_PIN );
					break;
					
					case DCM_U8_COUNTER_CLOCKWISE_DIRECTION:
						/* Step 1: Stop Rotating Clockwise */
						TMR_u8DisableCOMPPin( DCM_U8_TWO_DIR_TMR, DCM_U8_CW_CTRL_CHANNEL );
						/* Step 2: Set Rotate Speed */
						TMR_u8SetCompareMatchValue( DCM_U8_TWO_DIR_TMR, DCM_U8_CCW_CTRL_CHANNEL, Cpy_u16RotateSpeed );
						/* Step 3: Start Rotating Counter Clockwise */
						TMR_u8EnableCOMPPin( DCM_U8_TWO_DIR_TMR, DCM_U8_CCW_CTRL_CHANNEL, TMR_U8_CLR_OCR_PIN );
					break;
				}
			break;
		}
	}
	/* Check 2: RotateDirection or RotateSpeed is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong RotateDirection or RotateSpeed! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}

	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DCM_vdChangeDCMDirection
 Input: void
 Output: void
 Description: Function to Change DCM Direction.
*/
vd DCM_vdChangeDCMDirection( void )
{
	/* Check: Required DCMDirection */
	switch ( Glb_u8DCMDirection )
	{
		case DCM_U8_CLOCKWISE_DIRECTION        : Glb_u8DCMDirection = DCM_U8_COUNTER_CLOCKWISE_DIRECTION; break;
		case DCM_U8_COUNTER_CLOCKWISE_DIRECTION: Glb_u8DCMDirection = DCM_U8_CLOCKWISE_DIRECTION;         break;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: DCM_u8SetDutyCycleOfPWM
 Input: u8 DutyCycleValue
 Output: u8 Error or No Error
 Description: Function to Set Duty Cycle Value of DCM PWM.
*/
u8 DCM_u8SetDutyCycleOfPWM ( u16 Cpy_u16DutyCycleValue )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
	
	/* Check 1: DutyCycleValue is in the valid range */
	if ( Cpy_u16DutyCycleValue <= DCM_U16_TOP_SPEED )
	{
		/* Check 1.1: Required Rotation Direction Mode */
		switch ( DCM_U8_DIR_MODE_SELECT )
		{
			/* Case 1: One-Direction Mode */
			case DCM_U8_ONE_DIR_MODE: TMR_u8SetCompareMatchValue( DCM_U8_ONE_DIR_TMR, TMR_U8_NO_CHANNEL, Cpy_u16DutyCycleValue ); break;

			/* Case 2: Two-Direction Mode */
			case DCM_U8_TWO_DIR_MODE:
				/* Check 1.1.1: Required RotateDirection */
				switch ( Glb_u8DCMDirection )
				{
					case DCM_U8_CLOCKWISE_DIRECTION        : TMR_u8SetCompareMatchValue( DCM_U8_TWO_DIR_TMR, DCM_U8_CW_CTRL_CHANNEL , Cpy_u16DutyCycleValue ); break;
					case DCM_U8_COUNTER_CLOCKWISE_DIRECTION: TMR_u8SetCompareMatchValue( DCM_U8_TWO_DIR_TMR, DCM_U8_CCW_CTRL_CHANNEL, Cpy_u16DutyCycleValue ); break;
				}
			break;
		}	

	}
	/* Check 2: DutyCycleValue is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong DutyCycleValue! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DCM_u8GetDutyCycleOfPWM
 Input: Pointer to u8 ReturnedDutyCycleValue
 Output: u8 Error or No Error
 Description: Function to Get Duty Cycle Value of DCM PWM.
*/
u8 DCM_u8GetDutyCycleOfPWM ( u8 *Cpy_pu8ReturnedDutyCycleValue )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
	
	/* Check 1: Pointer is not equal to NULL */
	if ( Cpy_pu8ReturnedDutyCycleValue != NULL )
	{		
		u16 Loc_u16TotalPeriod = 0, Loc_u16OnPeriod = 0;		
			
		/* Step 1: Get Total Period Value = TCNT Register Value */
		/* Note: TMR1 TCNT Register Value is Top = 0x03FF ( i.e. Phase Correct PWM 10-Bit Mode ) */
		Loc_u16TotalPeriod = DCM_U16_TOP_SPEED;
			
		/* Step 2: Get On Period Value = OCR Value */
		/* Check 1.1: Required Rotation Direction Mode */
		switch ( DCM_U8_DIR_MODE_SELECT )
		{
			/* Case 1: One-Direction Mode */
			case DCM_U8_ONE_DIR_MODE: TMR_u8GetCompareMatchValue( DCM_U8_ONE_DIR_TMR, TMR_U8_NO_CHANNEL , &Loc_u16OnPeriod ); break;

			/* Case 2: Two-Direction Mode */
			case DCM_U8_TWO_DIR_MODE:
				/* Check 1.1.1: Required RotateDirection */
				switch ( Glb_u8DCMDirection )
				{
					case DCM_U8_CLOCKWISE_DIRECTION        : TMR_u8GetCompareMatchValue( DCM_U8_TWO_DIR_TMR, DCM_U8_CW_CTRL_CHANNEL , &Loc_u16OnPeriod ); break;
					case DCM_U8_COUNTER_CLOCKWISE_DIRECTION: TMR_u8GetCompareMatchValue( DCM_U8_TWO_DIR_TMR, DCM_U8_CCW_CTRL_CHANNEL, &Loc_u16OnPeriod ); break;
				}
			break;
		}
		
		/* Step 3: Calculate and return Duty Cycle Value = ( On Period Value * 100% ) / Total Period Value */
		*Cpy_pu8ReturnedDutyCycleValue = ( u8 ) ( ( ( u32 ) Loc_u16OnPeriod * 100 ) / Loc_u16TotalPeriod );
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
 Name: DCM_vdStopMotor
 Input: void
 Output: void
 Description: Function to Stop DCM.
*/
vd DCM_vdStopDCM         ( void )
{
	/* Check 1: Required Rotate Mode */
	switch ( DCM_U8_ROT_MODE_SELECT )
	{
		/* Case A: Normal Mode */
		case DCM_U8_NORMAL_MODE:

			/* Check 1.1: Required Direction Mode */
			switch ( DCM_U8_DIR_MODE_SELECT )
			{
				/* Case 1: One-Direction Mode */
				case DCM_U8_ONE_DIR_MODE:
					DIO_u8SetPinValue( DCM_U8_CTRL_PORT, DCM_U8_CTRL_PIN , DIO_U8_PIN_LOW );
				break;

				/* Case 2: Two-Direction Mode */
				case DCM_U8_TWO_DIR_MODE:
					DIO_u8SetPinValue( DCM_U8_CTRL_PORT, DCM_U8_CW_CTRL_PIN , DIO_U8_PIN_LOW );
					DIO_u8SetPinValue( DCM_U8_CTRL_PORT, DCM_U8_CCW_CTRL_PIN, DIO_U8_PIN_LOW );
				break;
			}
		break;
		
		/* Case B: Speed Mode */
		case DCM_U8_SPEED_MODE :

			/* Check 1.2: Required Direction Mode */
			switch ( DCM_U8_DIR_MODE_SELECT )
			{
				/* Case 1: One-Direction Mode */
				case DCM_U8_ONE_DIR_MODE:
					TMR_u8DisableCOMPPin( DCM_U8_ONE_DIR_TMR, TMR_U8_NO_CHANNEL );
				break;

				/* Case 2: Two-Direction Mode */
				case DCM_U8_TWO_DIR_MODE:
					TMR_u8DisableCOMPPin( DCM_U8_TWO_DIR_TMR, DCM_U8_CW_CTRL_CHANNEL  );
					TMR_u8DisableCOMPPin( DCM_U8_TWO_DIR_TMR, DCM_U8_CCW_CTRL_CHANNEL );
				break;
			}
		break;
	}
}

/*******************************************************************************************************************************************************************/