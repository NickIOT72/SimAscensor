#include <Arduino.h>
//#include "../.pio/libdeps/Arduino Mega/avr-debugger/avr8-stub/avr8-stub.h"
#include <ArduinoJson.h>
#include "Ascensor/Ascensor.h"
#include "modules/JsonMod/JsonMod.h"
#include <modules/Mod74hc595/Mod74hc595.h>
#include <modules/PCF8575/PCF8575Mod.h>
#include <modules/74HC4067MOD/74HC4067MOD.h>
#include <Ascensor/Puertas/Puertas.h>
#include "Ascensor/Seguridades/Seguridades.h"
#include "Ascensor/Banderas/Banderas.h"
#include "Protocols/SoftSerial/SoftSerial.h"
#include "modules/OLEDMod/OLEDMod.h"
#if defined(ESP8266)
  #include "modules/WebServer/WebServer.h"
  #include "Ascensor/AscWebServer/AscWebServer.h"
#endif
#include <Wire.h>

SoftwareSerial ESP_SERIAL(ESP_RX, ESP_TX);

void getI2Caddress()
{
  Wire.begin();
  byte error, address;
  int nDevices;

  ESP_SERIAL.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      ESP_SERIAL.print("I2C device found at address 0x");
      if (address<16) 
        ESP_SERIAL.print("0");
      ESP_SERIAL.print(address,HEX);
      ESP_SERIAL.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      ESP_SERIAL.print("Unknown error at address 0x");
      if (address<16) 
        ESP_SERIAL.print("0");
      ESP_SERIAL.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    ESP_SERIAL.println("No I2C devices found\n");
  else
    ESP_SERIAL.println("done\n");

}

void setup() {
  ESP_SERIAL.begin(9600);
  OLED_Init();
  OLED_MensajeInicial();
  MOD74HC595_Init();
  MUX74HC4067_Init();

  #if defined(ESP8266)
    WebServer_InitWiFiManager( AscensorWebServer_InitServer );
    while(true)
    {
      AscWebServer_handleClient();
      delay(5);
    }
  #elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    while(true)
    {
      delay(5);
    }
  #endif


  //MUX74HC4067_test();
  //PCF_Init();
  //getI2Caddress();
  //while (true)
  //{
  //  MUX74HC4067_test();
  //}
  
  String strConfInit = "{";
  strConfInit += "\"NombrePlaca\": \"\",";
  strConfInit += "\"Modelo\": \"V1\",";
  strConfInit += "\"ARCH\": {";
  strConfInit += "\"MSA\": {";
  strConfInit += "\"PINNAME\": [\"EXD\", \"PAD_PN\", \"PAS\", \"EXS\", \"FPA\", \"SPC\", \"SA\", \"SM\"],";
  strConfInit += "\"VAL\": [0, 0, 0, 0,0, 1, 1, 1]";
  strConfInit += "},";
  strConfInit += "\"MS2\": {";
  strConfInit += "\"PINNAME\": [\"BOMB\", \"EMER\", \"Q1\", \"Q2\", \"FOTO\", \"MANT\", \"PTC\", \"AUTAR\"],";
  strConfInit += "\"VAL\": [0, 0, 0, 0, 0,0, 0, 0]";
  strConfInit += "},";
  strConfInit += "\"MS1\": {";
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
  strConfInit += "\"TIPO_CONTEO\": \"PADPAS\",";
  strConfInit += "\"TOTAL_PISOS\": 8";
  strConfInit += "}";

  DynamicJsonDocument JSONObjectConfg(JSON_Buffer);
  if (!jsonMod_verificarJson( strConfInit,  JSONObjectConfg)) { ESP_SERIAL.println("Eror1");  while (true){delay(1);}}
  jsonMod_liberarDinMemJsonDoc(JSONObjectConfg);
  ESP_SERIAL.println("Init Asc:");
  Ascensor_Init(strConfInit);
  Banderas_resetContadorBanderas();
  ESP_SERIAL.println("Probar Puerta");
  delay(3000);

  ESP_SERIAL.println("Starting firmware");
}

void loop() {
  // put your main code here, to run repeatedly:
 

  uint16_t lecturaPuerta = Puertas_leerEstadoPuerta();
  uint16_t lecturaSeg = Seguridades_leerEstadoPuerta();

  //ESP_SERIAL.print("Puerta: ");
  //ESP_SERIAL.print(lecturaPuerta , BIN);
  //ESP_SERIAL.print("Banderas: ");
  //ESP_SERIAL.println(lecturaSeg , BIN);
  //delay(250);

  static bool PuertaAbiertaEsperandoStop = false;
  static bool PuertaCerradaEsperandoStop = false;
  static bool PuertaStop = false;
  bool CabinaEnMovimiento = false;

  
  switch (lecturaPuerta)
  {
  case puertaAbriendo:
    switch (lecturaSeg)
    {
    case abiertaPuerta:
      if (PuertaAbiertaEsperandoStop)
      {
        break;
      }

      ESP_SERIAL.println("Puerta Abierta.");
      PuertaAbiertaEsperandoStop = true;
      break;
    case entrePuerta:
    case CierreEsperandoSPC:
    case CierreEsperandoSA:
    case cerradoPuerta:
      Puertas_AbriendoPuerta();
      break;
    default:
      break;
    }
    if (PuertaStop)
      PuertaStop = false;
    if (PuertaCerradaEsperandoStop)
      PuertaCerradaEsperandoStop = false;
    break;
  case puertaCerrando:
    switch (lecturaSeg)
    {
    case cerradoPuerta:
      if (!PuertaCerradaEsperandoStop){
        ESP_SERIAL.println("Puerta Cerrada");
        PuertaCerradaEsperandoStop = true;
      }
      CabinaEnMovimiento = VerificarCabina();
      break;
    case entrePuerta:
    case CierreEsperandoSPC:
    case CierreEsperandoSA:
    case abiertaPuerta:
      Puertas_CerrandoPuerta();
      break;
    default:
      break;
    }
    if (PuertaStop)
      PuertaStop = false;
    if (PuertaAbiertaEsperandoStop)
      PuertaAbiertaEsperandoStop = false;
    break;
  case puertoStop:

    if (PuertaStop)
    {
      ESP_SERIAL.println("Puerta Stop. Esperando por rele");
      PuertaStop = false;
    }
  default:
    break;
  }
  
  
  
  
  
  if ( !CabinaEnMovimiento )delay(40);
  
  
  
  
  //while ( Puertas_leerEstadoPuerta() != puertaAbriendo )
  //{
  //  delay(1);
  //}
  //ESP_SERIAL.println("Abriendo Puerta");
  //while ( Seguridades_leerEstadoPuerta() != abiertaPuerta )
  //{
  //  delay(100);
  //  Puertas_AbriendoPuerta();
  //}
  //ESP_SERIAL.println("Puerta Abierta. Esperando por rele stop");
  //while ( Puertas_leerEstadoPuerta() != puertoStop )
  //{
  //  delay(1);
  //}
  //ESP_SERIAL.println("Puerta Stop. Esperando por rele de cerrar");
  //while ( Puertas_leerEstadoPuerta() != puertaCerrando )
  //{
  //  delay(1);
  //}
  //ESP_SERIAL.println("Cerrando Puerta");
  //while ( Seguridades_leerEstadoPuerta() != cerradoPuerta )
  //{
  //  delay(100);
  //  Puertas_CerrandoPuerta();
  //}
  //ESP_SERIAL.println("Puerta Cerrada. Subiendo ascensor");
  //Ascensor_VerificarPosicion();
  //ESP_SERIAL.println("Llego a piso");
}