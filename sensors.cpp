#include <Arduino_MKRENV.h>
#include "DHT.h"
#include "sensors.h"

#define DHTPIN 3        // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

/**
 * @brief Initialize sensors
 * @param[in/out] data Pointer to structure sensors_data_t
 * @return err_t Error status
 */
err_t sensors_init(sensors_data_t *data)
{
  err_t err = ERR_SUCCESS;
  if (data == NULL)
  {
    err = ERR_INVALID_POINTER;
  }
  else
  {
    data->temperature = 0;
    data->humidity = 0;
    data->dht_temp = 0;
    data->dht_hum = 0;

    dht.begin();

    if (!ENV.begin())
    {
      Serial.println("Failed to initialize MKR ENV Shield!");
      err = ERR_FAILURE;
    }
  }
  return err;
}

/**
 * @brief Get values from sensors (builtin & DHT22)
 * @param[in/out] data Pointer to structure sensors_data_t
 * @return err_t Error status
 */
err_t sensors_getValues(sensors_data_t *data)
{
  err_t err = ERR_SUCCESS;
  if (data == NULL)
  {
    err = ERR_INVALID_POINTER;
  }
  else
  {
    data->temperature = (int)ENV.readTemperature();
    data->humidity    = (int)ENV.readHumidity();

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      err = ERR_INVALID_ARGUMENT;
    }
    data->dht_temp = (int)t;
    data->dht_hum = (int)h;
  }
  return err;
}
