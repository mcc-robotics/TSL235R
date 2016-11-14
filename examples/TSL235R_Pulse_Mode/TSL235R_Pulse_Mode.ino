#include <TSL235R.h>

// Adjust the sensor and interrupt pin numbers as needed
const char SENSOR_PIN = 4;

unsigned long lastTime = millis();
int delayTimeMillis = 1000;

TSL235R sensor(SENSOR_PIN, PULSE_MODE);

void setup() {
    // Set up serial transmission
    Serial.begin(115200);
}

void loop() {

    // Print a reading
    Serial.println(sensor.read());

    // wait for a second
    delay(delayTimeMillis);
}