/*
 * EEPROM_Program.c
 *
 *   Created on: Dec 01, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Electrically Erasable Programmable Read-Only Memory (EEPROM) functions' implementation.
 *    Datasheet: https://ww1.microchip.com/downloads/en/devicedoc/doc0180.pdf
 *    Model No.: AT24C16A - EEPROM
 */

/* HAL */
#include "EEPROM_Private.h"
#include "EEPROM_Config.h"
#include "EEPROM_Interface.h"

/*******************************************************************************************************************************************************************/
/*
 Name: EEPROM_u8WriteByte
 Input: u8 DevicePageAddress, u8 ByteAddress, and u8 DataByte
 Output: u8 Error or No Error
 Description: Function to write Data Byte in an EEPROM Address Location.
*/
u8 EEPROM_u8WriteByte      ( u8 Cpy_u8DevicePageAddress, u8 Cpy_u8ByteAddress, u8 Cpy_u8DataByte )
{
    /* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

    /* Byte Write:
        --------------------------------------------------------------------------------
       | START | Device Address + W | ACK | Byte Address | ACK | Data Byte | ACK | STOP |
        --------------------------------------------------------------------------------
    */
	
	/* Check 1: DevicePageAddress is in the valid range */
	if ( Cpy_u8DevicePageAddress <= EEPROM_U8_PAGE_7 )
	{
		/* Step 1: Send START Condition */
		Loc_u8ErrorState = TWI_u8SendSTARTCondition();

		/* Check 1.1: START Condition is not transmitted */
		if ( Loc_u8ErrorState == TWI_U8_MM_START_ERR )
		{
			/* Update error state = NOK, START Condition is not transmitted! */
			Loc_u8ErrorState = STD_TYPES_NOK;
		}

		/* Step 2: Send Device Address with Write Operation ( i.e. SLA + W ) */
		Loc_u8ErrorState = TWI_u8MasterModeSendWriteToSlave( ( EEPROM_U8_DEVICE_ADDRESS ) | ( Cpy_u8DevicePageAddress << 1 ) );

		/* Check 1.2: Device Address ( i.e. SLA + W ) is not transmitted */
		if ( Loc_u8ErrorState == TWI_U8_MM_SLA_W_ERR )
		{
			/* Update error state = NOK, Device Address ( i.e. SLA + W ) is not transmitted! */
			Loc_u8ErrorState = STD_TYPES_NOK;
		}

		/* Step 3: Send Byte Address Location in EEPROM */
		Loc_u8ErrorState = TWI_u8MasterModeWriteData( Cpy_u8ByteAddress );

		/* Check 1.3: Byte Address is not transmitted */
		if ( Loc_u8ErrorState == TWI_U8_MM_DATA_W_ERR )
		{
			/* Update error state = NOK, Byte Address is not transmitted! */
			Loc_u8ErrorState = STD_TYPES_NOK;
		}

		/* Step 4: Send Data Byte */
		Loc_u8ErrorState = TWI_u8MasterModeWriteData( Cpy_u8DataByte );

		/* Check 1.4: Data Byte is not transmitted */
		if ( Loc_u8ErrorState == TWI_U8_MM_DATA_W_ERR )
		{
			/* Update error state = NOK, Data Byte is not transmitted! */
			Loc_u8ErrorState = STD_TYPES_NOK;
		}

		/* Step 5: Send STOP Condition */
		TWI_vdSendSTOPCondition();

		/* Check 1.5: Everything is transmitted */
		if ( Loc_u8ErrorState == TWI_U8_OK )
		{
			/* Update error state = OK, Everything is transmitted! */
			Loc_u8ErrorState = STD_TYPES_OK;
		}

		/* Step 6: Delay twr ( i.e. Write Cycle Time ) = +5 ms */
		_delay_ms(10);
	}
	/* Check 2: DevicePageAddress is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong DevicePageAddress! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}

    return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: EEPROM_u8WriteBytes
 Input: u8 DevicePageAddress, u8 ByteAddress, Pointer to u8 DataBytes, and u8 DataSize
 Output: u8 Error or No Error
 Description: Function to write Data Bytes starting from an EEPROM Address Location.
*/
u8 EEPROM_u8WriteBytes     ( u8 Cpy_u8DevicePageAddress, u8 Cpy_u8ByteAddress, u8 *Cpy_pu8DataBytes, u8 Cpy_u8DataSize )
{
    /* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

    /* Bytes Write:
        -------------------------------------------------------------------------------------------
       | START| Device Address + W | ACK | Byte Address | ACK | Data Byte | ACK | ... | ACK | STOP |
        -------------------------------------------------------------------------------------------
    */

    /* Check 1: DevicePageAddress is in the valid range, and Pointer is not equal to NULL */
    if ( ( Cpy_u8DevicePageAddress <= EEPROM_U8_PAGE_7 ) && ( Cpy_pu8DataBytes != NULL ) )
    {
        /* Step 1: Send START Condition */
        Loc_u8ErrorState = TWI_u8SendSTARTCondition();

        /* Check 1.1: START Condition is not transmitted */
        if ( Loc_u8ErrorState == TWI_U8_MM_START_ERR )
        {
            /* Update error state = NOK, START Condition is not transmitted! */
            Loc_u8ErrorState = STD_TYPES_NOK;
        }

        /* Step 2: Send Device Address with Write Operation ( i.e. SLA + W ) */
        Loc_u8ErrorState = TWI_u8MasterModeSendWriteToSlave( ( EEPROM_U8_DEVICE_ADDRESS ) | ( Cpy_u8DevicePageAddress << 1 ) );

        /* Check 1.2: Device Address ( i.e. SLA + W ) is not transmitted */
        if ( Loc_u8ErrorState == TWI_U8_MM_SLA_W_ERR )
        {
            /* Update error state = NOK, Device Address ( i.e. SLA + W ) is not transmitted! */
            Loc_u8ErrorState = STD_TYPES_NOK;
        }

        /* Step 3: Send Byte Address Location in EEPROM */
        Loc_u8ErrorState = TWI_u8MasterModeWriteData( Cpy_u8ByteAddress );

        /* Check 1.3: Byte Address is not transmitted */
        if ( Loc_u8ErrorState == TWI_U8_MM_DATA_W_ERR )
        {
            /* Update error state = NOK, Byte Address is not transmitted! */
            Loc_u8ErrorState = STD_TYPES_NOK;
        }

        /* Loop: Until reaching the end DataBytes array */
        for ( u8 Loc_u8Counter = 0; Loc_u8Counter < Cpy_u8DataSize; Loc_u8Counter++ )
        {
            /* Step 4: Send Data Byte */
            Loc_u8ErrorState = TWI_u8MasterModeWriteData( Cpy_pu8DataBytes[Loc_u8Counter] );
            
            /* Check 1.4: Data Byte is not transmitted */
            if ( Loc_u8ErrorState == TWI_U8_MM_DATA_W_ERR )
            {
                /* Update error state = NOK, Data Byte is not transmitted! */
                Loc_u8ErrorState = STD_TYPES_NOK;
                break;
            }
        }

        /* Step 5: Send STOP Condition */
        TWI_vdSendSTOPCondition();

        /* Check 1.5: Everything is transmitted */
        if ( Loc_u8ErrorState == TWI_U8_OK )
        {
            /* Update error state = OK, Everything is transmitted! */
            Loc_u8ErrorState = STD_TYPES_OK;
        }

        /* Step 6: Delay twr ( i.e. Write Cycle Time ) = +5 ms */
        _delay_ms(10);
    }
    /* Check 2: DevicePageAddress is not in the valid range, or Pointer is equal to NULL */
    else
    {
        /* Update error state = NOK, wrong DevicePageAddress, or Pointer is NULL! */
        Loc_u8ErrorState = STD_TYPES_NOK;
    }

    return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: EEPROM_u8ReadCurrentByte
 Input: u8 DevicePageAddress, and Pointer to u8 ReturnedDataByte
 Output: u8 Error or No Error
 Description: Function to read Data Byte from current EEPROM Address Location.
*/
u8 EEPROM_u8ReadCurrentByte( u8 Cpy_u8DevicePageAddress, u8 *Cpy_pu8ReturnedDataByte )
{
    /* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

    /* Current Byte Read:  
        --------------------------------------------------------------
       | START | Device Address + R | ACK | Data Byte | NO ACK | STOP |
        --------------------------------------------------------------
    */

    /* Check 1: DevicePageAddress is in the valid range, and Pointer is not equal to NULL */
    if ( ( Cpy_u8DevicePageAddress <= EEPROM_U8_PAGE_7 ) && ( Cpy_pu8ReturnedDataByte != NULL ) )
    {
        /* Step 1: Send START Condition */
        Loc_u8ErrorState = TWI_u8SendSTARTCondition();

        /* Check 1.1: START Condition is not transmitted */
        if ( Loc_u8ErrorState == TWI_U8_MM_START_ERR )
        {
            /* Update error state = NOK, START Condition is not transmitted! */
            Loc_u8ErrorState = STD_TYPES_NOK;
        }
        
        /* Step 2: Send Device Address with Read Operation ( i.e. SLA + R ) */
        Loc_u8ErrorState = TWI_u8MasterModeSendReadFromSlave( ( EEPROM_U8_DEVICE_ADDRESS ) | ( Cpy_u8DevicePageAddress << 1 ) );

        /* Check 1.2: Device Address ( i.e. SLA + R ) is not transmitted */
        if ( Loc_u8ErrorState == TWI_U8_MM_SLA_R_ERR )
        {
            /* Update error state = NOK, Device Address ( i.e. SLA + R ) is not transmitted! */
            Loc_u8ErrorState = STD_TYPES_NOK;
        }

        /* Step 3: Read Data Byte */
        Loc_u8ErrorState = TWI_u8MasterModeReadData( Cpy_pu8ReturnedDataByte, TWI_U8_NOT_ACK );

        /* Check 1.3: Data Byte is not received */
        if ( Loc_u8ErrorState == TWI_U8_MM_DATA_R_ERR )
        {
            /* Update error state = NOK, Data Byte is not received! */
            Loc_u8ErrorState = STD_TYPES_NOK;
        }

        /* Step 4: Send STOP Condition */
        TWI_vdSendSTOPCondition();

        /* Check 1.4: Everything is transmitted and received */
        if ( Loc_u8ErrorState == TWI_U8_OK )
        {
            /* Update error state = OK, Everything is transmitted and received! */
            Loc_u8ErrorState = STD_TYPES_OK;
        }
    }
    /* Check 2: DevicePageAddress is not in the valid range, or Pointer is equal to NULL */
    else
    {
        /* Update error state = NOK, wrong DevicePageAddress, or Pointer is NULL! */
        Loc_u8ErrorState = STD_TYPES_NOK;
    }

    return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: EEPROM_u8ReadByte
 Input: u8 DevicePageAddress, u8 ByteAddress, and Pointer to u8 ReturnedDataByte
 Output: u8 Error or No Error
 Description: Function to read Data Byte from an EEPROM Address Location.
*/
u8 EEPROM_u8ReadByte       ( u8 Cpy_u8DevicePageAddress, u8 Cpy_u8ByteAddress, u8 *Cpy_pu8ReturnedDataByte )
{
    /* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

    /* Dummy Write and Byte Read:
        ----------------------------------------------------------------------------------------------------------------------
       | START | Device Address + W | ACK | Byte Address | ACK | START | Device Address + R | ACK | Data Byte | NO ACK | STOP |
        ----------------------------------------------------------------------------------------------------------------------
    */

    /* Check 1: DevicePageAddress is in the valid range, and Pointer is not equal to NULL */
    if ( ( Cpy_u8DevicePageAddress <= EEPROM_U8_PAGE_7 ) && ( Cpy_pu8ReturnedDataByte != NULL ) )
    {
	    /* Step 1: Send START Condition */
	    Loc_u8ErrorState = TWI_u8SendSTARTCondition();

	    /* Check 1.1: START Condition is not transmitted */
	    if ( Loc_u8ErrorState == TWI_U8_MM_START_ERR )
	    {
		    /* Update error state = NOK, START Condition is not transmitted! */
		    Loc_u8ErrorState = STD_TYPES_NOK;
	    }

	    /* Step 2: Send Device Address with Dummy Write Operation ( i.e. SLA + W ) */
	    Loc_u8ErrorState = TWI_u8MasterModeSendWriteToSlave( ( EEPROM_U8_DEVICE_ADDRESS ) | ( Cpy_u8DevicePageAddress << 1 ) );

	    /* Check 1.2: Device Address ( i.e. SLA + W ) is not transmitted */
	    if ( Loc_u8ErrorState == TWI_U8_MM_SLA_W_ERR )
	    {
		    /* Update error state = NOK, Device Address ( i.e. SLA + W ) is not transmitted! */
		    Loc_u8ErrorState = STD_TYPES_NOK;
	    }

	    /* Step 3: Send Byte Address Location in EEPROM */
	    Loc_u8ErrorState = TWI_u8MasterModeWriteData( Cpy_u8ByteAddress );

	    /* Check 1.3: Byte Address is not transmitted */
	    if ( Loc_u8ErrorState == TWI_U8_MM_DATA_W_ERR )
	    {
		    /* Update error state = NOK, Byte Address is not transmitted! */
		    Loc_u8ErrorState = STD_TYPES_NOK;
	    }

	    /* Step 4: Send ReSTART Condition */
	    Loc_u8ErrorState = TWI_u8SendReSTARTCondition();

	    /* Check 1.4: ReSTART Condition is not transmitted */
	    if ( Loc_u8ErrorState == TWI_U8_MM_START_ERR )
	    {
		    /* Update error state = NOK, ReSTART Condition is not transmitted! */
		    Loc_u8ErrorState = STD_TYPES_NOK;
	    }

	    /* Step 5: Send Device Address with Read Operation ( i.e. SLA + R ) */
	    Loc_u8ErrorState = TWI_u8MasterModeSendReadFromSlave( ( EEPROM_U8_DEVICE_ADDRESS ) | ( Cpy_u8DevicePageAddress << 1 ) );

	    /* Check 1.5: Device Address ( i.e. SLA + R ) is not transmitted */
	    if ( Loc_u8ErrorState == TWI_U8_MM_SLA_R_ERR )
	    {
		    /* Update error state = NOK, Device Address ( i.e. SLA + R ) is not transmitted! */
		    Loc_u8ErrorState = STD_TYPES_NOK;
	    }

	    /* Step 6: Read Data Byte */
	    Loc_u8ErrorState = TWI_u8MasterModeReadData( Cpy_pu8ReturnedDataByte, TWI_U8_NOT_ACK );

	    /* Check 1.6: Data Byte is not received */
	    if ( Loc_u8ErrorState == TWI_U8_MM_DATA_R_ERR )
	    {
		    /* Update error state = NOK, Data Byte is not received! */
		    Loc_u8ErrorState = STD_TYPES_NOK;
	    }

	    /* Step 7: Send STOP Condition */
	    TWI_vdSendSTOPCondition();

	    /* Check 1.7: Everything is transmitted and received */
	    if ( Loc_u8ErrorState == TWI_U8_OK )
	    {
		    /* Update error state = OK, Everything is transmitted and received! */
		    Loc_u8ErrorState = STD_TYPES_OK;
	    }
    }
    /* Check 2: DevicePageAddress is not in the valid range, or Pointer is equal to NULL */
    else
    {
	    /* Update error state = NOK, wrong DevicePageAddress, or Pointer is NULL! */
	    Loc_u8ErrorState = STD_TYPES_NOK;
    }

    return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: EEPROM_u8ReadBytes
 Input: u8 DevicePageAddress, u8 ByteAddress, Pointer to u8 ReturnedDataBytes, and u8 DataSize
 Output: u8 Error or No Error
 Description: Function to read Data Bytes starting from an EEPROM Address Location.
*/
u8 EEPROM_u8ReadBytes      ( u8 Cpy_u8DevicePageAddress, u8 Cpy_u8ByteAddress, u8 *Cpy_pu8ReturnedDataBytes, u8 Cpy_u8DataSize )
{
    /* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

    /* Dummy Write and Bytes Read:
        ----------------------------------------------------------------------------------------------------------------------------------
       | START | Device Address + W | ACK | Byte Address | ACK | START | Device Address + R | ACK | Data Byte | ACK | ... | NO ACK | STOP |
        ----------------------------------------------------------------------------------------------------------------------------------
    */

    /* Check 1: DevicePageAddress is in the valid range, and Pointer is not equal to NULL */
    if ( ( Cpy_u8DevicePageAddress <= EEPROM_U8_PAGE_7 ) && ( Cpy_pu8ReturnedDataBytes != NULL ) )
    {
        /* Step 1: Send START Condition */
        Loc_u8ErrorState = TWI_u8SendSTARTCondition();

        /* Check 1.1: START Condition is not transmitted */
        if ( Loc_u8ErrorState == TWI_U8_MM_START_ERR )
        {
            /* Update error state = NOK, START Condition is not transmitted! */
            Loc_u8ErrorState = STD_TYPES_NOK;
        }

        /* Step 2: Send Device Address with Dummy Write Operation ( i.e. SLA + W ) */
        Loc_u8ErrorState = TWI_u8MasterModeSendWriteToSlave( ( EEPROM_U8_DEVICE_ADDRESS ) | ( Cpy_u8DevicePageAddress << 1 ) );

        /* Check 1.2: Device Address ( i.e. SLA + W ) is not transmitted */
        if ( Loc_u8ErrorState == TWI_U8_MM_SLA_W_ERR )
        {
            /* Update error state = NOK, Device Address ( i.e. SLA + W ) is not transmitted! */
            Loc_u8ErrorState = STD_TYPES_NOK;
        }

        /* Step 3: Send Byte Address Location in EEPROM */
        Loc_u8ErrorState = TWI_u8MasterModeWriteData( Cpy_u8ByteAddress );

        /* Check 1.3: Byte Address is not transmitted */
        if ( Loc_u8ErrorState == TWI_U8_MM_DATA_W_ERR )
        {
            /* Update error state = NOK, Byte Address is not transmitted! */
            Loc_u8ErrorState = STD_TYPES_NOK;
        }

        /* Step 4: Send ReSTART Condition */
        Loc_u8ErrorState = TWI_u8SendReSTARTCondition();

        /* Check 1.4: ReSTART Condition is not transmitted */
        if ( Loc_u8ErrorState == TWI_U8_MM_RESTART_ERR )
        {
            /* Update error state = NOK, ReSTART Condition is not transmitted! */
            Loc_u8ErrorState = STD_TYPES_NOK;
        }

        /* Step 5: Send Device Address with Read Operation ( i.e. SLA + R ) */
        Loc_u8ErrorState = TWI_u8MasterModeSendReadFromSlave( ( EEPROM_U8_DEVICE_ADDRESS ) | ( Cpy_u8DevicePageAddress << 1 ) );

        /* Check 1.5: Device Address ( i.e. SLA + R ) is not transmitted */
        if ( Loc_u8ErrorState == TWI_U8_MM_SLA_R_ERR )
        {
            /* Update error state = NOK, Device Address ( i.e. SLA + R ) is not transmitted! */
            Loc_u8ErrorState = STD_TYPES_NOK;
        }

        /* Loop: Until reaching the end ReturnedDataBytes array */
        for ( u8 Loc_u8Counter = 0; Loc_u8Counter < Cpy_u8DataSize; Loc_u8Counter++ )
        {
            /* Step 6: Read Data Byte */
            Loc_u8ErrorState = TWI_u8MasterModeReadData( &Cpy_pu8ReturnedDataBytes[Loc_u8Counter], TWI_U8_ACK );

            /* Check 1.6: Data Byte is not received */
            if ( Loc_u8ErrorState == TWI_U8_MM_DATA_R_ERR )
            {
                /* Update error state = NOK, Data Byte is not received! */
                Loc_u8ErrorState = STD_TYPES_NOK;
                break;
            }        
        }

        /* Step 7: Send STOP Condition */
        TWI_vdSendSTOPCondition();

        /* Check 1.7: Everything is transmitted and received */
        if ( Loc_u8ErrorState == TWI_U8_OK )
        {
            /* Update error state = OK, Everything is transmitted and received! */
            Loc_u8ErrorState = STD_TYPES_OK;
        }
    }
    /* Check 2: DevicePageAddress is not in the valid range, or Pointer is equal to NULL */
    else
    {
        /* Update error state = NOK, wrong DevicePageAddress, or Pointer is NULL! */
        Loc_u8ErrorState = STD_TYPES_NOK;
    }

    return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/