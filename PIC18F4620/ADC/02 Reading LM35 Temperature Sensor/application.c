/* 
 * File:   application.c
 * Author: Ahmed.Elghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 * Created on November 28, 2020, 8:43 PM
 */

#include "application.h"
#include "ECU_Layar/Chr_LCD/ecu_chr_lcd.h"
#include"ECU_Layar/DC_Motor/ecu_dc_motor.h"
adc_result_t lm35_res_1=0 ;
adc_result_t lm35_res_2=0;
uint16 lm35_res_1_celsius_mv = 0;
uint16 lm35_res_2_celsius_mv = 0;
volatile uint8 adc_flag;
uint16 data_1 = 0;
uint16 data_2 = 0;
uint8 lm35_res_txt_1[7];
uint8 lm35_res_txt_2[7];
uint8 adc_req = 0 ;
dc_motor_t dc_motor_1 = {
    .dc_motor[0].port = PORTD_INDEX,
    .dc_motor[0].pin = GPIO_PIN0,
    .dc_motor[0].logic = 0,
    .dc_motor[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor[1].port = PORTD_INDEX,
    .dc_motor[1].pin = GPIO_PIN1,
    .dc_motor[1].logic = 0,
    .dc_motor[1].direction = GPIO_DIRECTION_OUTPUT
};

dc_motor_t dc_motor_2 = {
    .dc_motor[0].port = PORTD_INDEX,
    .dc_motor[0].pin = GPIO_PIN2,
    .dc_motor[0].logic = 0,
    .dc_motor[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor[1].port = PORTD_INDEX,
    .dc_motor[1].pin = GPIO_PIN3,
    .dc_motor[1].logic = 0,
    .dc_motor[1].direction = GPIO_DIRECTION_OUTPUT
};
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
  .ADC_InterruptHandeller = NULL,
  .acquisition_time =  ADC_12_TAD,
  .adc_channel = ADC_CHANNEL_AN0,
  .convertion_clock = ADC_CONVERTION_CLOCK_FOSC_DIV_16 ,
  .result_format = ADC_RESULT_RIGHT,
  .voltage_refrance = ADC_VOLTAGE_REFERANCE_DISABLED
};
adc_conf_t adc_2 = {
  .ADC_InterruptHandeller = NULL,
  .acquisition_time =  ADC_12_TAD,
  .adc_channel = ADC_CHANNEL_AN1,
  .convertion_clock = ADC_CONVERTION_CLOCK_FOSC_DIV_16 ,
  .result_format = ADC_RESULT_RIGHT,
  .voltage_refrance = ADC_VOLTAGE_REFERANCE_DISABLED
};
adc_conf_t adc_3 = {
  .ADC_InterruptHandeller = NULL,
  .acquisition_time =  ADC_12_TAD,
  .adc_channel = ADC_CHANNEL_AN2,
  .convertion_clock = ADC_CONVERTION_CLOCK_FOSC_DIV_16 ,
  .result_format = ADC_RESULT_RIGHT,
  .voltage_refrance = ADC_VOLTAGE_REFERANCE_DISABLED
};
adc_conf_t adc_4 = {
  .ADC_InterruptHandeller = NULL,
  .acquisition_time =  ADC_12_TAD,
  .adc_channel = ADC_CHANNEL_AN3,
  .convertion_clock = ADC_CONVERTION_CLOCK_FOSC_DIV_16 ,
  .result_format = ADC_RESULT_RIGHT,
  .voltage_refrance = ADC_VOLTAGE_REFERANCE_DISABLED
};



int main() { 
    std_ReturnType ret = E_NOT_OK;
    
    application_intialize();
    ret = ADC_Init(&adc_1);
    ret = dc_motor_intalize(&dc_motor_1);
    ret = dc_motor_intalize(&dc_motor_2);
  
    ret = lcd_4bit_intialize(&lcd_1);
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 7, "LM35 TEST");
    __delay_ms(5000);
    ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "Temp1: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1, "Temp2: ");

    while(1){
        adc_req=0;
        if(0==adc_req){
           ret = ADC_GetConversiont_Blocking(&adc_1,ADC_CHANNEL_AN0 ,&lm35_res_1);
           ret = ADC_GetConversionResult(&adc_1,&data_1);
           
        }
        adc_req=1;
        if(1==adc_req){
           ret = ADC_GetConversiont_Blocking(&adc_2,ADC_CHANNEL_AN1 ,&lm35_res_2);
           ret = ADC_GetConversionResult(&adc_2,&data_2);
          
        }
        lm35_res_1_celsius_mv = lm35_res_1 * 4.88f;
        lm35_res_2_celsius_mv = lm35_res_2 * 4.88f;
        
        lm35_res_1_celsius_mv /= 10;
        lm35_res_2_celsius_mv /= 10;
        

        ret = convert_uint16_to_string(lm35_res_1_celsius_mv,lm35_res_txt_1);
        ret = convert_uint16_to_string(lm35_res_2_celsius_mv,lm35_res_txt_2);
    
        ret = lcd_4bit_send_string_pos(&lcd_1, 2, 8, lm35_res_txt_1);
        ret = lcd_4bit_send_string_pos(&lcd_1, 3, 8, lm35_res_txt_2);
        if(lm35_res_1_celsius_mv > 20){
          ret = dc_motor_move_right(&dc_motor_1);
        }
        else {
         ret = dc_motor_stop(&dc_motor_1); 
        }
        if(lm35_res_2_celsius_mv > 30){
           ret = dc_motor_move_right(&dc_motor_2);  
        }
        else {
         ret = dc_motor_stop(&dc_motor_2); 
        }
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    std_ReturnType ret = E_NOT_OK;
    ecu_layer_intialize();
}


