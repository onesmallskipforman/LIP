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
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Configure GPIO A pin 4 as output and set high
    GPIOA->CRL &= ~(GPIO_CRL_CNF4 | GPIO_CRL_MODE4); // reset mode
    GPIOA->CRL |=   GPIO_CRL_MODE4;    // set mode to output, max 50 MHz
    GPIOA->ODR |=   GPIO_ODR_ODR4;   // set output data register to high

    /* RCC->APB2ENR|=1<<2;      // */
    /* GPIOA->CRL&=0XFFF0FFFF; */
    /* GPIOA->CRL|=0X00030000;  //PA4 push-pull output */
    /* GPIOA->ODR|=1<<4;        //PA4 High output */
}

/**************************************************************************
Function: LED flicker
Entry parameter: Scintillation frequency
Return value: None
**************************************************************************/
void Led_Flash(uint16_t time)
{
    static int temp;
    if(0 == time)           LED=0;
    else if(++temp == time) LED=~LED,temp=0;
}
