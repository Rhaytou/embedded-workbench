/* --------------- */
/* Title: Controlling LED Brightness (Analog Output using PWM) */
/* --------------- */
/*
    Description:
        This example demonstrates how to use PWM (Pulse Width Modulation)
        to control the brightness of an LED. PWM simulates an analog output
        by rapidly switching the pin ON and OFF.

    Requirements:
        - 1 LED
        - 1 Resistor (220Ω recommended)
        - Wiring:
            Arduino pin 9 -> Resistor -> LED Anode (+)
            LED Cathode (-) -> GND

    Steps to run:
        1. copy the code into the main.cpp file in the workspace/arduino/src folder
        2. make build BOARD=arduino
        3. make upload BOARD=arduino
        4. make monitor BOARD=arduino
*/

#include <Arduino.h>

void setup() {
    pinMode(9, OUTPUT);
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for serial port to connect
    }

  Serial.println("Analog Output Example: LED Brightness Control");
}

void loop() {
    // Increase brightness
    for (int brightness = 0; brightness <= 255; brightness++) {
        analogWrite(9, brightness);
        Serial.print("Brightness: ");
        Serial.println(brightness);
        delay(10);
    }

    // Decrease brightness
    for (int brightness = 255; brightness >= 0; brightness--) {
        analogWrite(9, brightness);
        Serial.print("Brightness: ");
        Serial.println(brightness);
        delay(10);
    }
}










