/* --------------- */
/* Title: Debugging Variables and Program Flow */
/* --------------- */
/*
    Description:
        This example demonstrates how to debug variable values and track
        program execution flow using Serial monitoring. Learn to monitor
        changing values, identify where your program gets stuck, and
        understand the sequence of operations.

    Requirements:
        - No external components or wiring are needed.
        - Wiring:
            Just upload this code and open the Serial Monitor.

    Steps to run:
        1. copy the code into the main.cpp file in the workspace/esp32/src folder
        2. make build BOARD=esp32
        3. make upload BOARD=esp32
        4. make monitor BOARD=esp32
*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// Define a tag for all log messages in this file
static const char* TAG = "ESP32_Debug";

int counter = 0;
int sensorValue = 0;

// Equivalent to Arduino's setup()
void setup()
{
    // Wait a brief moment to allow the serial monitor to connect
    vTaskDelay(pdMS_TO_TICKS(500));

    // Print setup messages
    ESP_LOGI(TAG, "");
    ESP_LOGI(TAG, "=== Variable Debugging Example ===");

    // Debugging variable initialization
    ESP_LOGI(TAG, "Counter initialized to: %d", counter);

    // Track program flow through setup
    ESP_LOGI(TAG, "Step 1: Starting configuration...");
    vTaskDelay(pdMS_TO_TICKS(500));

    ESP_LOGI(TAG, "Step 2: Configuration complete");
    ESP_LOGI(TAG, "Setup complete - entering main loop");
}

// Equivalent to Arduino's loop()
void loop()
{
    // Debug loop execution with counter
    ESP_LOGI(TAG, "--- Loop cycle start ---");

    // Monitor counter variable changes
    ESP_LOGI(TAG, "Current counter value: %d", counter);

    // Simulate reading a sensor value
    sensorValue = 100 + (counter * 10); // Simulate analog read
    ESP_LOGI(TAG, "Analog read result: %d", sensorValue);

    // Debug conditional logic
    if (counter % 3 == 0) {
        ESP_LOGI(TAG, ">>> Counter is divisible by 3");
    }

    // Track timing
    ESP_LOGI(TAG, "System running for: %d milliseconds", (int)pdTICKS_TO_MS(xTaskGetTickCount()));

    counter++;
    ESP_LOGI(TAG, "--- Loop cycle end ---");
    vTaskDelay(pdMS_TO_TICKS(2000));
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










