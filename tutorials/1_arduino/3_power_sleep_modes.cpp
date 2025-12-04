/* --------------- */
/* Title: Arduino Power-Down Sleep Mode Example */
/* --------------- */
/*
    Description:
        - Implements power-down sleep mode with external wake-up
        - Automatically sleeps after 2 seconds of inactivity
        - Wakes on button press using FALLING edge interrupt
        - Includes button debouncing and power optimization
        - Built-in LED indicates sleep/awake states

    Requirements:
        - Arduino board (Uno, Nano, etc.)
        - One push button
        - No external resistors needed (uses internal pull-up)
        - Wiring:
            Arduino pin 2 -> Button one Pin
            Button other -> GND

    Steps to run:
        1. Copy the code into the main.cpp file in the workspace/arduino/src folder.
        2. make build BOARD=arduino
        3. make upload BOARD=arduino
        4. make monitor BOARD=arduino
*/

#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>

// Global Variables
// -----------------------
// VOLATILE variables for interrupt communication
volatile bool wakeFlag = false;             // Flag set when button is pressed
volatile unsigned long lastInterruptTime = 0; // Tracks last ISR call for debounce

// Constants
const unsigned long DEBOUNCE_TIME = 50;    // ms for button debounce
const unsigned long AWAKE_TIME = 2000;     // ms to stay awake after wake-up

// Function Declarations
// -----------------------
void wakeISR();      // Interrupt Service Routine for button press
void goToSleep();    // Puts Arduino into power-down sleep mode
void handleWake();   // Handles wake-up actions after button press

// Setup Function
// -----------------------
/*
    setup() runs once at the start. It is used to:
      - Initialize serial communication for debugging
      - Configure input pins and pull-ups
      - Configure output pins (LED)
      - Provide initial user feedback via Serial Monitor
*/
void setup() {
    // Initialize Serial communication at 9600 baud
    Serial.begin(9600);

    // Configure wake-up button on pin 2 with internal pull-up resistor
    pinMode(2, INPUT_PULLUP);

    // Configure built-in LED as output for sleep/awake status
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.println("System ready. Press button on pin 2 to wake from sleep.");
}

// Loop Function
// -----------------------
/*
    loop() runs repeatedly after setup() finishes.
    It is used to:
      - Handle wake-up events triggered by the ISR
      - Put Arduino into sleep after inactivity
      - Run normal application code when awake
*/
void loop() {
    // Handle wake event if flag is set
    if (wakeFlag) {
        handleWake();
    }

    // Automatically enter sleep after being awake for AWAKE_TIME
    static unsigned long awakeStart = millis(); // Track when Arduino last woke
    if (millis() - awakeStart > AWAKE_TIME && !wakeFlag) {
        goToSleep();
        awakeStart = millis(); // Reset awake timer after sleep
    }

    // Your normal application code goes here
    delay(100); // Small delay for loop stability
}

// Interrupt Service Routine (ISR)
// -----------------------
/*
    wakeISR() is triggered when the button on pin 2 is pressed.
    It sets a wake flag, but includes software debouncing to prevent
    multiple triggers from a single press.
    Keep ISR minimal to avoid blocking other operations.
*/
void wakeISR() {
    unsigned long currentTime = millis();

    // SOFTWARE DEBOUNCING
    if (currentTime - lastInterruptTime > DEBOUNCE_TIME) {
        wakeFlag = true;             // Set wake flag for main loop
        lastInterruptTime = currentTime; // Update last interrupt timestamp
    }
}

// Sleep Function
// -----------------------
/*
    goToSleep() puts Arduino into power-down sleep mode.
    Steps:
      1. Disable unnecessary peripherals for power optimization
      2. Attach wake-up interrupt on button pin
      3. Enable sleep mode and enter sleep_cpu()
      4. Resume execution here after wake-up
      5. Re-enable peripherals and detach interrupt
*/
void goToSleep() {
    Serial.println("Going to sleep...");
    Serial.flush();  // Ensure all Serial data is sent
    delay(100);

    // POWER OPTIMIZATION - Disable unused peripherals
    power_adc_disable();
    power_timer1_disable();
    power_timer2_disable();
    power_twi_disable();

    // Attach interrupt BEFORE sleeping
    attachInterrupt(digitalPinToInterrupt(2), wakeISR, FALLING);

    // Configure sleep mode
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();

    // Turn off LED to indicate sleeping
    digitalWrite(LED_BUILTIN, LOW);

    // Enter sleep (execution stops here until wake-up)
    sleep_cpu();

    // CODE RESUMES HERE AFTER WAKE-UP
    sleep_disable();

    // Re-enable all peripherals
    power_all_enable();

    // Detach interrupt to prevent repeated triggering
    detachInterrupt(digitalPinToInterrupt(2));
}

// Wake-Up Handler
// -----------------------
/*
    handleWake() runs after waking from sleep.
    It is used to:
      - Clear the wake flag
      - Provide visual and Serial feedback
      - Run tasks required upon wake-up (e.g., read sensors)
*/
void handleWake() {
    // Reset wake flag first
    wakeFlag = false;

    // Visual feedback using built-in LED
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.println("Awake! Button was pressed.");

    // Your wake-up tasks go here (reading sensors, sending data, etc.)

    // Keep LED on briefly for visual confirmation
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
}






