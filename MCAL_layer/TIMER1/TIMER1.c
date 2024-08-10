/* 
 * File:   TIMER1.h
 * Author: AHMED AKRAM
 *
 * Created on March 16, 2024, 10:40 PM
 */
#include"TIMER1.h"
static inline Std_ReturnType TIMER1_Set_Prescaler(const TIMER1 *my_TIMER1);
static inline Std_ReturnType TIMER1_Mode_Select(const TIMER1 *my_TIMER1);
static inline Std_ReturnType TIMER1_REGISTER_SIZE_Select(const TIMER1 *my_TIMER1);
static uint16 timer1_preload = 0;
#if TIMER1_INTERRUPT_MODE
volatile static Std_ReturnType (*TIMER1_INTERRUPT_HANDLER_CALL_BACK)(void) = NULL;
#endif

Std_ReturnType TIMER1_init(const TIMER1 *my_TIMER1)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER1)
    {
       RET = E_NOT_OK;
    }
    else
    {
        /*DISABLE Timer1 */
        DISABLE_Timer1();
        /*Set_Prescaler*/
        TIMER1_Set_Prescaler(my_TIMER1);
        /*Select Mode*/
        TIMER1_Mode_Select(my_TIMER1);
        /*Select REGISTER_SIZE*/
        TIMER1_REGISTER_SIZE_Select(my_TIMER1);
        /* handle preloaded value */
        TMR1H = (uint8)(my_TIMER1->Timer1_preloaded_value>>8);
        TMR1L = (uint8)(my_TIMER1->Timer1_preloaded_value);
        /*copy the preloaded value */
        timer1_preload=my_TIMER1->Timer1_preloaded_value;
        
#if TIMER1_INTERRUPT_MODE
       TIMER1_INTERRUPT_ENABLE();
       TIMER1_INERRUPT_CLEAR_FLAG(); 
       
#if !INTERRUPT_PRIORITY_mode
       INTERRUPT_GLOBAL_ENABLE();
       INTERRUPT_prepheral_ENABLE();
       INTERRUPT_PRIORITY_LEVELS_DISABLE();
#endif  
       
#if INTERRUPT_PRIORITY_mode
   
       INTERRUPT_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE();
       if(my_TIMER1->Timer1_PRIORITY==Timer1_interrupt_priority_high)
       {
           TIMER1_HIGH_PRIORITY_SET();
       }
       else if(my_TIMER1->Timer1_PRIORITY==Timer1_interrupt_priority_low)
       {
           TIMER1_LOW_PRIORITY_SET();
       }
#endif
        TIMER1_INTERRUPT_HANDLER_CALL_BACK=my_TIMER1->TIMER1_INTERRUPT_HANDLER;
#endif
        /*ENABLE Timer */
        Enable_Timer1();
    }
    return RET;
}



Std_ReturnType TIMER1_DEinit(const TIMER1 *my_TIMER1)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER1)
    {
       RET = E_NOT_OK;
    }
    else
    {
        /*DISABLE Timer1 */
        DISABLE_Timer1();
        /*Configure Timer1 interrupt (optional)*/
        #if TIMER1_INTERRUPT_MODE
        TIMER1_INTERRUPT_DISABLE();
        #endif
    }
    return RET;
}




Std_ReturnType TIMER1_WRITE_VALUE(const TIMER1 *my_TIMER1,uint16 value)
{
     Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER1)
    {
       RET = E_NOT_OK;
    }
    else
    {
        TMR1H = (uint8)(value >>8);
        TMR1L = (uint8)(value);
    }
}



Std_ReturnType TIMER1_READ_VALUE(const TIMER1 *my_TIMER1,uint16 *value)
{
   
   Std_ReturnType RET = E_OK;
        uint8 timer1l = TMR1L;
        uint8 timer1h = TMR1H;
    if(NULL==my_TIMER1 || NULL==value)
    {
       RET = E_NOT_OK;
    }
    else
    {

        *value=(uint16)((timer1h<<8)+timer1l);
    }
    return RET;
}



#if TIMER1_INTERRUPT_MODE
Std_ReturnType TIMER1_ISR(void)
{
    /* TIMER1_Interrupts_clear_flag (must be cleared in s/w) */
    TIMER1_INERRUPT_CLEAR_FLAG();
    /* reinitilaize the counter with the preloaded value after every over flow */
    TMR1H = (uint8)(timer1_preload>>8);
    TMR1L = (uint8)(timer1_preload);
    /* call back handling */
    if(TIMER1_INTERRUPT_HANDLER_CALL_BACK)
     {
        TIMER1_INTERRUPT_HANDLER_CALL_BACK();
        
     }  
}
#endif



static inline Std_ReturnType TIMER1_Set_Prescaler(const TIMER1 *my_TIMER1)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER1)
    {
       RET = E_NOT_OK;
    }
    else
    {
#if PRE_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER1
        
            Timer1_Input_Clock_Prescale_Select(my_TIMER1->PRE_SCALER_VALUE);
#endif
#if !PRE_SCALER_ACTIVATION_DEACTIVATION_CFG_TIMER1
        
            Timer1_Input_Clock_Prescale_Select(TIMER1_PRESCALER_DIV_BY_1);
#endif
    }
    return RET;
}


static inline Std_ReturnType TIMER1_Mode_Select(const TIMER1 *my_TIMER1)
{
     Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER1)
    {
       RET = E_NOT_OK;
    }
    else
    {
        if(my_TIMER1->Timer1_MODE==Timer_MODE)
        {
            Timer1_TIMER_MODE_ENABLE();
        }
        else if(my_TIMER1->Timer1_MODE==counter_MODE)
        {
            Timer1_COUNTER_MODE_ENABLE();  
        }
}
     
}


static inline Std_ReturnType TIMER1_REGISTER_SIZE_Select(const TIMER1 *my_TIMER1)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_TIMER1)
    {
       RET = E_NOT_OK;
    }
    else
    {
        if(my_TIMER1->Timer1_REGISTER_SIZE==TIMER1_RW_REG_8Bit_MODE)
        {
            TIMER1_RW_REG_8BIT_MODE_ENABLE();
        }
        else if(my_TIMER1->Timer1_REGISTER_SIZE==TIMER1_RW_REG_16Bit_MODE)
        {
            TIMER1_RW_REG_16BIT_MODE_ENABLE();
        }
    }
    return RET;
}