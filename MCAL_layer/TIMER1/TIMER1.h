/* 
 * File:   TIMER1.h
 * Author: AHMED AKRAM
 *
 * Created on March 16, 2024, 10:40 PM
 */

#ifndef TIMER1_H
#define	TIMER1_H
/*-------------------------------includes-------------------------- : */
#include "../GPIO/hal_gpio.h"
#include "../proc/pic18f46k20.h"
#include "../interrupt/mcal_internal_interrupt.h"
/*---------------------------macro declarations-------------------------- : */
/* PRE_SCALER_ACTIVATION_DEACTIVATION_CFG = 1 : ACTIVATE PRESCALER
 * PRE_SCALER_ACTIVATION_DEACTIVATION_CFG = 0 : DEACTIVATE PRESCALER   */
#define PRE_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER1        1 
/* Timer1 Clock Source (Timer or Counter) */
#define Timer_MODE                                           0
#define counter_MODE                                         1
/* Timer1 External Clock Input Synchronization */
#define Timer1_COUNTER_Async_MODE_ENABLE                     1
#define Timer1_COUNTER_Sync_MODE_ENABLE                      0
/* Timer1 Oscillator */
#define Timer1_Oscillator_HW_Enable                          1
#define Timer1_Oscillator_HW_DISABLE                         0
/* Timer1 Input Clock Pre-scaler */
#define TIMER1_PRESCALER_DIV_BY_1                            0
#define TIMER1_PRESCALER_DIV_BY_2                            1
#define TIMER1_PRESCALER_DIV_BY_4                            2
#define TIMER1_PRESCALER_DIV_BY_8                            3
/* 16-Bit Read/Write Mode */
#define TIMER1_RW_REG_8Bit_MODE        0
#define TIMER1_RW_REG_16Bit_MODE       1
/*----------------------------macro functions-------------------------- : */
/* Enable or Disable Timer1 Module */
#define Enable_Timer1()                                  T1CONbits.TMR1ON = 1
#define DISABLE_Timer1()                                 T1CONbits.TMR1ON = 0
/*  Timer1 Clock Source (Timer or Counter) */
#define Timer1_TIMER_MODE_ENABLE()                       T1CONbits.TMR1CS = 0
#define Timer1_COUNTER_MODE_ENABLE()                     T1CONbits.TMR1CS = 1
/*  Timer1 External Clock Input Synchronization */
#define Timer1_COUNTER_Async_MODE_ENABLE()               T1CONbits.NOT_T1SYNC = 1
#define Timer1_COUNTER_Sync_MODE_ENABLE()                T1CONbits.NOT_T1SYNC = 0
/* Timer1 Oscillator */
#define Timer1_Oscillator_HW_Enable()                    T1CONbits.T1OSCEN = 1 
#define Timer1_Oscillator_HW_DISABLE()                   T1CONbits.T1OSCEN = 0
/* Timer1 Input Clock Pre-scaler */
#define Timer1_Input_Clock_Prescale_Select(_Prescale_)   T1CONbits.T1CKPS = _Prescale_
/* Timer1 System Clock Status */
#define Timer1_System_Clock_Status_bit()                 T1CONbits.T1RUN
/* 16-Bit Read/Write Mode */
#define TIMER1_RW_REG_8BIT_MODE_ENABLE()                 T1CONbits.RD16 = 0
#define TIMER1_RW_REG_16BIT_MODE_ENABLE()                T1CONbits.RD16 = 1

/*-------------------------------data types-------------------------- : */

#if TIMER1_INTERRUPT_MODE
typedef enum
{
    Timer1_interrupt_priority_low,
    Timer1_interrupt_priority_high        
}Timer1_interrupt_priority;
#endif

typedef struct
{
#if TIMER1_INTERRUPT_MODE
    void (*TIMER1_INTERRUPT_HANDLER)(void); 
#if INTERRUPT_PRIORITY_mode
    Timer1_interrupt_priority Timer1_PRIORITY;
#endif
#endif
    uint8 Timer1_MODE : 1;
    uint8  Timer1_Oscillator_cfg :1;/*ref @  line 45*/
    /*only use it when in counter mode */
    uint8 Timer1_External_Clock_Input_Synchronization : 1; /*ref @ line 42 */
    uint8 Timer1_REGISTER_SIZE : 1;
    uint16 Timer1_preloaded_value;
#if PRE_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER1
    uint8 PRE_SCALER_VALUE   :2;
#endif 
    uint8  Timer1_Reserved : 2;
}TIMER1;



/*----------------------function declarations-------------------------- : */
Std_ReturnType TIMER1_init(const TIMER1 *my_TIMER1);
Std_ReturnType TIMER1_DEinit(const TIMER1 *my_TIMER1);
Std_ReturnType TIMER1_WRITE_VALUE(const TIMER1 *my_TIMER1,uint16 value);
Std_ReturnType TIMER1_READ_VALUE(const TIMER1 *my_TIMER1,uint16 *value);
#if TIMER1_INTERRUPT_MODE
Std_ReturnType TIMER1_ISR(void);
#endif

#endif	/* TIMER1_H */

