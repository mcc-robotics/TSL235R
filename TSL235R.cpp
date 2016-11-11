
#include <Arduino.h>
#include "TSL235R.h"

TSL235R::TSL235R(unsigned char dataPin) {
    // Set the default mode to use pulse mode since interrupt mode isn't working right now
    init(dataPin, PULSE_MODE);
}

TSL235R::TSL235R(unsigned char dataPin, char mode) {
    init(dataPin, mode);
}

void TSL235R::init(unsigned char dataPin, char mode) {
    // Set up the data pin
    TSL235R::dataPin = dataPin;
    pinMode(dataPin, INPUT);
    digitalWrite(dataPin, HIGH);

    // Set the desired mode
    TSL235R::mode = mode;

    // Default min and max and other variables
    min = 2000000;
    max = 0;
    lastTime = micros();
    sampleRateUS = 1000;
    interruptDuration = 0.0;
}

void TSL235R::handleInterrupt() {
    cli();
    unsigned long currentTime = micros();
    counter++;

    // Check if the sample rate has elapsed
    if ((currentTime - lastTime) >= sampleRateUS) {
        interruptDuration = sampleRateUS / counter;
        counter = 0;
        lastTime = currentTime;
    }

    sei();
}

unsigned long TSL235R::read() {
    unsigned long returnValue = 0;
    switch (mode) {
        case PULSE_MODE: {
            unsigned long pulseDuration = pulseIn(dataPin, HIGH);

            // Convert the result to frequency (# us in 1 second / pulse-width in us * 2)
            // Multiply the value by two since we only calculated the pulse width of half a cycle
            returnValue = 1000000 / (pulseDuration * 2);
            break;
        }
        case INTERRUPT_MODE: {
            // Convert the result to frequency, here we are actually calculating a full cycle but the sample rate
            returnValue = (unsigned long) (1000000 / interruptDuration);
            break;
        }
        default:
            returnValue = 0;
    }
    return returnValue;
}

char TSL235R::readCalibrated() {
    if (max ==0) {
        return 0;
    }

    // Return a normalized value between 0 and 100
    return (char) ((((float)read()) - min) / range * 100);
}

void TSL235R::calibrateOnce() {
    // Get a current reading
    unsigned long currentValue = read();

    // Adjust min and max
    if (currentValue > max) {
        max = currentValue;
    }
    if (currentValue < min) {
        min = currentValue;
    }

    // Adjust the range, we store this to save on calculating it later
    range = max - min;
}
