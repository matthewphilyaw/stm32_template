#include "main.h"

void config_led(void);

LL_UTILS_PLLInitTypeDef pll_init_struct = {LL_RCC_PLL_MUL_6, LL_RCC_PLL_DIV_3};
LL_UTILS_ClkInitTypeDef clk_init_struct = {LL_RCC_SYSCLK_DIV_1, LL_RCC_APB1_DIV_1, LL_RCC_APB2_DIV_1};

int main(void) {
  LL_PLL_ConfigSystemClock_HSI(&pll_init_struct, &clk_init_struct);
  SysTick_Config(32000);
  config_led();

  for(;;) {
    LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
    LL_mDelay(500);
  }
}

void config_led(void) {
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT);
}
