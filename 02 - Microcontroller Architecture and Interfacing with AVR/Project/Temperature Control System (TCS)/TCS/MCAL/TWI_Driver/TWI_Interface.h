/*
 * TWI_Interface.h
 *
 *     Created on: Nov 07, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Two Wire Interface (TWI) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */
 
#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* TWI Includes */

/* SRVL */
#include "../../SRVL/STD_TYPES/STD_TYPES.h"
#include "../../SRVL/BIT_MATH/BIT_MATH.h"
#include "../../SRVL/MCU_Config/MCU_Config.h"

/*******************************************************************************************************************************************************************/
/* TWI Macros */

/* TWI Error States */
#define TWI_U8_OK				1
#define TWI_U8_NULL_PTR			2
#define TWI_U8_MM_START_ERR		3
#define TWI_U8_MM_RESTART_ERR	4
#define TWI_U8_MM_STOP_ERR		5
#define TWI_U8_MM_SLA_ERR		6
#define TWI_U8_MM_SLA_W_ERR		7
#define TWI_U8_MM_SLA_R_ERR		8
#define TWI_U8_MM_DATA_W_ERR	9
#define TWI_U8_MM_DATA_R_ERR	10
#define TWI_U8_SM_SLA_ERR		11

/* TWI Acknowledge States */
#define TWI_U8_NOT_ACK			0
#define TWI_U8_ACK				1

/*******************************************************************************************************************************************************************/
/* TWI Functions' Prototypes */

vd TWI_vdMasterModeInitialization   ( void );
vd TWI_vdSlaveModeInitialization    ( void );

u8 TWI_u8SendSTARTCondition         ( void );
vd TWI_vdSendSTOPCondition          ( void );
u8 TWI_u8SendReSTARTCondition       ( void );

u8 TWI_u8MasterModeSendWriteToSlave ( u8 Cpy_u8SlaveAddress );
u8 TWI_u8MasterModeSendReadFromSlave( u8 Cpy_u8SlaveAddress );

u8 TWI_u8MasterModeWriteData	    ( u8 Cpy_u8Data );
u8 TWI_u8MasterModeReadData		    ( u8 *Cpy_pu8ReturnedData, u8 Cpy_u8ACKState );

u8 TWI_u8TWISetCallBack 		    ( void ( *Cpy_pfTWIInterruptAction ) ( void ) );

/*******************************************************************************************************************************************************************/

#endif /* TWI_INTERFACE_H_ */