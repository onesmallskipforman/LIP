#ifndef __EXTI_H
#define __EXTI_H
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/

void EXTI_Init(void);   //外部中断初始化
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
extern u8 Swing_up;
#endif
