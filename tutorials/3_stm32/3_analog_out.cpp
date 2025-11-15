/* --------------- */
/* Title: Controlling LED Brightness (Analog Output using PWM) on STM32 (STM32Cube) */
/* --------------- */
/*
    Description:
        This example demonstrates how to use PWM (Pulse Width Modulation)
        to control the brightness of an LED using the STM32 HAL TIM PWM driver.
        PWM simulates an analog output by rapidly switching the pin ON and OFF
        at a high frequency, controlling the perceived brightness.

    Requirements:
        - 1 LED
        - 1 Resistor (220Ω recommended)
        - Wiring:
            STM32 pin PA0  -> Resistor -> LED Anode (+)
            LED Cathode (-)  -> GND

    Steps to run (PlatformIO):
        1. Copy this file into src/main.cpp
        2. pio run -e bluepill_f103c8
        3. pio run -e bluepill_f103c8 -t upload
        4. pio device monitor -e bluepill_f103c8
*/

#include "stm32f1xx_hal.h"
#include <cstdio>

// Tag for logging
static const char* TAG = "PWM_LED_Brightness";

/* PWM definitions (map roughly to the ESP32 example names) */
#define LED_GPIO_PORT      GPIOA
#define LED_PIN            GPIO_PIN_0
#define LED_TIMER          TIM2
#define LED_TIMER_CHANNEL  TIM_CHANNEL_1
#define PWM_FREQUENCY_HZ   5000U
#define PWM_RESOLUTION     255U  // 8-bit resolution (0-255)

/* HAL handles */
TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart1;

/* Forward declarations */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);

/* Equivalent to Arduino’s setup() */
void setup()
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_TIM2_Init();
    MX_USART1_UART_Init();

    // Start PWM with 0 duty
    if (HAL_TIM_PWM_Start(&htim2, LED_TIMER_CHANNEL) != HAL_OK)
    {
        // PWM start error
        while (1) {}
    }

    printf("[%s] Analog Output Example: LED Brightness Control initialized.\r\n", TAG);
}

/* Equivalent to Arduino’s loop() */
void loop()
{
    // Ramp up 0 -> 255
    for (int brightness = 0; brightness <= (int)PWM_RESOLUTION; brightness++) {
        __HAL_TIM_SET_COMPARE(&htim2, LED_TIMER_CHANNEL, (uint32_t)brightness);
        printf("[%s] Brightness: %d\r\n", TAG, brightness);
        HAL_Delay(10);
    }

    // Ramp down 255 -> 0
    for (int brightness = (int)PWM_RESOLUTION; brightness >= 0; brightness--) {
        __HAL_TIM_SET_COMPARE(&htim2, LED_TIMER_CHANNEL, (uint32_t)brightness);
        printf("[%s] Brightness: %d\r\n", TAG, brightness);
        HAL_Delay(10);
    }
}

/* Retarget printf to USART1 */
extern "C" int __io_putchar(int ch)
{
    uint8_t c = ch & 0xFF;
    HAL_UART_Transmit(&huart1, &c, 1, HAL_MAX_DELAY);
    return ch;
}

/* System Clock Configuration
   Typical Blue Pill configuration: HSE 8 MHz -> PLL x9 -> 72 MHz SYSCLK
*/
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9; // 8MHz * 9 = 72MHz
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        while (1) {}
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
                                | RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2; // 36 MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1; // 72 MHz

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        while (1) {}
    }
}

/* TIM2 init for PWM on PA0 (TIM2_CH1)
   We choose prescaler and period to approximate 5 kHz with 8-bit resolution.
   prescaler = 55 => timer clock = 72MHz / (55+1) = 1.2857 MHz
   period = 255 => PWM freq ≈ 1.2857MHz / 256 ≈ 5.02 kHz
*/
static void MX_TIM2_Init(void)
{
    TIM_OC_InitTypeDef sConfigOC = {};
    uint32_t prescaler = 55; // calculated for ~5 kHz with 8-bit period

    htim2.Instance = LED_TIMER;
    htim2.Init.Prescaler = prescaler;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = PWM_RESOLUTION; // 0..255
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
    {
        while (1) {}
    }

    // Configure PWM channel
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0; // start with 0 duty
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, LED_TIMER_CHANNEL) != HAL_OK)
    {
        while (1) {}
    }
}

/* USART1 init for printf over PA9 (TX) */
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

/* GPIO init: enable clocks, configure PA0 as AF push-pull for TIM2_CH1,
   configure PA9/PA10 for USART1 TX/RX (optional RX).
*/
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {};

    // PA0 as TIM2_CH1 (Alternate function push-pull)
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

    // PA9 TX (USART1)
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PA10 RX (USART1) as input floating
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* Entry point */
int main(void)
{
    setup();
    while (1)
    {
        loop();
    }
}










