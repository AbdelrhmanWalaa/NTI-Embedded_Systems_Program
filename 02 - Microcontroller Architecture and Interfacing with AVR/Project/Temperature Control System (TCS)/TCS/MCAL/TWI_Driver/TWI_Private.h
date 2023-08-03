/*
 * TWI_Private.h
 *
 *     Created on: Nov 07, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Two Wire Interface (TWI) registers' locations and description, and other private Macros.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */
 
#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* TWI Registers' Locations */

#define TWI_U8_TWCR_REG			*( ( volatile  u8 * ) 0x56 )
#define TWI_U8_TWDR_REG			*( ( volatile  u8 * ) 0x23 )
#define TWI_U8_TWAR_REG			*( ( volatile  u8 * ) 0x22 )
#define TWI_U8_TWSR_REG			*( ( volatile  u8 * ) 0x21 )
#define TWI_U8_TWBR_REG			*( ( volatile  u8 * ) 0x20 )

/*******************************************************************************************************************************************************************/
/* TWI Registers' Description */

/* TWCR - TWI Control Register */
/* Bit 7 - TWINT: TWI Interrupt Flag */
#define TWI_U8_TWINT_BIT		7
/* Bit 6 - TWEA: TWI Enable Acknowledge Bit */
#define TWI_U8_TWEA_BIT			6
/* Bit 5 - TWSTA: TWI START Condition Bit */
#define TWI_U8_TWSTA_BIT		5
/* Bit 4 - TWSTO: TWI STOP Condition Bit */
#define TWI_U8_TWSTO_BIT		4
/* Bit 3 - TWWC: TWI Write Collision Flag */
#define TWI_U8_TWWC_BIT		    3
/* Bit 2 - TWEN: TWI Enable Bit */
#define TWI_U8_TWEN_BIT		    2
/* Bit 0 - TWIE: TWI Interrupt Enable */
#define TWI_U8_TWIE_BIT 		0
/* End of TWCR Register */

/* TWSR - TWI Status Register */
/* Bits 1:0 - TWPS: TWI Prescaler Bits */
#define TWI_U8_TWPS1_BIT		1
#define TWI_U8_TWPS0_BIT		0
/* End of TWSR Register */

/* TWAR - TWI (Slave) Address Register */
/* Bit 0 - TWGCE: TWI General Call Reco gnition Enable Bit */
#define TWI_U8_TWGCE_BIT		0
/* End of TWAR Register */

/*******************************************************************************************************************************************************************/

/* TWI has a 7-bit Address Space allows up to 128 Different Slave Addresses, except these Reserved Slave Addresses */
#define TWI_U8_GNRL_CALL_ADDRESS		  0x00
#define TWI_U8_LEAST_RES_ADDRESS		  0xF0
#define TWI_U8_MOST_RES_ADDRESS			  0xFE

/*******************************************************************************************************************************************************************/
/* TWI Status Codes */

/* TWI Status Codes for Master Mode */
/* Master Transmitter Mode */
#define TWI_U8_MM_START                   0x08   // A START condition has been transmitted.
#define TWI_U8_MM_RESTART                 0x10   // A repeated START condition has been transmitted.
#define TWI_U8_MM_SLA_W_ACK               0x18   // SLA + W has been transmitted; ACK has been received.
#define TWI_U8_MM_SLA_W_NOT_ACK           0x20   // SLA + W has been transmitted; NOT ACK has been received.
#define TWI_U8_MM_DATA_W_ACK              0x28   // Data byte has been transmitted; ACK has been received.
#define TWI_U8_MM_DATA_W_NOT_ACK          0x30   // Data byte has been transmitted; NOT ACK has been received.
#define TWI_U8_MM_ARB_LOST                0x38   // Arbitration lost in SLA + W or data bytes ( Transmitter Mode ), or Arbitration lost in SLA+R or NOT ACK bit ( Receiver Mode ).
/* Master Receiver Mode */
#define TWI_U8_MM_SLA_R_ACK               0x40   // SLA + R has been transmitted; ACK has been received.
#define TWI_U8_MM_SLA_R_NOT_ACK           0x48   // SLA + R has been transmitted; NOT ACK has been received.
#define TWI_U8_MM_DATA_R_ACK              0x50   // Data byte has been received; ACK has been received.
#define TWI_U8_MM_DATA_R_NOT_ACK          0x58   // Data byte has been received; NOT ACK has been received.
/* End of Master Mode */

/* TWI Status Codes for Slave Mode */
/* Slave Receiver Mode */
#define TWI_U8_SM_SLA_W_ACK               0x60   // Own SLA + W has been received, ACK has been returned.
#define TWI_U8_SM_SLA_W_ARB_LOST_ACK      0x68   // Arbitration lost in SLA + R/W as master; own SLA + W has been received; ACK has been returned.
#define TWI_U8_SM_GNRL_CALL_ACK           0x70   // General call address has been received; ACK has been returned.
#define TWI_U8_SM_GNRL_CALL_ARB_LOST_ACK  0x78   // Arbitration lost in SLA + R/W as master; General call address has been received; ACK has been returned.
#define TWI_U8_SM_SLA_W_DATA_ACK          0x80   // Previously addressed with own SLA + W; data has been received; ACK has been returned.
#define TWI_U8_SM_SLA_W_DATA_NOT_ACK      0x88   // Previously addressed with own SLA + W; data has been received; NOT ACK has been returned.
#define TWI_U8_SM_GNRL_CALL_DATA_ACK      0x90   // Previously addressed with general call; data has been received; ACK has been returned.
#define TWI_U8_SM_GNRL_CALL_DATA_NOT_ACK  0x98   // Previously addressed with general call; data has been received; NOT ACK has been returned.
#define TWI_U8_SM_STOP_RESTART            0xA0   // A STOP condition or repeated START condition has been received while still addressed as slave.
/* Slave Transmitter Mode */
#define TWI_U8_SM_SLA_R_ACK               0xA8   // Own SLA + R has been received; ACK has been returned.
#define TWI_U8_SM_SLA_R_ARB_LOST_ACK      0xB0   // Arbitration lost in SLA + R/W as master; own SLA + R has been received; ACK has been returned.
#define TWI_U8_SM_DATA_W_ACK              0xB8   // Data byte in TWDR has been transmitted; ACK has been received.
#define TWI_U8_SM_DATA_W_NOT_ACK          0xC0   // Data byte in TWDR has been transmitted; NOT ACK has been received.
#define TWI_U8_SM_LAST_DATA_W_ACK         0xC8   // Last data byte in TWDR has been transmitted ( TWEA = “0” ); ACK has been received.
/* End of Slave Mode */

/* TWI Miscellaneous States */
#define TWI_U8_NO_STATE_AVAILABLE         0xF8   // No relevant state information available; TWINT = “0”.
#define TWI_U8_BUS_ERROR                  0x00   // Bus error due to an illegal START or STOP condition.

/*******************************************************************************************************************************************************************/

#endif /* TWI_PRIVATE_H_ */