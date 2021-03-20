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
#define buz1_Pin GPIO_PIN_0
#define buz1_GPIO_Port GPIOC
#define buz2_Pin GPIO_PIN_1
#define buz2_GPIO_Port GPIOC
#define buz3_Pin GPIO_PIN_2
#define buz3_GPIO_Port GPIOC
#define buz4_Pin GPIO_PIN_3
#define buz4_GPIO_Port GPIOC
#define led4_Pin GPIO_PIN_7
#define led4_GPIO_Port GPIOA
#define trig4_Pin GPIO_PIN_10
#define trig4_GPIO_Port GPIOB
#define led1_Pin GPIO_PIN_8
#define led1_GPIO_Port GPIOA
#define led2_Pin GPIO_PIN_9
#define led2_GPIO_Port GPIOA
#define led3_Pin GPIO_PIN_10
#define led3_GPIO_Port GPIOA
#define trig1_Pin GPIO_PIN_3
#define trig1_GPIO_Port GPIOB
#define trig3_Pin GPIO_PIN_4
#define trig3_GPIO_Port GPIOB
#define trig2_Pin GPIO_PIN_5
#define trig2_GPIO_Port GPIOB
#define echo1_Pin GPIO_PIN_6
#define echo1_GPIO_Port GPIOB
#define echo2_Pin GPIO_PIN_7
#define echo2_GPIO_Port GPIOB
#define echo3_Pin GPIO_PIN_8
#define echo3_GPIO_Port GPIOB
#define echo4_Pin GPIO_PIN_9
#define echo4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
