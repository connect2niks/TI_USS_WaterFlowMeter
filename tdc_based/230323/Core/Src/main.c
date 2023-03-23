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
 #include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
 #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
 /************************************************************
* TDC7200 REGISTER SET ADDRESSES
************************************************************/

#define TDC7200_CONFIG1_REG						        0x00
#define TDC7200_CONFIG2_REG						        0x01
#define TDC7200_INTRPT_STATUS_REG			      	0x02
#define TDC7200_INTRPT_MASK_REG				      	0x03
#define TDC7200_COARSE_COUNTER_OVH_REG		  	0x04
#define TDC7200_COARSE_COUNTER_OVL_REG		  	0x05
#define TDC7200_CLOCK_COUNTER_OVH_REG			    0x06
#define TDC7200_CLOCK_COUNTER_OVL_REG		    	0x07
#define TDC7200_CLOCK_COUNTER_STOP_MASKH_REG	0x08
#define TDC7200_CLOCK_COUNTER_STOP_MASKL_REG	0x09

#define TDC7200_TIME1_REG						          0x10
#define TDC7200_CLOCK_COUNT1_REG				      0x11
#define TDC7200_TIME2_REG						          0x12
#define TDC7200_CLOCK_COUNT2_REG				      0x13
#define TDC7200_TIME3_REG						          0x14
#define TDC7200_CLOCK_COUNT3_REG				      0x15
#define TDC7200_TIME4_REG						          0x16
#define TDC7200_CLOCK_COUNT4_REG				      0x17
#define TDC7200_TIME5_REG						          0x18
#define TDC7200_CLOCK_COUNT5_REG				      0x19
#define TDC7200_TIME6_REG						          0x1A
#define TDC7200_CALIBRATION1_REG				      0x1B
#define TDC7200_CALIBRATION2_REG				      0x1C

#define TDC7200_TOTAL_NUM_CONFIG_REG			    10
#define TDC7200_TOTAL_NUM_RESULT_REG			    39
#define NUM_STOP                              5
#define usTIM TIM4
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
	uint8_t b[2],i,upbuff[TDC7200_TOTAL_NUM_RESULT_REG],dnbuff[TDC7200_TOTAL_NUM_RESULT_REG];
	uint8_t TDC7200_reg_local_copy[10] = {0x03, 0x44, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00};
	long int uCal[2],uTime[6],uClk[5],dTime[6],dClk[5],dCal[2];
	long double TOF[6],T12=0,T21=0,dTOF,mTOF,vel,flow;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */
	void TDC7200_reg_read(void);
	void TDC7200_reg_config(void);	
	void pulse_gen(void);
	void cal_tof(void);
	void tdc_trigger_measure(void);
	void tdc_trigger_common(uint8_t *buf);
	void usDelay(uint32_t uSec);
//	void AutoReadReg(uint8_t *buffer);
	
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
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	printf("\n\n\n ");
	printf("\n\r..................................................\n\r ");
	printf("\n\r..........Ultrasonic Water Flow Meter..............\n\r ");
	
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);//en
  TDC7200_reg_config();
	//TDC7200_reg_read();
	tdc_trigger_measure();
	//pulse_gen();
	cal_tof();
	//TDC7200_reg_read();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);//dis
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
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 16-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 4;
  if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

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
void TDC7200_reg_config(void)
{
	//printf("\n\rInitializing TDC7200 Registers.... ");
	HAL_Delay(1);
	b[0]=0x00;
	b[0] |= 0x40 + 0x80;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2,&b[0] ,1, 50);
	HAL_SPI_Transmit(&hspi2,TDC7200_reg_local_copy,10,100);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
}
	

void TDC7200_reg_read(void)
{

	printf("\n\r TDC_7200 REGISTER AFTER INITIALIZATION");
		
	b[0]=0x00;
	b[0] |= 0x80;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2,b ,1, 50);
	HAL_SPI_Receive(&hspi2,&b[1],1, 50);
	printf("\n\r CONFIG1_REG:0x0%x",b[1]);
	HAL_SPI_Receive(&hspi2,&b[1],1, 50);
	printf("\n\r CONFIG2_REG:0x%x",b[1]);
	HAL_SPI_Receive(&hspi2,&b[1],1, 50);
	printf("\n\r INTRPT_STATUS_REG:0x0%x",b[1]);
	HAL_SPI_Receive(&hspi2,&b[1],1, 50);
	printf("\n\r INTRPT_MASK_REG:0x0%x",b[1]);
	HAL_SPI_Receive(&hspi2,&b[1],1, 50);
	printf("\n\r COARSE_COUNTER_OVH_REG:0x%x",b[1]);
	HAL_SPI_Receive(&hspi2,&b[1],1, 50);
	printf("\n\r COARSE_COUNTER_OVL_REG:0x%x",b[1]);
	HAL_SPI_Receive(&hspi2,&b[1],1, 50);
	printf("\n\r CLOCK_COUNTER_OVH_REG:0x%x",b[1]);
	HAL_SPI_Receive(&hspi2,&b[1],1, 50);
	printf("\n\r CLOCK_COUNTER_OVL_REG:0x%x",b[1]);
	HAL_SPI_Receive(&hspi2,&b[1],1, 50);
	printf("\n\r CLOCK_COUNTER_STOP_MASKH_REG:0x0%x",b[1]);
	HAL_SPI_Receive(&hspi2,&b[1],1, 50);
	printf("\n\r CLOCK_COUNTER_STOP_MASKL_REG:0x0%x",b[1]);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
  HAL_Delay(500);
	

}	

//void AutoReadReg(uint8_t *buffer)
//{ 
//	buffer[0]=0x10;
//	buffer[0] |= 0x80;
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
//	HAL_SPI_Transmit(&hspi2,buffer ,1, 50);
//	HAL_SPI_Receive(&hspi2,buffer,TDC7200_TOTAL_NUM_RESULT_REG, 50);                            // Read result registers
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
//  HAL_Delay(500);
//}

void cal_tof(void)
{
	//TOF Calculation
	
	for (i=0; i<6; i++)
	{
	uTime[i]=0;
	uTime[i]=upbuff[6*i];
	uTime[i] <<= 8;
	uTime[i]  += upbuff[6*i +1];
	uTime[i] <<= 8;
	uTime[i]  += upbuff[6*i + 2];
		
	dTime[i]   = 0;
	dTime[i]   = dnbuff[6*i];
	dTime[i] <<= 8;
	dTime[i]  += dnbuff[6*i + 1];
	dTime[i] <<= 8;
	dTime[i]  += dnbuff[6*i + 2];
	}
	
	
 for (i=0; i<5; i++)
 {
	uClk[i]   = 0;
	uClk[i]   = upbuff[6*i + 3];
	uClk[i] <<= 8;
	uClk[i]  += upbuff[6*i + 4];
	uClk[i] <<= 8;
	uClk[i]  += upbuff[6*i + 5];

	dClk[i]   = 0;
	dClk[i]   = dnbuff[6*i + 3];
	dClk[i] <<= 8;
	dClk[i]  += dnbuff[6*i + 4];
	dClk[i] <<= 8;
	dClk[i]  += dnbuff[6*i + 5];
 }


 for (i=0; i<2; i++)
 {
	uCal[i]   = 0;
	uCal[i]   = upbuff[33 + i*3];
	uCal[i] <<= 8;
	uCal[i]  += upbuff[34 + i*3];
	uCal[i] <<= 8;
	uCal[i]  += upbuff[35 + i*3];

	dCal[i]   = 0;
	dCal[i]   = dnbuff[33 + i*3 ];
	dCal[i] <<= 8;
	dCal[i]  += dnbuff[34 + i*3];
	dCal[i] <<= 8;
	dCal[i]  += dnbuff[35 + i*3];
 }
// 	printf("\n\r time 1:0x0%ld",uTime[0]);
//	printf("\n\r time 2:0x0%ld",uTime[1]);
//	printf("\n\r time 3:0x0%ld",uTime[2]);
//	printf("\n\r time 4:0x0%ld",uTime[3]);
//	printf("\n\r time 5:0x0%ld",uTime[4]);
//	printf("\n\r time 6:0x0%ld",uTime[5]);
//	printf("\n\r clock count 1:0x0%ld",uClk[0]);
//	printf("\n\r clock count 2:0x0%ld",uClk[1]);
//	printf("\n\r clock count 3:0x0%ld",uClk[2]);
//	printf("\n\r clock count 4:0x0%ld",uClk[3]);
//	printf("\n\r clock count 5:0x0%ld",uClk[4]);
//	printf("\n\r cal 1:0x0%ld",uCal[0]);
//	printf("\n\r cal 2:0x0%ld",uCal[1]);
// 
//	printf("\n\r time 1:0x0%ld",dTime[0]);
//	printf("\n\r time 2:0x0%ld",dTime[1]);
//	printf("\n\r time 3:0x0%ld",dTime[2]);
//	printf("\n\r time 4:0x0%ld",dTime[3]);
//	printf("\n\r time 5:0x0%ld",dTime[4]);
//	printf("\n\r time 6:0x0%ld",dTime[5]);
//	printf("\n\r clock count 1:0x0%ld",dClk[0]);
//	printf("\n\r clock count 2:0x0%ld",dClk[1]);
//	printf("\n\r clock count 3:0x0%ld",dClk[2]);
//	printf("\n\r clock count 4:0x0%ld",dClk[3]);
//	printf("\n\r clock count 5:0x0%ld",dClk[4]);
//	printf("\n\r cal 1:0x0%ld",dCal[0]);
//	printf("\n\r cal 2:0x0%ld",dCal[1]);
 
 
 for (int i = 0; i<6; i++)
 {
	 TOF[i] = 9*0.125e-6 / (uCal[1] - uCal[0]);
	 TOF[i]= (uTime[i] - uTime[i+1])*TOF[i] + uClk[i]*0.125e-6;
	 T12 += TOF[i];
//	 mTOF=TOF[i]*1000;
//	 printf("\n\r UP TOF= %Lf s",TOF[i]);
//	 printf("\n\r UP TOF(in ms)= %Lf ms",mTOF);
 }
 
 T12 = T12/5;  // Upstream TIme of Flight
 printf("\n\r T12 = %Lf \n\n",T12);
  
 for (int i = 0; i<6; i++)
 {
	 TOF[i] = 9*0.125e-6 / (dCal[1] - dCal[0]);
	 TOF[i]= (dTime[i] - dTime[i+1])*TOF[i] + dClk[i]*0.125e-6;
	 T21 += TOF[i];
//	 mTOF=TOF[i]*1000;
//	 printf("\n\r DN TOF= %Lf s",TOF[i]);
//	 printf("\n\r DN TOF(in ms)= %Lf ms",mTOF);
 }
 T21 = T21/5;   // Downstream Time of Flight
 printf("\n\r T21 = %Lf \n\n",T21);
 dTOF = (T21 - T12);
 printf("\n\r dTOF = %Lf \n\n",dTOF);
 vel = 0.031*(dTOF/T21*T12);
 printf("\n\r Velocity of Water = %Lf m/s\n\n",vel);
 flow = (((22/7)*((0.015*0.015)/4))*vel)*1000000;
 printf("\n\r Water Flow = %Lf mL/s \n\n",flow);
}

void pulse_gen(void)
{
		
// Pulse Generation
	
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);    // start pulse
	usDelay(5);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	
	//usDelay(10);    //timeGap
	HAL_Delay(2);
	for(i=1; i<=NUM_STOP; i++)
	{
	
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);    // stop_pluse
	usDelay(5);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);	
	usDelay(5);
	}	

}

void usDelay(uint32_t uSec)
{
	if(uSec < 2) uSec = 2;
	usTIM->ARR = uSec - 1; 	/*sets the value in the auto-reload register*/
	usTIM->EGR = 1; 			/*Re-initialises the timer*/
	usTIM->SR &= ~1; 		//Resets the flag
	usTIM->CR1 |= 1; 		//Enables the counter
	while((usTIM->SR&0x0001) != 1);
	usTIM->SR &= ~(0x0001);
}

void tdc_trigger_common(uint8_t *buf)
{
	uint8_t byte_data[2];
	byte_data[0] =  TDC7200_CONFIG1_REG;
	byte_data[1] = TDC7200_reg_local_copy[0];
	byte_data[1] |= 0x01;                                                // Start measurement
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2,byte_data ,2, 50);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
	pulse_gen();
	buf[0]=0x10;
	buf[0] |= 0x80;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2,buf ,1, 50);
	HAL_SPI_Receive(&hspi2,buf,TDC7200_TOTAL_NUM_RESULT_REG, 50);       // Read result registers
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
	HAL_Delay(500);
}

void tdc_trigger_measure(void)
{
	uint8_t byte_data[2];
	byte_data[0] = TDC7200_INTRPT_STATUS_REG;
	byte_data[1] = 0x1F;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2,byte_data ,2, 50);      // clear error flags and reset state machine
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
	tdc_trigger_common(upbuff);
	tdc_trigger_common(dnbuff);
}

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart6, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
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
