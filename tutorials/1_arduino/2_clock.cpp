/* --------------- */
/* Title: Advanced Clock with Time Tracking and Serial Debugging */
/* --------------- */
/*
    Description:
        This example demonstrates how to create a comprehensive clock system
        using Arduino. The program tracks hours, minutes, and seconds with
        proper time formatting and includes extensive debugging features.
        Learn to monitor time variables, track program execution flow,
        and understand real-time clock operation with non-blocking timing.

    Requirements:
        - No external components or wiring are needed.
        - Wiring:
            Just upload this code and open the Serial Monitor.

    Steps to run:
        1. Copy the code into the main.cpp file in the workspace/arduino/src folder
        2. make build BOARD=arduino
        3. make upload BOARD=arduino
        4. make monitor BOARD=arduino
*/

#include <Arduino.h>


// Global Variables
// -----------------------
// Variables to track elapsed time using millis()
unsigned long previousMillis = 0;   // Stores the last time the clock was updated
const unsigned long interval = 1000; // Interval for clock update in milliseconds (1 second)

// Structure to store time components
struct ClockTime {
    int hours;
    int minutes;
    int seconds;
};

// Initialize clock and counters
ClockTime currentTime = {0, 0, 0};  // Start at 00:00:00
int loopCounter = 0;                 // Counts the number of loop iterations
int debugCycle = 0;                  // Tracks debug cycles for detailed printing

// Setup Function
// -----------------------
/*
    setup() runs once when the Arduino starts.
    It is used to:
      - Initialize communication (Serial)
      - Set up initial variables and state
      - Print initial debugging information
      - Prepare the environment for the main loop
*/
void setup() {
    // Start serial communication at 9600 baud
    Serial.begin(9600);

    // Wait for Serial port to connect (important on some boards like Leonardo)
    while (!Serial) {
        ; // Do nothing until Serial is ready
    }

    Serial.println("=== Advanced Clock System ===");

    // Display initial time values
    Serial.print("Time initialized to: ");
    Serial.print(currentTime.hours);
    Serial.print(":");
    Serial.print(currentTime.minutes);
    Serial.print(":");
    Serial.println(currentTime.seconds);

    // Track program flow through setup
    Serial.println("Step 1: Starting clock configuration...");
    delay(500); // Small delay for readability

    Serial.println("Step 2: Time structure initialized");
    delay(500);

    Serial.println("Step 3: Millis tracking started");
    Serial.println("Setup complete - entering main loop");
}

// Loop Function
// -----------------------
/*
    loop() runs repeatedly after setup() finishes.
    It is used to:
      - Update clock time using millis() for non-blocking timing
      - Monitor and print debug information
      - Handle rollovers for seconds, minutes, and hours
      - Provide detailed debug output every few cycles
*/
void loop() {
    Serial.println("--- Loop cycle start ---");
    Serial.print("Loop counter: ");
    Serial.println(loopCounter);

    // Get the current time since program start
    unsigned long currentMillis = millis();

    // Print timing variables for debugging
    Serial.print("Current millis: ");
    Serial.println(currentMillis);
    Serial.print("Previous millis: ");
    Serial.println(previousMillis);
    Serial.print("Time difference: ");
    Serial.println(currentMillis - previousMillis);

    // Check if 1 second has passed
    if (currentMillis - previousMillis >= interval) {
        Serial.println(">>> One second interval reached");

        // Update last tick time
        previousMillis = currentMillis;

        // Increment seconds
        currentTime.seconds++;
        Serial.print("Seconds updated to: ");
        Serial.println(currentTime.seconds);

        // Handle second rollover
        if (currentTime.seconds >= 60) {
            Serial.println(">>> Second rollover detected");
            currentTime.seconds = 0;
            currentTime.minutes++;
            Serial.print("Minutes updated to: ");
            Serial.println(currentTime.minutes);
        }

        // Handle minute rollover
        if (currentTime.minutes >= 60) {
            Serial.println(">>> Minute rollover detected");
            currentTime.minutes = 0;
            currentTime.hours++;
            Serial.print("Hours updated to: ");
            Serial.println(currentTime.hours);
        }

        // Handle 24-hour rollover
        if (currentTime.hours >= 24) {
            Serial.println(">>> Hour rollover detected - New day");
            currentTime.hours = 0;
        }

        // Display current time in HH:MM:SS format
        Serial.print("Current time: ");
        Serial.print(currentTime.hours);
        Serial.print(":");
        Serial.print(currentTime.minutes);
        Serial.print(":");
        Serial.println(currentTime.seconds);

        // Special detection for midnight
        if (currentTime.hours == 0 && currentTime.minutes == 0 && currentTime.seconds == 0) {
            Serial.println("!!! MIDNIGHT - Time reset !!!");
        }

        // Print detailed debug info every 5 cycles
        if (debugCycle % 5 == 0) {
            Serial.println("--- Detailed Debug Info ---");
            Serial.print("Total seconds today: ");
            Serial.println(currentTime.hours * 3600 + currentTime.minutes * 60 + currentTime.seconds);
            Serial.print("Program running for: ");
            Serial.print(millis() / 1000);
            Serial.println(" seconds");
            Serial.print("Debug cycle: ");
            Serial.println(debugCycle);
        }

        debugCycle++;
    } else {
        Serial.println("Waiting for interval...");
    }

    // Track total running time
    Serial.print("System running for: ");
    Serial.print(millis());
    Serial.println(" milliseconds");

    loopCounter++;
    Serial.println("--- Loop cycle end ---");

    // Delay for readability (slows loop)
    delay(1000);
}














