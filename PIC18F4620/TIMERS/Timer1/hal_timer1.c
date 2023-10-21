/* 
 * File:   hal_timer1.c
 * Author: Amr Ali
 *
 * Created on September 22, 2023, 6:36 PM
 */
#include"hal_timer1.h"
static inline void Timer1_Mode_Select (const timer1_t *_timer);

#if TIMER1_INTERRUPT_FEATURE_ENADBLE == INTERRUPT_FEATURE_ENABLE
static void(*TMR1_InterruptHandeller)(void)= NULL;
#endif
static uint16 timer1_preload = 0;

std_ReturnType Timer1_Init(const timer1_t *_timer){
    std_ReturnType ret = E_OK ;
    if(NULL == _timer ){
         ret = E_NOT_OK ;
    }
    else{  
        TIMER1_MODULE_DISABLE(); 
        TIMER1_PRESCALER_SELECT(_timer->timer1_prescaler_value );
        Timer1_Mode_Select(_timer);
#if TIMER1_INTERRUPT_FEATURE_ENADBLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_IntrruptEnable();
        TIMER1_IntrruptFlagClear();
        TMR1_InterruptHandeller = _timer->TMR1_InterruptHandeller; 
#if INTERRUPT_PERIRITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY  == _timer->priority){
           TIMER1_HighPrioritySet(); 
         }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
           TIMER1_LowPrioritySet(); 
        }
        else{
            /*NOTING*/
        } 
#else
        INTERRUPT_GlobalInterrptDisable(); 
        INTERRUPT_PeripherarIntarruptEnable();
#endif
#endif 
        TIMER1_MODULE_ENABLE(); 
         
     ret = E_OK;   
    }
    return ret;  
}
std_ReturnType Timer1_DeInit(const timer1_t *_timer){
    std_ReturnType ret = E_OK ;
    if(NULL == _timer ){
         ret = E_NOT_OK ;
    }
    else{  
       TIMER1_MODULE_DISABLE();
#if TIMER1_INTERRUPT_FEATURE_ENADBLE == INTERRUPT_FEATURE_ENABLE
       TIMER1_IntrruptDisable();
#endif
     ret = E_OK;   
    }
    return ret;     
}
std_ReturnType Timer1_Write_value(const timer1_t *_timer, uint16 _value){
      std_ReturnType ret = E_OK ;
    if(NULL == _timer ){
         ret = E_NOT_OK ;
    }
    else{  
       TMR1H = (_value)>>8;
       TMR1L = (uint8)(_value); 
     ret = E_OK;   
    }
    return ret;    
}
std_ReturnType Timer1_Read_value(const timer1_t *_timer, uint16 *_value){ 
     std_ReturnType ret = E_OK ;
    uint8 l_tmr1l = 0;
    uint8 l_tmr1h = 0;
    if(NULL == _timer ){
         ret = E_NOT_OK ;
    }
    else{  
     l_tmr1h =  TMR1H ; 
     l_tmr1l =  TMR1L ;
     *_value = (uint16)((l_tmr1h<<8)+l_tmr1l); 
     ret = E_OK;   
    }
    return ret;     
}
void TMR1_ISR(void){
    TIMER1_IntrruptFlagClear();
    TMR1H = (timer1_preload)>>8;
    TMR1L = (uint8)(timer1_preload);
    if(TMR1_InterruptHandeller){
        TMR1_InterruptHandeller();
    }
}

static inline void Timer1_Mode_Select (const timer1_t *_timer){
    if(TIMER1_TIMER_MODE  == _timer->timer1_mode){
      TIMER1_TIMER_MODE_ENABLE(); 
       
    }
    else if(TIMER1_COUNTER_MODE ==  _timer->timer1_mode){
       TIMER1_COUNTER_MODE_ENABLE(); 
       if(TIMER1_SYNC_COUNTER_MODE  == _timer->timer1_counter_mode){
         TIMER1_SYNC_COUNTER_MODE_ENABLE(); 
       
       }
       else if(TIMER1_ASYNC_COUNTER_MODE == _timer->timer1_counter_mode){
        TIMER1_ASYNC_COUNTER_MODE_ENABLE (); 
       } 
       else{
         /*NOTING*/
       }
    }
    else{
      /*NOTING*/
    }
    
}
