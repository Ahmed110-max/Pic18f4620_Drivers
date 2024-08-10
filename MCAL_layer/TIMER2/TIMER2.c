/* 
 * File:   TIMER2.c
 * Author: AHMED AKRAM
 *
 * Created on April 9, 2024, 4:10 PM
 */
#include"TIMER2.h"
static inline Std_ReturnType TIMER2_Set_Prescaler(const TIMER2 *my_TIMER2);
static inline Std_ReturnType TIMER2_Set_POSTscaler(const TIMER2 *my_TIMER2);
#if TIMER2_INTERRUPT_MODE
volatile static Std_ReturnType (*TIMER2_INTERRUPT_HANDLER_CALL_BACK)(void) = NULL;
#endif
static uint8 timer2_preload = 0;
Std_ReturnType TIMER2_init(const TIMER2 *my_TIMER2)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER2)
    {
       RET = E_NOT_OK;
    }
    else
    {
         /*DISABLE Timer2 */
        DISABLE_Timer2();
        /*Set_Prescaler*/
        TIMER2_Set_Prescaler(my_TIMER2);
        /*Set_POSTscaler*/
        TIMER2_Set_POSTscaler(my_TIMER2);
        /* handle preloaded value */
        TMR2 = (uint8)(my_TIMER2->Timer2_preloaded_value);
        /*copy the preloaded value */
        timer2_preload=my_TIMER2->Timer2_preloaded_value;  
        
#if TIMER2_INTERRUPT_MODE
       TIMER2_INTERRUPT_ENABLE();
       TIMER2_INERRUPT_CLEAR_FLAG(); 
       
#if !INTERRUPT_PRIORITY_mode
       INTERRUPT_GLOBAL_ENABLE();
       INTERRUPT_prepheral_ENABLE();
       INTERRUPT_PRIORITY_LEVELS_DISABLE();
       
#endif  
#if INTERRUPT_PRIORITY_mode
   
       INTERRUPT_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE();
       if(my_TIMER2->Timer2_PRIORITY==Timer2_interrupt_priority_high)
       {
           TIMER2_HIGH_PRIORITY_SET();
       }
       else if(my_TIMER0->Timer0_PRIORITY==Timer0_interrupt_priority_low)
       {
           TIMER2_LOW_PRIORITY_SET();
       }
#endif
        TIMER2_INTERRUPT_HANDLER_CALL_BACK=my_TIMER2->TIMER2_INTERRUPT_HANDLER;
#endif
        /*ENABLE Timer */
        Enable_Timer2();
    }
    return RET;
}

Std_ReturnType TIMER2_DEinit(const TIMER2 *my_TIMER2)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER2)
    {
       RET = E_NOT_OK;
    }
    else
    {
        /*DISABLE Timer2 */
        DISABLE_Timer2();
        /*Configure Timer2 interrupt (optional)*/
        #if TIMER2_INTERRUPT_MODE
        TIMER2_INTERRUPT_DISABLE();
        #endif
    }
    return RET;
}

Std_ReturnType TIMER2_WRITE_VALUE(const TIMER2 *my_TIMER2,uint8 value)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER2)
    {
       RET = E_NOT_OK;
    }
    else
    {
        TMR2 = (uint8)(value);
    }
    return RET;
}

Std_ReturnType TIMER2_READ_VALUE(const TIMER2 *my_TIMER2,uint8 *value)
{
    Std_ReturnType RET = E_OK;
    uint8 timer2 = TMR2;
    if(NULL==my_TIMER2 || NULL==value)
    {
       RET = E_NOT_OK;
    }
    else
    {

        *value=(uint8)(timer2);
    }
    return RET;
}

#if TIMER2_INTERRUPT_MODE
Std_ReturnType TIMER2_ISR(void)
{
    /* TIMER2_Interrupts_clear_flag (must be cleared in s/w) */
    TIMER2_INERRUPT_CLEAR_FLAG();
    /* reinitilaize the counter with the preloaded value after every over flow */
    TMR2 = (uint8)(timer2_preload);
    /* call back handling */
    if(TIMER2_INTERRUPT_HANDLER_CALL_BACK)
     {
        TIMER2_INTERRUPT_HANDLER_CALL_BACK();
     }  
}
#endif



static inline Std_ReturnType TIMER2_Set_Prescaler(const TIMER2 *my_TIMER2)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER2)
    {
       RET = E_NOT_OK;
    }
    else
    {
#if PRE_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER2
        
            Timer2_Input_Clock_Prescale_Select(my_TIMER2->PRE_SCALER_VALUE);
#endif
#if !PRE_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER2
        
            Timer2_Input_Clock_Prescale_Select(TIMER2_PRESCALER_DIV_BY_1);
#endif
    }
    return RET;
}

static inline Std_ReturnType TIMER2_Set_POSTscaler(const TIMER2 *my_TIMER2)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER2)
    {
       RET = E_NOT_OK;
    }
    else
    {
#if Post_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER2
        
            Timer2_Input_Clock_Postscale_Select(my_TIMER2->post_SCALER_VALUE);
#endif
#if !Post_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER2
        
            Timer2_Input_Clock_Postscale_Select(TIMER2_PRESCALER_DIV_BY_1);
#endif
    }
    return RET;
}



