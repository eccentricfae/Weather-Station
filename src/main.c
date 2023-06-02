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

void onConnectionLoss()
{
    static bool is_lit = false;

    if (is_lit) return;

    signalLoc();
    is_lit = true;
}

bool addReadingToBufferCallback(repeating_timer_t * rt)
{
    addRecToBuffer();

    return true;
}


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

    signalLoc();
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
    clearLoc();

    printf("Initializing http server\n");
    httpd_init();

    printf("Initializing CGI functionality\n");
    cgiInit();

    printf("Initializing SSI functionality\n");
    ssiInit();

    printf("Initializing the hardware module\n");
    hardwareInit();

    printf("Initialization completed. Going into the main loop\n");

    repeating_timer_t rt;
    add_repeating_timer_ms(-(TEMP_READ_INTERVAL_S * 1000), addReadingToBufferCallback, NULL, &rt);
    addRecToBuffer();

    while (true) {
        bool is_connected = cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA) == CYW43_LINK_JOIN ? true : false;
        if (!is_connected) {
            printf("Lost connection to the Wifi network\n");
            onConnectionLoss();
            int status = cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 10 * 1000);
            if (status != PICO_OK) {
                printf("Failed to connect to the Wifi network \"%s\". Error code: %s\n", WIFI_SSID, errCodeToStr(status));
            } else {
                printf("Connected to the network %s\n", WIFI_SSID);
                clearLoc();
            }
        }
    }
}