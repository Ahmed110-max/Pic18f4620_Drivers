/* 
 * File:   ecu_led.h
 * Author: AHMED AKRAM
 *
 * Created on September 14, 2023, 2:39 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/*-------------------------------includes-------------------------- : */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/*---------------------------macro declarations-------------------------- : */


/*----------------------------macro functions-------------------------- : */



/*-------------------------------data types-------------------------- : */
typedef enum 
{
    LED_OFF,
    LED_ON       
}LED_STATUS;

typedef struct 
{
    uint8 port          :4;
    uint8 pin           :3;
    uint8 led_status    :1;
}LED_t;

/*----------------------function declarations-------------------------- : */
Std_ReturnType led_initialize(const LED_t *led);
Std_ReturnType led_ON(const LED_t *led);
Std_ReturnType led_OFF(const LED_t *led);
Std_ReturnType led_toggle(const LED_t *led);




#endif	/* ECU_LED_H */

