/*
 * TMR_Config.h
 *
 *     Created on: Jul 27, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Timers (TMR) pre-build configurations, through which user can configure before using the TMR peripheral.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef TMR_CONFIG_H_
#define TMR_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* TMR Configurations' Definitions */

/*
 * 8-bit Timer/Counter0 Configurations' Definitions
 */

/* TMR0 Waveform Generation Modes */
#define TMR_U8_TMR_0_NORMAL_MODE							0
#define TMR_U8_TMR_0_PWM_PHASE_CORRECT_MODE					1
#define TMR_U8_TMR_0_CTC_MODE								2
#define TMR_U8_TMR_0_FAST_PWM_MODE							3

/* TMR0 Compare Match Output Modes */
#define TMR_U8_TMR_0_DISCONNECT_OC0_PIN						0
#define TMR_U8_TMR_0_TOG_OC0_PIN							1
#define TMR_U8_TMR_0_CLR_OC0_PIN							2
#define TMR_U8_TMR_0_SET_OC0_PIN							3

/* TMR0 Interrupt Sources */
#define TMR_U8_TMR_0_NO_INTERRUPT							0
#define TMR_U8_TMR_0_COMP_INTERRUPT							1
#define TMR_U8_TMR_0_OVF_INTERRUPT 							2

/* TMR0 Clock Sources */
#define TMR_U8_TMR_0_NO_CLOCK_SOURCE						0
#define TMR_U8_TMR_0_NO_PRESCALER							1
#define TMR_U8_TMR_0_8_PRESCALER							2
#define TMR_U8_TMR_0_64_PRESCALER							3
#define TMR_U8_TMR_0_256_PRESCALER							4
#define TMR_U8_TMR_0_1024_PRESCALER							5
#define TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_FALL_EDGE		6
#define TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_RISE_EDGE		7

/* End of Timer/Counter0 Configurations' Definitions */

/*****************************************************/

/*
 * 16-bit Timer/Counter1 Configurations' Definitions
 */

/* TMR1 Waveform Generation Modes */
#define TMR_U8_TMR_1_NORMAL_MODE							0
#define TMR_U8_TMR_1_PWM_PHASE_CORRECT_8_BIT_MODE			1
#define TMR_U8_TMR_1_PWM_PHASE_CORRECT_9_BIT_MODE			2
#define TMR_U8_TMR_1_PWM_PHASE_CORRECT_10_BIT_MODE			3
#define TMR_U8_TMR_1_CTC_OCR1A_TOP							4
#define TMR_U8_TMR_1_FAST_PWM_8_BIT_MODE					5
#define TMR_U8_TMR_1_FAST_PWM_9_BIT_MODE					6
#define TMR_U8_TMR_1_FAST_PWM_10_BIT_MODE					7
#define TMR_U8_TMR_1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_TOP	8
#define TMR_U8_TMR_1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_TOP	9
#define TMR_U8_TMR_1_PWM_PHASE_CORRECT_ICR1_TOP				10
#define TMR_U8_TMR_1_PWM_PHASE_CORRECT_OCR1A_TOP			11
#define TMR_U8_TMR_1_CTC_ICR1_TOP							12
#define TMR_U8_TMR_1_FAST_PWM_ICR1_TOP						13
#define TMR_U8_TMR_1_FAST_PWM_OCR1A_TOP						14

/* TMR1 Compare Match Output Modes - Channel A */
#define TMR_U8_TMR_1_DISCONNECT_OC1A_PIN					0
#define TMR_U8_TMR_1_TOG_OC1A_PIN							1
#define TMR_U8_TMR_1_CLR_OC1A_PIN							2
#define TMR_U8_TMR_1_SET_OC1A_PIN							3

/* TMR1 Compare Match Output Modes - Channel B */
#define TMR_U8_TMR_1_DISCONNECT_OC1B_PIN					0
#define TMR_U8_TMR_1_TOG_OC1B_PIN							1
#define TMR_U8_TMR_1_CLR_OC1B_PIN							2
#define TMR_U8_TMR_1_SET_OC1B_PIN							3

/* TMR1 Interrupt Sources */
#define TMR_U8_TMR_1_NO_INTERRUPT							0
#define TMR_U8_TMR_1_CAPT_INTERRUPT							1
#define TMR_U8_TMR_1_COMP_A_INTERRUPT						2
#define TMR_U8_TMR_1_COMP_B_INTERRUPT						3
#define TMR_U8_TMR_1_OVF_INTERRUPT 							4

/* TMR1 Clock Sources */
#define TMR_U8_TMR_1_NO_CLOCK_SOURCE						0
#define TMR_U8_TMR_1_NO_PRESCALER							1
#define TMR_U8_TMR_1_8_PRESCALER							2
#define TMR_U8_TMR_1_64_PRESCALER							3
#define TMR_U8_TMR_1_256_PRESCALER							4
#define TMR_U8_TMR_1_1024_PRESCALER							5
#define TMR_U8_TMR_1_EXTERNAL_CLOCK_SOURCE_FALL_EDGE		6
#define TMR_U8_TMR_1_EXTERNAL_CLOCK_SOURCE_RISE_EDGE		7

/* End of Timer/Counter1 Configurations' Definitions */

/*****************************************************/

/*
 * 8-bit Timer/Counter2 Configurations' Definitions
 */

/* TMR2 Waveform Generation Modes */
#define TMR_U8_TMR_2_NORMAL_MODE							0
#define TMR_U8_TMR_2_PWM_PHASE_CORRECT_MODE					1
#define TMR_U8_TMR_2_CTC_MODE								2
#define TMR_U8_TMR_2_FAST_PWM_MODE							3

/* TMR2 Compare Match Output Modes */
#define TMR_U8_TMR_2_DISCONNECT_OC2_PIN						0
#define TMR_U8_TMR_2_TOG_OC2_PIN							1
#define TMR_U8_TMR_2_CLR_OC2_PIN							2
#define TMR_U8_TMR_2_SET_OC2_PIN							3

/* TMR2 Interrupt Sources */
#define TMR_U8_TMR_2_NO_INTERRUPT							0
#define TMR_U8_TMR_2_COMP_INTERRUPT							1
#define TMR_U8_TMR_2_OVF_INTERRUPT 							2

/* TMR2 Clock Sources */
#define TMR_U8_TMR_2_NO_CLOCK_SOURCE						0
#define TMR_U8_TMR_2_NO_PRESCALER							1
#define TMR_U8_TMR_2_8_PRESCALER							2
#define TMR_U8_TMR_2_32_PRESCALER							3
#define TMR_U8_TMR_2_64_PRESCALER							4
#define TMR_U8_TMR_2_128_PRESCALER							5
#define TMR_U8_TMR_2_256_PRESCALER							6
#define TMR_U8_TMR_2_1024_PRESCALER							7

/* End of Timer/Counter2 Configurations' Definitions */

/*******************************************************************************************************************************************************************/
/* TMR Configurations */

/*
 * 8-bit Timer/Counter0 Configurations
 */

/* TMR0 Waveform Generation Mode Select */
/* Options: TMR_U8_TMR_0_NORMAL_MODE
 *          TMR_U8_TMR_0_PWM_PHASE_CORRECT_MODE
 *          TMR_U8_TMR_0_CTC_MODE
 *          TMR_U8_TMR_0_FAST_PWM_MODE
 */
#define TMR_U8_TMR_0_MODE_SELECT			TMR_U8_TMR_0_PWM_PHASE_CORRECT_MODE

/* TMR0 Compare Match Output Mode Select */
/* Options: TMR_U8_TMR_0_DISCONNECT_OC0_PIN                     // Any Mode
 *          TMR_U8_TMR_0_TOG_OC0_PIN                            // Non-PWM Modes only
 *          TMR_U8_TMR_0_CLR_OC0_PIN                            // Any Mode ( PWM -> Non-Inverting Mode )
 *          TMR_U8_TMR_0_SET_OC0_PIN                            // Any Mode ( PWM -> Inverting Mode )
 */
#define TMR_U8_TMR_0_COMP_OUTPUT_MODE		TMR_U8_TMR_0_DISCONNECT_OC0_PIN

/* TMR0 Interrupt Select */
/* Options: TMR_U8_TMR_0_NO_INTERRUPT
 * 			TMR_U8_TMR_0_COMP_INTERRUPT
 * 			TMR_U8_TMR_0_OVF_INTERRUPT
 */
#define TMR_U8_TMR_0_INTERRUPT_SELECT		TMR_U8_TMR_0_NO_INTERRUPT

/* TMR0 Clock Select */
/* Options: TMR_U8_TMR_0_NO_CLOCK_SOURCE						// No clock source ( Timer/Counter0 stopped )
 * 			TMR_U8_TMR_0_NO_PRESCALER							// CLK IO/1   ( No prescaling )
 * 			TMR_U8_TMR_0_8_PRESCALER							// CLK IO/8   ( From prescaler )
 * 			TMR_U8_TMR_0_64_PRESCALER							// CLK IO/64  ( From prescaler )
 * 			TMR_U8_TMR_0_256_PRESCALER							// CLK IO/256 ( From prescaler )
 * 			TMR_U8_TMR_0_1024_PRESCALER							// CLK IO/1024( From prescaler )
 * 			TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_FALL_EDGE		// External clock source on T0 pin. Clock on falling edge.
 * 			TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_RISE_EDGE		// External clock source on T0 pin. Clock on rising edge.
 */
#define TMR_U8_TMR_0_CLOCK_SELECT			TMR_U8_TMR_0_64_PRESCALER

/* TMR0 Other Configurations */
#define TMR_U8_TMR_0_PRELOAD_VALUE			0
#define TMR_U8_TMR_0_COMPARE_VALUE			0
#define TMR_U16_TMR_0_NUM_OF_OVERFLOWS		1

/* End of Timer/Counter0 Configurations */

/*****************************************************/

/*
 * 16-bit Timer/Counter1 Configurations
 */

/* TMR1 Waveform Generation Mode Select */
/* Options: TMR_U8_TMR_1_NORMAL_MODE							// Overflow Value ( TOP ) = 0xFFFF
 *			TMR_U8_TMR_1_PWM_PHASE_CORRECT_8_BIT_MODE			// Overflow Value ( TOP ) = 0x00FF
 *			TMR_U8_TMR_1_PWM_PHASE_CORRECT_9_BIT_MODE			// Overflow Value ( TOP ) = 0x01FF
 *			TMR_U8_TMR_1_PWM_PHASE_CORRECT_10_BIT_MODE			// Overflow Value ( TOP ) = 0x03FF
 *			TMR_U8_TMR_1_CTC_OCR1A_TOP							// Overflow Value ( TOP ) = OCR1A
 *			TMR_U8_TMR_1_FAST_PWM_8_BIT_MODE					// Overflow Value ( TOP ) = 0x00FF
 *			TMR_U8_TMR_1_FAST_PWM_9_BIT_MODE					// Overflow Value ( TOP ) = 0x01FF
 *			TMR_U8_TMR_1_FAST_PWM_10_BIT_MODE					// Overflow Value ( TOP ) = 0x03FF
 *			TMR_U8_TMR_1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_TOP	// Overflow Value ( TOP ) = ICR1
 *			TMR_U8_TMR_1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_TOP	// Overflow Value ( TOP ) = OCR1A
 *			TMR_U8_TMR_1_PWM_PHASE_CORRECT_ICR1_TOP				// Overflow Value ( TOP ) = ICR1
 *			TMR_U8_TMR_1_PWM_PHASE_CORRECT_OCR1A_TOP			// Overflow Value ( TOP ) = OCR1A
 *			TMR_U8_TMR_1_CTC_ICR1_TOP							// Overflow Value ( TOP ) = ICR1
 *			TMR_U8_TMR_1_FAST_PWM_ICR1_TOP						// Overflow Value ( TOP ) = ICR1
 *			TMR_U8_TMR_1_FAST_PWM_OCR1A_TOP						// Overflow Value ( TOP ) = OCR1A
 */
#define TMR_U8_TMR_1_MODE_SELECT			TMR_U8_TMR_1_NORMAL_MODE

/* TMR1 Compare Match Output Mode Select - Channel A */
/* Options: TMR_U8_TMR_1_DISCONNECT_OC1A_PIN                	// Any Mode
 *          TMR_U8_TMR_1_TOG_OC1A_PIN                        	// Selected Modes only
 *          TMR_U8_TMR_1_CLR_OC1A_PIN                        	// Any Mode ( PWM -> Non-Inverting Mode )
 *          TMR_U8_TMR_1_SET_OC1A_PIN                        	// Any Mode ( PWM -> Inverting Mode )
 */
#define TMR_U8_TMR_1_COMP_OUTPUT_MODE_A		TMR_U8_TMR_1_DISCONNECT_OC1A_PIN

/* TMR1 Compare Match Output Mode Select - Channel B */
/* Options: TMR_U8_TMR_1_DISCONNECT_OC1B_PIN 					// Any Mode
 * 			TMR_U8_TMR_1_TOG_OC1B_PIN                   		// Non-PWM Modes only
 *          TMR_U8_TMR_1_CLR_OC1B_PIN                           // Any Mode ( PWM -> Non-Inverting Mode )
 *          TMR_U8_TMR_1_SET_OC1B_PIN                           // Any Mode ( PWM -> Inverting Mode )
 */
#define TMR_U8_TMR_1_COMP_OUTPUT_MODE_B		TMR_U8_TMR_1_DISCONNECT_OC1A_PIN

/* TMR1 Interrupt Select */
/* Options: TMR_U8_TMR_1_NO_INTERRUPT
 * 			TMR_U8_TMR_1_CAPT_INTERRUPT
 * 			TMR_U8_TMR_1_COMP_A_INTERRUPT
 * 			TMR_U8_TMR_1_COMP_B_INTERRUPT
 * 			TMR_U8_TMR_1_OVF_INTERRUPT
 */
#define TMR_U8_TMR_1_INTERRUPT_SELECT		TMR_U8_TMR_1_NO_INTERRUPT

/* TMR1 Clock Select */
/* Options: TMR_U8_TMR_1_NO_CLOCK_SOURCE						// No clock source ( Timer/Counter1 stopped )
 * 			TMR_U8_TMR_1_NO_PRESCALER							// CLK IO/1   ( No prescaling )
 * 			TMR_U8_TMR_1_8_PRESCALER							// CLK IO/8   ( From prescaler )
 * 			TMR_U8_TMR_1_64_PRESCALER							// CLK IO/64  ( From prescaler )
 * 			TMR_U8_TMR_1_256_PRESCALER							// CLK IO/256 ( From prescaler )
 * 			TMR_U8_TMR_1_1024_PRESCALER							// CLK IO/1024( From prescaler )
 * 			TMR_U8_TMR_1_EXTERNAL_CLOCK_SOURCE_FALL_EDGE		// External clock source on T1 pin. Clock on falling edge.
 * 			TMR_U8_TMR_1_EXTERNAL_CLOCK_SOURCE_RISE_EDGE		// External clock source on T1 pin. Clock on rising edge.
 */
#define TMR_U8_TMR_1_CLOCK_SELECT			TMR_U8_TMR_1_NO_CLOCK_SOURCE

/* TMR1 Other Configurations */
#define TMR_U16_TMR_1_PRELOAD_VALUE			0
#define TMR_U16_TMR_1_COMPARE_VALUE_A		0
#define TMR_U16_TMR_1_COMPARE_VALUE_B		0
#define TMR_U16_TMR_1_INPUT_CAPTURE_VALUE	0
#define TMR_U16_TMR_1_NUM_OF_OVERFLOWS		1

/* End of Timer/Counter1 Configurations */

/*****************************************************/

/*
 * 8-bit Timer/Counter2 Configurations
 */

/* TMR2 Waveform Generation Mode Select */
/* Options: TMR_U8_TMR_2_NORMAL_MODE
 *          TMR_U8_TMR_2_PWM_PHASE_CORRECT_MODE
 *          TMR_U8_TMR_2_CTC_MODE
 *          TMR_U8_TMR_2_FAST_PWM_MODE
 */
#define TMR_U8_TMR_2_MODE_SELECT			TMR_U8_TMR_2_NORMAL_MODE

/* TMR2 Compare Match Output Mode Select */
/* Options: TMR_U8_TMR_2_DISCONNECT_OC2_PIN						// Any Mode
 *          TMR_U8_TMR_2_TOG_OC2_PIN							// Non-PWM Modes only
 *          TMR_U8_TMR_2_CLR_OC2_PIN							// Any Mode ( PWM -> Non-Inverting Mode )
 *          TMR_U8_TMR_2_SET_OC2_PIN							// Any Mode ( PWM -> Inverting Mode )
 */
#define TMR_U8_TMR_2_COMP_OUTPUT_MODE		TMR_U8_TMR_2_DISCONNECT_OC2_PIN

/* TMR2 Interrupt Select */
/* Options: TMR_U8_TMR_2_NO_INTERRUPT
 * 			TMR_U8_TMR_2_COMP_INTERRUPT
 * 			TMR_U8_TMR_2_OVF_INTERRUPT
 */
#define TMR_U8_TMR_2_INTERRUPT_SELECT		TMR_U8_TMR_2_NO_INTERRUPT

/* TMR2 Clock Select */
/* Options: TMR_U8_TMR_2_NO_CLOCK_SOURCE						// No clock source ( Timer/Counter2 stopped )
 * 			TMR_U8_TMR_2_NO_PRESCALER							// CLK T2S/1   ( No prescaling )
 * 			TMR_U8_TMR_2_8_PRESCALER							// CLK T2S/8   ( From prescaler )
 * 			TMR_U8_TMR_2_32_PRESCALER							// CLK T2S/32  ( From prescaler )
 * 			TMR_U8_TMR_2_64_PRESCALER							// CLK T2S/64  ( From prescaler )
 * 			TMR_U8_TMR_2_128_PRESCALER							// CLK T2S/128 ( From prescaler )
 * 			TMR_U8_TMR_2_256_PRESCALER							// CLK T2S/256 ( From prescaler )
 * 			TMR_U8_TMR_2_1024_PRESCALER							// CLK T2S/1024( From prescaler )
 */
#define TMR_U8_TMR_2_CLOCK_SELECT			TMR_U8_TMR_2_NO_CLOCK_SOURCE

/* TMR2 Other Configurations */
#define TMR_U8_TMR_2_PRELOAD_VALUE			0
#define TMR_U8_TMR_2_COMPARE_VALUE			0
#define TMR_U16_TMR_2_NUM_OF_OVERFLOWS		1

/* End of Timer/Counter2 Configurations */

/*****************************************************/

/*
 * TMR Other Configurations 
 */

/* Timers Flags */
#define TMR_U8_FLAG_DOWN					0
#define TMR_U8_FLAG_UP						1

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* TMR_CONFIG_H_ */