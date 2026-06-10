#include "soil.h"
#include "driver/adc.h"

void soil_init(void)
{
    // 12-bit resolution (0–4095)
    adc1_config_width(ADC_WIDTH_BIT_12);

    // GPIO34 → ADC1_CHANNEL_6
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
}

int soil_read(void)
{
    int value = adc1_get_raw(ADC1_CHANNEL_6);

    // Clamp values (safety)
    if (value < 0) value = 0;
    if (value > 4095) value = 4095;

    return value;
}