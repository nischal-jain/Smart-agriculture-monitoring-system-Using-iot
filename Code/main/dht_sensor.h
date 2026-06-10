#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include "esp_err.h"

esp_err_t dht_read(float *temperature, float *humidity);

#endif