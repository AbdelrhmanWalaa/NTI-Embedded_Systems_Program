/*
 * ADC_Config.h
 *
 *     Created on: Apr 28, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Successive Approximation Analog to Digital Converter (SAADC) pre-build configurations, through which user can configure before using the SAADC peripheral.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */
 
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* ADC Configurations' Definitions */

/* ADC Voltage Reference Selections */
#define ADC_U8_AREF_VOLT				    0
#define ADC_U8_AVCC_VOLT				    1
#define ADC_U8_INTERNAL_VOLT 			    2

/* ADC Conversion Result Presentation */
#define	ADC_U8_RIGHT_ADJUST				    0
#define ADC_U8_LEFT_ADJUST				    1

/* ADC Auto Trigger */
#define	ADC_U8_AUTO_TRIGGER_DISABLED	    0
#define ADC_U8_AUTO_TRIGGER_ENABLED		    1

/* ADC Auto Trigger Source Selections */
#define	ADC_U8_FREE_RUNNING_MODE		    0
#define ADC_U8_ANALOG_COMPARATOR		    1
#define ADC_U8_EXI_REQUEST_0			    2
#define ADC_U8_TMR_0_COMPARE_MATCH		    3
#define ADC_U8_TMR_0_OVERFLOW			    4
#define ADC_U8_TMR_1_COMPARE_MATCH_B	    5
#define ADC_U8_TMR_1_OVERFLOW			    6
#define ADC_U8_TMR_1_CAPTURE_EVENT		    7

/* ADC Conversion Complete Interrupt */
#define	ADC_U8_CC_INTERRUPT_DISABLED		0
#define	ADC_U8_CC_INTERRUPT_ENABLED 		1

/* ADC Prescaler Selections */
#define	ADC_U8_DIVISION_FACTOR_2		    0
#define ADC_U8_DIVISION_FACTOR_4		    1
#define ADC_U8_DIVISION_FACTOR_8		    2
#define ADC_U8_DIVISION_FACTOR_16		    3
#define ADC_U8_DIVISION_FACTOR_32		    4
#define ADC_U8_DIVISION_FACTOR_64		    5
#define ADC_U8_DIVISION_FACTOR_128		    6

/* End of Configurations' Definitions */

/*******************************************************************************************************************************************************************/
/* ADC Configurations */

/* ADC Voltage Reference Selection */
/* Options: ADC_U8_AREF_VOLT			// AREF, Internal Vref turned off
 * 			ADC_U8_AVCC_VOLT			// AVCC with external capacitor at AREF pin
 * 			ADC_U8_INTERNAL_VOLT 	    // Internal 2.56V Voltage Reference with external capacitor at AREF pin
 */
#define  ADC_U8_VREF_SELECT				ADC_U8_AVCC_VOLT

/* ADC Conversion Result Presentation Adjust */
/* Options: ADC_U8_RIGHT_ADJUST
 * 			ADC_U8_LEFT_ADJUST
 */
#define  ADC_U8_RESULT_ADJUST			ADC_U8_RIGHT_ADJUST

/* ADC Auto Trigger Enable */
/* Options: ADC_U8_AUTO_TRIGGER_DISABLED
 * 			ADC_U8_AUTO_TRIGGER_ENABLED
 */
#define  ADC_U8_AUTO_TRIGGER_ENABLE		ADC_U8_AUTO_TRIGGER_DISABLED

/* ADC Auto Trigger Source Selection */
/* Options: ADC_U8_FREE_RUNNING_MODE
 * 			ADC_U8_ANALOG_COMPARATOR
 * 			ADC_U8_EXI_REQUEST_0
 * 			ADC_U8_TMR_0_COMPARE_MATCH
 * 			ADC_U8_TMR_0_OVERFLOW
 * 			ADC_U8_TMR_1_COMPARE_MATCH_B
 * 			ADC_U8_TMR_1_OVERFLOW
 * 			ADC_U8_TMR_1_CAPTURE_EVENT
 */
#define  ADC_U8_AUTO_TRIGGER_SOURCE		ADC_U8_FREE_RUNNING_MODE

/* ADC Conversion Complete Interrupt Enable */
/* Options:	ADC_U8_CC_INTERRUPT_DISABLED
 *       	ADC_U8_CC_INTERRUPT_ENABLED
 */
#define  ADC_U8_CC_INTERRUPT_ENABLE		ADC_U8_CC_INTERRUPT_DISABLED

/* ADC Prescaler Selection */
/* Options: ADC_U8_DIVISION_FACTOR_2
 * 			ADC_U8_DIVISION_FACTOR_4
 * 			ADC_U8_DIVISION_FACTOR_8
 * 			ADC_U8_DIVISION_FACTOR_16
 * 			ADC_U8_DIVISION_FACTOR_32
 * 			ADC_U8_DIVISION_FACTOR_64
 * 			ADC_U8_DIVISION_FACTOR_128
 */
#define  ADC_U8_PRESCALER_SELECT		ADC_U8_DIVISION_FACTOR_128

/* TimeOutCounter Max Value */
#define ADC_U16_TIME_OUT_MAX_VALUE		50000

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* ADC_CONFIG_H_ */