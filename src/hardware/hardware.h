#ifndef _HARDWARE_H
#define _HARDWARE_H

#include <pico/stdlib.h>
#include <hardware/adc.h>

void hardwareInit();

float readTempSensor();

float readHumiditySensor();

float readBatteryVoltage();

#endif