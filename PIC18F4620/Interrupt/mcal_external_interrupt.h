/* 
 * File:   mcal_external_interrupt.h
 * Author: Amr Ali
 *
 * Created on September 9, 2023, 3:19 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H
#include"mcal_interrupt_config.h"
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
 
//section includes //

//section macro deleration //

//0
#define EXT_INT0_IntrruptDisable()                (INTCONbits.INT0IE = 0)
#define EXT_INT0_IntrruptEnable()                 (INTCONbits.INT0IE = 1)
#define EXT_INT0_IntrruptFlagClear()              (INTCONbits.INT0IF = 0)
#define EXT_INT0_IntrruptRisingEdgeSet()          (INTCON2bits.INTEDG0 = 1)
#define EXT_INT0_IntrruptFallingEdgeSet()         (INTCON2bits.INTEDG0 = 0)
//1
#define EXT_INT1_IntrruptDisable()                (INTCON3bits.INT1IE = 0)
#define EXT_INT1_IntrruptEnable()                 (INTCON3bits.INT1IE = 1)
#define EXT_INT1_IntrruptFlagClear()              (INTCON3bits.INT1IF = 0)
#define EXT_INT1_IntrruptRisingEdgeSet()          (INTCON2bits.INTEDG1 = 1)
#define EXT_INT1_IntrruptFallingEdgeSet()         (INTCON2bits.INTEDG1 = 0)
//2
#define EXT_INT2_IntrruptDisable()                (INTCON3bits.INT2IE = 0)
#define EXT_INT2_IntrruptEnable()                 (INTCON3bits.INT2IE = 1)
#define EXT_INT2_IntrruptFlagClear()              (INTCON3bits.INT2IF = 0)
#define EXT_INT2_IntrruptRisingEdgeSet()          (INTCON2bits.INTEDG2 = 1)
#define EXT_INT2_IntrruptFallingEdgeSet()         (INTCON2bits.INTEDG2 = 0)
//3
#if INTERRUPT_PERIRITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define EXT_INT1_HighPrioritySet()                (INTCON3bits.INT1IP = 1)
#define EXT_INT1_LowPrioritySet()                 (INTCON3bits.INT1IP = 0)
#define EXT_INT2_HighPrioritySet()                (INTCON3bits.INT2IP = 0)
#define EXT_INT2_LowPrioritySet()                 (INTCON3bits.INT2IP = 0)
#endif
#define EXT_RBx_IntrruptDisable()                 (INTCONbits.RBIE = 0)
#define EXT_RBx_IntrruptEnable()                  (INTCONbits.RBIE = 1)
#define EXT_RBx_IntrruptFlagClear()               (INTCONbits.RBIF = 0)

#define EXT_RBx_Priority_High()                   (INTCON2bits.RBIP = 1) 
#define EXT_RBx_Priority_Low()                    (INTCON2bits.RBIP = 0)

//section macro function //
  
//section data type decleration //
typedef enum {
    INTERRUPT_FALLING_EDGE =0,
    INTERRUPT_RISING_EDGE        
}interrupt_INTx_edge;
typedef enum {
    INTERRUPT_EXTERNAL_INT0 =0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2 
}interrupt_INTx_src;
typedef struct {
    void(*EXT_InterruptHandeler)(void);
    pin_confing_t muc_pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_src source;
    interrupt_priority_cfg priority ;
}interrupt_INTx_t;

typedef struct{
    void(*EXT_InterruptHandeler_LOW)(void);
    void(*EXT_InterruptHandeler_HIGH)(void);
    pin_confing_t muc_pin;
    interrupt_priority_cfg priority ;
}interrupt_RBx_t;
//section function declaration //

std_ReturnType Interrupt_ITNx_Init(const interrupt_INTx_t *int_obj);
std_ReturnType Interrupt_ITNx_DeInit(const interrupt_INTx_t *int_obj);
std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj);
std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

