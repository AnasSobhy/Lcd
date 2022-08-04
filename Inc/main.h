/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_BL_Pin GPIO_PIN_7
#define LCD_BL_GPIO_Port GPIOA
#define Buzz_Pin GPIO_PIN_0
#define Buzz_GPIO_Port GPIOB
#define SW6_EXTI15_Pin GPIO_PIN_15
#define SW6_EXTI15_GPIO_Port GPIOA
#define SW6_EXTI15_EXTI_IRQn EXTI15_10_IRQn
#define SW5_EXTI3_Pin GPIO_PIN_3
#define SW5_EXTI3_GPIO_Port GPIOB
#define SW5_EXTI3_EXTI_IRQn EXTI3_IRQn
#define SW4_EXTI4_Pin GPIO_PIN_4
#define SW4_EXTI4_GPIO_Port GPIOB
#define SW4_EXTI4_EXTI_IRQn EXTI4_IRQn
#define SW2_EXTI5_Pin GPIO_PIN_5
#define SW2_EXTI5_GPIO_Port GPIOB
#define SW2_EXTI5_EXTI_IRQn EXTI9_5_IRQn
#define SW3_EXTI6_Pin GPIO_PIN_6
#define SW3_EXTI6_GPIO_Port GPIOB
#define SW3_EXTI6_EXTI_IRQn EXTI9_5_IRQn
#define SW1_EXTI7_Pin GPIO_PIN_7
#define SW1_EXTI7_GPIO_Port GPIOB
#define SW1_EXTI7_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
