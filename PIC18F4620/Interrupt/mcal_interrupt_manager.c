/* 
 * File:   mcal_interrupt_manager.c
 * Author: Amr Ali
 *
 * Created on September 9, 2023, 3:22 AM
 */
#include"mcal_interrupt_manager.h"
#include"mcal_external_interrupt.h"
#include"../../application.h"
static volatile uint8 RB4_Flag= 1 ;
static volatile uint8 RB5_Flag= 1 ;
static volatile uint8 RB6_Flag= 1 ;
static volatile uint8 RB7_Flag= 1 ;

//#if INTERRUPT_PERIRITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*
void __interrupt()InterruotManagerHigh(void){
}
void __interrupt(low_priority)InterruotManagerLow(void){
}
*/
//#else
void  __interrupt() InterruotManager (void){
   std_ReturnType ret = E_NOT_OK;

  uint8 colum_logic = 0;
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCUR == INTCONbits.INT0IF) ){
        INT0_ISR();
    }
    else{/*NOTHING*/}
     if((INTERRUPT_ENABLE == INTCON3bits.INT1E)&&(INTERRUPT_OCCUR == INTCON3bits.INT1F) ){
        INT1_ISR();
    }
    else{/*NOTHING*/}
     if((INTERRUPT_ENABLE == INTCON3bits.INT2E)&&(INTERRUPT_OCCUR == INTCON3bits.INT2F) ){
        INT2_ISR();
    }
    else{/*NOTHING*/}
     if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 ==GPIO_HIGH) && (RB4_Flag =1) ){
        RB4_Flag = 0;
        RB4_ISR(0);
    }
    else{/*NOTHING*/}
     if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&& (PORTBbits.RB4 ==GPIO_LOW)&& (RB4_Flag = 0) ){
        RB4_Flag =1;
        RB4_ISR(1);
    }
    else{/*NOTHING*/}
     if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 ==GPIO_HIGH) && (RB5_Flag =1) ){
        RB5_Flag =0 ;
        RB5_ISR(0);
    }
   // else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&& (PORTBbits.RB5 ==GPIO_LOW) && (RB5_Flag =0) ){
        RB5_Flag =1;
        RB5_ISR(1);
    }
   // else{/*NOTHING*/}
         if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 ==GPIO_HIGH) && (RB6_Flag =1) ){
        RB6_Flag = 0;
        RB6_ISR(0);
    }
    else{/*NOTHING*/}
     if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&& (PORTBbits.RB6 ==GPIO_LOW)&& (RB6_Flag = 0) ){
        RB6_Flag =1;
        RB6_ISR(1);
    }
    else{/*NOTHING*/}
     if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 ==GPIO_HIGH) && (RB7_Flag =1) ){
        RB7_Flag =0 ;
        RB7_ISR(0);
    }
   // else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&& (PORTBbits.RB7 ==GPIO_LOW) && (RB7_Flag =0) ){
        RB7_Flag =1;
        RB7_ISR(1);
    }
    if((INTERRUPT_ENABLE == PIE1bits.ADIE)&&(INTERRUPT_OCCUR == PIR1bits.ADIF) ){
       
         ADC_ISR();
    }
   else{/*NOTHING*/}
    
}

//#endif