    /* 
     * File:   application.c
     * Author: AHMED AKRAM
     *
     * Created on September 30, 2023, 9:03 PM
     */
    
    #include "application.h"

    TIMER3 timer3 =
    {
      .TIMER3_INTERRUPT_HANDLER = APP_TIMER3_ISR,
      .Timer3_MODE = Timer_MODE,
      .Timer3_REGISTER_SIZE = TIMER3_RW_REG_8Bit_MODE,
      .Timer3_preloaded_value = 0,
      .PRE_SCALER_VALUE = TIMER3_PRESCALER_DIV_BY_1
    };
    
    CCP ccp2 =
     {
        .ccp_inst = CCP2_INST,
        .CCP2_InterruptHandler = APP_CCP2_ISR,
        .ccp_mode = CCP_CAPTURE_MODE_SELECTED,
        .ccp_pin.port = portC_index,
        .ccp_pin.pin = pin1,
        .ccp_pin.direction = input,
        .ccp_capture_timer = CCP1_CCP2_TIMER3,
        .ccp_mode_variant = CCP_CAPTURE_MODE_1_RISING_EDGE
     };
    
    
    
 
    Std_ReturnType APP_TIMER3_ISR(void)
    {
     
    }
    
    Std_ReturnType APP_CCP2_ISR(void)
    {
       
    }
    
    
     
     
    int main()
    {
        application_initialize();
        CCP_Init(&ccp2);
        TIMER3_init(&timer3);
       while(1)
       {
          
       }  
    }
   void application_initialize(void)
   {
       Ecu_initialize();
   }  