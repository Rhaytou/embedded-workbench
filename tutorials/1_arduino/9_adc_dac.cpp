/* --------------- */
/* Title: Advanced ADC & DAC with Potentiometer and PWM Control */
/* --------------- */
/*
    Description:
        - Demonstrates professional Analog-to-Digital Conversion (ADC) techniques
        - Implements Digital-to-Analog Conversion (DAC) using PWM with multiple outputs
        - Features comprehensive data visualization and system monitoring
        - Includes voltage calculations and real-time performance metrics
        - Provides both Serial Monitor and Serial Plotter compatible output

    Requirements:
        - Arduino board (Uno, Nano, etc.)
        - 1x Potentiometer (10k recommended)
        - 2x LEDs
        - 2x 220Ω resistors (for LEDs)

        Wiring:
            Potentiometer:
                Arduino 5V → Potentiometer left pin
                Arduino A0 → Potentiometer middle pin
                Arduino GND → Potentiometer right pin

            LEDs (PWM demonstration):
                Arduino Pin 9 → 220Ω resistor → LED → GND
                Arduino Pin 3 → 220Ω resistor → LED → GND

    Steps to run:
        1. Copy the code into the main.cpp file in the workspace/arduino/src folder
        2. make build BOARD=arduino
        3. make upload BOARD=arduino
        4. make monitor BOARD=arduino
*/

#include <Arduino.h>

// Constants
// -----------------------
const int POTENTIOMETER_PIN = A0;    // Analog input pin for potentiometer
const int PWM_LED1_PIN = 9;          // PWM output pin 1 (must be PWM-capable)
const int PWM_LED2_PIN = 3;          // PWM output pin 2 (must be PWM-capable)
const int SERIAL_BAUD_RATE = 9600;   // Serial communication speed
const unsigned long UPDATE_INTERVAL = 100; // ms between ADC readings
const unsigned long STATUS_INTERVAL = 2000; // ms between detailed status updates

// Global Variables
// -----------------------
int rawADCValue = 0;                 // Raw ADC reading (0-1023)
int pwmOutputValue = 0;              // PWM output value (0-255)
float inputVoltage = 0.0;            // Calculated input voltage (0.0-5.0V)
float pwmVoltage = 0.0;              // Effective PWM voltage (0.0-5.0V)
unsigned long lastUpdateTime = 0;    // Timer for ADC updates
unsigned long lastStatusTime = 0;    // Timer for status displays

// Function Declarations
// -----------------------
void readAnalogInput();              // Reads and processes potentiometer values
void updatePWMOutputs();             // Controls PWM outputs based on input
void printSystemStatus();            // Prints comprehensive system status
void printPlotterData();             // Prints data formatted for Serial Plotter

// Setup Function
// -----------------------
/*
    setup() runs once at the start. It is used to:
      - Initialize serial communication for monitoring
      - Configure analog input pin for potentiometer
      - Configure PWM output pins for LED control
      - Establish initial timing baselines
      - Provide user guidance and system information
*/
void setup() {
    // Initialize Serial communication at 9600 baud
    Serial.begin(SERIAL_BAUD_RATE);
    while (!Serial) {
        ; // Wait for serial port to connect
    }

    // Configure analog pin A0 as INPUT for potentiometer
    pinMode(POTENTIOMETER_PIN, INPUT);

    // Configure PWM pins as OUTPUT for LED control
    pinMode(PWM_LED1_PIN, OUTPUT);
    pinMode(PWM_LED2_PIN, OUTPUT);

    // Initialize timing baselines
    lastUpdateTime = millis();
    lastStatusTime = millis();

    Serial.println("Advanced ADC & DAC: Potentiometer to PWM Control System");
    Serial.println("=======================================================");
    Serial.println("Features: Analog Input, PWM Output, Voltage Conversion");
    Serial.println();
    Serial.println("Rotate potentiometer to control LED brightness");
    Serial.println("LED1: Direct control | LED2: Inverted control");
    Serial.println("---------------------------------------------");
}

// Loop Function
// -----------------------
/*
    loop() runs repeatedly after setup() finishes.
    It is used to:
      - Read analog input values at controlled intervals
      - Update PWM outputs based on input processing
      - Provide system status and visualization data
      - Maintain timing for both monitoring and control
*/
void loop() {
    // Read analog input at controlled interval (non-blocking)
    if (millis() - lastUpdateTime >= UPDATE_INTERVAL) {
        readAnalogInput();
        updatePWMOutputs();
        printPlotterData();  // Continuous data for plotting
        lastUpdateTime = millis();
    }

    // Print detailed status at longer intervals
    if (millis() - lastStatusTime >= STATUS_INTERVAL) {
        printSystemStatus();
        lastStatusTime = millis();
    }
}

// Analog Input Reading Function
// -----------------------
/*
    readAnalogInput() performs analog-to-digital conversion and calculations.
    It demonstrates:
      - ADC resolution understanding (10-bit = 0-1023)
      - Voltage calculation from digital values
      - Signal processing and value validation

    ADC EDUCATIONAL CONCEPT:
    Arduino's 10-bit ADC converts analog voltages (0-5V) to digital values (0-1023).
    Each step represents approximately 4.9mV (5V / 1024 steps).
*/
void readAnalogInput() {
    // Read raw analog value from potentiometer
    rawADCValue = analogRead(POTENTIOMETER_PIN);

    // Calculate actual input voltage
    // Formula: Voltage = (ADC_Value × Reference_Voltage) / ADC_Resolution
    inputVoltage = rawADCValue * (5.0 / 1023.0);

    // Map ADC range (0-1023) to PWM range (0-255) for output
    // This demonstrates range conversion between different resolutions
    pwmOutputValue = map(rawADCValue, 0, 1023, 0, 255);
}

// PWM Output Control Function
// -----------------------
/*
    updatePWMOutputs() demonstrates digital-to-analog conversion using PWM.
    It shows:
      - Direct control mapping (input directly controls output)
      - Complementary control (inverted relationship)
      - PWM as a DAC technique for analog simulation

    PWM EDUCATIONAL CONCEPT:
    Pulse Width Modulation creates an analog-like effect by rapidly switching
    digital output on/off. The duty cycle (on-time percentage) determines the
    effective voltage seen by devices like LEDs.
*/
void updatePWMOutputs() {
    // Direct control: LED brightness follows potentiometer position
    analogWrite(PWM_LED1_PIN, pwmOutputValue);

    // Complementary control: LED brightness inversely follows potentiometer
    analogWrite(PWM_LED2_PIN, 255 - pwmOutputValue);

    // Calculate effective PWM voltage for educational purposes
    pwmVoltage = pwmOutputValue * (5.0 / 255.0);
}

// System Status Printing Function
// -----------------------
/*
    printSystemStatus() provides comprehensive system monitoring with
    detailed technical information. This format is optimized for
    educational understanding and debugging.

    TELEMETRY CONCEPT:
    Regular system status reporting is essential for understanding
    system behavior, debugging issues, and verifying correct operation.
*/
void printSystemStatus() {
    Serial.println("=== ADC & DAC SYSTEM STATUS ===");

    // Input section - Potentiometer data
    Serial.println("INPUT (Potentiometer):");
    Serial.print("  ADC Raw: ");
    Serial.print(rawADCValue);
    Serial.print("/1023 | Voltage: ");
    Serial.print(inputVoltage, 2);
    Serial.println("V");

    // Input visual indicator
    Serial.print("  Position: [");
    int inputBar = map(rawADCValue, 0, 1023, 0, 20);
    for (int i = 0; i < 20; i++) {
        Serial.print(i < inputBar ? "=" : " ");
    }
    Serial.println("]");

    // Output section - PWM control data
    Serial.println("OUTPUT (PWM Control):");
    Serial.print("  PWM Value: ");
    Serial.print(pwmOutputValue);
    Serial.print("/255 | Effective Voltage: ");
    Serial.print(pwmVoltage, 2);
    Serial.println("V");

    Serial.print("  LED1 Brightness: ");
    Serial.print((pwmOutputValue * 100) / 255);
    Serial.print("% | LED2 Brightness: ");
    Serial.print(((255 - pwmOutputValue) * 100) / 255);
    Serial.println("%");

    // Output visual indicators
    Serial.print("  LED1: [");
    int led1Bar = map(pwmOutputValue, 0, 255, 0, 10);
    for (int i = 0; i < 10; i++) {
        Serial.print(i < led1Bar ? "#" : " ");
    }
    Serial.print("] LED2: [");
    int led2Bar = map(255 - pwmOutputValue, 0, 255, 0, 10);
    for (int i = 0; i < 10; i++) {
        Serial.print(i < led2Bar ? "#" : " ");
    }
    Serial.println("]");

    Serial.println("---------------------------------");
}

// Serial Plotter Data Function
// -----------------------
/*
    printPlotterData() provides data formatted specifically for the
    Arduino Serial Plotter. This allows visual representation of
    the system behavior over time.

    DATA VISUALIZATION CONCEPT:
    The Serial Plotter can graph multiple variables simultaneously,
    making it excellent for understanding relationships and trends
    in sensor data and system behavior.
*/
void printPlotterData() {
    // Format for Serial Plotter - simple comma-separated values
    // The plotter automatically detects multiple data streams
    Serial.print("ADC:");
    Serial.print(rawADCValue);
    Serial.print(",PWM:");
    Serial.println(pwmOutputValue);
}

/*
    EDUCATIONAL CONCEPTS FOR TRANSFER TO OTHER PROJECTS:

    1. ADC RESOLUTION AND SCALING:
    -----------------------------
    Understanding bit depth and value ranges:
    - 10-bit ADC: 0-1023 (Arduino Uno/Nano)
    - 12-bit ADC: 0-4095 (many ESP32, STM32)
    - Always check your microcontroller's ADC resolution
    - Scale values appropriately for different ranges

    2. PWM AS DIGITAL-TO-ANALOG CONVERSION:
    --------------------------------------
    Using PWM to simulate analog outputs:
    - 8-bit PWM: 0-255 (standard Arduino)
    - Higher resolution PWM on advanced boards
    - Effective voltage = (Duty_Cycle × Max_Voltage)
    - Applications: LED dimming, motor speed control, audio generation

    3. SIGNAL MAPPING AND TRANSFORMATION:
    ------------------------------------
    Converting between different value ranges:
    - Use map() function for linear transformations
    - Create custom functions for non-linear responses
    - Implement calibration for sensor-specific ranges
    - Apply filtering for noisy signals

    4. COMPLEMENTARY CONTROL PATTERNS:
    --------------------------------
    Creating opposing or related outputs:
    - Direct and inverted control (as shown)
    - Differential signals for motor control
    - Balanced systems with counter-acting elements
    - Proportional-Integral-Derivative (PID) control systems

    5. DATA VISUALIZATION STRATEGIES:
    --------------------------------
    Multiple output formats for different purposes:
    - Detailed status for debugging and education
    - Plotter-friendly data for trend analysis
    - Minimal data for high-speed logging
    - Conditional output to prevent information overload

    PRACTICAL APPLICATIONS:

    Robotics:
    - ADC for potentiometer-based joint position sensing
    - PWM for precise motor speed control
    - Complementary PWM for H-bridge motor drivers

    Industrial Control:
    - ADC for process variable monitoring (temperature, pressure)
    - PWM for actuator control (valves, heaters)
    - Signal conditioning for sensor interfacing

    Audio Systems:
    - ADC for microphone input and audio sampling
    - PWM for simple audio output generation
    - Volume control using PWM duty cycle

    Instrumentation:
    - Multi-channel data acquisition systems
    - Calibration and linearization of sensor data
    - Real-time data logging and visualization
*/
















