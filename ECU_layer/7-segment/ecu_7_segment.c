/* 
 * File:   ecu_7_segment.c
 * Author: AHMED AKRAM
 *
 * Created on September 27, 2023, 7:44 PM
 */
#include "ecu_7_segment.h"
 


/**
 * 
 * @param segment
 * @return 
 */
Std_ReturnType _7_segment_initialize(const _7_SEGMENT *segment)
{
    Std_ReturnType ret=E_OK;
    if(NULL==segment)
    {
        ret=E_NOT_OK;
    }
    else
    {
        gpio_pin_initialize(&(segment->segment_pins[SEGMENT_PIN0]));
        gpio_pin_initialize(&(segment->segment_pins[SEGMENT_PIN1]));
        gpio_pin_initialize(&(segment->segment_pins[SEGMENT_PIN2]));
        gpio_pin_initialize(&(segment->segment_pins[SEGMENT_PIN3]));
    }
    return ret;
}

/**
 * 
 * @param segment
 * @param number
 * @return 
 */
Std_ReturnType  _7_segment_write_number(const _7_SEGMENT *segment ,uint8 number)
{
    Std_ReturnType ret=E_OK;
    if( NULL==segment || number>9 )
    {
        ret=E_NOT_OK;
    }
    else
    {
      gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN0]),number & 0x01);
      gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN1]),number>>1 & 0x01);
      gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN2]),number>>2 & 0x01);
      gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN3]),number>>3 & 0x01);
    }
    return ret;
}



