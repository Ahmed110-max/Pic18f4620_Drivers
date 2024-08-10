/* 
 * File:   TIMER3.C
 * Author: AHMED AKRAM
 *
 * Created on April 11, 2024, 11:24 AM
 */
#include "TIMER3.h"

static inline Std_ReturnType TIMER3_Set_Prescaler(const TIMER3 *my_TIMER3);
static inline Std_ReturnType TIMER3_Mode_Select(const TIMER3 *my_TIMER3);
static inline Std_ReturnType TIMER3_REGISTER_SIZE_Select(const TIMER3 *my_TIMER3);
static uint16 timer3_preload = 0;
#if TIMER3_INTERRUPT_MODE
volatile static Std_ReturnType (*TIMER3_INTERRUPT_HANDLER_CALL_BACK)(void) = NULL;
#endif

Std_ReturnType TIMER3_init(const TIMER3 *my_TIMER3)
{
     Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER3)
    {
       RET = E_NOT_OK;
    }
    else
    {
        /*DISABLE Timer3 */
        DISABLE_Timer3();
        /*Set_Prescaler*/
        TIMER3_Set_Prescaler(my_TIMER3);
        /*Select Mode*/
        TIMER3_Mode_Select(my_TIMER3);
        /*Select REGISTER_SIZE*/
        TIMER3_REGISTER_SIZE_Select(my_TIMER3);
        /* handle preloaded value */
        TMR3H = (uint8)(my_TIMER3->Timer3_preloaded_value>>8);
        TMR3L = (uint8)(my_TIMER3->Timer3_preloaded_value);
        /*copy the preloaded value */
        timer3_preload=my_TIMER3->Timer3_preloaded_value;
        
#if TIMER3_INTERRUPT_MODE
       TIMER3_INTERRUPT_ENABLE();
       TIMER3_INERRUPT_CLEAR_FLAG(); 
       
#if !INTERRUPT_PRIORITY_mode
       INTERRUPT_GLOBAL_ENABLE();
       INTERRUPT_prepheral_ENABLE();
       INTERRUPT_PRIORITY_LEVELS_DISABLE();
#endif  
       
#if INTERRUPT_PRIORITY_mode
   
       INTERRUPT_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE();
       if(my_TIMER3->Timer3_PRIORITY==Timer3_interrupt_priority_high)
       {
           TIMER3_HIGH_PRIORITY_SET();
       }
       else if(my_TIMER3->Timer3_PRIORITY==Timer3_interrupt_priority_low)
       {
           TIMER3_LOW_PRIORITY_SET();
       }
#endif
        TIMER3_INTERRUPT_HANDLER_CALL_BACK=my_TIMER3->TIMER3_INTERRUPT_HANDLER;
#endif
        /*ENABLE Timer */
        Enable_Timer3();
    }
    return RET;
}
Std_ReturnType TIMER3_DEinit(const TIMER3 *my_TIMER3)
{
     Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER3)
    {
       RET = E_NOT_OK;
    }
    else
    {
        /*DISABLE Timer3 */
        DISABLE_Timer3();
        /*Configure Timer3 interrupt (optional)*/
        #if TIMER3_INTERRUPT_MODE
        TIMER3_INTERRUPT_DISABLE();
        #endif
    }
    return RET;
}
Std_ReturnType TIMER3_WRITE_VALUE(const TIMER3 *my_TIMER3,uint16 value)
{
     Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER3)
    {
       RET = E_NOT_OK;
    }
    else
    {
        TMR3H = (uint8)(value >>8);
        TMR3L = (uint8)(value);
    }
}
Std_ReturnType TIMER3_READ_VALUE(const TIMER3 *my_TIMER3,uint16 *value)
{
    Std_ReturnType RET = E_OK;
        uint8 timer3l = TMR3L;
        uint8 timer3h = TMR3H;
    if(NULL==my_TIMER3 || NULL==value)
    {
       RET = E_NOT_OK;
    }
    else
    {

        *value=(uint16)((timer3h<<8)+timer3l);
    }
    return RET;
}
#if TIMER1_INTERRUPT_MODE
Std_ReturnType TIMER3_ISR(void)
{
    /* TIMER3_Interrupts_clear_flag (must be cleared in s/w) */
    TIMER3_INERRUPT_CLEAR_FLAG();
    /* reinitilaize the counter with the preloaded value after every over flow */
    TMR3H = (uint8)(timer3_preload>>8);
    TMR3L = (uint8)(timer3_preload);
    /* call back handling */
    if(TIMER3_INTERRUPT_HANDLER_CALL_BACK)
     {
        TIMER3_INTERRUPT_HANDLER_CALL_BACK();
        
     }  
}
#endif
         
static inline Std_ReturnType TIMER3_Set_Prescaler(const TIMER3 *my_TIMER3)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER3)
    {
       RET = E_NOT_OK;
    }
    else
    {
#if PRE_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER3
        
            Timer3_Input_Clock_Prescale_Select(my_TIMER3->PRE_SCALER_VALUE);
#endif
#if !PRE_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER3
        
            Timer3_Input_Clock_Prescale_Select(TIMER3_PRESCALER_DIV_BY_1);
#endif
    }
    return RET;
}
static inline Std_ReturnType TIMER3_Mode_Select(const TIMER3 *my_TIMER3)
{
     Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER3)
    {
       RET = E_NOT_OK;
    }
    else
    {
        if(my_TIMER3->Timer3_MODE==Timer_MODE)
        {
            Timer3_TIMER_MODE_ENABLE();
        }
        else if(my_TIMER3->Timer3_MODE==counter_MODE)
        {
            Timer3_COUNTER_MODE_ENABLE();  
        }
}
     
}
static inline Std_ReturnType TIMER3_REGISTER_SIZE_Select(const TIMER3 *my_TIMER3)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER3)
    {
       RET = E_NOT_OK;
    }
    else
    {
        if(my_TIMER3->Timer3_REGISTER_SIZE==TIMER3_RW_REG_8Bit_MODE)
        {
            TIMER3_RW_REG_8BIT_MODE_ENABLE();
        }
        else if(my_TIMER3->Timer3_REGISTER_SIZE==TIMER3_RW_REG_16Bit_MODE)
        {
            TIMER3_RW_REG_16BIT_MODE_ENABLE();
        }
    }
    return RET;
}