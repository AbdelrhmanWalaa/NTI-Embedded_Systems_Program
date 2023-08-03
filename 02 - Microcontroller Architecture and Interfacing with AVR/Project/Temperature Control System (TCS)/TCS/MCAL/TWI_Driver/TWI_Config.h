/*
 * TWI_Config.h
 *
 *     Created on: Nov 07, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Two Wire Interface (TWI) pre-build configurations, through which user can configure before using the TWI peripheral.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef TWI_CONFIG_H_
#define TWI_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* TWI Configurations' Definitions */

/*
 * Master Mode Configurations' Definitions
 */

/* TWI Bit Rate Prescalers */
#define TWI_U8_BIT_RATE_PRESCALER_1             0
#define TWI_U8_BIT_RATE_PRESCALER_4             1
#define TWI_U8_BIT_RATE_PRESCALER_16            2
#define TWI_U8_BIT_RATE_PRESCALER_64            3

/* TWI Interrupt in Master Mode */
#define TWI_U8_MM_INT_DISABLED                  0
#define TWI_U8_MM_INT_ENABLED                   1

/* End of Master Mode Configurations' Definitions */

/**************************************************/

/*
 * Slave Mode Configurations' Definitions
 */

/* TWI General Call Recognition */
#define TWI_U8_GNRL_CALL_RECOG_DISABLED         0
#define TWI_U8_GNRL_CALL_RECOG_ENABLED          1

/* TWI Interrupt in Slave Mode */
#define TWI_U8_SM_INT_DISABLED                  0
#define TWI_U8_SM_INT_ENABLED                   1

/* End of Slave Mode Configurations' Definitions */

/*******************************************************************************************************************************************************************/
/* TWI Configurations */

/*
 * Master Mode Configurations 
 */

/* TWI Bit Rate Prescaler Select */
/* Options: TWI_U8_BIT_RATE_PRESCALER_1         // Bit Rate Prescaler = 4 ^ TWPS = 4 ^ 0 = 1
 *          TWI_U8_BIT_RATE_PRESCALER_4         // Bit Rate Prescaler = 4 ^ TWPS = 4 ^ 1 = 4
 *          TWI_U8_BIT_RATE_PRESCALER_16        // Bit Rate Prescaler = 4 ^ TWPS = 4 ^ 2 = 16
 *          TWI_U8_BIT_RATE_PRESCALER_64        // Bit Rate Prescaler = 4 ^ TWPS = 4 ^ 3 = 64 
 */
#define TWI_U8_BIT_RATE_PRESCALER_SELECT		TWI_U8_BIT_RATE_PRESCALER_1

/* TWI Interrupt in Master Mode Enable */
/* Options: TWI_U8_MM_INT_DISABLED
 *          TWI_U8_MM_INT_ENABLED
 */
#define TWI_U8_MM_INT_ENABLE		            TWI_U8_MM_INT_DISABLED

/* TWI SCL Frequency is up to 400 KHz Data Transfer Speed */
#define TWI_U32_SCL_FREQUENCY                   100000

/* End of Master Mode Configurations */

/**************************************************/

/*
 * Slave Mode Configurations 
 */

/* TWI Slave Address */
/* Note: Slave addresses can be freely allocated by the designer, but the address 0000 000 is reserved for a general call.
         All addresses of the format 1111 xxx should be reserved for future purposes. */
#define TWI_U8_SLAVE_ADDRESS                    0xA0

/* TWI General Call Recognition Enable */
/* Options: TWI_U8_GNRL_CALL_RECOG_DISABLED 
 *          TWI_U8_GNRL_CALL_RECOG_ENABLED 
 */
#define TWI_U8_GNRL_CALL_RECOG_ENABLE		    TWI_U8_GNRL_CALL_RECOG_DISABLED

/* TWI Interrupt in Slave Mode Enable */
/* Options: TWI_U8_SM_INT_DISABLED
 *          TWI_U8_SM_INT_ENABLED
 */
#define TWI_U8_SM_INT_ENABLE		            TWI_U8_SM_INT_DISABLED

/* End of Slave Mode Configurations */

/**************************************************/

/*
 * TWI Other Configurations 
 */

/* TimeOutCounter Max Value */
#define TWI_U16_TIME_OUT_MAX_VALUE               50000

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* TWI_CONFIG_H_ */