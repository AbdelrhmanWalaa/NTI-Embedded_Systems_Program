/*
 * BasicIO.h
 *
 * Created: 7/6/2021 11:01:27 AM
 *  Author: MahmoudH
 */ 


#ifndef BASICIO_H_
#define BASICIO_H_

#include "avr/io.h"
#include "data_types.h"
/* CFG Start */
#define LEDS_PORT			PORTA
#define LEDS_DDR			DDRA
#define LEDS_MSK			0xFF

#define BUTTONS_PORT		PORTD
#define BUTTONS_DDR			DDRD
#define BUTTONS_PINR		PIND
#define BUTTONS_START_PIN	PD2

#define BUZZER_PORT			PORTD
#define BUZZER_DDR			DDRD
#define BUZZER_PIN			PD7
/* CFG End */

typedef enum{
	LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7
}LED;

typedef enum{
	BTN_UP = BUTTONS_START_PIN, BTN_DOWN, BTN_CENTER, BTN_RIGHT, BTN_LEFT
}Button;

/* Leds */
void Led_Init(LED led);
void Led_On(LED led);
void Led_Off(LED led);
void Led_Toggle(LED led);

void Leds_Init(u8 ledMask);
void Leds_On(u8 ledMask);
void Leds_Off(u8 ledMask);
void Leds_Toggle(u8 ledMask);

void Leds_AllInit(void);
void Leds_AllOn(void);
void Leds_AllOff(void);
void Leds_AllToggle(void);

/* Buttons */
void Btn_Init(Button btn);
Bool Btn_IsPressed(Button btn);

/* Buzzer */
void Buz_Init(void);
void Buz_On(void);
void Buz_Off(void);
void Buz_Toggle(void);

#endif /* BASICIO_H_ */
