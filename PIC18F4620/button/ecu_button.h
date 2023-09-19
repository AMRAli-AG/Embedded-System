/* 
 * File:   ecu_button.h
 * Author: Amr Ali
 *
 * Created on August 31, 2023, 2:27 AM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

//section includes //
#define _XTAL_FREQ 500000

#include"../../MCAL_Layer/GPIO/hal_gpio.h"
#include"ecu_button_cfg.h"
//section macro deleration //


//section macro function //

//section data type decleration //
typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED
}button_state_t;

typedef enum {
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;
typedef struct{
    pin_confing_t button_bin;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;

//software interface  declaration //
std_ReturnType button_initialize (const button_t *btn );
std_ReturnType button_read_state (const button_t *btn, button_state_t *button_state );


#endif	/* ECU_BUTTON_H */

