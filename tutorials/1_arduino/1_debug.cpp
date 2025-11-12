/* --------------- */
/* Title: Debugging with Serial.println() */
/* --------------- */
/*
    Description:
        This example demonstrates how to use Serial.println() to debug
        your Arduino code. Serial debugging is a simple way to understand
        what your program is doing by printing messages or variable values
        to the Serial Monitor.

    Requirements:
        - No external components or wiring are needed.
        - Just upload this code and open the Serial Monitor.

    Steps to run:
        1. copy the code into the main.cpp file in the workspace/arduino/src folder
        2. make build BOARD=arduino
        3. make upload BOARD=arduino
        4. make monitor BOARD=arduino
*/

#include <Arduino.h>

void setup() {
    // Initialize the serial connection at a baud rate of 9600.
    // This must match the setting in your Serial Monitor.
    Serial.begin(9600);

    // Wait for the serial connection to start (helpful for some boards).
    while (!Serial) {
        ; // Wait for serial port to connect.
    }

    // Print a message to confirm setup has started.
    Serial.println("Setup started.");

    // Simulate an initialization step.
    Serial.println("Initializing system...");
    delay(1000); // Simulate a short delay

    // Confirm that setup is complete.
    Serial.println("Setup complete. Entering loop.");
}

void loop() {
    // Print a simple debug message.
    Serial.println("Loop running...");

    // You can imagine placing this inside a real program to check progress.
    delay(1000); // Wait one second before repeating
}








