/* --------------- */
/* Title: Controlling a Digital Output (LED On/Off) */
/* --------------- */
/*
    Description:
        This example demonstrates how to control a digital output pin
        by turning an LED ON and OFF at a fixed interval.

    Requirements:
        - 1 LED
        - 1 Resistor (220Ω recommended)
        - Wiring:
            Arduino pin 13 -> Resistor -> LED Anode (+)
            LED Cathode (-) -> GND

    Steps to run:
        1. copy the code into the main.cpp file in the workspace/arduino/src folder
        2. make build BOARD=arduino
        3. make upload BOARD=arduino
        4. make monitor BOARD=arduino
*/

#include <Arduino.h>

const int ledPin = 13;

void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for serial port to connect
    }

    Serial.println("Digital Output Example: LED On/Off");
}

void loop() {
    Serial.println("LED ON");
    digitalWrite(ledPin, HIGH);
    delay(1000);

    Serial.println("LED OFF");
    digitalWrite(ledPin, LOW);
    delay(1000);
}




