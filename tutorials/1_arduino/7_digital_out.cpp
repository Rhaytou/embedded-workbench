/* --------------- */
/* Title: Advanced Digital Output with LED State Management */
/* --------------- */
/*
    Description:
        - Demonstrates professional digital output control with LED
        - Implements non-blocking timing using millis() for multi-tasking
        - Uses state machine architecture for robust output control
        - Includes configurable blink patterns and timing parameters
        - Provides comprehensive system monitoring and debugging
        - Demonstrates output sequencing and pattern generation

    Requirements:
        - 1 LED
        - 1 Resistor (220Ω recommended)
        - Wiring:
            Arduino pin 13 -> Resistor -> LED Anode (+)
            LED Cathode (-) -> GND

    Steps to run:
        1. Copy the code into the main.cpp file in the workspace/arduino/src folder
        2. make build BOARD=arduino
        3. make upload BOARD=arduino
        4. make monitor BOARD=arduino
*/

#include <Arduino.h>

// Constants
// -----------------------
const int LED_PIN = 13;              // Digital output pin for LED
const unsigned long STATUS_UPDATE_INTERVAL = 1000;  // ms between status updates

// Timing Configuration - Easily modifiable behavior
const unsigned long BLINK_INTERVAL = 500;          // Base blink timing
const unsigned long PATTERN_CYCLE_TIME = 5000;     // Time between pattern changes

// LED Operation Modes
enum LEDMode {
    MODE_SOLID_ON,                   // Constant ON state
    MODE_SOLID_OFF,                  // Constant OFF state
    MODE_SLOW_BLINK,                 // Slow blinking pattern
    MODE_FAST_BLINK,                 // Fast blinking pattern
    MODE_HEARTBEAT,                  // Heartbeat pattern (short-long pulses)
    MODE_SOS                         // SOS pattern in Morse code
};

// Global Variables
// -----------------------
LEDMode currentMode = MODE_SLOW_BLINK;  // Current LED operation mode
bool ledState = false;               // Current physical LED state (true=ON, false=OFF)
unsigned long previousUpdateTime = 0; // Timer for non-blocking delays
unsigned long previousPatternTime = 0; // Timer for pattern cycling
unsigned long previousStatusTime = 0;  // Timer for status updates
unsigned long cycleCount = 0;        // Count of completed blink cycles

// Function Declarations
// -----------------------
void updateLEDState();               // Updates LED based on current mode and timing
void cycleOperationMode();           // Cycles through different LED modes
void printSystemStatus();            // Prints comprehensive system status
void executeHeartbeatPattern();      // Implements heartbeat pattern
void executeSOSPattern();            // Implements SOS Morse code pattern

// Setup Function
// -----------------------
/*
    setup() runs once at the start. It is used to:
      - Configure digital output pin for LED control
      - Initialize serial communication for monitoring
      - Set initial timing baselines for non-blocking operations
      - Establish initial system state and user guidance
*/
void setup() {
    // Configure LED pin as OUTPUT
    pinMode(LED_PIN, OUTPUT);

    // Initialize LED to OFF state
    digitalWrite(LED_PIN, LOW);
    ledState = false;

    // Initialize Serial communication at 9600 baud
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for serial port to connect
    }

    // Set initial timing baselines
    previousUpdateTime = millis();
    previousPatternTime = millis();
    previousStatusTime = millis();

    Serial.println("Advanced Digital Output: LED State Management System");
    Serial.println("====================================================");
    Serial.println("Features: Non-blocking timing, State Machine, Multiple Patterns");
    Serial.println();
    Serial.println("LED will automatically cycle through different patterns:");
    Serial.println("- Solid ON, Solid OFF, Slow Blink, Fast Blink, Heartbeat, SOS");
    Serial.println("---------------------------------------------");
}

// Loop Function
// -----------------------
/*
    loop() runs repeatedly after setup() finishes.
    It is used to:
      - Update LED state using non-blocking timing
      - Cycle through operation modes automatically
      - Provide system status updates
      - Maintain all timing without blocking delays
*/
void loop() {
    // Update LED state based on current mode (non-blocking)
    updateLEDState();

    // Cycle operation mode every PATTERN_CYCLE_TIME milliseconds
    cycleOperationMode();

    // Update status display at controlled interval
    if (millis() - previousStatusTime >= STATUS_UPDATE_INTERVAL) {
        printSystemStatus();
        previousStatusTime = millis();
    }
}

// LED State Update Function
// -----------------------
/*
    updateLEDState() implements non-blocking LED control using millis().
    This approach allows multiple operations to run concurrently without
    blocking the processor with delay() calls.

    NON-BLOCKING TIMING CONCEPT:
    Instead of stopping everything with delay(), we check how much time
    has passed since the last action and only act when enough time has
    elapsed. This enables multi-tasking in embedded systems.
*/
void updateLEDState() {
    unsigned long currentTime = millis();

    // Execute different behaviors based on current mode
    switch (currentMode) {
        case MODE_SOLID_ON:
            if (!ledState) {
                digitalWrite(LED_PIN, HIGH);
                ledState = true;
            }
            break;

        case MODE_SOLID_OFF:
            if (ledState) {
                digitalWrite(LED_PIN, LOW);
                ledState = false;
            }
            break;

        case MODE_SLOW_BLINK:
            if (currentTime - previousUpdateTime >= 1000) { // Slow blink: 1 second
                ledState = !ledState;
                digitalWrite(LED_PIN, ledState ? HIGH : LOW);
                previousUpdateTime = currentTime;
                if (ledState) cycleCount++; // Count ON cycles
            }
            break;

        case MODE_FAST_BLINK:
            if (currentTime - previousUpdateTime >= 250) { // Fast blink: 0.25 seconds
                ledState = !ledState;
                digitalWrite(LED_PIN, ledState ? HIGH : LOW);
                previousUpdateTime = currentTime;
                if (ledState) cycleCount++; // Count ON cycles
            }
            break;

        case MODE_HEARTBEAT:
            executeHeartbeatPattern();
            break;

        case MODE_SOS:
            executeSOSPattern();
            break;
    }
}

// Pattern Cycling Function
// -----------------------
/*
    cycleOperationMode() automatically rotates through LED modes
    using non-blocking timing. This demonstrates how to create
    automated sequences without complex scheduling systems.

    STATE MACHINE CONCEPT:
    The system moves between predefined states (modes) based on
    time or events. Each state has specific behavior, making
    complex sequences manageable and predictable.
*/
void cycleOperationMode() {
    if (millis() - previousPatternTime >= PATTERN_CYCLE_TIME) {
        // Cycle to next mode
        currentMode = static_cast<LEDMode>((currentMode + 1) % 6);
        previousPatternTime = millis();
        cycleCount = 0; // Reset cycle counter for new pattern

        Serial.print(">>> Mode Changed to: ");
        switch (currentMode) {
            case MODE_SOLID_ON: Serial.println("SOLID ON"); break;
            case MODE_SOLID_OFF: Serial.println("SOLID OFF"); break;
            case MODE_SLOW_BLINK: Serial.println("SLOW BLINK"); break;
            case MODE_FAST_BLINK: Serial.println("FAST BLINK"); break;
            case MODE_HEARTBEAT: Serial.println("HEARTBEAT"); break;
            case MODE_SOS: Serial.println("SOS PATTERN"); break;
        }
    }
}

// Heartbeat Pattern Function
// -----------------------
/*
    executeHeartbeatPattern() creates a biological heartbeat pattern
    (short pulse, pause, long pulse, long pause). This demonstrates
    how to create complex timing sequences by combining simple states.

    SEQUENCE GENERATION CONCEPT:
    Complex patterns can be created by breaking them into simple
    timed steps. This approach works for any sequential process.
*/
void executeHeartbeatPattern() {
    static unsigned long patternStartTime = 0;
    static int patternStep = 0;

    unsigned long currentTime = millis();
    unsigned long stepTime = currentTime - patternStartTime;

    switch (patternStep) {
        case 0: // First short pulse
            if (!ledState) {
                digitalWrite(LED_PIN, HIGH);
                ledState = true;
                patternStartTime = currentTime;
            }
            if (stepTime >= 100) { // Short pulse duration
                patternStep = 1;
            }
            break;

        case 1: // First pause
            if (ledState) {
                digitalWrite(LED_PIN, LOW);
                ledState = false;
                patternStartTime = currentTime;
            }
            if (stepTime >= 100) { // Short pause
                patternStep = 2;
            }
            break;

        case 2: // Second longer pulse
            if (!ledState) {
                digitalWrite(LED_PIN, HIGH);
                ledState = true;
                patternStartTime = currentTime;
                cycleCount++; // Count complete heartbeat cycles
            }
            if (stepTime >= 300) { // Long pulse duration
                patternStep = 3;
            }
            break;

        case 3: // Long pause between heartbeats
            if (ledState) {
                digitalWrite(LED_PIN, LOW);
                ledState = false;
                patternStartTime = currentTime;
            }
            if (stepTime >= 1000) { // Long pause
                patternStep = 0; // Restart pattern
            }
            break;
    }
}

// SOS Pattern Function
// -----------------------
/*
    executeSOSPattern() implements Morse code for SOS (··· --- ···)
    This demonstrates how to encode information in timing patterns
    and create recognizable communication signals.

    PROTOCOL IMPLEMENTATION CONCEPT:
    Many embedded systems use timing patterns for communication.
    This same approach works for IR remotes, serial protocols,
    and sensor data interpretation.
*/
void executeSOSPattern() {
    static unsigned long patternStartTime = 0;
    static int patternStep = 0;
    static const int sosPattern[] = {3, 3, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 7};
    // 3=dots, 7=dashes, 1=pauses between elements

    unsigned long currentTime = millis();
    unsigned long stepTime = currentTime - patternStartTime;
    int currentDuration = sosPattern[patternStep] * 200; // Convert to milliseconds

    if (stepTime >= currentDuration) {
        patternStep = (patternStep + 1) % 19; // Move to next step in pattern
        patternStartTime = currentTime;

        // Toggle LED for dots and dashes, keep off for pauses
        if (sosPattern[patternStep] == 3 || sosPattern[patternStep] == 7) {
            digitalWrite(LED_PIN, HIGH);
            ledState = true;
            if (sosPattern[patternStep] == 3) cycleCount++; // Count dots as cycles
        } else {
            digitalWrite(LED_PIN, LOW);
            ledState = false;
        }
    }
}

// System Status Printing Function
// -----------------------
/*
    printSystemStatus() provides comprehensive system monitoring
    with information about current mode, timing, and system state.

    SYSTEM TELEMETRY CONCEPT:
    Regular status reporting is essential for debugging and
    monitoring embedded systems. This structure scales to
    complex systems with multiple sensors and actuators.
*/
void printSystemStatus() {
    Serial.println("=== LED CONTROL SYSTEM STATUS ===");

    // Current mode and state
    Serial.print("Mode: ");
    switch (currentMode) {
        case MODE_SOLID_ON: Serial.print("SOLID ON"); break;
        case MODE_SOLID_OFF: Serial.print("SOLID OFF"); break;
        case MODE_SLOW_BLINK: Serial.print("SLOW BLINK"); break;
        case MODE_FAST_BLINK: Serial.print("FAST BLINK"); break;
        case MODE_HEARTBEAT: Serial.print("HEARTBEAT"); break;
        case MODE_SOS: Serial.print("SOS PATTERN"); break;
    }
    Serial.print(" | LED State: ");
    Serial.println(ledState ? "ON" : "OFF");

    // Performance metrics
    Serial.print("Cycle Count: ");
    Serial.println(cycleCount);

    // System uptime
    Serial.print("Uptime: ");
    Serial.print(millis() / 1000);
    Serial.println(" seconds");

    // Next pattern change indicator
    unsigned long timeUntilChange = PATTERN_CYCLE_TIME - (millis() - previousPatternTime);
    Serial.print("Next pattern in: ");
    Serial.print(timeUntilChange / 1000);
    Serial.println(" seconds");

    Serial.println("---------------------------------");
}

/*
    EDUCATIONAL CONCEPTS FOR TRANSFER TO OTHER PROJECTS:

    1. NON-BLOCKING TIMING ARCHITECTURE:
    -----------------------------------
    Essential for any responsive embedded system. Applications:
    - Reading multiple sensors simultaneously
    - Controlling multiple actuators independently
    - Maintaining communication while performing tasks
    - Creating complex timing sequences without blocking

    2. STATE MACHINE DESIGN:
    ----------------------
    Fundamental pattern for managing complex behavior:
    - User interface modes (menu systems)
    - System operational states (startup, running, error)
    - Protocol handling (communication states)
    - Process control (sequential operations)

    3. CONFIGURATION-DRIVEN BEHAVIOR:
    --------------------------------
    Separating configuration from logic enables:
    - Easy behavior modification without code changes
    - Parameter tuning during development
    - Different operating modes for various conditions
    - Maintainable and adaptable code structure

    4. PATTERN AND SEQUENCE GENERATION:
    ---------------------------------
    Creating complex behaviors from simple elements:
    - Motor control sequences (acceleration profiles)
    - Audio patterns (beeps, alarms, melodies)
    - Display animations (scrolling text, graphics)
    - Communication protocols (data packet timing)

    5. MODULAR FUNCTION ORGANIZATION:
    -------------------------------
    Breaking complex systems into manageable pieces:
    - Each function has single responsibility
    - Easy to test and debug individual components
    - Code reuse across different projects
    - Team collaboration on different system parts

    PRACTICAL APPLICATIONS:

    Home Automation:
    - Non-blocking timing for multiple device control
    - State machines for room occupancy detection
    - Pattern generation for status indicators

    Robotics:
    - State machines for autonomous behavior sequences
    - Non-blocking sensor reading during movement
    - Pattern generation for communication lights

    Industrial Control:
    - Sequence control for manufacturing processes
    - State machines for machine operational modes
    - Non-blocking monitoring during operations
*/





































































































