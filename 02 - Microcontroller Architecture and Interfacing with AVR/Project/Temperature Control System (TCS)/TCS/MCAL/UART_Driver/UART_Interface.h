/*
 * UART_Interface.h
 *
 *     Created on: Aug 5, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Universal Asynchronous Receiver Transmitter (UART) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* UART Includes */

/* SRVL */
#include "../../SRVL/STD_TYPES/STD_TYPES.h"
#include "../../SRVL/BIT_MATH/BIT_MATH.h"
#include "../../SRVL/MCU_Config/MCU_Config.h"

/*******************************************************************************************************************************************************************/
/* UART Macros */

/* UART Interruption Modes */
#define UART_U8_POLLING_MODE      0
#define UART_U8_RXC_INT_MODE      1
#define UART_U8_UDRE_INT_MODE     2

/*******************************************************************************************************************************************************************/
/* UART Functions' prototypes */

vd UART_vdInitialization ( void );

u8 UART_u8ReceiveByte    ( u8 Cpy_u8InterruptionMode, u8 *Cpy_pu8ReturnedReceiveByte );
u8 UART_u8TransmitByte   ( u8 Cpy_u8InterruptionMode, u8 Cpy_u8TransmitByte );

u8 UART_u8TransmitString ( u8 *Cpy_pu8String );

u8 UART_u8RXCSetCallBack ( void ( *Cpy_pfRXCInterruptAction ) ( void ) );
u8 UART_u8UDRESetCallBack( void ( *Cpy_pfUDREInterruptAction ) ( void ) );
u8 UART_u8TXCSetCallBack ( void ( *Cpy_pfTXCInterruptAction ) ( void ) );

/*******************************************************************************************************************************************************************/

#endif /* UART_INTERFACE_H_ */