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

    // Print setup messages directly to UART
    printf("\n");
    printf("=== Variable Debugging Example ===\n");

    // Debugging variable initialization
    printf("Counter initialized to: %d\n", counter);

    // Track program flow through setup
    printf("Step 1: Starting configuration...\n");
    vTaskDelay(pdMS_TO_TICKS(500));

    printf("Step 2: Configuration complete\n");
    printf("Setup complete - entering main loop\n");
    fflush(stdout); // make sure all prints appear immediately
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

// FreeRTOS task to run setup and loop
void main_task(void* arg)
{
    setup();
    while(true)
    {
        loop();
    }
}

// ESP-IDF entry point
extern "C" void app_main()
{
    // Create a FreeRTOS task to run your main code
    xTaskCreate(main_task, "main_task", 4096, NULL, 5, NULL);
}






