#include <stdint.h>
#define RCC_BASE 0x40021000
#define RCC_APB2ENR_REGISTER (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB2ENR_IOPCEN (1 << 4)
#define RCC_APB2ENR_IOPGEN (1 << 8)
#define RCC_APB2ENR_IOPAEN (1 << 2)




#define GPIO_PORTC_BASE 0x40011000
#define GPIO_PORTG_BASE 0x40012000
#define GPIO_PORTA_BASE 0x40010800
#define GPIO_CRH_REGISTER(x) (*(volatile uint32_t *)(x + 0x4))
#define GPIO_CRL_REGISTER(x) (*(volatile uint32_t *)(x + 0x0))
#define GPIO_CRH_MODE_MASK(x) (0x3 << ((x - 8) * 4))
#define GPIO_CRH_MODE_OUTPUT(x) (0x1 << ((x - 8) * 4))
#define GPIO_CRL_MODE_MASK(x) (0x3 << (x * 4))
#define GPIO_CRL_MODE_OUTPUT(x) (0x1 << (x * 4))
#define GPIOC_BLINK_PORT GPIO_PORTC_BASE
#define GPIOG_BLINK_PORT GPIO_PORTG_BASE
#define GPIOA_BLINK_PORT GPIO_PORTA_BASE
#define GPIOC_BLINK_NUM 13
#define GPIOG_BLINK_NUM 4
#define GPIOA_BLINK_NUM 4

#define GPIO_ODR_REGISTER(x) (*(volatile uint32_t *)(x + 0xC))
#define GPIO_ODR_PIN(x) (1 << x)




// Startup code
__attribute__((naked, noreturn)) void _reset(void) {
  // Initialise memory
  extern long _sbss, _ebss, _sdata, _edata, _sidata;
  for (long *dst = &_sbss; dst < &_ebss; dst++) *dst = 0;
  for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;) *dst++ = *src++;

  // Call main()
  extern int main(void);
  main();
  for (;;) (void) 0;  // Infinite loop
}

extern void SysTick_Handler(void);  // Defined in main.c
extern void _reset_stack_pointer(void);          // Defined in link.ld

// 16 standard and 91 STM32-specific handlers
__attribute__((section(".vectors"))) void (*const tab[16 + 91])(void) = {
    _reset_stack_pointer, _reset, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SysTick_Handler};



static volatile uint32_t s_ticks;
void SysTick_Handler(void) {
  s_ticks++;
}





void SystemInit(void) {
    return;
}
void SystemCoreClockUpdate(void) {
    return;
}
int main(void) {
    // Enable port C clock gate.
    RCC_APB2ENR_REGISTER |= RCC_APB2ENR_IOPCEN;
    RCC_APB2ENR_REGISTER |= RCC_APB2ENR_IOPGEN;
    RCC_APB2ENR_REGISTER |= RCC_APB2ENR_IOPAEN;


    // Configure GPIO C pin 13 as output.
    GPIO_CRH_REGISTER(GPIOC_BLINK_PORT) &= ~(GPIO_CRH_MODE_MASK(GPIOC_BLINK_NUM));
    GPIO_CRH_REGISTER(GPIOC_BLINK_PORT) |= GPIO_CRH_MODE_OUTPUT(GPIOC_BLINK_NUM);
    // Configure GPIO G pin 4 as output.
    GPIO_CRL_REGISTER(GPIOG_BLINK_PORT) &= ~(GPIO_CRL_MODE_MASK(GPIOG_BLINK_NUM));
    GPIO_CRL_REGISTER(GPIOG_BLINK_PORT) |= GPIO_CRL_MODE_OUTPUT(GPIOG_BLINK_NUM);
    // Configure GPIO A pin 4 as output.
    GPIO_CRL_REGISTER(GPIOA_BLINK_PORT) &= ~(GPIO_CRL_MODE_MASK(GPIOA_BLINK_NUM));
    GPIO_CRL_REGISTER(GPIOA_BLINK_PORT) |= GPIO_CRL_MODE_OUTPUT(GPIOA_BLINK_NUM);

    GPIO_ODR_REGISTER(GPIOG_BLINK_PORT) = 1;
    GPIO_ODR_REGISTER(GPIOC_BLINK_PORT) = 1;
    GPIO_ODR_REGISTER(GPIOA_BLINK_PORT) = 1;
    for (;;) {
        // Set the output bit.
        GPIO_ODR_REGISTER(GPIOC_BLINK_PORT) |= GPIO_ODR_PIN(GPIOC_BLINK_NUM);
        for (uint32_t i = 0; i < 400000; ++i) {
            __asm__ volatile("nop");
        }
        // Reset it again.
        GPIO_ODR_REGISTER(GPIOC_BLINK_PORT) &= ~GPIO_ODR_PIN(GPIOC_BLINK_NUM);
        for (uint32_t i = 0; i < 10000; ++i) {
            __asm__ volatile("nop");
        }



        // Set the output bit.
        GPIO_ODR_REGISTER(GPIOG_BLINK_PORT) |= GPIO_ODR_PIN(GPIOG_BLINK_NUM);
        for (uint32_t i = 0; i < 400000; ++i) {
            __asm__ volatile("nop");
        }
        // Reset it again.
        GPIO_ODR_REGISTER(GPIOG_BLINK_PORT) &= ~GPIO_ODR_PIN(GPIOG_BLINK_NUM);
        for (uint32_t i = 0; i < 10000; ++i) {
            __asm__ volatile("nop");
        }


        // Set the output bit.
        GPIO_ODR_REGISTER(GPIOA_BLINK_PORT) |= GPIO_ODR_PIN(GPIOA_BLINK_NUM);
        for (uint32_t i = 0; i < 400000; ++i) {
            __asm__ volatile("nop");
        }
        // Reset it again.
        GPIO_ODR_REGISTER(GPIOA_BLINK_PORT) &= ~GPIO_ODR_PIN(GPIOA_BLINK_NUM);
        for (uint32_t i = 0; i < 10000; ++i) {
            __asm__ volatile("nop");
        }
    }

    return 0;
}
