/*
 * LED_Interface.h
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Light Emitting Diode (LED) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* LED Includes */

/* SRVL */
#include "../../SRVL/STD_TYPES/STD_TYPES.h"
#include "../../SRVL/BIT_MATH/BIT_MATH.h"

/* MCAL */
#include "../../MCAL/DIO_Driver/DIO_Interface.h"

/*******************************************************************************************************************************************************************/
/* LED Macros */

/* The 8 LEDs counted from 0 to 7 */
#define LED_U8_0		0
#define LED_U8_1		1
#define LED_U8_2		2
#define LED_U8_3		3
#define LED_U8_4		4
#define LED_U8_5		5
#define LED_U8_6		6
#define LED_U8_7		7

/* LED 3 Operations counted from 0 to 2  */
#define LED_U8_ON		0
#define LED_U8_OFF		1
#define LED_U8_TOGGLE	2

/*******************************************************************************************************************************************************************/
/* LED Functions' Prototypes */

u8 LED_u8SetLEDPin ( u8 Cpy_u8LEDId, u8 Cpy_u8Operation );
u8 LED_u8SetLEDPort( u8 Cpy_u8Operation );

/*******************************************************************************************************************************************************************/

#endif /* LED_INTERFACE_H_ */