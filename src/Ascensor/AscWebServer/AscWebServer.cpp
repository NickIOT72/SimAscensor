
#include "../../Protocols/SoftSerial/SoftSerial.h"
SoftwareSerial ESP_SERIAL_ASCWEBSERVER(ESP_RX, ESP_TX);

#if defined(ESP8266)

#include "./AscWebServer.h"
#include "./AscWebServerAPI/AscWebServerAPI.h"
#include "../../modules/WebServer/WebServerFile/WebServerFile.h"

#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino


std::unique_ptr<ESP8266WebServer> AscServer;

void AscWebServer_callHandleSetPin(){AscWebServerAPI_handleSetPin( AscServer );}//WebServerAPI_handleSetPin( server );
void AscWebServer_callHandleHelloWorld(){ AscWebServerAPI_handleHelloWorld( AscServer ); }//WebServerAPI_handleHelloWorld( server ); 

void AscWebServer_handleClient()
{
  AscServer->handleClient();
}

void AscensorWebServer_InitServer(  )
{
    AscWebServerAPI_InitSerial();
    AscServer.reset(new ESP8266WebServer(WiFi.localIP(), WS_PORT));

    ESP_SERIAL_ASCWEBSERVER.begin(BAUD_SERIAL);

    AscServer->on("/helloWorld", HTTP_POST, AscWebServer_callHandleHelloWorld);
    AscServer->on("/setPin", HTTP_POST, AscWebServer_callHandleSetPin);
    
    AscServer->onNotFound([]() {                                   // If the client requests any URI
      if (!WebServerFile_HandleFileRead(AscServer, AscServer->uri())) // send it if it exists
        WebServerFile_handleNotFound(AscServer);                   // otherwise, respond with a 404 (Not Found) error
    });
    AscServer->begin();
    ESP_SERIAL_ASCWEBSERVER.println("HTTP server started");
}

#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)

#endif