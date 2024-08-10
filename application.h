/* 
 * File:   application.h
 * Author: AHMED AKRAM
 *
 * Created on September 14, 2023, 2:47 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H
/*-------------------------------includes-------------------------- : */
#include "ECU_layer/Ecu_initialize.h"
#include "MCAL_layer/interrupt/mcal_interrupt_manager.h"
#include "MCAL_layer/EEPROM/hal_EEPROM.h"
#include "MCAL_layer/ADC/ADC.h"
#include "MCAL_layer/TIMER0/TIMER0.h"
#include "MCAL_layer/TIMER1/TIMER1.h"
#include "MCAL_layer/TIMER2/TIMER2.h"
#include "MCAL_layer/TIMER3/TIMER3.h"
#include "CCP.h"
#include "MCAL_layer/EUSART/EUSART.h"
/*---------------------------macro declarations-------------------------- : */


/*----------------------------macro functions-------------------------- : */



/*-------------------------------data types-------------------------- : */
extern Key_pad keypad_1;
extern Lcd_4bit_mode lcd1;
extern Lcd_8bit_mode lcd2; 
extern LED_t LED1;
extern LED_t LED2;
extern LED_t LED3;
extern LED_t LED4;
extern BUTTON btn2;
extern BUTTON btn1;
extern MOTOR motor1;
extern MOTOR motor2;
/*----------------------function declarations-------------------------- : */
void application_initialize(void);

Std_ReturnType APP_INT0_ISR(void);
Std_ReturnType APP_INT1_ISR(void);
Std_ReturnType APP_INT2_ISR(void);

Std_ReturnType APP_RB4_ISR_high(void);
Std_ReturnType APP_RB4_ISR_low(void);

Std_ReturnType APP_RB5_ISR_high(void);
Std_ReturnType APP_RB5_ISR_low(void);

Std_ReturnType APP_RB6_ISR_high(void);
Std_ReturnType APP_RB6_ISR_low(void);

Std_ReturnType APP_RB7_ISR_high(void);
Std_ReturnType APP_RB7_ISR_low(void);

Std_ReturnType APP_ADC_ISR(void);

Std_ReturnType APP_TIMER0_ISR(void);
Std_ReturnType APP_TIMER1_ISR(void);
Std_ReturnType APP_TIMER2_ISR(void);
Std_ReturnType APP_TIMER3_ISR(void);

Std_ReturnType APP_CCP1_ISR(void);
Std_ReturnType APP_CCP2_ISR(void);
#endif	/* APPLICATION_H */

