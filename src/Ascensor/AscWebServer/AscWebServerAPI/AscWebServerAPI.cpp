

#include "../../../Protocols/SoftSerial/SoftSerial.h"
#include <ArduinoJson.h>
SoftwareSerial ESP_SERIAL_ASCWEBSERVERAPI(ESP_RX, ESP_TX);

#if defined(ESP8266)
#include "./AscWebServerAPI.h"
#include "../../../modules/WebServer/WebServerAPI/WebServerAPI.h"
#include "../../../modules/WebServer/WebServer.h"
#include "../../../Protocols/SPIFFS/SPIFFS.h"

void AscWebServerAPI_handleReqConfFile( std::unique_ptr<ESP8266WebServer> & server )
{
   String FileSend = SPIFFS_ReadFile("/ConfgPlaca.text");
   server->send(200, "text/plain", FileSend);
}



void EscribirConfPlaca(JsonDocument &JSONObject)
{
   String NombrePlacaV = JSONObject["NombrePlaca"];
   String ModeloV = JSONObject["Modelo"];
   String TIPO_CONTEOV = JSONObject["TIPO_CONTEO"];

   JsonObject EstructuraV = JSONObject["ARCH"];

   JsonArray ms1Vi = EstructuraV["MS1"]["PINNAME"];
   JsonArray ms2Vi = EstructuraV["MS2"]["PINNAME"];
   JsonArray msaVi = EstructuraV["MSA"]["PINNAME"];
   JsonArray me1Vi = EstructuraV["ME1"]["PINNAME"];
   JsonArray meaVi = EstructuraV["MEA"]["PINNAME"];

   String ms1V[8] = {
       ms1Vi[0], ms1Vi[1], ms1Vi[2], ms1Vi[3], ms1Vi[4], ms1Vi[5], ms1Vi[6], ms1Vi[7]};
   String ms2V[8] = {
       ms2Vi[0], ms2Vi[1], ms2Vi[2], ms2Vi[3], ms2Vi[4], ms2Vi[5], ms2Vi[6], ms2Vi[7]};
   String msaV[8] = {
       msaVi[0], msaVi[1], msaVi[2], msaVi[3], msaVi[4], msaVi[5], msaVi[6], msaVi[7]};
   String me1V[8] = {
       me1Vi[0], me1Vi[1], me1Vi[2], me1Vi[3], me1Vi[4], me1Vi[5], me1Vi[6], me1Vi[7]};
   String meaV[8] = {
       meaVi[0], meaVi[1], meaVi[2], meaVi[3], meaVi[4], meaVi[5], meaVi[6], meaVi[7]};

   JsonArray ms1Vvi = EstructuraV["MS1"]["VAL"];
   JsonArray ms2Vvi = EstructuraV["MS2"]["VAL"];
   JsonArray msaVvi = EstructuraV["MSA"]["VAL"];
   JsonArray me1Vvi = EstructuraV["ME1"]["VAL"];
   JsonArray meaVvi = EstructuraV["MEA"]["VAL"];

   String ms1Vv[8] = {
       ms1Vvi[0], ms1Vvi[1], ms1Vvi[2], ms1Vvi[3], ms1Vvi[4], ms1Vvi[5], ms1Vvi[6], ms1Vvi[7]};
   String ms2Vv[8] = {
       ms2Vvi[0], ms2Vvi[1], ms2Vvi[2], ms2Vvi[3], ms2Vvi[4], ms2Vvi[5], ms2Vvi[6], ms2Vvi[7]};
   String msaVv[8] = {
       msaVvi[0], msaVvi[1], msaVvi[2], msaVvi[3], msaVvi[4], msaVvi[5], msaVvi[6], msaVvi[7]};
   String me1Vv[8] = {
       me1Vvi[0], me1Vvi[1], me1Vvi[2], me1Vvi[3], me1Vvi[4], me1Vvi[5], me1Vvi[6], me1Vvi[7]};
   String meaVv[8] = {
       meaVvi[0], meaVvi[1], meaVvi[2], meaVvi[3], meaVvi[4], meaVvi[5], meaVvi[6], meaVvi[7]};

   String strG = "{";
         strG += "\"NombrePlaca\":\"" + NombrePlacaV + "\",";
          strG += "\"Modelo\":\"" + ModeloV + "\",";
          strG += "\"ARCH\": {";
              strG += "\"MS1\": {";
                  strG += "\"PINNAME\": [\"" + ms1V[0] + "\", \"" + ms1V[1] + "\", \"" + ms1V[2] + "\", \"" + ms1V[3] + "\", \"" + ms1V[4] + "\", \"" + ms1V[5] + "\", \"" + ms1V[6] + "\", \"" + ms1V[7] + "\"],";
                  strG += "\"VAL\": [\"" + ms1Vv[0] + "\", \"" + ms1Vv[1] + "\", \"" + ms1Vv[2] + "\", \"" + ms1Vv[3] + "\", \"" + ms1Vv[4] + "\", \"" + ms1Vv[5] + "\", \"" + ms1Vv[6] + "\", \"" + ms1Vv[7] + "\"]";
              strG += "},";
              strG += "\"MS2\": {";
                  strG += "\"PINNAME\": [\"" + ms2V[0] + "\", \"" + ms2V[1] + "\", \"" + ms2V[2] + "\", \"" + ms2V[3] + "\", \"" + ms2V[4] + "\", \"" + ms2V[5] + "\", \"" + ms2V[6] + "\", \"" + ms2V[7] + "\"],";
                  strG += "\"VAL\": [\"" + ms2Vv[0] + "\", \"" + ms2Vv[1] + "\", \"" + ms2Vv[2] + "\", \"" + ms2Vv[3] + "\", \"" + ms2Vv[4] + "\", \"" + ms2Vv[5] + "\", \"" + ms2Vv[6] + "\", \"" + ms2Vv[7] + "\"]";
              strG += "},";
              strG += "\"MSA\": {";
                  strG += "\"PINNAME\": [\"" + msaV[0] + "\", \"" + msaV[1] + "\", \"" + msaV[2] + "\", \"" + msaV[3] + "\", \"" + msaV[4] + "\", \"" + msaV[5] + "\", \"" + msaV[6] + "\", \"" + msaV[7] + "\"],";
                  strG += "\"VAL\": [\"" + msaVv[0] + "\", \"" + msaVv[1] + "\", \"" + msaVv[2] + "\", \"" + msaVv[3] + "\", \"" + msaVv[4] + "\", \"" + msaVv[5] + "\", \"" + msaVv[6] + "\", \"" + msaVv[7] + "\"]";
              strG += "},";
              strG += "\"ME1\": {";
                  strG += "\"PINNAME\": [\"" + me1V[0] + "\", \"" + me1V[1] + "\", \"" + me1V[2] + "\", \"" + me1V[3] + "\", \"" + me1V[4] + "\", \"" + me1V[5] + "\", \"" + me1V[6] + "\", \"" + me1V[7] + "\"],";
                  strG += "\"VAL\": [\"" + me1Vv[0] + "\", \"" + me1Vv[1] + "\", \"" + me1Vv[2] + "\", \"" + me1Vv[3] + "\", \"" + me1Vv[4] + "\", \"" + me1Vv[5] + "\", \"" + me1Vv[6] + "\", \"" + me1Vv[7] + "\"]";
              strG += "},";
              strG += "\"MEA\": {";
                  strG += "\"PINNAME\": [\"" + meaV[0] + "\", \"" + meaV[1] + "\", \"" + meaV[2] + "\", \"" + meaV[3] + "\", \"" + meaV[4] + "\", \"" + meaV[5] + "\", \"" + meaV[6] + "\", \"" + meaV[7] + "\"],";
                  strG += "\"VAL\": [\"" + meaVv[0] + "\", \"" + meaVv[1] + "\", \"" + meaVv[2] + "\", \"" + meaVv[3] + "\", \"" + meaVv[4] + "\", \"" + meaVv[5] + "\", \"" + meaVv[6] + "\", \"" + meaVv[7] + "\"]";
              strG += "}";
          strG += "},";
          strG += "\"TIPO_CONTEO\": \"" + TIPO_CONTEOV + "\"";
      strG += "}";
   ESP_SERIAL_ASCWEBSERVERAPI.println("Datos a ver: " + strG );

   SPIFFS_UpdateFile("/ConfgPlaca.text", strG);
   
}

bool ActulizarConfgPlaca(String jsonConfg)
{
   char StrProvp[ jsonConfg.length() + 1 ] ;
   jsonConfg.toCharArray(StrProvp , jsonConfg.length() + 1   );
   DynamicJsonDocument JSONObject(ws_json_capacity);
   DeserializationError error = deserializeJson(JSONObject, StrProvp);
   if (error)
   {
      ESP_SERIAL_ASCWEBSERVERAPI.println("DeserializeJson() for f2b message failed: " + String(error.c_str()));
      return false;
   }
   ESP_SERIAL_ASCWEBSERVERAPI.println(F("Json received: "));
   serializeJsonPretty(JSONObject, ESP_SERIAL_ASCWEBSERVERAPI); /**/

   EscribirConfPlaca(JSONObject);
   
   return true;
}

void AscWebServerAPI_handleSendConfg(std::unique_ptr<ESP8266WebServer> & server)
{
   ESP_SERIAL_ASCWEBSERVERAPI.println("handleSendConfg");
   ESP_SERIAL_ASCWEBSERVERAPI.println("");

   String jsonConfg = WebServerAPI_returnReqData(server);
   if( !jsonConfg )return;

   bool ActConfg = ActulizarConfgPlaca(jsonConfg);
   String respondData = ActConfg ? "{\"resp\":\"OK\"}" : "{\"resp\":\"NOK\"}";

   server->send(200, "text/plain", respondData );
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




bool setPinsEnConfg(String jsonSTR, uint8 mod)
{
   
   char StrProvp[ jsonSTR.length() + 1 ] ;
   jsonSTR.toCharArray(StrProvp , jsonSTR.length() + 1   );
   DynamicJsonDocument JSONObject(ws_json_capacity);
   DeserializationError error = deserializeJson(JSONObject, StrProvp);
   if (error)
   {
      ESP_SERIAL_ASCWEBSERVERAPI.println("DeserializeJson() for f2b message failed: " + String(error.c_str()));
      return false;
   }
   else
   {
      ESP_SERIAL_ASCWEBSERVERAPI.print(F("Json received: "));
      serializeJsonPretty(JSONObject, ESP_SERIAL_ASCWEBSERVERAPI); /**/

      String ConfgFile = SPIFFS_ReadFile("/ConfgPlaca.text");

      char StrProvp[ ConfgFile.length() + 1 ] ;
      ConfgFile.toCharArray(StrProvp , ConfgFile.length() + 1   );
      DynamicJsonDocument JSONObjectConfg(ws_json_capacity);
      DeserializationError error2 = deserializeJson(JSONObjectConfg, StrProvp);
      if (error2)
      {
         ESP_SERIAL_ASCWEBSERVERAPI.println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
         return false;
      }
      else
      {
         ESP_SERIAL_ASCWEBSERVERAPI.print(F("Json received: "));
         serializeJsonPretty(JSONObjectConfg, ESP_SERIAL_ASCWEBSERVERAPI); /**/

         if (mod == MOD_IN)
         {
            JsonArray arrayPinnameME1 = JSONObjectConfg["ARCH"]["ME1"]["PINNAME"];
            JsonArray arrayPinnameMEA = JSONObjectConfg["ARCH"]["MEA"]["PINNAME"];

            JsonArray PINNAMEnew = JSONObject["SETPIN"]["PINNAME"];
            JsonArray VALnew = JSONObject["SETPIN"]["VAL"];

            ESP_SERIAL_ASCWEBSERVERAPI.print("arrayPinnameME1.size(): ");
            ESP_SERIAL_ASCWEBSERVERAPI.println(arrayPinnameME1.size());

            ESP_SERIAL_ASCWEBSERVERAPI.print("arrayPinnameME1.size(): ");
            ESP_SERIAL_ASCWEBSERVERAPI.println(arrayPinnameMEA.size());

            for (size_t  i = 0; i < arrayPinnameME1.size(); i++)
            {
               String pinnameStr = arrayPinnameME1[i];
               for (size_t  j = 0; j < PINNAMEnew.size(); j++)
               {
                  String pinnameStrNew = PINNAMEnew[j];
                  String valStrNew = VALnew[j];
                  ESP_SERIAL_ASCWEBSERVERAPI.print("pinnameStrNew == pinnameStr: ");
                  ESP_SERIAL_ASCWEBSERVERAPI.println(pinnameStrNew + "," + pinnameStr + ";");
                  if (pinnameStrNew == pinnameStr)
                  {
                     ESP_SERIAL_ASCWEBSERVERAPI.println("OK MIN1");
                     JSONObjectConfg["ARCH"]["ME1"]["PINNAME"][i] = pinnameStrNew;
                     JSONObjectConfg["ARCH"]["ME1"]["VAL"][i] = valStrNew;
                     serializeJsonPretty(JSONObjectConfg["ARCH"]["MIN1"], ESP_SERIAL_ASCWEBSERVERAPI); 
                     break;
                  }
               }
            }

            for (size_t  i = 0; i < arrayPinnameMEA.size(); i++)
            {
               String pinnameStr = arrayPinnameMEA[i];
               for (size_t  j = 0; j < PINNAMEnew.size(); j++)
               {
                  String pinnameStrNew = PINNAMEnew[j];
                  String valStrNew = VALnew[j];
                  ESP_SERIAL_ASCWEBSERVERAPI.print("pinnameStrNew == pinnameStr: ");
                  ESP_SERIAL_ASCWEBSERVERAPI.println(pinnameStrNew + "," + pinnameStr + ";");
                  if (pinnameStrNew == pinnameStr)
                  {
                     ESP_SERIAL_ASCWEBSERVERAPI.println("OK min2");
                     JSONObjectConfg["ARCH"]["MEA"]["PINNAME"][i] = pinnameStrNew;
                     JSONObjectConfg["ARCH"]["MEA"]["VAL"][i] = valStrNew;
                     ESP_SERIAL_ASCWEBSERVERAPI.print(F("  NEW Json received: "));
                     serializeJsonPretty(JSONObjectConfg["ARCH"]["MIN2"], ESP_SERIAL_ASCWEBSERVERAPI); 
                     break;
                  }
               }
            }

            EscribirConfPlaca(JSONObjectConfg);
            serializeJsonPretty(JSONObjectConfg, ESP_SERIAL_ASCWEBSERVERAPI);

            return true;
         }
         else if (mod == MOD_OUT)
         {
            JsonArray arrayPinnameMS1 = JSONObjectConfg["ARCH"]["MS1"]["PINNAME"];
            JsonArray arrayPinnameMS2 = JSONObjectConfg["ARCH"]["MS2"]["PINNAME"];
            JsonArray arrayPinnameMSA = JSONObjectConfg["ARCH"]["MSA"]["PINNAME"];


            JsonArray PINNAMEnew = JSONObject["SETPIN"]["PINNAME"];
            JsonArray VALnew = JSONObject["SETPIN"]["VAL"];

            ESP_SERIAL_ASCWEBSERVERAPI.print("arrayPinnameMS1.size(): ");
            ESP_SERIAL_ASCWEBSERVERAPI.println(arrayPinnameMS1.size());

            ESP_SERIAL_ASCWEBSERVERAPI.print("arrayPinnameMS2.size(): ");
            ESP_SERIAL_ASCWEBSERVERAPI.println(arrayPinnameMS2.size());


            for (size_t  i = 0; i < arrayPinnameMS1.size(); i++)
            {
               String pinnameStr = arrayPinnameMS1[i];
               for (size_t  j = 0; j < PINNAMEnew.size(); j++)
               {
                  String pinnameStrNew = PINNAMEnew[j];
                  String valStrNew = VALnew[j];
                  ESP_SERIAL_ASCWEBSERVERAPI.print("pinnameStrNew == pinnameStr: ");
                  ESP_SERIAL_ASCWEBSERVERAPI.println(pinnameStrNew + "," + pinnameStr + ";");
                  if (pinnameStrNew == pinnameStr)
                  {
                     ESP_SERIAL_ASCWEBSERVERAPI.println("OK MS1");
                     JSONObjectConfg["ARCH"]["MS1"]["PINNAME"][i] = pinnameStrNew;
                     JSONObjectConfg["ARCH"]["MS1"]["VAL"][i] = valStrNew;
                     break;
                  }
               }
            }

            for (size_t  i = 0; i < arrayPinnameMS2.size(); i++)
            {
               String pinnameStr = arrayPinnameMS2[i];
               for (size_t  j = 0; j < PINNAMEnew.size(); j++)
               {
                  String pinnameStrNew = PINNAMEnew[j];
                  String valStrNew = VALnew[j];
                  ESP_SERIAL_ASCWEBSERVERAPI.print("pinnameStrNew == pinnameStr: ");
                  ESP_SERIAL_ASCWEBSERVERAPI.println(pinnameStrNew + "," + pinnameStr + ";");
                  if (pinnameStrNew == pinnameStr)
                  {
                     ESP_SERIAL_ASCWEBSERVERAPI.println("OK MS2");
                     JSONObjectConfg["ARCH"]["MS2"]["PINNAME"][i] = pinnameStrNew;
                     JSONObjectConfg["ARCH"]["MS2"]["VAL"][i] = valStrNew;
                     break;
                  }
               }
            }

            for (size_t  i = 0; i < arrayPinnameMSA.size(); i++)
            {
               String pinnameStr = arrayPinnameMSA[i];
               for (size_t  j = 0; j < PINNAMEnew.size(); j++)
               {
                  String pinnameStrNew = PINNAMEnew[j];
                  String valStrNew = VALnew[j];
                  ESP_SERIAL_ASCWEBSERVERAPI.print("pinnameStrNew == pinnameStr: ");
                  ESP_SERIAL_ASCWEBSERVERAPI.println(pinnameStrNew + "," + pinnameStr + ";");
                  if (pinnameStrNew == pinnameStr)
                  {
                     ESP_SERIAL_ASCWEBSERVERAPI.println("OK MSA");
                     JSONObjectConfg["ARCH"]["MSA"]["PINNAME"][i] = pinnameStrNew;
                     JSONObjectConfg["ARCH"]["MSA"]["VAL"][i] = valStrNew;
                     break;
                  }
               }
            }
            EscribirConfPlaca(JSONObjectConfg);
            serializeJsonPretty(JSONObjectConfg, ESP_SERIAL_ASCWEBSERVERAPI);
            
            return true;
         }
         else {
            return false;
         }
      }
   }
}

void AscWebServerAPI_handleSetPin(std::unique_ptr<ESP8266WebServer> & server)
{
   ESP_SERIAL_ASCWEBSERVERAPI.println("handleSetPin");
   ESP_SERIAL_ASCWEBSERVERAPI.println("");

   String jsonConfg = WebServerAPI_returnReqData(server);
   if( !jsonConfg )return;

   bool ActConfg = setPinsEnConfg(jsonConfg, MOD_OUT);
   if (ActConfg)
   {
      char StrProvp[ jsonConfg.length() + 1 ] ;
      jsonConfg.toCharArray(StrProvp , jsonConfg.length() + 1   );
      DynamicJsonDocument JSONObject(ws_json_capacity);
      DeserializationError error = deserializeJson(JSONObject, StrProvp);
      if (error)
      {
         ESP_SERIAL_ASCWEBSERVERAPI.println("DeserializeJson() for f2b message failed: " + String(error.c_str()));
         // server->send(200, "text/plain", "{\"resp\":\"NOK\"}");
         return;
      }
      JsonObject SETPIN = JSONObject["SETPIN"];
      JsonArray PINNAME = SETPIN["PINNAME"];
      JsonArray VAL = SETPIN["VAL"];

      ESP_SERIAL_ASCWEBSERVERAPI.println("Act PINS");
      uint8_t pinSize = PINNAME.size();
      for (uint8_t i = 0; i < pinSize; i++)
      {
         String pinnameStr = PINNAME[i];
         String valStr = VAL[i];
         ESP_SERIAL_ASCWEBSERVERAPI.println("PIN:" + pinnameStr + " -> VAL:" + valStr);
      }
      
      server->send(200, "text/plain", "{\"resp\":\"OK\"}");
   }
   else
   {
      server->send(200, "text/plain", "{\"resp\":\"NOK\"}");
   }
}

#endif
