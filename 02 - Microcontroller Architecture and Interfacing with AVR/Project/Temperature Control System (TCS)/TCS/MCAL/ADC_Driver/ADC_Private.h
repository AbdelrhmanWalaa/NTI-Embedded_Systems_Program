/*
 * ADC_Private.h
 *
 *     Created on: Apr 28, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Successive Approximation Analog to Digital Converter (SAADC) registers' locations.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* ADC Registers' Locations */

#define ADC_U8_ADMUX_REG	    *( ( volatile u8 * ) 0x27 )
#define ADC_U8_ADCSRA_REG	    *( ( volatile u8 * ) 0x26 )
#define ADC_U8_ADCH_REG		    *( ( volatile u8 * ) 0x25 )
#define ADC_U8_ADCL_REG		    *( ( volatile u8 * ) 0x24 )
/* DataType is u16 * in order to get both registers ( i.e. ADCH and ADCL ) locations in memory */
#define ADC_U16_ADC_REG		    *( ( volatile u16 * ) 0x24 )

#define ADC_U8_SFIOR_REG	    *( ( volatile u8 * ) 0x50 )

/*******************************************************************************************************************************************************************/
/* ADC Registers' Description */

/* ADC Multiplexer Selection Register - ADMUX */
/* Bit 7, 6 - REFS1, REFS0: Voltage Reference Selection Bits */
#define ADC_U8_REFS1_BIT	    7
#define ADC_U8_REFS0_BIT	    6
/* Bit 5 - ADLAR: ADC Left Adjust Result */
#define ADC_U8_ADLAR_BIT	    5
/* End of ADMUX Register */

/* ADC Control and Status Register A - ADCSRA */
/* Bit 7 - ADEN: ADC Enable */
#define ADC_U8_ADEN_BIT		    7
/* Bit 6 - ADSC: ADC Start Conversion */
#define ADC_U8_ADSC_BIT		    6
/* Bit 5 - ADATE: ADC Auto Trigger Enable */
#define ADC_U8_ADATE_BIT	    5
/* Bit 4 - ADIF: ADC Interrupt Flag */
#define ADC_U8_ADIF_BIT		    4
/* Bit 3 - ADIE: ADC Interrupt Enable */
#define ADC_U8_ADIE_BIT		    3
/* Bits 2:0 - ADPS2:0: ADC Prescaler Select Bits */
#define ADC_U8_ADPS2_BIT	    2
#define ADC_U8_ADPS1_BIT	    1
#define ADC_U8_ADPS0_BIT	    0
/* End of ADCSRA Register */

/* Special FunctionIO Register - SFIOR */
/* Bit 7:5 - ADTS2:0: ADC Auto Trigger Source */
#define ADC_U8_ADTS2_BIT	    7
#define ADC_U8_ADTS1_BIT	    6
#define ADC_U8_ADTS0_BIT	    5
/* End of SFIOR Register */

/*******************************************************************************************************************************************************************/

#endif /* ADC_PRIVATE_H_ */