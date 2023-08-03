/*
 * EEPROM_Interface.h
 *
 *   Created on: Dec 01, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *	Description: This file contains all Electrically Erasable Programmable Read-Only Memory (EEPROM) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *	  Datasheet: https://ww1.microchip.com/downloads/en/devicedoc/doc0180.pdf
 *    Model No.: AT24C16A - EEPROM
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* EEPROM Includes */

/* SRVL */
#include "../../SRVL/STD_TYPES/STD_TYPES.h"
#include "../../SRVL/BIT_MATH/BIT_MATH.h"
#include "../../SRVL/MCU_Config/MCU_Config.h"

/* MCAL */
#include "../../MCAL/TWI_Driver/TWI_Interface.h"

/*******************************************************************************************************************************************************************/
/* EEPROM Macros */

/* EEPROM Pages ( i.e. 16K ( 2048 Bits * 8 Pages -> 256 Bytes * 8 Pages ) ) */
#define EEPROM_U8_PAGE_0        0
#define EEPROM_U8_PAGE_1        1
#define EEPROM_U8_PAGE_2        2
#define EEPROM_U8_PAGE_3        3
#define EEPROM_U8_PAGE_4        4
#define EEPROM_U8_PAGE_5        5
#define EEPROM_U8_PAGE_6        6
#define EEPROM_U8_PAGE_7        7

/*******************************************************************************************************************************************************************/
/* EEPROM Functions' Prototypes */

u8 EEPROM_u8WriteByte      ( u8 Cpy_u8DevicePageAddress, u8 Cpy_u8ByteAddress, u8 Cpy_u8DataByte );
u8 EEPROM_u8WriteBytes     ( u8 Cpy_u8DevicePageAddress, u8 Cpy_u8ByteAddress, u8 *Cpy_pu8DataBytes, u8 Cpy_u8DataSize );

u8 EEPROM_u8ReadCurrentByte( u8 Cpy_u8DevicePageAddress, u8 *Cpy_pu8ReturnedDataByte );

u8 EEPROM_u8ReadByte       ( u8 Cpy_u8DevicePageAddress, u8 Cpy_u8ByteAddress, u8 *Cpy_pu8ReturnedDataByte );
u8 EEPROM_u8ReadBytes      ( u8 Cpy_u8DevicePageAddress, u8 Cpy_u8ByteAddress, u8 *Cpy_pu8ReturnedDataBytes, u8 Cpy_u8DataSize );

/*******************************************************************************************************************************************************************/

#endif /* EEPROM_INTERFACE_H_ */