#include "ssi.h"


char const * ssi_tags[] = { /* index 0 */ "temp", 
                            /* index 1 */ "humid" };


u16_t ssi_handlers(int index, char * insert, int insert_len)
{
    u16_t printed = 0;

    switch (index) {
        case 0: // #temp
            printed = (u16_t)snprintf(insert, insert_len, "%.1f", readTempSensor());
            break;

        case 1: // #humid
            printed = (u16_t)snprintf(insert, insert_len, "%.1f", readHumiditySensor());
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