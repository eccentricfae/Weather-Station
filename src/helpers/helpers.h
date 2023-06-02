#ifndef _HELPERS_H
#define _HELPERS_H

#include <pico/error.h>
#include <pico/time.h>
#include <math.h>
#include "hardware.h"

typedef struct {
    uint8_t days;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} uptime_t;

/**
 * @brief Given an enum "pico_error_codes" returns the name of
 * that constant / enum, e.g. returns string "PICO_TIMEOUT"
 * when given the value of PICO_TIMEOUT (== -1)
 */
char const * errCodeToStr(enum pico_error_codes code);

/**
 * @brief Wrapper function for getting the number of milliseconds since boot
 * 
 * @return uint32_t Milliseconds since boot
 */
uint32_t getMsSinceBoot();

uptime_t getUptime();

/**
 * @brief Given RSSI value returns text description of the signal's strength
 */
char const * rssiToStr(int32_t rssi);

/**
 * @brief TODO
 */
uptime_t parseSecs(uint32_t secs);

#endif