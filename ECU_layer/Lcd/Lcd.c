/* 
 * File:   Lcd.c
 * Author: AHMED AKRAM
 *
 * Created on January 29, 2024, 11:05 PM
 */

#include "Lcd.h"

static Std_ReturnType lcd_4bit_send_enable_signal(const Lcd_4bit_mode *lcd);
static Std_ReturnType lcd_8bit_send_enable_signal(const Lcd_8bit_mode *lcd);
static Std_ReturnType lcd_4bit_send_data_command(const Lcd_4bit_mode *lcd,uint8 command_data);
static Std_ReturnType lcd_8bit_set_cursor(const Lcd_8bit_mode *lcd,uint8 row,uint8 column);
static Std_ReturnType lcd_4bit_set_cursor(const Lcd_4bit_mode *lcd,uint8 row,uint8 column);



Std_ReturnType lcd_4bit_initialize(const Lcd_4bit_mode *lcd)
{
    Std_ReturnType RET = E_OK;
    uint8 counter = 0;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        RET=gpio_pin_initialize(&(lcd->RS_pin));
        RET=gpio_pin_initialize(&(lcd->Enable_pin));
        for(counter=0;counter<4;counter++)
        {
            RET=gpio_pin_initialize(&(lcd->data_pins[counter]));
        }
        /* i will start to initialize the lcd according to the table in slides */
        __delay_ms(20);
        lcd_4bit_send_command(lcd,LCD_8BIT_2LINE);
        __delay_ms(5);
        lcd_4bit_send_command(lcd,LCD_8BIT_2LINE);
        __delay_us(150);
         lcd_4bit_send_command(lcd,LCD_8BIT_2LINE); 
         /* now do the basic commands */
         lcd_4bit_send_command(lcd,LCD_CLEAR); 
         lcd_4bit_send_command(lcd,LCD_CLEAR);
         lcd_4bit_send_command(lcd,LCD_RETURN_HOME);
         lcd_4bit_send_command(lcd,LCD_ENTRY_MODE_INC_SHIFT_OFF);
         lcd_4bit_send_command(lcd,LCD_DIPLAY_ON_CURSOR_OFF);
         /* here is where we make it 4 bit mode */
          lcd_4bit_send_command(lcd,LCD_4BIT_2LINE);
          lcd_4bit_send_command(lcd,LCD_RETURN_HOME);
          lcd_4bit_send_command(lcd,LCD_CLEAR);
    }    
      return RET;
}


Std_ReturnType lcd_4bit_send_command (const Lcd_4bit_mode *lcd,uint8 command)
{
    Std_ReturnType RET = E_OK;
    uint8 counter = 0;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(lcd->RS_pin),low);
        lcd_4bit_send_data_command(lcd,command>>4);
        lcd_4bit_send_enable_signal(lcd);
        lcd_4bit_send_data_command(lcd,command);
        lcd_4bit_send_enable_signal(lcd);
    }
    return RET;
}



Std_ReturnType lcd_4bit_send_data(const Lcd_4bit_mode *lcd,uint8 data)
{
    Std_ReturnType RET = E_OK;
    uint8 counter = 0;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(lcd->RS_pin),high);
        lcd_4bit_send_data_command(lcd,data>>4);
        lcd_4bit_send_enable_signal(lcd);
        lcd_4bit_send_data_command(lcd,data);
        lcd_4bit_send_enable_signal(lcd);
    }
    return RET;
}


Std_ReturnType lcd_4bit_send_data_on_specific_position(const Lcd_4bit_mode *lcd,uint8 row,uint8 column,uint8 data)
{
    Std_ReturnType RET = E_OK;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        lcd_4bit_set_cursor(lcd,row,column);
        lcd_4bit_send_data(lcd,data);
    }
    return RET;
}



Std_ReturnType lcd_4bit_send_string(const Lcd_4bit_mode *lcd,uint8 *string)
{
    Std_ReturnType RET = E_OK;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        while(*string)
        {
            lcd_4bit_send_data(lcd,*string++);
        }
    }
    return RET;
}





Std_ReturnType lcd_4bit_send_string_on_specific_position(const Lcd_4bit_mode *lcd,uint8 row,uint8 column,uint8 *string)
{
    Std_ReturnType RET = E_OK;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        
        lcd_4bit_set_cursor(lcd,row,column);
        lcd_4bit_send_string(lcd,string);    
    }
}




Std_ReturnType lcd_4bit_send_custome_char_on_specific_position(const Lcd_4bit_mode *lcd,uint8 row,
                                                     uint8 column,uint8 custome_char[],uint8 mem_pos)
{
    Std_ReturnType RET = E_OK;
    uint8 counter = 0;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        /* access to cgram*/
        lcd_4bit_send_command(lcd,(LCD_CGRAM_START + mem_pos*8));
        /* write data to cgram and store custome char in it */
        for(counter=0;counter<=7;counter++)
        {
            lcd_4bit_send_data(lcd,custome_char[counter]);
        }
        /* show char on lcd from cgram */
        lcd_4bit_send_data_on_specific_position(lcd,row,column,mem_pos);
    } 
    return RET;
}








Std_ReturnType lcd_8bit_initialize(const Lcd_8bit_mode *lcd)
{
    Std_ReturnType RET = E_OK;
    uint8 counter = 0;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        RET=gpio_pin_initialize(&(lcd->RS_pin));
        RET=gpio_pin_initialize(&(lcd->Enable_pin));
        for(counter=0;counter<8;counter++)
        {
            RET=gpio_pin_initialize(&(lcd->data_pins[counter]));
        }
       /* i will start to initialize the lcd according to the table in slides */
        __delay_ms(20);
        lcd_8bit_send_command(lcd,LCD_8BIT_2LINE);
        __delay_ms(5);
        lcd_8bit_send_command(lcd,LCD_8BIT_2LINE);
        __delay_us(150);
         lcd_8bit_send_command(lcd,LCD_8BIT_2LINE); 
         /* now do the basic commands */
         lcd_8bit_send_command(lcd,LCD_CLEAR); 
         lcd_8bit_send_command(lcd,LCD_RETURN_HOME);
         lcd_8bit_send_command(lcd,LCD_ENTRY_MODE_INC_SHIFT_OFF);
         lcd_8bit_send_command(lcd,LCD_DIPLAY_ON_CURSOR_OFF);
    }
     return RET;
}




Std_ReturnType lcd_8bit_send_command (const Lcd_8bit_mode *lcd,uint8 command)
{
    Std_ReturnType RET = E_OK;
    uint8 counter = 0;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(lcd->RS_pin),low);
        for(counter=0;counter<8;counter++)
        {
            gpio_pin_write_logic(&(lcd->data_pins[counter]),(command>>counter)&0x01);
        }
        lcd_8bit_send_enable_signal(lcd);
    } 
    return RET;
}




Std_ReturnType lcd_8bit_send_data(const Lcd_8bit_mode *lcd,uint8 data)
{
    Std_ReturnType RET = E_OK;
    uint8 counter = 0;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(lcd->RS_pin),high);
        for(counter=0;counter<8;counter++)
        {
            gpio_pin_write_logic(&(lcd->data_pins[counter]),(data>>counter)&0x01);
        }
        lcd_8bit_send_enable_signal(lcd);
    } 
    return RET;
}





Std_ReturnType lcd_8bit_send_data_on_specific_position(const Lcd_8bit_mode *lcd,uint8 row,uint8 column,uint8 data)
{
    Std_ReturnType RET = E_OK;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        lcd_8bit_set_cursor(lcd,row,column);
        lcd_8bit_send_data(lcd,data);
        
    } 
    return RET;
}




Std_ReturnType lcd_8bit_send_string(const Lcd_8bit_mode *lcd,uint8 *string)
{
    Std_ReturnType RET = E_OK;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        /* hna kda L STRING DH INSIDE IT HAS THE ADDREESS OF THE FISRT CHAR OF THE STRING
         * WHEN WE ++ IT IT GOES TO THE NEXT CHAR UNTIL IT REACHES NULL 
         * AFTER IT REACH NULL IT WILL EXIT THE WHILE LOOP   */
        while(*string)
        {
           RET=lcd_8bit_send_data(lcd,*string++);
        }
        
    } 
    return RET;
}





Std_ReturnType lcd_8bit_send_string_on_specific_position(const Lcd_8bit_mode *lcd,uint8 row,uint8 column,uint8 *string)
{
    Std_ReturnType RET = E_OK;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        lcd_8bit_set_cursor(lcd,row,column);
        lcd_8bit_send_string(lcd,string);
        
    } 
    return RET;
}




/**
 * @param lcd
 * @param row
 * @param column
 * @param custome_char
 * @param mem_pos        we have 8 positions (0 ---> 7) 
 * @return 
 */
Std_ReturnType lcd_8bit_send_custome_char_on_specific_position(const Lcd_8bit_mode *lcd,uint8 row,
                                                       uint8 column,uint8 custome_char[],uint8 mem_pos)
{
    Std_ReturnType RET = E_OK;
    uint8 counter = 0;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        /* access to cgram*/
        lcd_8bit_send_command(lcd,(LCD_CGRAM_START + mem_pos*8));
        /* write data to cgram and store custome char in it */
        for(counter=0;counter<=7;counter++)
        {
            lcd_8bit_send_data(lcd,custome_char[counter]);
        }
        /* show char on lcd from cgram */
        lcd_8bit_send_data_on_specific_position(lcd,row,column,mem_pos);
    } 
}






Std_ReturnType convert_byte_to_string(uint8 value ,uint8 *string)
{
    Std_ReturnType RET = E_OK;
    if( NULL==string )
    {
        RET = E_NOT_OK;
    }
    else
    {
        memset(string,'\0',4);
        sprintf(string,"%i",value);
        
    } 
    return RET;
}




Std_ReturnType convert_short_to_string(uint16 value ,uint8 *string)
{
    
    Std_ReturnType RET = E_OK;
    uint8 dummy[6]={0};/* all elements are 0 */
    uint8 counter=0;
    if( NULL==string )
    {
        RET = E_NOT_OK;
    }
    else
    {
        memset(string,' ',5); /*string={" "," "," "," "," "," "}*/
        string[5]='\0'; /*string={" "," "," "," "," ","\0"}*/
        sprintf(dummy,"%i",value); /* if value is 213 >> dummy={"2","1","3","\0","\0","\0"}*/  
        while(dummy[counter]!='\0')
        {
            string[counter]=dummy[counter]; /*string={"2","1","3"," "," ","\0"}*/
            counter++;
        }
    } 
    return RET;
}



Std_ReturnType convert_int_to_string(uint32 value ,uint8 *string)
{
    
    Std_ReturnType RET = E_OK;
    if( NULL==string )
    {
        RET = E_NOT_OK;
    }
    else
    {
        memset(string,'\0',11);
        sprintf(string,"%i",value);
        
    } 
    return RET;
}



static Std_ReturnType lcd_4bit_send_enable_signal(const Lcd_4bit_mode *lcd)
{
    Std_ReturnType RET = E_OK;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(lcd->Enable_pin),high);
        __delay_us(5);
        gpio_pin_write_logic(&(lcd->Enable_pin),low);      
    }
    return RET;
}




static Std_ReturnType lcd_8bit_send_enable_signal(const Lcd_8bit_mode *lcd)
{
    Std_ReturnType RET = E_OK;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(lcd->Enable_pin),high);
        __delay_us(5);
        gpio_pin_write_logic(&(lcd->Enable_pin),low);      
    }
    return RET;
}





static Std_ReturnType lcd_4bit_send_data_command(const Lcd_4bit_mode *lcd,uint8 command_data)
{
    uint8 counter =0;
    Std_ReturnType RET = E_OK;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        for(counter=0;counter<4;counter++)
        {
            gpio_pin_write_logic(&(lcd->data_pins[counter]),(command_data>>counter)&0x01);
        }
    }
     return RET;
}




static Std_ReturnType lcd_8bit_set_cursor(const Lcd_8bit_mode *lcd,uint8 row,uint8 column)
{
    Std_ReturnType RET = E_OK;
    column--;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        switch(row)
        {
            case ROW1 : 
                lcd_8bit_send_command(lcd, (ROW1_START_ADDRESS) + column );
                break;
                
            case ROW2 : 
                lcd_8bit_send_command(lcd, (ROW2_START_ADDRESS) + column );
                break;    
            case ROW3 : 
                lcd_8bit_send_command(lcd, (ROW3_START_ADDRESS) + column );
                break;
            case ROW4 : 
                lcd_8bit_send_command(lcd, (ROW4_START_ADDRESS) + column );
                break;    
                
        }
    }
    return RET;
}



static Std_ReturnType lcd_4bit_set_cursor(const Lcd_4bit_mode *lcd,uint8 row,uint8 column)
{
    Std_ReturnType RET = E_OK;
    column--;
    if( NULL==lcd )
    {
        RET = E_NOT_OK;
    }
    else
    {
        switch(row)
        {
            case ROW1 : 
                lcd_4bit_send_command(lcd, (ROW1_START_ADDRESS) + column );
                break;
                
            case ROW2 : 
                lcd_4bit_send_command(lcd, (ROW2_START_ADDRESS) + column );
                break;    
            case ROW3 : 
                lcd_4bit_send_command(lcd, (ROW3_START_ADDRESS) + column );
                break;
            case ROW4 : 
                lcd_4bit_send_command(lcd, (ROW4_START_ADDRESS) + column );
                break;         
        }
    }
    return RET;
}
