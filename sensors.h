#ifndef SENSORS_H
#define SENSORS_H

typedef struct {
  int temperature;
  int humidity;
  int dht_temp;
  int dht_hum;
} sensors_data_t;

void sensors_init(sensors_data_t *data);
void sensors_getValues(sensors_data_t *data);

#endif // SENSORS_H