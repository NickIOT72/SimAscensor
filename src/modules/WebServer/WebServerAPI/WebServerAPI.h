#ifndef _WEBSERVERAPI_H
#define _WEBSERVERAPI_H 

#include <Arduino.h>

#if defined(ESP8266)
    #include <ESP8266WebServer.h>

    void WebServerAPI_InitSerial();
    String WebServerAPI_returnReqData( std::unique_ptr<ESP8266WebServer> & server );

#endif

#endif // _WEBSERVERAPI_H 