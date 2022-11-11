#ifndef _WEBSERVERAPI_H
#define _WEBSERVERAPI_H 

#include <Arduino.h>
#include "./WebServer.h"

#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino

// needed for library
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <fstream>

#include <WiFiManager.h> //https://github.com/tzapu/

std::unique_ptr<ESP8266WebServer> server;

#include "../../Protocols/SoftSerial/SoftSerial.h"
#include <ArduinoJson.h>

SoftwareSerial ESP_SERIAL_WEBSERVERAPI(ESP_RX, ESP_TX);

void handleSetPin()
{
   ESP_SERIAL_WEBSERVERAPI.println("handleSetPin");
   ESP_SERIAL_WEBSERVERAPI.println("");
}



#endif // _WEBSERVERAPI_H 

