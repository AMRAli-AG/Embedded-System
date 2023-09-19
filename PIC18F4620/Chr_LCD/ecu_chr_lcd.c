/* 
 * File:   ecu_chr_lcd.c
 * Author: Amr Ali
 *
 * Created on September 5, 2023, 2:13 AM
 */
#include"ecu_chr_lcd.h"


/*****************************  4 BIT   **********************/
static std_ReturnType lcd_send_4bit(const chr_lcd_8bit_t *lcd, uint8 _data_command );
static std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_8bit_t *lcd );
static std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd );
static std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row,uint8 coulmn );
static std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row,uint8 coulmn );

#define _XTAL_FREQ 500000



/**
 * 1
 * @param lcd
 * @return 
 */
std_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd){
    std_ReturnType ret = E_OK ;
    uint8 index = 0;
    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{     
     ret =   gpio_pin_intialize(&(lcd->lcd_rs));
     ret =   gpio_pin_intialize(&(lcd->lcd_en));
     for(index=0; index<4;index++){
         ret =   gpio_pin_intialize(&(lcd->lcd_data[index]));
     }
     __delay_ms(20);
     ret =  lcd_4bit_send_command (lcd,_LCD_8BIT_MODE_2_LINE);
     __delay_ms(5);
     ret =  lcd_4bit_send_command (lcd,_LCD_8BIT_MODE_2_LINE);
     __delay_us(150);
     ret =  lcd_4bit_send_command (lcd,_LCD_8BIT_MODE_2_LINE);
     ret =  lcd_4bit_send_command (lcd,_LCD_CLEAR);
     ret =  lcd_4bit_send_command (lcd,_LCD_RETURN_HOME);
     ret =  lcd_4bit_send_command (lcd,_LCD_ENTRY_MODE);
     ret =  lcd_4bit_send_command (lcd,_LCD_CURSOR_OFF_DISPLAY_ON);
     ret =  lcd_4bit_send_command (lcd,_LCD_4BIT_MODE_2_LINE);
     ret =  lcd_4bit_send_command (lcd,0x80);
         
    }
    return ret; 
}
/**
 * 2
 * @param lcd
 * @param command
 * @return 
 */
std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command){
      std_ReturnType ret = E_OK ;
    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{
        ret =  gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret =  lcd_send_4bit(lcd,command>>4);
        ret =  lcd_4bit_send_enable_signal(lcd);
        ret =  lcd_send_4bit(lcd,command);       
        ret =  lcd_4bit_send_enable_signal(lcd);
  
       
    }
    return ret;   
}
/**
 * 3
 * @param lcd
 * @param data
 * @return 
 */
std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data){
        std_ReturnType ret = E_OK ;
    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{
       ret =  gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret =  lcd_send_4bit(lcd,data>>4);
        ret =  lcd_4bit_send_enable_signal(lcd);
        ret =  lcd_send_4bit(lcd,data);
        ret =  lcd_4bit_send_enable_signal(lcd);
  
       
    }
    return ret;
}
/**
 * 4
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column, uint8 data){
    std_ReturnType ret = E_OK ;
    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{

    ret = lcd_4bit_set_cursor(lcd, row, column);
    ret = lcd_4bit_send_char_data(lcd,data);
       
    }
    return ret;
}
/**
 * 5
 * @param lcd
 * @param str
 * @return 
 */
std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str){
    std_ReturnType ret = E_OK ;
    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{
        while(*str){
            
           ret =  lcd_4bit_send_char_data(lcd, *str++);
        } 
       
    }
    return ret;
}
/**
 * 6
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column,uint8 *str){
      std_ReturnType ret = E_OK ;
    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{
        ret =    lcd_4bit_set_cursor (lcd, row, column);
        while(*str){
            
           ret =  lcd_4bit_send_char_data(lcd, *str++);
        } 
       
    }
    return ret;   
}
/**
 * 7
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @return 
 */

std_ReturnType lcd_4bit_send_costom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column,const uint8 _chr[], uint8 mem_pos ){
    std_ReturnType ret = E_OK ;
    uint8 lcd_counter = 0 ;
    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{
      ret = lcd_4bit_send_command(lcd,(_LCD_CGRAM_START+(mem_pos*8)));
      for(lcd_counter=0; lcd_counter<=7; ++lcd_counter){
          ret = lcd_4bit_send_char_data(lcd,_chr[lcd_counter] );
      }
      ret =  lcd_4bit_send_char_data_pos(lcd, row, column,mem_pos);
    }
    return ret;
}
/*****************************  8 BIT   **********************/
/**
 * 8
 * @param lcd
 * @return 
 */
std_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd){
    std_ReturnType ret = E_OK ;
    uint8 index;
    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{     
     ret =   gpio_pin_intialize(&(lcd->lcd_rs));
     ret =   gpio_pin_intialize(&(lcd->lcd_en));
     for(index=0; index<8;index++){
         ret = gpio_pin_intialize(&(lcd->lcd_data[index]));

     }
     __delay_ms(20);
     ret =  lcd_8bit_send_command (lcd,_LCD_8BIT_MODE_2_LINE);
     __delay_ms(5);
     ret =  lcd_8bit_send_command (lcd,_LCD_8BIT_MODE_2_LINE);
     __delay_us(150);
     ret =  lcd_8bit_send_command (lcd,_LCD_8BIT_MODE_2_LINE);
     ret =  lcd_8bit_send_command (lcd,_LCD_CLEAR);
     ret =  lcd_8bit_send_command (lcd,_LCD_RETURN_HOME);
     ret =  lcd_8bit_send_command (lcd,_LCD_ENTRY_MODE);
     ret =  lcd_8bit_send_command (lcd,_LCD_CURSOR_OFF_DISPLAY_ON);
     ret =  lcd_8bit_send_command (lcd,_LCD_8BIT_MODE_2_LINE);
     ret =  lcd_8bit_send_command (lcd,0x80);
         
    }
    return ret;  
}
/**
 * 9
 * @param lcd
 * @param command
 * @return 
 */
std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command){
    std_ReturnType ret = E_OK ;
    uint8 pin_counter = 0;
    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{
        ret =  gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for(pin_counter = 0;pin_counter<8;pin_counter++){
          ret =gpio_pin_write_logic(&(lcd->lcd_data[pin_counter]),(command >>pin_counter)&(uint8)0x01);
        }
        ret =   lcd_8bit_send_enable_signal(lcd);
       
    }
    return ret; 
}
/**
 * 10
 * @param lcd
 * @param data
 * @return 
 */
std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data){
    std_ReturnType ret = E_OK ;
    uint8 pin_counter = 0;

    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{
       ret =  gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        for(pin_counter = 0;pin_counter<8;pin_counter++){
          ret =gpio_pin_write_logic(&(lcd->lcd_data[pin_counter]),(data >>pin_counter)&(uint8)0x01);
        }
        ret =   lcd_8bit_send_enable_signal(lcd);

       
    }
    return ret;
}
/**
 * 11
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row, uint8 column, uint8 data){
        std_ReturnType ret = E_OK ;
    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{
      
    ret =    lcd_8bit_set_cursor (lcd, row, column);
    ret =    lcd_8bit_send_char_data (lcd,data);
    
    }
    return ret;
}
/**
 * 12
 * @param lcd
 * @param str
 * @return 
 */
std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str){
     std_ReturnType ret = E_OK ;
    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{
        while(*str){
            
           ret =  lcd_8bit_send_char_data(lcd, *str++);
        }
       
    }
    return ret;  
}
/**
 * 12
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column,uint8 *str){
       std_ReturnType ret = E_OK ;
    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{
      
          ret =    lcd_8bit_set_cursor (lcd, row, column);
        while(*str){
            
           ret =  lcd_8bit_send_char_data(lcd, *str++);
        } 
    }
    return ret; 
}
/**
 * 13
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @return 
 */
std_ReturnType lcd_8bit_send_costom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column,const uint8 _chr[],uint8 mem_pos ){
    std_ReturnType ret = E_OK ;
    uint8 lcd_counter = 0 ;
    if(NULL == lcd ){
         ret = E_NOT_OK ;
    }
    else{
      ret = lcd_8bit_send_command(lcd,(_LCD_CGRAM_START+(mem_pos*8)));
      for(lcd_counter=0; lcd_counter<=7; ++lcd_counter){
          ret = lcd_8bit_send_char_data(lcd,_chr[lcd_counter] );
      }
      ret =  lcd_8bit_send_char_data_pos(lcd, row, column,mem_pos);
    }
    return ret;
}

/******************************************************/
/**
 * 14
 * @param value
 * @param str
 */
std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str ){
     std_ReturnType ret = E_OK ;
    if(NULL == str ){
         ret = E_NOT_OK ;
    }
    else{
        memset(str, '\0',4);
        sprintf(str, "%i", value);
       
    }
   return ret;

}
/**
 * 15
 * @param value
 * @param str
 */
std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str ){
    std_ReturnType ret = E_OK ;
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0 ;
    if(NULL == str ){
         ret = E_NOT_OK ;
    }
    else{
        memset(str, ' ',5);
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter] ;
            DataCounter++;
        }
       
    }
    return ret;
}

/**
 * 16
 * @param value
 * @param str
 */
std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str ){
    std_ReturnType ret = E_OK ;
    if(NULL == str ){
         ret = E_NOT_OK ;
    }
    else{  
        memset(str, '\0',11);
        sprintf(str, "%i", value);
    }
    return ret;

}
static std_ReturnType lcd_send_4bit(const chr_lcd_8bit_t *lcd, uint8 _data_command ){
    std_ReturnType ret = E_OK;
    ret =gpio_pin_write_logic(&(lcd->lcd_data[0]),(_data_command >>0)&(uint8)0x01);
    ret =gpio_pin_write_logic(&(lcd->lcd_data[1]),(_data_command >>1)&(uint8)0x01);
    ret =gpio_pin_write_logic(&(lcd->lcd_data[2]),(_data_command >>2)&(uint8)0x01);
    ret =gpio_pin_write_logic(&(lcd->lcd_data[3]),(_data_command >>3)&(uint8)0x01);
    return ret;

}
static std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_8bit_t *lcd ){
    std_ReturnType ret = E_OK;
    ret =gpio_pin_write_logic(&(lcd->lcd_en),GPIO_HIGH);
    __delay_ms(5);
    ret =gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOW);
    return ret;
}
static std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd ){
    std_ReturnType ret = E_OK;
    ret =gpio_pin_write_logic(&(lcd->lcd_en),GPIO_HIGH);
    __delay_ms(5);
    ret =gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOW);
    return ret;
}
static std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row,uint8 coulmn ){
   std_ReturnType ret = E_OK;
   coulmn--;
   switch(row){
       case ROW1 :  ret =  lcd_8bit_send_command (lcd,(0x80+coulmn));break;
       case ROW2 :  ret =  lcd_8bit_send_command (lcd,(0xc0+coulmn));break;
       case ROW3 :  ret =  lcd_8bit_send_command (lcd,(0x94+coulmn));break;
       case ROW4 :  ret =  lcd_8bit_send_command (lcd,(0xd4+coulmn));break;
       default: ;

   }
}

static std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row,uint8 coulmn ){
   std_ReturnType ret = E_OK;
   coulmn--;
   switch(row){
       case ROW1 :  ret =  lcd_4bit_send_command (lcd,(0x80+coulmn));break;
       case ROW2 :  ret =  lcd_4bit_send_command (lcd,(0xc0+coulmn));break;
       case ROW3 :  ret =  lcd_4bit_send_command (lcd,(0x94+coulmn));break;
       case ROW4 :  ret =  lcd_4bit_send_command (lcd,(0xd4+coulmn));break;
       default: ;

   }
}
