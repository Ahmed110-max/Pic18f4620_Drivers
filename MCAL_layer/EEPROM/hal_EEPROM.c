/* 
 * File:   hal_EEPROM.C
 * Author: AHMED AKRAM
 *
 * Created on February 12, 2024, 6:24 PM
 */

#include "hal_EEPROM.h"

Std_ReturnType EEPROM_WRITE_DATA(uint16 ADDR,uint8 DATA)
{
    Std_ReturnType RET = E_OK;
    /* READ INTERRUPT STATUS  */
    uint8 Interrupts_status =0;
    Interrupts_status = INTCONbits.GIE ;
    /* choose the location to write in  */
    EEADRH = ((ADDR>>8)&(0x03));
    EEADR = ((ADDR)&(0xff));
    /* write data */
    EEDATA = DATA;
    /* select EEPROM to write in (Flash Program or Data EEPROM Memory) */
    EECON1bits.EEPGD = ACCESS_EEPROM;
    /* select EEPROM to write in (Flash Program/Data EEPROM or Configuration Select bit) */
    EECON1bits.CFGS = ACCESS_EEPROM_OR_FLASH;
    /* Flash Program/Data EEPROM Write Enable bit (Enable writes) */
    EECON1bits.WREN = Write_Enable;
    /* Disable Interrupts */
    INTERRUPT_GLOBAL_Disables();
    /* Required Sequence According to Data Sheet */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Set WR bit to begin write
     * (*The bit is cleared by hardware once write is complete. 
      The WR bit can only be set (not cleared) by software} */
    EECON1bits.WR = 1;
    /* wait till write is complete */
    while(EECON1bits.WR);
    /* restore interrupts original condition  */
    INTCONbits.GIE = Interrupts_status;
    /*  (disable writes) */
    EECON1bits.WREN = Write_disable ;
    return RET;
}




Std_ReturnType EEPROM_READ_DATA(uint16 ADDR,uint8 *DATA)
{
    Std_ReturnType RET = E_OK;
    if( (NULL==DATA)  )
    {
        RET = E_NOT_OK;
    }
    else
    {
        /* choose the location to read from  */
        EEADRH = ((ADDR>>8)&(0x03));
        EEADR = ((ADDR)&(0xff));
        /* select EEPROM to write in (Flash Program or Data EEPROM Memory) */
        EECON1bits.EEPGD = ACCESS_EEPROM;
        /* select EEPROM to write in (Flash Program/Data EEPROM or Configuration Select bit) */
        EECON1bits.CFGS = ACCESS_EEPROM_OR_FLASH;
        /* Flash Program/Data EEPROM read Enable bit (Enable writes)
         * RD is cleared by hardware. The RD bit can only
        be set (not cleared) by software. RD bit cannot be set when EEPGD = 1 or CFGS = 1.)
          */
        EECON1bits.RD = read_Enable;
         /* wait till write is complete */
        NOP(); /* NO OPERATIOPN  */
        NOP(); /* NO OPERATIOPN  */
        *DATA = EEDATA ;
    }
    return RET;
}

