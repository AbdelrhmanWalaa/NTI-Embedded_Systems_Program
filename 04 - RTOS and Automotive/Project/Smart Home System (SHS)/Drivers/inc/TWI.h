/*
 * TWI.h
 *
 * Created: 7/25/2021 1:26:58 PM
 *  Author: MahmoudH
 */ 


#ifndef TWI_H_
#define TWI_H_

#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "bit_handle.h"
#include "data_types.h"
/* Control Status Codes */
#define SC_START			0x08
#define SC_RESTART			0x10
/* Master Transmit Codes */
#define SC_MT_SLAW_ACK		0x18
#define SC_MT_SLAW_NOACK	0x20
#define SC_MT_DATA_ACK		0x28
#define SC_MT_DATA_NOACK	0x30
/* Master Receive Codes */
#define SC_MR_SLAR_ACK		0x40
#define SC_MR_SLAR_NOACK	0x48
#define SC_MR_DATA_ACK		0x50
#define SC_MR_DATA_NOACK	0x58

void TWI_Init(u32 scl);
Bool TWI_Start(void);
Bool TWI_Restart(void);
void TWI_Stop(void);

Bool TWI_Write(u8 u8Byte, u8 sCode);
Bool TWI_Read(u8* pu8Byte, u8 sCode);

#endif /* TWI_H_ */