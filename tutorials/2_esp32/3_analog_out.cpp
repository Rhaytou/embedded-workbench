/* --------------- */
/* Title: Controlling LED Brightness (Analog Output using PWM) on ESP32 (ESP-IDF) */
/* --------------- */
/*
    Description:
        This example demonstrates how to use PWM (Pulse Width Modulation)
        to control the brightness of an LED using the ESP-IDF LEDC driver.
        PWM simulates an analog output by rapidly switching the pin ON and OFF
        at a high frequency, controlling the perceived brightness.

    Requirements:
        - 1 LED
        - 1 Resistor (220Ω recommended)
        - Wiring:
            ESP32 pin GPIO18 -> Resistor -> LED Anode (+)
            LED Cathode (-)  -> GND

    Steps to run (PlatformIO):
        1. Copy this file into src/main.cpp
        2. make build BOARD=esp32 (or: pio run)
        3. make upload BOARD=esp32 (or: pio run -t upload)
        4. make monitor BOARD=esp32 (or: pio device monitor)
*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_log.h"

static const char* TAG = "PWM_LED_Brightness";

#define LED_PIN         GPIO_NUM_18
#define LEDC_CHANNEL    LEDC_CHANNEL_0
#define LEDC_TIMER      LEDC_TIMER_0
#define LEDC_MODE       LEDC_HIGH_SPEED_MODE
#define LEDC_FREQUENCY  5000
#define LEDC_RESOLUTION LEDC_TIMER_8_BIT

void setup()
{
    // Configure PWM timer
    // Note: older fields like `sleep_mode` / `deconfigure` are not present in some ESP-IDF versions.
    // Keep fields compatible with current LEDC timer structure while preserving logic.
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_RESOLUTION,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Configure PWM channel (field order adjusted for ESP-IDF v5.5)
    ledc_channel_config_t ledc_channel = {
        .gpio_num       = LED_PIN,
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER,
        .duty           = 0,
        .hpoint         = 0,
        .flags = {
            .output_invert = 0
        }
        // Note: do not set .sleep_mode here - some ESP-IDF versions do not expose it.
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    ESP_LOGI(TAG, "Analog Output Example: LED Brightness Control initialized.");
}

void loop()
{
    for (int brightness = 0; brightness <= 255; brightness++) {
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, brightness);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
        ESP_LOGI(TAG, "Brightness: %d", brightness);
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    for (int brightness = 255; brightness >= 0; brightness--) {
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, brightness);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
        ESP_LOGI(TAG, "Brightness: %d", brightness);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

extern "C" void app_main(void)
{
    setup();
    while (true) {
        loop();
    }
}










