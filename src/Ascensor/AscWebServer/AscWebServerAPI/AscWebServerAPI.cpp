

#include "../../../Protocols/SoftSerial/SoftSerial.h"

SoftwareSerial ESP_SERIAL_ASCWEBSERVERAPI(ESP_RX, ESP_TX);

#if defined(ESP8266)
#include "./AscWebServerAPI.h"
#include "../../../modules/WebServer/WebServerAPI/WebServerAPI.h"
#include "../../../modules/WebServer/WebServer.h"

void AscWebServerAPI_handleReqConfFile( std::unique_ptr<ESP8266WebServer> & server )
{
   ESP_SERIAL_ASCWEBSERVERAPI.println("handleReqConfFile");
   ESP_SERIAL_ASCWEBSERVERAPI.println("");

   String jsonConfg = WebServerAPI_returnReqData(server);
   if( !jsonConfg )return;

   server->send(200, "text/plain", "{\"resp\":\"OK\"}" );
}

void AscWebServerAPI_handleSendConfg(std::unique_ptr<ESP8266WebServer> & server)
{
   ESP_SERIAL_ASCWEBSERVERAPI.println("handleSendConfg");
   ESP_SERIAL_ASCWEBSERVERAPI.println("");

   String jsonConfg = WebServerAPI_returnReqData(server);
   if( !jsonConfg )return;

   server->send(200, "text/plain", "{\"resp\":\"OK\"}" );
}

void AscWebServerAPI_InitSerial()
{
  ESP_SERIAL_ASCWEBSERVERAPI.begin(BAUD_SERIAL);
}

void AscWebServerAPI_handleDashboardRedirect(std::unique_ptr<ESP8266WebServer> & server )
{  
   WebServer_redirectClient( server,"/dashboard.html" );
}

void AscWebServerAPI_handleHelloWorld( std::unique_ptr<ESP8266WebServer> & server )
{
   WebServer_redirectClient( server,"/index.html" );
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
