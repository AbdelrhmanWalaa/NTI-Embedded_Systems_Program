/*
 * TSI_Interface.h
 *
 *   Created on: Aug 11, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *	Description: This file contains all Temperature Sensor Interface (TSI) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *	  Datasheet: https://datasheetspdf.com/pdf/49860/NationalSemiconductor/LM35/1
 *    Model No.: LM35 - TSI
 */

#ifndef TSI_INTERFACE_H_
#define TSI_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* TSI Includes */

/* SRVL */
#include "../../SRVL/STD_TYPES/STD_TYPES.h"
#include "../../SRVL/BIT_MATH/BIT_MATH.h"
#include "../../SRVL/MCU_Config/MCU_Config.h"

/* MCAL */
#include "../../MCAL/ADC_Driver/ADC_Interface.h"

/*******************************************************************************************************************************************************************/
/* TSI Functions' Prototypes */

u8 TSI_u8GetTemperature( u16 *Cpy_pu16ReturnedTemperatureValue );

/*******************************************************************************************************************************************************************/

#endif /* TSI_INTERFACE_H_ */