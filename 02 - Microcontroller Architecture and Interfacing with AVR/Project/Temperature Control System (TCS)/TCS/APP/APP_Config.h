/*
 * APP_Config.h
 *
 *   Created on: Jan 10, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application (APP) pre-build configurations, through which user can configure before using the APP.
 */ 

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* APP Configurations */

/* APP Temperatures' Page Number in EEPROM */
/* Options: EEPROM_U8_PAGE_0
 *			EEPROM_U8_PAGE_1
 *			EEPROM_U8_PAGE_2
 *			EEPROM_U8_PAGE_3
 *			EEPROM_U8_PAGE_4
 *			EEPROM_U8_PAGE_5
 *			EEPROM_U8_PAGE_6
 * 			EEPROM_U8_PAGE_7
 */
#define APP_U8_TEMP_PAGE			EEPROM_U8_PAGE_0

/* APP Temperatures' Byte Locations in EEPROM */
#define APP_U8_LOW_TEMP_LOC			0x10
#define APP_U8_HIGH_TEMP_LOC		0x20

/* APP Temperatures' LEDs */
/* Options: LED_U8_0
			LED_U8_1
			LED_U8_2
			LED_U8_3
			LED_U8_4
			LED_U8_5
			LED_U8_6
			LED_U8_7
*/
#define APP_U8_L_RED_LED			LED_U8_4
#define APP_U8_N_GRN_LED			LED_U8_5
#define APP_U8_H_RED_LED			LED_U8_6

/* APP DCM' Speeds */
#define APP_U8_DCM_HALF_SPEED		128
#define APP_U8_DCM_FULL_SPEED		254

/* APP Buzzer Port */
/* Options: DIO_U8_PORTA
			DIO_U8_PORTB
			DIO_U8_PORTC
			DIO_U8_PORTD
 */
#define APP_U8_BUZ_PORT				DIO_U8_PORTB

/* APP Buzzer Pin */
/* Options: DIO_U8_PIN0
			DIO_U8_PIN1
			DIO_U8_PIN2
			DIO_U8_PIN3
			DIO_U8_PIN4
			DIO_U8_PIN5
			DIO_U8_PIN6
			DIO_U8_PIN7
 */
#define APP_U8_BUZ_PIN				DIO_U8_PIN7

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* APP_CONFIG_H_ */