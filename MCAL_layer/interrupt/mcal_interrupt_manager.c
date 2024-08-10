/* 
 * File:   mcal_interrupt_manager.c
 * Author: AHMED AKRAM
 *
 * Created on February 4, 2024, 2:30 AM
 */
#include "mcal_interrupt_manager.h"

volatile static uint8 RB4_FLAG = 1;
volatile static uint8 RB5_FLAG = 1;
volatile static uint8 RB6_FLAG = 1;
volatile static uint8 RB7_FLAG = 1;


#if INTERRUPT_PRIORITY_mode
void __interrupt() EXT_HIGH_ISR(void)
{
    /*---------------- INTX HANDLING START -------------------------------------------*/
    if((INTERRUPT_ENABLE==INTCONbits.INT0IE) && (INTERRUPT_OCCUR==INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCON3bits.INT2IE) && (INTERRUPT_OCCUR==INTCON3bits.INT2IF) )
    {
       INT2_ISR();
    }
    else{/*nothing*/}
    /*---------------- INTX HANDLING END  -------------------------------------------*/
    
}

void __interrupt(low_priority) EXT_low_ISR(void)
{
    if((INTERRUPT_ENABLE==INTCON3bits.INT1IE) && (INTERRUPT_OCCUR==INTCON3bits.INT1IF) )
    {
       INT1_ISR();
    }
    else{/*nothing*/}
    
   
}

#endif
#if !INTERRUPT_PRIORITY_mode
void __interrupt() _ISR(void)
{
    /*---------------- INTX HANDLING START -------------------------------------------*/
    if((INTERRUPT_ENABLE==INTCONbits.INT0IE) && (INTERRUPT_OCCUR==INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCON3bits.INT1IE) && (INTERRUPT_OCCUR==INTCON3bits.INT1IF) )
    {
       INT1_ISR();
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCON3bits.INT2IE) && (INTERRUPT_OCCUR==INTCON3bits.INT2IF) )
    {
       INT2_ISR();
    }
    else{/*nothing*/}
    /*---------------- INTX HANDLING START -------------------------------------------*/
    
    /*---------------- RBX HANDLING START -------------------------------------------*/
    
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
             && (INTERRUPT_ENABLE==IOCBbits.IOCB4) && (1==RB4_FLAG)
                             && (high==PORTBbits.RB4)  )
    {
       RB4_FLAG=0;
       RB4_ISR_high();
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
             && (INTERRUPT_ENABLE==IOCBbits.IOCB4) && (0==RB4_FLAG)
                             && (low==PORTBbits.RB4)  )
    {
       RB4_FLAG=1;
       RB4_ISR_low();
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
             && (INTERRUPT_ENABLE==IOCBbits.IOCB5) && (1==RB5_FLAG) 
                           && (high==PORTBbits.RB5))
    {
       RB5_FLAG=0;
       RB5_ISR_high();
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
             && (INTERRUPT_ENABLE==IOCBbits.IOCB5) && (0==RB5_FLAG) 
                           && (low==PORTBbits.RB5))
    {
       RB5_FLAG=1;
       RB5_ISR_low();
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
             && (INTERRUPT_ENABLE==IOCBbits.IOCB6) && (1==RB6_FLAG) 
                           && (high==PORTBbits.RB6))
    {
       RB6_FLAG=0;
       RB6_ISR_high();
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
             && (INTERRUPT_ENABLE==IOCBbits.IOCB6) && (0==RB6_FLAG) 
                           && (low==PORTBbits.RB6))
    {
       RB6_FLAG=1;
       RB6_ISR_low();
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
             && (INTERRUPT_ENABLE==IOCBbits.IOCB7) && (1==RB7_FLAG) 
                           && (high==PORTBbits.RB7))
    {
       RB7_FLAG=0;
       RB7_ISR_high();
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
             && (INTERRUPT_ENABLE==IOCBbits.IOCB7) && (0==RB7_FLAG) 
                           && (low==PORTBbits.RB7))
    {
       RB7_FLAG=1;
       RB7_ISR_low();
    }
    else{/*nothing*/}
    /*---------------- RBX HANDLING END -------------------------------------------*/
    
    /*---------------- ADC HANDLING -------------------------------------------*/
    if((INTERRUPT_ENABLE==PIE1bits.ADIE) && (INTERRUPT_OCCUR==PIR1bits.ADIF))
    {
        ADC_ISR();
    }
    else{/*nothing*/}
    /*---------------- TIMER0 HANDLING -------------------------------------------*/
    if((INTERRUPT_ENABLE== INTCONbits.TMR0IE) && (INTERRUPT_OCCUR==INTCONbits.TMR0IF))
    {
        TIMER0_ISR();
    }
    else{/*nothing*/} 
     /*---------------- TIMER1 HANDLING -------------------------------------------*/
    if((INTERRUPT_ENABLE== PIE1bits.TMR1IE) && (INTERRUPT_OCCUR==PIR1bits.TMR1IF))
    {
        TIMER1_ISR();
    }
    else{/*nothing*/} 
    /*---------------- TIMER2 HANDLING -------------------------------------------*/
    if((INTERRUPT_ENABLE== PIE1bits.TMR2IE) && (INTERRUPT_OCCUR==PIR1bits.TMR2IF))
    {
        TIMER2_ISR();
    }
    else{/*nothing*/} 
    /*---------------- TIMER3 HANDLING -------------------------------------------*/
    if((INTERRUPT_ENABLE== PIE2bits.TMR3IE) && (INTERRUPT_OCCUR==PIR2bits.TMR3IF))
    {
        TIMER3_ISR();
    }
    else{/*nothing*/} 
    /*---------------- ccp1 HANDLING -------------------------------------------*/
    if((INTERRUPT_ENABLE== PIE1bits.CCP1IE) && (INTERRUPT_OCCUR==PIR1bits.CCP1IF))
    {
        CCP1_ISR();
    }
    else{/*nothing*/} 
    /*---------------- ccp2 HANDLING -------------------------------------------*/
    if((INTERRUPT_ENABLE== PIE2bits.CCP2IE) && (INTERRUPT_OCCUR==PIR2bits.CCP2IF))
    {
        CCP2_ISR();
    }
    else{/*nothing*/} 
}
#endif