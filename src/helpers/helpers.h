#ifndef _HELPERS_H
#define _HELPERS_H

#include <pico/error.h>

/**
 * @brief Given an enum "pico_error_codes" returns the name of
 * that constant / enum, e.g. returns string "PICO_TIMEOUT"
 * when given the value of PICO_TIMEOUT (== -1)
 */
char const * errCodeToStr(enum pico_error_codes code);

#endif