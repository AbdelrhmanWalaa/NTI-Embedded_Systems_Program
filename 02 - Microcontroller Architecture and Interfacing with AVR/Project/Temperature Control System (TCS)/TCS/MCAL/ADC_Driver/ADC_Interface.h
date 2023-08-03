/*
 * ADC_Interface.h
 *
 *     Created on: Apr 28, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Successive Approximation Analog to Digital Converter (SAADC) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* ADC Includes */

/* SRVL */
#include "../../SRVL/STD_TYPES/STD_TYPES.h"
#include "../../SRVL/BIT_MATH/BIT_MATH.h"

/*******************************************************************************************************************************************************************/
/* ADC Macros */

/* ADC Channels */
/* Channels 0:7: Single Ended Input Channels */
#define ADC_U8_CHANNEL_0	    0
#define ADC_U8_CHANNEL_1	    1
#define ADC_U8_CHANNEL_2	    2
#define ADC_U8_CHANNEL_3	    3
#define ADC_U8_CHANNEL_4	    4
#define ADC_U8_CHANNEL_5	    5
#define ADC_U8_CHANNEL_6	    6
#define ADC_U8_CHANNEL_7	    7
/* Channels 8:29: Differential Input Channels */
#define ADC_U8_CHANNEL_8	    8
#define ADC_U8_CHANNEL_9	    9
#define ADC_U8_CHANNEL_10	    10
#define ADC_U8_CHANNEL_11	    11
#define ADC_U8_CHANNEL_12	    12
#define ADC_U8_CHANNEL_13	    13
#define ADC_U8_CHANNEL_14	    14
#define ADC_U8_CHANNEL_15	    15
#define ADC_U8_CHANNEL_16	    16
#define ADC_U8_CHANNEL_17	    17
#define ADC_U8_CHANNEL_18	    18
#define ADC_U8_CHANNEL_19	    19
#define ADC_U8_CHANNEL_20	    20
#define ADC_U8_CHANNEL_21	    21
#define ADC_U8_CHANNEL_22	    22
#define ADC_U8_CHANNEL_23	    23
#define ADC_U8_CHANNEL_24	    24
#define ADC_U8_CHANNEL_25	    25
#define ADC_U8_CHANNEL_26	    26
#define ADC_U8_CHANNEL_27	    27
#define ADC_U8_CHANNEL_28	    28
#define ADC_U8_CHANNEL_29	    29
/* Channels 30, 31: Testing Purpose Channels */
#define ADC_U8_CHANNEL_30	    30
#define ADC_U8_CHANNEL_31	    31

/* ADC Interruption Modes */
#define ADC_U8_POLLING_MODE     0
#define ADC_U8_CC_INT_MODE      1

/*******************************************************************************************************************************************************************/
/* ADC Functions' prototypes */

vd ADC_vdInitialization ( void );

u8 ADC_u8StartConversion( u8 Cpy_u8ChannelId );
u8 ADC_u8GetDigitalValue( u8 Cpy_u8InterruptionMode, u16 *Cpy_pu16ReturnedDigitalValue );

u8 ADC_u8ADCSetCallBack ( void ( *Cpy_pfADCInterruptAction ) ( void ) );

/*******************************************************************************************************************************************************************/

#endif /* ADC_INTERFACE_H_ */