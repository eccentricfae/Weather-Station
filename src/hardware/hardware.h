#ifndef _HARDWARE_H
#define _HARDWARE_H

#include <pico/stdlib.h>
#include <hardware/adc.h>

// "Loss of connection" LED pin number. This pin (if defined)
// will be put into state of logical '1' when the uC is not 
// connected to any network
#define LOC_LED 16

// Pin on which the battery Voltage will be read
#define BAT_ADC_PIN 26

// Pin on which the temperature sensor Vout will be read
#define TEMP_ADC_PIN 27

// Interval (in seconds) for reading the temperature and storing it in
// the buffer for storing the recorded temperatures
#define TEMP_READ_INTERVAL_S 600

// Length of the buffer that holds temperature recordings
// from previous readings, read at TEMP_READ_INTERVAL_S intervals
#define TEMP_REC_BUFF_LEN 144 
// ^ 144 len w/ 600 s interval -> stores data from the previous 24 hrs

void hardwareInit();

#ifdef LOC_LED
/**
 * @brief Signal Loss Of Connection by lighting a LED on
 * LOC_LED pin
 */
void signalLoc();

/**
 * @brief Opposite of signalLoc - turns off the LED
 */
void clearLoc();
#endif

#ifdef TEMP_ADC_PIN
/**
 * @brief Reads the temperature sensor and returns the value of temperature 
 * in Celsius
 */
float readTempSensor();
#endif

#ifdef BAT_ADC_PIN
/**
 * @brief Reads the voltage of the battery, returns the value in Volts
 */
float readBatteryVoltage();
#endif

/**
 * @brief Reads the current temperature from the sensor and stores it in
 * the temperature recordings buffer
 */
void addRecToBuffer();

/**
 * @brief Returns the average temperature from the temperature recordings
 * buffer
 */
float getAvgTempFromRecs();

/**
 * @brief Returns the highest recorded temperature from the temperature
 * recordings buffer
 */
float getMaxTempFromRecs();

/**
 * @brief Returns the smallest lowest recorded temperature from the
 * temperature recordings buffer
 */
float getMinTempFromRecs();

/**
 * @brief Returns the temperature read from the Pico's on-board 
 * temperature sensor
 */
float getPicoTemp();

/**
 * @brief Returns the size (no. of elements) in the recordings
 * buffer / array
 */
uint32_t getRecsSize();

#endif