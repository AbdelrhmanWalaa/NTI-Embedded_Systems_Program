/*
 * DCM_Interface.h
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Direct Current Motor (DCM) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *    Datasheet: https://datasheetspdf.com/pdf/917207/KYSAN/RF-300CA-11440/1
 *    Model No.: RF-300CA-11440 - DCM
 */

#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* DCM Includes */

/* SRVL */
#include "../../SRVL/STD_TYPES/STD_TYPES.h"
#include "../../SRVL/BIT_MATH/BIT_MATH.h"

/* MCAL */
#include "../../MCAL/DIO_Driver/DIO_Interface.h"
#include "../../MCAL/TMR_Driver/TMR_Interface.h"

/*******************************************************************************************************************************************************************/
/* DCM Macros */

/* DCM Directions of Rotation */
#define DCM_U8_CLOCKWISE_DIRECTION				0
#define DCM_U8_COUNTER_CLOCKWISE_DIRECTION		1

/* DCM Normal Mode: Speed is constant. */
#define DCM_U8_NO_SPEED							0
/* DCM Speed Mode : Speed is variable. Top Speed that can be generated is 1023, using the 16 bit TMR1 register ( Fast PWM 10-Bit Mode ). */
#define DCM_U16_TOP_SPEED						0x03FF

/*******************************************************************************************************************************************************************/
/* DCM Functions' Prototypes */

u8 DCM_u8RotateDCMInOneDirection ( u16 Cpy_u16RotateSpeed );
u8 DCM_u8RotateDCMInTwoDirections( u8 Cpy_u8RotateDirection, u16 Cpy_u16RotateSpeed );

vd DCM_vdChangeDCMDirection      ( void );

u8 DCM_u8SetDutyCycleOfPWM       ( u16 Cpy_u16DutyCycleValue );
u8 DCM_u8GetDutyCycleOfPWM       ( u8 *Cpy_pu8ReturnedDutyCycleValue );

vd DCM_vdStopDCM                 ( void );

/*******************************************************************************************************************************************************************/

#endif /* DCM_INTERFACE_H_ */