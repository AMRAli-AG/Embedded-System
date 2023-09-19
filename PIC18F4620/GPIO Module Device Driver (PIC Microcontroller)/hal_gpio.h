/* 
 * File:   hal_gpio.h
 * Author: Amr Ali
 *
 * Created on August 25, 2023, 2:00 AM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H
//section includes //
#include"../../../../../../../Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC18Fxxxx_DFP/1.4.151/xc8/pic/include/proc/pic18f4620.h"
#include"../mcal_std_types.h"
#include"../device_config.h"
#include"hal_gpio_cfg.h"
//section macro deleration //
#define BIT_MASK (uint8)1
#define PORT_PIN_MAX_NUMBER 8
#define PORT_MAX_NUMBER     5

#define GPIO_PORT_PIN_CONFIGURATIONS  CONFIG_ENABLE 
#define GPIO_PORT_CONFIGURATIONS  CONFIG_ENABLE 


//section macro function //
#define HWREG8(_X)   (*((*volatile uint8 *)(_X)))
#define SET_BIT(REG ,BIT_POSN)      (REG |= (BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG ,BIT_POSN)    (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG ,BIT_POSN)   (REG ^= (BIT_MASK << BIT_POSN))

#define READ_BIT(REG ,BIT_POSN)  ((REG >> BIT_POSN) & BIT_MASK)
//section data type decleration //
typedef enum{
   GPIO_LOW =0,
   GPIO_HIGH
}logic_t;
typedef enum{
   GPIO_DIRECTION_OUTPUT =0,
   GPIO_DIRECTION_INPUT
}direction_t;
typedef enum{
    GPIO_PIN0 = 0,
    GPIO_PIN1 = 1,
    GPIO_PIN2 = 2,
    GPIO_PIN3 = 3,
    GPIO_PIN4 = 4,
    GPIO_PIN5 = 5,
    GPIO_PIN6 = 6,
    GPIO_PIN7 = 7 
}pin_index_t;
typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX ,
    PORTC_INDEX ,
    PORTD_INDEX ,
    PORTE_INDEX 
}port_index_t;
typedef struct {
    uint8 port : 3;        //@ref  port_index_t 
    uint8 pin : 3;         //@ref  pin_index_t
    uint8 direction : 1;   //@ref  direction_t
    uint8 logic :1;        //@ref  logic_t
}pin_confing_t;
//section function declaration //
std_ReturnType gpio_pin_direction_intialize (const pin_confing_t *_pin_config);
std_ReturnType gpio_pin_get_direction_status (const pin_confing_t *_pin_config,direction_t *direction_status );
std_ReturnType gpio_pin_write_logic(const pin_confing_t *_pin_config, logic_t logic);
std_ReturnType gpio_pin_read_logic (const pin_confing_t *_pin_config, logic_t *logic);
std_ReturnType gpio_pin_toggle_logic (const pin_confing_t *_pin_config);
std_ReturnType gpio_pin_intialize (const pin_confing_t *_pin_config);


std_ReturnType gpio_port_direction_intialize (port_index_t port,uint8 direction);
std_ReturnType gpio_port_direction_status (port_index_t port, uint8 *direction_status);
std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);
std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic);
std_ReturnType gpio_port_toggle_logic (port_index_t port);


#endif	/* HAL_GPIO_H */

