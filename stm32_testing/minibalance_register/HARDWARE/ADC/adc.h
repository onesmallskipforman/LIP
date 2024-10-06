#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
 /**************************************************************************
作者：平衡小车之家 
淘宝店铺：http://shop114407458.taobao.com/
**************************************************************************/
#define Battery_Ch 6
uint16_t Get_Adc(uint8_t ch);
int Get_battery_volt(void);   
void Adc_Init(void);  
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times);
#endif 















