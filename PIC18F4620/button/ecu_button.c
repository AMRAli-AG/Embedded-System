/* 
 * File:   ecu_button.c
 * Author: Amr Ali
 *
 * Created on August 31, 2023, 2:27 AM
 */
#include"ecu_button.h"

std_ReturnType button_initialize (const button_t *btn ){
    std_ReturnType ret = E_OK ;
    if(NULL == btn ){
         ret = E_NOT_OK ;
    }
    else{
     ret = gpio_pin_direction_intialize(&btn->button_bin);
    }
    return ret;
}
std_ReturnType button_read_state (const button_t *btn, button_state_t *button_state ){
      std_ReturnType ret = E_OK ;
      logic_t pin_logic_status =    GPIO_LOW ;
 
    if((NULL == btn) ||(NULL == button_state)){
         ret = E_NOT_OK ;
    }
    else{
        gpio_pin_read_logic(&(btn->button_bin), &pin_logic_status  );
        if(BUTTON_ACTIVE_HIGH == btn->button_connection){
            if(GPIO_HIGH == pin_logic_status ){
                *button_state = BUTTON_PRESSED;
            }
            else{
                 *button_state = BUTTON_RELEASED;

            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection){
                 if(GPIO_HIGH == pin_logic_status ){
                *button_state = BUTTON_RELEASED
;
            }
            else{
                 *button_state = BUTTON_PRESSED;
            }
        }
        else{/*nothing*/}
        ret = E_OK ;
    }
    return ret;  
    
}
