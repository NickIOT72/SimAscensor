#ifndef _ASCWEBSERVERAPI_H
#define _ASCWEBSERVERAPI_H 

#include <Arduino.h>

#if defined(ESP8266)
    #include <ESP8266WebServer.h>

    void AscWebServerAPI_InitSerial();
    void AscWebServerAPI_handleSetPin(std::unique_ptr<ESP8266WebServer> & server);
    void AscWebServerAPI_handleHelloWorld( std::unique_ptr<ESP8266WebServer> & server );

#endif

#endif // _WEBSERVERAPI_H 