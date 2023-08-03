/*
 * LCD_Config.h
 *
 *   Created on: Apr 20, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Liquid Crystal Display (LCD) pre-build configurations, through which user can configure before using the LCD peripheral.
 *    Datasheet: https://datasheetspdf.com/pdf/746281/Topway/LMB161ABC-1/1
 *    Model No.: LMB161A - LCD
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* ATmega32(L) interfacing with LCD: */
/*
									  -----------                   ----------
									 | ATmega32  |                 |   LCD    |
									 |           |                 |          |
									 |        PB0|---------------->|RS        |
									 |        PB1|---------------->|RW        |
									 |        PB2|---------------->|E         |
									 |           |                 |          |
									 |        PA4|---------------->|D4        |
									 |        PA5|---------------->|D5        |
									 |        PA6|---------------->|D6        |
									 |        PA7|---------------->|D7        |
									  -----------                   ----------
 */

/*******************************************************************************************************************************************************************/
/* LCD Configurations' Definitions */

/* LCD Modes */
#define LCD_U8_4_BIT_MODE				0
#define LCD_U8_8_BIT_MODE				1

/* LCD Pins Locations ( In case 4-Bit Mode is selected ) */
#define LCD_U8_LOWER_PORT_PINS			0
#define LCD_U8_UPPER_PORT_PINS			1

/* End of Configurations' Definitions */

/*******************************************************************************************************************************************************************/
/* LCD Configurations */

/* LCD Mode Select */
/* Options: LCD_U8_4_BIT_MODE
			LCD_U8_8_BIT_MODE
 */
#define LCD_U8_MODE_SELECT				LCD_U8_4_BIT_MODE

/* LCD Port(s) */
/* Options: DIO_U8_PORTA
			DIO_U8_PORTB
			DIO_U8_PORTC
			DIO_U8_PORTD
 */
#define LCD_U8_CTRL_PORT 				DIO_U8_PORTB
#define LCD_U8_DATA_PORT 				DIO_U8_PORTA

/* LCD Ctrl Pins connected to Ctrl Port */
/* Options: DIO_U8_PIN0
			DIO_U8_PIN1
			DIO_U8_PIN2
			DIO_U8_PIN3
			DIO_U8_PIN4
			DIO_U8_PIN5
			DIO_U8_PIN6
			DIO_U8_PIN7
 */
#define LCD_U8_RS_PIN	 				DIO_U8_PIN0
#define LCD_U8_RW_PIN	 				DIO_U8_PIN1
#define LCD_U8_EN_PIN	 				DIO_U8_PIN2

/* LCD Data Pins' Location ( In case 4-Bit Mode is selected ) */
/* Options: LCD_U8_LOWER_PORT_PINS
			LCD_U8_UPPER_PORT_PINS
 */
#define LCD_U8_DATA_PINS_LOCATION		LCD_U8_UPPER_PORT_PINS

/* LCD 4 Bit Mode Configured bits: ( 0 0 1 DL N F X X ) */
/* Options: 1- BIT4 DL: 0-> 4 bit    , 1-> 8 bit
 * 			2- BIT3 N : 0-> 1 Line   , 1-> 2 Lines
 * 			3- BIT2 F : 0-> 5*7 dots , 1-> 5*10 dots
 */
#define LCD_U8_FUNC_SET_4_BIT			0b00101000

/* LCD 8 Bit Mode Configured bits: ( 0 0 1 DL N F X X ) */
/* Options: 1- BIT4 DL: 0-> 4 bit    , 1-> 8 bit
 * 			2- BIT3 N : 0-> 1 Line   , 1-> 2 Lines
 * 			3- BIT2 F : 0-> 5*7 dots , 1-> 5*10 dots
 */
#define LCD_U8_FUNC_SET_8_BIT			0b00111000

/* Configured bits: ( 0 0 0 0 1 D C B ) */
/* Options: 1- BIT2 D : 0-> Display OFF 	 , 1-> Display ON
 * 			2- BIT1 C : 0-> Cursor OFF  	 , 1-> Cursor ON
 * 			3- BIT0 B : 0-> Cursor Blink OFF , 1-> Cursor Blink ON
 */
#define LCD_U8_DISP_ON_OFF_CTRL 		0b00001100

/* Configured bits: ( 0 0 0 0 0 1 I/D SH ) */
/* Options: 1- BIT1 I/D : 0-> Decrement , 1-> Increment
 * 			2- BIT0 SH  : 0-> Shift OFF , 1-> Shift ON
 */
#define LCD_U8_ENTRY_MODE				0b00000110

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* LCD_CONFIG_H_ */