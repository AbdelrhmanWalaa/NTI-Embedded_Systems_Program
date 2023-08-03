/*
* uart.c
*
* Created: 7/14/2021 10:44:50 AM
*  Author: MahmoudH
*/
#include "uart.h"
/* default: 8N1  */
void	Uart_Init(u32 baudRate){
	/* BR = (clock/(16*baud)) - 1*/
	u32 BRValue = (F_CPU/(16UL*baudRate)) - 1;
	
	/* Set baud rate */
	UCSRC &= ~(1<<URSEL);
	UBRRH = (u8)(BRValue>>8);
	UBRRL = (u8)BRValue;
	
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);//|(1<<RXCIE);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
//	sei();
}
void	Uart_SendByte(u8 data){
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}
void	Uart_ReceiveByte(u8* pData){
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	(*pData) =  UDR;
}
Bool	Uart_ReceiveByte_Unblock(u8* pData){
	Bool result = FALSE;
	if(UCSRA & (1<<RXC)){
		(*pData) =  UDR;
		result =  TRUE;
	}
	else{
		result = FALSE;
	}
	return result;
}
Bool	Uart_ReceiveByte_UnblockTimeout(u8* pData)
{
	u32 timeoutCounter = 0;

	/* Wait for data to be received, taking into consideration timeout counter */
	while((!(UCSRA & (1<<RXC))) && (timeoutCounter < UART_MAX_TIMEOUT)){
		timeoutCounter++;
	}
	if(timeoutCounter < UART_MAX_TIMEOUT){
		/* Data is received */
		(*pData) =  UDR;
		return TRUE;
	}
	else{
		/* Data is not received */
		return FALSE;
	}
}
void	Uart_SendStr(u8* str){
	u32 ind = 0;
	while(str[ind] != 0){
		Uart_SendByte(str[ind]);
		ind++;
	}
}

ISR(USART_RXC_vect){
	LCD_DispCharXY(2,5,UDR);
}
