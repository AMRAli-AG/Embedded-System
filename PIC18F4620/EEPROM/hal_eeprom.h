/* 
 * File:   hal_eeprom.h
 * Author: Amr Ali
 *
 * Created on September 14, 2023, 2:11 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H
//section includes //

// <editor-fold defaultstate="collapsed" desc="comment">
#include"../../../../../../../Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC18Fxxxx_DFP/1.4.151/xc8/pic/include/proc/pic18f4620.h"// </editor-fold>
#include"../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include"../mcal_std_types.h"

//section macro deleration //
#define ACCESS_FLASH_PROGRAM_MEMORY 1
#define ACCESS_EEPROM_PROGRAM_MEMORY 0
#define ACCESS_CONFIG_REGISTAR     1
#define ACCESS_EEPROM_FLASH_MEMORY 0
#define ALLOW_WRITE_CYCLES_EEPROM_FLASH 1
#define INHIBIT_WRITE_CYCLES_EEPROM_FLASH 0
#define INITIATE_DATA_EEPROM_WRITE_ERASE 1
#define INITIATE_DATA_EEPROM_WRITE_COMPLETED 0
#define INITIATE_DATA_EEPROM_READ 1

//section macro function //

//section data type decleration //

//section function declaration //

 void Data_WriteByte(uint16 bAdd, uint8 bData);
std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);
#endif	/* HAL_EEPROM_H */

