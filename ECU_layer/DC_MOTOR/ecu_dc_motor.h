/* 
 * File:   ecu_dc_motor.h
 * Author: AHMED AKRAM
 *
 * Created on September 27, 2023, 2:52 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H
/*-------------------------------includes-------------------------- : */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/*---------------------------macro declarations-------------------------- : */


/*----------------------------macro functions-------------------------- : */

/*-------------------------------data types-------------------------- : */
typedef enum 
{
    Motor_is_off,
    Motor_is_on        
}Motor_status;

typedef struct
{
    /*note that every motor is connected to 2 pins */
    pin_configration Motor_pin_1;
    pin_configration Motor_pin_2;
    Motor_status status_of_motor;
}MOTOR;

/*----------------------function declarations-------------------------- : */
Std_ReturnType Motor_initialize(const MOTOR *_motor);
Std_ReturnType Motor_move_forward(const MOTOR *_motor);
Std_ReturnType Motor_move_backward(const MOTOR *_motor);
Std_ReturnType Motor_stop(const MOTOR *_motor);



#endif	/* ECU_DC_MOTOR_H */

