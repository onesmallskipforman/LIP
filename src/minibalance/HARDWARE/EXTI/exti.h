#ifndef __EXTI_H
#define __EXTI_H
  /**************************************************************************
Author：Minibalance
Our aliexpress：https://minibalance.aliexpress.com
**************************************************************************/

void EXTI_Init(void);   //外部中断初始化
void EXTI3_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
#endif
