/* --------------- */
/* Title: Reading an Analog Input (Potentiometer) */
/* --------------- */
/*
    Description:
        This example demonstrates how to read an analog value from a
        potentiometer using the Arduino analog input pin. The value
        represents the voltage level (0–5V), which is converted to
        a digital number between 0 and 1023.

    Requirements:
        - 1 Potentiometer (3 pins)
        - Wiring:
            Potentiometer VCC  -> 5V
            Potentiometer GND  -> GND
            Potentiometer OUT  -> A0

    Steps to run:
        1. copy the code into the main.cpp file in the workspace/arduino/src folder
        2. make build BOARD=arduino
        3. make upload BOARD=arduino
        4. make monitor BOARD=arduino
*/

#include <Arduino.h>

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for serial port to connect
    }

    Serial.println("Analog Input Example: Potentiometer");
}

void loop() {
    // Read the analog value from pin A0
    int sensorValue = analogRead(A0);

    // Print the value to the Serial Monitor
    Serial.print("Potentiometer value: ");
    Serial.println(sensorValue);

    delay(500); // Small delay for readability
}








