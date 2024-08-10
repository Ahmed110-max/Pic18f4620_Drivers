/* 
 * File:   hal_gpio.h
 * Author: AHMED AKRAM
 *
 * Created on September 13, 2023, 12:22 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H
/*-------------------------------includes-------------------------- : */
#include "../mcal_std_types.h"
#include "../device_configration.h"
#include "../proc/pic18f46k20.h"


/*---------------------------macro declarations-------------------------- : */
#define BIT_MASK                        (uint8)1
#define PORT_MAX_PINS                       8
#define MAX_PORT                            5
#define _XTAL_FREQ                      8000000UL 
/*----------------------------macro functions-------------------------- : */
#define access_reg(_x)                  (*((volatile unsigned char * )(_x))) 
#define SET_BIT(reg,bit_pos)            reg|=(BIT_MASK<<bit_pos)
#define clear_BIT(reg,bit_pos)          reg&=~(BIT_MASK<<bit_pos)
#define TOGGLE_BIT(reg,bit_pos)         reg^=(BIT_MASK<<bit_pos)
/* read what in this bit 0 or 1 : */ 
#define READ_BIT(reg,bit_pos)           ((reg>>bit_pos)&BIT_MASK)

/*-------------------------------data types-------------------------- : */
typedef enum 
{
    low =0,
    high        
}logic_t;

typedef enum
{
    output =0,
    input,       
}direction_t;

typedef enum
{
    pin0,
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7        
}pin_index_t;

typedef enum
{
    portA_index,
    portB_index,
    portC_index,
    portD_index,
    portE_index
}port_index_t;


typedef struct 
{
    uint8 port       :3 ; /* @ref port_index_t  */
    uint8 pin        :3 ; /* @ref pin_index_t   */
    uint8 logic      :1 ; /* @ref logic_t       */  
    uint8 direction  :1 ; /* @ref direction_t   */
}pin_configration;
/*----------------------function declarations-------------------------- : */
Std_ReturnType gpio_pin_direction_initialize(const pin_configration *pin);
Std_ReturnType gpio_get_pin_direction_status(const pin_configration *pin,direction_t *direction);        
Std_ReturnType gpio_pin_write_logic(const pin_configration *pin,logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_configration *pin,logic_t *logic);
Std_ReturnType gpio_pin_toggle(const pin_configration *pin);
Std_ReturnType gpio_pin_initialize(const pin_configration *pin);


Std_ReturnType gpio_port_direction_initialize(port_index_t port,uint8 direction);
Std_ReturnType gpio_get_port_direction_status(port_index_t port,uint8 *direction);
Std_ReturnType gpio_port_read_logic (port_index_t port,uint8 *logic);
Std_ReturnType gpio_port_write_logic(port_index_t port,uint8 logic);
Std_ReturnType gpio_port_toggle (port_index_t port);
#endif	/* HAL_GPIO_H */

