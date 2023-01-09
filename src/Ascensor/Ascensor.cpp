#include <Arduino.h>
#include "Ascensor.h"
#include "../modules/ModBackend.h"
#include "../modules/PCF8575/PCF8575Mod.h"
#include "Seguridades/Seguridades.h"
#include "Banderas/Banderas.h"
#include "Alertas/Alertas.h"
#include "Puertas/Puertas.h"
#include "../Protocols/SoftSerial/SoftSerial.h"
#include "../modules/JsonMod/JsonMod.h"
#include "Cabina/Cabina.h"

SoftwareSerial ESP_SERIAL_ASC(ESP_RX, ESP_TX);

int TotalPisos = 14;
int pisoActual = 1;

uint8_t Ascensor_VerificarModuloSegunPosicion(uint8_t PosicionEnPlaca)
{
  uint8_t valRet = 0;
  if (PosicionEnPlaca < device595pos)
    valRet = dev595;
  else if (PosicionEnPlaca < deviceMUX4067pos)
    valRet = dev4067;
  return valRet;
}

/**
 * @brief Ascensor_Init( JsonDocument &JSONObject)
 *
 * 1. Actualizar los parametros de cada uno los modulos que comoponen el ascensor con el argumento JSON
 *
 * @param JSONObject
 * Argumento usado para definir cada unos los bloques de la placa, indicadndo la poscion y la funcion a ejecutar
 *
 *
 */

void Ascensor_Init(String StrJSONObject)
{
  ESP_SERIAL_ASC.begin(BAUD_SERIAL);
  JsonMod_SerialInit();
  //ESP_SERIAL_ASC.println("STR 2:" + StrJSONObject );
  ActualizarModulos(StrJSONObject);
}

/**
 * @brief ActualizarModulos(JsonDocument &JSONObject)
 *
 * 1.Se obtiene el el Modo de conteo de Banderas dentro del JSON (key = "TIPO_CONTEO")
 * 2.Se obtiene la estructura dentro del KEY "ARCH" para ver la configuracion a actual de la placa
 * 3.Se parsea la estructura ARCH de la siguinete forma:
 *  3.1. La ubicacion del PIN dentro de ARCH es su posicion dentro de la placa. Ex: mod1 , pos 7; mod2, pos 4.... Esto se hara usando el nombre del PIN
 *  3.2. Dependiendo la posicion va a ser seleccionado un device Module usado como extensor dentro de la placa(dicha extructura de device Modules depende exclusivamente del diseño de la placa)
 *  3.3. Se debe almacenar por cada pin => el device module(calculado), la posicion dentro de la placa(json), el estado (1 o 0)(json) y si es entrada o salida o bidireccional (nombre del PIN)
 *  3.4. Cada estrucutura se alamacena en un array que guarda la configuracion de un pin en especifico dentro de la placa.
 *  3.5. Habra un array por cada componente del Modulo "Ascensor"
 *  3.6. Al final cada array debe ser una usado dentro de la inicializacion de cada componente del ascensor para asi configruar los pines correspondientes.
 *
 * @param JSONObject
 * Argumento usado para definir cada unos los bloques de la placa, indicadndo la poscion y la funcion a ejecutar
 *
 *
 */

void ActualizarModulos(String StrJSONObject)
{
  //DynamicJsonDocument JSONObject(JSON_Buffer);
  ////ESP_SERIAL_ASC.println("STR 3:" + StrJSONObject );
  //if (!jsonMod_verificarJson(StrJSONObject, JSONObject))
  //{
  //  ESP_SERIAL_ASC.println("Eror1");
  //  while (true)
  //  {
  //    delay(1);
  //  }
  //}

  String CongfPinsStr[24] = {"EXD", "PAD_PN", "PAS", "EXS", "FPA", "SPC", "SA", "SM", "BOMB", "EMER", "Q1", "Q2", "FOTO", "MANT", "PTC", "AUTAR", "RSUB", "RBAJ", "RAV", "RBV", "RABR", "RCER", "VENT", "PATIN"}; //;
  //String Modff[NUM_TOTAL_MODULOS] = {"MS1", "MS2", "MSA", "ME1", "MEA"};
  enum internalOrderPins
  {
    posBand = 4,
    posSeg = 8,
    posAl = 16,
    posPuertas = 18
  };
  char TIPO_CONTEO_C[20];
  char *titlePart[1] = { "TIPO_CONTEO" };
  JsonMod_FilterChar( StrJSONObject, TIPO_CONTEO_C , titlePart, 1 );
  String TIPO_CONTEO = String(TIPO_CONTEO_C);
  ESP_SERIAL_ASC.println("TIPO_CONTEO: " + TIPO_CONTEO);
  int TOTAL_PISOS;
  char *titlePart2[1] = { "TOTAL_PISOS" };
  JsonMod_FilterInt( StrJSONObject, &TOTAL_PISOS, titlePart2, 1 );
  uint8_t modoConteoBandera = strcmp( TIPO_CONTEO_C , "PADPAS" ) == 0  ? PADPAS : PN;

  uint8_t JSON_TOTAL_PISOS = TOTAL_PISOS;
  TotalPisos = JSON_TOTAL_PISOS;

  //JsonObject EstructuraV = JSONObject["ARCH"];

  struct data_ModBackend data_mod_Band[4];
  struct data_ModBackend data_mod_Seguridades[4];
  struct data_ModBackend data_mod_Alertas[8];
  struct data_ModBackend data_mod_Puertas[2];
  struct data_ModBackend data_mod_Cabinas[4];

  // struct data_ModBackend data_mod_PCF[16];
  // uint8_t countPCF = 0;
  const int  TOTAL_IO_MODULES_BOARD_CONFIG = 5;
  const int TOTAL_PINS_BOARD_CONFIG = 24;
  char* Modff[TOTAL_IO_MODULES_BOARD_CONFIG] = {"MS1", "MS2", "MSA", "ME1", "MEA"};
  uint8_t EspacioModulos[TOTAL_IO_MODULES_BOARD_CONFIG] = {8,8,8,8,8};


  uint16_t counterPos = 0;
  ESP_SERIAL_ASC.println("Start system");
  for (uint8_t i = 0; i < TOTAL_IO_MODULES_BOARD_CONFIG; i++)
  {
    
    
    char *titlePart4[3] = { "ARCH",Modff[i], "PINNAME" };
    char PINNAME[8][10];
    JsonMod_FilterCharArray( StrJSONObject,  &PINNAME[0][0], 10, titlePart4, 3 );
    //ESP_SERIAL_ASC.println("ARCH" +  String(Modff[i]) +"PINNAME: ");
    //for (size_t i = 0; i < 8; i++)
    //{
    //  ESP_SERIAL_ASC.println(PINNAME[i]);
    //}

    char *titlePart5[3] = { "ARCH", Modff[i], "VAL" };
    uint8_t Values[8];
    JsonMod_FilterIntArray( StrJSONObject,  Values, titlePart5, 3 );
    //ESP_SERIAL_ASC.println("ARCH" +  String(Modff[i]) +"PINNAME: ");
    //for (size_t i = 0; i < 8; i++)
    //{
    //  ESP_SERIAL_ASC.println(Values[i]);
    //}

    for (uint8_t j = 0; j < EspacioModulos[i]; j++)
    {
      char* pinameStr = PINNAME[j] ;
      //strcpy( pinameStr, PINNAME[j] );
      //ESP_SERIAL_ASC.println("pinameStr:" + String(pinameStr)  );
      if (strcmp(pinameStr , "" ) != 0)
      {
        for (uint8_t k = 0; k < TOTAL_PINS_BOARD_CONFIG ; k++)
        {
          if (  String(CongfPinsStr[k]) == String(pinameStr  ) 
            &&  String(CongfPinsStr[k]) != "VENT"
            &&  String(CongfPinsStr[k]) != "PATIN" /*strcmp( CongfPinsStr[k] ,pinameStr ) == 0*/ )
          {
            uint8_t pinameVal = Values[j];
            //ESP_SERIAL_ASC.println("pinameVal:" + String(pinameVal)  );
            uint8_t PosicionEnPlaca = counterPos;
            struct data_ModBackend prov_data_mod;
            
            if (k < 4)
            {
              data_mod_Band[k].device = Ascensor_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Band[k].posPin = PosicionEnPlaca;
              //strcpy( data_mod_Band[k].nombrePin, pinameStr );
              data_mod_Band[k].estadoPin= pinameVal >0 ;
              //data_mod_Band[k]. = CongfPinsStr[k];
              prov_data_mod = data_mod_Band[k];
            }
            else if (k < 8 && k >= 4)
            {
              data_mod_Seguridades[k - posBand].device = Ascensor_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Seguridades[k - posBand].posPin = PosicionEnPlaca;
              //strcpy( data_mod_Seguridades[k - posBand].nombrePin, pinameStr );
              //data_mod_Seguridades[k - posBand].nombrePin = CongfPinsStr[k];
              data_mod_Seguridades[k - posBand].estadoPin= pinameVal >0 ;
              //data_mod_Seguridades[k].available = false;
              prov_data_mod = data_mod_Seguridades[k - posBand];
            }
            else if (k < 16 && k >= 8)
            {
              data_mod_Alertas[k - posSeg].device = Ascensor_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Alertas[k - posSeg].posPin = PosicionEnPlaca;
              //strcpy( data_mod_Alertas[k - posSeg].nombrePin, pinameStr );
              //data_mod_Alertas[k - posSeg].nombrePin = CongfPinsStr[k];
              data_mod_Alertas[k - posSeg].estadoPin= pinameVal >0 ;
              //data_mod_Alertas[k - posSeg].available = false;
              prov_data_mod = data_mod_Alertas[k - posSeg];
            }
            else if (k < 22 && k >= 20)
            {
              data_mod_Puertas[k - 20].device = Ascensor_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Puertas[k - 20].posPin = PosicionEnPlaca;
              //strcpy( data_mod_Puertas[k - 20].nombrePin, pinameStr );
              //data_mod_Puertas[k - 20].nombrePin = CongfPinsStr[k];
              data_mod_Puertas[k - 20].estadoPin= pinameVal >0 ;
              //data_mod_Puertas[k - 20].available = false;
              prov_data_mod = data_mod_Puertas[k - 20];
            }
            else if (k < 20 && k >= 16)
            {
              data_mod_Cabinas[k - 16].device = Ascensor_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Cabinas[k - 16].posPin = PosicionEnPlaca;
              data_mod_Cabinas[k - 16].estadoPin= pinameVal >0 ;
              //strcpy( data_mod_Cabinas[k - 16].nombrePin, pinameStr );
              //data_mod_Cabinas[k - 16].nombrePin = CongfPinsStr[k];
              //data_mod_Cabinas[k - 16].available = false;
              prov_data_mod = data_mod_Cabinas[k - 16];
            }
            //ESP_SERIAL_ASC.print( F("K: "));
            //ESP_SERIAL_ASC.print( k);
            //ESP_SERIAL_ASC.print( F(" , "));
            //ESP_SERIAL_ASC.print( F("PosicionPlaca: "));
            //ESP_SERIAL_ASC.print(String( prov_data_mod.posPin ));
            //ESP_SERIAL_ASC.print(F(" , NombrePin: "));
            //ESP_SERIAL_ASC.print( pinameStr   );
            //String deviceName = ( prov_data_mod.device == dev595 )?"595":"MUXBID";
            //ESP_SERIAL_ASC.print( F("Device:") );
            //ESP_SERIAL_ASC.print( deviceName );
            //ESP_SERIAL_ASC.print(F(", Pos:") );
            //ESP_SERIAL_ASC.print(String(  prov_data_mod.posPin) );
            //deviceName = ( prov_data_mod.estadoPin )?"ON":"OFF";
            //ESP_SERIAL_ASC.print(F(", Estado:"));
            //ESP_SERIAL_ASC.println( deviceName  );

            break;
          }
          
        }
      }
      counterPos++;
    }
  }
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
  Backend_ResetModules();
  // PCF_Configuration( data_mod_PCF , countPCF );
  Seguridades_ApagarSM();
  delay(100);
  Banderas_Init(data_mod_Band, 4, modoConteoBandera);
  Seguridades_Init(data_mod_Seguridades, 4);
  Alertas_Init(data_mod_Alertas, 8);
  Puertas_Init(data_mod_Puertas, 2);
  Cabinas_Init(data_mod_Cabinas, 4);
}

bool VerificarCabina()
{
  static uint8_t lecturaPuertaAct = 0;
  static bool reateardoBaja = true;
  //lecturaPuertaAct = Cabina_leerEstadoCabina();
  //reateardoBaja = lecturaPuertaAct == cabinaSubiendoEnBaja || lecturaPuertaAct == cabinaBajandoEnBaja;

  if (Cabina_leerEstadoCabina() != cabinaDetenida)
  {
    if (Cabina_leerEstadoCabina() == cabinaSubiendoEnAlta || Cabina_leerEstadoCabina() == cabinaSubiendoEnBaja || Cabina_leerEstadoCabina() == cabinaBajandoEnAlta || Cabina_leerEstadoCabina() == cabinaBajandoEnBaja)
    {
      if (Cabina_leerEstadoCabina() == cabinaSubiendoEnAlta || Cabina_leerEstadoCabina() == cabinaSubiendoEnBaja)
      {
        IncrementarBandera(&pisoActual, &TotalPisos);
        if (Cabina_leerEstadoCabina() == cabinaSubiendoEnAlta && lecturaPuertaAct != cabinaSubiendoEnAlta)
        {
          lecturaPuertaAct = cabinaSubiendoEnAlta;
          ESP_SERIAL_ASC.println("Cabina Subiendo en Alta");
          reateardoBaja = false;
        }
        else if (Cabina_leerEstadoCabina() == cabinaSubiendoEnBaja && lecturaPuertaAct != cabinaSubiendoEnBaja)
        {
          lecturaPuertaAct = cabinaSubiendoEnBaja;
          ESP_SERIAL_ASC.println("Cabina Subiendo en baja");
          reateardoBaja = true;
        }
      }
      else if (Cabina_leerEstadoCabina() == cabinaBajandoEnAlta || Cabina_leerEstadoCabina() == cabinaBajandoEnBaja)
      {
        DecrementarBandera(&pisoActual);
        if (Cabina_leerEstadoCabina() == cabinaBajandoEnAlta && lecturaPuertaAct != cabinaBajandoEnAlta)
        {
          lecturaPuertaAct = cabinaBajandoEnAlta;
          ESP_SERIAL_ASC.println("Cabina Bajando en Alta");
          reateardoBaja = false;
        }
        else if (Cabina_leerEstadoCabina() == cabinaBajandoEnBaja && lecturaPuertaAct != cabinaBajandoEnBaja)
        {
          lecturaPuertaAct = cabinaBajandoEnBaja;
          ESP_SERIAL_ASC.println("Cabina Bajando en baja");
          reateardoBaja = true;
        }
      }
      reateardoBaja ? delay(DELAY_BV) : delay(DELAY_AV);
      return true;
    }
    return false;
  }
  return false;
}