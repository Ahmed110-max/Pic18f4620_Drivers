/* 
 * File:   ecu_7_segment.h
 * Author: AHMED AKRAM
 *
 * Created on September 27, 2023, 7:44 PM
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H
/*-------------------------------includes-------------------------- : */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/*---------------------------macro declarations-------------------------- : */

/* this to convert the number to bcd */
#define BCD_number(number)      (((uint8)(number/10)<<4) | ((uint8)number%10))
#define SEGMENT_PIN0                        0
#define SEGMENT_PIN1                        1
#define SEGMENT_PIN2                        2
#define SEGMENT_PIN3                        3
/*----------------------------macro functions-------------------------- : */

/*-------------------------------data types-------------------------- : */
typedef enum 
{
    common_cathode,
    common_anode  
}segment_type;

typedef struct
{
    /* NOTE THE 7_SEGMENT DECODER IS CONNECTED ON 4 PINS  */
    pin_configration segment_pins[4];
    segment_type type_of_segment;
}_7_SEGMENT;

/*----------------------function declarations-------------------------- : */
Std_ReturnType _7_segment_initialize(const _7_SEGMENT *segment);
Std_ReturnType  _7_segment_write_number(const _7_SEGMENT *segment ,uint8 number);

#endif	/* ECU_7_SEGMENT_H */




