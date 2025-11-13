/* --------------- */
/* Title: Debugging with ESP_LOGI() on ESP32 (ESP-IDF) */
/* --------------- */
/*
    Description:
        This example demonstrates how to use ESP-IDF logging functions
        for debugging your ESP32 code. Unlike Arduino’s Serial.println(),
        ESP-IDF provides a flexible logging system with log levels and tags.

    Requirements:
        - No external components required.
        - Just build, flash, and open the serial monitor.

    Steps to run (PlatformIO):
        1. Copy this file into src/main.cpp
        2. make build BOARD=esp32 (or: pio run)
        3. make upload BOARD=esp32 (or: pio run -t upload)
        4. make monitor BOARD=esp32 (or: pio device monitor)
*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// Define a tag for all log messages in this file
static const char* TAG = "ESP32_Debug";

// Equivalent to Arduino’s setup()
void setup()
{
    // Wait a brief moment to allow the serial monitor to connect
    vTaskDelay(pdMS_TO_TICKS(500));

    // Print setup messages
    ESP_LOGI(TAG, "");
    ESP_LOGI(TAG, "=== ESP32 Serial Debug Example ===");
    ESP_LOGI(TAG, "Setup started.");

    // Simulate system initialization
    ESP_LOGI(TAG, "Initializing system...");
    vTaskDelay(pdMS_TO_TICKS(1000));

    ESP_LOGI(TAG, "Setup complete. Entering loop.");
}

// Equivalent to Arduino’s loop()
void loop()
{
    // Print a debug message every second
    ESP_LOGI(TAG, "Loop running...");

    // Simulate workload or sensor reading delay
    vTaskDelay(pdMS_TO_TICKS(1000));
}

// ESP-IDF entry point
extern "C" void app_main(void)
{
    setup();
    while (true)
    {
        loop();
    }
}







