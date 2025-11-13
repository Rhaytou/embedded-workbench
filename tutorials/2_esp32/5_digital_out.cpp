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
            ESP32 GPIO2 -> Resistor -> LED Anode (+)
            LED Cathode (-) -> GND

    Steps to run:
        1. copy the code into the src/main.cpp file in your ESP-IDF project
        2. make build BOARD=esp32 (or: pio run)
        3. make upload BOARD=esp32 (or: pio run -t upload)
        4. make monitor BOARD=esp32 (or: pio device monitor)
*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"

static const char* TAG = "DigitalOutput_LED";

#define LED_PIN GPIO_NUM_2

// Keep Arduino-like structure for familiarity: setup() and loop() in C++.
static void setup()
{
    // Configure the GPIO as output
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << LED_PIN);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    esp_err_t err = gpio_config(&io_conf);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure GPIO: %s", esp_err_to_name(err));
    } else {
        ESP_LOGI(TAG, "GPIO configured for LED on GPIO%d", LED_PIN);
    }
}

static void loop()
{
    // Turn LED ON
    ESP_LOGI(TAG, "LED ON");
    gpio_set_level(LED_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(1000));

    // Turn LED OFF
    ESP_LOGI(TAG, "LED OFF");
    gpio_set_level(LED_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(1000));
}

extern "C" void app_main(void)
{
    setup();
    while (true) {
        loop();
    }
}




