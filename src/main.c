#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <lwip/apps/httpd.h>
#include "lwipopts.h"

#include "cgi.h"
#include "ssi.h"
#include "hardware.h"
#include "helpers.h"
#include "wifi_config/wifi_credentials.h"


#define WIFI_CONN_TIMEOUT_S 10
#define ERROR_SLEEP_MS 2000

typedef enum pico_error_codes pico_error_codes_t;


void main(void)
{
    pico_error_codes_t error = PICO_OK;

    stdio_init_all();

    do {
        error = cyw43_arch_init();
        if (error) {
            printf("Error initializing the wifi chip. Error code: %s\n", errCodeToStr(error));
            sleep_ms(ERROR_SLEEP_MS);
        }
    } while (error);

    cyw43_arch_enable_sta_mode();

    do {
        error = cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, 
                                                   WIFI_PASS, 
                                                   CYW43_AUTH_WPA2_AES_PSK, 
                                                   WIFI_CONN_TIMEOUT_S * 1000);
        if (error == PICO_ERROR_TIMEOUT) {
            printf("Connecting to %s...\n", WIFI_SSID);
        } else if (error != PICO_OK) {
            printf("Error connecting to the %s network. Error code: %s\n", WIFI_SSID, errCodeToStr(error));
            sleep_ms(ERROR_SLEEP_MS);
        }
    } while (error);
    
    printf("Initializing http server\n");
    httpd_init();

    printf("Initializing CGI functionality\n");
    cgiInit();

    printf("Initializing SSI functionality\n");
    ssiInit();

    printf("Initializing the hardware module\n");
    hardwareInit();

    printf("Initialization completed. Going into the main loop\n");


    while (true) {
        //
        // TODO network connection OK?
        // TODO regular intervals -> read temp and store it for the debug page (addRecToBuffer())
    }
}