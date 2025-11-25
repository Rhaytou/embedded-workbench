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
        1. copy the code into the main.cpp file in the workspace/arduino/src folder
        2. make build BOARD=arduino
        3. make upload BOARD=arduino
        4. make monitor BOARD=arduino
*/

#include <Arduino.h>

int counter = 0;
int sensorValue = 0;

void setup() {
    Serial.begin(9600);

    while (!Serial) {
        ; // Wait for serial port to connect.
    }

    Serial.println("=== Variable Debugging Example ===");

    // Debugging variable initialization
    Serial.print("Counter initialized to: ");
    Serial.println(counter);

    // Track program flow through setup
    Serial.println("Step 1: Starting configuration...");
    delay(500);

    Serial.println("Step 2: Configuration complete");
    Serial.println("Setup complete - entering main loop");
}

void loop() {
    // Debug loop execution with counter
    Serial.println("--- Loop cycle start ---");

    // Monitor counter variable changes
    Serial.print("Current counter value: ");
    Serial.println(counter);

    // Simulate reading a sensor value
    sensorValue = analogRead(A0);
    Serial.print("Analog read result: ");
    Serial.println(sensorValue);

    // Debug conditional logic
    if (counter % 3 == 0) {
        Serial.println(">>> Counter is divisible by 3");
    }

    // Track timing
    Serial.print("System running for: ");
    Serial.print(millis());
    Serial.println(" milliseconds");

    counter++;
    Serial.println("--- Loop cycle end ---");
    delay(2000);
}






