#include "dht_sensor.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"
#include "esp_timer.h"
#include "esp_log.h"

#define DHT_GPIO 15

static const char *TAG = "DHT";

static int wait_for_level(int level, int timeout_us)
{
    int64_t start = esp_timer_get_time();
    while (gpio_get_level(DHT_GPIO) == level)
    {
        if ((esp_timer_get_time() - start) > timeout_us)
            return -1;
    }
    return 0;
}

esp_err_t dht_read(float *temperature, float *humidity)
{
    uint8_t data[5] = {0};

    // Step 1: Send start signal
    gpio_set_direction(DHT_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(DHT_GPIO, 0);
    esp_rom_delay_us(20000);   // 20ms
    gpio_set_level(DHT_GPIO, 1);
    esp_rom_delay_us(40);

    // Step 2: Switch to input
    gpio_set_direction(DHT_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(DHT_GPIO, GPIO_PULLUP_ONLY);

    // Step 3: Sensor response
    if (wait_for_level(1, 100) < 0) {
        ESP_LOGE(TAG, "No response (1)");
        return ESP_FAIL;
    }
    if (wait_for_level(0, 100) < 0) {
        ESP_LOGE(TAG, "No response (0)");
        return ESP_FAIL;
    }

    // Step 4: Read 40 bits
    for (int i = 0; i < 40; i++)
    {
        if (wait_for_level(1, 70) < 0) {
            ESP_LOGE(TAG, "Timeout HIGH");
            return ESP_FAIL;
        }

        int64_t start = esp_timer_get_time();

        if (wait_for_level(0, 100) < 0) {
            ESP_LOGE(TAG, "Timeout LOW");
            return ESP_FAIL;
        }

        int64_t duration = esp_timer_get_time() - start;

        if (duration > 40) // logic 1
            data[i / 8] |= (1 << (7 - (i % 8)));
    }

    // Step 5: Checksum
    if ((data[0] + data[1] + data[2] + data[3]) != data[4])
    {
        ESP_LOGE(TAG, "Checksum failed");
        return ESP_FAIL;
    }

    // Step 6: Convert values
    *humidity = ((data[0] << 8) | data[1]) / 10.0;
    *temperature = ((data[2] << 8) | data[3]) / 10.0;

    ESP_LOGI(TAG, "Temp: %.2f, Hum: %.2f", *temperature, *humidity);

    return ESP_OK;
}