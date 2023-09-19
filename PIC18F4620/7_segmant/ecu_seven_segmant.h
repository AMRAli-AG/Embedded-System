/* 
 * File:   ecu_seven_segmant.h
 * Author: Amr Ali
 *
 * Created on September 2, 2023, 3:15 AM
 */

#ifndef ECU_SEVEN_SEGMANT_H
#define	ECU_SEVEN_SEGMANT_H
//section includes //
#define _XTAL_FREQ 500000

#include"../../MCAL_Layer/GPIO/hal_gpio.h"
#include"ecu_seven_segmant_cfg.h"

//section macro deleration //


//section macro function //

//section data type decleration //
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHOD
}segmant_type_t;

typedef struct{
    pin_confing_t segmant_pin[7];
    segmant_type_t segmant_type;
}segmant_t;
//section function declaration //
std_ReturnType seven_segmant_intialize(const segmant_t *seg);
std_ReturnType seven_segmant_write_number(const segmant_t *seg,uint8 number);


#endif	/* ECU_SEVEN_SEGMANT_H */

