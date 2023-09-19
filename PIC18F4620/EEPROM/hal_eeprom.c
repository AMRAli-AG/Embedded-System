/* 
 * File:   hal_eeprom.c
 * Author: Amr Ali
 *
 * Created on September 14, 2023, 2:11 AM
 */
#include"hal_eeprom.h"

void Data_WriteByte(uint16 bAdd, uint8 bData){
    std_ReturnType ret = E_NOT_OK ;

    if(NULL == bData ){
        ret = E_NOT_OK ;
    }
     else{
    std_ReturnType ret = E_OK ;
    uint8 glopal_intarrupt = INTCONbits.GIE;
    
    EEADRH = (uint8)((bAdd >> 8) & 0x03);
    EEADR = (uint8) (bAdd & 0xFF);
    
    EEDATA = bData;
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_EEPROM_FLASH_MEMORY;
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_EEPROM_FLASH;
    INTCONbits.GIE = 0;//INTERRUPT
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    while(EECON1bits.WR);
    EECON1bits.WREN = INHIBIT_WRITE_CYCLES_EEPROM_FLASH;

     }
    
    
    
       
    
}
std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData){
     std_ReturnType ret = E_NOT_OK ;
    if(NULL == bData ){
        ret = E_NOT_OK ;
    }
    else{
        EEADRH = (uint8)((bAdd >> 8) & 0x03);
        EEADR = (uint8) (bAdd & 0xFF);
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_EEPROM_FLASH_MEMORY;
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        NOP();
        NOP();
        *bData = EEDATA;
    ret = E_OK ;
    }
    return ret;    
    
    
}