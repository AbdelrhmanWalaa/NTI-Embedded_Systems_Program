/*
 * TMR_Private.h
 *
 *     Created on: Jul 27, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Timers (TMR) registers' locations and description.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef TMR_PRIVATE_H_
#define TMR_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* TMR Registers' Locations */

#define	TMR_U8_TIMSK_REG		* ( ( volatile  u8 * ) 0x59 )
#define	TMR_U8_TIFR_REG			* ( ( volatile  u8 * ) 0x58 )
#define	TMR_U8_SFIOR_REG		* ( ( volatile  u8 * ) 0x50 )

/*
 * 8-bit Timer/Counter0
 */

#define	TMR_U8_TCCR0_REG		* ( ( volatile  u8 * ) 0x53 )
#define	TMR_U8_TCNT0_REG		* ( ( volatile  u8 * ) 0x52 )
#define	TMR_U8_OCR0_REG			* ( ( volatile  u8 * ) 0x5C )

/*
 * 16-bit Timer/Counter1
 */

#define	TMR_U8_TCCR1A_REG		*( ( volatile  u8 * ) 0x4F )
#define	TMR_U8_TCCR1B_REG		*( ( volatile  u8 * ) 0x4E )
#define	TMR_U8_TCNT1H_REG		*( ( volatile  u8 * ) 0x4D )
#define	TMR_U8_TCNT1L_REG		*( ( volatile  u8 * ) 0x4C )
/* DataType is u16 * in order to get both registers ( i.e. TCNT1L and TCNT1H respectively ) locations in memory */
#define TMR_U16_TCNT1_REG		*( ( volatile  u16 * ) 0x4C )
#define	TMR_U8_OCR1AH_REG		*( ( volatile  u8 * ) 0x4B )
#define	TMR_U8_OCR1AL_REG		*( ( volatile  u8 * ) 0x4A )
/* DataType is u16 * in order to get both registers ( i.e. OCR1AL and OCR1AH respectively ) locations in memory */
#define TMR_U16_OCR1A_REG		*( ( volatile  u16 * ) 0x4A )
#define	TMR_U8_OCR1BH_REG		*( ( volatile  u8 * ) 0x49 )
#define	TMR_U8_OCR1BL_REG		*( ( volatile  u8 * ) 0x48 )
/* DataType is u16 * in order to get both registers ( i.e. OCR1BL and OCR1BH respectively ) locations in memory */
#define TMR_U16_OCR1B_REG		*( ( volatile  u16 * ) 0x48 )
#define	TMR_U8_ICR1H_REG		*( ( volatile  u8 * ) 0x47 )
#define	TMR_U8_ICR1L_REG		*( ( volatile  u8 * ) 0x46 )
/* DataType is u16 * in order to get both registers ( i.e. ICR1L and ICR1H respectively ) locations in memory */
#define TMR_U16_ICR1_REG		*( ( volatile  u16 * ) 0x46 )

/*
 * 8-bit Timer/Counter2
 */

#define	TMR_U8_TCCR2_REG		*( ( volatile  u8 * ) 0x45 )
#define	TMR_U8_TCNT2_REG		*( ( volatile  u8 * ) 0x44 )
#define	TMR_U8_OCR2_REG			*( ( volatile  u8 * ) 0x43 )
#define	TMR_U8_ASSR_REG			*( ( volatile  u8 * ) 0x42 )

/*******************************************************************************************************************************************************************/
/* TMR Registers' Description */

/* Timer/Counter Interrupt Mask Register - TIMSK */
/* Bit 7 - OCIE2: Timer/Counter2 Output Compare Match Interrupt Enable */
#define TMR_U8_OCIE2_BIT		7
/* Bit 6 - TOIE2: Timer/Counter2 Overflow Interrupt Enable */
#define TMR_U8_TOIE2_BIT		6
/* Bit 5 - TICIE1: Timer/Counter1, Input Capture Interrupt Enable */
#define TMR_U8_TICIE1_BIT		5
/* Bit 4 - OCIE1A: Timer/Counter1, Output Compare A Match Interrupt Enable */
#define TMR_U8_OCIE1A_BIT		4
/* Bit 3 - OCIE1B: Timer/Counter1, Output Compare B Match Interrupt Enable */
#define TMR_U8_OCIE1B_BIT		3
/* Bit 2 - TOIE1: Timer/Counter1, Overflow Interrupt Enable */
#define TMR_U8_TOIE1_BIT		2
/* Bit 1 - OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable */
#define TMR_U8_OCIE0_BIT		1
/* Bit 0 - TOIE0: Timer/Counter0 Overflow Interrupt Enable */
#define TMR_U8_TOIE0_BIT		0
/* End of TIMSK Register */

/* Timer/Counter Interrupt Flag Register - TIFR */
/* Bit 7 - OCF2: Output Compare Flag 2 */
#define TMR_U8_OCF2_BIT			7
/* Bit 6 - TOV2: Timer/Counter2 Overflow Flag */
#define TMR_U8_TOV2_BIT			6
/* Bit 5 - ICF1: Timer/Counter1, Input Capture Flag */
#define TMR_U8_ICF1_BIT			5
/* Bit 4 - OCF1A: Timer/Counter1, Output Compare A Match Flag */
#define TMR_U8_OCF1A_BIT		4
/* Bit 3 - OCF1B: Timer/Counter1, Output Compare B Match Flag */
#define TMR_U8_OCF1B_BIT		3
/* Bit 2 - TOV1: Timer/Counter1, Overflow Flag */
#define TMR_U8_TOV1_BIT			2
/* Bit 1 - OCF0: Output Compare Flag 0 */
#define TMR_U8_OCF0_BIT			1
/* Bit 0 - TOV0: Timer/Counter0 Overflow Flag */
#define TMR_U8_TOV0_BIT			0
/* End of TIFR Register */

/* Special Function IO Register - SFIOR */
/* Bit 1 - PSR2: Prescaler Reset Timer/Counter2 */
#define TMR_U8_PSR2_BIT			1
/* Bit 0 - PSR10: Prescaler Reset Timer/Counter1 and Timer/Counter0 */
#define TMR_U8_PSR10_BIT		0
/* End of SFIOR Register */

/*
 *  8-bit Timer/Counter0 Registers' Description
 */

/* Timer/Counter Control Register - TCCR0 */
/* Bit 7 - FOC0: Force Output Compare */
#define TMR_U8_FOC0_BIT			7
/* Bit 6, 3 - WGM01:0: Waveform Generation Mode */
#define TMR_U8_WGM01_BIT		3
#define TMR_U8_WGM00_BIT		6
/* Bit 5:4 - COM01:0: Compare Match Output Mode */
#define TMR_U8_COM01_BIT		5
#define TMR_U8_COM00_BIT		4
/* Bit 2:0 - CS02:0: Clock Select */
#define TMR_U8_CS02_BIT			2
#define TMR_U8_CS01_BIT			1
#define TMR_U8_CS00_BIT			0
/* End of TCCR0 Register */

/*
 * 16-bit Timer/Counter1 Registers' Description
 */

/* Timer/Counter1 Control Register A - TCCR1A */
/* Bit 7:6 - COM1A1:0: Compare Output Mode for Channel A */
#define TMR_U8_COM1A1_BIT		7
#define TMR_U8_COM1A0_BIT		6
/* Bit 5:4 - COM1B1:0: Compare Output Mode for Channel B */
#define TMR_U8_COM1B1_BIT		5
#define TMR_U8_COM1B0_BIT		4
/* Bit 3 - FOC1A: Force Output Compare for Channel A */
#define TMR_U8_FOC1A_BIT		3
/* Bit 2 - FOC1B: Force Output Compare for Channel B */
#define TMR_U8_FOC1B_BIT		2
/* Bit 1:0 - WGM11:0: Waveform Generation Mode */
#define TMR_U8_WGM11_BIT		1
#define TMR_U8_WGM10_BIT		0
/* End of TCCR1A Register */

/* Timer/Counter1 Control Register B - TCCR1B */
/* Bit 7 - ICNC1: Input Capture Noise Canceler */
#define TMR_U8_ICNC1_BIT		7
/* Bit 6 - ICES1: Input Capture Edge Select */
#define TMR_U8_ICES1_BIT		6
/* Bit 4:3 - WGM13:2: Waveform Generation Mode */
#define TMR_U8_WGM13_BIT		4
#define TMR_U8_WGM12_BIT		3
/* Bit 2:0 - CS12:0: Clock Select */
#define TMR_U8_CS12_BIT			2
#define TMR_U8_CS11_BIT			1
#define TMR_U8_CS10_BIT			0
/* End of TCCR1B Register */

/*
 * 8-bit Timer/Counter2 Registers' Description
 */

/* Timer/Counter Control Register - TCCR2 */
/* Bit 7 - FOC2: Force Output Compare */
#define TMR_U8_FOC2_BIT			7
/* Bit 6, 3 - WGM21:0: Waveform Generation Mode */
#define TMR_U8_WGM21_BIT		3
#define TMR_U8_WGM20_BIT		6
/* Bit 5:4 - COM21:0: Compare Match Output Mode */
#define TMR_U8_COM21_BIT		5
#define TMR_U8_COM20_BIT		4
/* Bit 2:0 - CS22:0: Clock Select */
#define TMR_U8_CS22_BIT			2
#define TMR_U8_CS21_BIT			1
#define TMR_U8_CS20_BIT			0
/* End of TCCR2 Register */

/* Asynchronous Status Register - ASSR */
/* Bit 3 - AS2: Asynchronous Timer/Counter2 */
#define TMR_U8_AS2_BIT			3
/* Bit 2 - TCN2UB: Timer/Counter2 Update Busy */
#define TMR_U8_TCN2UB_BIT		2
/* Bit 1 - OCR2UB: Output Compare Register2 Update Busy */
#define TMR_U8_OCR2UB_BIT		1
/* Bit 0 - TCR2UB: Timer/Counter Control Register2 Update Busy */
#define TMR_U8_TCR2UB_BIT		0
/* End of ASSR Register */

/*******************************************************************************************************************************************************************/

#endif /* TMR_PRIVATE_H_ */