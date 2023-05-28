#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <lwip/apps/httpd.h>
#include "lwipopts.h"

// ssi
#include "cgi.h"
#include "helpers.h"
#include "wifi_credentials.h"


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
        if (error) {
            // TODO
        }
    } while (error);
    
    printf("Initializing http server\n");
    httpd_init();

    printf("Initializing CGI functionality\n");
    cgiInit();

    // printf("Initializing SSI functionality\n");
    // ssi_init(); 

    printf("Initialization completed. Going into the main loop\n");


    while (true) {
        //
    }
}