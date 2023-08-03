/*
 * main.c
 *
 *   Created on: Jan 10, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This Application uses ATmega32 to send data using TWI from a microcontroller (Master), and receive the data on an EEPROM (Slave), and display it on an LCD.
 */

/* APP */
#include "APP/APP_Interface.h"

int main(void)
{
	APP_vdInitialization();
	APP_vdStartProgram();    
}