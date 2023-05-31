#include "ssi.h"


char const * ssi_tags[] = { 
                            /* index 0 */ "temp", 
                            /* index 1 */ "humid",
                            /* index 2 */ "uptime",
                            /* index 3 */ "wfnm",   // Wifi Name
                            /* index 4 */ "sigstr", // Signal Strength
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

        case 3: // #wfnm
            printed = (u16_t)snprintf(insert, insert_len, "%s", WIFI_SSID);
            break;

        case 4: // #sigstr
            int32_t rssi = 0;
            int retval = cyw43_wifi_get_rssi(&cyw43_state, &rssi);
            if (retval != 0) rssi = 0;
            // TODO Set some kind of way of telling if signal is strong / weak?
            printed = (u16_t)snprintf(insert, insert_len, "%d", rssi);
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