/* 
 * File:   hal_timer1.h
 * Author: Amr Ali
 *
 * Created on September 22, 2023, 6:36 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

//section includes //    
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
#include"../mcal_std_types.h"
#include"../../../../../../../Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC18Fxxxx_DFP/1.4.151/xc8/pic/include/proc/pic18f4620.h"
#include"../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include"../../MCAL_Layer/Interrupt/mcal_interrupt_config.h"
#include"../../MCAL_Layer/Interrupt/mcal_interrupt_manager.h"

//section macro deleration //
#define TIMER1_COUNTER_MODE               1
#define TIMER1_TIMER_MODE                 0

#define TIMER1_ASYNC_COUNTER_MODE         1
#define TIMER1_SYNC_COUNTER_MODE          0

#define TIMER1_OSC_ENABLE  1
#define TIMER1_OSC_DISABLE 0

#define TIMER1_PRESCALER_DIV_BY_1         0
#define TIMER1_PRESCALER_DIV_BY_2         1
#define TIMER1_PRESCALER_DIV_BY_4         2
#define TIMER1_PRESCALER_DIV_BY_8         3

#define TIMER1_RW_REG_16BIT_MODE          1
#define TIMER1_RW_REG_8BIT_MODE           0

//section macro function //
#define TIMER1_MODULE_ENABLE()                 (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()                (T1CONbits.TMR1ON = 0)

#define TIMER1_TIMER_MODE_ENABLE()             (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()           (T1CONbits.TMR1CS = 1)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()     (T1CONbits.T1SYNC= 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()      (T1CONbits.T1SYNC =0)

#define TIMER1_OSC_HW_ENABLE()                   (T1CONbits.T1OSCEN =1)
#define TIMER1_OSC_HW_DISABLE()                  (T1CONbits.T1OSCEN =0)

#define TIMER1_PRESCALER_SELECT(_PRESCALER_)      (T1CONbits.T1CKPS =_PRESCALER_)

#define TIMER1_SYSTEM_CLK_STATUS()                (T1CONbits.T1RUN)

#define TIMER1_RW_REG_8BIT_MODE_ENABLE ()         (T1CONbits.RD16 = 0)
#define TIMER1_RW_REG_16BIT_MODE_ENABLE ()        (T1CONbits.RD16 = 1)


//section data type decleration //
typedef struct{
#if TIMER1_INTERRUPT_FEATURE_ENADBLE == INTERRUPT_FEATURE_ENABLE
    void(*TMR1_InterruptHandeller)(void);
    interrupt_priority_cfg priority ;
#endif   
    uint16 timer0_peroled_value ;
    uint8 timer1_prescaler_value : 2;
    uint8 timer1_mode : 1;
    uint8 timer1_counter_mode : 1;
    uint8 timer1_osc_cfg : 1;
    uint8 timer1_reg_rw_mode : 1;
    uint8 timer0_reserved : 2; 
}timer1_t;
//section function declaration //
std_ReturnType Timer1_Init(const timer1_t *_timer);
std_ReturnType Timer1_DeInit(const timer1_t *_timer);
std_ReturnType Timer1_Write_value(const timer1_t *_timer, uint16 _value);
std_ReturnType Timer1_Read_value(const timer1_t *_timer, uint16 *_value);




#endif	/* HAL_TIMER1_H */

