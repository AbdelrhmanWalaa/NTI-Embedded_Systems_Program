/*
 * MCU_Config.h
 *
 *     Created on: Dec 19, 2022
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */ 

#ifndef MCU_CONFIG_H_
#define MCU_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* MCU Configurations' Definitions */

#define MCU_U8_FCPU_1_MHZ		0
#define MCU_U8_FCPU_2_MHZ		1
#define MCU_U8_FCPU_4_MHZ		2
#define MCU_U8_FCPU_8_MHZ		3
#define MCU_U8_FCPU_16_MHZ		4
#define MCU_U8_FCPU_20_MHZ		5

/* End of Configurations' Definitions */

/*******************************************************************************************************************************************************************/
/* MCU Configurations */

/* FCPU Select */
/* Options: MCU_U8_FCPU_1_MHZ
 *			MCU_U8_FCPU_2_MHZ
 *			MCU_U8_FCPU_4_MHZ
 *			MCU_U8_FCPU_8_MHZ
 *			MCU_U8_FCPU_16_MHZ
 *			MCU_U8_FCPU_20_MHZ
*/
#define MCU_U8_FCPU_SELECT		MCU_U8_FCPU_8_MHZ

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#if ( MCU_U8_FCPU_SELECT == MCU_U8_FCPU_1_MHZ )
	#define F_CPU	1000000UL
#elif ( MCU_U8_FCPU_SELECT == MCU_U8_FCPU_2_MHZ )
	#define F_CPU	2000000UL
#elif ( MCU_U8_FCPU_SELECT == MCU_U8_FCPU_4_MHZ )
	#define F_CPU	4000000UL
#elif ( MCU_U8_FCPU_SELECT == MCU_U8_FCPU_8_MHZ )
	#define F_CPU	8000000UL
#elif ( MCU_U8_FCPU_SELECT == MCU_U8_FCPU_16_MHZ )
	#define F_CPU	16000000UL
#elif ( MCU_U8_FCPU_SELECT == MCU_U8_FCPU_20_MHZ )
	#define F_CPU	20000000UL
#endif

#include <util/delay.h>

/*******************************************************************************************************************************************************************/

#endif /* MCU_CONFIG_H_ */