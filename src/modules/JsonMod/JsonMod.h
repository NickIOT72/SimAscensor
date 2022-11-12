#ifndef _JSONMOD_H
#define _JSONMOD_H

#include <Arduino.h>
#include <ArduinoJson.h>

#define JSON_Buffer 1000

bool jsonMod_verificarJson(String Str);
bool jsonMod_verificarJson(char* json );
bool jsonMod_verificarJson(String Str, JsonDocument &JSONObject );
bool jsonMod_verificarJson(char* json, JsonDocument &JSONObject );

void jsonMod_liberarDinMemJsonDoc(DynamicJsonDocument &JsonObject);
void jsonMod_limpiarJsonDoc(JsonDocument &JsonObject);

#endif // !_JSONMOD_H