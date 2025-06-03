#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
 /**************************************************************************
Author£ºMinibalance
Our aliexpress£ºhttps://minibalance.aliexpress.com
**************************************************************************/
#define Battery_Ch 6
uint16_t Get_Adc(uint8_t ch);
int Get_battery_volt(void);   
void Angle_Adc_Init(void);   
void  Baterry_Adc_Init(void);
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times);
#endif 















