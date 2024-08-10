/* 
 * File:   ecu_dc_motor.c
 * Author: AHMED AKRAM
 *
 * Created on September 27, 2023, 2:52 AM
 */

#include "ecu_dc_motor.h"


/**
 * @param _motor
 * @return 
 */

Std_ReturnType Motor_initialize(const MOTOR *_motor)
{
    Std_ReturnType ret = E_OK;
    if(NULL==_motor)
    {
        ret=E_NOT_OK;
    }
    else
    {
        gpio_pin_initialize(&(_motor->Motor_pin_1));
        gpio_pin_initialize(&(_motor->Motor_pin_2));
    }
    return ret;
}

/**
 * @param _motor
 * @return 
 */

Std_ReturnType Motor_move_forward(const MOTOR *_motor)
{
    Std_ReturnType ret=E_OK;
    if(NULL==_motor)
    {
        ret=E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_motor->Motor_pin_1),high);
        gpio_pin_write_logic(&(_motor->Motor_pin_2),low);
    }
    return ret;
}

/**
 * @param _motor
 * @return 
 */

Std_ReturnType Motor_move_backward(const MOTOR *_motor)
{
    Std_ReturnType ret=E_OK;
    if(NULL==_motor)
    {
        ret=E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_motor->Motor_pin_1),low);
        gpio_pin_write_logic(&(_motor->Motor_pin_2),high);
    }
    return ret;
}

/**
 * @param _motor
 * @return 
 */

Std_ReturnType Motor_stop(const MOTOR *_motor)
{
    Std_ReturnType ret=E_OK;
    if(NULL==_motor)
    {
        ret=E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_motor->Motor_pin_1),low);
        gpio_pin_write_logic(&(_motor->Motor_pin_2),low);
    }
    return ret;
}

