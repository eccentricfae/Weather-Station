#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <lwip/apps/httpd.h>
#include "lwipopts.h"

// ssi
#include "cgi.h"
#include "wifi_credentials.h"


typedef enum pico_error_codes pico_error_codes_t;


void main(void)
{
    pico_error_codes_t error = PICO_OK;

    stdio_init_all();

    // TODO rewrite w/ error checking
    cyw43_arch_init();
    cyw43_arch_enable_sta_mode();
    while(cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 30 * 1000) != 0){
        printf("Attempting to connect...\n");
    }
    httpd_init();
    cgiInit();

    // ssi_init(); 


    while (true) {
        //
    }
}