/* 
 * File:   ecu_relay.c
 * Author: AHMED AKRAM
 *
 * Created on September 22, 2023, 4:12 AM
 */

#include "ecu_relay.h"

/**
 * @param _relay
 * @return 
 */
Std_ReturnType relay_initialize(const RELAY *_relay)
{
    Std_ReturnType ret=E_OK;
    if(NULL==_relay)
    {
        ret=E_NOT_OK;
    }
    else
    {
        gpio_pin_initialize(&(_relay->relay_pin));
    }
    return ret;
}


/**
 * @param _relay
 * @return 
 */
Std_ReturnType relay_turn_on(const RELAY *_relay)
{
    Std_ReturnType ret=E_OK;
    if(NULL==_relay)
    {
        ret=E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_relay->relay_pin),high);
    }  
     return ret;
}


/**
 * @param _relay
 * @return 
 */
Std_ReturnType relay_turn_off(const RELAY *_relay)
{
    Std_ReturnType ret=E_OK;
    if(NULL==_relay)
    {
        ret=E_NOT_OK;
    }
    else
    {
         gpio_pin_write_logic(&(_relay->relay_pin),low);
    }
      return ret; 
}