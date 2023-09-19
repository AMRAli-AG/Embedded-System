/* 
 * File:   ecu_seven_segmant_cfg.c
 * Author: Amr Ali
 *
 * Created on September 2, 2023, 3:17 AM
 */
#include"ecu_seven_segmant.h"
/**
 * 
 * @param seg
 * @return 
 */
std_ReturnType seven_segmant_intialize(const segmant_t *seg){
    std_ReturnType ret = E_OK ;
    if(NULL == seg ){
         ret = E_NOT_OK ;
    }
    else{
      ret = gpio_pin_intialize (&(seg->segmant_pin[0]) );
      ret = gpio_pin_intialize (&(seg->segmant_pin[1]) );
      ret = gpio_pin_intialize (&(seg->segmant_pin[2]) );
      ret = gpio_pin_intialize (&(seg->segmant_pin[3]) );
      ret = gpio_pin_intialize (&(seg->segmant_pin[4]) );
      ret = gpio_pin_intialize (&(seg->segmant_pin[5]) );
      ret = gpio_pin_intialize (&(seg->segmant_pin[6]) );

    }
    return ret;
}
/**
 * 
 * @param seg
 * @param number
 * @return 
 */
std_ReturnType seven_segmant_write_number(const segmant_t *seg,uint8 number){
       std_ReturnType ret = E_OK ;
    if(NULL == seg  ){
         ret = E_NOT_OK ;
    }
    else{
      ret = gpio_port_write_logic((seg->segmant_pin[0].port), number);
      ret = gpio_port_write_logic((seg->segmant_pin[1].port), number);
      ret = gpio_port_write_logic((seg->segmant_pin[2].port), number);
      ret = gpio_port_write_logic((seg->segmant_pin[3].port), number);
      ret = gpio_port_write_logic((seg->segmant_pin[3].port), number);
      ret = gpio_port_write_logic((seg->segmant_pin[5].port), number);
      ret = gpio_port_write_logic((seg->segmant_pin[6].port), number);
      

    }
    return ret;  
}

