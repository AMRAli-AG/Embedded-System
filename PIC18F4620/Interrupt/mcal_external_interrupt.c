/* 
 * File:   mcal_external_interrupt.c
 * Author: Amr Ali
 *
 * Created on September 9, 2023, 3:19 AM
 */

#include"mcal_external_interrupt.h"

static void (*INT0_Interrupthandlar)(void) = NULL;
static void (*INT1_Interrupthandlar)(void) = NULL;
static void (*INT2_Interrupthandlar)(void) = NULL;

static void (*RB4_Interrupthandlar_HIGH)(void) = NULL;
static void (*RB4_Interrupthandlar_LOW) (void) = NULL;
static void (*RB5_Interrupthandlar_HIGH)(void) = NULL;
static void (*RB5_Interrupthandlar_LOW)(void) = NULL;
static void (*RB6_Interrupthandlar_HIGH)(void) = NULL;
static void (*RB6_Interrupthandlar_LOW)(void) = NULL;
static void (*RB7_Interrupthandlar_HIGH)(void) = NULL;
static void (*RB7_Interrupthandlar_LOW)(void) = NULL;

static std_ReturnType Interrupt_ITNx_Enable(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_ITNx_Disable(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_ITNx_Priority_Init(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_ITNx_Edge_Init(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_ITNx_Pin_Init(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_ITNx_Clear_Flage(const interrupt_INTx_t *int_obj);

static std_ReturnType INT0_SetInterruptHandler( void (*Interrupthandlar)(void));
static std_ReturnType INT1_SetInterruptHandler( void (*Interrupthandlar)(void));
static std_ReturnType INT2_SetInterruptHandler( void (*Interrupthandlar)(void));
static std_ReturnType Interrupt_ITNx_SetInterruptHandler(const interrupt_INTx_t *int_obj);

static std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);

/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_ITNx_Init(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK ;
    if(NULL==int_obj){
        ret = E_NOT_OK;
    }
    else{
        //disable
         ret = Interrupt_ITNx_Disable(int_obj);
        //clear flage 
         ret = Interrupt_ITNx_Clear_Flage(int_obj);
        //configar edge
         ret = Interrupt_ITNx_Edge_Init(int_obj);
        //configur priority
         ret =Interrupt_ITNx_Priority_Init(int_obj);
        //cofigur I/O pin
         ret =Interrupt_ITNx_Pin_Init(int_obj);
        //configur callback
         ret= Interrupt_ITNx_SetInterruptHandler(int_obj);
        //enable
         ret = Interrupt_ITNx_Enable(int_obj);
    }
    return ret; 
}
void INT0_ISR(void){
    //CLEAR FLAG
    EXT_INT0_IntrruptFlagClear();
    //CODE
    //CALLBACK FUNICTION
    if(INT0_SetInterruptHandler){INT0_Interrupthandlar();}
    else{/*NOTING*/}
}
void INT1_ISR(void){
    //CLEAR FLAG
    EXT_INT1_IntrruptFlagClear();
    //CODE
    //CALLBACK FUNICTION
    if(INT1_SetInterruptHandler){INT1_Interrupthandlar();}
    else{/*NOTING*/}
}
void INT2_ISR(void){
    //CLEAR FLAG
    EXT_INT2_IntrruptFlagClear();
    //CODE
    //CALLBACK FUNICTION
    if(INT2_SetInterruptHandler){INT2_Interrupthandlar();}
    else{/*NOTING*/}
}
void RB4_ISR(uint8 RB4_SOURCE){
   EXT_RBx_IntrruptFlagClear();  
   if( 0== RB4_SOURCE){
         if(RB4_Interrupthandlar_HIGH){RB4_Interrupthandlar_HIGH();}   
         else{/*NOTING*/}
 
   }
   else if (1 == RB4_SOURCE){
          if(RB4_Interrupthandlar_LOW){RB4_Interrupthandlar_LOW();}   
          else{/*NOTING*/}

   }     
   else{/*NOTING*/}



}
void RB5_ISR(uint8 RB5_SOURCE){
   EXT_RBx_IntrruptFlagClear();  
   if( 0== RB5_SOURCE){
         if(RB5_Interrupthandlar_HIGH){RB5_Interrupthandlar_HIGH();}   
         else{/*NOTING*/}
 
   }
   else if (1 == RB5_SOURCE){
          if(RB5_Interrupthandlar_LOW){RB5_Interrupthandlar_LOW();}   
          else{/*NOTING*/}

   }     
   else{/*NOTING*/}



}
void RB7_ISR(uint8 RB7_SOURCE){
   EXT_RBx_IntrruptFlagClear();  
   if( 0== RB7_SOURCE){
         if(RB7_Interrupthandlar_HIGH){RB7_Interrupthandlar_HIGH();}   
         else{/*NOTING*/}
 
   }
   else if (1 == RB7_SOURCE){
          if(RB7_Interrupthandlar_LOW){RB7_Interrupthandlar_LOW();}   
          else{/*NOTING*/}

   }     
   else{/*NOTING*/}



}
void RB6_ISR(uint8 RB6_SOURCE){
   EXT_RBx_IntrruptFlagClear();  
   if( 0== RB6_SOURCE){
         if(RB6_Interrupthandlar_HIGH){RB6_Interrupthandlar_HIGH();}   
         else{/*NOTING*/}
 
   }
   else if (1 == RB6_SOURCE){
          if(RB6_Interrupthandlar_LOW){RB6_Interrupthandlar_LOW();}   
          else{/*NOTING*/}

   }     
   else{/*NOTING*/}



}


/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_ITNx_DeInit(const interrupt_INTx_t *int_obj){
     std_ReturnType ret = E_OK ;
    if(NULL==int_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = Interrupt_ITNx_Disable(int_obj);
    }
    return ret; 
}
/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj){
    std_ReturnType ret = E_OK ;
    if(NULL==int_obj){
        ret = E_NOT_OK;
    }
    else{
        EXT_RBx_IntrruptDisable();
        EXT_RBx_IntrruptFlagClear();

                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterrptLowEnable();
                    EXT_RBx_Priority_Low();
                }
                else if(INTERRUPT_HIGH_PRIORITY== int_obj->priority){
                    INTERRUPT_GlobalInterrptHightEnable(); 
                    EXT_RBx_Priority_High();
                }
                else{/*NOTHING*/}
       INTERRUPT_GlobalInterrptEnable();
       INTERRUPT_PeripherarIntarruptEnable();
                
       ret =gpio_pin_direction_intialize(&(int_obj->muc_pin));
       switch(int_obj->muc_pin.pin){
           case GPIO_PIN4:
               RB4_Interrupthandlar_HIGH = int_obj->EXT_InterruptHandeler_HIGH;
               RB4_Interrupthandlar_LOW = int_obj->EXT_InterruptHandeler_LOW;
           break;
           case GPIO_PIN5:
                RB5_Interrupthandlar_HIGH = int_obj->EXT_InterruptHandeler_HIGH;
                RB5_Interrupthandlar_LOW = int_obj->EXT_InterruptHandeler_LOW;

           break;
           case GPIO_PIN6:
                RB6_Interrupthandlar_HIGH = int_obj->EXT_InterruptHandeler_HIGH;
                RB6_Interrupthandlar_LOW = int_obj->EXT_InterruptHandeler_LOW;

           break;
           case GPIO_PIN7:
                RB7_Interrupthandlar_HIGH = int_obj->EXT_InterruptHandeler_HIGH;
                RB7_Interrupthandlar_LOW = int_obj->EXT_InterruptHandeler_LOW;

           break;
           default:
               ret = E_NOT_OK ;
       }
        
        EXT_RBx_IntrruptEnable();
    }
    return ret; 
}
/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj){
    std_ReturnType ret = E_OK ;
    if(NULL==int_obj){
        ret = E_NOT_OK;
    }
    else{
        
    }
    return ret;
} 

/**
 * 
 * @param int_obj
 */
static std_ReturnType Interrupt_ITNx_Enable(const interrupt_INTx_t *int_obj){
 std_ReturnType ret = E_OK ;
    if(NULL==int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0: 
                INTERRUPT_GlobalInterrptEnable();
                INTERRUPT_PeripherarIntarruptEnable();
                EXT_INT0_IntrruptEnable();
                ret = E_OK ;
                break;
            case INTERRUPT_EXTERNAL_INT1:
                INTERRUPT_GlobalInterrptEnable();
                INTERRUPT_PeripherarIntarruptEnable();
                EXT_INT1_IntrruptEnable();
                ret = E_OK ;
                break;
            case INTERRUPT_EXTERNAL_INT2:
                INTERRUPT_GlobalInterrptEnable();
                INTERRUPT_PeripherarIntarruptEnable();
                EXT_INT2_IntrruptEnable();
                ret = E_OK ;
                break;
            default: ret = E_NOT_OK;

        }
        
    }
    return ret;
}
/**
 * 
 * @param int_obj
 */
static std_ReturnType Interrupt_ITNx_Disable(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK ;
    if(NULL==int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0: 
                EXT_INT0_IntrruptDisable();
                ret = E_OK ;
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_IntrruptDisable();
                ret = E_OK ;
                break;
            case INTERRUPT_EXTERNAL_INT2: 
                EXT_INT2_IntrruptDisable();
                ret = E_OK ;
                break;
            default: ret = E_NOT_OK;

        }
        
    }
}
/**
 * 
 * @param int_obj
 */

static std_ReturnType Interrupt_ITNx_Priority_Init(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK ;
    if(NULL==int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
              case INTERRUPT_EXTERNAL_INT1:
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INT1_LowPrioritySet();}
                else if(INTERRUPT_HIGH_PRIORITY== int_obj->priority){EXT_INT1_HighPrioritySet(); }
                else{/*NOTHING*/}
                ret = E_OK ;
               
            case INTERRUPT_EXTERNAL_INT2: 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INT2_LowPrioritySet();}
                else if(INTERRUPT_HIGH_PRIORITY== int_obj->priority){EXT_INT2_HighPrioritySet();}
                else{/*NOTHING*/}
                ret = E_OK ;
               
            default: ret = E_NOT_OK;
    }
    }
     return ret;
}
//#endif
/**
 * 
 * @param int_obj
 */
static std_ReturnType Interrupt_ITNx_Edge_Init(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK ;
    if(NULL==int_obj){
        ret = E_NOT_OK;
    }
    else{
              switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0: 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT0_IntrruptFallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE== int_obj->edge){EXT_INT0_IntrruptRisingEdgeSet();}
                else{/*NOTING*/}
                ret = E_OK ;
                break;
            case INTERRUPT_EXTERNAL_INT1:
              if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INT1_IntrruptFallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE== int_obj->edge){EXT_INT1_IntrruptRisingEdgeSet();}
                else{/*NOTING*/}
                ret = E_OK ;
                break;
            case INTERRUPT_EXTERNAL_INT2: 
               if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INT2_IntrruptFallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE== int_obj->edge){EXT_INT2_IntrruptRisingEdgeSet();}
                else{/*NOTING*/}
                ret = E_OK ;
                break;
            default: ret = E_NOT_OK;
        
    }
    return ret;
    }
 }
/**
 * 
 * @param int_obj
 */
static std_ReturnType Interrupt_ITNx_Pin_Init(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK ;
    if(NULL==int_obj){
        ret = E_NOT_OK;
    }
    else{
       ret = gpio_pin_direction_intialize(&(int_obj->muc_pin));
    }
 return ret;
}
static std_ReturnType Interrupt_ITNx_Clear_Flage(const interrupt_INTx_t *int_obj){
     std_ReturnType ret = E_OK ;
    if(NULL==int_obj){
        ret = E_NOT_OK;
    }
    else{
              switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0: 
               EXT_INT0_IntrruptFlagClear();
                ret = E_OK ;
                break;
            case INTERRUPT_EXTERNAL_INT1:
             EXT_INT1_IntrruptFlagClear();
                ret = E_OK ;
                break;
            case INTERRUPT_EXTERNAL_INT2: 
               EXT_INT2_IntrruptFlagClear(); 
                ret = E_OK ;
                break;
            default: ret = E_NOT_OK;
        
    }
    return ret;
    }
}
static std_ReturnType INT0_SetInterruptHandler( void (*Interrupthandlar)(void)){
  std_ReturnType ret = E_OK ;
    if(NULL==Interrupthandlar){
        ret = E_NOT_OK;
    }
    else{
      INT0_Interrupthandlar=Interrupthandlar;
      ret = E_OK ;
    }
    return ret;
}     


static std_ReturnType INT1_SetInterruptHandler( void (*Interrupthandlar)(void)){
      std_ReturnType ret = E_OK ;
    if(NULL==Interrupthandlar){
        ret = E_NOT_OK;
    }
    else{
      INT0_Interrupthandlar=Interrupthandlar;
      ret = E_OK ;
    }
    return ret;
}
static std_ReturnType INT2_SetInterruptHandler( void (*Interrupthandlar)(void)){
      std_ReturnType ret = E_OK ;
    if(NULL==Interrupthandlar){
        ret = E_NOT_OK;
    }
    else{
      INT0_Interrupthandlar=Interrupthandlar;
      ret = E_OK ;
    }
    return ret;
}
static std_ReturnType Interrupt_ITNx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
   std_ReturnType ret = E_OK ;
    if(NULL==int_obj){
        ret = E_NOT_OK;
    }
    else{
            switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0: 
                ret =  INT0_SetInterruptHandler(int_obj->EXT_InterruptHandeler);
                ret = E_OK ;
                break;
            case INTERRUPT_EXTERNAL_INT1:
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandeler);
                ret = E_OK ;
                break;
            case INTERRUPT_EXTERNAL_INT2: 
                ret =  INT2_SetInterruptHandler(int_obj->EXT_InterruptHandeler);
                ret = E_OK ;
                break;
            default: ret = E_NOT_OK;
        
    }
    return ret;
    }  
} 

