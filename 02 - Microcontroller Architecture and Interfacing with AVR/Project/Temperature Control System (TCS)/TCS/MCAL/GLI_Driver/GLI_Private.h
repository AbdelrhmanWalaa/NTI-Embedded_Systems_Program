/*
 * GLI_Private.h
 *
 *     Created on: Apr 25, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Global Interrupt (GLI) registers' locations and description.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef GLI_PRIVATE_H_
#define GLI_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* GLI Registers' Locations */

#define GLI_U8_SREG_REG		    *( ( volatile u8 * ) 0x5F )

/*******************************************************************************************************************************************************************/
/* GLI Registers' Description */

/* The AVR Status Register - SREG: Enable Global Interrupt */
/* Bit 7 -> I: Global Interrupt Enable */
#define GLI_U8_I_BIT		    7
/* End of SREG Register */

/*******************************************************************************************************************************************************************/

#endif /* GLI_PRIVATE_H_ */