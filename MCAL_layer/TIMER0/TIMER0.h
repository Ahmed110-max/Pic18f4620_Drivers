/* 
 * File:   TIMER0.h
 * Author: AHMED AKRAM
 *
 * Created on March 1, 2024, 9:49 AM
 */

#ifndef TIMER0_H
#define	TIMER0_H
/*-------------------------------includes-------------------------- : */
#include "../GPIO/hal_gpio.h"
#include "../proc/pic18f46k20.h"
#include "../interrupt/mcal_internal_interrupt.h"
/*---------------------------macro declarations-------------------------- : */

/* PRE_SCALER_ACTIVATION_DEACTIVATION_CFG = 1 : ACTIVATE PRESCALER
 * PRE_SCALER_ACTIVATION_DEACTIVATION_CFG = 0 : DEACTIVATE PRESCALER   */
#define PRE_SCALER_ACTIVATION_DEACTIVATION_CFG               0 

#define Timer0_8_bit_MODE                                    1
#define Timer0_16_bit_MODE                                   0

#define Timer_MODE                                           1
#define counter_MODE                                         0

#define TIMER0_COUNTER_RISING_EDGE_CFG                       1
#define TIMER0_COUNTER_FALLING_EDGE_CFG                      0

/*----------------------------macro functions-------------------------- : */
#define PRE_SCALER_ENABLE()                                 T0CONbits.PSA    = 0              
#define PRE_SCALER_DISABLE()                                T0CONbits.PSA    = 1
#define Timer0_Source_Edge_RISING_EDGE()                    T0CONbits.T0SE   = 0
#define Timer0_Source_Edge_FALING_EDGE()                    T0CONbits.T0SE   = 1
#define Timer0_TIMER_MODE_ENABLE()                          T0CONbits.T0CS   = 0
#define Timer0_COUNTER_MODE_ENABLE()                        T0CONbits.T0CS   = 1
#define Timer0_8_bit()                                      T0CONbits.T08BIT = 1
#define Timer0_16_bit()                                     T0CONbits.T08BIT = 0
#define Enable_Timer0()                                     T0CONbits.TMR0ON = 1
#define DISABLE_Timer0()                                    T0CONbits.TMR0ON = 0
/*-------------------------------data types-------------------------- : */
/**
 * Timer0 Pre-Scaler Select 
 */
typedef enum 
{
    TIMER0_PRESCALER_DIV_BY_2,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256        
}Timer0_Prescaler_Select;


#if TIMER0_INTERRUPT_MODE
typedef enum
{
    Timer0_interrupt_priority_low,
    Timer0_interrupt_priority_high        
}Timer0_interrupt_priority;
#endif

typedef struct
{
    uint8 Timer0_MODE : 1;
    /*dont use Timer0_counter_Edge if you are in timer mode */
    uint8 Timer0_counter_Edge : 1;
    uint8 Timer0_REGISTER_SIZE : 1;
    uint8  Timer0_Reserved : 5;
    uint16 Timer0_preloaded_value;
#if PRE_SCALER_ACTIVATION_DEACTIVATION_CFG
    Timer0_Prescaler_Select PRE_SCALER_VALUE;
#endif 
       
#if TIMER0_INTERRUPT_MODE
    void (*TIMER0_INTERRUPT_HANDLER)(void); 
    #if INTERRUPT_PRIORITY_mode
    Timer0_interrupt_priority Timer0_PRIORITY;
    #endif
#endif    
}TIMER0;

/*----------------------function declarations-------------------------- : */
Std_ReturnType TIMER0_init(const TIMER0 *my_TIMER0);
Std_ReturnType TIMER0_DEinit(const TIMER0 *my_TIMER0);
Std_ReturnType TIMER0_WRITE_VALUE(const TIMER0 *my_TIMER0,uint16 value);
Std_ReturnType TIMER0_READ_VALUE(const TIMER0 *my_TIMER0,uint16 *value);
#if ADC_INTERRUPT_MODE
Std_ReturnType TIMER0_ISR(void);
#endif
#endif	/* TIMER0_H */

