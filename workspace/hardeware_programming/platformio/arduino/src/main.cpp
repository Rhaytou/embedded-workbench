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
        2. make pio_build BOARD=arduino
        3. make pio_upload BOARD=arduino
        4. make pio_monitor BOARD=arduino
*/

#include <Arduino.h>

// Global Variables
int counter = 0;       // Tracks the number of loop cycles
int sensorValue = 0;   // Stores analog sensor readings


// Setup Function
/*
    The setup() function runs **once** when the Arduino board starts.
    It is used to:
      - Initialize hardware and communication
      - Set initial states of variables
      - Prepare the program environment before entering the loop
*/
void setup() {
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);

    // Wait for the serial port to be ready (important for some boards)
    while (!Serial) {
        ; // Do nothing until Serial is connected
    }

    Serial.println("=== Variable Debugging Example ===");

    // Debugging: show initial value of the counter
    Serial.print("Counter initialized to: ");
    Serial.println(counter);

    // Track program flow through setup
    Serial.println("Step 1: Starting configuration...");
    delay(500);  // Short delay for readability in Serial Monitor

    Serial.println("Step 2: Configuration complete");
    Serial.println("Setup complete - entering main loop");
}


// Loop Function
/*
    The loop() function runs **repeatedly** after setup() finishes.
    It is used to:
      - Perform ongoing tasks
      - Monitor and update variables
      - Read sensors or inputs continuously
      - Provide feedback via Serial or other outputs
*/
void loop() {
    Serial.println("--- Loop cycle start ---");

    // Monitor counter variable changes
    Serial.print("Current counter value: ");
    Serial.println(counter);

    // Simulate reading an analog sensor (e.g., potentiometer on A0)
    sensorValue = analogRead(A0);
    Serial.print("Analog read result: ");
    Serial.println(sensorValue);

    // Conditional debug logic
    if (counter % 3 == 0) {
        Serial.println(">>> Counter is divisible by 3");
    }

    // Track system uptime
    Serial.print("System running for: ");
    Serial.print(millis());
    Serial.println(" milliseconds");

    // Increment counter for next loop iteration
    counter++;

    Serial.println("--- Loop cycle end ---");

    // Delay to slow down loop for readability
    delay(2000);
}








