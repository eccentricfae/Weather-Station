#include "ssi.h"


char const * ssi_tags[] = { 
                            /* index 0 */ "temp", 
                            /* index 1 */ "humid",    // todo Delete later and refactor the rest
                            /* index 2 */ "uptime",
                            /* index 3 */ "wfnm",     // Wifi Name
                            /* index 4 */ "sigstr",   // Signal Strength
                            /* index 5 */ "batvolt",  // Voltage across the battery
                            /* index 6 */ "picotmp",  // Temperature on the Pico
                            /* index 7 */ "recper",   // Recordings period
                            /* index 8 */ "avgtmp",
                            /* index 9 */ "maxtmp",   // Highest temperature from the recordings
                            /* index 10 */ "mintmp",  // Lowest temperature from the recordings
                            /* index 11 */ "picotmp", // Temperature on the Pico
                          };


u16_t ssi_handlers(int index, char * insert, int insert_len)
{
    u16_t printed = 0;

    switch (index) {
        case 0: // #temp
            printed = (u16_t)snprintf(insert, insert_len, "%.1f", readTempSensor());
            break;

        case 1: // #humid
            // Just for legacy purposes, maybe will be deleted later 
            printed = 0;
            break;

        case 2: // #uptime
            uptime_t val = getUptime();
            printed = (u16_t)snprintf(insert, insert_len, "%dd-%dh-%2dm-%2ds", val.days, val.hours, val.minutes, val.seconds);
            break;

        case 3: // #wfnm
            printed = (u16_t)snprintf(insert, insert_len, "%s", WIFI_SSID);
            break;

        case 4: // #sigstr
            int32_t rssi = 0;
            if (cyw43_wifi_get_rssi(&cyw43_state, &rssi) != 0) {
                printed = (u16_t)snprintf(insert, insert_len, "%s", "error");
            } else {
                printed = (u16_t)snprintf(insert, insert_len, "%s", rssiToStr(rssi));
            }
            break;

        case 5: // #batvolt
            printed = (u16_t)snprintf(insert, insert_len, "%.2f", readBatteryVoltage());
            break;

        case 6: // #picotmp
            printed = (u16_t)snprintf(insert, insert_len, "%.1f", getPicoTemp());
            break;

        case 7: // #recper
            uptime_t sval = parseSecs(TEMP_READ_INTERVAL_S * TEMP_REC_BUFF_LEN);
            printed = (u16_t)snprintf(insert, insert_len, "%dd-%dh-%2dm-%2ds", sval.days, sval.hours, sval.minutes, sval.seconds);
            break;

        case 8: // #avgtmp
            printed = (u16_t)snprintf(insert, insert_len, "%.2f", getAvgTempFromRecs());
            break;

        case 9: // #maxtmp
            printed = (u16_t)snprintf(insert, insert_len, "%.1f", getMaxTempFromRecs());
            break;

        case 10: // #mintmp
            printed = (u16_t)snprintf(insert, insert_len, "%.1f", getMinTempFromRecs());
            break;

        case 11: // #picotmp
            printed = (u16_t)snprintf(insert, insert_len, "%.1f", getPicoTemp());
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
