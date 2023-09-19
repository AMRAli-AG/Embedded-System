/* 
 * File:   mcal_interrupt_manager.h
 * Author: Amr Ali
 *
 * Created on September 9, 2023, 3:22 AM
 */
#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H


#include"mcal_interrupt_config.h"
#include"../../MCAL_Layer/GPIO/hal_gpio.h"


//section includes //

//section macro deleration //


//section macro function //

//section data type decleration //
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB4_SOURCE);
void RB5_ISR(uint8 RB5_SOURCE);
void RB6_ISR(uint8 RB6_SOURCE);
void RB7_ISR(uint8 RB7_SOURCE);
void ADC_ISR(void);
//section function declaration //


#endif	/* MCAL_INTERRUPT_MANAGER_H */

