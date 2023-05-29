#include "cgi.h"

const char * home_handler(int index, 
                          int num_params, 
                          char * params[], 
                          char * values[])
{
    return "/index.shtml";
}

const char * debug_handler(int index, 
                           int num_params, 
                           char * params[], 
                           char * values[])
{
    return "/debug.shtml";
}

tCGI const cgi_handlers[] = {
    { "/home",  home_handler }, // index 0;  <ip-addr>/home; also works <ip-addr> (nothing)
    { "/debug", debug_handler } // index 1; <ip-addr>/debug
};


void cgiInit(void)
{
    http_set_cgi_handlers(cgi_handlers, LWIP_ARRAYSIZE(cgi_handlers));
}