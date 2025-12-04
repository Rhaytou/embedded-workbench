/* --------------- */
/* Title: Reading an Analog Input (Potentiometer) with Voltage Calculation */
/* --------------- */
/*
    Description:
        - Demonstrates how to read analog values from a potentiometer
        - Converts raw ADC readings to actual voltage values
        - Explains Arduino's 10-bit ADC resolution and voltage scaling
        - Provides real-time monitoring of both digital and analog values
        - Includes comprehensive Serial output for educational purposes

    Requirements:
        - 1 Potentiometer (3 pins)
        - Wiring:
            Potentiometer VCC  -> 5V
            Potentiometer GND  -> GND
            Potentiometer OUT  -> A0

    Steps to run:
        1. Copy the code into the main.cpp file in the workspace/arduino/src folder
        2. make build BOARD=arduino
        3. make upload BOARD=arduino
        4. make monitor BOARD=arduino
*/

#include <Arduino.h>

// Constants
// -----------------------
const int POTENTIOMETER_PIN = A0;    // Analog pin for potentiometer
const int SERIAL_BAUD_RATE = 9600;   // Serial communication speed
const int READ_DELAY = 1000;          // ms delay between readings

// Global Variables
// -----------------------
int rawADCValue = 0;                 // Stores raw analog reading (0-1023)
float calculatedVoltage = 0.0;       // Stores calculated voltage (0.0-5.0V)

// Function Declarations
// -----------------------
void printSensorData();              // Prints formatted sensor data to Serial

// Setup Function
// -----------------------
/*
    setup() runs once at the start. It is used to:
      - Initialize serial communication for data monitoring
      - Configure analog input pin for potentiometer
      - Provide initial user instructions and system readiness
*/
void setup() {
    // Initialize Serial communication at 9600 baud
    Serial.begin(SERIAL_BAUD_RATE);

    // Wait for serial port to connect (important for some boards)
    while (!Serial) {
        ; // Wait for serial port to connect
    }

    // Configure analog pin A0 as input (default state, but explicit for clarity)
    pinMode(POTENTIOMETER_PIN, INPUT);

    Serial.println("Analog Input Example: Potentiometer with Voltage Calculation");
    Serial.println("Turn the potentiometer knob to see changing values!");
    Serial.println("==========================================================");
}

// Loop Function
// -----------------------
/*
    loop() runs repeatedly after setup() finishes.
    It is used to:
      - Read raw analog values from the potentiometer
      - Convert ADC readings to actual voltage values
      - Display both raw and converted values via Serial
      - Maintain readable output with appropriate delays
*/
void loop() {
    // ANALOG-TO-DIGITAL CONVERSION
    // Read the raw analog value from pin A0
    // Arduino's 10-bit ADC returns values from 0 to 1023
    rawADCValue = analogRead(POTENTIOMETER_PIN);

    // VOLTAGE CALCULATION
    // Convert ADC reading to actual voltage
    // Formula: Voltage = (ADC_Value / 1023) × 5.0V
    // 1023 represents maximum digital value (2^10 - 1)
    // 5.0V represents the reference voltage
    calculatedVoltage = rawADCValue * (5.0 / 1023.0);

    // Display the sensor data in formatted output
    printSensorData();

    // Small delay for Serial Monitor readability
    // Prevents data from scrolling too quickly
    delay(READ_DELAY);
}

// Data Printing Function
// -----------------------
/*
    printSensorData() formats and displays sensor readings.
    It shows:
      - Raw ADC value (0-1023) for digital understanding
      - Calculated voltage (0.0-5.0V) for analog understanding
      - Visual indicator of potentiometer position
*/
void printSensorData() {
    Serial.print("Raw ADC Value: ");
    Serial.print(rawADCValue);
    Serial.print(" | Voltage: ");
    Serial.print(calculatedVoltage, 2);  // 2 decimal places for voltage
    Serial.println("V");

    // Optional: Visual progress bar for potentiometer position
    Serial.print("Position: [");
    int barLength = map(rawADCValue, 0, 1023, 0, 20);  // Scale to 20 characters
    for (int i = 0; i < 20; i++) {
        if (i < barLength) {
            Serial.print("=");
        } else {
            Serial.print(" ");
        }
    }
    Serial.println("]");

    Serial.println("---");  // Separator for better readability
}





