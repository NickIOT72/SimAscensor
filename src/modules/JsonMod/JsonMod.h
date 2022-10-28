#ifndef _JSONMOD_H
#define _JSONMOD_H

#include <Arduino.h>
#include <ArduinoJson.h>

#define JSON_Buffer 2000

bool verificarJson(String Str);
bool verificarJson(char* json );
bool verificarJson(String Str, JsonDocument &JSONObject );
bool verificarJson(char* json, JsonDocument &JSONObject );

void liberarDinMemJsonDoc(DynamicJsonDocument &JsonObject);
void limpiarJsonDoc(JsonDocument &JsonObject);

#endif // !_JSONMOD_H