#include "cgi.h"

const char * home_handler(int index, 
                          int num_params, 
                          char * params[], 
                          char * values[])
{
    return "/index.shtml";
}


tCGI const cgi_handlers[] = {
    { "/home", home_handler } // index 0;  <ip-addr>/home; also works <ip-addr> (nothing)
    // IDEA Create debug page?
};


void cgiInit(void)
{
    http_set_cgi_handlers(cgi_handlers, LWIP_ARRAYSIZE(cgi_handlers));
}