/*
 * KPD_Interface.h
 *
 *   Created on: Apr 3, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Keypad (KPD) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */
 
#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* KPD Includes */

/* SRVL */
#include "../../SRVL/STD_TYPES/STD_TYPES.h"
#include "../../SRVL/BIT_MATH/BIT_MATH.h"
#include "../../SRVL/MCU_Config/MCU_Config.h"

/* MCAL */
#include "../../MCAL/DIO_Driver/DIO_Interface.h"

/*******************************************************************************************************************************************************************/
/* KPD Macros */

/* KPD Flag Values */
#define KPD_U8_KEY_NOT_FOUND		0
#define KPD_U8_KEY_FOUND			1

/* KPD Initial Value of Key */
#define KPD_U8_KEY_NOT_PRESSED		0xff

/*******************************************************************************************************************************************************************/
/* KPD Functions' Prototypes */

vd KPD_vdEnableKPD    ( void );
vd KPD_vdDisableKPD   ( void );

u8 KPD_u8GetPressedKey( u8 *ReturnedKeyValue );

/*******************************************************************************************************************************************************************/

#endif /* KPD_INTERFACE_H_ */