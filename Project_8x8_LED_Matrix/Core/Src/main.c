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
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

const uint8_t char_map[95][8] = {
    // 0-9
    {0x3C,0x66,0x6E,0x76,0x66,0x66,0x66,0x3C}, // '0'
    {0x18,0x38,0x18,0x18,0x18,0x18,0x18,0x7E}, // '1'
    {0x3C,0x66,0x06,0x0C,0x18,0x30,0x60,0x7E}, // '2'
    {0x3C,0x66,0x06,0x1C,0x06,0x06,0x66,0x3C}, // '3'
    {0x0C,0x1C,0x3C,0x6C,0x7E,0x0C,0x0C,0x0C}, // '4'
    {0x7E,0x60,0x60,0x7C,0x06,0x06,0x66,0x3C}, // '5'
    {0x1C,0x30,0x60,0x7C,0x66,0x66,0x66,0x3C}, // '6'
    {0x7E,0x06,0x0C,0x18,0x30,0x30,0x30,0x30}, // '7'
    {0x3C,0x66,0x66,0x3C,0x66,0x66,0x66,0x3C}, // '8'
    {0x3C,0x66,0x66,0x66,0x3E,0x06,0x0C,0x38}, // '9'

    // A-Z
    {0x18,0x3C,0x66,0x66,0x7E,0x66,0x66,0x66}, // A
    {0x7C,0x66,0x66,0x7C,0x66,0x66,0x66,0x7C}, // B
    {0x3C,0x66,0x60,0x60,0x60,0x60,0x66,0x3C}, // C
    {0x78,0x6C,0x66,0x66,0x66,0x66,0x6C,0x78}, // D
    {0x7E,0x60,0x60,0x7C,0x60,0x60,0x60,0x7E}, // E
    {0x7E,0x60,0x60,0x7C,0x60,0x60,0x60,0x60}, // F
    {0x3C,0x66,0x60,0x60,0x6E,0x66,0x66,0x3C}, // G
    {0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x66}, // H
    {0x3C,0x18,0x18,0x18,0x18,0x18,0x18,0x3C}, // I
    {0x0E,0x06,0x06,0x06,0x06,0x66,0x66,0x3C}, // J
    {0x66,0x6C,0x78,0x70,0x78,0x6C,0x66,0x66}, // K
    {0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7E}, // L
    {0x63,0x77,0x7F,0x6B,0x63,0x63,0x63,0x63}, // M
    {0x66,0x76,0x7E,0x7E,0x6E,0x66,0x66,0x66}, // N
    {0x3C,0x66,0x66,0x66,0x66,0x66,0x66,0x3C}, // O
    {0x7C,0x66,0x66,0x7C,0x60,0x60,0x60,0x60}, // P
    {0x3C,0x66,0x66,0x66,0x66,0x6E,0x3C,0x0E}, // Q
    {0x7C,0x66,0x66,0x7C,0x78,0x6C,0x66,0x66}, // R
    {0x3C,0x66,0x60,0x3C,0x06,0x06,0x66,0x3C}, // S
    {0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x18}, // T
    {0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x3C}, // U
    {0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x18}, // V
    {0x63,0x63,0x63,0x6B,0x7F,0x77,0x63,0x63}, // W
    {0x66,0x66,0x3C,0x18,0x3C,0x66,0x66,0x66}, // X
    {0x66,0x66,0x66,0x3C,0x18,0x18,0x18,0x18}, // Y
    {0x7E,0x06,0x0C,0x18,0x30,0x60,0x60,0x7E}, // Z
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void max7219_write(uint8_t addr, uint8_t data) {
    uint16_t writeData = (addr << 8) | data;
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET); // Enable slave
    HAL_SPI_Transmit(&hspi1, (uint8_t *)&writeData, 1, 100);
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);  // Disable slave
}

void matrixInit(void) {
    max7219_write(0x09, 0x00); // No decoding
    max7219_write(0x0A, 0x07); // Intensity (7/15)
    max7219_write(0x0B, 0x07); // Scan all 8 digits
    max7219_write(0x0C, 0x01); // Normal operation
    max7219_write(0x0F, 0x00); // No display test
}

void matrixClear(void) {
    // Clear all digits (rows)
    for (int i = 1; i <= 8; i++) {
        max7219_write(i, 0x00);
    }
}

void displayCharacter(const uint8_t character[8]) {
    matrixClear(); // Clear display before showing new character
    for (int i = 0; i < 8; i++) {
        max7219_write(i + 1, character[i]);
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    /* USER CODE BEGIN 1 */
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/
    HAL_Init();

    /* USER CODE BEGIN Init */
    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */
    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_SPI1_Init();
    /* USER CODE BEGIN 2 */
    matrixInit();
    matrixClear();
    /* USER CODE END 2 */
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        for (int i = 0; i < 36; i++) {
            displayCharacter(char_map[i]);
            HAL_Delay(500); // Wait 500ms before next character
        }
        /* USER CODE END WHILE */
        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 72;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void) {
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES; // 2-line mode for MAX7219
    hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8; // Faster clock
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&hspi1) != HAL_OK) {
        Error_Handler();
    }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);

    /* Configure GPIO pin : PC13 */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* Configure GPIO pin : CS_Pin */
    GPIO_InitStruct.Pin = CS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(CS_GPIO_Port, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    __disable_irq();
    while (1) {
    }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line) {
}
#endif /* USE_FULL_ASSERT */
