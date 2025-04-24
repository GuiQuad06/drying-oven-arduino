/*
  Drying Oven Arduino

 Web server application that publish Temp & humidity data to monitor the
 drying oven. 

 created 19 april 2025
 by gcuadrado
 */
#include "batmon.h"
#include "error.h"
#include "sensors.h"
#include "server.h"

int battLevel = 0;

sensors_data_t sensorsData;
static err_t err = ERR_SUCCESS;

void setup(void)
{  
  Serial.begin(115200);
  while(!Serial);

  batmon_init();

  err = sensors_init(&sensorsData);
  if (ERR_SUCCESS != err)
  {
    // do not continue
    while(1);
  }

  err = server_init();
  if (ERR_SUCCESS != err && NEEDS_UPDATE != err)
  {
    // do not continue
    while(1);
  }

  server_setupRest(sensorsData.temperature,
                  sensorsData.humidity,
                  sensorsData.dht_temp,
                  sensorsData.dht_hum,
                  battLevel);
  server_begin();
}

void loop() {
  battLevel = batmon_getBattData();

  err = sensors_getValues(&sensorsData);
  if (ERR_SUCCESS != err)
  {
    // do not continue
    while(1);
  }
  
  server_listen();
  delay(2000);
}
