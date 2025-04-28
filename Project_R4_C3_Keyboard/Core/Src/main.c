#include "main.h"
#include "gpio.h"
#include "usart.h"
#include <stdio.h>

/* Keypad Configuration */
char keypad[4][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

GPIO_TypeDef* rowPorts[4] = {GPIOA, GPIOB, GPIOB, GPIOB};
uint16_t rowPins[4] = {GPIO_PIN_10, GPIO_PIN_15, GPIO_PIN_14, GPIO_PIN_13};

GPIO_TypeDef* colPorts[3] = {GPIOB, GPIOC, GPIOB};
uint16_t colPins[3] = {GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5};

/* Redirect printf to USART2 */
int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

/* Scan the 4x3 keypad */
char scanKeypad(void) {
    for (int col = 0; col < 3; col++) {
        // Set all columns high
        for (int i = 0; i < 3; i++) {
            HAL_GPIO_WritePin(colPorts[i], colPins[i], GPIO_PIN_SET);
        }

        // Set current column low
        HAL_GPIO_WritePin(colPorts[col], colPins[col], GPIO_PIN_RESET);

        // Debug: Print column being checked
     //   printf("Scanning Column: %d\r\n", col);

        // Check each row
        for (int row = 0; row < 4; row++) {
            // Read the row pin
            GPIO_PinState rowState = HAL_GPIO_ReadPin(rowPorts[row], rowPins[row]);

            // Debug: Print row state for each row
           //printf("Row %d State: %d\r\n", row, rowState);

            if (rowState == GPIO_PIN_RESET) {
                HAL_Delay(20); // Debounce
                while (HAL_GPIO_ReadPin(rowPorts[row], rowPins[row]) == GPIO_PIN_RESET);  // Wait until the key is released
                return keypad[row][col];  // Return the key that was pressed
            }
        }
    }
    return '\0';  // No key pressed
}

void SystemClock_Config(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init(); // Only initialize USART2 for communication

    printf("UART2 Ready - Keypad Listening...\r\n");

    while (1)
    {
    	char key = scanKeypad();
        if (key != '\0') {
            printf("Key Pressed: %c\r\n", key);
        }
        HAL_Delay(100);
    }
}

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

void Error_Handler(void)
{
    __disable_irq();
    while (1) {}
}
