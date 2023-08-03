/*
 * TMR_Interface.h
 *
 *     Created on: Jul 27, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Timers (TMR) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef TMR_INTERFACE_H_
#define TMR_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* TMR Includes */

/* SRVL */
#include "../../SRVL/STD_TYPES/STD_TYPES.h"
#include "../../SRVL/BIT_MATH/BIT_MATH.h"

/*******************************************************************************************************************************************************************/
/* TMR Macros */

/* The 3 Timers counted from 0 to 2 */
#define TMR_U8_TMR0							0
#define TMR_U8_TMR1 						1
#define TMR_U8_TMR2 						2

/* The 3 Timers Channels counted from 0 to 2 */
#define TMR_U8_NO_CHANNEL					0
#define TMR_U8_TMR_1_CHANNEL_A				1
#define TMR_U8_TMR_1_CHANNEL_B				2

/* The 3 Timers Interrupts counted from 0 to 2 */
#define TMR_U8_CAPT_INTERRUPT				0
#define TMR_U8_COMP_INTERRUPT				1
#define TMR_U8_OVF_INTERRUPT				2

/* The 3 Timers Compare Match Output Modes counted from 0 to 2 */
#define TMR_U8_TOG_OCR_PIN					0
#define TMR_U8_CLR_OCR_PIN					1
#define TMR_U8_SET_OCR_PIN					2

/*******************************************************************************************************************************************************************/
/* TMR Functions' prototypes */

vd TMR_vdTMR0Initialization  ( void );
vd TMR_vdTMR1Initialization  ( void );
vd TMR_vdTMR2Initialization  ( void );

u8 TMR_u8EnableTMR		     ( u8 Cpy_u8TimerId );
u8 TMR_u8DisableTMR		     ( u8 Cpy_u8TimerId );

u8 TMR_u8EnableTMRInterrupt  ( u8 Cpy_u8TimerId, u8 Cpy_u8Timer1ChannelId, u8 Cpy_u8InterruptType );
u8 TMR_u8DisableTMRInterrupt ( u8 Cpy_u8TimerId, u8 Cpy_u8Timer1ChannelId, u8 Cpy_u8InterruptType );

u8 TMR_u8EnableCOMPPin	     ( u8 Cpy_u8TimerId, u8 Cpy_u8Timer1ChannelId, u8 Cpy_u8COMPMode );
u8 TMR_u8DisableCOMPPin		 ( u8 Cpy_u8TimerId, u8 Cpy_u8Timer1ChannelId );

u8 TMR_u8GetNumberOfOVF		 ( u8 Cpy_u8TimerId, u16 *Cpy_pu16ReturnedNumberOfOVF );
u8 TMR_u8GetOVFFlagStatus	 ( u8 Cpy_u8TimerId, u8 *Cpy_pu8FlagStatus );
u8 TMR_u8ClearOVFFlag		 ( u8 Cpy_u8TimerId );

u8 TMR_u8OVFSetCallBack	     ( u8 Cpy_u8TimerId, void ( *Cpy_pfOVFInterruptAction ) ( void ) );
u8 TMR_u8COMPSetCallBack	 ( u8 Cpy_u8TimerId, u8 Cpy_u8Timer1ChannelId, void ( *Cpy_pfCOMPInterruptAction ) ( void ) );

u8 TMR_u8GetCounterValue	 ( u8 Cpy_u8TimerId, u16 *Cpy_pu16ReturnedCounterValue );

u8 TMR_u8SetCompareMatchValue( u8 Cpy_u8TimerId, u8 Cpy_u8Timer1ChannelId, u16 Cpy_u16CompareMatchValue );
u8 TMR_u8GetCompareMatchValue( u8 Cpy_u8TimerId, u8 Cpy_u8Timer1ChannelId, u16 *Cpy_pu16ReturnedCompareMatchValue );

vd TMR_vdSetInputCaptureValue( u16 Cpy_u16InputCaptureValue );
u8 TMR_u8GetInputCaptureValue( u16 *Cpy_pu16ReturnedInputCaptureValue );

/*******************************************************************************************************************************************************************/

#endif /* TMR_INTERFACE_H_ */