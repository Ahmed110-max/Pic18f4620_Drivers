/* 
 * File:   TIMER2.h
 * Author: AHMED AKRAM
 *
 * Created on April 9, 2024, 4:10 PM
 */

#ifndef TIMER2_H
#define	TIMER2_H
/*-------------------------------includes-------------------------- : */
#include "../GPIO/hal_gpio.h"
#include "../proc/pic18f46k20.h"
#include "../interrupt/mcal_internal_interrupt.h"
/*---------------------------macro declarations-------------------------- : */
/* Post_SCALER_ACTIVATION_DEACTIVATION_CFG = 1 : ACTIVATE   PostSCALER
 * Post_SCALER_ACTIVATION_DEACTIVATION_CFG = 0 : DEACTIVATE PostSCALER   */
#define  Post_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER2        1 
/* Timer2 Input Clock Post-scaler */
#define TIMER2_PostSCALER_DIV_BY_1                             0
#define TIMER2_PostSCALER_DIV_BY_2                             1
#define TIMER2_PostSCALER_DIV_BY_3                             2
#define TIMER2_PostSCALER_DIV_BY_4                             3
#define TIMER2_PostSCALER_DIV_BY_5                             4
#define TIMER2_PostSCALER_DIV_BY_6                             5
#define TIMER2_PostSCALER_DIV_BY_7                             6
#define TIMER2_PostSCALER_DIV_BY_8                             7
#define TIMER2_PostSCALER_DIV_BY_9                             8
#define TIMER2_PostSCALER_DIV_BY_10                            9
#define TIMER2_PostSCALER_DIV_BY_11                            10
#define TIMER2_PostSCALER_DIV_BY_12                            11
#define TIMER2_PostSCALER_DIV_BY_13                            12
#define TIMER2_PostSCALER_DIV_BY_14                            13
#define TIMER2_PostSCALER_DIV_BY_15                            14
#define TIMER2_PostSCALER_DIV_BY_16                            15


/* PRE_SCALER_ACTIVATION_DEACTIVATION_CFG = 1 : ACTIVATE PRESCALER
 * PRE_SCALER_ACTIVATION_DEACTIVATION_CFG = 0 : DEACTIVATE PRESCALER   */
#define PRE_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER2          1 
/* Timer2 Input Clock Pre-scaler */
#define TIMER2_PRESCALER_DIV_BY_1                              0
#define TIMER2_PRESCALER_DIV_BY_4                              1
#define TIMER2_PRESCALER_DIV_BY_16                             2

/*----------------------------macro functions-------------------------- : */    
/* Enable or Disable Timer2 Module */
#define Enable_Timer2()                                  T2CONbits.TMR2ON = 1
#define DISABLE_Timer2()                                 T2CONbits.TMR2ON = 0
/* Timer2 Input Clock Post-scaler */
#define Timer2_Input_Clock_Postscale_Select(_Postscale_)   T2CONbits.T2OUTPS = _Postscale_
/* Timer2 Input Clock Pre-scaler */
#define Timer2_Input_Clock_Prescale_Select(_Prescale_)   T2CONbits.T2CKPS = _Prescale_


/*-------------------------------data types-------------------------- : */
#if TIMER2_INTERRUPT_MODE
typedef enum
{
    Timer2_interrupt_priority_low,
    Timer2_interrupt_priority_high        
}Timer2_interrupt_priority;
#endif

typedef struct
{
#if TIMER2_INTERRUPT_MODE
    void (*TIMER2_INTERRUPT_HANDLER)(void); 
#if INTERRUPT_PRIORITY_mode
    Timer2_interrupt_priority Timer2_PRIORITY;
#endif
#endif
   
#if PRE_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER2
    uint8 PRE_SCALER_VALUE   :2;
#endif 
#if Post_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER2
    uint8 post_SCALER_VALUE   :4;
#endif 
    uint8 Timer2_preloaded_value;
    uint8  Timer1_Reserved : 2;
}TIMER2;

/*----------------------function declarations-------------------------- : */
Std_ReturnType TIMER2_init(const TIMER2 *my_TIMER2);
Std_ReturnType TIMER2_DEinit(const TIMER2 *my_TIMER2);
Std_ReturnType TIMER2_WRITE_VALUE(const TIMER2 *my_TIMER2,uint8 value);
Std_ReturnType TIMER2_READ_VALUE(const TIMER2 *my_TIMER2,uint8 *value);
#if TIMER2_INTERRUPT_MODE
Std_ReturnType TIMER2_ISR(void);
#endif

#endif	/* TIMER2_H */

