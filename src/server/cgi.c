#include "cgi.h"

// CGI handler which is run when a request for /led.cgi is detected
const char * cgi_led_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    static int x = 0;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, x);
    x = !x;

    return "/index.shtml";
}

static const tCGI cgi_handlers[] = {
    {
        // Html request for "/led.cgi" triggers cgi_handler
        "/led", cgi_led_handler
    }
};

void cgiInit(void)
{
    http_set_cgi_handlers(cgi_handlers, LWIP_ARRAYSIZE(cgi_handlers));
}