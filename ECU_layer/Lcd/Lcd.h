/* 
 * File:   Lcd.h
 * Author: AHMED AKRAM
 *
 * Created on January 29, 2024, 11:05 PM
 */

#ifndef LCD_H
#define	LCD_H
/*-------------------------------includes-------------------------- : */
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/*---------------------------macro declarations-------------------------- : */
#define LCD_CLEAR                                 0x01

#define LCD_RETURN_HOME                           0x02

#define LCD_ENTRY_MODE_INC_SHIFT_OFF              0X06   
#define LCD_ENTRY_MODE_DEC_SHIFT_OFF              0X04
#define LCD_ENTRY_MODE_INC_SHIFT_ON               0X07
#define LCD_ENTRY_MODE_DEC_SHIFT_ON               0X05

#define LCD_DIPLAY_ON_CURSOR_ON                   0X0D
#define LCD_DIPLAY_ON_CURSOR_OFF                  0X0C

#define LCD_CURSOR_MOVE_RIGHT                     0X14
#define LCD_CURSOR_MOVE_LEFT                      0X10

#define LCD_DISPLAY_MOVE_RIGHT                    0X1C
#define LCD_DISPLAY_MOVE_LEFT                     0X18

#define LCD_8BIT_2LINE                            0X38
#define LCD_4BIT_2LINE                            0X28

#define LCD_CGRAM_START                           0X40
#define LCD_DDRAM_START                           0X80

#define ROW1                                      0X01
#define ROW2                                      0X02
#define ROW3                                      0X03
#define ROW4                                      0X04

#define ROW1_START_ADDRESS                        0X80
#define ROW2_START_ADDRESS                        0XC0
#define ROW3_START_ADDRESS                        0X94
#define ROW4_START_ADDRESS                        0XD4

/*----------------------------macro functions-------------------------- : */

/*-------------------------------data types-------------------------- : */
typedef struct
{
    pin_configration RS_pin ;
    pin_configration Enable_pin ;
    pin_configration data_pins[4];
    
}Lcd_4bit_mode;

typedef struct
{
    pin_configration RS_pin ;
    pin_configration Enable_pin ;
    pin_configration data_pins[8];
    
}Lcd_8bit_mode;


/*----------------------function declarations-------------------------- : */
Std_ReturnType lcd_4bit_initialize(const Lcd_4bit_mode *lcd); 
Std_ReturnType lcd_4bit_send_command (const Lcd_4bit_mode *lcd,uint8 command);
Std_ReturnType lcd_4bit_send_data(const Lcd_4bit_mode *lcd,uint8 data);
Std_ReturnType lcd_4bit_send_data_on_specific_position(const Lcd_4bit_mode *lcd,uint8 row,uint8 column,uint8 data);
Std_ReturnType lcd_4bit_send_string(const Lcd_4bit_mode *lcd,uint8 *string);
Std_ReturnType lcd_4bit_send_string_on_specific_position(const Lcd_4bit_mode *lcd,uint8 row,uint8 column,uint8 *string);
Std_ReturnType lcd_4bit_send_custome_char_on_specific_position(const Lcd_4bit_mode *lcd,uint8 row,
                                                     uint8 column,uint8 custome_char[],uint8 mem_pos);



Std_ReturnType lcd_8bit_initialize(const Lcd_8bit_mode *lcd); 
Std_ReturnType lcd_8bit_send_command (const Lcd_8bit_mode *lcd,uint8 command);
Std_ReturnType lcd_8bit_send_data(const Lcd_8bit_mode *lcd,uint8 data);
Std_ReturnType lcd_8bit_send_data_on_specific_position(const Lcd_8bit_mode *lcd,uint8 row,uint8 column,uint8 data);
Std_ReturnType lcd_8bit_send_string(const Lcd_8bit_mode *lcd,uint8 *string);
Std_ReturnType lcd_8bit_send_string_on_specific_position(const Lcd_8bit_mode *lcd,uint8 row,uint8 column,uint8 *string);
Std_ReturnType lcd_8bit_send_custome_char_on_specific_position(const Lcd_8bit_mode *lcd,uint8 row,
                                                       uint8 column,uint8 custome_char[],uint8 mem_pos);

Std_ReturnType convert_byte_to_string(uint8 value ,uint8 *string);
Std_ReturnType convert_short_to_string(uint16 value ,uint8 *string);
Std_ReturnType convert_int_to_string(uint32 value ,uint8 *string);
#endif	/* LCD_H */

