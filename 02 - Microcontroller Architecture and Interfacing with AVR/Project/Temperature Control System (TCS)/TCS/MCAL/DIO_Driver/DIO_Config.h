/*
 * DIO_Config.h
 *
 *     Created on: Mar 31, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Digital Input Output (DIO) pre-build configurations, through which user can configure before using the DIO peripheral.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */
 
#ifndef DIO_CONFIG_H_
#define DIO_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* ATmega32 Pinouts: */
/*
							  PDIP
						  -------------
		   (XCK/T0) PB0 -| 1		40 |- PA0 (ADC0)
			   (T1)	PB1	-| 2		39 |- PA1 (ADC1)
		(INT2/AIN0)	PB2	-| 3		38 |- PA2 (ADC2)
		 (OC0/AIN1)	PB3	-| 4		37 |- PA3 (ADC3)
			   (SS)	PB4	-| 5		36 |- PA4 (ADC4)
			 (MOSI)	PB5	-| 6		35 |- PA5 (ADC5)
			 (MISO)	PB6	-| 7		34 |- PA6 (ADC6)
			  (SCK)	PB7	-| 8		33 |- PA7 (ADC7)
				  RESET -| 9		32 |- AREF
					VCC	-| 10		31 |- GND
					GND	-| 11		30 |- AVCC
				  XTAL2	-| 12		29 |- PC0 (TOSC2)
				  XTAL1	-| 13		28 |- PC1 (TOSC1)
			  (RXD)	PD0 -| 14		27 |- PC2 (TDI)
			  (TXD)	PD1 -| 15		26 |- PC3 (TDO)
			 (INT0)	PD2 -| 16		25 |- PC4 (TMS)
			 (INT1)	PD3 -| 17		24 |- PC5 (TCK)
			 (OC1B)	PD4 -| 18		23 |- PC6 (SDA)
			 (OC1A)	PD5 -| 19		22 |- PC7 (SCL)
			  (ICP)	PD6 -| 20		21 |- PD7 (OC2)
					 	  -------------
 */

/*******************************************************************************************************************************************************************/
/* DIO Configurations' Definitions */

/* Initial Pin Directions */
#define DIO_U8_INITIAL_INPUT				0
#define DIO_U8_INITIAL_OUTPUT				1

/* Initial Pin Values */
#define DIO_U8_INPUT_FLOATING				0
#define DIO_U8_INPUT_PULLUP_RESISTOR		1
#define DIO_U8_OUTPUT_LOW					0
#define DIO_U8_OUTPUT_HIGH					1

/* End of Configurations' Definitions */

/*******************************************************************************************************************************************************************/
/* DIO Configurations */

/* Initial Directions of all Pins */
/* Options: DIO_U8_INITIAL_INPUT
 * 			DIO_U8_INITIAL_OUTPUT
 */

/* PORTA */
#define DIO_U8_PA0_INITIAL_DIRECTION		DIO_U8_INITIAL_INPUT
#define DIO_U8_PA1_INITIAL_DIRECTION		DIO_U8_INITIAL_INPUT
#define DIO_U8_PA2_INITIAL_DIRECTION		DIO_U8_INITIAL_INPUT
#define DIO_U8_PA3_INITIAL_DIRECTION        DIO_U8_INITIAL_INPUT
#define DIO_U8_PA4_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT
#define DIO_U8_PA5_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT
#define DIO_U8_PA6_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT
#define DIO_U8_PA7_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT

/* PORTB */
#define DIO_U8_PB0_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT
#define DIO_U8_PB1_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT
#define DIO_U8_PB2_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT
#define DIO_U8_PB3_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT
#define DIO_U8_PB4_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT
#define DIO_U8_PB5_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT
#define DIO_U8_PB6_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT
#define DIO_U8_PB7_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT

/* PORTC */
#define DIO_U8_PC0_INITIAL_DIRECTION        DIO_U8_INITIAL_INPUT
#define DIO_U8_PC1_INITIAL_DIRECTION        DIO_U8_INITIAL_INPUT
#define DIO_U8_PC2_INITIAL_DIRECTION        DIO_U8_INITIAL_INPUT
#define DIO_U8_PC3_INITIAL_DIRECTION        DIO_U8_INITIAL_INPUT
#define DIO_U8_PC4_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT
#define DIO_U8_PC5_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT
#define DIO_U8_PC6_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT
#define DIO_U8_PC7_INITIAL_DIRECTION        DIO_U8_INITIAL_OUTPUT

/* PORTD */
#define DIO_U8_PD0_INITIAL_DIRECTION        DIO_U8_INITIAL_INPUT
#define DIO_U8_PD1_INITIAL_DIRECTION        DIO_U8_INITIAL_INPUT
#define DIO_U8_PD2_INITIAL_DIRECTION        DIO_U8_INITIAL_INPUT
#define DIO_U8_PD3_INITIAL_DIRECTION        DIO_U8_INITIAL_INPUT
#define DIO_U8_PD4_INITIAL_DIRECTION        DIO_U8_INITIAL_INPUT
#define DIO_U8_PD5_INITIAL_DIRECTION        DIO_U8_INITIAL_INPUT
#define DIO_U8_PD6_INITIAL_DIRECTION        DIO_U8_INITIAL_INPUT
#define DIO_U8_PD7_INITIAL_DIRECTION        DIO_U8_INITIAL_INPUT

/* Initial Values of all Pins */
/* Options: DIO_U8_INPUT_FLOATING
 * 			DIO_U8_INPUT_PULLUP_RESISTOR
 * 			DIO_U8_OUTPUT_LOW
 * 			DIO_U8_OUTPUT_HIGH
 */

/* PORTA */
#define DIO_U8_PA0_INITIAL_VALUE			DIO_U8_INPUT_FLOATING
#define DIO_U8_PA1_INITIAL_VALUE			DIO_U8_INPUT_FLOATING
#define DIO_U8_PA2_INITIAL_VALUE			DIO_U8_INPUT_FLOATING
#define DIO_U8_PA3_INITIAL_VALUE	        DIO_U8_INPUT_FLOATING
#define DIO_U8_PA4_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW
#define DIO_U8_PA5_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW
#define DIO_U8_PA6_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW
#define DIO_U8_PA7_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW

/* PORTB */
#define DIO_U8_PB0_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW
#define DIO_U8_PB1_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW
#define DIO_U8_PB2_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW
#define DIO_U8_PB3_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW
#define DIO_U8_PB4_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW
#define DIO_U8_PB5_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW
#define DIO_U8_PB6_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW
#define DIO_U8_PB7_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW

/* PORTC */
#define DIO_U8_PC0_INITIAL_VALUE	        DIO_U8_INPUT_FLOATING
#define DIO_U8_PC1_INITIAL_VALUE	        DIO_U8_INPUT_FLOATING
#define DIO_U8_PC2_INITIAL_VALUE	        DIO_U8_INPUT_FLOATING
#define DIO_U8_PC3_INITIAL_VALUE	        DIO_U8_INPUT_FLOATING
#define DIO_U8_PC4_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW
#define DIO_U8_PC5_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW
#define DIO_U8_PC6_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW
#define DIO_U8_PC7_INITIAL_VALUE	        DIO_U8_OUTPUT_LOW

/* PORTD */
#define DIO_U8_PD0_INITIAL_VALUE	        DIO_U8_INPUT_FLOATING
#define DIO_U8_PD1_INITIAL_VALUE	        DIO_U8_INPUT_FLOATING
#define DIO_U8_PD2_INITIAL_VALUE	        DIO_U8_INPUT_PULLUP_RESISTOR
#define DIO_U8_PD3_INITIAL_VALUE	        DIO_U8_INPUT_FLOATING
#define DIO_U8_PD4_INITIAL_VALUE	        DIO_U8_INPUT_PULLUP_RESISTOR
#define DIO_U8_PD5_INITIAL_VALUE	        DIO_U8_INPUT_PULLUP_RESISTOR
#define DIO_U8_PD6_INITIAL_VALUE	        DIO_U8_INPUT_PULLUP_RESISTOR
#define DIO_U8_PD7_INITIAL_VALUE	        DIO_U8_INPUT_PULLUP_RESISTOR

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* DIO_CONFIG_H_ */