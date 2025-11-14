/* --------------- */
/* Title: Debugging with ESP_LOGI() on ESP32 (ESP-IDF) */
/* --------------- */
/*
    Description:
        This example demonstrates how to use a lightweight logging function
        for debugging on STM32. It mimics ESP-IDF’s ESP_LOGI() function by
        sending formatted log messages through USART1 (PA9/PA10).

    Requirements:
        - A USB-to-Serial adapter (FTDI / CH340 / CP2102)
        - Connect:
              PA9  →  RX of USB-Serial
              PA10 →  TX of USB-Serial (optional if only transmitting)
              GND  →  GND
        - Serial monitor must be opened on the host computer
          (e.g., /dev/ttyUSB0 at 115200 baud)
        - ST-Link is used ONLY for upload (not for serial logging)

    Steps to run (PlatformIO):
        1. Copy this file into src/main.cpp
        2. make build BOARD=stm32 (or: pio run)
        3. make upload BOARD=stm32 (or: pio run -t upload)
        4. make monitor BOARD=stm32 (or: pio device monitor)
*/

#include "stm32f1xx_hal.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>

// Define a tag for all log messages in this file
static const char* TAG = "ESP32_Debug";

// UART handle for USART1 (commonly available on many STM32 boards)
static UART_HandleTypeDef huart1;

extern "C" void SysTick_Handler(void);
void SystemClock_Config(void);
static void MX_USART1_UART_Init(void);
void Error_Handler(void);

// Lightweight logger that mirrors ESP_LOGI(TAG, ...) semantics by sending
// formatted text over a UART (blocking transmit). Keeps the same call
// pattern and messages as the original.
static void ESP_LOGI_like(const char* tag, const char* fmt, ...)
{
    char buf[256];
    int offset = snprintf(buf, sizeof(buf), "[%s] ", tag);

    va_list args;
    va_start(args, fmt);
    vsnprintf(buf + offset, sizeof(buf) - offset, fmt, args);
    va_end(args);

    // ensure CRLF termination
    size_t len = strlen(buf);
    if (len + 2 < sizeof(buf)) {
        buf[len] = '\r';
        buf[len+1] = '\n';
        buf[len+2] = '\0';
        len += 2;
    }

    if (huart1.Instance != nullptr) {
        HAL_UART_Transmit(&huart1, reinterpret_cast<uint8_t*>(buf), (uint16_t)len, 1000);
    }
}

// Equivalent to Arduino’s setup()
void setup()
{
    // Wait a brief moment to allow the serial monitor to connect
    HAL_Delay(500);

    // Print setup messages
    ESP_LOGI_like(TAG, "");
    ESP_LOGI_like(TAG, "=== ESP32 Serial Debug Example ===");
    ESP_LOGI_like(TAG, "Setup started.");

    // Simulate system initialization
    ESP_LOGI_like(TAG, "Initializing system...");
    HAL_Delay(1000);

    ESP_LOGI_like(TAG, "Setup complete. Entering loop.");
}

// Equivalent to Arduino’s loop()
void loop()
{
    // Print a debug message every second
    ESP_LOGI_like(TAG, "Loop running...");

    // Simulate workload or sensor reading delay
    HAL_Delay(1000);
}

// STM32 entry point
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_USART1_UART_Init();

    setup();
    while (true)
    {
        loop();
    }

    // Should never reach here
    return 0;
}

/* Initialize USART1 on PA9(TX)/PA10(RX) at 115200 (adjust if your board differs) */
static void MX_USART1_UART_Init(void)
{
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure PA9 as TX (AF push-pull)
    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configure PA10 as RX (input floating)
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
}

/* Minimal HSI-based clock setup suitable for simple apps */
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

    // Configure SysTick to generate 1ms interrupts (used by HAL_Delay)
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}

extern "C" void SysTick_Handler(void)
{
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}

void Error_Handler(void)
{
    // Minimal error handler: stay here
    while (1)
    {
        HAL_Delay(200);
    }
}







