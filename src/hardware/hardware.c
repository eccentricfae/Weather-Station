#include "hardware.h"

void hardwareInit()
{
    // Assuming 26'th pin is the adc input
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);
}

float readTempSensor()
{
    static float num = 23.23f;
    num += 1.0f;
    return num;
}

float readHumiditySensor()
{
    static float num = 77.77f;
    num += 1.0f;
    return num;
}

float readBatteryVoltage()
{
    float vref_value = 3.3f;  // TODO
    
    uint16_t raw = adc_read();
    float converted = raw * (vref_value /(1 << 12));
    
    return converted;
}