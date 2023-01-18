#include <Arduino.h>
// #include "../.pio/libdeps/Arduino Mega/avr-debugger/avr8-stub/avr8-stub.h"
#include <ArduinoJson.h>
#include "Ascensor/Ascensor.h"
#include "Protocols/SoftSerial/SoftSerial.h"
#include "FirmwareModules/OLEDMod/OLEDMod.h"
#include "FirmwareModules/Mod74hc595/Mod74hc595.h"
#include "FirmwareModules/74HC4067MOD/74HC4067MOD.h"
#include "Ascensor/Puertas/Puertas.h"
#include "Ascensor/Seguridades/Seguridades.h"
#include "Ascensor/Banderas/Banderas.h"


/**
 * Colocar Nuevos Modulos
*/


/**
 * If the moudle used is the ESP8266 
 * add the libraries used to init Web server
 * Add the API for SPIFFSS for Elevator
 * Add API for SPIFFSS
*/
#if defined(ESP8266)
#include "modules/WebServer/WebServer.h"
#include "Ascensor/AscWebServer/AscWebServer.h"
#include "Ascensor/AscSPIFFS/AscSPIFFS.h"
#include "Protocols/SPIFFS/SPIFFS.h"
#endif

#include <Wire.h>

/**
 * There are 2 modes for the simulator
 * 1) ESP_MOD_WIFI => used to set the board as WiFi Module and Master Controller
 * The board will send the notifications to and  interface where the client will be connectted
 * 
*/

// #define ESP_MOD_WIFI
// #define ARD_MOD_SER


/**
 * If we are using an Dev board with not WiFiMidules
 * This is the set where: 
 * 1. Init the Software Serial Module
 * 2. Start the OLED Module
*/
#ifndef ESP_MOD_WIFI
void setup()
{
  /** Init All Modules */
  SoftSerial_IniModules();
  OLED_Init();
  OLED_TestFile();
  MOD74HC595_Init();
  MUX74HC4067_Init();

#if defined(ESP8266)
  WebServer_InitWiFiManager(AscensorWebServer_InitServer);
#endif
  /** As we are using Arduino Noard wtn o WiFI mODULE
   * Let's create the JSON for our Baord Configuration in the flash
   */
  String strConfInit = "{";
  strConfInit += "\"NombrePlaca\": \"Placa1\",";
  strConfInit += "\"Modelo\": \"V1\",";
  strConfInit += "\"ARCH\": {";
  strConfInit += "\"MSA\": {";
  strConfInit += "\"PINNAME\": [\"EXD\", \"PAD_PN\", \"PAS\", \"EXS\", \"FPA\", \"SPC\", \"SA\", \"SM\"],";
  strConfInit += "\"VAL\": [0, 0, 0, 0, 1, 1, 1, 0]";
  strConfInit += "},";
  strConfInit += "\"MS2\": {";
  strConfInit += "\"PINNAME\": [\"BOMB\", \"EMER\", \"Q1\", \"Q2\", \"FOTO\", \"MANT\", \"PTC\", \"AUTAR\"],";
  strConfInit += "\"VAL\": [0, 0, 0, 0, 0,0, 0, 1]";
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
  strConfInit += "\"TOTAL_PISOS\": 14";
  strConfInit += "}";
#ifdef ARD_MOD_SER
  /** if we are connectted to wifi module
   * Let's send a command inidcating the system is active.
   */
#endif

#if defined(ESP8266)
/** Let's connect the ESp to Internet */
  WebServer_InitWiFiManager(AscensorWebServer_InitServer);
  VerificarArchivos(strConfInit, CONFG_FILE);
  strConfInit = SPIFFS_ReadFile(CONFG_FILE);
  SPIFFS_printFiles();
  AscensorWebServer_InitServer();
#endif
  /** Now, will be configured the board and reset its parameters
   * Simulating a initiation of elevator
   */
  SoftSerial_Degub_println("Init Asc:");
  Ascensor_Init(strConfInit);
  Banderas_resetContadorBanderas();
  Seguridades_ActivarSM();
  SoftSerial_Degub_println("Starting firmware");
}

void loop()
{
  // put your main code here, to run repeatedly:
  static bool init = false;// used to verify parameters at the initiation
/**
 * If the module used is ESP8266:
 * the Module will verify if connectted or not
 * If not, will open the WiFi Manager
 * if not will continue with the rest of the code
*/
#if defined(ESP8266)
  static unsigned long tstart = millis();
  static unsigned long tstartWiFi = millis();
  bool WifiDesconectado = false;
  if (!WifiDesconectado)
    AscWebServer_handleClient();/* Function to connect to wifi */
#endif
  /** Read Door and Securities and determinate the movement of the elevator*/
  uint16_t lecturaPuerta = Puertas_leerEstadoPuerta();
  uint16_t lecturaSeg = Seguridades_leerEstadoPuerta();

  static bool PuertaAbiertaEsperandoStop = false;
  static bool PuertaCerradaEsperandoStop = false;
  static bool PuertaStop = false;

  bool CabinaEnMovimiento = false;
  if (!init)
  {
    SoftSerial_Degub_print(F("lecturaPuerta:"));
    SoftSerial_Degub_println(lecturaPuerta, BIN);
    SoftSerial_Degub_print(F("lecturaSeg:"));
    SoftSerial_Degub_println(lecturaSeg, BIN);
    init = true;
  }
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
      SoftSerial_Degub_println("Puerta Abierta.");
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
      if (!PuertaCerradaEsperandoStop)
      {
        SoftSerial_Degub_println("Puerta Cerrada");
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
      SoftSerial_Degub_println("Puerta Stop. Esperando por rele");
      PuertaStop = false;
    }
  default:
    break;
  }
  if (!CabinaEnMovimiento)
  {
#if defined(ESP8266)
    while (millis() - tstart <= 40)
    {
      if (!WifiDesconectado)
        AscWebServer_handleClient();
    }
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    delay(40);
#endif
  }
#if defined(ESP8266)
  if (millis() - tstartWiFi >= 10000 && !WifiDesconectado)
  {
    if (WiFi.status() != WL_CONNECTED && !WifiDesconectado)
    {
      SoftSerial_Degub_println("ESP desconectado de la red. Por favor Reseteelo y vuelva a conectar");
      WifiDesconectado = true;
    }
    tstartWiFi = millis();
  }
  else if (millis() - tstartWiFi >= 1000 && WifiDesconectado)
  {
    if (WiFi.status() == WL_CONNECTED && WifiDesconectado)
    {
      SoftSerial_Degub_println("ESP conectado nuevamente la red");
      WifiDesconectado = false;
    }
    tstartWiFi = millis();
  }

#endif
}

#else
void setup()
{
  SoftSerial_IniModules();
  OLED_Init();
  OLED_MensajeInicial();

#if defined(ESP8266)
  WebServer_InitWiFiManager(AscensorWebServer_InitServer);

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

  VerificarArchivos(strConfInit, "ConfgFile.json");
  strConfInit = SPIFFS_ReadFile("ConfgFile.json");
  SPIFFS_printFiles();
  AscensorWebServer_InitServer();

#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
  while (true)
  {
    delay(1);
  }

#endif

  SoftSerial_Degub_println("Init Mdo");
  delay(3000);
  SoftSerial_Degub_println("Starting firmware");
}

void loop()
{
  // put your main code here, to run repeatedly:
  static unsigned long tstartWiFi = millis();
  bool WifiDesconectado = false;

  if (!WifiDesconectado)
    AscWebServer_handleClient();

  if (millis() - tstartWiFi >= 10000 && !WifiDesconectado)
  {
    if (WiFi.status() != WL_CONNECTED && !WifiDesconectado)
    {
      SoftSerial_Degub_println("ESP desconectado de la red. Por favor Reseteelo y vuelva a conectar");
      WifiDesconectado = true;
    }
    tstartWiFi = millis();
  }
  else if (millis() - tstartWiFi >= 1000 && WifiDesconectado)
  {
    if (WiFi.status() == WL_CONNECTED && WifiDesconectado)
    {
      SoftSerial_Degub_println("ESP conectado nuevamente la red");
      WifiDesconectado = false;
    }
    tstartWiFi = millis();
  }
}

#endif
