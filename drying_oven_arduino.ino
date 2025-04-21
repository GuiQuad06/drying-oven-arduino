/*
  Drying Oven Arduino

 Web server application that publish Temp & humidity data to monitor the
 drying oven. 

 created 19 april 2025
 by gcuadrado
 */
#include <Arduino_MKRENV.h>
#include "server.h"

int temperature = 0;
int humidity = 0;

void setup(void)
{  
  err_t err = ERR_SUCCESS;

  Serial.begin(115200);
  while(!Serial);

  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV Shield!");
    while (1);
  }

  err = server_init();
  if (ERR_SUCCESS != err)
  {
    // do not continue
    while(1);
  }

  server_setupRest(temperature, humidity);
  server_begin();
}

void loop() {
  temperature = (int)ENV.readTemperature();
  humidity    = (int)ENV.readHumidity();
  
  server_listen();
}
