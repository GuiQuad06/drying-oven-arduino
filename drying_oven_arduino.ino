/*
  Drying Oven Arduino

 TODO

 created 19 april 2025
 by gcuadrado
 */
#include <Arduino_MKRENV.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <aREST.h>

#include "arduino_secrets.h"

// The port to listen for incoming TCP connections 
#define LISTEN_PORT           80

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;    // your network SSID
char pass[] = SECRET_PASS;    // your network password

int status = WL_IDLE_STATUS;
int temperature = 0;
int humidity = 0;

// Create aREST instance
aREST rest = aREST();
WiFiServer restServer(LISTEN_PORT);

void setup(void)
{  
  Serial.begin(115200);
  while(!Serial);

  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV Shield!");
    while (1);
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // Give name and ID to device
  rest.set_id("001");
  rest.set_name("drying_oven");

  // Init variables and expose them to REST API
  rest.variable("temperature", &temperature);
  rest.variable("humidity", &humidity);
  
  // Start server
  restServer.begin();
  printWifiStatus();
}

void loop() {
  temperature = (int)ENV.readTemperature();
  humidity    = (int)ENV.readHumidity();
  
  // listen for incoming clients
  WiFiClient client = restServer.available();
  rest.handle(client);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
