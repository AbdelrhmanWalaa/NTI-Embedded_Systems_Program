/*
 * SPI.h
 *
 * Created: 7/15/2021 10:43:20 AM
 *  Author: MahmoudH
 */ 


#ifndef SPI_H_
#define SPI_H_

#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "bit_handle.h"
#include "data_types.h"

#define SPI_PORT			PORTB
#define SPI_DDR				DDRB

#define SPI_SCK				PB7
#define SPI_MISO			PB6
#define SPI_MOSI			PB5
#define SPI_SS				PB4

#define SPI_DUMMY			0x00

typedef enum{
	SPI_SLAVE, SPI_MASTER
}SPI_Mode;

void	SPI_Init(SPI_Mode mode);
u8		SPI_Transceve(u8 data);

#endif /* SPI_H_ */