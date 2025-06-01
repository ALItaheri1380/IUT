/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
uint8_t UART1_rxBuffer[12] = {0}; 
uint8_t paswd [12] = {0};
uint8_t user[5] = {0};
int flag = 0;
uint8_t rg_paswd [12] = {0};
uint8_t rg_user[5] = {0};
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
 UART_HandleTypeDef huart4;
DMA_HandleTypeDef hdma_uart4_rx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_UART4_Init(void);
/* USER CODE BEGIN PFP */
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {    
	HAL_UART_Transmit(&huart4, UART1_rxBuffer, 12, 100);
	HAL_UART_Receive_IT(&huart4, UART1_rxBuffer, 12); 
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {    
	HAL_UART_Transmit(&huart4, UART1_rxBuffer, 12, 100);
	HAL_UART_Receive_IT(&huart4, UART1_rxBuffer, 12); 
}*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	
	
		if(flag==0){
			HAL_UART_Transmit(&huart4, "\n\r Enter Password \n\r", sizeof("\n\r Enter Password \n\r"), 100); 
			HAL_UART_Receive_DMA (&huart4, paswd, 5); 
			flag ++;
			return;
		}
		
		// HAL_UART_Transmit(&huart4, str, 15, 100);
		if(flag ==1){
			HAL_UART_Transmit(&huart4, "\n\r sign up was successful \n\r", sizeof("\n\r sign up was successful \n\r"), 100); 
			HAL_UART_Transmit(&huart4, "\n\r Enter Username (for Login) \n\r", sizeof("\n\r Enter Username (for Login) \n\r"), 100);
			HAL_UART_Receive_DMA (&huart4, rg_user, 5); 
			flag ++;
			return;
		}
		if(flag==2){
			HAL_UART_Transmit(&huart4, "\n\r Enter Password (for Login) \n\r", sizeof("\n\r Enter Password (for Login) \n\r"), 100);
			HAL_UART_Receive_DMA (&huart4, rg_paswd, 5); 
			flag ++;
			return;
		}
		
		if(flag ==3){
			int check = 1;
			for(int i =0 ; i <5 ; i++){
				if(rg_user[i] != user[i]) check = 0;
			}
			if(check){
				for(int i =0 ; i< 5; i++){
					if(rg_paswd[i] != paswd[i]) check = 0;
				}
			}
			
			if(check)
				HAL_UART_Transmit(&huart4, "\n\r Welcome ! \n\r", sizeof("\n\r Welcome ! \n\r"), 100); 
			else 
				HAL_UART_Transmit(&huart4, "\n\r Incorrent pass or username ! \n\r", sizeof("\n\r Incorrent pass or username ! \n\r"), 100);
	}
}
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
		MX_DMA_Init();
		MX_UART4_Init();
  /* USER CODE BEGIN 2 */
	
		
		HAL_UART_Transmit(&huart4, "\n\r Enter Username \n\r", sizeof("\n\r Enter Username \n\r"), 100); 
		HAL_UART_Receive_DMA (&huart4, user, 5); 
		
	 

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	//HAL_UART_Transmit_IT (&huart4, "Hi Ali Taheri !", sizeof("Hi Ali Taheri !")); 
  while (1)
  {
		//HAL_UART_Receive (&huart4, UART1_rxBuffer, 12, 5000);
		//HAL_UART_Transmit(&huart4, "Hi Ali !\n", sizeof("Hi Ali !\n"),1000);
		
		//HAL_UART_Transmit(&huart4, UART1_rxBuffer, 12, 100); 
		
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

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
