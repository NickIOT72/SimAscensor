

#include "../../modules/JsonMod/JsonMod.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"

SoftwareSerial ESP_SERIAL_ASCSPIFFS(ESP_RX, ESP_TX);

#if defined(ESP8266)
#include "AscSPIFFS.h"
#include "../../Protocols/SPIFFS/SPIFFS.h"

    void VerificarArchivos(String strConfInit, String path)
    {
        ESP_SERIAL_ASCSPIFFS.begin(BAUD_SERIAL);
        if (!SPIFFS_ExistFile(path))
        {
            SPIFFS_UpdateFile(path, strConfInit);
        }
        else
        {
            String FileToSend = SPIFFS_ReadFile(CONFG_FILE);
            if( !jsonMod_verificarJson( FileToSend ) ){
                SPIFFS_UpdateFile(CONFG_FILE, strConfInit);
            }
        }
    }
    
#endif
