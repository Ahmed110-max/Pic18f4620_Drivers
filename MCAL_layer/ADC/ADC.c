/* 
 * File:   ADC.C
 * Author: AHMED AKRAM
 *
 * Created on February 16, 2024, 2:35 PM
 */
#include "ADC.h"
static inline Std_ReturnType Adc_Set_Analog_Pin(Adc_channel MY_CHANNEL);
static inline Std_ReturnType Adc_Set_Result_Format(const ADC *my_ADC);
static inline Std_ReturnType Adc_Set_VREF(const ADC *my_ADC);
#if ADC_INTERRUPT_MODE
volatile static Std_ReturnType (*ADC_INTERRUPT_HANDLER_CALL_BACK)(void) = NULL;
#endif
Std_ReturnType Adc_init(const ADC *my_ADC)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_ADC)
    {
       RET = E_NOT_OK;
    }
    else
    {
            /*DISABLE ADC */
        Adc_Disable();
       /*Select acquisition delay*/
       ADCON2bits.ACQT = my_ADC->acquisition_time; 
       /* Select ADC conversion clock*/
       ADCON2bits.ADCS = my_ADC->conversion_clock;
       /*Select ADC input channel*/
       ADCON0bits.CHS = my_ADC->acquisition_time;
       /*Configure Port:
        . Disable pin output driver (TRIS register)
        . Configure pin as analog*/
       Adc_Set_Analog_Pin(my_ADC->adc_channel);
       /*Configure voltage reference*/
       Adc_Set_VREF(my_ADC);
       /*Configure ADC interrupt (optional)*/
#if ADC_INTERRUPT_MODE
       ADC_INTERRUPT_ENABLE();
       ADC_INERRUPT_CLEAR_FLAG();
 #if !INTERRUPT_PRIORITY_mode
       INTERRUPT_GLOBAL_ENABLE();
       INTERRUPT_prepheral_ENABLE();
       INTERRUPT_PRIORITY_LEVELS_DISABLE();
#endif  
#if INTERRUPT_PRIORITY_mode
       INTERRUPT_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE();
       if(my_ADC->ADC_PRIORITY==ADC_interrupt_priority_high)
       {
           ADC_HIGH_PRIORITY_SET();
       }
       else if(my_ADC->ADC_PRIORITY==ADC_interrupt_priority_low)
       {
           ADC_LOW_PRIORITY_SET();
       }
#endif
       ADC_INTERRUPT_HANDLER_CALL_BACK = my_ADC->ADC_INTERRUPT_HANDLER;
#endif
       /*  Set Result Format*/
       Adc_Set_Result_Format(my_ADC);
        /*ENABLE ADC */
        Adc_Enable();
    }
    return RET;
}



Std_ReturnType Adc_DEinit(const ADC *my_ADC)
{
     Std_ReturnType RET = E_OK;
    if(NULL==my_ADC)
    {
       RET = E_NOT_OK;
    }
    else
    {
        /*DISABLE ADC */
        Adc_Disable();
        /*Configure ADC interrupt (optional)*/
        #if ADC_INTERRUPT_MODE
        ADC_INTERRUPT_DISABLE();
        #endif
    }
    return RET;
}



Std_ReturnType Adc_change_default_Channel(const ADC *my_ADC,Adc_channel MY_CHANNEL)
{
     Std_ReturnType RET = E_OK;
    if(NULL==my_ADC)
    {
       RET = E_NOT_OK;
    }
    else
    {
        /*Select ADC input channel*/
       ADCON0bits.CHS = MY_CHANNEL;
       /*Configure Port:
        . Disable pin output driver (TRIS register)
        . Configure pin as analog*/
       Adc_Set_Analog_Pin(MY_CHANNEL);
    }
    return RET;
    
}





Std_ReturnType Adc_START_CONVERSION(const ADC *my_ADC)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_ADC)
    {
       RET = E_NOT_OK;
    }
    else
    {
        Adc_start_conversion();
    }
    return RET;
}




Std_ReturnType Adc_CONVERSION_STATUS(const ADC *my_ADC,uint8 *status)
{
     Std_ReturnType RET = E_OK;
    if((NULL==my_ADC)||(NULL==status))
    {
       RET = E_NOT_OK;
    }
    else
    {
        *status = !Adc_conversion_status(); 
    }
    return RET;
}





Std_ReturnType Adc_get_CONVERSION_result(const ADC *my_ADC,uint16 *result)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_ADC)
    {
       RET = E_NOT_OK;
    }
    else
    {
        switch(my_ADC->result_format)
        {
            case ADC_RESULT_RIGHT :
                *result = (uint16)(ADRESL + (ADRESH<<8));
                break;
            case ADC_RESULT_LEFT :
                *result = (uint16)((ADRESL>>6) + (ADRESH<<2));
                break;    
            default :
                RET = E_NOT_OK;
        }
    }
}




Std_ReturnType Adc_get_CONVERSION_Looping(const ADC *my_ADC,uint16 *result,Adc_channel MY_CHANNEL)
{
    Std_ReturnType RET = E_OK;
    if((NULL==my_ADC)||(NULL==result))
    {
       RET = E_NOT_OK;
    }
    else
    {
        Adc_change_default_Channel(my_ADC,MY_CHANNEL);
        /* start conversion */
        Adc_START_CONVERSION(my_ADC);
        /*check if conversion is completed :
         * while(Adc_conversion_status()) : wait till conversion is completed ( looping ) */
        while(Adc_conversion_status()); 
        /* get result  */
        Adc_get_CONVERSION_result(my_ADC,result);
    }
    return RET;
}



Std_ReturnType Adc_START_CONVERSION_interrupt(const ADC *my_ADC,Adc_channel MY_CHANNEL)
{
    Std_ReturnType RET = E_OK;
    if((NULL==my_ADC))
    {
       RET = E_NOT_OK;
    }
    else
    {
        Adc_change_default_Channel(my_ADC,MY_CHANNEL);
        /* start conversion */
        Adc_START_CONVERSION(my_ADC);

    }
    return RET;
}


static inline Std_ReturnType Adc_Set_Analog_Pin(Adc_channel MY_CHANNEL)
{
    Std_ReturnType RET = E_OK;
        switch(MY_CHANNEL)
        {
            case Adc_channel_AN0 :
                SET_BIT(TRISA,_TRISA_TRISA0_POSN);
                SET_BIT(ANSEL,_ANSEL_ANS0_POSN);
                break;
            case Adc_channel_AN1 :
                SET_BIT(TRISA,_TRISA_TRISA1_POSN);
                SET_BIT(ANSEL,_ANSEL_ANS1_POSN);
                break; 
            case Adc_channel_AN2:
                SET_BIT(TRISA,_TRISA_TRISA2_POSN);
                SET_BIT(ANSEL,_ANSEL_ANS2_POSN);
                break;
            case Adc_channel_AN3 :
               SET_BIT(TRISA,_TRISA_TRISA3_POSN);
               SET_BIT(ANSEL,_ANSEL_ANS3_POSN);
                break;    
            case Adc_channel_AN4 :
                SET_BIT(TRISA,_TRISA_RA5_POSN);
                SET_BIT(ANSEL,_ANSEL_ANS4_POSN);
                break;    
            case Adc_channel_AN5 :
                SET_BIT(TRISE,_TRISE_TRISE0_POSN);
                SET_BIT(ANSEL,_ANSEL_ANS5_POSN);
                break;    
            case Adc_channel_AN6 :
                SET_BIT(TRISE,_TRISE_TRISE1_POSN);
                SET_BIT(ANSEL,_ANSEL_ANS6_POSN);
                break;
            case Adc_channel_AN7 :
                SET_BIT(TRISE,_TRISE_TRISE2_POSN);
                SET_BIT(ANSEL,_ANSEL_ANS0_POSN);
                break;    
            case Adc_channel_AN8 :
                SET_BIT(TRISB,_TRISB_RB2_POSN);
                SET_BIT(ANSELH,_ANSELH_ANS8_POSN);
                break;    
            case Adc_channel_AN9 :
                SET_BIT(TRISB,_TRISB_RB3_POSN);
                SET_BIT(ANSELH,_ANSELH_ANS9_POSN);
                break;    
            case Adc_channel_AN10 :
                SET_BIT(TRISB,_TRISB_RB1_POSN);
                SET_BIT(ANSELH,_ANSELH_ANS10_POSN);
                break;    
            case Adc_channel_AN11 :
                SET_BIT(TRISB,_TRISB_RB4_POSN);
                SET_BIT(ANSELH,_ANSELH_ANS11_POSN);
                break;    
            case Adc_channel_AN12 :
                SET_BIT(TRISB,_TRISB_RB0_POSN);
                SET_BIT(ANSELH,_ANSELH_ANS12_POSN);
                break;    
            default :
                RET = E_NOT_OK;       
        }
            return RET;
    }





static inline Std_ReturnType Adc_Set_Result_Format(const ADC *my_ADC)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_ADC)
    {
       RET = E_NOT_OK;
    }
    else
    {
        switch(my_ADC->result_format)
        {
            case ADC_RESULT_RIGHT :
                ADC_Right_justified();
                break;
            case ADC_RESULT_LEFT :
                ADC_LEFT_justified();
                break;    
            default :
                RET = E_NOT_OK;
        }
    }
    return RET;
}



static inline Std_ReturnType Adc_Set_VREF(const ADC *my_ADC)
{
    Std_ReturnType RET = E_OK;
    if(NULL==my_ADC)
    {
       RET = E_NOT_OK;
    }
    else
    {
        if(my_ADC->voltage_reference == Adc_Internal_Vlotage_Ref )
       {
           Adc_Enable_Internal_Vlotage_Ref();
       }
       else if (my_ADC->voltage_reference == Adc_EXTERNAL_Vlotage_Ref)
       {
           Adc_Enable_EXTERNAL_Vlotage_Ref();
       }
       else
       {
           RET = E_NOT_OK;
       }
    }
    return RET;
}

#if ADC_INTERRUPT_MODE
Std_ReturnType ADC_ISR(void)
{
    /* ADC_Interrupts_clear_flag (must be cleared in s/w) */
    ADC_INERRUPT_CLEAR_FLAG();
     /* write your code here */
    
    
    /* call back handling */
    if(ADC_INTERRUPT_HANDLER_CALL_BACK)
     {
        ADC_INTERRUPT_HANDLER_CALL_BACK();
     }  
}
#endif