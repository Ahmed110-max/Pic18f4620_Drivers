/* 
 * File:   mcal_std_types.h
 * Author: AHMED AKRAM
 *
 * Created on September 14, 2023, 2:23 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H
/*-------------------------------includes-------------------------- : */
#include "std_libraries.h"
#include "compiler.h"


/*-------------------------------data types-------------------------- : */
typedef unsigned char uint8;    
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed char sint8;    
typedef signed short sint16;
typedef signed int sint32;
typedef uint8  Std_ReturnType;  /* AUTOSAR */
/*---------------------------macro declarations-------------------------- : */
#define STD_HIGH          0X01    
#define STD_LOW           0X00

#define STD_ON            0X01
#define STD_OFF           0X00

#define STD_ACTIVE        0x01
#define STD_IDLE          0x00

#define E_OK              (Std_ReturnType)0x01
#define E_NOT_OK          (Std_ReturnType)0x00

#define GPIO_CONFIG_ENABLE       0x01
#define GPIo_CONFIG_disable      0x00

/*----------------------function declarations-------------------------- : */

/*-----------------------macro functions-------------------------- : */

#endif	/* MCAL_STD_TYPES_H */

