/*
 * EEPROM_Private.h
 *
 *   Created on: Dec 01, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *	Description: This file contains all Electrically Erasable Programmable Read-Only Memory (EEPROM) important locations.
 *	  Datasheet: https://ww1.microchip.com/downloads/en/devicedoc/doc0180.pdf
 *    Model No.: AT24C16A - EEPROM
 */

#ifndef EEPROM_PRIVATE_H_
#define EEPROM_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* EEPROM Important Locations */

/* EEPROM 16K Device Address:
    ------------------------------------
   | 1 | 0 | 1 | 0 | P2 | P1 | P3 | R/W |
    ------------------------------------
*/
#define EEPROM_U8_DEVICE_ADDRESS        0xA0

/*******************************************************************************************************************************************************************/

#endif /* EEPROM_PRIVATE_H_ */