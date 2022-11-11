#ifndef _WEBSERVERFILE_H
#define _WEBSERVERFILE_H 

#include <Arduino.h>
#if defined(ESP8266)
    #include <ESP8266WebServer.h>

    void WebServerFile_InitSerial();
    bool WebServerFile_HandleFileRead(std::unique_ptr<ESP8266WebServer> & server, String path);
    void WebServerFile_handleNotFound(std::unique_ptr<ESP8266WebServer> & server);

#endif

#endif // _WEBSERVERFILE_H 