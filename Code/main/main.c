#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "wifi.h"
#include "soil.h"
#include "ubidots.h"

void app_main(void)
{
    wifi_init();
    soil_init();

    int soil;
    float humidity, temperature;

    while (1)
    {
        // 🌱 REAL SENSOR READ
        soil = soil_read();

        // 🌡 Simulated realistic environment (based on soil)
        if (soil > 3000)  // DRY
        {
            humidity = 35;
            temperature = 30;
        }
        else if (soil > 2000)
        {
            humidity = 50;
            temperature = 29;
        }
        else if (soil > 1200)
        {
            humidity = 65;
            temperature = 28;
        }
        else  // WET
        {
            humidity = 80;
            temperature = 27;
        }

        printf("Soil: %d\n", soil);
        printf("Humidity: %.2f %%\n", humidity);
        printf("Temperature: %.2f °C\n", temperature);

        // 🚀 Send to Ubidots
        send_to_ubidots(soil, humidity, temperature);

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}