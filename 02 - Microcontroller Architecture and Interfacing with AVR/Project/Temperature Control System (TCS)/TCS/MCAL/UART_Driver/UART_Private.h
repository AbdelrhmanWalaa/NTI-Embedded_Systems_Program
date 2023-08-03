/*
 * UART_Private.h
 *
 *     Created on: Aug 5, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Universal Asynchronous Receiver Transmitter (UART) registers' locations and description.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/*******************************************************************************************************************************************************************/

/* UART Registers' Locations */

#define	UART_U8_UDR_REG		    *( ( volatile  u8 * ) 0x2C )

#define	UART_U8_UCSRA_REG		*( ( volatile  u8 * ) 0x2B )
#define	UART_U8_UCSRB_REG		*( ( volatile  u8 * ) 0x2A )
#define	UART_U8_UCSRC_REG		*( ( volatile  u8 * ) 0x40 )

#define	UART_U8_UBRRL_REG		*( ( volatile  u8 * ) 0x29 )
#define	UART_U8_UBRRH_REG		*( ( volatile  u8 * ) 0x40 )

/*******************************************************************************************************************************************************************/

/* UART Registers' Description */

/* UART Control and Status Register A - UCSRA */
/* Bit 7 - RXC: UART Receive Complete */
#define UART_U8_RXC_BIT		    7
/* Bit 6 – TXC: UART Transmit Complete */
#define UART_U8_TXC_BIT	    	6
/* Bit 5 - UDRE: UART Data Register Empty */
#define UART_U8_UDRE_BIT    	5
/* Bit 4 - FE: Frame Error */
#define UART_U8_FE_BIT	    	4
/* Bit 3 - DOR: Data OverRun */
#define UART_U8_DOR_BIT	    	3
/* Bit 2 - PE: Parity Error */
#define UART_U8_PE_BIT	    	2
/* Bit 1 - U2X: Double the USART Transmission Speed */
#define UART_U8_U2X_BIT	    	1
/* Bit 0 - MPCM: Multi-processor Communication Mode */
#define UART_U8_MPCM_BIT	    0
/* End of UCSRA Register */

/* UART Control and Status Register B - UCSRB */
/* Bit 7 - RXCIE: RX Complete Interrupt Enable */
#define UART_U8_RXCIE_BIT		7
/* Bit 6 - TXCIE: TX Complete Interrupt Enable */
#define UART_U8_TXCIE_BIT		6
/* Bit 5 - UDRIE: UART Data Register Empty Interrupt Enable */
#define UART_U8_UDRIE_BIT		5
/* Bit 4 - RXEN: Receiver Enable */
#define UART_U8_RXEN_BIT		4
/* Bit 3 - TXEN: Transmitter Enable */
#define UART_U8_TXEN_BIT		3
/* Bit 2 - UCSZ2: Character Size */
#define UART_U8_UCSZ2_BIT		2
/* Bit 1 - RXB8: Receive Data Bit 8 */
#define UART_U8_RXB8_BIT		1
/* Bit 0 - TXB8: Transmit Data Bit 8 */
#define UART_U8_TXB8_BIT		0
/* End of UCSRB Register */

/* UART Control and Status Register C - UCSRC */
/* Bit 7 - URSEL: Register Select */
#define UART_U8_URSEL_BIT		7
/* Bit 6 - UMSEL: USART Mode Select */
#define UART_U8_UMSEL_BIT		6
/* Bit 5:4 - UPM1:0: Parity Mode */
#define UART_U8_UPM1_BIT		5
#define UART_U8_UPM0_BIT		4
/* Bit 3 - USBS: Stop Bit Select */
#define UART_U8_USBS_BIT		3
/* Bit 2:1 - UCSZ1:0: Character Size */
#define UART_U8_UCSZ1_BIT		2
#define UART_U8_UCSZ0_BIT		1
/* Bit 0 - UCPOL: Clock Polarity */
#define UART_U8_UCPOL_BIT		0
/* End of UCSRC Register */

/*******************************************************************************************************************************************************************/

#endif /* UART_PRIVATE_H_ */