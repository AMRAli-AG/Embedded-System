/* 
 * File:   mcal_internal_interrupt.h
 * Author: Amr Ali
 *
 * Created on September 9, 2023, 3:20 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

//section includes //

//section macro deleration //
#if ADC_INTERRUPT_FEATURE_ENADBLE == INTERRUPT_FEATURE_ENABLE 
#define  ADC_IntrruptEnable()                ( PIE1bits.ADIE = 1)
#define  ADC_IntrruptDisable()               ( PIE1bits.ADIE= 0)
#define ADC_IntrruptFlagClear()              (PIR1bits.ADIF = 0)
#if INTERRUPT_PERIRITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define ADC_HighPrioritySet()                (IPR1bits.ADIP  = 1)
#define ADC_LowPrioritySet()                 (IPR1bits.ADIP = 0)
#endif

#endif 

//section macro function //

//section data type decleration //

//section function declaration //



#endif	/* MCAL_INTERNAL_INTERRUPT_H */

