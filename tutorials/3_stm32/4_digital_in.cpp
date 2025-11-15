/* --------------- */
/* Title: Reading a Digital Input (Push Button) */
/* --------------- */
/*
    Description:
        This example demonstrates how to read the state of a push button
        connected to a digital input pin. The program prints whether the
        button is pressed or released.

    Requirements:
        - 1 Push button
        - 1 Resistor (10kΩ pull-down)
        - Wiring:
            Button one side  -> 3.3V
            Button other side -> PA0 (STM32 digital input)
            PA0               -> 10kΩ resistor -> GND

            Note:
                Use a breadboard.
                    Connect both the button leg and one side of the resistor to the same breadboard row.
                    Then run one jumper wire from that row to the STM32 PA0 pin.

    Steps to run:
        1. copy the code into the src/main.cpp file in your STM32Cube project
        2. pio run -e bluepill_f103c8
        3. pio run -e bluepill_f103c8 -t upload
        4. pio device monitor -e bluepill_f103c8
*/

#include "stm32f1xx_hal.h"
#include <cstdio>

static const char* TAG = "DigitalInput_Button";

#define BUTTON_GPIO_PORT GPIOA
#define BUTTON_PIN       GPIO_PIN_0

UART_HandleTypeDef huart1;

/* Forward declarations */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

/* Keep Arduino-like structure for familiarity: setup() and loop() in C++. */
static void setup()
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART1_UART_Init();

    // Notify via UART
    printf("[%s] Digital Input Example: Push Button initialized on PA0\r\n", TAG);
}

static void loop()
{
    GPIO_PinState state = HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_PIN);
    int buttonState = (state == GPIO_PIN_SET) ? 1 : 0;

    if (buttonState == 1) {
        printf("[%s] Button is PRESSED\r\n", TAG);
    } else {
        printf("[%s] Button is RELEASED\r\n", TAG);
    }

    HAL_Delay(300);
}

/* Retarget printf to USART1 */
extern "C" int __io_putchar(int ch)
{
    uint8_t c = ch & 0xFF;
    HAL_UART_Transmit(&huart1, &c, 1, HAL_MAX_DELAY);
    return ch;
}

/* GPIO init: enable clocks, configure PA0 as input (external pull-down), and
   PA9/PA10 for USART1 TX/RX (optional RX).
*/
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {};

    // PA0 as input, no internal pull (external 10k pull-down is used)
    GPIO_InitStruct.Pin = BUTTON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStruct);

    // PA9 TX (USART1) as alternate function push-pull
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

/* USART1 init for printf over PA9 (TX) */
static void MX_USART1_UART_Init(void)
{
    __HAL_RCC_USART1_CLK_ENABLE();

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
        // Initialization Error
        while (1) {}
    }
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

/* Entry point */
int main(void)
{
    setup();
    while (1) {
        loop();
    }
}




