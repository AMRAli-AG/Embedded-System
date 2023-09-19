/* 
 * File:   application.c
 * Author: Amr Ali
 *  Created on August 25, 2023, 2:16 AM
 */

#include "application.h"
#include "ECU_Layar/Chr_LCD/ecu_chr_lcd.h"
adc_result_t adc_res_1=0 ;
adc_result_t adc_res_2=0;
adc_result_t adc_res_3=0;
adc_result_t adc_res_4 =0 ;
volatile uint8 adc_flag;
uint16 data_1 = 0;
uint16 data_2 = 0;
uint16 data_3 = 0;
uint16 data_4 = 0;
uint8 adc_res_txt_1[6];
uint8 adc_res_txt_2[6];
uint8 adc_res_txt_3[6];
uint8 adc_res_txt_4[6];
uint8 adc_req = 0 ;

void ADC_DefaultInterruptHandellar(void);
chr_lcd_4bit_t lcd_1 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW
};

adc_conf_t adc_1 = {
  .ADC_InterruptHandeller = ADC_DefaultInterruptHandellar,
  .acquisition_time =  ADC_12_TAD,
  .adc_channel = ADC_CHANNEL_AN0,
  .convertion_clock = ADC_CONVERTION_CLOCK_FOSC_DIV_16 ,
  .result_format = ADC_RESULT_RIGHT,
  .voltage_refrance = ADC_VOLTAGE_REFERANCE_DISABLED
};
adc_conf_t adc_2 = {
  .ADC_InterruptHandeller = ADC_DefaultInterruptHandellar,
  .acquisition_time =  ADC_12_TAD,
  .adc_channel = ADC_CHANNEL_AN1,
  .convertion_clock = ADC_CONVERTION_CLOCK_FOSC_DIV_16 ,
  .result_format = ADC_RESULT_RIGHT,
  .voltage_refrance = ADC_VOLTAGE_REFERANCE_DISABLED
};
adc_conf_t adc_3 = {
  .ADC_InterruptHandeller = ADC_DefaultInterruptHandellar,
  .acquisition_time =  ADC_12_TAD,
  .adc_channel = ADC_CHANNEL_AN2,
  .convertion_clock = ADC_CONVERTION_CLOCK_FOSC_DIV_16 ,
  .result_format = ADC_RESULT_RIGHT,
  .voltage_refrance = ADC_VOLTAGE_REFERANCE_DISABLED
};
adc_conf_t adc_4 = {
  .ADC_InterruptHandeller = ADC_DefaultInterruptHandellar,
  .acquisition_time =  ADC_12_TAD,
  .adc_channel = ADC_CHANNEL_AN3,
  .convertion_clock = ADC_CONVERTION_CLOCK_FOSC_DIV_16 ,
  .result_format = ADC_RESULT_RIGHT,
  .voltage_refrance = ADC_VOLTAGE_REFERANCE_DISABLED
};
void ADC_DefaultInterruptHandellar(void){
   std_ReturnType ret = E_NOT_OK;
    adc_flag++;
   ret =  ADC_GetConversionResult(&adc_1, &adc_res_1);
}


int main() { 
    std_ReturnType ret = E_NOT_OK;
    
    application_intialize();
    ret = ADC_Init(&adc_1);
  
    ret = lcd_4bit_intialize(&lcd_1);
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 7, "ADC TEST ");
    __delay_ms(2000);
    ret = lcd_4bit_send_command (&lcd_1, _LCD_CLEAR );

    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "pot0: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "pot0: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1, "pot0: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 4, 1, "pot0: ");
    while(1){
        adc_req=0;
        if(0==adc_req){
           ret = ADC_GetConversiont_Blocking(&adc_1,ADC_CHANNEL_AN0 ,&adc_res_1);
           ret = ADC_GetConversionResult(&adc_1,&data_1);
           
        }
        adc_req=1;
        if(1==adc_req){
           ret = ADC_GetConversiont_Blocking(&adc_2,ADC_CHANNEL_AN1 ,&adc_res_2);
           ret = ADC_GetConversionResult(&adc_2,&data_2);
          
        }
        adc_req=2;
        if(2==adc_req){
        ret = ADC_GetConversiont_Blocking(&adc_3,ADC_CHANNEL_AN2 ,&adc_res_3);
        ret = ADC_GetConversionResult(&adc_3,&data_3);
       
        }
        adc_req=3;
        if(3==adc_req){
        ret = ADC_GetConversiont_Blocking(&adc_4,ADC_CHANNEL_AN3 ,&adc_res_4);
        ret = ADC_GetConversionResult(&adc_4,&data_4); 
        }
        

        ret = convert_uint16_to_string(data_1,adc_res_txt_1);
        ret = convert_uint16_to_string(data_2,adc_res_txt_2);
        ret = convert_uint16_to_string(data_3,adc_res_txt_3);
        ret = convert_uint16_to_string(data_4,adc_res_txt_4);
        ret = lcd_4bit_send_string_pos(&lcd_1, 1, 7, adc_res_txt_1);
        ret = lcd_4bit_send_string_pos(&lcd_1, 2, 7, adc_res_txt_2);
        ret = lcd_4bit_send_string_pos(&lcd_1, 3, 7, adc_res_txt_3);
        ret = lcd_4bit_send_string_pos(&lcd_1, 4, 7, adc_res_txt_4);

    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    std_ReturnType ret = E_NOT_OK;
    ecu_layer_intialize();
}


