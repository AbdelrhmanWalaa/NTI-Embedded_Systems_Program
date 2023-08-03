/*
 * TWI_Program.c
 *
 *     Created on: Nov 07, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Two Wire Interface (TWI) functions' implementation, and ISR functions' prototypes and implementation.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

/* MCAL */
#include "TWI_Private.h"
#include "TWI_Config.h"
#include "TWI_Interface.h"

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */

/* Global Pointer to Function, this function ( in APP Layer ) which this Pointer will hold its address; is having void input arguments and void return type. */
static void ( *Glb_pfTWIInterruptAction ) ( void ) = NULL;

/*******************************************************************************************************************************************************************/
/*
 Name: TWI_vdMasterModeInitialization
 Input: void
 Output: void
 Description: Function to Initialize TWI peripheral in Master Mode.
*/
vd TWI_vdMasterModeInitialization   ( void )
{
    /* Step 1: Set Bit Rate Prescaler Value */
    switch ( TWI_U8_BIT_RATE_PRESCALER_SELECT )
    {
        /* Case 1: TWI Bit Rate Prescaler = 1 */
        case TWI_U8_BIT_RATE_PRESCALER_1 : CLR_BIT( TWI_U8_TWSR_REG, TWI_U8_TWPS1_BIT ); CLR_BIT( TWI_U8_TWSR_REG, TWI_U8_TWPS0_BIT ); break;
        /* Case 2: TWI Bit Rate Prescaler = 4 */
        case TWI_U8_BIT_RATE_PRESCALER_4 : CLR_BIT( TWI_U8_TWSR_REG, TWI_U8_TWPS1_BIT ); SET_BIT( TWI_U8_TWSR_REG, TWI_U8_TWPS0_BIT ); break;
        /* Case 3: TWI Bit Rate Prescaler = 16 */
        case TWI_U8_BIT_RATE_PRESCALER_16: SET_BIT( TWI_U8_TWSR_REG, TWI_U8_TWPS1_BIT ); CLR_BIT( TWI_U8_TWSR_REG, TWI_U8_TWPS0_BIT ); break;
        /* Case 4: TWI Bit Rate Prescaler = 64 */
        case TWI_U8_BIT_RATE_PRESCALER_64: SET_BIT( TWI_U8_TWSR_REG, TWI_U8_TWPS1_BIT ); SET_BIT( TWI_U8_TWSR_REG, TWI_U8_TWPS0_BIT ); break;
    }

    /* Step 2: Set Bit Rate Value */
    /* Important Note: SCL Frequency = F_CPU / ( 16 + 2 ( TWBR Register ) * ( 4 ^ TWPS ) ) --> TWBR Register = ( ( F_CPU / SCL Frequency ) - 16 ) / ( 2 * ( 4 ^ TWPS ) )
     *               - TWBR = Bit Rate Value
     *               - TWPS = Bit Rate Prescaler Value
     *        Example: TWBR Register = ( ( 8000000 / 200000 ) - 16 ) / ( 2 * ( 4 ^ 0 ) ) = 12
     */
    TWI_U8_TWBR_REG = ( u8 ) ( ( F_CPU / TWI_U32_SCL_FREQUENCY ) - 16 ) / ( 2 * ( 4 ^ TWI_U8_BIT_RATE_PRESCALER_SELECT ) );

    /* Step 3: TWI Interrupt in Master Mode Enable */
    switch ( TWI_U8_MM_INT_ENABLE )
	{
        /* Case 1: TWI Interrupt = Disabled */
		case TWI_U8_MM_INT_DISABLED: CLR_BIT( TWI_U8_TWCR_REG, TWI_U8_TWIE_BIT ); break;
        /* Case 2: TWI Interrupt = Enabled */
        case TWI_U8_MM_INT_ENABLED : SET_BIT( TWI_U8_TWCR_REG, TWI_U8_TWIE_BIT ); break;
    }

    /* Step 4: Enable Acknowledge */
    SET_BIT( TWI_U8_TWCR_REG, TWI_U8_TWEA_BIT );

    /* Step 5: Enable TWI peripheral */
    SET_BIT( TWI_U8_TWCR_REG, TWI_U8_TWEN_BIT );
}

/*******************************************************************************************************************************************************************/
/*
 Name: TWI_vdSlaveModeInitialization
 Input: void
 Output: void
 Description: Function to Initialize TWI peripheral in Slave Mode.
*/
vd TWI_vdSlaveModeInitialization    ( void )
{
    /* Step 1: Set Slave Address */
    TWI_U8_TWAR_REG = TWI_U8_SLAVE_ADDRESS;

    /* Step 2: TWI General Call Recognition Enable */
    switch ( TWI_U8_GNRL_CALL_RECOG_ENABLE )
    {
        /* Case 1: General Call Recognition = Disabled */
        case TWI_U8_GNRL_CALL_RECOG_DISABLED: CLR_BIT( TWI_U8_TWAR_REG, TWI_U8_TWGCE_BIT ); break;
        /* Case 2: General Call Recognition = Enabled */
        case TWI_U8_GNRL_CALL_RECOG_ENABLED : SET_BIT( TWI_U8_TWAR_REG, TWI_U8_TWGCE_BIT ); break;
    }

    /* Step 3: TWI Interrupt in Slave Mode Enable */
    switch ( TWI_U8_SM_INT_ENABLE )
	{
        /* Case 1: TWI Interrupt = Disabled */
		case TWI_U8_SM_INT_DISABLED: CLR_BIT( TWI_U8_TWCR_REG, TWI_U8_TWIE_BIT ); break;
        /* Case 2: TWI Interrupt = Enabled */
        case TWI_U8_SM_INT_ENABLED : SET_BIT( TWI_U8_TWCR_REG, TWI_U8_TWIE_BIT ); break;
    }

    /* Step 4: Enable Acknowledge */
    SET_BIT( TWI_U8_TWCR_REG, TWI_U8_TWEA_BIT );

    /* Step 5: Enable TWI peripheral */
    SET_BIT( TWI_U8_TWCR_REG, TWI_U8_TWEN_BIT );
}

/*******************************************************************************************************************************************************************/
/*
 Name: TWI_u8SendSTARTCondition
 Input: void
 Output: u8 Error or No Error
 Description: Function to send START Condition.
*/
u8 TWI_u8SendSTARTCondition         ( void )
{
    /* Define local variable to set the error state = OK */
    u8 Loc_u8ErrorState = TWI_U8_OK;

	/* Define local variable to configure TWCR Register bits separately, then to put this value in the Register directly, as TWCR Register bits cannot be configured separately */
	u8 Loc_u8TWCRRegisterValue = 0b00000000;
	
    u16 Loc_u16TimeOutCounter = 0;

    /* Step 1: Clear TWI Interrupt Flag */
    SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWINT_BIT );

    /* Step 2: Set the START Condition */
    SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWSTA_BIT );
	
	/* Step 3: Enable TWI peripheral */
	SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWEN_BIT );
		
	/* Step 4: Update TWCR Register, after configuring bits */
	TWI_U8_TWCR_REG = Loc_u8TWCRRegisterValue;

    /* Step 5: Wait ( Poll ) until START Condition is transmitted ( i.e. until Flag ( TWINT ) = 1 ), taking into consideration TimeOutCounter */
    while ( ( GET_BIT( TWI_U8_TWCR_REG, TWI_U8_TWINT_BIT ) == 0 ) && ( Loc_u16TimeOutCounter < TWI_U16_TIME_OUT_MAX_VALUE ) )
    {
	    Loc_u16TimeOutCounter++;
    }

    /* Check 1: START Condition is not transmitted ( i.e. Status Register ( TWSR ) is not updated, or TimeOutCounter reached Max value ) */
    if ( ( TWI_U8_TWSR_REG & 0xF8 ) != TWI_U8_MM_START )
    {
	    /* Update error state = START Error, START Condition is not transmitted or TimeOutCounter reached Max value! */
	    Loc_u8ErrorState = TWI_U8_MM_START_ERR;
    }
    
    return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TWI_vdSendSTOPCondition
 Input: void
 Output: void
 Description: Function to send STOP Condition.
*/
vd TWI_vdSendSTOPCondition          ( void )
{
	/* Define local variable to configure TWCR Register bits separately, then to put this value in the Register directly, as TWCR Register bits cannot be configured separately */
	u8 Loc_u8TWCRRegisterValue = 0b00000000;
	
	/* Step 1: Clear TWI Interrupt Flag */
	SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWINT_BIT );

	/* Step 2: Set the STOP Condition */
	SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWSTO_BIT );
	
	/* Step 3: Enable TWI peripheral */
	SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWEN_BIT );
			
	/* Step 4: Update TWCR Register, after configuring bits */
	TWI_U8_TWCR_REG = Loc_u8TWCRRegisterValue;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TWI_u8SendReSTARTCondition
 Input: void
 Output: u8 Error or No Error
 Description: Function to send ReSTART Condition.
*/
u8 TWI_u8SendReSTARTCondition       ( void )
{
    /* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = TWI_U8_OK;

	/* Define local variable to configure TWCR Register bits separately, then to put this value in the Register directly, as TWCR Register bits cannot be configured separately */
	u8 Loc_u8TWCRRegisterValue = 0b00000000;
	
	u16 Loc_u16TimeOutCounter = 0;

	/* Step 1: Clear TWI Interrupt Flag */
	SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWINT_BIT );

	/* Step 2: Set the START Condition */
	SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWSTA_BIT );
	
	/* Step 3: Enable TWI peripheral */
	SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWEN_BIT );
	
	/* Step 4: Update TWCR Register, after configuring bits */
	TWI_U8_TWCR_REG = Loc_u8TWCRRegisterValue;

	/* Step 5: Wait ( Poll ) until START Condition is transmitted ( i.e. until Flag ( TWINT ) = 1 ), taking into consideration TimeOutCounter */
	while ( ( GET_BIT( TWI_U8_TWCR_REG, TWI_U8_TWINT_BIT ) == 0 ) && ( Loc_u16TimeOutCounter < TWI_U16_TIME_OUT_MAX_VALUE ) )
	{
		Loc_u16TimeOutCounter++;
	}

    /* Check 1: ReSTART Condition is not transmitted ( i.e. Status Register ( TWSR ) is not updated, or TimeOutCounter reached Max value ) */
    if ( ( TWI_U8_TWSR_REG & 0xF8 ) == TWI_U8_MM_RESTART )
    {
        /* Update error state = ReSTART Error, ReSTART Condition is not transmitted or TimeOutCounter reached Max value! */
        Loc_u8ErrorState = TWI_U8_MM_RESTART_ERR;
    }
    
    return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TWI_u8MasterModeSendWriteToSlave
 Input: u8 SlaveAddress
 Output: u8 Error or No Error
 Description: Function to send Slave Address with Write Operation.
*/
u8 TWI_u8MasterModeSendWriteToSlave ( u8 Cpy_u8SlaveAddress )
{
    /* Define local variable to set the error state = OK */
    u8 Loc_u8ErrorState = TWI_U8_OK;

    /* Check 1: SlaveAddress is in the valid range */
    if ( ( Cpy_u8SlaveAddress > TWI_U8_GNRL_CALL_ADDRESS ) && ( Cpy_u8SlaveAddress < TWI_U8_LEAST_RES_ADDRESS ) )
    {
		/* Define local variable to configure TWCR Register bits separately, then to put this value in the Register directly, as TWCR Register bits cannot be configured separately */
		u8 Loc_u8TWCRRegisterValue = 0b00000000;

	    u16 Loc_u16TimeOutCounter = 0;

	    /* Step 1: Set SLA + W ( i.e. Slave Address + 0 ) into TWDR Register */
	    TWI_U8_TWDR_REG = Cpy_u8SlaveAddress + 0;

	    /* Step 2: Clear TWI Interrupt Flag */
	    SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWINT_BIT );
		
		/* Step 3: Enable TWI peripheral */
		SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWEN_BIT );
		
		/* Step 4: Update TWCR Register, after configuring bits */
		TWI_U8_TWCR_REG = Loc_u8TWCRRegisterValue;		

	    /* Step 5: Wait ( Poll ) until SLA + W is transmitted ( i.e. until Flag ( TWINT ) = 1 ), taking into consideration TimeOutCounter */
	    while ( ( GET_BIT( TWI_U8_TWCR_REG, TWI_U8_TWINT_BIT ) == 0 ) && ( Loc_u16TimeOutCounter < TWI_U16_TIME_OUT_MAX_VALUE ) )
	    {
		    Loc_u16TimeOutCounter++;
	    }

	    /* Check 1.1: SLA + W is not transmitted ( i.e. Status Register ( TWSR ) is not updated, or TimeOutCounter reached Max value ) */
	    if ( ( TWI_U8_TWSR_REG & 0xF8 ) != TWI_U8_MM_SLA_W_ACK )
	    {
		    /* Update error state = SLA + W Error, SLA + W is not transmitted or TimeOutCounter reached Max value! */
		    Loc_u8ErrorState = TWI_U8_MM_SLA_W_ERR;
	    }
    }
    /* Check 2: SlaveAddress is not in the valid range */
    else
    {
	    /* Update error state = Slave Address Error, wrong SlaveAddress! */
	    Loc_u8ErrorState = TWI_U8_MM_SLA_ERR;
    }

    return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TWI_u8MasterModeSendReadFromSlave
 Input: u8 SlaveAddress
 Output: u8 Error or No Error
 Description: Function to send Slave Address with Read Operation.
*/
u8 TWI_u8MasterModeSendReadFromSlave( u8 Cpy_u8SlaveAddress )
{
    /* Define local variable to set the error state = OK */
    u8 Loc_u8ErrorState = TWI_U8_OK;

    /* Check 1: SlaveAddress is in the valid range */
    if ( ( Cpy_u8SlaveAddress > TWI_U8_GNRL_CALL_ADDRESS ) && ( Cpy_u8SlaveAddress < TWI_U8_LEAST_RES_ADDRESS ) )
    {
		/* Define local variable to configure TWCR Register bits separately, then to put this value in the Register directly, as TWCR Register bits cannot be configured separately */
		u8 Loc_u8TWCRRegisterValue = 0b00000000;
		
	    u16 Loc_u16TimeOutCounter = 0;

	    /* Step 1: Set SLA + R ( i.e. Slave Address + 1 ) into TWDR Register */
	    TWI_U8_TWDR_REG = Cpy_u8SlaveAddress + 1;

	    /* Step 2: Clear TWI Interrupt Flag */
	    SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWINT_BIT );
		
		/* Step 3: Enable TWI peripheral */
		SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWEN_BIT );
			
		/* Step 4: Update TWCR Register, after configuring bits */
		TWI_U8_TWCR_REG = Loc_u8TWCRRegisterValue;

	    /* Step 5: Wait ( Poll ) until SLA + R is transmitted ( i.e. until Flag ( TWINT ) = 1 ), taking into consideration TimeOutCounter */
	    while ( ( GET_BIT( TWI_U8_TWCR_REG, TWI_U8_TWINT_BIT ) == 0 ) && ( Loc_u16TimeOutCounter < TWI_U16_TIME_OUT_MAX_VALUE ) )
	    {
		    Loc_u16TimeOutCounter++;
	    }

	    /* Check 1.1: SLA + R is not transmitted ( i.e. Status Register ( TWSR ) is not updated, or TimeOutCounter reached Max value ) */
	    if ( ( TWI_U8_TWSR_REG & 0xF8 ) != TWI_U8_MM_SLA_R_ACK )
	    {
		    /* Update error state = SLA + R Error, SLA + R is not transmitted or TimeOutCounter reached Max value! */
		    Loc_u8ErrorState = TWI_U8_MM_SLA_R_ERR;
	    }
    }
    /* Check 2: SlaveAddress is not in the valid range */
    else
    {
	    /* Update error state = Slave Address Error, wrong SlaveAddress! */
	    Loc_u8ErrorState = TWI_U8_MM_SLA_ERR;
    }

    return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TWI_u8MasterModeWriteData
 Input: u8 Data
 Output: u8 Error or No Error
 Description: Function to send Data.
*/
u8 TWI_u8MasterModeWriteData	    ( u8 Cpy_u8Data )
{
    /* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = TWI_U8_OK;
	
	/* Define local variable to configure TWCR Register bits separately, then to put this value in the Register directly, as TWCR Register bits cannot be configured separately */
	u8 Loc_u8TWCRRegisterValue = 0b00000000;
	
	u16 Loc_u16TimeOutCounter = 0;
	
	/* Step 1: Set Data into TWDR Register */
	TWI_U8_TWDR_REG = Cpy_u8Data;

	/* Step 2: Clear TWI Interrupt Flag */
	SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWINT_BIT );
	
	/* Step 3: Enable TWI peripheral */
	SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWEN_BIT );
			
	/* Step 4: Update TWCR Register, after configuring bits */
	TWI_U8_TWCR_REG = Loc_u8TWCRRegisterValue;

	/* Step 5: Wait ( Poll ) until Data is transmitted ( i.e. until Flag ( TWINT ) = 1 ), taking into consideration TimeOutCounter */
	while ( ( GET_BIT( TWI_U8_TWCR_REG, TWI_U8_TWINT_BIT ) == 0 ) && ( Loc_u16TimeOutCounter < TWI_U16_TIME_OUT_MAX_VALUE ) )
	{
		Loc_u16TimeOutCounter++;
	}

	/* Check 1: Data is not transmitted ( i.e. Status Register ( TWSR ) is not updated, or TimeOutCounter reached Max value ) */
	if ( ( TWI_U8_TWSR_REG & 0xF8 ) != TWI_U8_MM_DATA_W_ACK )
	{
		/* Update error state = Data Write Error, Data is not transmitted or TimeOutCounter reached Max value! */
		Loc_u8ErrorState = TWI_U8_MM_DATA_W_ERR;
	}
	
    return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TWI_u8MasterModeReadData
 Input: Pointer to u8 ReturnedData, and u8 ACKState
 Output: u8 Error or No Error
 Description: Function to receive Data.
*/
u8 TWI_u8MasterModeReadData		    ( u8 *Cpy_pu8ReturnedData, u8 Cpy_u8ACKState )
{
    /* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = TWI_U8_OK;
	
	/* Check 1: Pointer is not equal to NULL, and ACKState is in the valid range */
	if ( ( Cpy_pu8ReturnedData != NULL ) && ( Cpy_u8ACKState <= TWI_U8_ACK ) )
	{
		/* Define local variable to configure TWCR Register bits separately, then to put this value in the Register directly, as TWCR Register bits cannot be configured separately */
		u8 Loc_u8TWCRRegisterValue = 0b00000000;
		
		u16 Loc_u16TimeOutCounter = 0;
				
		/* Step 1: Clear TWI Interrupt Flag */
		SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWINT_BIT );
		
		/* Step 2: Set or Clear Acknowledge State */
		switch ( Cpy_u8ACKState )
		{
			/* Case 1: ACKState = NOT ACK */
			case TWI_U8_NOT_ACK: CLR_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWEA_BIT ); break;
			/* Case 2: ACKState = ACK */
			case TWI_U8_ACK    : SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWEA_BIT ); break;
		}
		
		/* Step 3: Enable TWI peripheral */
		SET_BIT( Loc_u8TWCRRegisterValue, TWI_U8_TWEN_BIT );
		
		/* Step 4: Update TWCR Register, after configuring bits */
		TWI_U8_TWCR_REG = Loc_u8TWCRRegisterValue;
			
        /* Step 5: Wait ( Poll ) until Data is received ( i.e. until Flag ( TWINT ) = 1 ), taking into consideration TimeOutCounter */
        while ( ( GET_BIT( TWI_U8_TWCR_REG, TWI_U8_TWINT_BIT ) == 0 ) && ( Loc_u16TimeOutCounter < TWI_U16_TIME_OUT_MAX_VALUE ) )
        {
	        Loc_u16TimeOutCounter++;
        }
		
		/* Check 1.1: Data is received ( i.e. Status Register ( TWSR ) is updated ) */
		if ( ( ( TWI_U8_TWSR_REG & 0xF8 ) == TWI_U8_MM_DATA_R_ACK ) || ( ( TWI_U8_TWSR_REG & 0xF8 ) == TWI_U8_MM_DATA_R_NOT_ACK ) )
		{
			/* Step 6: Get Data from TWDR Register */
			*Cpy_pu8ReturnedData = TWI_U8_TWDR_REG;
		}
		/* Check 1.2: Data is not received ( i.e. Status Register ( TWSR ) is not updated, or TimeOutCounter reached Max value ) */
		else
		{
			/* Update error state = Data Read Error, Data is not received, or TimeOutCounter reached Max value! */
			Loc_u8ErrorState = TWI_U8_MM_DATA_R_ERR;
		}		
	}
	/* Check 2: Pointer is equal to NULL, or ACKState is not in the valid range  */
	else
	{
		/* Update error state = NULL PTR, Pointer is NULL, or wrong ACKState! */
		Loc_u8ErrorState = TWI_U8_NULL_PTR;
	}
	
    return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TWI_u8TWISetCallBack
 Input: Pointer to Function that takes void and returns void
 Output: u8 Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( TWIInterruptAction ), and then pass this address to ISR function.
*/
u8 TWI_u8TWISetCallBack 		    ( void ( *Cpy_pfTWIInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = TWI_U8_OK;

	/* Check 1: Pointer to Function is not equal to NULL */
	if( Cpy_pfTWIInterruptAction != NULL )
	{
		/* Store the passed address of function ( in APP Layer ) through pointer to function ( TWIInterruptAction ) into Global Pointer to Function ( TWIInterruptAction ). */
		Glb_pfTWIInterruptAction = Cpy_pfTWIInterruptAction;
	}
	/* Check 2: Pointer to Function is equal to NULL */
	else
	{
		/* Update error state = NULL PTR, Pointer to Function is NULL! */
		Loc_u8ErrorState = TWI_U8_NULL_PTR;
	}
	
	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/

/* ISR function prototype of Two Wire Interface ( TWI ) */
void __vector_19( void )	__attribute__((signal));

/*******************************************************************************************************************************************************************/

/* ISR function implementation of TWI */
void __vector_19( void )
{
	/* Check: Global Pointer to Function is not equal to NULL */
	if ( Glb_pfTWIInterruptAction != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Pointer to Function ( TWIInterruptAction ) */
		Glb_pfTWIInterruptAction();
	}
}

/*******************************************************************************************************************************************************************/