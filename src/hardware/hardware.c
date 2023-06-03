#include "hardware.h"

float    g_temp_rec_buff[TEMP_REC_BUFF_LEN] = { 0.0f }; // Temperature recordings buffer
uint32_t g_taken   = 0; // How many items are stored in the temp_rec_buff
uint32_t g_buff_it = 0; // Position for the next recording (in the temp_rec_buff)
float    g_min = 1000.0f;  // Lowest recorded temperature
float    g_max = -1000.0f; // Highest recorded temperature

void try_min(float val)
{
    if (val < g_min) {
        g_min = val;
    }
}

void try_max(float val)
{
    if (val > g_max) {
        g_max = val;
    }
}

void hardwareInit()
{
    // Assuming 26'th pin is the adc input for the battery "+ terminal"
    adc_init();
    #ifdef BAT_ADC_PIN
    adc_gpio_init(BAT_ADC_PIN);
    #endif

    #ifdef TEMP_ADC_PIN
    adc_gpio_init(TEMP_ADC_PIN);
    #endif

    #ifdef LOC_LED
    gpio_init(LOC_LED);
    gpio_set_dir(LOC_LED, GPIO_OUT);
    gpio_pull_down(LOC_LED);
    gpio_put(LOC_LED, 0);
    #endif

    adc_set_temp_sensor_enabled(true);
}

#ifdef LOC_LED
void signalLoc()
{
    gpio_put(LOC_LED, 1);
}

void clearLoc()
{
    gpio_put(LOC_LED, 0);
}
#endif


#ifdef TEMP_ADC_PIN
float readTempSensor()
{
    // Take the current battery's voltage as Vref for more accurate reading
    float const vref = 3.3f;

    adc_select_input(1);
    uint16_t adc_raw = adc_read();
    float voltage = (float)adc_raw * (vref / (float)(1 << 12));

    float temp = (voltage - 0.5f) * 100;

    try_min(temp);
    try_max(temp);

    return temp;
}
#endif

#ifdef BAT_ADC_PIN
float readBatteryVoltage()
{
    float vref_value = 3.2f;

    adc_select_input(0);
    uint16_t adc_raw = adc_read();
    float converted = (float)adc_raw * (vref_value / (float)(1 << 12));
    
    return converted;
}
#endif

void addRecToBuffer()
{
    float const temp_val = readTempSensor();

    g_temp_rec_buff[g_buff_it] = temp_val;
    g_buff_it++;
    if (g_buff_it >= TEMP_REC_BUFF_LEN) {
        g_buff_it = 0;
    }
    if (g_taken < (TEMP_REC_BUFF_LEN - 1)) {
        g_taken++;
    }

    try_min(temp_val);
    try_max(temp_val);
}

float getAvgTempFromRecs()
{
    double sum = 0.0;

    for (uint32_t i = 0; i < g_taken; i++) {
        sum += g_temp_rec_buff[i];
    }

    return sum / (double)g_taken;
}

float getMaxTempFromRecs()
{
    return g_max;
}

float getMinTempFromRecs()
{
    return g_min;
}

float getPicoTemp()
{
    // Take the current battery's voltage as Vref for more accurate reading
    float vref = 3.3f;
    float conversion_factor = vref / (1 << 12);

    adc_select_input(4);
    uint16_t adc_raw = adc_read();

    float adc = (float)adc_raw * conversion_factor;
    float temp_C = 27.0f - (adc - 0.706f) / 0.001721f;

    return temp_C;
}

uint32_t getRecsSize()
{
    return g_taken;
}