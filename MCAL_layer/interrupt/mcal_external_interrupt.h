/* 
 * File:   mcal_external_interrupt.h
 * Author: AHMED AKRAM
 *
 * Created on February 4, 2024, 2:29 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/*-------------------------------includes-------------------------- : */
#include "mcal_interrupt_configration.h"
/*---------------------------macro declarations-------------------------- : */
/*----------------------------macro functions-------------------------- : */
#if EXTERNAL_INTERRUPT_INTX_MODE

/*THE NEXT 4 MACROS ARE FOR INT0 PIN INTERRUPT HANDLING (ALWAYS HIGH PRIOTITY)*/
/*Enables the INT0 external interrupt */
#define EXT_INT0_ENABLE()                   (INTCONbits.INT0IE = 1)          
/*Disables the INT0 external interrupt*/
#define EXT_INT0_Disables()                 (INTCONbits.INT0IE = 0)
/* CLEAR INTO FLAG BIT (must be cleared by software) */
#define EXT_INT0_CLEAR_FLAG()               (INTCONbits.INT0IF = 0)
/*Interrupt on rising edge*/
#define EXT_INT0_ON_RISING_EDGE_SET()       (INTCON2bits.INTEDG0 = 1)
/*Interrupt on falling edge*/
#define EXT_INT0_ON_FALLING_EDGE_SET()      (INTCON2bits.INTEDG0 = 0)

/*THE NEXT 4 MACROS ARE FOR INT1 PIN INTERRUPT HANDLING */

/*Enables the INT1 external interrupt */
#define EXT_INT1_ENABLE()                     (INTCON3bits.INT1IE = 1) 
/*Disables the INT1 external interrupt*/
#define EXT_INT1_Disables()                   (INTCON3bits.INT1IE = 0)
/* CLEAR INTO FLAG BIT (must be cleared by software) */
#define EXT_INT1_CLEAR_FLAG()                 (INTCON3bits.INT1IF = 0)
/*Interrupt on rising edge*/
#define EXT_INT1_ON_RISING_EDGE_SET()         (INTCON2bits.INTEDG1 = 1)
/*Interrupt on falling edge*/ 
#define EXT_INT1_ON_FALLING_EDGE_SET()        (INTCON2bits.INTEDG1 = 0)


/*THE NEXT 4 MACROS ARE FOR INT2 PIN INTERRUPT HANDLING */

/*Enables the INT2 external interrupt */
#define EXT_INT2_ENABLE()                      (INTCON3bits.INT2IE = 1)
/*Disables the INT2 external interrupt*/
#define EXT_INT2_Disables()                    (INTCON3bits.INT2IE = 0)
/* CLEAR INTO FLAG BIT (must be cleared by software) */
#define EXT_INT2_CLEAR_FLAG()                  (INTCON3bits.INT2IF = 0)
/*Interrupt on rising edge*/
#define EXT_INT2_ON_RISING_EDGE_SET()          (INTCON2bits.INTEDG2 = 1)
/*Interrupt on falling edge*/ 
#define EXT_INT2_ON_FALLING_EDGE_SET()         (INTCON2bits.INTEDG2 = 0)

/*IF PRIORITY IS ENABLED */
#if INTERRUPT_PRIORITY_mode
/*SET INT1 AS HIGH PRIORITY */
#define EXT_INT1_HIGH_PRORITY_SET()            (INTCON3bits.INT1IP = 1)  
/*SET INT1 AS LOW PRIORITY */
#define EXT_INT1_LOW_PRORITY_SET()             (INTCON3bits.INT1IP = 0)

/*SET INT2 AS HIGH PRIORITY */
#define EXT_INT2_HIGH_PRORITY_SET()            (INTCON3bits.INT2IP = 1)  
/*SET INT2 AS LOW PRIORITY */
#define EXT_INT2_LOW_PRORITY_SET()             (INTCON3bits.INT2IP = 0) 

#endif

#endif

#if EXTERNAL_INTERRUPT_ONCHANGE_MODE

/*THE NEXT 3 MACROS ARE FOR RBx PIN INTERRUPT HANDLING */



/*Enables the RBx external interrupt */
#define EXT_RBx_ENABLE()                     (INTCONbits.RBIE = 1)          
/*Disables the RBx external interrupt*/
#define EXT_RBx_Disables()                   (INTCONbits.RBIE = 0)
/* CLEAR RBx FLAG BIT (must be cleared by software) */
#define EXT_RBx_CLEAR_FLAG()                 (INTCONbits.RBIF = 0)

/* AFTER ENABLING RBIE :
 * The RBIF interrupt also requires the individual pin IOCB enables.  */

/*Enables the RB4 external interrupt */
#define RB4_ENABLE()                           IOCBbits.IOCB4 = 1
/*Disables the RB4 external interrupt */
#define RB4_Disables()                         IOCBbits.IOCB4 = 0

/*Enables the RB5 external interrupt */
#define RB5_ENABLE()                           IOCBbits.IOCB5 = 1
/*Disables the RB5 external interrupt */
#define RB5_Disables()                         IOCBbits.IOCB5 = 0

/*Enables the RB6 external interrupt */
#define RB6_ENABLE()                           IOCBbits.IOCB6 = 1
/*Disables the RB6 external interrupt */
#define RB6_Disables()                         IOCBbits.IOCB6 = 0


/*Enables the RB7 external interrupt */
#define RB7_ENABLE()                           IOCBbits.IOCB7 = 1
/*Disables the RB4 external interrupt */
#define RB7_Disables()                         IOCBbits.IOCB7 = 0

/*IF PRIORITY IS ENABLED */

#if INTERRUPT_PRIORITY_mode
/*SET RBX AS HIGH PRIORITY */
#define EXT_RBX_HIGH_PRORITY_SET()           (INTCON2bits.RBIP = 1)  
/*SET RBX AS LOW PRIORITY */
#define EXT_RBX_LOW_PRORITY_SET()            (INTCON2bits.RBIP = 0)
#endif

#endif

/*-------------------------------data types-------------------------- : */

typedef enum
{
    Ext_interrupt_priority_low,
    Ext_interrupt_priority_high        
}Ext_interrupt_priority;

typedef enum 
{
    Falling_Edge,
    Rising_Edge,        
}EXT_Intx_Edge;

typedef enum 
{
    Int0,
    Int1,
    Int2,        
}EXT_Intx_Source;


typedef struct 
{
    Std_ReturnType (* EXTERNAL_INTX_callback)(void);
    pin_configration MCU_pin;
    #if INTERRUPT_PRIORITY_mode
    Ext_interrupt_priority priority;
    #endif
    EXT_Intx_Edge Intx_Edge;
    EXT_Intx_Source source; 
}EXTERNAL_INTX_INTERRUPT;


typedef struct 
{
    Std_ReturnType (* EXTERNAL_RBX_callback_high)(void);
    Std_ReturnType (* EXTERNAL_RBX_callback_low)(void);
    pin_configration pin;
    #if INTERRUPT_PRIORITY_mode
    Ext_interrupt_priority priority;
    #endif
}EXTERNAL_RBX_INTERRUPT;


/*----------------------function declarations-------------------------- : */
Std_ReturnType Activate_Intx_Interrupts(const EXTERNAL_INTX_INTERRUPT *obj);
Std_ReturnType Dectivate_Intx_Interrupts(const EXTERNAL_INTX_INTERRUPT *obj);


Std_ReturnType Activate_RBX_Interrupts(const EXTERNAL_RBX_INTERRUPT *obj);
Std_ReturnType Dectivate_RBX_Interrupts(const EXTERNAL_RBX_INTERRUPT *obj);  

Std_ReturnType INT0_ISR(void);
Std_ReturnType INT1_ISR(void);
Std_ReturnType INT2_ISR(void);

Std_ReturnType RB4_ISR_high(void);
Std_ReturnType RB4_ISR_low(void);

Std_ReturnType RB5_ISR_high(void);
Std_ReturnType RB5_ISR_low(void);

Std_ReturnType RB6_ISR_high(void);
Std_ReturnType RB6_ISR_low(void);

Std_ReturnType RB7_ISR_high(void);
Std_ReturnType RB7_ISR_low(void);


#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

