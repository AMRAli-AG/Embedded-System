/* 
 * File:   euc_kaypad.h
 * Author: Amr Ali
 *
 * Created on September 3, 2023, 2:05 AM
 */

#ifndef EUC_KAYPAD_H
#define	EUC_KAYPAD_H

//section includes //
#define _XTAL_FREQ 500000

#include"euc_kaypad_cfg.h"
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
//section macro deleration //
#define EUC_KAYPAD_ROW 4
#define EUC_KAYPAD_COLUMNS 4

//section macro function //

//section data type decleration //
typedef struct {
    pin_confing_t kaypad_row_pin[EUC_KAYPAD_ROW];
    pin_confing_t kaypad_columns_pin[EUC_KAYPAD_COLUMNS];
}kaypad_t;
//section function declaration //
std_ReturnType kaypad_intialize(const kaypad_t *kaypad_obj);
std_ReturnType kaypad_get_value (const kaypad_t *kaypad_obj, uint8 *value);


#endif	/* EUC_KAYPAD_H */

