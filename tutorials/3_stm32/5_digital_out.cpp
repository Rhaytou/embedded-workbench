/* --------------- */
/* Title: Controlling a Digital Output (LED On/Off) */
/* --------------- */
/*
    Description:
        This example demonstrates how to control a digital output pin
        by turning an LED ON and OFF at a fixed interval.

    Requirements:
        - 1 LED
        - 1 Resistor (220Ω recommended)
        - Wiring:
            PA5 (STM32 digital output) -> Resistor -> LED Anode (+)
            LED Cathode (-)            -> GND

    Steps to run:
        1. copy the code into the src/main.cpp file in your STM32 project
        2. make build BOARD=stm32 (or: pio run)
        3. make upload BOARD=stm32 (or: pio run -t upload)
        4. make monitor BOARD=stm32 (or: pio device monitor)
*/

#include "stm32f1xx_hal.h"

#define LED_GPIO_PORT GPIOC
#define LED_PIN       GPIO_PIN_13

extern "C" void SysTick_Handler(void);
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void Error_Handler(void);

int main()
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1)
    {
        // Active-low LED on BluePill: RESET -> ON, SET -> OFF
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET); // LED ON
        HAL_Delay(2000);

        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET);   // LED OFF
        HAL_Delay(1000);
    }
}

static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

    // Ensure LED starts OFF (set pin high for active-low LED)
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET);
}

// Minimal HSI-based clock setup; suitable for simple apps on BluePill
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
                                | RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}

extern "C" void SysTick_Handler(void)
{
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}

void Error_Handler(void)
{
    // Indicate error by fast blinking the LED (active-low)
    while (1)
    {
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
        HAL_Delay(200);
    }
}




