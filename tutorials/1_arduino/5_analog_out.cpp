/* --------------- */
/* Title: Analog Output Control with Potentiometer and LED */
/* --------------- */
/*
    Description:
        - Demonstrates analog input reading from potentiometer
        - Controls LED brightness using PWM (Pulse Width Modulation)
        - Maps analog input values (0-1023) to PWM output values (0-255)
        - Provides real-time monitoring of input and output values
        - Shows relationship between voltage, ADC readings, and PWM duty cycle
        - Visual feedback through both Serial Monitor and LED brightness

    Requirements:
        - 1 Potentiometer (3 pins - vcc output grd)
        - 1 LED
        - 1 220Ω resistor (for LED current limiting)
        - Wiring:
            Potentiometer VCC  -> 5V
            Potentiometer GND  -> GND
            Potentiometer OUT  -> A0
            LED anode (+)      -> Pin 9 (with 220Ω resistor)
            LED cathode (-)    -> GND

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
const int LED_PIN = 9;               // PWM-capable pin for LED (marked with ~)
const int SERIAL_BAUD_RATE = 9600;   // Serial communication speed
const int READ_DELAY = 500;          // ms delay between readings

// PWM Configuration
const int PWM_MIN = 0;               // Minimum PWM value (LED off)
const int PWM_MAX = 255;             // Maximum PWM value (LED full brightness)
const int ADC_MIN = 0;               // Minimum ADC value
const int ADC_MAX = 1023;            // Maximum ADC value

// Global Variables
// -----------------------
int rawADCValue = 0;                 // Stores raw analog reading (0-1023)
int pwmValue = 0;                    // Stores PWM output value (0-255)
float inputVoltage = 0.0;            // Stores calculated input voltage (0.0-5.0V)
float outputDutyCycle = 0.0;         // Stores PWM duty cycle percentage

// Function Declarations
// -----------------------
void readSensorInput();              // Reads and processes potentiometer values
void controlLEDBrightness();         // Controls LED using PWM based on input
void printSystemStatus();            // Prints formatted system data to Serial

// Setup Function
// -----------------------
/*
    setup() runs once at the start. It is used to:
      - Initialize serial communication for data monitoring
      - Configure analog input pin for potentiometer
      - Configure PWM output pin for LED control
      - Provide initial user instructions and system readiness
*/
void setup() {
    // Initialize Serial communication at 9600 baud
    Serial.begin(SERIAL_BAUD_RATE);

    // Wait for serial port to connect (important for some boards)
    while (!Serial) {
        ; // Wait for serial port to connect
    }

    // Configure analog pin A0 as input for potentiometer
    pinMode(POTENTIOMETER_PIN, INPUT);

    // Configure digital pin 9 as OUTPUT for LED (PWM capable)
    pinMode(LED_PIN, OUTPUT);

    Serial.println("Analog Output Control: Potentiometer to LED Brightness");
    Serial.println("Turn potentiometer to control LED brightness!");
    Serial.println("=====================================================");
    Serial.println();
}

// Loop Function
// -----------------------
/*
    loop() runs repeatedly after setup() finishes.
    It is used to:
      - Read analog input values from potentiometer
      - Convert input values to PWM output values
      - Control LED brightness using PWM
      - Display system status via Serial Monitor
      - Maintain system timing and responsiveness
*/
void loop() {
    // Read and process sensor input values
    readSensorInput();

    // Control LED brightness based on sensor input
    controlLEDBrightness();

    // Display current system status
    printSystemStatus();

    // Small delay for stability and Serial Monitor readability
    delay(READ_DELAY);
}

// Input Reading Function
// -----------------------
/*
    readSensorInput() reads potentiometer values and performs calculations.
    It handles:
      - Analog-to-digital conversion from potentiometer
      - Voltage calculation for educational purposes
      - PWM value mapping from ADC range (0-1023) to PWM range (0-255)
      - Duty cycle calculation for output monitoring
*/
void readSensorInput() {
    // ANALOG-TO-DIGITAL CONVERSION
    // Read raw analog value from potentiometer (0-1023)
    rawADCValue = analogRead(POTENTIOMETER_PIN);

    // VOLTAGE CALCULATION
    // Convert ADC reading to actual input voltage (0.0-5.0V)
    inputVoltage = rawADCValue * (5.0 / 1023.0);

    // PWM VALUE MAPPING
    // Map ADC range (0-1023) to PWM range (0-255)
    // This scales the input to appropriate output range for LED control
    pwmValue = map(rawADCValue, ADC_MIN, ADC_MAX, PWM_MIN, PWM_MAX);

    // DUTY CYCLE CALCULATION
    // Calculate PWM duty cycle as percentage (0-100%)
    outputDutyCycle = (pwmValue / 255.0) * 100.0;
}

// LED Control Function
// -----------------------
/*
    controlLEDBrightness() outputs PWM signal to control LED brightness.
    It uses:
      - analogWrite() for PWM generation on supported pins
      - PWM values from 0 (always off) to 255 (always on)
      - Pulse Width Modulation to control effective voltage to LED
*/
void controlLEDBrightness() {
    // PWM OUTPUT
    // Generate PWM signal on LED pin
    // analogWrite() creates a square wave with varying duty cycle
    // 0 = 0% duty cycle (always off), 255 = 100% duty cycle (always on)
    analogWrite(LED_PIN, pwmValue);
}

// System Status Printing Function
// -----------------------
/*
    printSystemStatus() formats and displays comprehensive system data.
    It shows:
      - Input values from potentiometer (raw and voltage)
      - Output values to LED (PWM and duty cycle)
      - Visual indicators for both input and output
      - Real-time feedback of the control system
*/
void printSystemStatus() {
    // INPUT SECTION - Potentiometer Data
    Serial.println("=== INPUT (Potentiometer) ===");
    Serial.print("ADC Value: ");
    Serial.print(rawADCValue);
    Serial.print(" | Voltage: ");
    Serial.print(inputVoltage, 2);
    Serial.println("V");

    // Input visual indicator
    Serial.print("Input Level:  [");
    int inputBar = map(rawADCValue, 0, 1023, 0, 20);
    for (int i = 0; i < 20; i++) {
        Serial.print(i < inputBar ? "=" : " ");
    }
    Serial.println("]");

    // OUTPUT SECTION - LED Control Data
    Serial.println("=== OUTPUT (LED Control) ===");
    Serial.print("PWM Value: ");
    Serial.print(pwmValue);
    Serial.print(" | Duty Cycle: ");
    Serial.print(outputDutyCycle, 1);
    Serial.println("%");

    // Output visual indicator
    Serial.print("Brightness:   [");
    int outputBar = map(pwmValue, 0, 255, 0, 20);
    for (int i = 0; i < 20; i++) {
        Serial.print(i < outputBar ? "#" : " ");
    }
    Serial.println("]");

    // System separator
    Serial.println("-----------------------------");
    Serial.println();
}

/*
    EDUCATIONAL NOTES:

    PWM (Pulse Width Modulation) Explanation:
    ----------------------------------------
    PWM works by rapidly turning a digital output on and off. The ratio of
    on-time to off-time (duty cycle) determines the effective voltage.

    - 0% duty cycle: Always OFF (0V effective)
    - 50% duty cycle: ON half the time, OFF half the time (2.5V effective)
    - 100% duty cycle: Always ON (5V effective)

    Arduino's analogWrite() uses 8-bit resolution (0-255) where:
    - 0 = 0% duty cycle = 0V effective
    - 127 = 50% duty cycle = 2.5V effective
    - 255 = 100% duty cycle = 5V effective

    Only pins marked with ~ support PWM output on most Arduino boards.
*/






