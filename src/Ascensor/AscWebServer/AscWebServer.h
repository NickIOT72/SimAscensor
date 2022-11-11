#ifndef _ASCWEBSERVER_H
#define _ASCWEBSERVER_H 

#include <Arduino.h>

#if defined(ESP8266)
    #include <ESP8266WebServer.h>
    #define WS_PORT 80 
    //extern std::unique_ptr<ESP8266WebServer> AscServer;
    //void (*f)(std::unique_ptr<ESP8266WebServer> &  );
    void AscensorWebServer_InitServer(  );
    void AscWebServer_handleClient();

#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)

#endif


#endif // _ASCWEBSERVER_H 