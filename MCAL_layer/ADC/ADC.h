/* 
 * File:   ADC.h
 * Author: AHMED AKRAM
 *
 * Created on February 16, 2024, 2:35 PM
 */

#ifndef ADC_H
#define	ADC_H
/*-------------------------------includes-------------------------- : */
#include "../GPIO/hal_gpio.h"
#include "../proc/pic18f46k20.h"
#include"../../MCAL_layer/interrupt/mcal_internal_interrupt.h"


/*---------------------------macro declarations-------------------------- : */



/*----------------------------macro functions-------------------------- : */
#define Adc_conversion_status()                ADCON0bits.GO_DONE
#define Adc_start_conversion()                 ADCON0bits.GO_DONE = 1

#define Adc_Enable()                           ADCON0bits.ADON = 1
#define Adc_Disable()                          ADCON0bits.ADON = 0

/* VREF IS THE VDD */
#define Adc_Enable_Internal_Vlotage_Ref()      do{ADCON1bits.VCFG0 = 0; \
                                                  ADCON1bits.VCFG1 = 0; \
                                                 }while(0)

/* VREF CONNECTED EXTERNALLY THROUGH A BATTERY  */
#define Adc_Enable_EXTERNAL_Vlotage_Ref()      do{ADCON1bits.VCFG0 = 1; \
                                                  ADCON1bits.VCFG1 = 1; \
                                                 }while(0)


/*choose voltage ref source */
#define Adc_Internal_Vlotage_Ref            0X01
#define Adc_EXTERNAL_Vlotage_Ref            0X00


/*Activate chanels*/
#define AN0_ENABLE()                              ANSELbits.ANS0   = 1
#define AN1_ENABLE()                              ANSELbits.ANS1   = 1
#define AN2_ENABLE()                              ANSELbits.ANS2   = 1
#define AN3_ENABLE()                              ANSELbits.ANS3   = 1
#define AN4_ENABLE()                              ANSELbits.ANS4   = 1
#define AN5_ENABLE()                              ANSELbits.ANS5   = 1
#define AN6_ENABLE()                              ANSELbits.ANS6   = 1
#define AN7_ENABLE()                              ANSELbits.ANS7   = 1
#define AN8_ENABLE()                              ANSELHbits.ANS8  = 1
#define AN9_ENABLE()                              ANSELHbits.ANS9  = 1
#define AN10_ENABLE()                             ANSELHbits.ANS10 = 1
#define AN11_ENABLE()                             ANSELHbits.ANS11 = 1
#define AN12_ENABLE()                             ANSELHbits.ANS12 = 1

/*A/D Conversion Result Format Select bit*/
#define ADC_Right_justified()                      ADCON2bits.ADFM = 1
#define ADC_LEFT_justified()                       ADCON2bits.ADFM = 0

/*choose result format*/
#define ADC_RESULT_RIGHT    0x01
#define ADC_RESULT_LEFT     0x00


/*-------------------------------data types-------------------------- : */
/**
 * @brief Analog Channel Select
 */
typedef enum 
{
    Adc_channel_AN0,
    Adc_channel_AN1,
    Adc_channel_AN2,
    Adc_channel_AN3,  
    Adc_channel_AN4,
    Adc_channel_AN5,
    Adc_channel_AN6,
    Adc_channel_AN7,
    Adc_channel_AN8,
    Adc_channel_AN9,
    Adc_channel_AN10,
    Adc_channel_AN11, 
    Adc_channel_AN12,
            
}Adc_channel;

/**
 * @brief  A/D Acquisition Time Select 
 * @note   Acquisition time (sampling time) is the time required for the (ADC) to 
 *         capture the input voltage during sampling.
 * @note   Acquisition time of a Successive Approximation Register (SAR) ADC is the amount of time 
 *         required to charge the holding capacitor (CHOLD) on the front end of an ADC
 */
typedef enum 
{
    ADC_0_TAD,
    ADC_2_TAD,
    ADC_4_TAD,        
    ADC_6_TAD,        
    ADC_8_TAD,        
    ADC_12_TAD,        
    ADC_16_TAD,
    ADC_20_TAD,               
}Adc_Aquisation_time;


/**
 * @brief  A/D Conversion Clock Select
 * @note   If the A/D FRC clock source is selected, a delay of one TCY (instruction cycle) 
 *         is added before the A/D clock starts.
 * @note   This allows the SLEEP instruction to be executed before starting a conversion.
 */
typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
}Adc_conversion_clock;

#if ADC_INTERRUPT_MODE
typedef enum
{
    ADC_interrupt_priority_low,
    ADC_interrupt_priority_high        
}ADC_interrupt_priority;
#endif

   /**
     * ADC Configurations
     */
typedef struct
{
    #if ADC_INTERRUPT_MODE
    void (*ADC_INTERRUPT_HANDLER)(void);  
    ADC_interrupt_priority ADC_PRIORITY;
    #endif
    Adc_Aquisation_time acquisition_time;     /* @ref Adc_Aquisation_time */
    Adc_conversion_clock conversion_clock;    /* @ref adc_conversion_clock */
    Adc_channel adc_channel;                  /* @ref Adc_channel */
    uint8 result_format : 1;                  /* A/D Result Format Select */
    uint8 voltage_reference : 1;           /* Voltage Reference Configuration */
    uint8 ADC_Reserved : 6;
}ADC;
/*----------------------function declarations-------------------------- : */
Std_ReturnType Adc_init(const ADC *my_ADC);
Std_ReturnType Adc_DEinit(const ADC *my_ADC);
Std_ReturnType Adc_Select_Channel(const ADC *my_ADC,Adc_channel MY_CHANNEL);
Std_ReturnType Adc_START_CONVERSION(const ADC *my_ADC);
Std_ReturnType Adc_CONVERSION_STATUS(const ADC *my_ADC,uint8 *status);
Std_ReturnType Adc_get_CONVERSION_result(const ADC *my_ADC,uint16 *result);
Std_ReturnType Adc_get_CONVERSION_Looping(const ADC *my_ADC,uint16 *result,Adc_channel MY_CHANNEL);
Std_ReturnType Adc_START_CONVERSION_interrupt(const ADC *my_ADC,Adc_channel MY_CHANNEL);
#if ADC_INTERRUPT_MODE
Std_ReturnType ADC_ISR(void);
#endif
#endif	/* ADC_H */

