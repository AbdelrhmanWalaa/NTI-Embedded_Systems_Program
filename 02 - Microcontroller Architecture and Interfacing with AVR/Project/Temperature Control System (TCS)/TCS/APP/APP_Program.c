/*
 * APP_Program.c
 *
 *   Created on: Jan 10, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application (APP) functions' implementation.
 */

#include "APP_Config.h"
#include "APP_Interface.h"

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */

/* Global Variable ( Flag ) to be altered when Current State is changed. */
static u8 Glb_u8CurrentState = APP_U8_S1_HOME_SCREEN;

/* Global Variable ( Flag ) to be altered when Home Screen State is changed. */
static u8 Glb_u8HomeScreenState = APP_U8_HOME_SCREEN_1;

/* Global Variables to hold Low Temperature Value and High Temperature Value respectively */
static u8 Glb_u8LowTempValue, Glb_u8HighTempValue;

/* Global Array of Flags to be altered when Current Temperature Value is changed, in order not to overwrite written data in the same Temperature Mode */
static u8 Glb_Au8TempFlagesStates[4] = { APP_U8_FLAG_DOWN, APP_U8_FLAG_DOWN, APP_U8_FLAG_DOWN, APP_U8_FLAG_DOWN };

/*******************************************************************************************************************************************************************/ 
/*
 Name: APP_vdInitialization
 Input: void
 Output: void
 Description: Function to initialize the application.
*/
vd APP_vdInitialization      ( void )
{
	/* MCAL Initialization */
	DIO_vdInitialization();
	
	GLI_vdEnableGIE();
	EXI_u8INTSetCallBack( EXI_U8_INT0, &APP_vdSwitchToHomeScreen );
	EXI_u8EnablePIE( EXI_U8_INT0, EXI_U8_SENSE_FALLING_EDGE );
	
	ADC_vdInitialization();
	
	TMR_vdTMR0Initialization();
	
	UART_vdInitialization();
	TWI_vdMasterModeInitialization();
	
	/* HAL Initialization */
	LCD_vdInitialization();
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdStartProgram
 Input: void
 Output: void
 Description: Function to start the program.
*/
vd APP_vdStartProgram        ( void )
{	
	/* Step 1: Display Welcome Screen -> Temperature Control System */
	LCD_vdClearDisplay();
			
	LCD_u8GoToLocation( LCD_U8_LINE1, 2 );
	LCD_u8WriteString( "Temperature" );
	LCD_u8GoToLocation( LCD_U8_LINE2, 1 );
	LCD_u8WriteString( "Control System" );
			
	_delay_ms(2500);
	
	/* Toggle forever */
	while (1)
	{
		/* Check: Required CurrentState */
		switch ( Glb_u8CurrentState )
		{
			/* Case 1: CurrentState is Home Screen */
			case APP_U8_S1_HOME_SCREEN    : APP_vdDisplayHomeScreen()   ; break;
			/* Case 2: CurrentState is Temperature Screen */
			case APP_U8_S2_TEMP_SCREEN    : APP_vdDisplayTempScreen()   ; break;
			/* Case 2: CurrentState is Set Temperature Screen */
			case APP_U8_S3_SET_TEMP_SCREEN: APP_vdDisplaySetTempScreen(); break;
			/* Case 3: CurrentState is Get Temperature Screen */
			case APP_U8_S4_GET_TEMP_SCREEN: APP_vdDisplayGetTempScreen(); break;
		}
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdSwitchToHomeScreen
 Input: void
 Output: void
 Description: Function to Switch to Home Screen.
*/
vd APP_vdSwitchToHomeScreen	 ( void )
{	
	/* Step 1: Turn Off Temperature LEDs */
	LED_u8SetLEDPin( APP_U8_L_RED_LED, LED_U8_OFF );
	LED_u8SetLEDPin( APP_U8_N_GRN_LED, LED_U8_OFF );
	LED_u8SetLEDPin( APP_U8_H_RED_LED, LED_U8_OFF );
		
	/* Step 2: Turn Off the Fan ( i.e. DCM ) */
	DCM_vdStopDCM();
		
	/* Step 3: Turn Off the Buzzer */
	DIO_u8SetPinValue( APP_U8_BUZ_PORT, APP_U8_BUZ_PIN, DIO_U8_PIN_LOW );
	
	/* Step 4: Change CurrentState to Home Screen State */
	Glb_u8CurrentState = APP_U8_S1_HOME_SCREEN;
	
	/* Step 5: Change HomeScreenState to Home Screen 1 */
	Glb_u8HomeScreenState = APP_U8_HOME_SCREEN_1;
	
	/* Step 6: Update Glb_Au8TempFlagesStates = FLAG DOWN */
	Glb_Au8TempFlagesStates[APP_U8_LOW_TEMP_FLAG]  = APP_U8_FLAG_DOWN;
	Glb_Au8TempFlagesStates[APP_U8_NORM_TEMP_FLAG] = APP_U8_FLAG_DOWN;
	Glb_Au8TempFlagesStates[APP_U8_HIGH_TEMP_FLAG] = APP_U8_FLAG_DOWN;
	Glb_Au8TempFlagesStates[APP_U8_FIRE_TEMP_FLAG] = APP_U8_FLAG_DOWN;
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdDisplayHomeScreen
 Input: void
 Output: void
 Description: Function to display to Home screen.
*/
vd APP_vdDisplayHomeScreen   ( void )
{
	/* Check: Required HomeScreenState */
	switch ( Glb_u8HomeScreenState )
	{
		/* Case 1: HomeScreenState is Home Screen 1 */
		case APP_U8_HOME_SCREEN_1: APP_vdDisplayHomeScreen1(); break;
		/* Case 2: HomeScreenState is Home Screen 2 */
		case APP_U8_HOME_SCREEN_2: APP_vdDisplayHomeScreen2(); break;
		/* Case 3: HomeScreenState is Home Screen 3 */
		case APP_U8_HOME_SCREEN_3: APP_vdDisplayHomeScreen3(); break;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdDisplayHomeScreen1
 Input: void
 Output: void
 Description: Function to display Home screen 1.
*/
vd APP_vdDisplayHomeScreen1  ( void )
{
	/* Define local variable to get the Pressed Key Value = KEY NOT PRESSED */
	u8 Loc_u8PressedKey = KPD_U8_KEY_NOT_PRESSED;

	/* Step 1: Display Home Screen 1 -> Display Temp */
	LCD_vdClearDisplay();
					
	LCD_u8WriteString( "1. Display Temp" );
		
	LCD_u8GoToLocation( LCD_U8_LINE2, 15 );
	LCD_vdSendChar( '+' );
	
	/* Loop: Wait ( Poll ) PressedKey is changed ( i.e. Key is Pressed ) */
	while ( Loc_u8PressedKey == KPD_U8_KEY_NOT_PRESSED )
	{
		/* Step 2: Get PressedKey Value */
		KPD_u8GetPressedKey( &Loc_u8PressedKey );
	}
	
	/* Check 2: Required PressedKey */
	switch ( Loc_u8PressedKey )
	{
		/* Case 1: Number '1' is Pressed */
		case '1': Glb_u8CurrentState    = APP_U8_S2_TEMP_SCREEN; break;
		/* Case 2: Character '+' is Pressed */
		case '+': Glb_u8HomeScreenState = APP_U8_HOME_SCREEN_2 ; break;
		/* Case 3: Other Key is Pressed */
		default:
			/* Error 1: Display Wrong Input on LCD */
			LCD_vdClearDisplay();
			LCD_u8WriteString( "Wrong Input!" );
			
			_delay_ms(1000);
		break;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdDisplayHomeScreen2
 Input: void
 Output: void
 Description: Function to display Home screen 2.
*/
vd APP_vdDisplayHomeScreen2  ( void )
{
	/* Define local variable to get the Pressed Key Value = KEY NOT PRESSED */
	u8 Loc_u8PressedKey = KPD_U8_KEY_NOT_PRESSED;
	
	/* Step 1: Display Home Screen 2 -> Set T_L & T_H */
	LCD_vdClearDisplay();
				
	LCD_u8WriteString( "2. Set T_L & T_H" );
		
	LCD_u8GoToLocation( LCD_U8_LINE2, 0 );
	LCD_vdSendChar( '-' );
		
	LCD_u8GoToLocation( LCD_U8_LINE2, 15 );
	LCD_vdSendChar( '+' );
	
	/* Loop: Wait ( Poll ) PressedKey is changed ( i.e. Key is Pressed ) */
	while ( Loc_u8PressedKey == KPD_U8_KEY_NOT_PRESSED )
	{
		/* Step 2: Get PressedKey Value */
		KPD_u8GetPressedKey( &Loc_u8PressedKey );
	}
	
	/* Check 2: Required PressedKey */
	switch ( Loc_u8PressedKey )
	{
		/* Case 1: Number '2' is Pressed */
		case '2': Glb_u8CurrentState    = APP_U8_S3_SET_TEMP_SCREEN; break;	
		/* Case 2: Character '-' is Pressed */			
		case '-': Glb_u8HomeScreenState = APP_U8_HOME_SCREEN_1     ; break;
		/* Case 3: Character '+' is Pressed */
		case '+': Glb_u8HomeScreenState = APP_U8_HOME_SCREEN_3     ; break;
		/* Case 4: Other Key is Pressed */
		default:
			/* Error 1: Display Wrong Input on LCD */
			LCD_vdClearDisplay();
			LCD_u8WriteString( "Wrong Input!" );
			
			_delay_ms(1000);
		break;
	}	
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdDisplayHomeScreen3
 Input: void
 Output: void
 Description: Function to display Home screen 3.
*/
vd APP_vdDisplayHomeScreen3  ( void )
{
	/* Define local variable to get the Pressed Key Value = KEY NOT PRESSED */
	u8 Loc_u8PressedKey = KPD_U8_KEY_NOT_PRESSED;
	
	/* Step 1: Display Home Screen 3 -> Get T_L & T_H */
	LCD_vdClearDisplay();
		
	LCD_u8WriteString( "3. Get T_L & T_H" );
		
	LCD_u8GoToLocation( LCD_U8_LINE2, 0 );
	LCD_vdSendChar( '-' );
	
	
	/* Loop: Wait ( Poll ) PressedKey is changed ( i.e. Key is Pressed ) */
	while ( Loc_u8PressedKey == KPD_U8_KEY_NOT_PRESSED )
	{
		/* Step 3: Get PressedKey Value */
		KPD_u8GetPressedKey( &Loc_u8PressedKey );
	}
	
	/* Check 2: Required PressedKey */
	switch ( Loc_u8PressedKey )
	{
		/* Case 1: Number '3' is Pressed */
		case '3': Glb_u8CurrentState    = APP_U8_S4_GET_TEMP_SCREEN; break;
		/* Case 2: Character '-' is Pressed */
		case '-': Glb_u8HomeScreenState = APP_U8_HOME_SCREEN_2     ; break;
		/* Case 3: Other Key is Pressed */
		default:
			/* Error 1: Display Wrong Input on LCD */
			LCD_vdClearDisplay();
			LCD_u8WriteString( "Wrong Input!" );
			
			_delay_ms(1000);
		break;	
	}	
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdDisplayTempScreen
 Input: void
 Output: void
 Description: Function to display Temperature Screen.
*/
vd APP_vdDisplayTempScreen   ( void )
{	
	/* Define local variable to get the Current Temperature Value */
	u16 Loc_u16CurrentTempValue = 0;
	
	/* Loop: Wait until external interrupt takes place  */
	while ( Glb_u8CurrentState == APP_U8_S2_TEMP_SCREEN )
	{
		/* Step 1: Get CurrentTempValue  */
		TSI_u8GetTemperature( &Loc_u16CurrentTempValue );
			
		/* Step 2: Display CurrentTempValue on LCD */
		LCD_vdClearDisplay();
		LCD_u8WriteString( "Temp: " );
		LCD_vdWriteNumber( Loc_u16CurrentTempValue );
		LCD_u8WriteString( " C" );
		LCD_u8GoToLocation( LCD_U8_LINE2, 0 );
							
		/* Check 1: Low Temperature ( i.e. CurrentTempValue <= LowTempValue ) */
		if ( Loc_u16CurrentTempValue <= Glb_u8LowTempValue )
		{
			/* Step 1: Display Operating Mode on LCD */			
			LCD_u8WriteString( "Low Temp Mode" );
			
			/* Check 1.1: TempFlagesStates of Low Temp in order not to overwrite written data of Low Temp Mode */
			if ( Glb_Au8TempFlagesStates[APP_U8_LOW_TEMP_FLAG] == APP_U8_FLAG_DOWN )
			{ 
				APP_vdLowTempMode();
			}
		}
		/* Check 2: Normal Temperature ( i.e. LowTempValue < CurrentTempValue < HighTempValue ) */
		else if ( ( Loc_u16CurrentTempValue > Glb_u8LowTempValue ) && ( Loc_u16CurrentTempValue < Glb_u8HighTempValue ) )
		{
			/* Step 1: Display Operating Mode on LCD */
			LCD_u8WriteString( "Normal Temp Mode" );
			
			/* Check 2.1: TempFlagesStates of Normal Temp in order not to overwrite written data of Normal Temp Mode */
			if ( Glb_Au8TempFlagesStates[APP_U8_NORM_TEMP_FLAG] == APP_U8_FLAG_DOWN )
			{
				APP_vdNormalTempMode();
			}
		}
		/* Check 3: High Temperature ( i.e. HighTempValue <= CurrentTempValue < 75 C ) */
		else if ( ( Loc_u16CurrentTempValue >= Glb_u8HighTempValue ) && ( Loc_u16CurrentTempValue < 75 ) )
		{
			/* Step 1: Display Operating Mode on LCD */
			LCD_u8WriteString( "High Temp Mode" );
			
			/* Check 3.1: TempFlagesStates of High Temp in order not to overwrite written data of High Temp Mode */
			if ( Glb_Au8TempFlagesStates[APP_U8_HIGH_TEMP_FLAG] == APP_U8_FLAG_DOWN )
			{
				APP_vdHighTempMode();
			}
		}
		/* Check 4: Extreme High Temperature or Fire ( i.e. CurrentTempValue >= 75 C ) */
		else if ( Loc_u16CurrentTempValue >= 75 )
		{
			/* Step 1: Display Operating Mode on LCD */
			LCD_u8WriteString( "Caution Fire !!" );
			
			/* Check 4.1: TempFlagesStates of Fire Temp in order not to overwrite written data of Fire Temp Mode */
			if ( Glb_Au8TempFlagesStates[APP_U8_FIRE_TEMP_FLAG] == APP_U8_FLAG_DOWN )
			{
				APP_vdFireTempMode();
			}
		}
		
		_delay_ms(1000);
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdLowTempMode
 Input: void
 Output: void
 Description: Function to display Low Temperature Mode.
*/
vd APP_vdLowTempMode		 ( void )
{
	/* Step 1: Turn On the Red Low Temperature LED */
	LED_u8SetLEDPin( APP_U8_L_RED_LED, LED_U8_ON  );
	LED_u8SetLEDPin( APP_U8_N_GRN_LED, LED_U8_OFF );
	LED_u8SetLEDPin( APP_U8_H_RED_LED, LED_U8_OFF );
				
	/* Step 2: Turn Off the Fan ( i.e. DCM ) */
	DCM_vdStopDCM();
				
	/* Step 3: Send "Current Temperature is Low" on UART terminal */
	UART_u8TransmitString( "Current Temperature is Low" );
	UART_u8TransmitByte( UART_U8_POLLING_MODE, 13 );
				
	/* Step 4: Turn Off the Buzzer */
	DIO_u8SetPinValue( APP_U8_BUZ_PORT, APP_U8_BUZ_PIN, DIO_U8_PIN_LOW );
	
	/* Step 5: Update TempFlagesStates = FLAG DOWN, and TempFlagesStates of Low Temp = FLAG UP */
	Glb_Au8TempFlagesStates[APP_U8_LOW_TEMP_FLAG]  = APP_U8_FLAG_UP  ;
	Glb_Au8TempFlagesStates[APP_U8_NORM_TEMP_FLAG] = APP_U8_FLAG_DOWN;
	Glb_Au8TempFlagesStates[APP_U8_HIGH_TEMP_FLAG] = APP_U8_FLAG_DOWN;
	Glb_Au8TempFlagesStates[APP_U8_FIRE_TEMP_FLAG] = APP_U8_FLAG_DOWN;
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdNormalTempMode
 Input: void
 Output: void
 Description: Function to display Normal Temperature Mode.
*/
vd APP_vdNormalTempMode		 ( void )
{	
	/* Step 1: Turn On the Green Normal Temperature LED */
	LED_u8SetLEDPin( APP_U8_L_RED_LED, LED_U8_OFF );
	LED_u8SetLEDPin( APP_U8_N_GRN_LED, LED_U8_ON  );
	LED_u8SetLEDPin( APP_U8_H_RED_LED, LED_U8_OFF );
	
	/* Step 2: Turn On the Fan with 50% Speed ( i.e. DCM with 50% PWM ) */
	DCM_u8RotateDCMInOneDirection( APP_U8_DCM_HALF_SPEED );
	
	/* Step 3: Send "Current Temperature is Normal" on UART terminal */
	UART_u8TransmitString( "Current Temperature is Normal" );
	UART_u8TransmitByte( UART_U8_POLLING_MODE, 13 );
	
	/* Step 4: Turn Off the Buzzer */
	DIO_u8SetPinValue( APP_U8_BUZ_PORT, APP_U8_BUZ_PIN, DIO_U8_PIN_LOW );
	
	/* Step 5: Update TempFlagesStates = FLAG DOWN, and TempFlagesStates of Normal Temp = FLAG UP */
	Glb_Au8TempFlagesStates[APP_U8_LOW_TEMP_FLAG]  = APP_U8_FLAG_DOWN;
	Glb_Au8TempFlagesStates[APP_U8_NORM_TEMP_FLAG] = APP_U8_FLAG_UP  ;
	Glb_Au8TempFlagesStates[APP_U8_HIGH_TEMP_FLAG] = APP_U8_FLAG_DOWN;
	Glb_Au8TempFlagesStates[APP_U8_FIRE_TEMP_FLAG] = APP_U8_FLAG_DOWN;
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdHighTempMode
 Input: void
 Output: void
 Description: Function to display High Temperature Mode.
*/
vd APP_vdHighTempMode		 ( void )
{
	/* Step 1: Turn on the Red High Temperature LED */
	LED_u8SetLEDPin( APP_U8_L_RED_LED, LED_U8_OFF );
	LED_u8SetLEDPin( APP_U8_N_GRN_LED, LED_U8_OFF );
	LED_u8SetLEDPin( APP_U8_H_RED_LED, LED_U8_ON  );
	
	/* Step 2: Turn On the Fan with 100% Speed ( i.e. DCM with 100% PWM ) */
	DCM_u8RotateDCMInOneDirection( APP_U8_DCM_FULL_SPEED );
	
	/* Step 3: Send "Current Temperature is High" on UART terminal */
	UART_u8TransmitString( "Current Temperature is High" );
	UART_u8TransmitByte( UART_U8_POLLING_MODE, 13 );
	
	/* Step 4: Turn Off the Buzzer */
	DIO_u8SetPinValue( APP_U8_BUZ_PORT, APP_U8_BUZ_PIN, DIO_U8_PIN_LOW );
	
	/* Step 5: Update TempFlagesStates = FLAG DOWN, and TempFlagesStates of High Temp = FLAG UP */
	Glb_Au8TempFlagesStates[APP_U8_LOW_TEMP_FLAG]  = APP_U8_FLAG_DOWN;
	Glb_Au8TempFlagesStates[APP_U8_NORM_TEMP_FLAG] = APP_U8_FLAG_DOWN;
	Glb_Au8TempFlagesStates[APP_U8_HIGH_TEMP_FLAG] = APP_U8_FLAG_UP  ;
	Glb_Au8TempFlagesStates[APP_U8_FIRE_TEMP_FLAG] = APP_U8_FLAG_DOWN;	
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdFireTempMode
 Input: void
 Output: void
 Description: Function to display Fire Temperature Mode.
*/
vd APP_vdFireTempMode		 ( void )
{
	/* Step 1: Turn on the Red High Temperature LED */
	LED_u8SetLEDPin( APP_U8_L_RED_LED, LED_U8_OFF );
	LED_u8SetLEDPin( APP_U8_N_GRN_LED, LED_U8_OFF );
	LED_u8SetLEDPin( APP_U8_H_RED_LED, LED_U8_ON  );
	
	/* Step 2: Turn On the Fan with 100% Speed ( i.e. DCM with 100% PWM ) */
	DCM_u8RotateDCMInOneDirection( APP_U8_DCM_FULL_SPEED );
	
	/* Step 3: Send "Caution Fire !!" on UART terminal */
	UART_u8TransmitString( "Caution Fire !!" );
	UART_u8TransmitByte( UART_U8_POLLING_MODE, 13 );
	
	/* Step 4: Turn On the Buzzer */
	DIO_u8SetPinValue( APP_U8_BUZ_PORT, APP_U8_BUZ_PIN, DIO_U8_PIN_HIGH );
	
	/* Step 5: Update TempFlagesStates = FLAG DOWN, and TempFlagesStates of Fire Temp = FLAG UP */
	Glb_Au8TempFlagesStates[APP_U8_LOW_TEMP_FLAG]  = APP_U8_FLAG_DOWN;
	Glb_Au8TempFlagesStates[APP_U8_NORM_TEMP_FLAG] = APP_U8_FLAG_DOWN;
	Glb_Au8TempFlagesStates[APP_U8_HIGH_TEMP_FLAG] = APP_U8_FLAG_DOWN  ;
	Glb_Au8TempFlagesStates[APP_U8_FIRE_TEMP_FLAG] = APP_U8_FLAG_UP  ;
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdDisplaySetTempScreen
 Input: void
 Output: void
 Description: Function to display Set Temperature Screen.
*/
vd APP_vdDisplaySetTempScreen( void )
{	
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
	
	u8 Loc_u8TempValue = 0;
		
	/* Step 1: Display LowTemp Value on LCD */
	LCD_vdClearDisplay();				
	LCD_u8WriteString( "T_L = " );
	
	/* Step 2: Get LowTempValue */
	LCD_vdSendCmnd( LCD_U8_CURSOR_ON );	
	Loc_u8ErrorState = APP_u8SetTemperatureValue( &Loc_u8TempValue );	
	LCD_vdSendCmnd( LCD_U8_CURSOR_OFF );
	
	/* Check 1: ErrorState is not OK ( i.e. LowTempValue is not Set ) */
	if ( Loc_u8ErrorState != STD_TYPES_OK )
	{
		/* Error 1: Display Wrong Input on LCD */
		_delay_ms(500);
		
		LCD_vdClearDisplay();
		LCD_u8WriteString( "Wrong Input!" );
		
		_delay_ms(1000);
		return;
	}
	
	_delay_ms(500);
	Glb_u8LowTempValue = Loc_u8TempValue;
	
	/* Step 3: Display HighTemp Value on LCD */
	LCD_u8GoToLocation( LCD_U8_LINE2, 0 );
	LCD_u8WriteString( "T_H = " );
	
	/* Step 4: Get HighTempValue */
	LCD_vdSendCmnd( LCD_U8_CURSOR_ON );	
	Loc_u8ErrorState = APP_u8SetTemperatureValue( &Loc_u8TempValue );	
	LCD_vdSendCmnd( LCD_U8_CURSOR_OFF );
	
	/* Check 2: ErrorState is not OK ( i.e. HighTempValue is not Set ) */
	if ( Loc_u8ErrorState != STD_TYPES_OK )
	{
		/* Error 2: Display Wrong Input on LCD */
		_delay_ms(500);
				
		LCD_vdClearDisplay();
		LCD_u8WriteString( "Wrong Input!" );
		
		_delay_ms(1000);
		return;
	}
	
	_delay_ms(500);
	Glb_u8HighTempValue = Loc_u8TempValue;
		
	/* Check 3: LowTempValue < HighTempValue < 75 */
	if ( ( Glb_u8HighTempValue > Glb_u8LowTempValue ) && ( Glb_u8HighTempValue < 75 ) )
	{
		/* Step 5: Set LowTempValue and HighTempValue in EEPROM */
		Loc_u8ErrorState = EEPROM_u8WriteByte( APP_U8_TEMP_PAGE, APP_U8_LOW_TEMP_LOC , Glb_u8LowTempValue  );
		Loc_u8ErrorState = EEPROM_u8WriteByte( APP_U8_TEMP_PAGE, APP_U8_HIGH_TEMP_LOC, Glb_u8HighTempValue );
		
		/* Check 3.1: ErrorState is OK */
		if ( Loc_u8ErrorState == STD_TYPES_OK )
		{
			/* Success 1: Display Success on LCD */
			LCD_vdClearDisplay();
			LCD_u8WriteString( "Success!" );
			
			_delay_ms(1000);
		}
		/* Check 3.2: ErrorState is NOK */
		else
		{
			/* Error 3: Display Failed on LCD */
			LCD_vdClearDisplay();
			LCD_u8WriteString( "Failed!" );
					
			_delay_ms(1000);
		}
		
		/* Step 6: Update CurrentState = HOME SCREEN, and HomeScreenState = HOME SCREEN 1 */
		Glb_u8CurrentState    = APP_U8_S1_HOME_SCREEN;
		Glb_u8HomeScreenState = APP_U8_HOME_SCREEN_1;		
	}
	/* Check 4: LowTempValue >= HighTempValue, or HighTempValue > 75 */
	else
	{
		/* Error 4: Display Logic Error on LCD */
		LCD_vdClearDisplay();
		LCD_u8WriteString( "Logic Error!" );
					
		_delay_ms(1000);
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdDisplayGetTempScreen
 Input: void
 Output: void
 Description: Function to display Get Temperature Screen.
*/
vd APP_vdDisplayGetTempScreen( void )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
		
	/* Step 1: Get LowTempValue and HighTempValue from EEPROM */
	Loc_u8ErrorState = EEPROM_u8ReadByte( APP_U8_TEMP_PAGE, APP_U8_LOW_TEMP_LOC , &Glb_u8LowTempValue  );
	Loc_u8ErrorState = EEPROM_u8ReadByte( APP_U8_TEMP_PAGE, APP_U8_HIGH_TEMP_LOC, &Glb_u8HighTempValue );
		
	/* Check 1: ErrorState is OK */
	if ( Loc_u8ErrorState == STD_TYPES_OK )
	{		
		/* Step 2: Display LowTemp and HighTemp Values on LCD */
		LCD_vdClearDisplay();
				
		LCD_u8WriteString( "T_L = " );
		LCD_vdWriteNumber( Glb_u8LowTempValue );
				
		LCD_u8GoToLocation( LCD_U8_LINE2, 0 );
			
		LCD_u8WriteString( "T_H = " );
		LCD_vdWriteNumber( Glb_u8HighTempValue );
		
		/* Loop: Wait until external interrupt takes place */
		while ( Glb_u8CurrentState == APP_U8_S4_GET_TEMP_SCREEN );
	}
	/* Check 2: ErrorState is NOK */
	else
	{		
		/* Error 1: Display Failed on LCD */
		LCD_vdClearDisplay();
		LCD_u8WriteString( "Failed!" );
			
		_delay_ms(1000);
	}
}

/*******************************************************************************************************************************************************************/

/*
 Name: APP_u8SetTemperatureValue
 Input: Pointer to u8 ReturnedTempValue
 Output: u8 Error or No Error
 Description: Function to Set Temperature Value.
*/
u8 APP_u8SetTemperatureValue ( u8 *Cpy_pu8ReturnedTempValue )
{	
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
	
	/* Define local variable to get the Pressed Key Value = KEY NOT PRESSED */
	u8 Loc_u8PressedKey = KPD_U8_KEY_NOT_PRESSED;
	
	/* Define local variable to set the TempValue with Two Digits only */
	u8 Loc_u8Counter = 1;	
		
	/* Loop 1: Wait until Counter equals to 2 ( i.e. TempValue is Set ) */
	while ( Loc_u8Counter <= 2 )
	{
		/* Loop 1.1: Wait ( Poll ) until PressedKey is changed ( i.e. Key is Pressed ), or CurrentState is changed */
		while ( ( Loc_u8PressedKey == KPD_U8_KEY_NOT_PRESSED ) && ( Glb_u8CurrentState == APP_U8_S3_SET_TEMP_SCREEN ) )
		{
			/* Step 1: Get PressedKey Value */
			KPD_u8GetPressedKey( &Loc_u8PressedKey );
		}
		
		/* Step 2: Write Number or Character on LCD */
		LCD_vdSendChar( Loc_u8PressedKey );		
		
		/* Check 1: Required PressedKey */
		switch ( Loc_u8PressedKey )
		{
			/* Case 1: PressedKey is a Digit */
			case '0'...'9':
			
				/* Check 1.1: Required Counter Value */
				switch ( Loc_u8Counter )
				{
					/* Case A: Counter = 1 ( i.e. 1st Digit ) */
					case 1:
						/* Step 3: Set TempValue 1st Digit, and increment Counter */
						*Cpy_pu8ReturnedTempValue = Loc_u8PressedKey - '0';
						Loc_u8Counter++;
					break;
					
					/* Case B: Counter = 2 ( i.e. 2nd Digit ) */
					case 2:
						/* Step 5: Set TempValue 2nd Digit, and increment Counter */
						*Cpy_pu8ReturnedTempValue = ( ( *Cpy_pu8ReturnedTempValue ) * 10 ) + ( Loc_u8PressedKey - '0' );
						Loc_u8Counter++;
					break;
				}
			break;
			
			/* Case 2: PressedKey is not a Digit */
			default:
				
				/* Update error state = NOK, wrong PressedKey! */
				Loc_u8ErrorState = STD_TYPES_NOK;		
				
				return Loc_u8ErrorState;
								
			break;
		}
		
		/* Step 4: Update PressedKey to KEY NOT PRESSED */
		Loc_u8PressedKey = KPD_U8_KEY_NOT_PRESSED;
	}
	
	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/