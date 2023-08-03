/*
 * DCM_Config.h
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Direct Current Motor (DCM) pre-build configurations, through which user can configure before using the DCM peripheral.
 *    Datasheet: https://datasheetspdf.com/pdf/917207/KYSAN/RF-300CA-11440/1
 *    Model No.: RF-300CA-11440 - DCM
 */

#ifndef DCM_CONFIG_H_
#define DCM_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* ATmega32(L) interfacing with DCM: */
/*
								One-Dirction Mode											Two-Dirction Mode
				 --------------                   ----------				 --------------                   ----------
				|   ATmega32   |                 |   DCM    |				|   ATmega32   |                 |   DCM    |
				|              |                 |          |				|              |                 |          |
				| 	 (OCR0) PB4|---------------->|Ctrl Pin  |				| 	 (OC1B) PD4|---------------->|CW        |
				 -------------- 				  ----------				| 	 (OC1A) PD5|---------------->|CCW       |
				                   					 						 --------------                   ----------
 */

/*******************************************************************************************************************************************************************/
/* DCM Configurations' Definitions */

/* DCM Modes of Rotation */
#define DCM_U8_NORMAL_MODE				0
#define DCM_U8_SPEED_MODE				1

/* DCM Modes of Rotation Direction */
#define DCM_U8_ONE_DIR_MODE				0
#define DCM_U8_TWO_DIR_MODE				1

/* End of Configurations' Definitions */

/*******************************************************************************************************************************************************************/
/* DCM Configurations */

/* DCM Mode of Rotation */
/* Options: DCM_U8_NORMAL_MODE
 *			DCM_U8_SPEED_MODE
 */
#define DCM_U8_ROT_MODE_SELECT			DCM_U8_SPEED_MODE

/* DCM Mode of Rotation Direction */
/* Options: DCM_U8_ONE_DIR_MODE
 *			DCM_U8_TWO_DIR_MODE
 */
#define DCM_U8_DIR_MODE_SELECT			DCM_U8_ONE_DIR_MODE

/* DCM Port */
/* Options: DIO_U8_PORTA
 *			DIO_U8_PORTB
 *			DIO_U8_PORTC
 *			DIO_U8_PORTD
 */
#define DCM_U8_CTRL_PORT				DIO_U8_PORTB

/********************************************/

/*
 * One-Direction Mode Configurations 
 */

/* DCM One-Direction Mode Ctrl Pin */
/* Options: DIO_U8_PIN0			// Normal mode only.
 *			DIO_U8_PIN1			// Normal mode only.
 *			DIO_U8_PIN2			// Normal mode only.
 *			DIO_U8_PIN3			// Both Normal and Speed modes, Can generate PWM using TMR0 ( In case PORTB is selected ).
 *			DIO_U8_PIN4			// Both Normal and Speed modes. Can generate PWM using TMR1 channel B ( In case PORTD is selected ).
 *			DIO_U8_PIN5			// Both Normal and Speed modes. Can generate PWM using TMR1 channel A ( In case PORTD is selected ).
 *			DIO_U8_PIN6			// Normal mode only.
 *			DIO_U8_PIN7			// Both Normal and Speed modes. Can generate PWM using TMR2 ( In case PORTD is selected ).
 */
#define DCM_U8_CTRL_PIN					DIO_U8_PIN3

/* DCM One-Direction TMR ( In case Speed Mode is selected ) */
/* Options: TMR_U8_TMR0
 *			TMR_U8_TMR2
 */
#define DCM_U8_ONE_DIR_TMR				TMR_U8_TMR0

/* End of One-Direction Mode Configurations */

/********************************************/

/*
 * Two-Direction Mode Configurations 
 */

/* DCM Two-Direction Mode Ctrl Pins */
/* Options: DIO_U8_PIN0			// Normal mode only.
 *			DIO_U8_PIN1			// Normal mode only.
 *			DIO_U8_PIN2			// Normal mode only.
 *			DIO_U8_PIN3			// Both Normal and Speed modes, Can generate PWM using TMR0 ( In case PORTB is selected ).
 *			DIO_U8_PIN4			// Both Normal and Speed modes. Can generate PWM using TMR1 channel B ( In case PORTD is selected ).
 *			DIO_U8_PIN5			// Both Normal and Speed modes. Can generate PWM using TMR1 channel A ( In case PORTD is selected ).
 *			DIO_U8_PIN6			// Normal mode only.
 *			DIO_U8_PIN7			// Both Normal and Speed modes. Can generate PWM using TMR2 ( In case PORTD is selected ).
 */
#define DCM_U8_CW_CTRL_PIN				DIO_U8_PIN0
#define DCM_U8_CCW_CTRL_PIN				DIO_U8_PIN1

/* DCM Two-Direction TMR ( In case Speed Mode is selected ) */
#define DCM_U8_TWO_DIR_TMR				TMR_U8_TMR1

/* DCM Ctrl Channels of TMR1 connected to DCM ( In case Speed Mode is selected ) */
/* Options: TMR_U8_NO_CHANNEL
 *		    TMR_U8_TMR_1_CHANNEL_A
 *		    TMR_U8_TMR_1_CHANNEL_B
 */
#define DCM_U8_CW_CTRL_CHANNEL			TMR_U8_NO_CHANNEL
#define DCM_U8_CCW_CTRL_CHANNEL			TMR_U8_NO_CHANNEL

/* End of Two-Direction Mode Configurations */

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* DCM_CONFIG_H_ */