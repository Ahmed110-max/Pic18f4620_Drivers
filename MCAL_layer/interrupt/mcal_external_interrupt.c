/* 
 * File:   mcal_external_interrupt.c
 * Author: AHMED AKRAM
 *
 * Created on February 4, 2024, 2:29 AM
 */
#include "mcal_external_interrupt.h"

static Std_ReturnType EXTERNAL_INT0_SET_INTERRUPT_HANDLER(void (* EXTERNAL_INTERRUPT_HANDLER)(void));
static Std_ReturnType EXTERNAL_INT1_SET_INTERRUPT_HANDLER(void (* EXTERNAL_INTERRUPT_HANDLER)(void));
static Std_ReturnType EXTERNAL_INT2_SET_INTERRUPT_HANDLER(void (* EXTERNAL_INTERRUPT_HANDLER)(void));

static Std_ReturnType EXTERNAL_INTX_INTERRUPT_HANDLER(const EXTERNAL_INTX_INTERRUPT *obj);




static Std_ReturnType Intx_Interrupts_Enable(const EXTERNAL_INTX_INTERRUPT *obj);
static Std_ReturnType Intx_Interrupts_Disable(const EXTERNAL_INTX_INTERRUPT *obj);
static Std_ReturnType Intx_Interrupts_activate_priority(const EXTERNAL_INTX_INTERRUPT *obj);
static Std_ReturnType Intx_Interrupts_deactivate_priority(const EXTERNAL_INTX_INTERRUPT *obj);
static Std_ReturnType Intx_Interrupts_Set_Edge(const EXTERNAL_INTX_INTERRUPT *obj);
static Std_ReturnType Intx_Interrupts_Set_Pin(const EXTERNAL_INTX_INTERRUPT *obj);
static Std_ReturnType Intx_Interrupts_clear_flag(const EXTERNAL_INTX_INTERRUPT *obj);



volatile static Std_ReturnType (*INT0_INTERRUPT_HANDLER_CALL_BACK)(void);
volatile static Std_ReturnType (*INT1_INTERRUPT_HANDLER_CALL_BACK)(void);
volatile static Std_ReturnType (*INT2_INTERRUPT_HANDLER_CALL_BACK)(void);

/******************************************************************************/

static Std_ReturnType EXTERNAL_RB4_SET_INTERRUPT_HANDLER_high(void (* EXTERNAL_INTERRUPT_HANDLER)(void));
static Std_ReturnType EXTERNAL_RB4_SET_INTERRUPT_HANDLER_low(void (* EXTERNAL_INTERRUPT_HANDLER)(void));

static Std_ReturnType EXTERNAL_RB5_SET_INTERRUPT_HANDLER_high(void (* EXTERNAL_INTERRUPT_HANDLER)(void));
static Std_ReturnType EXTERNAL_RB5_SET_INTERRUPT_HANDLER_low(void (* EXTERNAL_INTERRUPT_HANDLER)(void));

static Std_ReturnType EXTERNAL_RB6_SET_INTERRUPT_HANDLER_high(void (* EXTERNAL_INTERRUPT_HANDLER)(void));
static Std_ReturnType EXTERNAL_RB6_SET_INTERRUPT_HANDLER_low(void (* EXTERNAL_INTERRUPT_HANDLER)(void));

static Std_ReturnType EXTERNAL_RB7_SET_INTERRUPT_HANDLER_high(void (* EXTERNAL_INTERRUPT_HANDLER)(void));
static Std_ReturnType EXTERNAL_RB7_SET_INTERRUPT_HANDLER_low(void (* EXTERNAL_INTERRUPT_HANDLER)(void));


static Std_ReturnType EXTERNAL_RBX_INTERRUPT_HANDLER(const EXTERNAL_RBX_INTERRUPT *obj);





static Std_ReturnType RBX_Interrupts_Enable(const EXTERNAL_RBX_INTERRUPT *obj);
static Std_ReturnType RBX_Interrupts_Disable(const EXTERNAL_RBX_INTERRUPT *obj);
static Std_ReturnType RBX_Interrupts_activate_priority(const EXTERNAL_RBX_INTERRUPT *obj);
static Std_ReturnType RBX_Interrupts_deactivate_priority(const EXTERNAL_RBX_INTERRUPT *obj);
static Std_ReturnType RBX_Interrupts_Set_Pin(const EXTERNAL_RBX_INTERRUPT *obj);
static Std_ReturnType RBX_Interrupts_clear_flag(const EXTERNAL_RBX_INTERRUPT *obj);



volatile static Std_ReturnType (*RB4_INTERRUPT_HANDLER_CALL_BACK_high)(void);
volatile static Std_ReturnType (*RB4_INTERRUPT_HANDLER_CALL_BACK_low)(void);

volatile static Std_ReturnType (*RB5_INTERRUPT_HANDLER_CALL_BACK_high)(void);
volatile static Std_ReturnType (*RB5_INTERRUPT_HANDLER_CALL_BACK_low)(void);

volatile static Std_ReturnType (*RB6_INTERRUPT_HANDLER_CALL_BACK_high)(void);
volatile static Std_ReturnType (*RB6_INTERRUPT_HANDLER_CALL_BACK_low)(void);

volatile static Std_ReturnType (*RB7_INTERRUPT_HANDLER_CALL_BACK_high)(void);
volatile static Std_ReturnType (*RB7_INTERRUPT_HANDLER_CALL_BACK_low)(void);

Std_ReturnType Activate_Intx_Interrupts(const EXTERNAL_INTX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        /* the next steps is to activate the interrupt */
        /* disable intx */
        Intx_Interrupts_Disable(obj);
        /*clear flag */
        Intx_Interrupts_clear_flag(obj);
        /*configure edge */
        Intx_Interrupts_Set_Edge(obj);
        #if INTERRUPT_PRIORITY_mode
        /*configure priority*/
        Intx_Interrupts_activate_priority(obj);
        #endif
        #if !INTERRUPT_PRIORITY_mode
        /*configure priority*/
        Intx_Interrupts_deactivate_priority(obj);
        #endif
        /*configure pin */
        Intx_Interrupts_Set_Pin(obj);
        /*CONFIGURE CALL BACK */
        EXTERNAL_INTX_INTERRUPT_HANDLER(obj);
        /*enable intx */
        Intx_Interrupts_Enable(obj);

        
    }
    return RET;
}



Std_ReturnType Activate_RBX_Interrupts(const EXTERNAL_RBX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        /* the next steps is to activate the interrupt */
        /* disable RBX */
        RBX_Interrupts_Disable(obj);
        /*clear flag */
        RBX_Interrupts_clear_flag(obj);
        #if INTERRUPT_PRIORITY_mode
        /*configure priority*/
        RBX_Interrupts_activate_priority(obj);
        #endif
        #if !INTERRUPT_PRIORITY_mode
        /*configure priority*/
        RBX_Interrupts_deactivate_priority(obj);
        #endif
        /*configure pin */
        RBX_Interrupts_Set_Pin(obj);
        /*CONFIGURE CALL BACK */
        EXTERNAL_RBX_INTERRUPT_HANDLER(obj);
        /*enable RBX */
        RBX_Interrupts_Enable(obj);
    }
    return RET;
}





Std_ReturnType Dectivate_Intx_Interrupts(const EXTERNAL_INTX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
         Intx_Interrupts_Disable(obj);
    }
    return RET;
}








Std_ReturnType Dectivate_RBX_Interrupts(const EXTERNAL_RBX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        RBX_Interrupts_Disable(obj);
    }
    return RET;
}


static Std_ReturnType Intx_Interrupts_Enable(const EXTERNAL_INTX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        #if INTERRUPT_PRIORITY_mode
        switch((obj->source))
        {
            case Int0 :
              INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE(); 
              EXT_INT0_ENABLE();
                break;
            case Int1 :
                INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE();
                INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE();
                EXT_INT1_ENABLE();
                break;
            case Int2 :
                INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE(); 
                INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE();
                EXT_INT2_ENABLE();  
                break;
            default :
                RET = E_NOT_OK;
        }
        #endif

        #if !INTERRUPT_PRIORITY_mode
        switch((obj->source))
        {
            case Int0 :
              INTERRUPT_GLOBAL_ENABLE();
              EXT_INT0_ENABLE();
                break;
            case Int1 :
                INTERRUPT_GLOBAL_ENABLE();
                EXT_INT1_ENABLE();
                break;
            case Int2 :
                INTERRUPT_GLOBAL_ENABLE();
                EXT_INT2_ENABLE();  
                break;
            default :
                RET = E_NOT_OK;
        }
        #endif
    }
    return RET;
}


static Std_ReturnType RBX_Interrupts_Enable(const EXTERNAL_RBX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        #if INTERRUPT_PRIORITY_mode
        switch((obj->pin.pin))
        {
            case pin4 :
              INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE();
              INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE();
              EXT_RBx_ENABLE();
              RB4_ENABLE();
                break;
            case pin5 :
                INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE();
                INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE();
                EXT_RBx_ENABLE();
                RB5_ENABLE(); 
                break;
            case pin6 :
                INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE(); 
                INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE();
                EXT_RBx_ENABLE();
                RB6_ENABLE();
                break;
            case pin7 :
             INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE(); 
             INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE();
             EXT_RBx_ENABLE();
             RB7_ENABLE();
                break;
            default :
                RET = E_NOT_OK;
        }
        #endif

        #if !INTERRUPT_PRIORITY_mode
        switch((obj->pin.pin))
        {
            case pin4 :
              INTERRUPT_GLOBAL_ENABLE();
              INTERRUPT_prepheral_ENABLE();
              EXT_RBx_ENABLE();
              RB4_ENABLE();
                break;
            case pin5 :
                INTERRUPT_GLOBAL_ENABLE();
                INTERRUPT_prepheral_ENABLE();
                EXT_RBx_ENABLE();
                RB5_ENABLE();
                break;
            case pin6 :
                INTERRUPT_GLOBAL_ENABLE();
                INTERRUPT_prepheral_ENABLE();
                EXT_RBx_ENABLE();
                RB6_ENABLE();  
                break;
            case pin7 :
                INTERRUPT_GLOBAL_ENABLE();
                INTERRUPT_prepheral_ENABLE();
                EXT_RBx_ENABLE();
                RB7_ENABLE();  
                break;    
            default :
                RET = E_NOT_OK;
        }
        #endif
    }
    return RET;
}





 static Std_ReturnType Intx_Interrupts_Disable(const EXTERNAL_INTX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        switch(obj->source)
        {
            case Int0 :
                EXT_INT0_Disables();
                break;
            case Int1 :
                EXT_INT1_Disables();
                break;
            case Int2 :
                EXT_INT2_Disables();  
                break;
            default :
                RET = E_NOT_OK;
        }
    }
    return RET;
}


 
 static Std_ReturnType RBX_Interrupts_Disable(const EXTERNAL_RBX_INTERRUPT *obj)
 {
     Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        EXT_RBx_Disables(); 
    }
    return RET;
 }
 
 
#if INTERRUPT_PRIORITY_mode
static Std_ReturnType Intx_Interrupts_activate_priority(const EXTERNAL_INTX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        switch(obj->source)
        {
            case Int1 :
                if(obj->priority==Ext_interrupt_priority_high)
                {
                    INTERRUPT_PRIORITY_LEVELS_ENABLE();
                    EXT_INT1_HIGH_PRORITY_SET();
                }
                else if(obj->priority==Ext_interrupt_priority_low)
                {
                    INTERRUPT_PRIORITY_LEVELS_ENABLE(); 
                    EXT_INT1_LOW_PRORITY_SET();
                }
                break;
            case Int2 :
                if(obj->priority==Ext_interrupt_priority_high)
                {
                    INTERRUPT_PRIORITY_LEVELS_ENABLE();;
                    EXT_INT2_HIGH_PRORITY_SET();
                }
                else if(obj->priority==Ext_interrupt_priority_low)
                {
                    INTERRUPT_PRIORITY_LEVELS_ENABLE();
                    EXT_INT2_LOW_PRORITY_SET();
                }
                break;
            default :
                RET = E_NOT_OK;
        }
    }
    return RET;
}
#endif


#if INTERRUPT_PRIORITY_mode
static Std_ReturnType RBX_Interrupts_activate_priority(const EXTERNAL_RBX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        if(obj->priority==Ext_interrupt_priority_high)
        {
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            EXT_RBX_HIGH_PRORITY_SET();
        }
        else if(obj->priority==Ext_interrupt_priority_low)
        {
           INTERRUPT_PRIORITY_LEVELS_ENABLE();
           EXT_RBX_LOW_PRORITY_SET();
        }
    }
}
#endif

#if !INTERRUPT_PRIORITY_mode

static Std_ReturnType Intx_Interrupts_deactivate_priority(const EXTERNAL_INTX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        INTERRUPT_PRIORITY_LEVELS_DISABLE();
        switch(obj->source)
        {
            case Int1 :
                INTERRUPT_PRIORITY_int1_DISABLE();
                break;
            case Int2 :
                    INTERRUPT_PRIORITY_int2_DISABLE();
                break;
            default :
                RET = E_NOT_OK;
        }
        
    }
}

#endif

#if !INTERRUPT_PRIORITY_mode
static Std_ReturnType RBX_Interrupts_deactivate_priority(const EXTERNAL_RBX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        INTERRUPT_PRIORITY_LEVELS_DISABLE();
        INTERRUPT_PRIORITY_RBX_DISABLE(); 
    }
}
#endif

static Std_ReturnType Intx_Interrupts_Set_Edge(const EXTERNAL_INTX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        switch(obj->source)
        {
            case Int0 :
                if(obj->Intx_Edge==Rising_Edge)
                {
                    EXT_INT0_ON_RISING_EDGE_SET();
                }
                else if(obj->Intx_Edge==Falling_Edge)
                {
                    EXT_INT0_ON_FALLING_EDGE_SET();
                }
              break;
              
            case Int1 :
                if(obj->Intx_Edge==Rising_Edge)
                {
                    EXT_INT1_ON_RISING_EDGE_SET();
                }
                else if(obj->Intx_Edge==Falling_Edge)
                {
                    EXT_INT1_ON_FALLING_EDGE_SET();
                }
              break;
              
              case Int2 :
                if(obj->Intx_Edge==Rising_Edge)
                {
                    EXT_INT2_ON_RISING_EDGE_SET();
                }
                else if(obj->Intx_Edge==Falling_Edge)
                {
                    EXT_INT2_ON_FALLING_EDGE_SET();
                }
              break;
              
              default :
                RET = E_NOT_OK;
        }
    }
    return RET;
}

static Std_ReturnType Intx_Interrupts_Set_Pin(const EXTERNAL_INTX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        gpio_pin_direction_initialize(&(obj->MCU_pin));
    }
    return RET;
}


static Std_ReturnType RBX_Interrupts_Set_Pin(const EXTERNAL_RBX_INTERRUPT *obj)
{
    
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        gpio_pin_direction_initialize(&(obj->pin));
    }
    return RET;
}

 static Std_ReturnType Intx_Interrupts_clear_flag(const EXTERNAL_INTX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
       switch(obj->source)
        {
            case Int0 :
                EXT_INT0_CLEAR_FLAG();
                break;
            case Int1 :
                EXT_INT1_CLEAR_FLAG();
                break;
            case Int2 :
                EXT_INT2_CLEAR_FLAG();  
                break;
            default :
                RET = E_NOT_OK;
        }
    }
    return RET;
}
 
 
 static Std_ReturnType RBX_Interrupts_clear_flag(const EXTERNAL_RBX_INTERRUPT *obj)
 {
     Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
        EXT_RBx_CLEAR_FLAG();
    }
 }



static Std_ReturnType EXTERNAL_INT0_SET_INTERRUPT_HANDLER(void (* EXTERNAL_INTERRUPT_HANDLER)(void))
{
     Std_ReturnType RET = E_OK;
    if(NULL==EXTERNAL_INTERRUPT_HANDLER)
    {
       RET = E_NOT_OK;
    }
    else
    {
        INT0_INTERRUPT_HANDLER_CALL_BACK=EXTERNAL_INTERRUPT_HANDLER;
    }
      return RET;
}



static Std_ReturnType EXTERNAL_RB4_SET_INTERRUPT_HANDLER_high(void (* EXTERNAL_INTERRUPT_HANDLER)(void))
{
    Std_ReturnType RET = E_OK;
    if(NULL==EXTERNAL_INTERRUPT_HANDLER)
    {
       RET = E_NOT_OK;
    }
    else
    {
        RB4_INTERRUPT_HANDLER_CALL_BACK_high=EXTERNAL_INTERRUPT_HANDLER;
    }
      return RET;
}


static Std_ReturnType EXTERNAL_RB4_SET_INTERRUPT_HANDLER_low(void (* EXTERNAL_INTERRUPT_HANDLER)(void))
{
    Std_ReturnType RET = E_OK;
    if(NULL==EXTERNAL_INTERRUPT_HANDLER)
    {
       RET = E_NOT_OK;
    }
    else
    {
        RB4_INTERRUPT_HANDLER_CALL_BACK_low=EXTERNAL_INTERRUPT_HANDLER;
    }
      return RET;
}




static Std_ReturnType EXTERNAL_INT1_SET_INTERRUPT_HANDLER(void (* EXTERNAL_INTERRUPT_HANDLER)(void))
{
    Std_ReturnType RET = E_OK;
    if(NULL==EXTERNAL_INTERRUPT_HANDLER)
    {
       RET = E_NOT_OK;
    }
    else
    {
        INT1_INTERRUPT_HANDLER_CALL_BACK=EXTERNAL_INTERRUPT_HANDLER;
    }
      return RET;
}

static Std_ReturnType EXTERNAL_RB5_SET_INTERRUPT_HANDLER_high(void (* EXTERNAL_INTERRUPT_HANDLER)(void))
{
    Std_ReturnType RET = E_OK;
    if(NULL==EXTERNAL_INTERRUPT_HANDLER)
    {
       RET = E_NOT_OK;
    }
    else
    {
        RB5_INTERRUPT_HANDLER_CALL_BACK_high=EXTERNAL_INTERRUPT_HANDLER;
    }
      return RET;
}


static Std_ReturnType EXTERNAL_RB5_SET_INTERRUPT_HANDLER_low(void (* EXTERNAL_INTERRUPT_HANDLER)(void))
{
    Std_ReturnType RET = E_OK;
    if(NULL==EXTERNAL_INTERRUPT_HANDLER)
    {
       RET = E_NOT_OK;
    }
    else
    {
        RB5_INTERRUPT_HANDLER_CALL_BACK_low=EXTERNAL_INTERRUPT_HANDLER;
    }
      return RET;
}


static Std_ReturnType EXTERNAL_INT2_SET_INTERRUPT_HANDLER(void (* EXTERNAL_INTERRUPT_HANDLER)(void))
{
    Std_ReturnType RET = E_OK;
    if(NULL==EXTERNAL_INTERRUPT_HANDLER)
    {
       RET = E_NOT_OK;
    }
    else
    {
        INT2_INTERRUPT_HANDLER_CALL_BACK=EXTERNAL_INTERRUPT_HANDLER;
    }
      return RET;
}

static Std_ReturnType EXTERNAL_RB6_SET_INTERRUPT_HANDLER_high(void (* EXTERNAL_INTERRUPT_HANDLER)(void))
{
    Std_ReturnType RET = E_OK;
    if(NULL==EXTERNAL_INTERRUPT_HANDLER)
    {
       RET = E_NOT_OK;
    }
    else
    {
        RB6_INTERRUPT_HANDLER_CALL_BACK_high=EXTERNAL_INTERRUPT_HANDLER;
    }
      return RET;
}


static Std_ReturnType EXTERNAL_RB6_SET_INTERRUPT_HANDLER_low(void (* EXTERNAL_INTERRUPT_HANDLER)(void))
{
    Std_ReturnType RET = E_OK;
    if(NULL==EXTERNAL_INTERRUPT_HANDLER)
    {
       RET = E_NOT_OK;
    }
    else
    {
        RB6_INTERRUPT_HANDLER_CALL_BACK_low=EXTERNAL_INTERRUPT_HANDLER;
    }
      return RET;
}

static Std_ReturnType EXTERNAL_RB7_SET_INTERRUPT_HANDLER_high(void (* EXTERNAL_INTERRUPT_HANDLER)(void))
{
    Std_ReturnType RET = E_OK;
    if(NULL==EXTERNAL_INTERRUPT_HANDLER)
    {
       RET = E_NOT_OK;
    }
    else
    {
        RB7_INTERRUPT_HANDLER_CALL_BACK_high=EXTERNAL_INTERRUPT_HANDLER;
    }
      return RET;
}


static Std_ReturnType EXTERNAL_RB7_SET_INTERRUPT_HANDLER_low(void (* EXTERNAL_INTERRUPT_HANDLER)(void))
{
    Std_ReturnType RET = E_OK;
    if(NULL==EXTERNAL_INTERRUPT_HANDLER)
    {
       RET = E_NOT_OK;
    }
    else
    {
        RB7_INTERRUPT_HANDLER_CALL_BACK_low=EXTERNAL_INTERRUPT_HANDLER;
    }
      return RET;
}


static Std_ReturnType EXTERNAL_INTX_INTERRUPT_HANDLER(const EXTERNAL_INTX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
       switch(obj->source)
        {
            case Int0 :
                EXTERNAL_INT0_SET_INTERRUPT_HANDLER(obj->EXTERNAL_INTX_callback);
                break;
            case Int1 :
                EXTERNAL_INT1_SET_INTERRUPT_HANDLER(obj->EXTERNAL_INTX_callback);
                break;
            case Int2 :
                EXTERNAL_INT2_SET_INTERRUPT_HANDLER(obj->EXTERNAL_INTX_callback);  
                break;
            default :
                RET = E_NOT_OK;
        }
    }
    return RET;
}


static Std_ReturnType EXTERNAL_RBX_INTERRUPT_HANDLER(const EXTERNAL_RBX_INTERRUPT *obj)
{
    Std_ReturnType RET = E_OK;
    if(NULL==obj)
    {
       RET = E_NOT_OK;
    }
    else
    {
       switch(obj->pin.pin)
        {
            case pin4 :
                EXTERNAL_RB4_SET_INTERRUPT_HANDLER_high(obj->EXTERNAL_RBX_callback_high);
                EXTERNAL_RB4_SET_INTERRUPT_HANDLER_low(obj->EXTERNAL_RBX_callback_low);
                break;
            case pin5 :
                EXTERNAL_RB5_SET_INTERRUPT_HANDLER_high(obj->EXTERNAL_RBX_callback_high);
                EXTERNAL_RB5_SET_INTERRUPT_HANDLER_low(obj->EXTERNAL_RBX_callback_low);
                break;
            case pin6 :
                EXTERNAL_RB6_SET_INTERRUPT_HANDLER_high(obj->EXTERNAL_RBX_callback_high);
                EXTERNAL_RB6_SET_INTERRUPT_HANDLER_low(obj->EXTERNAL_RBX_callback_low);  
                break;
            case pin7 :
                EXTERNAL_RB7_SET_INTERRUPT_HANDLER_high(obj->EXTERNAL_RBX_callback_high);
                EXTERNAL_RB7_SET_INTERRUPT_HANDLER_low(obj->EXTERNAL_RBX_callback_low);  
                break;    
            default :
                RET = E_NOT_OK;
        }
    }
    return RET;
}


Std_ReturnType INT0_ISR(void)
{
     /* Int0_Interrupts_clear_flag (must be cleared in s/w) */
     EXT_INT0_CLEAR_FLAG(); 
     /* write your code here */

     /* call back handling */
     if(INT0_INTERRUPT_HANDLER_CALL_BACK)
     {
         INT0_INTERRUPT_HANDLER_CALL_BACK();
     }
}
Std_ReturnType INT1_ISR(void)
{
    /* Int0_Interrupts_clear_flag (must be cleared in s/w) */
    EXT_INT1_CLEAR_FLAG();
    /* write your code here */
    
    /* call back handling */
    if(INT1_INTERRUPT_HANDLER_CALL_BACK)
     {
         INT1_INTERRUPT_HANDLER_CALL_BACK();
     }
}
Std_ReturnType INT2_ISR(void)
{
    /* Int0_Interrupts_clear_flag (must be cleared in s/w) */
    EXT_INT2_CLEAR_FLAG();
    /* write your code here */
    
    /* call back handling */
    if(INT2_INTERRUPT_HANDLER_CALL_BACK)
     {
         INT2_INTERRUPT_HANDLER_CALL_BACK();
     }
}



Std_ReturnType RB4_ISR_high(void)
{
    /* A mismatch condition will continue to set the RBIF bit. Reading PORTB will end the 
       mismatch condition and allow the bit to be cleared
     */
    volatile uint8 dummy = PORTB ;
     /* Int0_Interrupts_clear_flag (must be cleared in s/w) */
     EXT_RBx_CLEAR_FLAG();  
     /* write your code here */

     /* call back handling */
     if(RB4_INTERRUPT_HANDLER_CALL_BACK_high)
     {
         RB4_INTERRUPT_HANDLER_CALL_BACK_high();
     }
}



Std_ReturnType RB4_ISR_low(void)
{
    /* A mismatch condition will continue to set the RBIF bit. Reading PORTB will end the 
       mismatch condition and allow the bit to be cleared
     */
    volatile uint8 dummy = PORTB ;
     /* Int0_Interrupts_clear_flag (must be cleared in s/w) */
     EXT_RBx_CLEAR_FLAG();  
     /* write your code here */

     /* call back handling */
     if(RB4_INTERRUPT_HANDLER_CALL_BACK_low)
     {
         RB4_INTERRUPT_HANDLER_CALL_BACK_low();
     }
}



Std_ReturnType RB5_ISR_high(void)
{
    /* A mismatch condition will continue to set the RBIF bit. Reading PORTB will end the 
       mismatch condition and allow the bit to be cleared
     */
    volatile uint8 dummy = PORTB ;
     /* Int0_Interrupts_clear_flag (must be cleared in s/w) */
     EXT_RBx_CLEAR_FLAG();  
     /* write your code here */

     /* call back handling */
     if(RB5_INTERRUPT_HANDLER_CALL_BACK_high)
     {
         RB5_INTERRUPT_HANDLER_CALL_BACK_high();
     }
}


Std_ReturnType RB5_ISR_low(void)
{
    /* A mismatch condition will continue to set the RBIF bit. Reading PORTB will end the 
       mismatch condition and allow the bit to be cleared
     */
    volatile uint8 dummy = PORTB ;
     /* Int0_Interrupts_clear_flag (must be cleared in s/w) */
     EXT_RBx_CLEAR_FLAG();  
     /* write your code here */

     /* call back handling */
     if(RB5_INTERRUPT_HANDLER_CALL_BACK_low)
     {
         RB5_INTERRUPT_HANDLER_CALL_BACK_low();
     }
}



Std_ReturnType RB6_ISR_high(void)
{
    /* A mismatch condition will continue to set the RBIF bit. Reading PORTB will end the 
       mismatch condition and allow the bit to be cleared
     */
    volatile uint8 dummy = PORTB ;
     /* Int0_Interrupts_clear_flag (must be cleared in s/w) */
     EXT_RBx_CLEAR_FLAG();  
     /* write your code here */

     /* call back handling */
     if(RB6_INTERRUPT_HANDLER_CALL_BACK_high)
     {
         RB6_INTERRUPT_HANDLER_CALL_BACK_high();
     }
}


Std_ReturnType RB6_ISR_low(void)
{
    /* A mismatch condition will continue to set the RBIF bit. Reading PORTB will end the 
       mismatch condition and allow the bit to be cleared
     */
    volatile uint8 dummy = PORTB ;
     /* Int0_Interrupts_clear_flag (must be cleared in s/w) */
     EXT_RBx_CLEAR_FLAG();  
     /* write your code here */

     /* call back handling */
     if(RB6_INTERRUPT_HANDLER_CALL_BACK_low)
     {
         RB6_INTERRUPT_HANDLER_CALL_BACK_low();
     }
}




Std_ReturnType RB7_ISR_high(void)
{
    /* A mismatch condition will continue to set the RBIF bit. Reading PORTB will end the 
       mismatch condition and allow the bit to be cleared
     */
    volatile uint8 dummy = PORTB ;
     /* Int0_Interrupts_clear_flag (must be cleared in s/w) */
     EXT_RBx_CLEAR_FLAG();  
     /* write your code here */

     /* call back handling */
     if(RB7_INTERRUPT_HANDLER_CALL_BACK_high)
     {
         RB7_INTERRUPT_HANDLER_CALL_BACK_high();
     }
}


Std_ReturnType RB7_ISR_low(void)
{
    /* A mismatch condition will continue to set the RBIF bit. Reading PORTB will end the 
       mismatch condition and allow the bit to be cleared
     */
    volatile uint8 dummy = PORTB ;
     /* Int0_Interrupts_clear_flag (must be cleared in s/w) */
     EXT_RBx_CLEAR_FLAG();  
     /* write your code here */

     /* call back handling */
     if(RB7_INTERRUPT_HANDLER_CALL_BACK_low)
     {
         RB7_INTERRUPT_HANDLER_CALL_BACK_low();
     }
}


