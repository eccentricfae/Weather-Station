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