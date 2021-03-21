/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define COUNT_PLACE 4
#define PLACE_FREE  4
#define TIME        1000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t TriggerEdge = 0;
uint8_t TimeEllapsed_Flag = 0;
uint8_t CaptureIsOver_Flag = 0;

uint32_t Difference = 0;
uint32_t IC_Val1 = 0;
uint32_t IC_Val2 = 0;

uint8_t flag[4] = {0,0,0,0};

uint64_t tim_channal[4] = {TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Measure_Distance(uint32_t Distance_cm[]);
void write_handler();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint32_t Distance[4] = {0};
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		Measure_Distance(Distance);
		if (PLACE_FREE > Distance[0] )
		{
			// busy
			HAL_GPIO_WritePin(GPIOA, led1_Pin, GPIO_PIN_RESET); // led off
			if (flag[0] == 1)
			{
				HAL_GPIO_WritePin(GPIOC, buz1_Pin, GPIO_PIN_RESET); // buzzer on
				HAL_Delay(TIME);
				HAL_GPIO_WritePin(GPIOC, buz1_Pin, GPIO_PIN_SET); // buzzer off
			}
			flag[0] = 0;
		}
		else
		{
			// free
			HAL_GPIO_WritePin(GPIOA, led1_Pin, GPIO_PIN_SET); // led on
			flag[0] = 1;
		}

		if (PLACE_FREE > Distance[1] )
		{
			// busy
			HAL_GPIO_WritePin(GPIOA, led2_Pin, GPIO_PIN_RESET); // led off
			if (flag[1] == 1)
			{
				HAL_GPIO_WritePin(GPIOC, buz2_Pin, GPIO_PIN_RESET); // buzzer on
				HAL_Delay(TIME);
				HAL_GPIO_WritePin(GPIOC, buz2_Pin, GPIO_PIN_SET); // buzzer off
			}
			flag[1] = 0;
		}
		else
		{
			// free
			HAL_GPIO_WritePin(GPIOA, led2_Pin, GPIO_PIN_SET); // led on
			flag[1] = 1;
		}

		if (PLACE_FREE > Distance[2] )
		{
			// busy
			HAL_GPIO_WritePin(GPIOA, led3_Pin, GPIO_PIN_RESET); // led off
			if (flag[2] == 1)
			{
				HAL_GPIO_WritePin(GPIOC, buz3_Pin, GPIO_PIN_RESET); // buzzer on
				HAL_Delay(TIME);
				HAL_GPIO_WritePin(GPIOC, buz3_Pin, GPIO_PIN_SET); // buzzer off
			}
			flag[2] = 0;
		}
		else
		{
			// free
			HAL_GPIO_WritePin(GPIOA, led3_Pin, GPIO_PIN_SET); // led on
			flag[2] = 1;
		}

		if (PLACE_FREE > Distance[3] )
		{
			// busy
			HAL_GPIO_WritePin(GPIOA, led4_Pin, GPIO_PIN_RESET); // led off
			if (flag[3] == 1)
			{
				HAL_GPIO_WritePin(GPIOC, buz4_Pin, GPIO_PIN_RESET); // buzzer on
				HAL_Delay(TIME);
				HAL_GPIO_WritePin(GPIOC, buz4_Pin, GPIO_PIN_SET); // buzzer off
			}
			flag[3] = 0;

		}
		else
		{
			// free
			HAL_GPIO_WritePin(GPIOA, led4_Pin, GPIO_PIN_SET); // led on
			flag[3] = 1;
		}

	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void Measure_Distance(uint32_t Distance_cm[])
{
	/*--------------------------1------------------------*/
	HAL_GPIO_WritePin(GPIOB, trig1_Pin, GPIO_PIN_SET);
	HAL_TIM_Base_Start_IT(&htim1); // 10us

	while (!TimeEllapsed_Flag)
	{
	}

	__HAL_TIM_SET_COUNTER(&htim4, 0);
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);

	TimeEllapsed_Flag = 0;
	HAL_GPIO_WritePin(GPIOB, trig1_Pin, GPIO_PIN_RESET);

	while (!CaptureIsOver_Flag)
	{
	}

	CaptureIsOver_Flag = 0;

	Distance_cm[0] = Difference / 58;
	HAL_Delay(20);

	/*--------------------------2------------------------*/

	HAL_GPIO_WritePin(GPIOB, trig2_Pin, GPIO_PIN_SET);
	HAL_TIM_Base_Start_IT(&htim1); // 10us

	while (!TimeEllapsed_Flag)
	{
	}

	__HAL_TIM_SET_COUNTER(&htim4, 0);
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_2);

	TimeEllapsed_Flag = 0;
	HAL_GPIO_WritePin(GPIOB, trig2_Pin, GPIO_PIN_RESET);

	while (!CaptureIsOver_Flag)
	{
	}

	CaptureIsOver_Flag = 0;

	Distance_cm[1] = Difference / 58;
	HAL_Delay(20);

	/*--------------------------3------------------------*/

	HAL_GPIO_WritePin(GPIOB, trig3_Pin, GPIO_PIN_SET);
	HAL_TIM_Base_Start_IT(&htim1); // 10us

	while (!TimeEllapsed_Flag)
	{
	}

	__HAL_TIM_SET_COUNTER(&htim4, 0);
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_3);

	TimeEllapsed_Flag = 0;
	HAL_GPIO_WritePin(GPIOB, trig3_Pin, GPIO_PIN_RESET);

	while (!CaptureIsOver_Flag)
	{
	}

	CaptureIsOver_Flag = 0;

	Distance_cm[2] = Difference / 58;
	HAL_Delay(20);

	/*--------------------------4------------------------*/

	HAL_GPIO_WritePin(GPIOB, trig4_Pin, GPIO_PIN_SET);
	HAL_TIM_Base_Start_IT(&htim1); // 10us

	while (!TimeEllapsed_Flag)
	{
	}

	__HAL_TIM_SET_COUNTER(&htim4, 0);
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_4);

	TimeEllapsed_Flag = 0;
	HAL_GPIO_WritePin(GPIOB, trig4_Pin, GPIO_PIN_RESET);

	while (!CaptureIsOver_Flag)
	{
	}

	CaptureIsOver_Flag = 0;

	Distance_cm[3] = Difference / 58;
	HAL_Delay(20);
}

void write_handler (uint64_t tim_channel)
{
	if (TriggerEdge == 0)
	{
		IC_Val1 = 0;
		IC_Val1 = HAL_TIM_ReadCapturedValue(&htim4, tim_channel);
		TriggerEdge = 1;

		__HAL_TIM_SET_CAPTUREPOLARITY(&htim4, tim_channel,
				TIM_INPUTCHANNELPOLARITY_FALLING);
	}
	else
	{
		IC_Val2 = 0;
		IC_Val2 = HAL_TIM_ReadCapturedValue(&htim4, tim_channel);
		TriggerEdge = 0;

		if (IC_Val2 > IC_Val1)
			Difference = IC_Val2 - IC_Val1;
		else
			Error_Handler();

		__HAL_TIM_SET_COUNTER(&htim4, 0);
		__HAL_TIM_SET_CAPTUREPOLARITY(&htim4, tim_channel,
				TIM_INPUTCHANNELPOLARITY_RISING);

		HAL_TIM_IC_Stop_IT(&htim4, tim_channel);

		CaptureIsOver_Flag = 1;
	}
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	//	UNUSED(htim);

	if (htim->Instance == TIM4)
	{
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			write_handler(tim_channal[0]);
		}
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
			write_handler(tim_channal[1]);
		}
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
		{
			write_handler(tim_channal[2]);
		}
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
		{
			write_handler(tim_channal[3]);
		}
	}
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	UNUSED(htim);

	if (htim->Instance == TIM1)
	{
		HAL_TIM_Base_Stop_IT(htim);
		__HAL_TIM_SET_COUNTER(htim, 0);
		TimeEllapsed_Flag = 1;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
