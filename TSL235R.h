#ifndef TSL235R_H
#define TSL235R_H

#define INTERRUPT_MODE 0
#define PULSE_MODE 1


class TSL235R {
public:
    TSL235R(unsigned char dataPin);

    TSL235R(unsigned char dataPin, char mode);

    /**
     * handleInterrupt
     * If you are using the interrupt method you must set up an interrupt
     * in the main program and call this method each time the interrupt
     * service routine is triggered.
     */
    void handleInterrupt();

    /**
     * read
     * Takes an instant reading the light intensity. In actuality may take
     * multiple readings and averages them to avoid spurios noise effects.
     * @return int the frequency (Hz) of the sensor signal
     */
    unsigned long read();

    /**
     * readCalibrated
     * Takes an instant reading and normalizes the value utilizing
     * the calibrated min and max values. The ultimate value returned is a value
     * between 0 and 1000.
     * @return char the intensity value between 0 and 100
     */
    long readCalibrated();

    /**
     * calibrateOnce
     * Takes exactly one reading and adjusts the min and max values. Ideally
     * this method would be called repeatedly a certain number of times or for
     * a certain amount of elapsed time.
     */
    void calibrateOnce();

    unsigned long getCalibratedMin() { return min; }
    unsigned long getCalibratedMax() { return max; }

private:
    void init(unsigned char dataPin, char mode);

    char mode;
    unsigned char dataPin;
    volatile unsigned long counter;
    volatile unsigned long lastCounter;
    unsigned long max;
    unsigned long min;
    unsigned long range;
    volatile unsigned long lastTime;
    unsigned int sampleRateUS;
    volatile float interruptDuration;

};

#endif // TSL235R_H
