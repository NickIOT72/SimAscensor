#ifndef _ASCWEBSERVERAPI_H
#define _ASCWEBSERVERAPI_H 

#include <Arduino.h>

#define MOD_OUT 1
#define MOD_IN 2

const size_t ws_json_capacity = 2000;

#if defined(ESP8266)
    #include <ESP8266WebServer.h>
    void AscWebServerAPI_handleDashboardRedirect(std::unique_ptr<ESP8266WebServer> & server );
    void AscWebServerAPI_InitSerial();
    void AscWebServerAPI_handleSetPin(std::unique_ptr<ESP8266WebServer> & server);
    void AscWebServerAPI_handleHelloWorld( std::unique_ptr<ESP8266WebServer> & server );
    void AscWebServerAPI_handleSendConfg(std::unique_ptr<ESP8266WebServer> & server);
    void AscWebServerAPI_handleReqConfFile( std::unique_ptr<ESP8266WebServer> & server );

#endif

#endif // _WEBSERVERAPI_H 