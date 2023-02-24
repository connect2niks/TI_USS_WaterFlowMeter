/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART6_UART_Init(void);
/* USER CODE BEGIN PFP */
uint8_t byte_data[2],byte_data1[2];
uint8_t b[3],b0[2],b1[2],b2[2],b3[2],b4[2],b5[2],b6[2],b7[2],b8[2],b9[2];
//uint8_t data1[8];//={0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11};//{30,31,32,44,34,35,36,37,38,39};//{0x02,0x44,0x07,0x07,0xFF,0xFF,0xFF,0xFF,0x00,0x00};
//uint8_t data[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//uint8_t data[8]={0x11,0x11};
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int i=0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_SPI2_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
	
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);//en
HAL_Delay(1000);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);//en
		
////0x00
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b0[0]=0x00 ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b0 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b0[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);


HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b[0]=(0x00)|(0x40);
b[1]=0x02;
HAL_SPI_Transmit(&hspi2,b ,2, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);
//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b[0]=0x00;
HAL_SPI_Receive(&hspi2,&b[2],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);

////0x01
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b1[0]=0x01 ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b1 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b1[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);

////0x02
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b2[0]=0x02 ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b2 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b2[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);

////0x03

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b3[0]=0x03 ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b3 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b3[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);

////0x04

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b4[0]=0x04 ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b4 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b4[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);

////0x05

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b5[0]=0x05 ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b5 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b5[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);

////0x06

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b6[0]=0x06 ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b6 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b6[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);

////0x07

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b7[0]=0x07 ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b7 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b7[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);

////0x08

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b8[0]=0x08 ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b8 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b8[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);

////0x09

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b9[0]=0x09 ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b9 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b9[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PE14 */
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

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
