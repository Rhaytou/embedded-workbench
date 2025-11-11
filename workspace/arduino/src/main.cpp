/* --------------- */
/* Blink the BUILTIN LED */
/* --------------- */
/*
    * No need for any other component than an arduino, this simple code blink the bultin led.
*/
#include <Arduino.h>

void setup() {
    pinMode(LED_BUILTIN, OUTPUT); // or pinMode(13, OUTPUT);
}

void loop() {
    digitalWrite(13, HIGH);
    delay(2000);
    digitalWrite(13, LOW);
    delay(1000);
}
























