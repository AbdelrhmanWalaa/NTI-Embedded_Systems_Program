/*
 * main.c
 *
 *   Created on: Mar 1, 2023
 *       Author: Abdelrhman Walaa Hussein
 *  Description: Smart Home System is an application that Controls Home Temperature in real-time,
 *               and displays it on the LCD. The system also Controls Home Lighting System.
 *               This application allows the user to Access Doors using password, if the password is
 *               wrong, after a certain number of trials it will Fire a Door Alarm, and Send a Notification
 *               on mobile.
 */

/* Application */
#include "Application/Application.h"

int main(void)
{
	APP_SystemStart();

	return 0;
}
