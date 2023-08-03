/*
 * APP_Interface.h
 *
 *   Created on: Jan 10, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* APP Includes */

/* SRVL */
#include "../SRVL/STD_TYPES/STD_TYPES.h"
#include "../SRVL/BIT_MATH/BIT_MATH.h"
#include "../SRVL/MCU_Config/MCU_Config.h"

/* MCAL */
#include "../MCAL/DIO_Driver/DIO_Interface.h"
#include "../MCAL/GLI_Driver/GLI_Interface.h"
#include "../MCAL/EXI_Driver/EXI_Interface.h"
#include "../MCAL/ADC_Driver/ADC_Interface.h"
#include "../MCAL/TMR_Driver/TMR_Interface.h"
#include "../MCAL/UART_Driver/UART_Interface.h"
#include "../MCAL/TWI_Driver/TWI_Interface.h"

/* HAL */
#include "../HAL/LED_Driver/LED_Interface.h"
#include "../HAL/DCM_Driver/DCM_Interface.h"
#include "../HAL/LCD_Driver/LCD_Interface.h"
#include "../HAL/KPD_Driver/KPD_Interface.h"
#include "../HAL/TSI_Driver/TSI_Interface.h"
#include "../HAL/EEPROM_Driver/EEPROM_Interface.h"

/*******************************************************************************************************************************************************************/
/* APP Macros */

/* APP States */
#define  APP_U8_S1_HOME_SCREEN			0
#define  APP_U8_S2_TEMP_SCREEN			1
#define  APP_U8_S3_SET_TEMP_SCREEN		2
#define  APP_U8_S4_GET_TEMP_SCREEN		3

/* APP Home Screens */
#define  APP_U8_HOME_SCREEN_1			0
#define  APP_U8_HOME_SCREEN_2			1
#define  APP_U8_HOME_SCREEN_3			2

/* APP Temperature Modes Flags */
#define  APP_U8_LOW_TEMP_FLAG			0
#define  APP_U8_NORM_TEMP_FLAG			1
#define  APP_U8_HIGH_TEMP_FLAG			2
#define  APP_U8_FIRE_TEMP_FLAG			3

/* APP Flags States */
#define  APP_U8_FLAG_DOWN				0
#define  APP_U8_FLAG_UP					1

/*******************************************************************************************************************************************************************/
/* APP Functions' Prototypes */

vd APP_vdInitialization      ( void );
vd APP_vdStartProgram        ( void );

vd APP_vdSwitchToHomeScreen	 ( void );

vd APP_vdDisplayHomeScreen   ( void );
vd APP_vdDisplayHomeScreen1  ( void );
vd APP_vdDisplayHomeScreen2  ( void );
vd APP_vdDisplayHomeScreen3  ( void );

vd APP_vdDisplayTempScreen   ( void );
vd APP_vdLowTempMode		 ( void );
vd APP_vdNormalTempMode		 ( void );
vd APP_vdHighTempMode		 ( void );
vd APP_vdFireTempMode		 ( void );

vd APP_vdDisplaySetTempScreen( void );
vd APP_vdDisplayGetTempScreen( void );

u8 APP_u8SetTemperatureValue ( u8 *Cpy_pu8ReturnedTempValue );

/*******************************************************************************************************************************************************************/

#endif /* APP_INTERFACE_H_ */