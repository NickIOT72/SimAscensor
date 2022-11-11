

#include "../../../Protocols/SoftSerial/SoftSerial.h"

SoftwareSerial ESP_SERIAL_WEBSERVERAPI(ESP_RX, ESP_TX);

#if defined(ESP8266)
#include "./WebServerAPI.h"

void WebServerAPI_InitSerial()
{
  ESP_SERIAL_WEBSERVERAPI.begin(BAUD_SERIAL);
}

String WebServerAPI_returnReqData( std::unique_ptr<ESP8266WebServer> & server )
{
    if (server->hasArg("plain") == false)
    { // Check if body received
       server->send(200, "text/plain", "{\"resp\":\"NOK\"}");
       return "";
    }
    String jsonConfg = server->arg("plain");
    String message = "handleHelloWorld Body received:\n";
    message += jsonConfg;
    message += "\n";

   ESP_SERIAL_WEBSERVERAPI.println(message);

   return jsonConfg;


}
#endif
