#include "hardware.h"

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
