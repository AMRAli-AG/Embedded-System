/* 
 * File:   ecu_dc_motor.h
 * Author: Amr Ali
 *
 * Created on September 1, 2023, 2:34 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

//section includes //
#define _XTAL_FREQ 500000

#include"ecu_dc_motor_cfg.h"
#include"../../MCAL_Layer/GPIO/hal_gpio.h"

//section macro deleration //
#define DC_MOTOR_ON_STATUS 0x01U;
#define DC_MOTOR_Off_STATUS 0x00U;


//section macro function //

//section data type decleration //

typedef struct{
    pin_confing_t dc_motor[2];
}dc_motor_t;


//software interface  declaration //
std_ReturnType dc_motor_intalize(const dc_motor_t *_dc_motor );
std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor );
std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor );
std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor );

#endif	/* ECU_DC_MOTOR_H */

