/* --------------- */
/* Title: Advanced Digital Input with Push Button and State Management */
/* --------------- */
/*
    Description:
        - Demonstrates professional digital input reading with push button
        - Implements software debouncing to eliminate mechanical switch noise
        - Tracks button state changes (press and release events)
        - Implements edge detection for precise event timing
        - Includes state machine for robust button handling
        - Provides comprehensive system monitoring with optimized display

    Requirements:
        - 1 Push button
        - 1 Resistor (10kΩ pull-down)
        - Wiring:
            Button one side  -> 5V
            Button other side -> Arduino pin 2
            Arduino pin 2     -> 10kΩ resistor -> GND

            Note:
                Use a breadboard.
                    Connect both the button leg and one side of the resistor to the same breadboard row.
                    Then run one jumper wire from that row to Arduino pin 2.

    Steps to run:
        1. Copy the code into the main.cpp file in the workspace/arduino/src folder
        2. make build BOARD=arduino
        3. make upload BOARD=arduino
        4. make monitor BOARD=arduino
*/

#include <Arduino.h>

// Constants
// -----------------------
const int BUTTON_PIN = 2;            // Digital input pin for button
const unsigned long DEBOUNCE_DELAY = 50;  // ms debounce time for switch stabilization
const unsigned long STATUS_UPDATE_INTERVAL = 1000;  // ms between status updates

// Global Variables
// -----------------------
int currentButtonState = LOW;        // Current debounced button state
int lastButtonState = LOW;           // Previous debounced button state
int rawButtonState = LOW;            // Raw immediate reading from pin
unsigned long lastDebounceTime = 0;  // Timer for debounce calculations
unsigned long pressCount = 0;        // Total number of button presses
unsigned long lastStatusUpdate = 0;  // Timer for status display updates
bool displayInitialized = false;     // Track if initial display is shown

// Function Declarations
// -----------------------
bool readDebouncedButton();          // Reads button with debounce processing
void handleButtonEvents();           // Handles button press/release events
void printSystemStatus();            // Prints comprehensive system status
void printInitialDisplay();          // Shows initial instructions

// Setup Function
// -----------------------
/*
    setup() runs once at the start. It is used to:
      - Configure digital input pin with proper mode
      - Initialize serial communication for monitoring
      - Set initial system state for debounce calculations
*/
void setup() {
    // Configure button pin as INPUT (no pull-up, using external pull-down)
    pinMode(BUTTON_PIN, INPUT);

    // Initialize Serial communication at 9600 baud
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for serial port to connect
    }

    // Read initial button state to establish baseline
    currentButtonState = digitalRead(BUTTON_PIN);
    lastButtonState = currentButtonState;
}

// Loop Function
// -----------------------
/*
    loop() runs repeatedly after setup() finishes.
    It is used to:
      - Read and debounce button input
      - Detect state changes and trigger events
      - Manage system timing and display updates
*/
void loop() {
    // Show initial display once
    if (!displayInitialized) {
        printInitialDisplay();
        displayInitialized = true;
    }

    // Read button with debounce processing
    bool buttonChanged = readDebouncedButton();

    // Handle button events if state changed (immediate feedback)
    if (buttonChanged) {
        handleButtonEvents();
    }

    // Update status display at controlled interval (non-blocking)
    if (millis() - lastStatusUpdate >= STATUS_UPDATE_INTERVAL) {
        printSystemStatus();
        lastStatusUpdate = millis();
    }
}

// Initial Display Function
// -----------------------
/*
    printInitialDisplay() shows setup information once at startup.
    This prevents repeated header printing while providing clear instructions.
*/
void printInitialDisplay() {
    Serial.println("Advanced Digital Input: Push Button with State Management");
    Serial.println("=========================================================");
    Serial.println("Features: Debouncing, Edge Detection, Event Tracking");
    Serial.println();
    Serial.println("ACTIONS - Immediate feedback on button events");
    Serial.println("STATUS  - Updates every second with system info");
    Serial.println();
    Serial.println("Press and release the button to see events...");
    Serial.println("---------------------------------------------");
}

// Debounced Button Reading Function
// -----------------------
/*
    readDebouncedButton() implements software debouncing to eliminate
    mechanical switch noise. This is CRITICAL for reliable button reading.

    DEBOUNCE CONCEPT:
    Mechanical switches physically bounce when pressed/released, causing
    multiple rapid state changes. Debouncing waits for a stable state
    before accepting the change.

    Returns: true if button state changed, false otherwise
*/
bool readDebouncedButton() {
    // Read raw button state immediately
    rawButtonState = digitalRead(BUTTON_PIN);

    // Check if button state has changed from last stable state
    if (rawButtonState != lastButtonState) {
        // Reset debounce timer on any change
        lastDebounceTime = millis();
    }

    // Only accept state change after debounce period has elapsed
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
        // If current reading is different from stable state, update
        if (rawButtonState != currentButtonState) {
            currentButtonState = rawButtonState;
            lastButtonState = currentButtonState;
            return true; // State change occurred
        }
    }

    // Update last state for next comparison
    lastButtonState = rawButtonState;
    return false; // No state change
}

// Button Event Handler Function
// -----------------------
/*
    handleButtonEvents() processes button state changes using edge detection.
    This separates the concepts of STATE (pressed/released) from EVENTS
    (press/release actions), which is essential for responsive interfaces.

    EDGE DETECTION CONCEPT:
    - RISING EDGE: Transition from LOW to HIGH (button press)
    - FALLING EDGE: Transition from HIGH to LOW (button release)
*/
void handleButtonEvents() {
    if (currentButtonState == HIGH) {
        // RISING EDGE DETECTED - Button pressed
        pressCount++;
        Serial.println(">>> BUTTON PRESSED! (Rising Edge Detected)");

    } else {
        // FALLING EDGE DETECTED - Button released
        Serial.println("<<< BUTTON RELEASED (Falling Edge Detected)");
    }
}

// System Status Printing Function
// -----------------------
/*
    printSystemStatus() provides comprehensive system monitoring
    at a readable interval. This demonstrates rate-limited debugging
    that prevents information overload while maintaining system awareness.
*/
void printSystemStatus() {
    Serial.println("=== SYSTEM STATUS ===");

    // Current state information
    Serial.print("Button State: ");
    Serial.println(currentButtonState == HIGH ? "PRESSED" : "RELEASED");

    // Event statistics
    Serial.print("Total Presses: ");
    Serial.println(pressCount);

    // System uptime
    Serial.print("Uptime: ");
    Serial.print(millis() / 1000);
    Serial.println(" seconds");

    // Next update indicator
    Serial.println("Next update in 1 second...");
    Serial.println();
}

/*
    EDUCATIONAL CONCEPTS FOR TRANSFER TO OTHER PROJECTS:

    1. RATE-LIMITED DISPLAY STRATEGY:
    --------------------------------
    Separating immediate event feedback from periodic status updates:
    - Events: Show immediately when they happen
    - Status: Update at fixed intervals for monitoring
    - Prevents Serial Monitor flooding while maintaining responsiveness

    2. NON-BLOCKING TIMING:
    ----------------------
    Using millis() instead of delay() allows:
    - Multiple operations to run concurrently
    - Responsive event handling during updates
    - Precise control over different timing requirements

    3. INFORMATION HIERARCHY:
    -----------------------
    Organizing output by importance:
    - Critical: Immediate event notifications
    - Important: Periodic system status
    - Reference: One-time setup information
    - This structure scales to complex systems

    4. STATE VS EVENT THINKING:
    -------------------------
    Critical distinction for robust systems:
    - STATES: Continuous conditions (button pressed)
    - EVENTS: Instantaneous occurrences (button press action)
    - Different handling strategies for each
*/

/*
    PRACTICAL APPLICATIONS OF THESE CONCEPTS:

    Home Automation:
    - Immediate: Light toggle on button press
    - Periodic: Energy usage statistics every minute

    Industrial Control:
    - Immediate: Emergency stop activation
    - Periodic: Machine status monitoring every 5 seconds

    Robotics:
    - Immediate: Sensor collision detection
    - Periodic: Battery level updates every 30 seconds

    Data Logging:
    - Immediate: Critical error recording
    - Periodic: Regular sensor data sampling
*/









