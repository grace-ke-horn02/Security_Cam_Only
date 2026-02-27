#include "stm32f4xx_hal.h"

#ifndef _STM_HAL
#define _STM_HAL

extern ADC_HandleTypeDef hadc1;

extern I2C_HandleTypeDef hi2c1;

extern RTC_HandleTypeDef hrtc;

extern SPI_HandleTypeDef hspi1;

extern TIM_HandleTypeDef htim1;

extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;


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
