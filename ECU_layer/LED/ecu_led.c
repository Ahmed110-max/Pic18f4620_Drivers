/* 
 * File:   ecu_led.c
 * Author: AHMED AKRAM
 *
 * Created on September 14, 2023, 2:39 PM
 */

#include "ecu_led.h"

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_initialize(const LED_t *led)
{
    Std_ReturnType ret = E_OK;
     if(NULL==led)
    {
       ret = E_NOT_OK;
    }
    else
    {
         pin_configration led_pin =
         {
            .port = led->port,
            .pin = led->pin,
            .logic = led->led_status,
            .direction = output             
         };
 /* @brief initialize the pin as an output or an input and write 0 logic in it*/ 
         gpio_pin_initialize(&led_pin);
    }
    return ret;
}


/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_ON(const LED_t *led)
{
    Std_ReturnType ret = E_OK;
     if(NULL==led)
    {
       ret = E_NOT_OK;
    }
    else
    {
         pin_configration led_pin =
         {
            .port = led->port,
            .pin = led->pin,
            .logic = led->led_status,
            .direction = output             
         };
         gpio_pin_write_logic(&led_pin,high);
    }
    return ret;
}


/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_OFF(const LED_t *led)
{
    Std_ReturnType ret = E_OK;
     if(NULL==led)
    {
       ret = E_NOT_OK;
    }
    else
    {
         pin_configration led_pin =
         {
            .port = led->port,
            .pin = led->pin,
            .logic = led->led_status,
            .direction = output             
         };
         gpio_pin_write_logic(&led_pin,low);
    }
    return ret;
}


/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_toggle(const LED_t *led)
{
    Std_ReturnType ret = E_OK;
     if(NULL==led)
    {
       ret = E_NOT_OK;
    }
    else
    {
         pin_configration led_pin =
         {
            .port = led->port,
            .pin = led->pin,
            .logic = led->led_status,
            .direction = output             
         };
         gpio_pin_toggle(&led_pin);
    }    
    return ret;        
}