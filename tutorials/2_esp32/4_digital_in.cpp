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
            Button other side -> ESP32 GPIO2
            GPIO2             -> 10kΩ resistor -> GND

            Note:
                Use a breadboard.
                    Connect both the button leg and one side of the resistor to the same breadboard row.
                    Then run one jumper wire from that row to ESP32 GPIO2.

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

static const char* TAG = "DigitalInput_Button";

#define BUTTON_PIN GPIO_NUM_2

// Keep Arduino-like structure for familiarity: setup() and loop() in C++.
static void setup()
{
    // Configure the GPIO as input.
    // This example assumes an external 10k pull-down resistor is used,
    // so internal pull-ups/pull-downs are left disabled.
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << BUTTON_PIN);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;

    esp_err_t err = gpio_config(&io_conf);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "gpio_config failed: %s", esp_err_to_name(err));
    } else {
        ESP_LOGI(TAG, "Digital Input Example: Push Button initialized on GPIO%d", BUTTON_PIN);
    }
}

static void loop()
{
    int buttonState = gpio_get_level(BUTTON_PIN);

    if (buttonState == 1) {
        ESP_LOGI(TAG, "Button is PRESSED");
    } else {
        ESP_LOGI(TAG, "Button is RELEASED");
    }

    vTaskDelay(pdMS_TO_TICKS(300));
}

extern "C" void app_main(void)
{
    setup();
    while (true) {
        loop();
    }
}




