

#include "../../../Protocols/SoftSerial/SoftSerial.h"

SoftwareSerial ESP_SERIAL_ASCWEBSERVERAPI(ESP_RX, ESP_TX);

#if defined(ESP8266)
#include "./AscWebServerAPI.h"
#include "../../../modules/WebServer/WebServerAPI/WebServerAPI.h"

void AscWebServerAPI_InitSerial()
{
  ESP_SERIAL_ASCWEBSERVERAPI.begin(BAUD_SERIAL);
}

void AscWebServerAPI_handleHelloWorld( std::unique_ptr<ESP8266WebServer> & server )
{
   ESP_SERIAL_ASCWEBSERVERAPI.println("handleHelloWorld");
   ESP_SERIAL_ASCWEBSERVERAPI.println("");

   String jsonConfg = WebServerAPI_returnReqData(server);
   if( !jsonConfg )return;

   server->send(200, "text/plain", "{\"resp\":\"OK\"}" );
}

void AscWebServerAPI_handleSetPin(std::unique_ptr<ESP8266WebServer> & server)
{
   ESP_SERIAL_ASCWEBSERVERAPI.println("handleSetPin");
   ESP_SERIAL_ASCWEBSERVERAPI.println("");

   String jsonConfg = WebServerAPI_returnReqData(server);
   if( !jsonConfg )return;

   server->send(200, "text/plain", "{\"resp\":\"OK\"}" );
}

#endif
