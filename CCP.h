/* 
 * File:   CCP.h
 * Author: AHMED AKRAM
 *
 * Created on April 12, 2024, 5:17 PM
 */

#ifndef CCP_H
#define	CCP_H
/* ----------------- Includes -----------------*/
#include "MCAL_layer/GPIO/hal_gpio.h"
#include "MCAL_layer/mcal_std_types.h"
#include "../proc/pic18f46k20.h"
#include "MCAL_layer/interrupt/mcal_internal_interrupt.h"
/* ----------------- Macro Declarations -----------------*/
/* choose the mode in line 21 and 22 */
#define CCP_CFG_CAPTURE_MODE_SELECTED  0x00
#define CCP_CFG_COMPARE_MODE_SELECTED  0x01
#define CCP_CFG_PWM_MODE_SELECTED      0x02

#define CCP1_CFG_SELECTED_MODE      CCP_CFG_COMPARE_MODE_SELECTED
#define CCP2_CFG_SELECTED_MODE      CCP_CFG_COMPARE_MODE_SELECTED

/* CCP2 Module(SUB) Mode Select  */
#define CCP_MODULE_DISABLE                 ((uint8)0x00)
#define CCP_CAPTURE_MODE_1_FALLING_EDGE    ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE     ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE     ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE    ((uint8)0x07)
#define CCP_COMPARE_MODE_SET_PIN_LOW       ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH      ((uint8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH   ((uint8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT  ((uint8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT         ((uint8)0x0B)
#define CCP_PWM_MODE                       ((uint8)0x0C)

/* CCP2 Capture Mode State  */
#define CCP_CAPTURE_NOT_READY              0X00
#define CCP_CAPTURE_READY                  0X01

/* CCP2 Compare Mode State  */
#define CCP_COMPARE_NOT_READY              0X00
#define CCP_COMPARE_READY                  0X01

/* Timer2 Input Clock Post-scaler */
#define CCP_TIMER2_POSTSCALER_DIV_BY_1       1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2       2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3       3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4       4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5       5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6       6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7       7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8       8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9       9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10      10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11      11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12      12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13      13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14      14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15      15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16      16

/* Timer2 Input Clock Pre-scaler */
#define CCP_TIMER2_PRESCALER_DIV_BY_1        1
#define CCP_TIMER2_PRESCALER_DIV_BY_4        4
#define CCP_TIMER2_PRESCALER_DIV_BY_16       16

/* ----------------- Macro Functions Declarations -----------------*/
#define CCP1_SET_MODE(_CONFIG)  (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG)  (CCP2CONbits.CCP2M = _CONFIG)
/* ----------------- Data Type Declarations -----------------*/

/*
  @Summary      Define the values to select the CCP1 Main mode
*/
typedef enum{
    CCP_CAPTURE_MODE_SELECTED = 0, /* Select CCP2 Capture Mode */
    CCP_COMPARE_MODE_SELECTED,     /* Select CCP2 Compare Mode */
    CCP_PWM_MODE_SELECTED          /* Select CCP2 PWM Mode */
}ccp_mode;

/*
  @Summary      Defines the values to convert from 16bit to two 8 bit and vice versa
  @Description  Used to get two 8 bit values from 16bit also two 8 bit value are combine to get 16bit.
*/
typedef union{
    struct{
        uint8 ccpr_low;  /* CCPR2 low register */
        uint8 ccpr_high; /* CCPR2 high register */
    };
    struct{
        uint16 ccpr_16Bit; /* Read CCPR2 as a 16 Bit value */
    };
}CCP_REG;

typedef enum{
    CCP1_INST = 0,
    CCP2_INST
}ccp_inst;

typedef enum{
    CCP1_CCP2_TIMER3 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER1
}ccp_capture_timer_t;


#if TIMER0_INTERRUPT_MODE
typedef enum
{
    CCP_interrupt_priority_low,
    CCP_interrupt_priority_high        
}CCP_interrupt_priority;
#endif

typedef struct{
    ccp_inst ccp_inst;      /* choose ccp1 or ccp2 */
    ccp_mode ccp_mode;      /* CCP main mode */
    uint8 ccp_mode_variant;    /* CCP selected SUB mode  */
    pin_configration ccp_pin;      /* CCP Pin I/O configurations */
    ccp_capture_timer_t ccp_capture_timer;
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
    uint32 PWM_Frequency;      /* CCP PWM mode frequency */
    uint8 timer2_postscaler_value;
    uint8 timer2_prescaler_value;
#endif
#if CCP1_INTERRUPT_MODE
    void (* CCP1_InterruptHandler)(void);   /* Call back used for all CCP1 Modes */
    #if INTERRUPT_PRIORITY_mode
    CCP_interrupt_priority CCP1_priority;   /* Configure the CCP1 mode interrupt */
    #endif
#endif
#if CCP2_INTERRUPT_MODE
     void (* CCP2_InterruptHandler)(void);   /* Call back used for all CCP2 Modes */
     #if INTERRUPT_PRIORITY_mode
     CCP_interrupt_priority CCP2_priority;  /* Configure the CCP2 mode interrupt */
     #endif 
#endif
}CCP;


/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType CCP_Init(const CCP *_ccp_obj);
Std_ReturnType CCP_DeInit(const CCP *_ccp_obj);

#if (CCP2_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType CCP2_IsCapturedDataReady(uint8 *_capture_status);
Std_ReturnType CCP2_Capture_Mode_Read_Value(uint16 *capture_value);
#endif

#if (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
Std_ReturnType CCP_IsCompareComplete(uint8 *_compare_status);
Std_ReturnType CCP_Compare_Mode_Set_Value(const CCP *_ccp_obj, uint16 compare_value);
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
Std_ReturnType CCP_PWM_Set_Duty(const CCP *_ccp_obj, const uint8 _duty);
Std_ReturnType CCP_PWM_Start(const CCP *_ccp_obj);
Std_ReturnType CCP_PWM_Stop(const CCP *_ccp_obj);
#endif

#if CCP1_INTERRUPT_MODE_ENABLE
void CCP1_ISR(void);
#endif

#if CCP2_INTERRUPT_MODE_ENABLE
void CCP2_ISR(void);
#endif

#endif	/* CCP_H */

