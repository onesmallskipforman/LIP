#include "led.h"
 /**************************************************************************
Author£ºMinibalance
Our aliexpress£ºhttps://minibalance.aliexpress.com
**************************************************************************/
/**************************************************************************
Function: initialization of LED interface
Entry parameters: None
Return value: None
**************************************************************************/


void ledInit(void)
{
    // Reset and Clock Control: Enable IO port A register
    // TODO: where is IOPGEN in cmsis headers?
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN_Msk;

    // Configure GPIO A pin 4 as output and set high
    GPIOA->CRL &= ~(GPIO_CRL_MODE4_Msk); // reset mode
    GPIOA->CRL |=   GPIO_CRL_MODE4_0;    // set mode to output, max 10 MHz
    GPIOA->ODR |=   GPIO_ODR_ODR4_Msk;   // set output data register to high
}

/**************************************************************************
Function: LED flicker
Entry parameter: Scintillation frequency
Return value: None
**************************************************************************/
void Led_Flash(uint16_t time)
{
      static int temp;
      if(0==time) LED=0;
      else      if(++temp==time)    LED=~LED,temp=0;
}
