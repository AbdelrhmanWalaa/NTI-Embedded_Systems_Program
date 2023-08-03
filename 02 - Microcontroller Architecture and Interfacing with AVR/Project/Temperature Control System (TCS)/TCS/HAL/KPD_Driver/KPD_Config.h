/*
 * KPD_Config.h
 *
 *   Created on: Apr 3, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Keypad (KPD) pre-build configurations, through which user can configure before using the KPD peripheral.
 */

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* ATmega32(L) interfacing with KPD: */
/*
 									  -----------                   ----------
									 | ATmega32  |                 |   KPD    |
									 |           |                 |          |
									 |        PC4|---------------->|R1        |
									 |        PC5|---------------->|R2        |
									 |        PC6|---------------->|R3        |
									 |        PC7|---------------->|R4        |
									 |           |                 |          |
									 |        PD4|<----------------|C1        |
									 |        PD5|<----------------|C2        |
									 |        PD6|<----------------|C3        |
									 |        PD7|<----------------|C4        |
									  -----------                   ----------
 */

/*******************************************************************************************************************************************************************/
/* KPD Configurations */

/* KPD Port(s) */
/* Options: DIO_U8_PORTA
			DIO_U8_PORTB
			DIO_U8_PORTC
			DIO_U8_PORTD
 */
#define KPD_U8_INPUT_PORT		DIO_U8_PORTD
#define KPD_U8_OUTPUT_PORT		DIO_U8_PORTC

/* KPD Pins */
/* Options: DIO_U8_PIN0
			DIO_U8_PIN1
			DIO_U8_PIN2
			DIO_U8_PIN3
			DIO_U8_PIN4
			DIO_U8_PIN5
			DIO_U8_PIN6
			DIO_U8_PIN7
 */
/* KPD Rows */
#define KPD_U8_R1_PIN			DIO_U8_PIN4
#define KPD_U8_R2_PIN			DIO_U8_PIN5
#define KPD_U8_R3_PIN			DIO_U8_PIN6
#define KPD_U8_R4_PIN			DIO_U8_PIN7

/* KPD Columns */
#define KPD_U8_C1_PIN			DIO_U8_PIN4
#define KPD_U8_C2_PIN			DIO_U8_PIN5
#define KPD_U8_C3_PIN			DIO_U8_PIN6
#define KPD_U8_C4_PIN			DIO_U8_PIN7

/* KPD Output Pins */
/* Options: 1.Rows:    KPD_U8_R1_PIN
 * 			           KPD_U8_R2_PIN
 *                     KPD_U8_R3_PIN
 *                     KPD_U8_R4_PIN
 *
 *          2.Columns: KPD_U8_C1_PIN
 *                     KPD_U8_C2_PIN
 *                     KPD_U8_C3_PIN
 *                     KPD_U8_C4_PIN
 */
#define KPD_U8_OUTPUT_PIN1		KPD_U8_R1_PIN
#define KPD_U8_OUTPUT_PIN2		KPD_U8_R2_PIN
#define KPD_U8_OUTPUT_PIN3		KPD_U8_R3_PIN
#define KPD_U8_OUTPUT_PIN4		KPD_U8_R4_PIN

/* KPD Configured Keys */
#define KPD_AU8_KEYS	  	  { { '7', '8', '9', '/' },  \
								{ '4', '5', '6', '*' },  \
								{ '1', '2', '3', '-' },  \
								{ 'c', '0', '=', '+' } }

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* KPD_CONFIG_H_ */