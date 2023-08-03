/*
 * STD_TYPES.h
 *
 *  Created on: Mar 31, 2021
 *      Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char u8;				/* 1 byte , 0 -> 255 */
typedef unsigned short int u16;			/* 2 bytes, 0 -> 65,535 */
typedef unsigned long  int u32;			/* 4 bytes, 0 -> 4,294,967,295 */
typedef unsigned long long int u64;		/* 8 bytes, 0 -> 18,446,744,073,709,551,615 */

typedef signed char s8;					/* 1 byte , -128 -> 127 */
typedef signed short int s16;			/* 2 bytes, -32,768 -> 32,767 */
typedef signed long  int s32;			/* 4 bytes, -2,147,483,648 -> 2,147,483,647 */
typedef signed long long int s64;		/* 8 bytes, -9,223,372,036,854,775,807 -> 9,223,372,036,854,775,807 */

typedef float  f32;						/* 4 bytes, 3.4e-38 -> 3.4e+38 */
typedef double f64;						/* 8 bytes, 1.7e-308 -> 1.7e+308 */

typedef void vd;

#define STD_TYPES_OK	1
#define STD_TYPES_NOK	0

#define NULL	        ( ( void * ) 0 )

#endif /* STD_TYPES_H_ */