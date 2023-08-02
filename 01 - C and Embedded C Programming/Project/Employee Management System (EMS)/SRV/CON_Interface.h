/*
 * CON_Interface.h
 *
 *   Created on: Aug 1, 2022
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all CON -Console- functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef CON_INTERFACE_H_
#define CON_INTERFACE_H_

/* STD -> Standard Library Layer */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* LIB -> Library Layer */
#include "../LIB/STD_TYPES.h"
#include "../LIB/ERR_TYPES.h"

#define CON_U8_FALSE 0
#define CON_U8_TRUE  1

#define CON_U8_ASCII_ZERO   48
#define CON_U8_ASCII_NINE   56

// Functions' Prototypes
extern u8 CON_u8SystemOut(u8 *Cpy_pu8String);
extern u8 CON_u8IsDigit  (u8 *Cpy_pu8String);

#endif /* CON_INTERFACE_H_ */