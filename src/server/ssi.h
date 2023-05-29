#ifndef _SSI_H
#define _SSI_H

#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <lwip/apps/httpd.h>

#include "hardware.h"

void ssiInit(void);

#endif