/* 
 * File:   hal_adc.c
 * Author: Amr Ali
 *
 * Created on September 17, 2023, 5:37 AM
 */
#include"hal_adc.h"
#include<xc.h>   
#if ADC_INTERRUPT_FEATURE_ENADBLE == INTERRUPT_FEATURE_ENABLE
static void (*ADC_Interrupthandlar)(void) = NULL;
#endif 
static inline void adc_input_channel_port_configure(adc_channel_select_t channel);
static inline void select_result_format (const adc_conf_t *_adc);
static inline void configure_voltage_referance (const adc_conf_t *_adc);
/**
 * 
 * @param _adc
 * @return 
 */

std_ReturnType ADC_Init(const adc_conf_t *_adc){
    std_ReturnType ret = E_OK ;
    if(NULL == _adc ){
         ret = E_NOT_OK ;
    }
    else{
        ADC_CONVERSION_DISABLE();
        ADCON2bits.ACQT =_adc->acquisition_time;
        ADCON2bits.ADCS = _adc->convertion_clock;
        ADCON0bits.CHS = _adc->adc_channel;
        adc_input_channel_port_configure(_adc->adc_channel);
        select_result_format(_adc);
        configure_voltage_referance(_adc);
        #if ADC_INTERRUPT_FEATURE_ENADBLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_GlobalInterrptDisable(); 
        INTERRUPT_PeripherarIntarruptEnable();
        ADC_IntrruptEnable();
        ADC_IntrruptFlagClear();
        #if INTERRUPT_PERIRITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY ==_adc->priority){ADC_HighPrioritySet();}
        else if(INTERRUPT_LOW_PRIORITY ==_adc->priority){ADC_LowPrioritySet();}
        else{/*NOTHING*/}
        #endif
        ADC_Interrupthandlar = _adc->ADC_InterruptHandeller;
        #endif  
       ADC_CONVERSION_ENABLE();
    }
    return ret; 
}

/**
 * 
 * @param _adc
 * @return 
 */
std_ReturnType ADC_DeInit(const adc_conf_t *_adc){
     std_ReturnType ret = E_OK ;
    if(NULL == _adc ){
         ret = E_NOT_OK ;
    }
    else{
        ADC_CONVERSION_DISABLE(); 
       #if ADC_INTERRUPT_FEATURE_ENADBLE == INTERRUPT_FEATURE_ENABLE
       ADC_IntrruptDisable();  
       #endif 
    }
    return ret;    
}
/**
 * 
 * @param _adc
 * @param channel
 * @return 
 */
std_ReturnType ADC_SelectChannal(const adc_conf_t *_adc, adc_channel_select_t channel ){
     std_ReturnType ret = E_OK ;
    if(NULL == _adc ){
         ret = E_NOT_OK ;
    }
    else{
        ADCON0bits.CHS = channel;
        adc_input_channel_port_configure(channel);
    }
    return ret;    
}
/**
 * 
 * @param _adc
 * @return 
 */
std_ReturnType ADC_StartConversion(const adc_conf_t *_adc){
      std_ReturnType ret = E_OK ;
    if(NULL == _adc ){
         ret = E_NOT_OK ;
    }
    else{
       ADC_START_CONVERTION();  
    }
    return ret;   
}
/**
 * 
 * @param _adc
 * @param convertion_status
 * @return 
 */
std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc, uint8 *convertion_status){
     std_ReturnType ret = E_OK ;
    if((NULL == _adc) || (NULL == convertion_status )){
         ret = E_NOT_OK ;
    }
    else{
      *convertion_status = (uint8)(!ADCON0bits.GO_nDONE);
    }
    return ret;    
}
/**
 * 
 * @param _adc
 * @param convertion_result
 * @return 
 */
std_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc, adc_result_t *convertion_result ){
      std_ReturnType ret = E_OK ;
    if((NULL == _adc) || (NULL == convertion_result) ){
         ret = E_NOT_OK ;
    }
    else{
    if(ADC_RESULT_RIGHT == _adc->result_format){
       *convertion_result = (adc_result_t) ((ADRESH <<8 )+ ADRESL);
    }
    else if(ADC_RESULT_LEFT == _adc->result_format){
      *convertion_result = (adc_result_t) (((ADRESH <<8 )+ ADRESL)>>6);

    }
    else{
     *convertion_result = (adc_result_t) ((ADRESH <<8 )+ ADRESL);

    }
    }
    return ret;     
}
/**
 * 
 * @param _adc
 * @param channel
 * @param convertion_status
 * @return 
 */
std_ReturnType ADC_GetConversiont_Blocking(const adc_conf_t *_adc, adc_channel_select_t channel,adc_result_t *convertion_result ){
   std_ReturnType ret = E_OK ;
   uint8 l_convertion_status = 0 ;
    if((NULL == _adc) || (NULL == convertion_result) ){
         ret = E_NOT_OK ;
    }
    else{
       ret = ADC_SelectChannal(_adc, channel);
       ret = ADC_StartConversion(_adc);
       while(ADCON0bits.GO_nDONE);
       ret = ADC_GetConversionResult(_adc, convertion_result );
       
    }
    return ret;    
}
std_ReturnType ADC_StartConversiont_interrupt(const adc_conf_t *_adc, adc_channel_select_t channel ){
   std_ReturnType ret = E_OK ;
   uint8 l_convertion_status = 0 ;
    if(NULL == _adc ){
         ret = E_NOT_OK ;
    }
    else{
       ret = ADC_SelectChannal(_adc, channel);
       ret = ADC_StartConversion(_adc);
       
    }
    return ret;    
}
static inline void adc_input_channel_port_configure(adc_channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0 : SET_BIT(TRISA, _TRISA_RA0_POSN); break;
        case ADC_CHANNEL_AN1 : SET_BIT(TRISA, _TRISA_RA1_POSN); break;
        case ADC_CHANNEL_AN2 : SET_BIT(TRISA, _TRISA_RA2_POSN); break;
        case ADC_CHANNEL_AN3 : SET_BIT(TRISA, _TRISA_RA3_POSN); break;
        case ADC_CHANNEL_AN4 : SET_BIT(TRISA, _TRISA_RA5_POSN); break;
        case ADC_CHANNEL_AN5 : SET_BIT(TRISE, _TRISA_RA0_POSN); break;
        case ADC_CHANNEL_AN6 : SET_BIT(TRISE, _TRISA_RA1_POSN); break;
        case ADC_CHANNEL_AN7 : SET_BIT(TRISE, _TRISA_RA2_POSN); break;
        case ADC_CHANNEL_AN8 : SET_BIT(TRISB, _TRISA_RA2_POSN); break;
        case ADC_CHANNEL_AN9 : SET_BIT(TRISB, _TRISA_RA3_POSN); break;
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB, _TRISA_RA1_POSN); break;
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB, _TRISA_RA4_POSN); break;
        case ADC_CHANNEL_AN12: SET_BIT(TRISB, _TRISA_RA0_POSN); break;
    }
}
static inline void select_result_format (const adc_conf_t *_adc){
    if(ADC_RESULT_RIGHT == _adc->result_format){
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if(ADC_RESULT_LEFT == _adc->result_format){
        ADC_RESULT_LEFT_FORMAT();
    }
    else{
       ADC_RESULT_RIGHT_FORMAT();  
    }
    
}
static inline void configure_voltage_referance (const adc_conf_t *_adc){
    if(ADC_VOLTAGE_REFERANCE_ENABLED  == _adc->voltage_refrance){
        ADC_ENABLE_VOLTAGE_REFRANCE();
    }
    else if(ADC_VOLTAGE_REFERANCE_DISABLED == _adc->voltage_refrance){
        ADC_DISABLE_VOLTAGE_REFRANCE();
    }
    else{
        ADC_DISABLE_VOLTAGE_REFRANCE();
    }
    
}
void ADC_ISR(void){
    ADC_IntrruptFlagClear();
    if(ADC_Interrupthandlar){
        ADC_Interrupthandlar();
    }
}