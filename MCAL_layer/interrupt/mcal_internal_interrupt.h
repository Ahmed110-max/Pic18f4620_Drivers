/* 
 * File:   mcal_internal_interrupt.h
 * Author: AHMED AKRAM
 *
 * Created on February 4, 2024, 2:27 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H
/*-------------------------------includes-------------------------- : */
#include "mcal_interrupt_configration.h"
#include "../ADC/ADC.h"
#include "../TIMER0/TIMER0.h"
#include "../TIMER1/TIMER1.h"
#include "../TIMER2/TIMER2.h"
#include "../TIMER3/TIMER3.h"
#include "../../CCP.h"
/*---------------------------macro declarations-------------------------- : */



/*----------------------------macro functions-------------------------- : */

/*----------------------------ADC-------------------------- : */
#if ADC_INTERRUPT_MODE
/*Enables the ADC interrupt */
#define ADC_INTERRUPT_ENABLE()                  PIE1bits.ADIE = 1
/*Disables the ADC interrupt*/
#define ADC_INTERRUPT_DISABLE()                 PIE1bits.ADIE = 0
/* CLEAR ADC_INTERRUPT FLAG BIT (must be cleared by software) */
#define ADC_INERRUPT_CLEAR_FLAG()               PIR1bits.ADIF = 0    

/*IF PRIORITY IS ENABLED */
 #if INTERRUPT_PRIORITY_mode
/*SET ADC AS HIGH PRIORITY */
#define ADC_HIGH_PRIORITY_SET()                  IPR1bits.ADIP = 1
/*SET ADC AS LOW PRIORITY */
#define ADC_LOW_PRIORITY_SET()                   IPR1bits.ADIP = 0
#endif

#endif

/*----------------------------TIMER0-------------------------- : */
#if TIMER0_INTERRUPT_MODE
/* Enables the TMR0 overflow interrupt  */
#define TIMER0_INTERRUPT_ENABLE()               INTCONbits.TMR0IE = 1
/*Disables the TMR0 overflow interrupt*/
#define TIMER0_INTERRUPT_DISABLE()              INTCONbits.TMR0IE = 0
/* CLEAR TIMER0_INTERRUPT FLAG BIT (must be cleared by software) */
#define TIMER0_INERRUPT_CLEAR_FLAG()            INTCONbits.TMR0IF = 0    

/*IF PRIORITY IS ENABLED */
 #if INTERRUPT_PRIORITY_mode
/*SET TIMER0 AS HIGH PRIORITY */
#define TIMER0_HIGH_PRIORITY_SET()                  INTCON2bits.TMR0IP = 1
/*SET TIMER0 AS LOW PRIORITY */
#define TIMER0_LOW_PRIORITY_SET()                   INTCON2bits.TMR0IP = 0
#endif
#endif

/*----------------------------TIMER1-------------------------- : */
#if TIMER1_INTERRUPT_MODE
/* Enables the TMR1 overflow interrupt  */
#define TIMER1_INTERRUPT_ENABLE()               PIE1bits.TMR1IE = 1
/*Disables the TMR0 overflow interrupt*/
#define TIMER1_INTERRUPT_DISABLE()              PIE1bits.TMR1IE = 0
/* CLEAR TIMER1_INTERRUPT FLAG BIT (must be cleared by software) */
#define TIMER1_INERRUPT_CLEAR_FLAG()            PIR1bits.TMR1IF = 0    

/*IF PRIORITY IS ENABLED */
 #if INTERRUPT_PRIORITY_mode
/*SET TIMER1 AS HIGH PRIORITY */
#define TIMER1_HIGH_PRIORITY_SET()                  IPR1bits.TMR1IP = 1
/*SET TIMER1 AS LOW PRIORITY */
#define TIMER1_LOW_PRIORITY_SET()                   IPR1bits.TMR1IP = 0
#endif
#endif
/*----------------------------TIMER2-------------------------- : */
#if TIMER2_INTERRUPT_MODE
/* Enables the TMR2 overflow interrupt  */
#define TIMER2_INTERRUPT_ENABLE()               PIE1bits.TMR2IE = 1
/*Disables the TMR2 overflow interrupt*/
#define TIMER2_INTERRUPT_DISABLE()              PIE1bits.TMR2IE = 0
/* CLEAR TIMER2_INTERRUPT FLAG BIT (must be cleared by software) */
#define TIMER2_INERRUPT_CLEAR_FLAG()            PIR1bits.TMR2IF = 0    

/*IF PRIORITY IS ENABLED */
 #if INTERRUPT_PRIORITY_mode
/*SET TIMER2 AS HIGH PRIORITY */
#define TIMER2_HIGH_PRIORITY_SET()                  IPR1bits.TMR2IP = 1
/*SET TIMER2 AS LOW PRIORITY */
#define TIMER2_LOW_PRIORITY_SET()                   IPR1bits.TMR2IP = 0
#endif
#endif

/*----------------------------TIMER3-------------------------- : */
#if TIMER3_INTERRUPT_MODE
/* Enables the TMR3 overflow interrupt  */
#define TIMER3_INTERRUPT_ENABLE()               PIE2bits.TMR3IE = 1
/*Disables the TMR3 overflow interrupt*/
#define TIMER3_INTERRUPT_DISABLE()              PIE2bits.TMR3IE = 0
/* CLEAR TIMER3_INTERRUPT FLAG BIT (must be cleared by software) */
#define TIMER3_INERRUPT_CLEAR_FLAG()            PIR2bits.TMR3IF = 0    

/*IF PRIORITY IS ENABLED */
 #if INTERRUPT_PRIORITY_mode
/*SET TIMER3 AS HIGH PRIORITY */
#define TIMER3_HIGH_PRIORITY_SET()                  IPR2bits.TMR3IP = 1
/*SET TIMER2 AS LOW PRIORITY */
#define TIMER2_LOW_PRIORITY_SET()                   IPR2bits.TMR2IP = 0
#endif
#endif

/*----------------------------CCP1-------------------------- : */
#if CCP1_INTERRUPT_MODE
/* Enables the CCP1 overflow interrupt  */
#define CCP1_INTERRUPT_ENABLE()               PIE1bits.CCP1IE = 1
/*Disables the CCP1 overflow interrupt*/
#define CCP1_INTERRUPT_DISABLE()              PIE1bits.CCP1IE = 0
/* CLEAR CCP1_INTERRUPT FLAG BIT (must be cleared by software) */
#define CCP1_INERRUPT_CLEAR_FLAG()            PIR1bits.CCP1IF = 0    

/*IF PRIORITY IS ENABLED */
 #if INTERRUPT_PRIORITY_mode
/*SET CCP1 AS HIGH PRIORITY */
#define CCP1_HIGH_PRIORITY_SET()                  IPR1bits.CCP1IP = 1
/*SET CCP1 AS LOW PRIORITY */
#define CCP1_LOW_PRIORITY_SET()                   IPR1bits.CCP1IP = 0
#endif
#endif
/*----------------------------CCP2-------------------------- : */
#if CCP2_INTERRUPT_MODE
/* Enables the CCP2 overflow interrupt  */
#define CCP2_INTERRUPT_ENABLE()               PIE2bits.CCP2IE = 1
/*Disables the CCP2 overflow interrupt*/
#define CCP2_INTERRUPT_DISABLE()              PIE2bits.CCP2IE = 0
/* CLEAR CCP1_INTERRUPT FLAG BIT (must be cleared by software) */
#define CCP2_INERRUPT_CLEAR_FLAG()            PIR2bits.CCP2IF = 0    

/*IF PRIORITY IS ENABLED */
 #if INTERRUPT_PRIORITY_mode
/*SET CCP2 AS HIGH PRIORITY */
#define CCP2_HIGH_PRIORITY_SET()                  IPR2bits.CCP2IP = 1
/*SET CCP2 AS LOW PRIORITY */
#define CCP2_LOW_PRIORITY_SET()                   IPR2bits.CCP2IP = 0
#endif
#endif

/*----------------------function declarations-------------------------- : */




/*-------------------------------data types-------------------------- : */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

