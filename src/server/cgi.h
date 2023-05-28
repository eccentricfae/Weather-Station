#ifndef _CGI_H
#define _CGI_H

#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <lwip/apps/httpd.h>

/**
 * @brief Initializes CGI functionality
 */
void cgiInit(void);

#endif