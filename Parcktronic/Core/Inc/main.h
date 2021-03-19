/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define trig1_Pin GPIO_PIN_0
#define trig1_GPIO_Port GPIOA
#define trig2_Pin GPIO_PIN_1
#define trig2_GPIO_Port GPIOA
#define trig3_Pin GPIO_PIN_2
#define trig3_GPIO_Port GPIOA
#define trid4_Pin GPIO_PIN_3
#define trid4_GPIO_Port GPIOA
#define led1_Pin GPIO_PIN_5
#define led1_GPIO_Port GPIOA
#define led2_Pin GPIO_PIN_6
#define led2_GPIO_Port GPIOA
#define led4_Pin GPIO_PIN_8
#define led4_GPIO_Port GPIOA
#define led3_Pin GPIO_PIN_9
#define led3_GPIO_Port GPIOA
#define sens4_Pin GPIO_PIN_6
#define sens4_GPIO_Port GPIOB
#define sens3_Pin GPIO_PIN_7
#define sens3_GPIO_Port GPIOB
#define sens2_Pin GPIO_PIN_8
#define sens2_GPIO_Port GPIOB
#define sens1_Pin GPIO_PIN_9
#define sens1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
