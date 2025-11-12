/* --------------- */
/* Title: Reading a Digital Input (Push Button) */
/* --------------- */
/*
    Description:
        This example demonstrates how to read the state of a push button
        connected to a digital input pin. The program prints whether the
        button is pressed or released.

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
        1. copy the code into the main.cpp file in the workspace/arduino/src folder
        2. make build BOARD=arduino
        3. make upload BOARD=arduino
        4. make monitor BOARD=arduino
*/

#include <Arduino.h>

const int buttonPin = 2;

void setup() {
    pinMode(buttonPin, INPUT);
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for serial port to connect
    }

    Serial.println("Digital Input Example: Push Button");
}

void loop() {
    int buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH) {
        Serial.println("Button is PRESSED");
    } else {
        Serial.println("Button is RELEASED");
    }

    delay(300);
}









