

#include "../../../Protocols/SoftSerial/SoftSerial.h"
SoftwareSerial ESP_SERIAL_WEBSERVERFILE(ESP_RX, ESP_TX);

#if defined(ESP8266)
  #include "WebServerFile.h"
  #include "FS.h"

  void WebServerFile_handleNotFound(std::unique_ptr<ESP8266WebServer> & server)
  {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server->uri();
    message += "\nMethod: ";
    message += (server->method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server->args();
    message += "\n";
    for (uint8_t i = 0; i < server->args(); i++)
    {
      message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
    }
    server->send(404, "text/plain", message);
  }
  
  String WebServerFile_GetContentType(String filename)
  {
    if (filename.endsWith(".htm"))
      return "text/html";
    else if (filename.endsWith(".html"))
      return "text/html";
    else if (filename.endsWith(".css"))
      return "text/css";
    else if (filename.endsWith(".js"))
      return "application/javascript";
    else if (filename.endsWith(".png"))
      return "image/png";
    else if (filename.endsWith(".gif"))
      return "image/gif";
    else if (filename.endsWith(".jpg"))
      return "image/jpeg";
    else if (filename.endsWith(".ico"))
      return "image/x-icon";
    else if (filename.endsWith(".xml"))
      return "text/xml";
    else if (filename.endsWith(".pdf"))
      return "application/x-pdf";
    else if (filename.endsWith(".map"))
      return "application/json";
    else if (filename.endsWith(".zip"))
      return "application/x-zip";
    else if (filename.endsWith(".gz"))
      return "application/x-gzip";
    return "text/plain";
  }
  
  void WebServerFile_ServeFile(std::unique_ptr<ESP8266WebServer> & server, String path)
  {
    File file = SPIFFS.open(path, "r");
    size_t sent = server->streamFile(file, WebServerFile_GetContentType(path));
    file.close();
  }
  
  void WebServerFile_ServeFile(std::unique_ptr<ESP8266WebServer> & server, String path, String contentType)
  {
    File file = SPIFFS.open(path, "r");
    size_t sent = server->streamFile(file, contentType);
    file.close();
  }
  
  bool WebServerFile_HandleFileRead(std::unique_ptr<ESP8266WebServer> & server, String path)
  {
    // if (path.endsWith("/")) path += "confplaca.html";
    ESP_SERIAL_WEBSERVERFILE.println("handleFileRead: " + path);
  
    if (SPIFFS.exists(path))
    {
      WebServerFile_ServeFile(server, path);
      return true;
    }
    ESP_SERIAL_WEBSERVERFILE.println("\tFile Not Found");
    return false;
  }
  
  bool WebServerFile_HandleFileReadGzip(std::unique_ptr<ESP8266WebServer> & server, String path)
  {
    // if (path.endsWith("/")) path += "confplaca.html";
    ESP_SERIAL_WEBSERVERFILE.println("handleFileRead: " + path);
  
    if (SPIFFS.exists(path))
    {
      WebServerFile_ServeFile(server, path, WebServerFile_GetContentType(path));
      return true;
    }
    else
    {
      String pathWithGz = path + ".gz";
      if (SPIFFS.exists(pathWithGz))
      {
        WebServerFile_ServeFile(server, pathWithGz, WebServerFile_GetContentType(path));
        return true;
      }
    }
    ESP_SERIAL_WEBSERVERFILE.println("\tFile Not Found");
    return false;
  }

  void WebServerFile_InitSerial()
  {
    ESP_SERIAL_WEBSERVERFILE.begin(BAUD_SERIAL);
  }

#endif
