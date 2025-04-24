/*
  Drying Oven Arduino

 Web server application that publish Temp & humidity data to monitor the
 drying oven. 

 created 19 april 2025
 by gcuadrado
 */
#include "batmon.h"
#include "sensors.h"
#include "server.h"

int battLevel = 0;

sensors_data_t sensorsData;

void setup(void)
{  
  err_t err = ERR_SUCCESS;

  Serial.begin(115200);
  while(!Serial);

  sensors_init(&sensorsData);
  batmon_init();

  err = server_init();
  if (ERR_SUCCESS != err)
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

  sensors_getValues(&sensorsData);
  
  server_listen();
  delay(2000);
}
