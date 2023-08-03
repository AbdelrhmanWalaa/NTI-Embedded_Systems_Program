/*
 * GLI_Program.c
 *
 *     Created on: Apr 25, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Global Interrupt (GLI) functions' implementation.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

/* MCAL */
#include "GLI_Private.h"
#include "GLI_Interface.h"

/*******************************************************************************************************************************************************************/
/*
 Name: GLI_vdEnableGIE
 Input: void
 Output: void
 Description: Function to set I bit in SREG, to enable the Global Interrupt Enable (GIE).
*/
vd GLI_vdEnableGIE ( void )
{
	SET_BIT( GLI_U8_SREG_REG, GLI_U8_I_BIT );
}

/*******************************************************************************************************************************************************************/
/*
 Name: GLI_vdDisableGIE
 Input: void
 Output: void
 Description: Function to clear I bit in SREG, to disable the Global Interrupt Enable (GIE).
*/
vd GLI_vdDisableGIE( void )
{
	CLR_BIT( GLI_U8_SREG_REG, GLI_U8_I_BIT );
}

/*******************************************************************************************************************************************************************/