/* 
 * File:   ecu_led.c
 * Author: Amr Ali
 *
 * Created on August 25, 2023, 2:22 AM
 */
#include"ecu_led.h"
/**
 * 
 * @param led
 * @return 
 */
std_ReturnType led_intialize(const led_t *led){
    std_ReturnType ret = E_OK ;
    pin_confing_t pin_obj = {.port = led->port_name,
                             .pin =led->pin, 
                             .direction = GPIO_DIRECTION_OUTPUT,
                             .logic = led->led_status
                            };
    if(NULL == led ){
         ret = E_NOT_OK ;
    }
    else{
         pin_confing_t pin_obj = {.port = led->port_name,
                             .pin =led->pin, 
                             .direction = GPIO_DIRECTION_OUTPUT,
                             .logic = led->led_status
                            };
        gpio_pin_intialize(&pin_obj);
        
    }
    return ret;
}
/**
 * 
 * @param led
 * @return 
 */
std_ReturnType led_turn_on (const led_t *led){
    std_ReturnType ret = E_OK ;
    if(NULL == led ){
         ret = E_NOT_OK ;
    }
    else{
         pin_confing_t pin_obj = {.port = led->port_name,
                             .pin =led->pin, 
                             .direction = GPIO_DIRECTION_OUTPUT,
                             .logic = led->led_status
                            };
         gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
        
    }
    return ret; 
    
}
/**
 * 
 * @param led
 * @return 
 */
std_ReturnType led_turn_off (const led_t *led){
    std_ReturnType ret = E_OK ;
    if(NULL == led ){
         ret = E_NOT_OK ;
    }
    else{
     pin_confing_t pin_obj = {.port = led->port_name,
                             .pin =led->pin, 
                             .direction = GPIO_DIRECTION_OUTPUT,
                             .logic = led->led_status
                            };
     gpio_pin_write_logic(&pin_obj, GPIO_LOW);
        
        
    }
    return ret;
}
/**
 * 
 * @param led
 * @return 
 */
std_ReturnType led_turn_toggel (const led_t *led){
    std_ReturnType ret = E_OK ;
    if(NULL == led ){
         ret = E_NOT_OK ;
    }
    else{
    pin_confing_t pin_obj = {.port = led->port_name,
                             .pin =led->pin, 
                             .direction = GPIO_DIRECTION_OUTPUT,
                             .logic = led->led_status
                            };
    gpio_pin_toggle_logic(&pin_obj);
           
        
    }
    return ret;
}