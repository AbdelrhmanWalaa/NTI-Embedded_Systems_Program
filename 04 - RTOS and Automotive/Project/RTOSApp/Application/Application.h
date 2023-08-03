/*
 * Application.h
 *
 *   Created on: Apr 6, 2023
 *       Author: Abdelrhman Walaa Hussein - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application tasks and functions prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

/*******************************************************************************************************/
/* Application Includes */

/* Drivers Includes */
#include "BasicIO.h"
#include "LCD.h"
#include "ADC.h"
#include "uart.h"

/* FreeRTOS Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

/*******************************************************************************************************/
/* Application Macros */

/* Door and Fan Configurations */
#define APP_DOOR_PORT				PORTA
#define APP_FAN_PORT				PORTA
#define APP_DOOR_PIN				5
#define APP_FAN_PIN					6

/* LEDs */
#define APP_ROOM_1_LED				LED1
#define APP_ROOM_2_LED				LED2
#define APP_ROOM_3_LED				LED3
#define APP_DOOR_LED				LED4
#define APP_AC_LED					LED7

/* Terminal Macros */
#define APP_U8_ENTER_CHAR			13
#define APP_U8_PASSWORD_CHARS		3

/* Flag States */
#define APP_U8_FLAG_DOWN			0
#define APP_U8_FLAG_UP				1

/* Temperature States */
#define APP_U8_NORMAL_TEMP			1
#define APP_U8_HIGH_TEMP			2
#define APP_U8_VERY_HIGH_TEMP		3
#define APP_U8_EXTREME_HIGH_TEMP	4

/* FreeRTOS Events of Event Group: LCD Display */
#define E_DISP_TEMPERATURE			(1<<0)
#define E_DOOR_ALARM	    		(1<<4)

/*******************************************************************************************************/
/* Application Functions and Tasks Prototypes */

void APP_SystemStart	 ( void );
void APP_SystemInit		 ( void );

void T_SendReceiveFrame  ( void* pvParam );
void T_DisplayOnLCD      ( void* pvParam );
void T_ControlTemperature( void* pvParam );
void T_DoorAlarm         ( void* pvParam );

/*******************************************************************************************************/

#endif /* APPLICATION_H_ */
