/*
  Server module

 Defines the Web server handler with REST API. 

 created 19 april 2025
 by gcuadrado
 */
#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <aREST.h>

#include "arduino_secrets.h"
#include "server.h"

const uint16_t port = 80;
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;    // your network SSID
char pass[] = SECRET_PASS;    // your network password
int status = WL_IDLE_STATUS;

aREST rest = aREST();
WiFiServer restServer(port);

// Static function prototypes
static void printWifiStatus();

// PUBLIC FUNCTIONS
/**
 * @brief Initialize server and WIFI connection
 * @return err_t Error status 
 */
err_t server_init(void)
{
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");
    return ERR_FAILURE;
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
  return ERR_SUCCESS;
}

/**
 * @brief Initialize REST API for web server
 * @param[in] temp Temperature as int
 * @param[in] hum Humidity as int
 * @param[in] bat battery level in percentage
 */
void server_setupRest(int &temp, int &hum, int &bat)
{
  // Give name and ID to device
  rest.set_id("001");
  rest.set_name("drying_oven");

  // Init variables and expose them to REST API
  rest.variable("temperature", &temp);
  rest.variable("humidity", &hum);
  rest.variable("battery", &bat);
}

/**
 * @brief Start Server on port 80
 */
void server_begin()
{
  restServer.begin();
  printWifiStatus();
}

/**
 * @brief Handle clients connection
 */
void server_listen()
{
  WiFiClient client = restServer.available();
  rest.handle(client);
}

// PRIVATE FUNCTIONS
/**
 * @brief Print WIFI connection information
 */
static void printWifiStatus()
{
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