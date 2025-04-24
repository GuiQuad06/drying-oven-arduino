/*
  Drying Oven Arduino

 Web server application that publish Temp & humidity data to monitor the
 drying oven. 

 created 19 april 2025
 by gcuadrado
 */
#include <Arduino_MKRENV.h>
#include "batmon.h"
#include "server.h"

int temperature = 0;
int humidity = 0;
int battLevel = 0;

void setup(void)
{  
  err_t err = ERR_SUCCESS;

  pinMode(LED_BUILTIN, OUTPUT);

  if (!ENV.begin())
  {
    // do not continue
    while (1);
  }

  batmon_init();

  err = server_init();
  if (ERR_FAILURE == err)
  {
    // do not continue
    while(1);
  }

  server_setupRest(temperature, humidity, battLevel);
  server_begin();
  // Init succeed
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  temperature = (int)ENV.readTemperature();
  humidity    = (int)ENV.readHumidity();

  battLevel = batmon_getBattData();
  
  server_listen();
}
