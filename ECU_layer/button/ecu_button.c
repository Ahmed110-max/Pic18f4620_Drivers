/* 
 * File:   ecu_button.c
 * Author: AHMED AKRAM
 *
 * Created on September 20, 2023, 8:43 PM
 */

#include "ecu_button.h"


/**
 * @param button
 * @return 
 */
Std_ReturnType button_initialize(const BUTTON *button)
{
    Std_ReturnType ret=E_OK;
    if(NULL==button)
    {
        ret=E_NOT_OK;
    }
    else
    {
        ret=gpio_pin_direction_initialize(&(button->button_pin));
    }
    return ret;
}


/**
 * @param button
 * @param status
 * @return 
 */
Std_ReturnType button_read_status(const BUTTON *button,button_status *status)
{
    Std_ReturnType RET = E_OK;
    logic_t button_status;
    if( (NULL==button) || (NULL==status) )
    {
        RET = E_NOT_OK;
    }
    else
    {
          gpio_pin_read_logic(&(button->button_pin),&button_status);
          
        switch (button->type_of_button)
        {
            case BUTTON_ACTIVE_HIGH :
                
                if(low==button_status)
                {
                    *status=BUTTON_RELEASED;
                }
                else if(high==button_status)
                {
                    *status=BUTTON_PRESSED;
                }
                break;
            case BUTTON_ACTIVE_LOW :
                if(low==button_status)
                {
                    *status=BUTTON_PRESSED;
                }
                else if(high==button_status)
                {
                    *status=BUTTON_RELEASED;
                }
                break;       
        }
    }
    return RET;
}
