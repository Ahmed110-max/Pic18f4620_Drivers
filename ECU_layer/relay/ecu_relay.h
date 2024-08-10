/* 
 * File:   ecu_relay.h
 * Author: AHMED AKRAM
 *
 * Created on September 22, 2023, 4:12 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H
/*-------------------------------includes-------------------------- : */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/*---------------------------macro declarations-------------------------- : */

/*----------------------------macro functions-------------------------- : */



/*-------------------------------data types-------------------------- : */
typedef enum 
{
    relay_is_off,
    relay_is_on        
}relay_status;

typedef struct
{
    pin_configration relay_pin;
    relay_status state_of_relay; 
}RELAY;

/*----------------------function declarations-------------------------- : */
Std_ReturnType relay_initialize(const RELAY *_relay);
Std_ReturnType relay_turn_on(const RELAY *_relay);
Std_ReturnType relay_turn_off(const RELAY *_relay);
#endif	/* ECU_RELAY_H */

