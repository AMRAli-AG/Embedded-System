
/* 
 * File:   euc_kaypad.c
 * Author: Amr Ali
 *
 * Created on September 3, 2023, 2:05 AM
 */
#include"euc_kaypad.h"

static const uint8 btn_values[EUC_KAYPAD_ROW][EUC_KAYPAD_COLUMNS]={
                                                      {'7','8','9','/'},  
                                                      {'4','5','6','*'},
                                                      {'1','2','3','-'},
                                                      {'#','0','=','+'},

                                                     };
/**
 * 
 * @param kaypad_obj
 * @return 
 */
std_ReturnType kaypad_intialize(const kaypad_t *kaypad_obj){
    std_ReturnType ret = E_OK ;
    uint8 row_counter=0;
    uint8 columns_counter=0;
    if(NULL == kaypad_obj ){
         ret = E_NOT_OK ;
    }
    else{
        for(row_counter =0 ; row_counter<EUC_KAYPAD_ROW;row_counter++){
           ret = gpio_pin_intialize(&(kaypad_obj->kaypad_row_pin[row_counter]));
        }     
        for(columns_counter =0 ; columns_counter<EUC_KAYPAD_COLUMNS;columns_counter++){
           ret = gpio_pin_intialize(&(kaypad_obj->kaypad_columns_pin[columns_counter]));

        }
       
    }
    return ret;;
    
}
/**
 * 
 * @param kaypad_obj
 * @param value
 * @return 
 */
std_ReturnType kaypad_get_value (const kaypad_t *kaypad_obj, uint8 *value){
    std_ReturnType ret = E_OK ;
    uint8 l_row_counter=0;
    uint8 l_columns_counter=0;
    uint8 l_counter = 0;
    uint8 colum_logic = 0;
    if((NULL == kaypad_obj) || (NULL== value)){
       ret = E_NOT_OK ;
    }
    else{
       for(l_row_counter =0 ; l_row_counter<EUC_KAYPAD_ROW;l_row_counter++){
           for(l_counter =0 ; l_counter<EUC_KAYPAD_COLUMNS;l_counter++){
               gpio_pin_write_logic(&(kaypad_obj->kaypad_row_pin[l_counter]),GPIO_LOW);
           }
           gpio_pin_write_logic(&(kaypad_obj->kaypad_row_pin[l_row_counter]),GPIO_HIGH);
           __delay_ms(50);
           for(l_columns_counter =0 ; l_columns_counter<EUC_KAYPAD_COLUMNS;l_columns_counter++){
               ret =  gpio_pin_read_logic(&(kaypad_obj->kaypad_columns_pin[l_columns_counter]),&colum_logic);
               if(GPIO_HIGH == colum_logic){
               *value =btn_values[l_row_counter][l_columns_counter];
               }
            }
       
       
       }

    }
    return ret;;
}