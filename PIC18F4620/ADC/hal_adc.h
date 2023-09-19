/* 
 * File:   hal_adc.h
 * Author: Amr Ali
 *
 * Created on September 17, 2023, 5:37 AM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H
//section includes //


#include"hal_adc_cfg.h"
       
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
#include"../mcal_std_types.h"
#include"../../../../../../../Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC18Fxxxx_DFP/1.4.151/xc8/pic/include/proc/pic18f4620.h"
#include"../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include"../../MCAL_Layer/Interrupt/mcal_interrupt_config.h"

//section macro deleration //
/*FROM ANx TO 0 ANALOG*/
#define ADC_AN0_ANALOG_FUNCTIONALTY       0x0E    
#define ADC_AN1_ANALOG_FUNCTIONALTY       0x0D                    
#define ADC_AN2_ANALOG_FUNCTIONALTY       0x0C                    
#define ADC_AN3_ANALOG_FUNCTIONALTY       0x0B                    
#define ADC_AN4_ANALOG_FUNCTIONALTY       0x0A                    
#define ADC_AN5_ANALOG_FUNCTIONALTY       0x09                    
#define ADC_AN6_ANALOG_FUNCTIONALTY       0x08                    
#define ADC_AN7_ANALOG_FUNCTIONALTY       0x07                    
#define ADC_AN8_ANALOG_FUNCTIONALTY       0x06                    
#define ADC_AN9_ANALOG_FUNCTIONALTY       0x05                    
#define ADC_AN10_ANALOG_FUNCTIONALTY      0x04                    
#define ADC_AN11_ANALOG_FUNCTIONALTY      0x03                    
#define ADC_AN12_ANALOG_FUNCTIONALTY      0x02                    
#define ADC_ALL_ANALOG_FUNCTIONALTY       0x00                    
#define ADC_ALL_DIGITAL_FUNCTIONALTY      0x0F                    

#define ADC_RESULT_RIGHT                  0x01U
#define ADC_RESULT_LEFT                   0x00U

#define ADC_VOLTAGE_REFERANCE_ENABLED    0x01U
#define ADC_VOLTAGE_REFERANCE_DISABLED   0x00U
                                            
#define ADC_CONVERTION_COMPLETED           1
#define ADC_CONVERTION_INPROGRESS          0


//section macro function //

/* A/D Conversion Status bit*/
#define ADC_CONVVERSION_STATUS()      (ADCON0bits.GO_nDONE)
#define ADC_START_CONVERTION()       (ADCON0bits.GODONE = 1)
#define ADC_CONVERSION_ENABLE()      (ADCON0bits.ADON = 1)
#define ADC_CONVERSION_DISABLE()     (ADCON0bits.ADON = 0)
#define ADC_ENABLE_VOLTAGE_REFRANCE() do{ADCON1bits.VCFG1 = 1;\
                                         ADCON1bits.VCFG0 = 1;\       
                                        }while(0)
#define ADC_DISABLE_VOLTAGE_REFRANCE() do{ADCON1bits.VCFG1 = 0;\
                                         ADCON1bits.VCFG0 = 0;\       
                                        }while(0)
#define ADC_ANALOG_DIGITAL_PORT_CONFIG (_CONFIG) (ADCON1bits.PCFG = _CONFIG )  
#define ADC_RESULT_RIGHT_FORMAT()(ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()(ADCON2bits.ADFM = 0)
                                            
                                        
                      

//section data type decleration //
typedef enum {
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
}adc_channel_select_t;
typedef enum {
    ADC_0_TAD = 0  ,
    ADC_2_TAD ,
    ADC_4_TAD ,
    ADC_6_TAD ,
    ADC_8_TAD ,
    ADC_12_TAD ,
    ADC_16_TAD ,
    ADC_20_TAD 
}adc_acquisition_time_t;
typedef enum{
    ADC_CONVERTION_CLOCK_FOSC_DIV_2 = 0 ,
    ADC_CONVERTION_CLOCK_FOSC_DIV_8 ,
    ADC_CONVERTION_CLOCK_FOSC_DIV_32 ,
    ADC_CONVERTION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERTION_CLOCK_FOSC_DIV_4 ,
    ADC_CONVERTION_CLOCK_FOSC_DIV_16 ,
    ADC_CONVERTION_CLOCK_FOSC_DIV_64,
    
}adc_convertion_clock_t;    
typedef struct{
#if ADC_INTERRUPT_FEATURE_ENADBLE == INTERRUPT_FEATURE_ENABLE 
    void(*ADC_InterruptHandeller)(void);
      interrupt_priority_cfg priority ;
#endif 
    adc_acquisition_time_t acquisition_time;    /*@ref adc_acquisition_time_t*/
    adc_convertion_clock_t   convertion_clock ; /*@ref adc_convertion_clock_t*/                                      
    adc_channel_select_t      adc_channel ;     /*@ref adc_channel_select_t*/ 
    uint8 voltage_refrance : 1 ;
    uint8 result_format : 1 ;
    uint8 ADC_Reserved : 6 ;
}adc_conf_t;

typedef uint16 adc_result_t ;
//section function declaration //
std_ReturnType ADC_Init(const adc_conf_t *_adc);
std_ReturnType ADC_DeInit(const adc_conf_t *_adc);
std_ReturnType ADC_SelectChannal(const adc_conf_t *_adc, adc_channel_select_t channel );
std_ReturnType ADC_StartConversion(const adc_conf_t *_adc);
std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc, uint8 *convertion_status);
std_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc, adc_result_t *convertion_result );
std_ReturnType ADC_GetConversiont_Blocking(const adc_conf_t *_adc, adc_channel_select_t channel, adc_result_t *convertion_result );
std_ReturnType ADC_StartConversiont_interrupt(const adc_conf_t *_adc, adc_channel_select_t channel);
#endif	/* HAL_ADC_H */

