#include "ssi.h"


char const * ssi_tags[] = { 
                            /* index 0 */ "temp", 
                            /* index 1 */ "humid",
                            /* index 2 */ "uptime",
                          };


u16_t ssi_handlers(int index, char * insert, int insert_len)
{
    // TODO What is the max allowed length of inserted string?
    u16_t printed = 0;

    switch (index) {
        case 0: // #temp
            printed = (u16_t)snprintf(insert, insert_len, "%.1f", readTempSensor());
            break;

        case 1: // #humid
            printed = (u16_t)snprintf(insert, insert_len, "%.1f", readHumiditySensor());
            break;

        case 2: // #uptime
            uptime_t val = getUptime();
            printed = (u16_t)snprintf(insert, insert_len, "%2dd-%2dh-%2dm-%2ds", val.days, val.hours, val.minutes, val.seconds);
            break;

        default:
            printed = 0;
            break;
    }

    return printed;
}


void ssiInit(void)
{
    http_set_ssi_handler(ssi_handlers, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}