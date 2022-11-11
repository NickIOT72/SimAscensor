
#include "../../Protocols/SoftSerial/SoftSerial.h"
#include <ArduinoJson.h>

SoftwareSerial ESP_SERIAL_WEBSERVER(ESP_RX, ESP_TX);

#if defined(ESP8266)

#include "./WebServerFile/WebServerFile.h"
#include "./WebServerAPI/WebServerAPI.h"
#include "./WebServer.h"

#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino

// needed for library
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>

#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager

std::unique_ptr<ESP8266WebServer> server;

void WebServer_redirectClient(  std::unique_ptr<ESP8266WebServer> & server , String path)
{
  server->sendHeader("Location", path, true);
  server->send(302, "text/plain", "");
}

void WebServer_handleClient()
{
  server->handleClient();
}

void WebServer_InitWiFiManager( void (*f)()  )
{
  WiFiManager wifiManager;
  // fetches ssid and pass from eeprom and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration
  // wifiManager.autoConnect("AutoConnectAP");O
  // or use this for auto generated name ESP + ChipID
  wifiManager.autoConnect("AutoConnectAP");

  // if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  
  ESP_SERIAL_WEBSERVER.begin(9600);
  WebServerFile_InitSerial();
  WebServerAPI_InitSerial();
  f(); 
}

#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)

#endif