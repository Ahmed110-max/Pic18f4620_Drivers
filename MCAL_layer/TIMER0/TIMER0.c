/* 
 * File:   TIMER0.C
 * Author: AHMED AKRAM
 * Created on March 1, 2024, 9:49 AM
 */
#include "TIMER0.h"
static inline Std_ReturnType TIMER0_Set_Prescaler(const TIMER0 *my_TIMER0);
static inline Std_ReturnType TIMER0_Mode_Select(const TIMER0 *my_TIMER0);
static inline Std_ReturnType TIMER0_REGISTER_SIZE_Select(const TIMER0 *my_TIMER0);

static uint16 timer0_preload = 0;
#if TIMER0_INTERRUPT_MODE
volatile static Std_ReturnType (*TIMER0_INTERRUPT_HANDLER_CALL_BACK)(void) = NULL;
#endif

Std_ReturnType TIMER0_init(const TIMER0 *my_TIMER0)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER0)
    {
       RET = E_NOT_OK;
    }
    else
    {
        /*DISABLE Timer0 */
        DISABLE_Timer0();
        /*Set_Prescaler*/
        TIMER0_Set_Prescaler(my_TIMER0);
        /*Select Mode*/
        TIMER0_Mode_Select(my_TIMER0);
        /*Select REGISTER_SIZE*/
        TIMER0_REGISTER_SIZE_Select(my_TIMER0);
        /* handle preloaded value */
        TMR0H = (uint8)(my_TIMER0->Timer0_preloaded_value>>8);
        TMR0L = (uint8)(my_TIMER0->Timer0_preloaded_value);
        /*copy the preloaded value */
        timer0_preload=my_TIMER0->Timer0_preloaded_value;
        
#if TIMER0_INTERRUPT_MODE
       TIMER0_INTERRUPT_ENABLE();
       TIMER0_INERRUPT_CLEAR_FLAG(); 

#if !INTERRUPT_PRIORITY_mode
       INTERRUPT_GLOBAL_ENABLE();
       INTERRUPT_prepheral_ENABLE();
       INTERRUPT_PRIORITY_LEVELS_DISABLE();
#endif       

#if INTERRUPT_PRIORITY_mode
   
       INTERRUPT_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE();
       if(my_TIMER0->Timer0_PRIORITY==Timer0_interrupt_priority_high)
       {
           TIMER0_HIGH_PRIORITY_SET();
       }
       else if(my_TIMER0->Timer0_PRIORITY==Timer0_interrupt_priority_low)
       {
           TIMER0_LOW_PRIORITY_SET();
       }
#endif
         TIMER0_INTERRUPT_HANDLER_CALL_BACK=my_TIMER0->TIMER0_INTERRUPT_HANDLER;
#endif
        
        /*ENABLE Timer0 */
        Enable_Timer0();
    }
    return RET;
}
Std_ReturnType TIMER0_DEinit(const TIMER0 *my_TIMER0)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER0)
    {
       RET = E_NOT_OK;
    }
    else
    {
        /*DISABLE Timer0 */
        DISABLE_Timer0();
        /*Configure Timer0 interrupt (optional)*/
        #if TIMER0_INTERRUPT_MODE
        TIMER0_INTERRUPT_DISABLE();
        #endif
    }
    return RET;
}
Std_ReturnType TIMER0_WRITE_VALUE(const TIMER0 *my_TIMER0,uint16 value)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER0)
    {
       RET = E_NOT_OK;
    }
    else
    {
        TMR0H = (uint8)(value>>8);
        TMR0L = (uint8)(value);
    }
    return RET;
}
Std_ReturnType TIMER0_READ_VALUE(const TIMER0 *my_TIMER0,uint16 *value)
{
    Std_ReturnType RET = E_OK;
        uint8 timer0l = TMR0L;
        uint8 timer0h = TMR0H;
    if(NULL==my_TIMER0 || NULL==value)
    {
       RET = E_NOT_OK;
    }
    else
    {

        *value=(uint16)((timer0h<<8)+timer0l);
    }
    return RET;
}


static inline Std_ReturnType TIMER0_Set_Prescaler(const TIMER0 *my_TIMER0)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER0)
    {
       RET = E_NOT_OK;
    }
    else
    {
#if PRE_SCALER_ACTIVATION_DEACTIVATION_CFG
        
            PRE_SCALER_ENABLE();
            T0CONbits.T0PS = my_TIMER0->PRE_SCALER_VALUE;
#endif
#if !PRE_SCALER_ACTIVATION_DEACTIVATION_CFG
        
            PRE_SCALER_DISABLE();
#endif
    }
    return RET;
}

static inline Std_ReturnType TIMER0_Mode_Select(const TIMER0 *my_TIMER0)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER0)
    {
       RET = E_NOT_OK;
    }
    else
    {
        if(my_TIMER0->Timer0_MODE==Timer_MODE)
        {
            Timer0_TIMER_MODE_ENABLE();
        }
        else if(my_TIMER0->Timer0_MODE==counter_MODE)
        {
            Timer0_COUNTER_MODE_ENABLE();
            if(my_TIMER0->Timer0_counter_Edge==TIMER0_COUNTER_RISING_EDGE_CFG)
            {
                Timer0_Source_Edge_RISING_EDGE();
            }
            else if(my_TIMER0->Timer0_counter_Edge==TIMER0_COUNTER_FALLING_EDGE_CFG)
            {
                Timer0_Source_Edge_FALING_EDGE();
            }   
        }
    }
    return RET;
}


static inline Std_ReturnType TIMER0_REGISTER_SIZE_Select(const TIMER0 *my_TIMER0)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER0)
    {
       RET = E_NOT_OK;
    }
    else
    {
        if(my_TIMER0->Timer0_REGISTER_SIZE==Timer0_8_bit_MODE)
        {
            Timer0_8_bit();
        }
        else if(my_TIMER0->Timer0_REGISTER_SIZE==Timer0_16_bit_MODE)
        {
            Timer0_16_bit();
        }
    }
    return RET;
}



#if TIMER0_INTERRUPT_MODE
Std_ReturnType TIMER0_ISR(void)
{
    /* TIMER0_Interrupts_clear_flag (must be cleared in s/w) */
    TIMER0_INERRUPT_CLEAR_FLAG();
    /* reinitilaize the counter with the preloaded value after every over flow */
    TMR0H = (uint8)(timer0_preload>>8);
    TMR0L = (uint8)(timer0_preload);
    /* call back handling */
    if(TIMER0_INTERRUPT_HANDLER_CALL_BACK)
     {
        TIMER0_INTERRUPT_HANDLER_CALL_BACK();
        
     }  
}
#endif
