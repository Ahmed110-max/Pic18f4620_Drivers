/* 
 * File:   ecu_button.h
 * Author: AHMED AKRAM
 *
 * Created on September 20, 2023, 8:43 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H
/*-------------------------------includes-------------------------- : */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/*---------------------------macro declarations-------------------------- : */


/*----------------------------macro functions-------------------------- : */



/*-------------------------------data types-------------------------- : */
typedef enum 
{
     BUTTON_RELEASED,
     BUTTON_PRESSED,
}button_status;

typedef enum 
{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW        
}button_type;

typedef struct
{
    pin_configration button_pin;
    button_status state_of_button ;
    button_type  type_of_button;   
}BUTTON;

/*----------------------function declarations-------------------------- : */
Std_ReturnType button_initialize(const BUTTON *button);
Std_ReturnType button_read_status(const BUTTON *button,button_status *status);

#endif	/* ECU_BUTTON_H */

