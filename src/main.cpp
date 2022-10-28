#include <Arduino.h>
//#include "../.pio/libdeps/Arduino Mega/avr-debugger/avr8-stub/avr8-stub.h"
#include <ArduinoJson.h>
#include "Ascensor/Ascensor.h"
#include "modules/JsonMod/JsonMod.h"
#include <modules/Mod74hc595/Mod74hc595.h>
#include <modules/PCF8575/PCF8575Mod.h>
#include "Protocols/SoftSerial/SoftSerial.h"

SoftwareSerial ESP_SERIAL(ESP_RX, ESP_TX);

void setup() {
  // put your setup code here, to run once:
  ESP_SERIAL.begin(9600);
  MOD74HC595_Init();
  PCF_Init();


  String strConfInit = "{";
  strConfInit += "\"NombrePlaca\": \"\",";
  strConfInit += "\"Modelo\": \"V1\",";
  strConfInit += "\"ARCH\": {";
  strConfInit += "\"MS1\": {";
  strConfInit += "\"PINNAME\": [\"\", \"PAD_PN\", \"PAS\", \"EXS\", \"FPA\", \"SPC\", \"SA\", \"\"],";
  strConfInit += "\"VAL\": [0, 0, 0, 0,0, 1, 1, 0]";
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
  strConfInit += "\"PINNAME\": [\"SM\", \"EXD\", \"\", \"\", \"\", \"\", \"\", \"\"],";
  strConfInit += "\"VAL\": [1, 1, 0, 0, 0, 0, 0, 0]";
  strConfInit += "}";
  strConfInit += "},";
  strConfInit += "\"TIPO_CONTEO\": \"PADPAS\"";
  strConfInit += "}";

  DynamicJsonDocument JSONObjectConfg(JSON_Buffer);
  if (!verificarJson( strConfInit,  JSONObjectConfg)) { ESP_SERIAL.println("Eror1");  while (true){delay(1);}}
  liberarDinMemJsonDoc(JSONObjectConfg);
  ESP_SERIAL.println("Init Asc:");
  long tstart = micros();
  Ascensor_Init(strConfInit);
  ESP_SERIAL.println("End Asc: " + String( micros()-tstart ));
  ESP_SERIAL.print("PCF:");
  ESP_SERIAL.println(PCF_readBuffer(),BIN);
  ESP_SERIAL.print("74HC595:");
  ESP_SERIAL.println(MOD74HC595_Configuration() ,BIN);

}

void loop() {
  // put your main code here, to run repeatedly:
}