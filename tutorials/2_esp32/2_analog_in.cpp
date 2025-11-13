/* --------------- */
/* Title: Reading an Analog Input (Potentiometer) on ESP32 (ESP-IDF) */
/* --------------- */
/*
    Description:
        This example demonstrates how to read an analog value from a
        potentiometer using the ESP-IDF ADC driver. The ESP32 converts
        the analog voltage (0–3.3V) into a digital value between 0 and 4095
        (for 12-bit resolution).

    Requirements:
        - 1 Potentiometer (3 pins)
        - Wiring:
            Potentiometer VCC  -> 3.3V
            Potentiometer GND  -> GND
            Potentiometer OUT  -> GPIO34 (ADC1 Channel 6)

    Steps to run (PlatformIO):
        1. Copy this file into src/main.cpp
        2. make build BOARD=esp32 (or: pio run)
        3. make upload BOARD=esp32 (or: pio run -t upload)
        4. make monitor BOARD=esp32 (or: pio device monitor)
*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/adc.h"

// Tag for logging
static const char* TAG = "AnalogInputExample";

// Equivalent to Arduino’s setup()
void setup()
{
    // Configure ADC1 Channel 6 (GPIO34)
    adc1_config_width(ADC_WIDTH_BIT_12);                  // 12-bit resolution (0–4095)
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11); // 0–3.3V range

    ESP_LOGI(TAG, "Analog Input Example: Potentiometer");
}

// Equivalent to Arduino’s loop()
void loop()
{
    // Read analog value from ADC1 channel 6 (GPIO34)
    int sensorValue = adc1_get_raw(ADC1_CHANNEL_6);

    // Print the value to the serial monitor
    ESP_LOGI(TAG, "Potentiometer value: %d", sensorValue);

    // Small delay for readability
    vTaskDelay(pdMS_TO_TICKS(500));
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








