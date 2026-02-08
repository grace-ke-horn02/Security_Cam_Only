#include "stm32f4xx_hal.h"

#ifndef _STM_HAL
#define _STM_HAL

void SystemClock_Config(void);
void MX_GPIO_Init(void); /*originally these functions are all static, but that would mean they would not be seen by main*/
void MX_DMA_Init(void);
void MX_I2C1_Init(void);
void MX_RTC_Init(void);
void MX_TIM1_Init(void);
void MX_ADC1_Init(void);
void MX_SPI1_Init(void);
void MX_USART3_UART_Init(void);

#endif
