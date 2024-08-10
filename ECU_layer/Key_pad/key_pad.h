/* 
 * File:   key_pad.h
 * Author: AHMED AKRAM
 *
 * Created on January 25, 2024, 9:46 PM
 */

#ifndef KEY_PAD_H
#define	KEY_PAD_H
/*-------------------------------includes-------------------------- : */
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/*---------------------------macro declarations-------------------------- : */
#define KEY_PAD_ROW                 4
#define KEY_PAD_COLUMNS             4

/*----------------------------macro functions-------------------------- : */

/*-------------------------------data types-------------------------- : */
typedef struct
{
    pin_configration keypad_row[KEY_PAD_ROW];
    pin_configration keypad_columns[KEY_PAD_COLUMNS];
}Key_pad;


/*----------------------function declarations-------------------------- : */
Std_ReturnType keypad_initialize(const Key_pad *keypad_obj);
Std_ReturnType keypad_get_value(const Key_pad *keypad_obj,volatile uint8 *value);
#endif	/* KEY_PAD_H */

