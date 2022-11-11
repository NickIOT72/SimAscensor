#ifndef _WEBSERVER_H
#define _WEBSERVER_H 

#include <Arduino.h>

#if defined(ESP8266)
    #include <ESP8266WebServer.h>
    
    extern std::unique_ptr<ESP8266WebServer> server;
    //void (*f)(std::unique_ptr<ESP8266WebServer> &  );
    void WebServer_InitWiFiManager( void (*f)()    );
    void WebServer_handleClient();
    void WebServer_redirectClient(std::unique_ptr<ESP8266WebServer> & server , String path);
    //void WebServer_handleServer( void (*f)(std::unique_ptr<ESP8266WebServer>) );
    //std::unique_ptr<ESP8266WebServer> &  return_server();


#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)

#endif


#endif // _WEBSERVER_H 