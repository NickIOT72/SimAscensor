#ifndef _ASCSPIFFS_H
#define _ASCSPIFFS_H

#include <Arduino.h>
const String CONFG_FILE = "/ConfgPlaca.json";

#if defined(ESP8266)
    void VerificarArchivos(String strConfInit, String path);
#endif

#endif