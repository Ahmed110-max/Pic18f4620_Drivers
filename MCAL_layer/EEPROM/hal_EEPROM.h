/* 
 * File:   hal_EEPROM.h
 * Author: AHMED AKRAM
 *
 * Created on February 12, 2024, 6:24 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H
/*-------------------------------includes-------------------------- : */
#include "../proc/pic18f46k20.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_interrupt_configration.h"
/*---------------------------macro declarations-------------------------- : */
#define ACCESS_EEPROM               0
#define ACCESS_FLASH                1

#define ACCESS_EEPROM_OR_FLASH      0
#define ACCESS_CONFIGRATION_BITS    1

#define Write_Enable                1
#define Write_disable               0

#define read_Enable                1
#define read_disable               0
/*----------------------------macro functions-------------------------- : */




/*-------------------------------data types-------------------------- : */



/*----------------------function declarations-------------------------- : */
Std_ReturnType EEPROM_WRITE_DATA(uint16 ADDR,uint8 DATA);
Std_ReturnType EEPROM_READ_DATA(uint16 ADDR,uint8 *DATA);
#endif	/* HAL_EEPROM_H */