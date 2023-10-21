/* 
 * File:   hal_timer0.c
 * Author: Amr Ali
 *
 * Created on September 20, 2023, 1:56 AM
 */
#include"hal_timer0.h"

#if TIMER0_INTERRUPT_FEATURE_ENADBLE == INTERRUPT_FEATURE_ENABLE
static void(*TMR0_InterruptHandeller)(void)= NULL;
#endif

static inline void Timer0_Prescaler_Config (const timer0_t *_timer);
static inline void Timer0_Mode_Select (const timer0_t *_timer); 
static inline void Timer0_Regestar_Size (const timer0_t *_timer); 
static inline void Timer0_Prescaler_Config (const timer0_t *_timer);

static uint16 timer0_preload = 0;

std_ReturnType Timer0_Init(const timer0_t *_timer){
    std_ReturnType ret = E_OK ;
    if(NULL == _timer ){
         ret = E_NOT_OK ;
    }
    else{
       TIMER0_MODULE_DISABLE(); 
       Timer0_Prescaler_Config(_timer);
       Timer0_Mode_Select(_timer);
       Timer0_Regestar_Size(_timer);
       TMR0H = (_timer->timer0_peroled_value)>>8;
       TMR0L = (uint8)(_timer->timer0_peroled_value);
       timer0_preload = _timer->timer0_peroled_value;
#if TIMER0_INTERRUPT_FEATURE_ENADBLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_IntrruptEnable();
        TIMER0_IntrruptFlagClear();
        TMR0_InterruptHandeller = _timer->TMR0_InterruptHandeller; 
#if INTERRUPT_PERIRITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY  == _timer->priority){
           TIMER0_HighPrioritySet(); 
         }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
           TIMER0_LowPrioritySet(); 
        }
        else{
            /*NOTING*/
        } 
#else
        INTERRUPT_GlobalInterrptDisable(); 
        INTERRUPT_PeripherarIntarruptEnable();
#endif
#endif
       TIMER0_MODULE_ENABLE();
    }
    return ret;  

    
}
std_ReturnType Timer0_DeInit(const timer0_t *_timer){
    std_ReturnType ret = E_OK ;
    if(NULL == _timer ){
         ret = E_NOT_OK ;
    }
    else{
        TIMER0_MODULE_DISABLE();
       #if TIMER0_INTERRUPT_FEATURE_ENADBLE == INTERRUPT_FEATURE_ENABLE
       TIMER0_IntrruptDisable();
       #endif
    }
    return ret;  

}
std_ReturnType Timer0_Write_value(const timer0_t *_timer, uint16 _value){
    std_ReturnType ret = E_OK ;

    if((NULL == _timer) || (NULL == _value )){
         ret = E_NOT_OK ;
    }
    else{
       TMR0H = (_value)>>8;
       TMR0L = (uint8)(_value);
    }
    return ret;  
   
}
std_ReturnType Timer0_Read_value(const timer0_t *_timer, uint16 *_value){
    std_ReturnType ret = E_OK ;
    uint8 l_tmr0l = 0;
    uint8 l_tmr0h = 0;
    if((NULL == _timer) || (NULL == _value )){
         ret = E_NOT_OK ;
    }
    else{
     l_tmr0h =  TMR0H ; 
     l_tmr0l =  TMR0L ;
     *_value = (uint16)((l_tmr0h<<8)+l_tmr0l);
    }
    return ret;  
  
}
    
void TMR0_ISR(void){
    TIMER0_IntrruptFlagClear();
    TMR0H = (timer0_preload)>>8;
    TMR0L = (uint8)(timer0_preload);
    if(TMR0_InterruptHandeller){
        TMR0_InterruptHandeller();
    }
}

static inline void Timer0_Prescaler_Config (const timer0_t *_timer){
    if(TIMER0_PRESCALER_ENABLE_CFG  == _timer->prescaler_enable){
       TIMER0_PRESCALER_ENABLE(); 
       T0CONbits.T0PS =_timer->prescaler_value;
    }
    else if(TIMER0_PRESCALER_DISABLE_CFG ==  _timer->prescaler_enable){
       TIMER0_PRESCALER_DISABLE(); 
    }
    else{
      /*NOTING*/
    }
    
}

static inline void Timer0_Mode_Select (const timer0_t *_timer){
    if(TIMER0_TIMER_MODE  == _timer->timer0_mode){
      TIMER0_TIMER_MODE_ENABLE(); 
       
    }
    else if(TIMER0_COUNTER_MODE ==  _timer->timer0_mode){
       TIMER0_COUNTER_MODE_ENABLE(); 
       if(TIMER0_RISING_EDGE_CFG  == _timer->timer0_counter_edge){
         TIMER0_RISING_EDGE_ENABLE(); 
       
       }
       else if(TIMER0_FALLING_EDGEE_CFG == _timer->timer0_counter_edge){
        TIMER0_FALLING_EDGE_ENABLE (); 
       } 
       else{
         /*NOTING*/
       }
    }
    else{
      /*NOTING*/
    }
    
}
static inline void Timer0_Regestar_Size (const timer0_t *_timer){
    if(TIMER0_8_BIT_REGESTER_MODE  == _timer->timer0_regestaer_size){
       TIMER0_8BIT_REGISTER_MODE_ENABLE(); 
   
    }
    else if(TIMER0_16_BIT_REGESTER_MODE == _timer->timer0_regestaer_size){
       TIMER0_16BIT_REGISTER_MODE_ENABLE(); 
    }
    else{
      /*NOTING*/
    }
    
}