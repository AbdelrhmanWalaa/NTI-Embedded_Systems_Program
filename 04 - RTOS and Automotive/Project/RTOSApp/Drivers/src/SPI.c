/*
* SPI.c
*
* Created: 7/15/2021 10:43:40 AM
*  Author: MahmoudH
*/
#include "SPI.h"
void	SPI_Init(SPI_Mode mode){
	/*
	1- if Master -> set MOSI, SCK, SS outpus and set MSTR
	2- if Slave ->  set MISO outpus and Clear MSTR
	3- Enable SPI
	*/
	switch (mode)
	{
		case SPI_MASTER:
		setBits(SPI_DDR, ((1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)));
		clearBit(SPI_DDR, SPI_MISO);		
		setBit(SPCR, MSTR);
		break;
		case SPI_SLAVE:
		clearBits(SPI_DDR, ((1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)));
		setBit(SPI_DDR, SPI_MISO);
		clearBit(SPCR, MSTR);
		break;
	}
	setBit(SPCR, SPE);
}
u8		SPI_Transceve(u8 data){
	/*
	1- Write DR
	2- Wait shift complete flag
	3- Return DR
	*/
	SPDR = data;
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}