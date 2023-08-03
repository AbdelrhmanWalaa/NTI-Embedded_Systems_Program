/*
 * Application.c
 *
 *   Created on: Apr 6, 2023
 *       Author: Abdelrhman Walaa Hussein - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application functions' implementation.
 */

/* Application */
#include "Application.h"

/* OS Object Declarations */
EventGroupHandle_t EG_SystemEventGroupHandle = NULL;
EventBits_t EB_Value = 0;

static u8 Glb_u8Temperature;

/*******************************************************************************************************/
/*
 Name: APP_SystemStart
 Input: void
 Output: void
 Description: Function to Start the System.
*/
void APP_SystemStart	 ( void )
{
	/* Step 1: System Initialization */
	APP_SystemInit();

	/* Step 2: Display Welcome Message for 1 sec. */
	LCD_DispStrXY( 1, 1, ( u8 * ) "System Started" );
	_delay_ms(1000);
	LCD_Clear();

	/* Step 3: Create OS Objects */
	EG_SystemEventGroupHandle = xEventGroupCreate();

	/* Step 4: Create Tasks */
	xTaskCreate(T_SendReceiveFrame, NULL, 200, NULL, 1, NULL);
	xTaskCreate(T_DisplayOnLCD, NULL, 100, NULL, 2, NULL);
	xTaskCreate(T_ControlTemperature, NULL, 100, NULL, 3, NULL);
	xTaskCreate(T_DoorAlarm, NULL, 100, NULL, 4, NULL);

	/* Step 5: Start OS */
	vTaskStartScheduler();

	/* Unreachable Code */
	while(1);
}

/*******************************************************************************************************/
/*
 Name: APP_SystemInit
 Input: void
 Output: void
 Description: Function to initialize the System.
*/
void APP_SystemInit		 ( void )
{
	Leds_AllInit();
	LCD_Init();
	ADC_Init();
	Uart_Init(9600);
}

/*******************************************************************************************************/
/*
 Name: T_SendReceiveFrame
 Priority: 1
 Stack Size: 200
 Description: Task to Receive Frames from the UART.
*/
void T_SendReceiveFrame  ( void* pvParam )
{
	/* Flags to be used */
	u8 Loc_u8PasswordFlag = APP_U8_FLAG_DOWN, Loc_u8TimeoutFlag = APP_U8_FLAG_DOWN;

	/* UART Frame */
	u8 Loc_u8RxData = 0, Loc_u8FrameIndex = 1;
	u8 Loc_Au8Frame[11] = { '\0' };

	/* Password Buffers */
	const u8 Loc_Au8DefaultPassword[10] = { "123" };
	u8 Loc_Au8InputPassword[10] = { '\0' };
	u8 Loc_u8TrialNumber = 0;

	while(1)
	{
		/* Check 1: A Data is Received on the UART ( N.B.: Receiving is Unblocking -> in order to check only the UART ) */
		if ( Uart_ReceiveByte_Unblock( &Loc_u8RxData ) == TRUE )
		{
			/* Check 1.1: First element in Frame is '*' character */
			if( Loc_u8RxData == '*' )
			{
				/* Step 1: Save the '*' character to the first element in the Frame Array */
				Loc_Au8Frame[0] = '*';

				/* Loop: Until User enters '\n' character ( N.B.: Receiving is Blocking -> in order to wait until the User puts the whole Frame ) */
				while( Loc_u8RxData != APP_U8_ENTER_CHAR )
				{
					/* Step 2: Receive Frame byte by byte.  */
					Uart_ReceiveByte(&Loc_u8RxData);
					/* Step 3: Save Data to Frame Array */
					Loc_Au8Frame[Loc_u8FrameIndex] = Loc_u8RxData;
					/* Step 4: Increment Index */
					Loc_u8FrameIndex++;
				}

				/* Check 1.1.1: Required Data in the second element of the Frame */
				switch( Loc_Au8Frame[1] )
				{
					/* Case 1: Turn On or Off rooms' light */
					case 'I':

						Uart_SendStr( ( u8 * ) "\r\n" );
						Uart_SendStr( ( u8 * ) "**** Room Light ****\r\n" );

						/* Check 1.1.1.1: Required Data of the fourth element of the Frame */
						switch( Loc_Au8Frame[3] )
						{
							/* Case 1.1: Room 1 */
							case '1':

								/* Check 1.1.1.1.1: Required Data of the sixth element of the Frame */
								switch( Loc_Au8Frame[5] )
								{
									/* Case 1.1.1: Turn off Room 1 light */
									case '0':

										Uart_SendStr( ( u8 * ) "Room 1: LED Off\r\n" );
										Led_Off( APP_ROOM_1_LED );	// Switch off room 1 led

										break;

									/* Case 1.1.2: Turn on Room 1 light */
									case '1':

										Uart_SendStr( ( u8 * ) "Room 1: LED On\r\n" );
										Led_On( APP_ROOM_1_LED );	// Switch on room 1 led

										break;
								}
								break;

							/* Case 1.2: Room 2 */
							case '2':

								/* Check 1.1.1.1.2: Required Data of the sixth element of the Frame */
								switch( Loc_Au8Frame[5] )
								{
									/* Case 1.2.1: Turn off Room 2 light */
									case '0':

										Uart_SendStr( ( u8 * ) "Room 2: LED Off\r\n" );
										Led_Off( APP_ROOM_2_LED );	// Switch off room 2 led

										break;

									/* Case 1.2.2: Turn on Room 2 light */
									case '1':

										Uart_SendStr( ( u8 * ) "Room 2: LED On\r\n" );
										Led_On( APP_ROOM_2_LED );	// Switch on room 2 led

										break;
								}
								break;

							/* Case 1.3: Room 3 */
							case '3':

								/* Check 1.1.1.1.3: Required Data of the sixth element of the Frame */
								switch( Loc_Au8Frame[5] )
								{
									/* Case 1.3.1: Turn off Room 3 light */
									case '0':

										Uart_SendStr( ( u8 * ) "Room 2: LED Off\r\n" );
										Led_Off( APP_ROOM_3_LED );	// Switch off room 3 led

										break;

									/* Case 1.3.2: Turn on Room 3 light */
									case '1':

										Uart_SendStr( ( u8 * ) "Room 3: LED On\r\n" );
										Led_On( APP_ROOM_3_LED );	// Switch on room 3 led

										break;
								}
								break;
						}
						break;

					/* Case 2: Access door using password */
					case 'A':

						Uart_SendStr( ( u8 * ) "\r\n" );
						Uart_SendStr( ( u8 * ) "**** Door Access ****\r\n" );

						/* Check 1.1.1.1: Required Data of the fourth element of the Frame */
						switch( Loc_Au8Frame[3] )
						{
							/* Case 2.1: Close Door */
							case '0':

								Uart_SendStr( ( u8 * ) "Door Closed\r\n" );
								Led_Off( APP_DOOR_LED );		// Switch off door led

								break;

							/* Case 2.2: Open Door */
							case '1':

								/* Loop: Until User enters the correct password or Number of Trials reach 3 */
								for ( Loc_u8TrialNumber = 0; Loc_u8TrialNumber < 3; Loc_u8TrialNumber++ )
								{
									Uart_SendStr( ( u8 * ) "Enter Password: " );

									/* Loop: Until User enters '\n' character ( N.B.: Receiving is Blocking -> in order to wait until the User puts the whole Frame ) */
									for ( u8 Loc_u8Index = 0; Loc_u8Index < APP_U8_PASSWORD_CHARS;  Loc_u8Index++ )
									{
										/* Step 1: Receive Password byte by byte, and check if timeout is reached */
										if ( Uart_ReceiveByte_UnblockTimeout(&Loc_u8RxData) == FALSE )
										{
											Uart_SendStr( ( u8 * ) "\r\n" );
											Uart_SendStr( ( u8 * ) "Timeout\r\n" );

											/* Break: Password Entrance Trials Loop */
											Loc_u8TimeoutFlag = APP_U8_FLAG_UP;
											break;
										}

										/* Step 2: Save Data to Input Password Array */
										Loc_Au8InputPassword[Loc_u8Index] = Loc_u8RxData;
									}

									/* Check 2: Timeout is reached */
									if ( Loc_u8TimeoutFlag == APP_U8_FLAG_UP )
									{
										/* Break: Password Entrance Trials Loop */
										break;
									}

									/* Loop: Until password is being checked */
									for ( u8 Loc_u8Index = 0; Loc_u8Index < APP_U8_PASSWORD_CHARS;  Loc_u8Index++ )
									{
										/* Check 3: Password Validity */
										if ( Loc_Au8DefaultPassword[Loc_u8Index] != Loc_Au8InputPassword[Loc_u8Index] )
										{
											/* Break: Password Validity Loop */
											Loc_u8PasswordFlag = APP_U8_FLAG_UP;
											break;
										}
									}

									/* Check 4: PasswordFlag is up ( i.e.: Incorrect Password ) */
									if ( Loc_u8PasswordFlag == APP_U8_FLAG_UP )
									{
										//xEventGroupSetBits( EG_LCDDisplayHandle, E_DISP_INCORRECT_PASS_SCRN );
										Uart_SendStr( ( u8 * ) "\r\nIncorrect Password\r\n" );
										Uart_SendStr( ( u8 * ) "Trial: " );
										Uart_SendByte( ( Loc_u8TrialNumber + 1 ) + '0' );
										Uart_SendStr( ( u8 * ) "\r\n" );
									}
									/* Check 5: PasswordFlag is down ( i.e.: Correct Password ) */
									else
									{
										Uart_SendStr( ( u8 * ) "\r\nCorrect Password\r\n" );
										Uart_SendStr( ( u8 * ) "Door Opened\r\n" );

										/* Open door */
										Led_On( APP_DOOR_LED );					 // Switch on door led
										setBit( APP_DOOR_PORT, APP_DOOR_PIN );   // Switch on door motor
										vTaskDelay(500);						 // Delay 0.5 sec.
										clearBit( APP_DOOR_PORT, APP_DOOR_PIN ); // Switch off door motor

										/* Break: Password Entrance Trials Loop */
										break;
									}

									/* Reset Password Flag */
									Loc_u8PasswordFlag = APP_U8_FLAG_DOWN;
									Uart_SendStr( ( u8 * ) "\r\n" );
								}

								/* Check 6: Max Trials are reached */
								if ( Loc_u8TrialNumber == 3 )
								{
									Uart_SendStr( ( u8 * ) "Reached Max Trials!\r\n" );
									Uart_SendStr( ( u8 * ) "Door Closed\r\n" );
									Led_Off( APP_DOOR_LED );		// Switch off door led

									/* Step 3: Turn on Door Alarm */
									xEventGroupSetBits( EG_SystemEventGroupHandle, E_DOOR_ALARM );
								}
								break;
						}
						break;
				}

				Uart_SendStr( ( u8 * ) "\r\n" );
			}
		}

		Loc_u8FrameIndex = 0;

		/* Loop: Until Frame is re-intialized with '\0' */
		while ( Loc_Au8Frame[Loc_u8FrameIndex] != '\0' )
		{
			Loc_Au8Frame[Loc_u8FrameIndex] = '\0';
			Loc_u8FrameIndex++;
		}

		/* Reset index to its initial value */
		Loc_u8FrameIndex = 1,
		/* Reset flags to their initial value */
		Loc_u8PasswordFlag = APP_U8_FLAG_DOWN, Loc_u8TimeoutFlag = APP_U8_FLAG_DOWN;

		vTaskDelay(100);
	}
}

/*******************************************************************************************************/
/*
 Name: T_DisplayOnLCD
 Priority: 2
 Stack Size: 100
 Description: Task to Display on the LCD.
*/
void T_DisplayOnLCD      ( void* pvParam )
{
	while(1)
	{
		EB_Value = xEventGroupWaitBits (
				   /* Event Group */
				   EG_SystemEventGroupHandle,
				   /* The Event ( i.e.: bit ) within the Event Group to wait for */
				   ( E_DISP_TEMPERATURE ),
				   /* Event should be cleared before returning */
				   pdTRUE,
				   /* Don't wait for the all Events ( i.e.: bits ) */
				   pdFALSE,
				   /* Max delay to wait for Event to be set */
				   portMAX_DELAY );

		/* Check 1: "Display Temperature Screen" Event is set */
		if ( EB_Value & ( E_DISP_TEMPERATURE ) )
		{
			LCD_Clear();
			LCD_DispStrXY( 1, 1, ( u8 * ) "Temperature: " );
			LCD_DispIntXY( 1, 14, Glb_u8Temperature );
		}
	}
}

/*******************************************************************************************************/
/*
 Name: T_ControlTemperature
 Priority: 3
 Stack Size: 100
 Description: Task to Control home Temperature through switching On or Off Fan and AC,
 	 	 	  after getting Temperature value from LM35 sensor.
*/
void T_ControlTemperature( void* pvParam )
{
	u16 Loc_u16ADCValue = 0;
	u8 Loc_u8TemperatureStatus = 0;

	while(1)
	{
		/* Step 1: Get Temperature from LM35 */
		Loc_u16ADCValue = ADC_Read(ADC_CH0);
		Glb_u8Temperature = ( Loc_u16ADCValue * 500 ) / 1023;

		/* Step 2: Display Temperature on LCD */
		xEventGroupSetBits( EG_SystemEventGroupHandle, E_DISP_TEMPERATURE );

		/* Step 3: Check Temperature Status */
		/* Check 1: Temperature ( Temperature < 45 Degree Celsius ) */
		if( Glb_u8Temperature < 45 )
		{
			/* Check 1.1: Normal Temperature ( Temperature < 30 Degree Celsius ) */
			if( Glb_u8Temperature < 30 )
			{
				/* Check 1.1.1: Temperature Status is changed */
				if ( Loc_u8TemperatureStatus != APP_U8_NORMAL_TEMP )
				{
					/* Step 4: Update Temperature Status */
					Loc_u8TemperatureStatus = APP_U8_NORMAL_TEMP;

					/* Step 5: Take Action */
					clearBit( APP_FAN_PORT, APP_FAN_PIN ); 	// Turn off fan
					Led_Off( APP_AC_LED );					// Turn off AC
				}
			}
			/* Check 1.2: Hot Temperature ( Temperature < 35 Degree Celsius ) */
			else if( Glb_u8Temperature < 35 )
			{
				/* Check 1.2.1: Temperature Status is changed */
				if ( Loc_u8TemperatureStatus != APP_U8_HIGH_TEMP )
				{
					/* Step 4: Update Temperature Status */
					Loc_u8TemperatureStatus = APP_U8_HIGH_TEMP;

					/* Step 5: Take Action */
					setBit( APP_FAN_PORT, APP_FAN_PIN );   	// Turn on fan
					Led_Off( APP_AC_LED );					// Turn off AC
				}
			}
			/* Check 1.3: Very Hot Temperature ( Temperature < 45 Degree Celsius ) */
			else if( Glb_u8Temperature < 45 )
			{
				/* Check 1.3.1: Temperature Status is changed */
				if ( Loc_u8TemperatureStatus != APP_U8_VERY_HIGH_TEMP )
				{
					/* Step 4: Update Temperature Status */
					Loc_u8TemperatureStatus = APP_U8_VERY_HIGH_TEMP;

					/* Step 5: Take Action */
					clearBit( APP_FAN_PORT, APP_FAN_PIN );  // Turn off fan
					Led_On( APP_AC_LED );					// Turn on AC
				}
			}
		}
		/* Check 2: Extreme Temperature ( Temperature >= 45 Degree Celsius ) */
		else
		{
			/* Check 2.1: Temperature Status is changed */
			if ( Loc_u8TemperatureStatus != APP_U8_EXTREME_HIGH_TEMP )
			{
				/* Step 4: Update Temperature Status */
				Loc_u8TemperatureStatus = APP_U8_EXTREME_HIGH_TEMP;

				/* Step 5: Take Action */
				setBit( APP_FAN_PORT, APP_FAN_PIN );    // Turn on fan
				Led_On( APP_AC_LED );					// Turn on AC
			}
		}

		vTaskDelay(1000);
	}
}

/*******************************************************************************************************/
/*
 Name: T_DoorAlarm
 Priority: 4
 Stack Size: 100
 Description: Task to fire an Alarm for 1 sec. when Accessing the Door with a wrong password.
*/
void T_DoorAlarm         ( void* pvParam )
{
	while(1)
	{
		EB_Value = xEventGroupWaitBits (
				   /* Event Group */
				   EG_SystemEventGroupHandle,
				   /* The Event ( i.e.: bit ) within the Event Group to wait for */
				   ( E_DOOR_ALARM ),
				   /* Event should be cleared before returning */
				   pdTRUE,
				   /* Don't wait for the all Events ( i.e.: bits ) */
				   pdFALSE,
				   /* Max delay to wait for Event to be set */
				   portMAX_DELAY );

		/* Check 1: "Door Alarm" Event is set */
		if ( EB_Value & ( E_DOOR_ALARM ) )
		{
			Buz_On();
		}

		vTaskDelay(1000);

		Buz_Off();
	}
}

/*******************************************************************************************************/
