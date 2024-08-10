/* 
 * File:   key_pad.c
 * Author: AHMED AKRAM
 *
 * Created on January 25, 2024, 9:46 PM
 */
#include "key_pad.h"

static const uint8 buttons_values[KEY_PAD_ROW][KEY_PAD_COLUMNS]=
{
    {'7','8','9','/'},
    {'4','5','6','x'},
    {'1','2','3','-'},
    {'c','0','=','+'},
};

/**
 * @param keypad_obj
 * @return 
 */
Std_ReturnType keypad_initialize(const Key_pad *keypad_obj)
{
    /* this because i dont know the keypad type*/
    uint8 rows_counter = 0;
    uint8 columns_counter = 0; 

    Std_ReturnType RET = E_OK;
   if(NULL==keypad_obj) 
   {
       RET=E_NOT_OK;
   }
   else
   {
       /* first make all rows pins as an output */
       for(rows_counter=0; rows_counter<KEY_PAD_ROW; rows_counter++)
       {
           RET=gpio_pin_initialize(&(keypad_obj->keypad_row[rows_counter]));
       }
       /* make all columns pins as an input */
     for(columns_counter=0; columns_counter<KEY_PAD_COLUMNS; columns_counter++)
       {
          RET=gpio_pin_direction_initialize(&(keypad_obj->keypad_columns[columns_counter]));
       }        
   }
    return RET;
}


/**
 *
 * @param keypad_obj
 * @param value
 * @return 
 */
Std_ReturnType keypad_get_value(const Key_pad *keypad_obj,volatile uint8 *value)
{
    uint8 rows_counter = 0;
    uint8 columns_counter = 0;
    uint8 counter = 0;
    logic_t check = low ;
    Std_ReturnType RET = E_OK;
   if(NULL==keypad_obj || NULL==value) 
   {
       RET=E_NOT_OK;
   }
   else
   {
       for(rows_counter=0; rows_counter<KEY_PAD_ROW; rows_counter++)
       {
           /* make sure  all rows first have zero volt  */
           for(counter=0;counter<KEY_PAD_ROW;counter++)
           {
               gpio_pin_write_logic(&(keypad_obj->keypad_row[counter]),low);
           }
           /* activate row by row while all other rows are not activated */
           gpio_pin_write_logic(&(keypad_obj->keypad_row[rows_counter]),high);
           
           for(columns_counter=0; columns_counter<KEY_PAD_COLUMNS; columns_counter++)
           {
               gpio_pin_read_logic(&(keypad_obj->keypad_columns[columns_counter]),&check);
               if(high==check)
               {
                   *value=buttons_values[rows_counter][columns_counter];
               }
           }
       }
   }
    return RET;
}