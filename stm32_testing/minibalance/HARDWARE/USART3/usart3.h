#ifndef __USRAT3_H
#define __USRAT3_H 
#include "sys.h"	  	

extern uint8_t Usart3_Receive;
void uart3_init(uint32_t pclk2,uint32_t bound);
void USART3_IRQHandler(void);
#endif

