/* 
 * File:   mcal_interrupt_configration.h
 * Author: AHMED AKRAM
 *
 * Created on February 4, 2024, 6:24 AM
 */

#ifndef MCAL_INTERRUPT_CONFIGRATION_H
#define	MCAL_INTERRUPT_CONFIGRATION_H

/*-------------------------------includes-------------------------- : */
#include "../proc/pic18f46k20.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
/*---------------------------macro declarations-------------------------- : */
#define INTERRUPT_ENABLE                1
#define INTERRUPT_DISABLE               0

#define INTERRUPT_OCCUR                 1
#define INTERRUPT_NOT_OCCUR             0

#define INTERRUPT_PRIORITY_ENABLE       1 /* if choosen in line 24  enables prority mode */ 
#define INTERRUPT_PRIORITY_DISABLE      0 /* if choosen in line 24  DISABLE prority mode */ 

#define INTERRUPT_PRIORITY_mode         INTERRUPT_PRIORITY_DISABLE

/* CHOOSE THE EXTERNAL INTERRUPT CONFIGRATION */
#define EXTERNAL_INTERRUPT_INTX_ENABLE           1 /* if choosen in line 33  enables INTX INTERRUPTS */
#define EXTERNAL_INTERRUPT_INTX_DISABLE          0 /* if choosen in line 33  DISABLE INTX INTERRUPTS*/

#define EXTERNAL_INTERRUPT_ONCHANGE_ENABLE       1 /* if choosen in line 34  enables ONCHANGE INTERRUPTS  */
#define EXTERNAL_INTERRUPT_ONCHANGE_DISABLE      0 /* if choosen in line 34  DISABLE ONCHANGE INTERRUPTS  */

#define EXTERNAL_INTERRUPT_INTX_MODE                EXTERNAL_INTERRUPT_INTX_ENABLE 

#define EXTERNAL_INTERRUPT_ONCHANGE_MODE            EXTERNAL_INTERRUPT_ONCHANGE_ENABLE 

/*------------------------------------ADC INTERRUPT---------------------------------------------------*/
 /*CHOOSE ADC INTERRUPT MODE  */
#define ADC_INTERRUPT_MODE_ENABLE              1  /* if choosen in line 44  ENABLE ADC_INTERRUPT */ 
#define ADC_INTERRUPT_MODE_DISABLE             0  /* if choosen in line 44  DISABLE ADC_INTERRUPT */


#define ADC_INTERRUPT_MODE           ADC_INTERRUPT_MODE_ENABLE

/*------------------------------------TIMER0 INTERRUPT---------------------------------------------------*/
#define TIMER0_INTERRUPT_MODE_ENABLE            1  /* if choosen in line 51  ENABLE TIMER0_INTERRUPT */ 
#define TIMER0_INTERRUPT_MODE_DISABLE           0  /* if choosen in line 51  DISABLE TIMER0_INTERRUPT */


#define TIMER0_INTERRUPT_MODE           TIMER0_INTERRUPT_MODE_ENABLE

/*------------------------------------TIMER1 INTERRUPT---------------------------------------------------*/
#define TIMER1_INTERRUPT_MODE_ENABLE            1  /* if choosen in line 58  ENABLE TIMER1_INTERRUPT */ 
#define TIMER1_INTERRUPT_MODE_DISABLE           0  /* if choosen in line 58  DISABLE TIMER1_INTERRUPT */


#define TIMER1_INTERRUPT_MODE           TIMER1_INTERRUPT_MODE_ENABLE

/*------------------------------------TIMER2 INTERRUPT---------------------------------------------------*/
#define TIMER2_INTERRUPT_MODE_ENABLE            1  /* if choosen in line 65  ENABLE TIMER2_INTERRUPT */ 
#define TIMER2_INTERRUPT_MODE_DISABLE           0  /* if choosen in line 65  DISABLE TIMER2_INTERRUPT */


#define TIMER2_INTERRUPT_MODE           TIMER2_INTERRUPT_MODE_ENABLE
/*------------------------------------TIMER3 INTERRUPT---------------------------------------------------*/
#define TIMER3_INTERRUPT_MODE_ENABLE            1  /* if choosen in line 71  ENABLE TIMER2_INTERRUPT */ 
#define TIMER3_INTERRUPT_MODE_DISABLE           0  /* if choosen in line 71  DISABLE TIMER2_INTERRUPT */


#define TIMER3_INTERRUPT_MODE           TIMER3_INTERRUPT_MODE_ENABLE

/*------------------------------------CCP2 INTERRUPT---------------------------------------------------*/
#define CCP2_INTERRUPT_MODE_ENABLE            1  /* if choosen in line 78  ENABLE TIMER2_INTERRUPT */ 
#define CCP2_INTERRUPT_MODE_DISABLE           0  /* if choosen in line 78  DISABLE TIMER2_INTERRUPT */


#define CCP2_INTERRUPT_MODE           CCP2_INTERRUPT_MODE_ENABLE

/*------------------------------------CCP1 INTERRUPT---------------------------------------------------*/
#define CCP1_INTERRUPT_MODE_ENABLE            1  /* if choosen in line 78  ENABLE TIMER2_INTERRUPT */ 
#define CCP1_INTERRUPT_MODE_DISABLE           0  /* if choosen in line 78  DISABLE TIMER2_INTERRUPT */


#define CCP1_INTERRUPT_MODE           CCP1_INTERRUPT_MODE_ENABLE

/*------------------------------------usart_tx INTERRUPT---------------------------------------------------*/
 /*CHOOSE usart_tx INTERRUPT MODE  */
#define usart_tx_INTERRUPT_MODE_ENABLE              1  /* if choosen in line 44  ENABLE ADC_INTERRUPT */ 
#define usart_tx_INTERRUPT_MODE_DISABLE             0  /* if choosen in line 44  DISABLE ADC_INTERRUPT */


#define usart_tx_INTERRUPT_MODE           usart_tx_INTERRUPT_MODE_ENABLE

/*------------------------------------usart_rx INTERRUPT---------------------------------------------------*/
 /*CHOOSE usart_rx INTERRUPT MODE  */
#define usart_rx_INTERRUPT_MODE_ENABLE              1  /* if choosen in line 44  ENABLE ADC_INTERRUPT */ 
#define usart_rx_INTERRUPT_MODE_DISABLE             0  /* if choosen in line 44  DISABLE ADC_INTERRUPT */


#define usart_rx_INTERRUPT_MODE           usart_rx_INTERRUPT_MODE_ENABLE


/*----------------------------macro functions-------------------------- : */
#if INTERRUPT_PRIORITY_mode
       /*  enable priority levels  */
#define INTERRUPT_PRIORITY_LEVELS_ENABLE()                RCONbits.IPEN =   1    
       /* enable all high priority interrupts */
#define INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_ENABLE()    INTCONbits.GIEH = 1
       /* disable all high priority interrupts */
#define INTERRUPT_GLOBAL_HIGH_PRIORITY_LEVELS_DISABLE()   INTCONbits.GIEH = 0
      /* enable all low priority interrupts */
#define INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_ENABLE()     INTCONbits.GIEL = 1
      /* disable all low priority interrupts */
#define INTERRUPT_GLOBAL_low_PRIORITY_LEVELS_DISABLE()    INTCONbits.GIEL = 0
 
#endif

#if !INTERRUPT_PRIORITY_mode
       /*  disable priority levels  */
#define INTERRUPT_PRIORITY_LEVELS_DISABLE()               RCONbits.IPEN =   0
        /*  disable priority of int1  */
#define INTERRUPT_PRIORITY_int1_DISABLE()                 INTCON3bits.INT1IP = 0
       /*  disable priority of int2  */
#define INTERRUPT_PRIORITY_int2_DISABLE()                 INTCON3bits.INT2IP= 0
       /*  disable priority of RBX  */
#define INTERRUPT_PRIORITY_RBX_DISABLE()                 INTCON2bits.RBIP = 0
       /* Enables all unmasked interrupts */
#define INTERRUPT_GLOBAL_ENABLE()                         INTCONbits.GIE =  1
       /* Disables all interrupts including peripherals */
#define INTERRUPT_GLOBAL_Disables()                       INTCONbits.GIE =  0
      /* Enables all unmasked peripheral interrupts */
#define INTERRUPT_prepheral_ENABLE()                      INTCONbits.PEIE = 1
      /* Disables all peripheral interrupts */
#define INTERRUPT_prepheral_Disables()                    INTCONbits.PEIE = 0
#endif
/*----------------------function declarations-------------------------- : */

/*-------------------------------data types-------------------------- : */


#endif	/* MCAL_INTERRUPT_CONFIGRATION_H */

