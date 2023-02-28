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
#ifdef __GNUC__
  /* With GCC, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */
void TDC7200_SPIByteWriteReg(uint8_t addr, uint8_t value);
/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/************************************************************
* TDC7200 REGISTER SET ADDRESSES
************************************************************/

#define TDC7200_CONFIG1_REG						0x00
#define TDC7200_CONFIG2_REG						0x01
#define TDC7200_INTRPT_STATUS_REG				0x02
#define TDC7200_INTRPT_MASK_REG					0x03
#define TDC7200_COARSE_COUNTER_OVH_REG			0x04
#define TDC7200_COARSE_COUNTER_OVL_REG			0x05
#define TDC7200_CLOCK_COUNTER_OVH_REG			0x06
#define TDC7200_CLOCK_COUNTER_OVL_REG			0x07
#define TDC7200_CLOCK_COUNTER_STOP_MASKH_REG	0x08
#define TDC7200_CLOCK_COUNTER_STOP_MASKL_REG	0x09

#define TDC7200_TIME1_REG						0x10
#define TDC7200_CLOCK_COUNT1_REG				0x11
#define TDC7200_TIME2_REG						0x12
#define TDC7200_CLOCK_COUNT2_REG				0x13
#define TDC7200_TIME3_REG						0x14
#define TDC7200_CLOCK_COUNT3_REG				0x15
#define TDC7200_TIME4_REG						0x16
#define TDC7200_CLOCK_COUNT4_REG				0x17
#define TDC7200_TIME5_REG						0x18
#define TDC7200_CLOCK_COUNT5_REG				0x19
#define TDC7200_TIME6_REG						0x1A
#define TDC7200_CALIBRATION1_REG				0x1B
#define TDC7200_CALIBRATION2_REG				0x1C

#define TDC7200_TOTAL_NUM_CONFIG_REG			10
#define TDC7200_TOTAL_NUM_RESULT_REG			39


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
void TDC7200_reg_init(void);
void tdc_trigger_measure(void);	
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART6_UART_Init(void);
/* USER CODE BEGIN PFP */

uint8_t b[3],b0[2],b1[2],b2[2],b3[2],b4[2],b5[2],b6[2],b7[2],b8[2],b9[2],i0[3];
uint8_t temp[3];

uint8_t a0,a1,a2;
uint8_t d0[4],d1[4],d2[4],d3[4],d5[4];
/* USER CODE END PFP */
uint8_t TDC7200_reg_local_copy[10] = {0x02, 0x40, 0x07, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0x0, 0x0 };
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int i=0;
uint8_t byte_data[3];
uint8_t read_data[2];
/* USER CODE END 0 */
uint8_t upStreamBuf[48];

    long int uTime[2];
    long int uClk;
    long int uCal[2];
 long int us, ur;
    long int ds, dr;
    long int dn;
    long int dmy;
int flag=0;
long double CLOCKperiod;
long double calCount,normLSB,TOF,LSB,mTOF;
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
	printf("\n\rTDC7200\n\r ");
		printf("\n\rInitializing TDC7200 Registers.... ");
  /* USER CODE BEGIN 2 */
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);//en
HAL_Delay(1000);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);//en	

  /* USER CODE END 2 */
/* init registers of TDC7200 */
TDC7200_reg_init();

	printf("\n\rClear error flags and reset state machine");

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
temp[0]= 0x02;
temp[0]|=(0x40);
temp[1]=0x1F;
HAL_SPI_Transmit(&hspi2,temp ,2, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
HAL_Delay(1000);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
temp[0]= TDC7200_INTRPT_STATUS_REG;
HAL_SPI_Transmit(&hspi2,temp ,1, 50);
HAL_SPI_Receive(&hspi2,&temp[2],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
HAL_Delay(1000);
printf("\n\r set start measurement bit");
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);	

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
byte_data[0]=TDC7200_CONFIG1_REG;
byte_data[0] |= 0x40;	
byte_data[1] =0x03;
HAL_SPI_Transmit(&hspi2,byte_data,2, 50);	
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
HAL_Delay(1/2);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
HAL_Delay(4);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
HAL_Delay(1/2);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);


HAL_Delay(3000);

printf("\n\r Measurement Done...Calculating TOF ");
printf(" \n\r Reading all the result registers");

//INT status

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
i0[0]=0x02 ;//| 0x40;;
HAL_SPI_Transmit(&hspi2,i0 ,1, 50);
HAL_SPI_Receive(&hspi2,&i0[1],3, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);



//TDC7200_TIME1_REG

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
d0[0]=0x10 ;//| 0x40;;
HAL_SPI_Transmit(&hspi2,d0 ,1, 50);
HAL_SPI_Receive(&hspi2,&d0[1],3, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);

//TDC7200_CLOCK_COUNT1_REG
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
d1[0]=0x11;//| 0x40;
HAL_SPI_Transmit(&hspi2,d1 ,1, 50);
HAL_SPI_Receive(&hspi2,&d1[1],3, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);

//TDC7200_TIME1_REG
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
d5[0]=0x12;//| 0x40;
HAL_SPI_Transmit(&hspi2,d5 ,1, 50);
HAL_SPI_Receive(&hspi2,&d5[1],3, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);
//TDC7200_CALIBRATION1_REG
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
d2[0]=0x1B ;//| 0x40;;
HAL_SPI_Transmit(&hspi2,d2 ,1, 50);
HAL_SPI_Receive(&hspi2,&d2[1],3, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);

//TDC7200_CALIBRATION2_REG
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
d3[0]=0x1C;//| 0x40;
HAL_SPI_Transmit(&hspi2,d3 ,1, 50);
HAL_SPI_Receive(&hspi2,&d3[1],3, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);


//tof ccalculation
uTime[0]=0;
uTime[0]=d0[1];
uTime[0] <<= 8;
uTime[0]  += d0[2];
uTime[0] <<= 8;
uTime[0]  += d0[3];

uTime[1]=0;
uTime[1]=d5[1];
uTime[1] <<= 8;
uTime[1]  += d5[2];
uTime[1] <<= 8;
uTime[1]  += d5[3];
	  
		uClk   = 0;
   	uClk   = d1[1];
   	uClk <<= 8;
   	uClk  += d1[2];
   	uClk <<= 8;
   	uClk  += d1[3];
	 
	  uCal[0]  = 0;
   	uCal[0]   = d2[1];
   	uCal[0] <<= 8;
   	uCal[0]  += d2[2];
    uCal[0] <<= 8;
   	uCal[0]  += d2[3];		
		
		 uCal[1]  = 0;
   	uCal[1]   = d3[1];
   	uCal[1] <<= 8;
   	uCal[1]  += d3[2];
    uCal[1] <<= 8;
   	uCal[1]  += d3[3];		
			
			
//		dmy = (uTime[0] - uTime[1])*140625;
//      dn  = uCal[1] - uCal[0];
//      us  = dmy / dn;

//      ur  = dmy - us*dn;
//      dmy = dn / 2;
//      ur  = (ur*8 + dmy);
//      ur  = ur / dn;
//      us  = 8*us + ur;
//      us  = us + uClk * 125000;


  calCount= (	uCal[1]-uCal[0])/(10-1);
	CLOCKperiod=(8000000);
	//normLSB=CLOCKperiod/calCount;
LSB=calCount*8000000;
normLSB=1/LSB;
  TOF=(uTime[0]*normLSB)+(uClk/CLOCKperiod)-(uTime[1]*normLSB);  
 mTOF=TOF*1000;    
printf("\n\r TOF= %f s",TOF);
printf("\n\r TOF(in ms)= %f ms",mTOF);
/* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
 //HAL_UART_Transmit(&huart6,(uint8_t*)"Trigger",sizeof("Trigger"),200);
flag=1;
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
void TDC7200_reg_init(void)
{
	b[0]=0x00;
	for(int i=0;i<10;i++)
{
	b[0]|=(0x40);
	b[1]=TDC7200_reg_local_copy[i];
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2,b ,2, 50);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
  HAL_Delay(1000);
	b[0]++;
}
  

//Setting CONFIG rEG1 0x00==0x02
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b[0]=(0x00)|(0x40);
b[1]=0x03;
HAL_SPI_Transmit(&hspi2,b ,2, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);
//0x02==0x07
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b[0]=(0x02)|(0x40);
b[1]=0x07;
HAL_SPI_Transmit(&hspi2,b ,2, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
HAL_Delay(1000);


printf("\n\r TDC_7200 REGISTER AFTER INITIALIZATION");
////0x00
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b0[0]=TDC7200_CONFIG1_REG ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b0 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b0[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
printf("\n\r CONFIG1_REG:0x0%x",b0[1]);
HAL_Delay(1000);
////0x01
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b1[0]=TDC7200_CONFIG2_REG ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b1 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b1[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
printf("\n\r CONFIG2_REG:0x0%x",b1[1]);
HAL_Delay(1000);

////0x02
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b2[0]=TDC7200_INTRPT_STATUS_REG ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b2 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b2[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
printf("\n\r INTRPT_STATUS_REG:0x0%x",b2[1]);
HAL_Delay(1000);

////0x03

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b3[0]=TDC7200_INTRPT_MASK_REG ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b3 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b3[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
printf("\n\r INTRPT_MASK_REG:0x0%x",b3[1]);
HAL_Delay(1000);

////0x04

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b4[0]=TDC7200_COARSE_COUNTER_OVH_REG ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b4 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b4[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
printf("\n\r COARSE_COUNTER_OVH_REG:0x0%x",b4[1]);
HAL_Delay(1000);

////0x05

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b5[0]=TDC7200_COARSE_COUNTER_OVL_REG ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b5 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b5[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
printf("\n\r COARSE_COUNTER_OVL_REG:0x0%x",b5[1]);
HAL_Delay(1000);

////0x06

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b6[0]=TDC7200_CLOCK_COUNTER_OVH_REG ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b6 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b6[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
printf("\n\r CLOCK_COUNTER_OVH_REG:0x0%x",b6[1]);
HAL_Delay(1000);

////0x07

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b7[0]=TDC7200_CLOCK_COUNTER_OVL_REG ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b7 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b7[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
printf("\n\r CLOCK_COUNTER_OVL_REG:0x0%x",b7[1]);
HAL_Delay(1000);

////0x08

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b8[0]=TDC7200_CLOCK_COUNTER_STOP_MASKH_REG ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b8 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b8[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
printf("\n\r CLOCK_COUNTER_STOP_MASKH_REG:0x0%x",b8[1]);
HAL_Delay(1000);

////0x09

HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
b9[0]=TDC7200_CLOCK_COUNTER_STOP_MASKL_REG ;//| 0x40;;

HAL_SPI_Transmit(&hspi2,b9 ,1, 50);

//HAL_SPI_Transmit(&hspi2,byte_data ,1, 50);

HAL_SPI_Receive(&hspi2,&b9[1],1, 50);
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);	
printf("\n\r CLOCK_COUNTER_STOP_MASKL_REG:0x0%x",b9[1]);
HAL_Delay(1000);

	
	
}	
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
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
