/* 
 * File:   hal_timer0.h
 * Author: Amr Ali
 *
 * Created on September 20, 2023, 1:56 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

//section includes //    
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
#include"../mcal_std_types.h"
#include"../../../../../../../Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC18Fxxxx_DFP/1.4.151/xc8/pic/include/proc/pic18f4620.h"
#include"../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include"../../MCAL_Layer/Interrupt/mcal_interrupt_config.h"
#include"../../MCAL_Layer/Interrupt/mcal_interrupt_manager.h"

//section macro deleration //
#define TIMER0_PRESCALER_ENABLE_CFG       1
#define TIMER0_PRESCALER_DISABLE_CFG      0
#define TIMER0_RISING_EDGE_CFG            1
#define TIMER0_FALLING_EDGEE_CFG          0
#define TIMER0_TIMER_MODE                 1
#define TIMER0_COUNTER_MODE               0
#define TIMER0_8_BIT_REGESTER_MODE        1
#define TIMER0_16_BIT_REGESTER_MODE       0

//section macro function //
#define TIMER0_PRESCALER_ENABLE()              (T0CONbits.PSA = 0 )
#define TIMER0_PRESCALER_DISABLE()             (T0CONbits.PSA = 1 )
#define TIMER0_RISING_EDGE_ENABLE()            (T0CONbits.T0SE = 0 )
#define TIMER0_FALLING_EDGE_ENABLE()           (T0CONbits.T0SE = 1 )
#define TIMER0_TIMER_MODE_ENABLE()             (T0CONbits.T0CS = 0 )
#define TIMER0_COUNTER_MODE_ENABLE()           (T0CONbits.T0CS = 1 )
#define TIMER0_8BIT_REGISTER_MODE_ENABLE()     (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGISTER_MODE_ENABLE()    (T0CONbits.T08BIT = 0)
#define TIMER0_MODULE_ENABLE()                 (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()                (T0CONbits.TMR0ON = 0)

//section data type decleration //
typedef enum {
    TIMER0_PRESCALER_DIV_BY_2,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256 
}timer0_prescaler_select_t;

typedef struct{
    
#if TIMER0_INTERRUPT_FEATURE_ENADBLE == INTERRUPT_FEATURE_ENABLE
    void(*TMR0_InterruptHandeller)(void);
    interrupt_priority_cfg priority ;
#endif
    timer0_prescaler_select_t prescaler_value;
    uint8 prescaler_enable : 1;
    uint8 timer0_counter_edge : 1;
    uint8 timer0_mode : 1;
    uint8 timer0_regestaer_size : 1; 
    uint16 timer0_peroled_value ;
    uint8 timer0_reserved : 4; 

    
}timer0_t;
//section function declaration //
std_ReturnType Timer0_Init(const timer0_t *_timer);
std_ReturnType Timer0_DeInit(const timer0_t *_timer);
std_ReturnType Timer0_Write_value(const timer0_t *_timer, uint16 _value);
std_ReturnType Timer0_Read_value(const timer0_t *_timer, uint16 *_value);



#endif	/* HAL_TIMER0_H */

