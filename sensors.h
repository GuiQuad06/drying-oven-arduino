#ifndef SENSORS_H
#define SENSORS_H

#include "error.h"

/**
 * @brief Data structure to store data sensors
 */
typedef struct {
  int temperature;
  int humidity;
  int dht_temp;
  int dht_hum;
} sensors_data_t;

err_t sensors_init(sensors_data_t *data);
err_t sensors_getValues(sensors_data_t *data);

#endif // SENSORS_H