#include <TSL235R.h>

TSL235R sensor(4, PULSE_MODE);

void setup() {
    // Set up serial transmission
    Serial.begin(115200);

}

void loop() {

    // Print a reading
    Serial.println(sensor.read());

    // wait for a second
    delay(1000);
}