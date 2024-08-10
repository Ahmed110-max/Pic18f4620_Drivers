/* 
 * File:   TIMER3.h
 * Author: AHMED AKRAM
 *
 * Created on April 11, 2024, 11:24 AM
 */

#ifndef TIMER3_H
#define	TIMER3_H
/*-------------------------------includes-------------------------- : */
#include "../GPIO/hal_gpio.h"
#include "../proc/pic18f46k20.h"
#include "../interrupt/mcal_internal_interrupt.h"
/*---------------------------macro declarations-------------------------- : */
/* PRE_SCALER_ACTIVATION_DEACTIVATION_CFG = 1 : ACTIVATE PRESCALER
 * PRE_SCALER_ACTIVATION_DEACTIVATION_CFG = 0 : DEACTIVATE PRESCALER   */
#define PRE_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER3        1 
/* Timer3 Clock Source (Timer or Counter) */
#define Timer_MODE                                           0
#define counter_MODE                                         1
/* Timer3 External Clock Input Synchronization */
#define Timer3_COUNTER_Async_MODE_ENABLE                     1
#define Timer3_COUNTER_Sync_MODE_ENABLE                      0
/* Timer3 Input Clock Pre-scaler */
#define TIMER3_PRESCALER_DIV_BY_1                            0
#define TIMER3_PRESCALER_DIV_BY_2                            1
#define TIMER3_PRESCALER_DIV_BY_4                            2
#define TIMER3_PRESCALER_DIV_BY_8                            3
/* 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_8Bit_MODE        0
#define TIMER3_RW_REG_16Bit_MODE       1
/*Timer3 and Timer1 to CCPx Enable bits*/
/*----------------------------macro functions-------------------------- : */
/* Enable or Disable Timer3 Module */
#define Enable_Timer3()                                  T3CONbits.TMR3ON = 1
#define DISABLE_Timer3()                                 T3CONbits.TMR3ON = 0
/*  Timer3 Clock Source (Timer or Counter) */
#define Timer3_TIMER_MODE_ENABLE()                       T3CONbits.TMR3CS = 0
#define Timer3_COUNTER_MODE_ENABLE()                     T3CONbits.TMR3CS = 1
/*  Timer3 External Clock Input Synchronization */
#define Timer3_COUNTER_Async_MODE_ENABLE()               T3CONbits.NOT_T3SYNC = 1
#define Timer3_COUNTER_Sync_MODE_ENABLE()                T3CONbits.NOT_T3SYNC = 0
/* Timer3 Input Clock Pre-scaler */
#define Timer3_Input_Clock_Prescale_Select(_Prescale_)   T3CONbits.T3CKPS = _Prescale_
/* 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_8BIT_MODE_ENABLE()                 T3CONbits.RD16 = 0
#define TIMER3_RW_REG_16BIT_MODE_ENABLE()                T3CONbits.RD16 = 1
/*-------------------------------data types-------------------------- : */
#if TIMER3_INTERRUPT_MODE
typedef enum
{
    Timer3_interrupt_priority_low,
    Timer3_interrupt_priority_high        
}Timer3_interrupt_priority;
#endif

 
  typedef struct
{
#if TIMER3_INTERRUPT_MODE
    void (*TIMER3_INTERRUPT_HANDLER)(void); 
#if INTERRUPT_PRIORITY_mode
    Timer3_interrupt_priority Timer3_PRIORITY;
#endif
#endif
#if PRE_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER3
   uint8 PRE_SCALER_VALUE   :2;
#endif 
    uint8 Timer3_MODE : 1;
    /*only use it when in counter mode */
    uint8 Timer3_External_Clock_Input_Synchronization : 1; /*ref @ line 40 */
    uint8 Timer3_REGISTER_SIZE : 1;
    uint16 Timer3_preloaded_value;

    uint8  Timer3_Reserved : 4;
}TIMER3;

/*----------------------function declarations-------------------------- : */
Std_ReturnType TIMER3_init(const TIMER3 *my_TIMER3);
Std_ReturnType TIMER3_DEinit(const TIMER3 *my_TIMER3);
Std_ReturnType TIMER3_WRITE_VALUE(const TIMER3 *my_TIMER3,uint16 value);
Std_ReturnType TIMER3_READ_VALUE(const TIMER3 *my_TIMER3,uint16 *value);
#if TIMER1_INTERRUPT_MODE
Std_ReturnType TIMER3_ISR(void);
#endif
            
#endif	/* TIMER3_H */

