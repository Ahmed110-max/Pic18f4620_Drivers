/* 
 * File:   Ecu_initialize.c
 * Author: AHMED AKRAM
 *
 * Created on January 26, 2024, 2:58 AM
 */

#include "Ecu_initialize.h"

Lcd_4bit_mode lcd1 =
{
  .RS_pin.port = portD_index,
  .RS_pin.pin = pin0,
  .RS_pin.direction = output,
  .RS_pin.logic = low,
  
  .Enable_pin.port = portD_index,
  .Enable_pin.pin = pin1,
  .Enable_pin.direction = output,
  .Enable_pin.logic = low,
  
    .data_pins[0].port = portD_index,
    .data_pins[0].pin = pin2,
    .data_pins[0].direction = output,
    .data_pins[0].logic = low,
  
    .data_pins[1].port = portD_index,
    .data_pins[1].pin = pin3,
    .data_pins[1].direction = output,
    .data_pins[1].logic = low,
  
    .data_pins[2].port = portD_index,
    .data_pins[2].pin = pin4,
    .data_pins[2].direction = output,
    .data_pins[2].logic = low,
  
  
    .data_pins[3].port = portD_index,
    .data_pins[3].pin = pin5,
    .data_pins[3].direction = output,
    .data_pins[3].logic = low,
};



Lcd_8bit_mode lcd2 =
{
    .RS_pin.port = portC_index,
    .RS_pin.pin = pin6,
    .RS_pin.direction = output,
    .RS_pin.logic = low,
  
    .Enable_pin.port = portC_index,
    .Enable_pin.pin = pin7,
    .Enable_pin.direction = output,
    .Enable_pin.logic = low,
  
    .data_pins[0].port = portD_index,
    .data_pins[0].pin = pin0,
    .data_pins[0].direction = output,
    .data_pins[0].logic = low,
  
    .data_pins[1].port = portD_index,
    .data_pins[1].pin = pin1,
    .data_pins[1].direction = output,
    .data_pins[1].logic = low,
  
    .data_pins[2].port = portD_index,
    .data_pins[2].pin = pin2,
    .data_pins[2].direction = output,
    .data_pins[2].logic = low,
  
  
    .data_pins[3].port = portD_index,
    .data_pins[3].pin = pin3,
    .data_pins[3].direction = output,
    .data_pins[3].logic = low,
    
    .data_pins[4].port = portD_index,
    .data_pins[4].pin = pin4,
    .data_pins[4].direction = output,
    .data_pins[4].logic = low,
    
    .data_pins[5].port = portD_index,
    .data_pins[5].pin = pin5,
    .data_pins[5].direction = output,
    .data_pins[5].logic = low,
    
    .data_pins[6].port = portD_index,
    .data_pins[6].pin = pin6,
    .data_pins[6].direction = output,
    .data_pins[6].logic = low,
    
    .data_pins[7].port = portD_index,
    .data_pins[7].pin = pin7,
    .data_pins[7].direction = output,
    .data_pins[7].logic = low,
    
};




Key_pad keypad_1=
{
    .keypad_row[0].port = portC_index,
    .keypad_row[0].pin = pin0,
    .keypad_row[0].direction = output,
    .keypad_row[0].logic = low,
    
    .keypad_row[1].port = portC_index,
    .keypad_row[1].pin = pin1,
    .keypad_row[1].direction = output,
    .keypad_row[1].logic = low,
    
    .keypad_row[2].port = portC_index,
    .keypad_row[2].pin = pin2,
    .keypad_row[2].direction = output,
    .keypad_row[2].logic = low,
    
    .keypad_row[3].port = portC_index,
    .keypad_row[3].pin = pin3,
    .keypad_row[3].direction = output,
    .keypad_row[3].logic = low,
    
    .keypad_columns[0].port = portC_index,
    .keypad_columns[0].pin = pin4,
    .keypad_columns[0].direction = input,
    .keypad_columns[0].logic = low,
    
    .keypad_columns[1].port = portC_index,
    .keypad_columns[1].pin = pin5,
    .keypad_columns[1].direction = input,
    .keypad_columns[1].logic = low,

    .keypad_columns[2].port = portC_index,
    .keypad_columns[2].pin = pin6,
    .keypad_columns[2].direction = input,
    .keypad_columns[2].logic = low,

    .keypad_columns[3].port = portC_index,
    .keypad_columns[3].pin = pin7,
    .keypad_columns[3].direction = input,
    .keypad_columns[3].logic = low,    
};

LED_t LED1 =
{
    .port = portC_index,
    .pin = pin0,
    .led_status = LED_OFF
};

LED_t LED2 =
{
    .port = portC_index,
    .pin = pin1,
    .led_status = LED_OFF
};

LED_t LED3 =
{
    .port = portC_index,
    .pin = pin2,
    .led_status = LED_OFF
};

LED_t LED4 =
{
    .port = portC_index,
    .pin = pin3,
    .led_status = LED_OFF
};

BUTTON btn1 =
{
  .button_pin.port = portC_index,
  .button_pin.pin = pin7,
  .button_pin.direction = input,
  .type_of_button = BUTTON_ACTIVE_HIGH,
};


BUTTON btn2 =
{
  .button_pin.port = portD_index,
  .button_pin.pin = pin7,
  .button_pin.direction = input,
  .type_of_button = BUTTON_ACTIVE_HIGH,
};

MOTOR motor1 =
{
  .Motor_pin_1.port = portD_index,
  .Motor_pin_1.pin =   pin0,
  .Motor_pin_1.direction = output,
  
  .Motor_pin_2.port = portD_index,
  .Motor_pin_2.pin =   pin1,
  .Motor_pin_2.direction = output,
};


MOTOR motor2 =
{
  .Motor_pin_1.port = portD_index,
  .Motor_pin_1.pin =   pin2,
  .Motor_pin_1.direction = output,
  
  .Motor_pin_2.port = portD_index,
  .Motor_pin_2.pin =   pin3,
  .Motor_pin_2.direction = output,
};



void Ecu_initialize(void)
{
   
}




