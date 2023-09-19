/* 
 * File:   ecu_led_cgg.h
 * Author: Amr Ali
 *
 * Created on August 30, 2023, 3:34 AM
 */

#ifndef ECU_LED_CGG_H
#define	ECU_LED_CGG_H
typedef unsigned char uint8;
typedef uint8 std_ReturnType;


//section includes //

//section macro function //

//section data type decleration //
typedef enum{
    LED_OFF,
    LED_ON        
}led_status_t;
typedef struct {
    uint8 port_name : 4;
    uint8 pin : 1;
    uint8 led_status : 1;
}led_t;
//section macro deleration //

//section function declaration //
std_ReturnType led_intialize(const led_t *led);
std_ReturnType led_turn_on (const led_t *led);
std_ReturnType led_turn_off (const led_t *led);
std_ReturnType led_turn_toggel (const led_t *led);
 
#endif	/* ECU_LED_CGG_H */

