/* 
 * File:   hal_gpio.c
 * Author: AHMED AKRAM
 *
 * Created on September 13, 2023, 12:22 PM
 *
 */

#include "hal_gpio.h"

volatile uint8 *TRIS_REGESTERS[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8 *PORT_REGESTERS[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};
volatile uint8 *LAT_REGESTERS[]={&LATA,&LATB,&LATC,&LATD,&LATE};


#if GPIO_CONFIG_ENABLE
/**
 * 
 * @param pin
 * @return 
 */
Std_ReturnType gpio_pin_direction_initialize(const pin_configration *pin)
{
    Std_ReturnType RET = E_OK;
    if( (NULL==pin) || (pin->pin > PORT_MAX_PINS-1) )
    {
        RET = E_NOT_OK;
    }
    else
    {
        switch(pin->direction)
    {
        case output:
            clear_BIT(*TRIS_REGESTERS[pin->port],pin->pin);
            break;
        case input:
            SET_BIT(*TRIS_REGESTERS[pin->port],pin->pin);  
            break;
            default :
            RET = E_NOT_OK;
    }        
    }
 return   RET; 
}
#endif


#if GPIO_CONFIG_ENABLE
/**
 * 
 * @param pin
 * @param direction
 * @return 
 */
Std_ReturnType gpio_get_pin_direction_status(const pin_configration *pin,direction_t *direction)
{
    Std_ReturnType RET = E_OK;
    if(NULL==pin || NULL==direction )
    {
       RET = E_NOT_OK;
    }
    else
    {
        /* 1 -----> input   */
        *direction = READ_BIT(*TRIS_REGESTERS[pin->port],pin->pin);
        /* 0 -----> output  */ 
        
    }
    return RET;
}
#endif



#if GPIO_CONFIG_ENABLE
/**
 * 
 * @param pin
 * @param logic
 * @return 
 */
Std_ReturnType gpio_pin_write_logic(const pin_configration *pin,logic_t logic)
{
    Std_ReturnType RET = E_OK;
    if( (NULL==pin) || (pin->pin > PORT_MAX_PINS-1) )
    {
        RET = E_NOT_OK;
    }
    else
    {
        switch(logic)
        {
            case low :
                clear_BIT(*LAT_REGESTERS[pin->port],pin->pin);
                break;
                
            case high :
                SET_BIT(*LAT_REGESTERS[pin->port],pin->pin);
                break;
                
            default :
                RET = E_NOT_OK;
        }
    }
    return  RET;
}
#endif



#if GPIO_CONFIG_ENABLE
/**
 * 
 * @param pin
 * @param logic
 * @return 
 */
Std_ReturnType gpio_pin_read_logic(const pin_configration *pin,logic_t *logic)
{
     Std_ReturnType RET = E_OK;
    if(NULL==pin || NULL==logic )
    {
       RET = E_NOT_OK;
    }
    else
    {
        *logic = READ_BIT(*PORT_REGESTERS[pin->port],pin->pin);
    }
     return RET;
}
#endif


#if GPIO_CONFIG_ENABLE
/**
 * 
 * @param pin
 * @return 
 */
Std_ReturnType gpio_pin_toggle(const pin_configration *pin)
{
    Std_ReturnType RET = E_OK;
    if(NULL==pin)
    {
       RET = E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*LAT_REGESTERS[pin->port],pin->pin); 
    }
    return RET;
}
#endif




#if GPIO_CONFIG_ENABLE
/**
 * 
 * @param port
 * @param direction
 * @return 
 */
Std_ReturnType gpio_port_direction_initialize(port_index_t port,uint8 direction)
{
    Std_ReturnType RET = E_OK;
    if(port > MAX_PORT-1)
    {
        RET = E_NOT_OK;
    }
    else
    {
        *TRIS_REGESTERS[port]=direction;
    }
    return RET;
}
#endif



#if GPIO_CONFIG_ENABLE
/**
 * 
 * @param port
 * @param direction
 * @return 
 */
Std_ReturnType gpio_get_port_direction_status(port_index_t port,uint8 *direction)
{
    Std_ReturnType RET = E_OK;
    if(port > MAX_PORT-1 || NULL==direction)
    {
        RET = E_NOT_OK;
    }
    else
    {
        *direction =  *TRIS_REGESTERS[port];
    }
    return RET;
}
#endif



#if GPIO_CONFIG_ENABLE
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
Std_ReturnType gpio_port_write_logic(port_index_t port,uint8 logic)
{
    Std_ReturnType RET = E_OK;
    if(port > MAX_PORT-1 )
    {
        RET = E_NOT_OK;
    }
    else
    {
        *LAT_REGESTERS[port]=logic;
    }
    return RET;
}
#endif


#if GPIO_CONFIG_ENABLE
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
Std_ReturnType gpio_port_read_logic (port_index_t port,uint8 *logic)
{
    Std_ReturnType RET = E_OK;
    if(port > MAX_PORT-1 || NULL==logic)
    {
        RET = E_NOT_OK;
    }
    else
    {
        *logic=*LAT_REGESTERS[port];
    }
    return RET;
}

#endif



#if GPIO_CONFIG_ENABLE
/**
 * 
 * @param port
 * @return 
 */
Std_ReturnType gpio_port_toggle (port_index_t port)
{
    Std_ReturnType RET = E_OK;
    if(port > MAX_PORT-1 )
    {
        RET = E_NOT_OK;
    }
    else
    {
        *LAT_REGESTERS[port]^= 0xff ;/* this will toglle the whole port  */
    }
    return RET;
}
#endif



#if GPIO_CONFIG_ENABLE
/**
 * @brief initialize the pin as an output or an input and write 0 logic in it 
 * @param pin
 * @return 
 */
Std_ReturnType gpio_pin_initialize(const pin_configration *pin)
{
    Std_ReturnType RET = E_OK;
    if(NULL==pin)
    {
       RET = E_NOT_OK;
    }
    else
    {
        gpio_pin_direction_initialize(pin);
        gpio_pin_write_logic(pin,low);
    }
    return RET;
}
#endif
