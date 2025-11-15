/*
/* --------------- */
/* Title: Reading an Analog Input (Potentiometer) on STM32 (STM32Cube) */
/* --------------- */
/*
    Description:
        This example demonstrates how to read an analog value from a
        potentiometer using the STM32 HAL ADC driver. The STM32 converts
        the analog voltage (0–3.3V) into a digital value between 0 and 4095
        (for 12-bit resolution on ADC1).

    Requirements:
        - 1 Potentiometer (3 pins)
        - Wiring:
            Potentiometer VCC  -> 3.3V
            Potentiometer GND  -> GND
            Potentiometer OUT  -> PA0 (ADC1 Channel 0)

    Steps to run (PlatformIO):
        1. Copy this file into src/main.cpp
        2. pio run -e bluepill_f103c8
        3. pio run -e bluepill_f103c8 -t upload
        4. pio device monitor -e bluepill_f103c8
*/

#include "stm32f1xx_hal.h"
#include <cstdio>

// Tag for logging
static const char* TAG = "AnalogInputExample";

// HAL handles
ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart1;

// Forward declarations
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);

// Equivalent to Arduino’s setup()
void setup()
{
    // Initialize HAL library and system clock
    HAL_Init();
    SystemClock_Config();

    // Initialize peripherals
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_USART1_UART_Init();

    // Notify via UART
    printf("[%s] Analog Input Example: Potentiometer on PA0 (ADC1_IN0)\r\n", TAG);
}

// Equivalent to Arduino’s loop()
void loop()
{
    // Start ADC conversion
    HAL_ADC_Start(&hadc1);

    // Poll for conversion (timeout 10 ms)
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
        // Read analog value (12-bit: 0 - 4095)
        uint32_t sensorValue = HAL_ADC_GetValue(&hadc1);
        printf("[%s] Potentiometer value: %lu\r\n", TAG, (unsigned long)sensorValue);
    }
    else
    {
        printf("[%s] ADC conversion timeout\r\n", TAG);
    }

    // Small delay for readability (500 ms)
    HAL_Delay(500);
}

// Retarget printf to USART1
extern "C" int __io_putchar(int ch)
{
    uint8_t c = ch & 0xFF;
    HAL_UART_Transmit(&huart1, &c, 1, HAL_MAX_DELAY);
    return ch;
}

// STM32Cube HAL generated-like initializers (kept simple and self-contained)

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

    // Use HSE (8 MHz) and PLL to 72 MHz which is typical for Blue Pill
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9; // 8MHz * 9 = 72MHz
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        // Initialization Error
        while (1) {}
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2; // 36 MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1; // 72 MHz

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        // Initialization Error
        while (1) {}
    }
}

static void MX_ADC1_Init(void)
{
    ADC_ChannelConfTypeDef sConfig = {};

    hadc1.Instance = ADC1;
#if defined(ADC_SCAN_DISABLE)
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
#else
    hadc1.Init.ScanConvMode = DISABLE;
#endif
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        while (1) {}
    }

    // Configure Regular Channel: PA0 => ADC_CHANNEL_0
    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        while (1) {}
    }
}

static void MX_USART1_UART_Init(void)
{
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
        while (1) {}
    }
}

static void MX_GPIO_Init(void)
{
    // On STM32F1, analog inputs do not need explicit GPIO init for analog mode;
    // still, init the clocks for used peripherals.

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_ADC1_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    // Optional: configure PA9 (TX) and PA10 (RX) for USART1
    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = GPIO_PIN_9; // PA9 TX
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10; // PA10 RX
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PA0 will be used as analog input (ADC1_IN0). No further GPIO config required.
}

// Entry point
int main(void)
{
    setup();
    while (1)
    {
        loop();
    }
}









