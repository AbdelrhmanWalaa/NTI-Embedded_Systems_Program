/*
 * EEPROM_Config.h
 *
 *   Created on: Dec 01, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Electrically Erasable Programmable Read-Only Memory (EEPROM) pre-build configurations, through which user can configure the EEPROM peripheral before using.
 *    Datasheet: https://ww1.microchip.com/downloads/en/devicedoc/doc0180.pdf
 *    Model No.: AT24C16A - EEPROM
 */

#ifndef EEPROM_CONFIG_H_
#define EEPROM_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* EEPROM Configurations' Definitions */

/* EEPROM Memory Sizes */
#define EEPROM_U8_MEMORY_1K				0
#define EEPROM_U8_MEMORY_2K				1
#define EEPROM_U8_MEMORY_4K				2
#define EEPROM_U8_MEMORY_8K				3
#define EEPROM_U8_MEMORY_16K			4

/* End of Configurations' Definitions */

/*******************************************************************************************************************************************************************/
/* EEPROM Configurations */

/* EEPROM Memory Size Select */
/* Options: EEPROM_U8_MEMORY_1K
 *          EEPROM_U8_MEMORY_2K
 *          EEPROM_U8_MEMORY_4K
 *          EEPROM_U8_MEMORY_8K
 *          EEPROM_U8_MEMORY_16K
 */
#define EEPROM_U8_MEMORY_SIZE_SELECT    EEPROM_U8_MEMORY_1K

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* EEPROM_CONFIG_H_ */