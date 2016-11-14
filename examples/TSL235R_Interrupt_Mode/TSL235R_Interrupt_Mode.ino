#include <TSL235R.h>

// Adjust the sensor and interrupt pin numbers as needed
const char SENSOR_PIN = 4;
const char INTERRUPT_PIN = 4;

unsigned long lastTime = millis();
int delayTimeMillis = 1000;
int elapsedTime = 0;

// Create our sensor object
TSL235R sensor(SENSOR_PIN, INTERRUPT_MODE);

void setup() {
    // Set up serial transmission
    Serial.begin(115200);

    // Attach an interrupt
    // It's better to do this in the main code since a lot depends on the board being used.
    attachInterrupt(INTERRUPT_PIN, sensorISR, RISING);

    // Update last time
    lastTime = millis();
}

void loop() {
    // Calculated the elapsed time
    elapsedTime = millis() - lastTime;

    // Only print if the desired delay has been met
    if (elapsedTime >= delayTimeMillis) {
        // Print a reading
        Serial.println(sensor.read());

        // Increment the lastTime
        lastTime += elapsedTime;
    }
}

void sensorISR() {
    // Call the sensor function to handle the interrupt
    sensor.handleInterrupt();
}