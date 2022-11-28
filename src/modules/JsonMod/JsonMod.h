#ifndef _JSONMOD_H
#define _JSONMOD_H

#include <Arduino.h>
#include <ArduinoJson.h>

#define JSON_Buffer 3000

bool jsonMod_verificarJson(String Str);
bool jsonMod_verificarJson(char* json );
bool jsonMod_verificarJson(String Str, JsonDocument &JSONObject );
bool jsonMod_verificarJson(char* json, JsonDocument &JSONObject );

void jsonMod_liberarDinMemJsonDoc(DynamicJsonDocument &JsonObject);
void jsonMod_limpiarJsonDoc(JsonDocument &JsonObject);
void JsonMod_FilterPrint(String NewJsonInit, JsonDocument &JSONObjectFilter, char* titleDta[], uint8_t elements);
void JsonMod_SerialInit();

void JsonMod_FilterCharArray(String NewJsonInit, char* variableStore[], char* titleDta[], uint8_t elements );
void JsonMod_FilterChar(String NewJsonInit, char* variableStore, char* titleDta[], uint8_t elements);
void JsonMod_FilterInt(String NewJsonInit, int* valor, char* titleDta[], uint8_t elements);

void JsonMod_FilterIntArray(String NewJsonInit, uint8_t* variableStore, char* titleDta[], uint8_t elements );


#endif // !_JSONMOD_H