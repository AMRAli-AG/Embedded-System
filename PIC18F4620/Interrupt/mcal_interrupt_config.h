/* 
 * File:   mcal_interrupt_config.h
 * Author: Amr Ali
 *
 * Created on September 9, 2023, 3:21 AM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H
//section includes //
#include"../../../../../../../Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC18Fxxxx_DFP/1.4.151/xc8/pic/include/proc/pic18f4620.h"
#include"../mcal_std_types.h"
#include"mcal_interrupt_gen_cfg.h"


//section macro deleration //
#define INTERRUPT_ENABLE             1
#define INTERRUPT_DISABLE            0
#define INTERRUPT_OCCUR              1
#define INTERRUPT_NOT_OCCUR          0
#define INTERRUPT_PERIRITY_ENABLE    1
#define INTERRUPT_PERIRITY_DISABLE   0


//section macro function //

 #define INTERRUPT_PriorityLevelsEnable() (RCONbits.IPEN = 1)
#define INTERRUPT_PriorityLevelsDisable() (RCONbits.IPEN = 0)
#define INTERRUPT_GlobalInterrptHightEnable() (INTCONbits.GIEH =1)
#define INTERRUPT_GlobalInterrptHightDisable() (INTCONbits.GIEH =0)
#define INTERRUPT_GlobalInterrptLowEnable() (INTCONbits.GIEL =1)
#define INTERRUPT_GlobalInterrptLowDisable() (INTCONbits.GIEL =0)
#define INTERRUPT_GlobalInterrptEnable() (INTCONbits.GIE =1)
#define INTERRUPT_GlobalInterrptDisable() (INTCONbits.GIE =0)
#define INTERRUPT_PeripherarIntarruptEnable() (INTCONbits.PEIE =1)
#define INTERRUPT_PeripherarIntarruptDisable() (INTCONbits.PEIE =0)
//section data type decleration //
typedef enum {
   INTERRUPT_LOW_PRIORITY = 0,
   INTERRUPT_HIGH_PRIORITY 
}interrupt_priority_cfg;
//section function declaration //





#endif/* MCAL_INTERRUPT_CONFIG_H */


