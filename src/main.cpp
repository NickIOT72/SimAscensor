#include <Arduino.h>
#include <ArduinoJson.h>
#include "Ascensor/Ascensor.h"
#include "modules/JsonMod/JsonMod.h"
#include <modules/Mod74hc595/Mod74hc595.h>
#include <modules/PCF8575/PCF8575Mod.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MOD74HC595_Init();
  PCF_Init();


  String strConfInit = "{";
  strConfInit += "\"NombrePlaca\": \"\",";
  strConfInit += "\"Modelo\": \"V1\",";
  strConfInit += "\"ARCH\": {";
  strConfInit += "\"MS1\": {";
  strConfInit += "\"PINNAME\": [\"EXD\", \"PAD_PN\", \"PAS\", \"EXS\", \"FPA\", \"SPC\", \"SA\", \"SM\"],";
  strConfInit += "\"VAL\": [0, 0, 0, 0,0, 1, 1, 1]";
  strConfInit += "},";
  strConfInit += "\"MS2\": {";
  strConfInit += "\"PINNAME\": [\"BOMB\", \"EMER\", \"Q1\", \"Q2\", \"FOTO\", \"MANT\", \"PTC\", \"AUTAR\"],";
  strConfInit += "\"VAL\": [0, 0, 0, 0, 0,0, 0, 0]";
  strConfInit += "},";
  strConfInit += "\"MSA\": {";
  strConfInit += "\"PINNAME\": [\"\", \"\", \"\", \"\", \"\", \"\", \"\", \"\"],";
  strConfInit += "\"VAL\": [0, 0, 0, 0, 0, 0,0, 0]";
  strConfInit += "},";
  strConfInit += "\"ME1\": {";
  strConfInit += "\"PINNAME\": [\"RSUB\", \"RBAJ\", \"RAV\", \"RBV\", \"RABR\", \"RCER\", \"VENT\", \"PATIN\"],";
  strConfInit += "\"VAL\": [0, 0, 0, 0, 0, 0, 0, 0]";
  strConfInit += "},";
  strConfInit += "\"MEA\": {";
  strConfInit += "\"PINNAME\": [\"\", \"\", \"\", \"\", \"\", \"\", \"\", \"\"],";
  strConfInit += "\"VAL\": [0, 0, 0, 0, 0, 0, 0, 0]";
  strConfInit += "}";
  strConfInit += "},";
  strConfInit += "\"TIPO_CONTEO\": \"PADPAS\"";
  strConfInit += "}";

  DynamicJsonDocument JSONObjectConfg(JSON_Buffer);
  if (!verificarJson( strConfInit,  JSONObjectConfg)) { Serial.println("Eror1");  while (true){delay(1);}}
  Serial.println("Init Asc:");
  long tstart = millis();
  Serial.println("End Asc: " + String( millis()-tstart ));
  Ascensor_Init(JSONObjectConfg); 
  Serial.print("PCF:");
  Serial.println(PCF_readBuffer(),BIN);
  Serial.print("74HC595:");
  Serial.println(MOD74HC595_Configuration() ,BIN);

}

void loop() {
  // put your main code here, to run repeatedly:
}