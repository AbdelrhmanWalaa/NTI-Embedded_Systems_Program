/*
 * EXI_Private.h
 *
 *     Created on: Apr 25, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all External Interrupt (EXI) registers' locations and description.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */
 
#ifndef EXI_PRIVATE_H_
#define EXI_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* EXI Registers' Locations */

#define EXI_U8_MCUCR_REG		*( ( volatile u8 * ) 0x55 )
#define EXI_U8_MCUCSR_REG		*( ( volatile u8 * ) 0x54 )
#define EXI_U8_GICR_REG			*( ( volatile u8 * ) 0x5B )
#define EXI_U8_GIFR_REG			*( ( volatile u8 * ) 0x5A )

/*******************************************************************************************************************************************************************/
/* EXI Registers' Description */

/* MCU Control Register - MCUCR: Configure External Interrupt 0 & 1 */
/* Interrupt 0:
 * Bit 0, 1 -> ISC00, ISC01: Interrupt Sense Control 0
 */
#define EXI_U8_ISC00_BIT	    0
#define EXI_U8_ISC01_BIT	    1
/* Interrupt 1:
 * Bit 2, 3 -> ISC10, ISC11: Interrupt Sense Control 1
 */
#define EXI_U8_ISC10_BIT	    2
#define EXI_U8_ISC11_BIT	    3
/* End of MCUCR Register */

/* MCU Control and Status Register - MCUCSR: Configure External Interrupt 2 */
/* Interrupt 2 (Asynchronous External Interrupt):
 * Bit 6 -> ISC2: Interrupt Sense Control 2
 */
#define EXI_U8_ISC2_BIT		    6
/* End of MCUCSR Register */

/* General Interrupt Control Register - GICR: Enable External Interrupt 0, 1 and 2 */
/* Bit 6 -> INT0: External Interrupt Request 0 Enable */
#define EXI_U8_INT0_BIT		    6
/* Bit 7 -> INT1: External Interrupt Request 1 Enable */
#define EXI_U8_INT1_BIT		    7
/* Bit 5 -> INT2: External Interrupt Request 2 Enable */
#define EXI_U8_INT2_BIT		    5
/* End of GICR Register */

/* General Interrupt Flag Register - GIFR: Flags of External Interrupt 0, 1 and 2 */
/* Bit 6 -> INTF0: External Interrupt Flag 0 */
#define EXI_U8_INTF0_BIT	    6
/* Bit 7 -> INTF1: External Interrupt Flag 1 */
#define EXI_U8_INTF1_BIT	    7
/* Bit 5 -> INTF2: External Interrupt Flag 2 */
#define EXI_U8_INTF2_BIT	    5
/* End of GIFR Register */

/*******************************************************************************************************************************************************************/

#endif /* EXI_PRIVATE_H_ */