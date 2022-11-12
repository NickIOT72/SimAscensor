#ifndef _SPIFFS_H
#define _SPIFFS_H

#include <Arduino.h>

#if defined(ESP8266)
    void SPIFFS_InitSPIFFS();
    void SPIFFS_printFiles();
    void SPIFFS_DeleteFile(String path);
    void SPIFFS_CreateFile(String path);
    void SPIFFS_AppendFile(String path, String data);
    void SPIFFS_UpdateFile(String path, String data);
    bool SPIFFS_ExistFile(String path );
    String SPIFFS_ReadFile(String path);


#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    
#endif


#endif // !_SPIFFS_H