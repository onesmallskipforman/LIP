#include <stdint.h>
#include "stm32f1xx.h"


void SystemInit(void) {
    // Enable port A clock gate.
    // TODO: where is IOPGEN in cmsis headers?
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN_Msk;

    // Configure GPIO A pin 4 as output.
    GPIOA->CRL &= ~(GPIO_CRL_MODE4_Msk);
    GPIOA->CRL |=   GPIO_CRL_MODE4_0;
    GPIOA->ODR = 1; // TODO: not sure what this line does

    /* SysTick_Config(RCC_MAX_FREQUENCY/1000000); // Tick every 1 ms */
    return;
}
void SystemCoreClockUpdate(void) {
    return;
}

static volatile uint32_t s_ticks;
void SysTick_Handler(void) {
  s_ticks++;
}

int main(void) {
    for (;;) {
        for (uint32_t i = 0; i < 820000; ++i) __asm__ volatile("nop");
        // Set the output bit.
        GPIOA->ODR |= GPIO_ODR_ODR4_Msk;
        for (uint32_t i = 0; i < 400000; ++i) __asm__ volatile("nop");
        // Reset it again.
        GPIOA->ODR &= ~GPIO_ODR_ODR4_Msk;
        for (uint32_t i = 0; i < 10000; ++i) __asm__ volatile("nop");
    }

    return 0;
}
