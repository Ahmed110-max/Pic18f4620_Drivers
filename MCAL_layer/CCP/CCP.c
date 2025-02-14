/* 
 * File:   CCP.C
 * Author: AHMED AKRAM
 *
 * Created on April 12, 2024, 5:17 PM
 */
#include "CCP.h"

#if CCP1_INTERRUPT_MODE_ENABLE
    static void (*CCP1_InterruptHandler)(void) = NULL;
#endif
    
#if CCP2_INTERRUPT_MODE_ENABLE
    static void (*CCP2_InterruptHandler)(void) = NULL;
#endif
    
static void CCP_Interrupt_Config(const CCP *_ccp_obj);
static void CCP_PWM_Mode_Config(const CCP *_ccp_obj);
static void CCP_Mode_Timer_Select(const CCP *_ccp_obj);
static Std_ReturnType CCP_Capture_Mode_Config(const CCP *_ccp_obj);
static Std_ReturnType CCP_Compare_Mode_Config(const CCP *_ccp_obj);
Std_ReturnType CCP_Init(const CCP *_ccp_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else
    {
        /* CCP Module Disable */
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        else { /* Nothing */ }
        
        /* CCP Module Capture Mode Initialization */
        if(CCP_CAPTURE_MODE_SELECTED == _ccp_obj->ccp_mode){
            ret = CCP_Capture_Mode_Config(_ccp_obj);
        }
        /* CCP Module Compare Mode Initialization */
        else if(CCP_COMPARE_MODE_SELECTED == _ccp_obj->ccp_mode){
            ret = CCP_Compare_Mode_Config(_ccp_obj);
        }
        #if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
        /* CCP Module PWM Mode Initialization */
        else if(CCP_PWM_MODE_SELECTED == _ccp_obj->ccp_mode){
            CCP_PWM_Mode_Config(_ccp_obj);
        }
        #endif
        else {/* Nothing */}
         /* PIN Configurations */
        ret = gpio_pin_initialize(&(_ccp_obj->ccp_pin));
        /* Interrupt Configurations for CCP1 and CCP2 Modules */
        CCP_Interrupt_Config(_ccp_obj);
        
    }
}
Std_ReturnType CCP_DeInit(const CCP *_ccp_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else
    {
        if(CCP1_INST == _ccp_obj->ccp_inst)
        {
            CCP1_SET_MODE(CCP_MODULE_DISABLE); /* CCP1 Module Disable */
/* Interrupt Configurations */ 
#if CCP1_INTERRUPT_MODE_ENABLE
            CCP1_INTERRUPT_DISABLE();
#endif 
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE); /* CCP2 Module Disable */
#if CCP2_INTERRUPT_MODE_ENABLE
            CCP2_INTERRUPT_DISABLE();
#endif  
        }
        else { /* Nothing */ }
 
        ret = E_OK;
    }
    return ret;
    }

#if (CCP2_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType CCP2_IsCapturedDataReady(uint8 *_capture_status)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _capture_status){
        ret = E_NOT_OK;
    }
    else
    {
          if(CCP_CAPTURE_READY == PIR2bits.CCP2IF){
            *_capture_status = CCP_CAPTURE_READY;
            CCP2_INERRUPT_CLEAR_FLAG();
        }
        else{
            *_capture_status = CCP_CAPTURE_NOT_READY;
        }
        ret = E_OK;
    }
    return ret;
    }

Std_ReturnType CCP2_Capture_Mode_Read_Value(uint16 *capture_value)
{
    Std_ReturnType ret = E_OK;
    CCP_REG capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
    if(NULL == capture_value){
        ret = E_NOT_OK;
    }
    else
    {
        /* Copy captured value */
        capture_temp_value.ccpr_low = CCPR2L;
        capture_temp_value.ccpr_high = CCPR2H;
        /* Write the 16-bit capture value */
        *capture_value = capture_temp_value.ccpr_16Bit;
        ret = E_OK;
    }
    return ret;
    }

#endif

#if (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
Std_ReturnType CCP_IsCompareComplete(uint8 *_compare_status)
{
     Std_ReturnType ret = E_OK;
    if(NULL == _compare_status){
        ret = E_NOT_OK;
    }
    else
    {
        if(CCP_COMPARE_READY == PIR2bits.CCP2IF){
            *_compare_status = CCP_COMPARE_READY;
            CCP2_INERRUPT_CLEAR_FLAG();
        }
        else{
            *_compare_status = CCP_COMPARE_NOT_READY;
        }
        ret = E_OK;
    }
    return ret;
    }

Std_ReturnType CCP_Compare_Mode_Set_Value(const CCP *_ccp_obj, uint16 compare_value)
{
    Std_ReturnType ret = E_OK;
    CCP_REG capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else
    {
         /* Copy compared value */
        capture_temp_value.ccpr_16Bit = compare_value;

        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCPR1L = capture_temp_value.ccpr_low;
            CCPR1H = capture_temp_value.ccpr_high;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCPR2L = capture_temp_value.ccpr_low;
            CCPR2H = capture_temp_value.ccpr_high;
        }
        else{ /* Nothing */ }
        
        ret = E_OK;
    }
    return ret;
    }

#endif

#if (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) 
Std_ReturnType CCP_PWM_Set_Duty(const CCP *_ccp_obj, const uint8 _duty)
{
    Std_ReturnType ret = E_OK;
    uint16 l_duty_temp = 0;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else
    {
        l_duty_temp = (uint16)((float)4 * ((float)PR2 + 1.0) * ((float)_duty / 100.0));
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
            CCPR1L = (uint8)(l_duty_temp >> 2);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003);
            CCPR2L = (uint8)(l_duty_temp >> 2);
        }
        else{ /* Nothing */ }
        
        ret = E_OK;
    }
}
Std_ReturnType CCP_PWM_Start(const CCP *_ccp_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else
    {
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.CCP1M = CCP_PWM_MODE;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.CCP2M = CCP_PWM_MODE;
        }
        else{ /* Nothing */ }
        ret = E_OK;
    }
}
Std_ReturnType CCP_PWM_Stop(const CCP *_ccp_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else
    {
         if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
        }
        else{ /* Nothing */ }
        ret = E_OK;
    }
}
#endif

static Std_ReturnType CCP_Capture_Mode_Config(const CCP *_ccp_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(CCP1_INST == _ccp_obj->ccp_inst){
        /* CCP1 Module Capture variants Mode Initialization */
        switch(_ccp_obj->ccp_mode_variant){
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }
    }
    else if(CCP2_INST == _ccp_obj->ccp_inst){
        /* CCP2 Module Capture variants Mode Initialization */
        switch(_ccp_obj->ccp_mode_variant){
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }
    }
    else{ /* Nothing */ }
    CCP_Mode_Timer_Select(_ccp_obj);
    return ret;
}
static Std_ReturnType CCP_Compare_Mode_Config(const CCP *_ccp_obj)
{
    Std_ReturnType ret = E_OK;
    if(CCP1_INST == _ccp_obj->ccp_inst){
        /* CCP1 Module Compare variants Mode Initialization */
        switch(_ccp_obj->ccp_mode_variant){
            case CCP_COMPARE_MODE_SET_PIN_LOW      : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);      break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH     : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);     break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);  break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
            case CCP_COMPARE_MODE_GEN_EVENT        : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);        break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }
    }
    else if(CCP2_INST == _ccp_obj->ccp_inst){
        /* CCP2 Module Compare variants Mode Initialization */
        switch(_ccp_obj->ccp_mode_variant){
            case CCP_COMPARE_MODE_SET_PIN_LOW      : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);      break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH     : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);     break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);  break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
            case CCP_COMPARE_MODE_GEN_EVENT        : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);        break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }
    }
     CCP_Mode_Timer_Select(_ccp_obj);
}


static void CCP_Interrupt_Config(const CCP *_ccp_obj)
{
    /* CCP1 Interrupt Configurations */ 
#if CCP1_INTERRUPT_MODE_ENABLE
       CCP1_INTERRUPT_ENABLE();
       CCP1_INERRUPT_CLEAR_FLAG(); 

#if !INTERRUPT_PRIORITY_mode
       INTERRUPT_GLOBAL_ENABLE();
       INTERRUPT_prepheral_ENABLE();
       INTERRUPT_PRIORITY_LEVELS_DISABLE();
#endif       

#if INTERRUPT_PRIORITY_mode
   
       INTERRUPT_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE();
       if(_ccp_obj->CCP1_priority==CCP_interrupt_priority_high)
       {
           CCP1_HIGH_PRIORITY_SET();
       }
       else if(_ccp_obj->CCP1_priority==CCP_interrupt_priority_low)
       {
           CCP1_LOW_PRIORITY_SET();
       }
#endif
         CCP1_InterruptHandler=_ccp_obj->CCP1_InterruptHandler;
#endif
         
    /* CCP2 Interrupt Configurations */ 
#if CCP2_INTERRUPT_MODE_ENABLE
       CCP2_INTERRUPT_ENABLE();
       CCP2_INERRUPT_CLEAR_FLAG(); 

#if !INTERRUPT_PRIORITY_mode
       INTERRUPT_GLOBAL_ENABLE();
       INTERRUPT_prepheral_ENABLE();
       INTERRUPT_PRIORITY_LEVELS_DISABLE();
#endif       

#if INTERRUPT_PRIORITY_mode
   
       INTERRUPT_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE();
       INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE();
       if(_ccp_obj->CCP2_priority==CCP_interrupt_priority_high)
       {
           CCP2_HIGH_PRIORITY_SET();
       }
       else if(_ccp_obj->CCP2_priority==CCP_interrupt_priority_low)
       {
           CCP2_LOW_PRIORITY_SET();
       }
#endif
         CCP2_InterruptHandler=_ccp_obj->CCP2_InterruptHandler;
#endif
    
}

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
 static void CCP_PWM_Mode_Config(const CCP *_ccp_obj)
{
    /* PWM Frequency Initialization */
    PR2 = (uint8)(((float)_XTAL_FREQ / ((float)_ccp_obj->PWM_Frequency * 4.0 * (float)_ccp_obj->timer2_prescaler_value * 
                    (float)_ccp_obj->timer2_postscaler_value)) - 1);
    
    if(CCP1_INST == _ccp_obj->ccp_inst){
        if(CCP_PWM_MODE == _ccp_obj->ccp_mode_variant){
            CCP1_SET_MODE(CCP_PWM_MODE);
        }
        else {/* Nothing */}
    }
    else if(CCP2_INST == _ccp_obj->ccp_inst){
        if(CCP_PWM_MODE == _ccp_obj->ccp_mode_variant){
            CCP2_SET_MODE(CCP_PWM_MODE);
        }
        else {/* Nothing */}
}
     else{ /* Nothing */ }
}
#endif

static void CCP_Mode_Timer_Select(const CCP *_ccp_obj)
{
    if(CCP1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer){
        /* Timer3 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0; 
        T3CONbits.T3CCP2 = 1;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer){
        /* Timer3 is the capture/compare clock source for CCP2 */
        /* Timer1 is the capture/compare clock source for CCP1 */
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_CCP2_TIMER1 == _ccp_obj->ccp_capture_timer){
        /* Timer1 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else{ /* Nothing */ }
}

#if CCP1_INTERRUPT_MODE_ENABLE
void CCP1_ISR(void){
    CCP1_INERRUPT_CLEAR_FLAG();
    if(CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }
    else{ /* Nothing */ }
}
#endif

#if CCP2_INTERRUPT_MODE_ENABLE
void CCP2_ISR(void){
    CCP2_INERRUPT_CLEAR_FLAG();
    if(CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    }
    else{ /* Nothing */ }
}
#endif