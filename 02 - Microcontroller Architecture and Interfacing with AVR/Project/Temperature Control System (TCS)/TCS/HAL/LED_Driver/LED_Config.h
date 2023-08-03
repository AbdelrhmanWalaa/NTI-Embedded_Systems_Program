/*
 * LED_Config.h
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Light Emitting Diode (LED) pre-build configurations, through which user can configure before using the LCD peripheral.
 */

#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* LED Configurations */

/* LED Port */
/* Options: DIO_U8_PORTA
			DIO_U8_PORTB
			DIO_U8_PORTC
			DIO_U8_PORTD
 */
#define LED_U8_PORT			DIO_U8_PORTB

/* LED Pin(s) */
/* Options: DIO_U8_PIN0
			DIO_U8_PIN1
			DIO_U8_PIN2
			DIO_U8_PIN3
			DIO_U8_PIN4
			DIO_U8_PIN5
			DIO_U8_PIN6
			DIO_U8_PIN7
 */
#define LED_U8_0_PIN		DIO_U8_PIN0
#define LED_U8_1_PIN		DIO_U8_PIN1
#define LED_U8_2_PIN		DIO_U8_PIN2
#define LED_U8_3_PIN		DIO_U8_PIN3
#define LED_U8_4_PIN		DIO_U8_PIN4
#define LED_U8_5_PIN		DIO_U8_PIN5
#define LED_U8_6_PIN		DIO_U8_PIN6
#define LED_U8_7_PIN		DIO_U8_PIN7

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* LED_CONFIG_H_ */