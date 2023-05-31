#include "helpers.h"

char const * errCodeToStr(enum pico_error_codes code)
{
    switch (code) {
        case PICO_ERROR_NONE:
            return "PICO_ERROR_NONE";

        case PICO_ERROR_TIMEOUT:
            return "PICO_ERROR_TIMEOUT";

        case PICO_ERROR_GENERIC:
            return "PICO_ERROR_GENERIC";

        case PICO_ERROR_NO_DATA:
            return "PICO_ERROR_NO_DATA";
        
        case PICO_ERROR_NOT_PERMITTED:
            return "PICO_ERROR_NOT_PERMITTED";

        case PICO_ERROR_INVALID_ARG:
            return "PICO_ERROR_INVALID_ARG";

        case PICO_ERROR_IO:
            return "PICO_ERROR_IO";

        case PICO_ERROR_BADAUTH:
            return "PICO_ERROR_BADAUTH";

        case PICO_ERROR_CONNECT_FAILED:
            return "PICO_ERROR_CONNECT_FAILED";

        default:
            return "UNKNOWN_CODE";
    }
}

uint32_t getMsSinceBoot()
{
    return to_ms_since_boot(get_absolute_time());
}

uptime_t getUptime()
{
    uint32_t uptime_ms = to_ms_since_boot(get_absolute_time());

    uptime_t retval;

    retval.days = (uint8_t)floor(uptime_ms / 86400000);
    uptime_ms = uptime_ms - (retval.days * 86400000);
    retval.hours = (uint8_t)floor(uptime_ms / 3600000);
    uptime_ms = uptime_ms - (retval.hours * 3600000);
    retval.minutes = (uint8_t)floor(uptime_ms / 60000);
    uptime_ms = uptime_ms - (retval.minutes * 60000);
    retval.seconds = (uint8_t)(uptime_ms / 1000);

    return retval;
}

char const * rssiToStr(int32_t rssi)
{
    if (rssi > -65) {
        return "Excellent";
    } else if (rssi <= -65 && rssi > -75) {
        return "Good";
    } else if (rssi <= -75 && rssi > -85) {
        return "Fair";
    } else {
        return "Poor";
    }
}