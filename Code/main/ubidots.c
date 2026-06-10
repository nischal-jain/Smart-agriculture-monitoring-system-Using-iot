#include "ubidots.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include <string.h>

#define UBIDOTS_TOKEN "BBUS-FQiShcSRmcSAAgeh6IjJYqKoIcT1Lh"
#define DEVICE_LABEL "smart-agriculture"

void send_to_ubidots(int soil, float humidity, float temperature)
{
    char data[200];

    sprintf(data,
        "{\"soil\": %d, \"humidity\": %.2f, \"temperature\": %.2f}",
        soil, humidity, temperature);

    esp_http_client_config_t config = {
        .url = "http://industrial.api.ubidots.com/api/v1.6/devices/smart-agriculture",
        .method = HTTP_METHOD_POST,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);

    esp_http_client_set_header(client, "X-Auth-Token", UBIDOTS_TOKEN);
    esp_http_client_set_header(client, "Content-Type", "application/json");

    esp_http_client_set_post_field(client, data, strlen(data));
    esp_http_client_perform(client);

    int status = esp_http_client_get_status_code(client);
    ESP_LOGI("UBIDOTS", "HTTP Status: %d", status);

    esp_http_client_cleanup(client);
}