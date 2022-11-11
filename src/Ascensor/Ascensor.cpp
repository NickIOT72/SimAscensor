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

int TotalPisos = 8;
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
  ESP_SERIAL_ASC.begin(9600);
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
  DynamicJsonDocument JSONObject(JSON_Buffer);
  if (!jsonMod_verificarJson(StrJSONObject, JSONObject))
  {
    ESP_SERIAL_ASC.println("Eror1");
    while (true)
    {
      delay(1);
    }
  }

  String CongfPinsStr[24] = {"EXD", "PAD_PN", "PAS", "EXS", "FPA", "SPC", "SA", "SM", "BOMB", "EMER", "Q1", "Q2", "FOTO", "MANT", "PTC", "AUTAR", "RSUB", "RBAJ", "RAV", "RBV", "RABR", "RCER", "VENT", "PATIN"}; //;
  String Modff[NUM_TOTAL_MODULOS] = {"MS1", "MS2", "MSA", "ME1", "MEA"};
  enum internalOrderPins
  {
    posBand = 4,
    posSeg = 8,
    posAl = 16,
    posPuertas = 18
  };
  String TIPO_CONTEO = JSONObject["TIPO_CONTEO"];
  uint8_t modoConteoBandera = TIPO_CONTEO == "PADPAS" ? PADPAS : PN;
  uint8_t JSON_TOTAL_PISOS = JSONObject["TOTAL_PISOS"];
  TotalPisos = JSON_TOTAL_PISOS;

  JsonObject EstructuraV = JSONObject["ARCH"];

  struct data_ModBackend data_mod_Band[4];
  struct data_ModBackend data_mod_Seguridades[4];
  struct data_ModBackend data_mod_Alertas[8];
  struct data_ModBackend data_mod_Puertas[2];
  struct data_ModBackend data_mod_Cabinas[4];

  // struct data_ModBackend data_mod_PCF[16];
  // uint8_t countPCF = 0;

  ESP_SERIAL_ASC.println("Start system");
  for (uint8_t i = 0; i < NUM_TOTAL_MODULOS; i++)
  {
    JsonArray ms1Vi = EstructuraV[Modff[i]]["PINNAME"];
    String ms1V[NUM_PIN_MODULO] = {ms1Vi[0], ms1Vi[1], ms1Vi[2], ms1Vi[3], ms1Vi[4], ms1Vi[5], ms1Vi[6], ms1Vi[7]};

    JsonArray ms1Vvi = EstructuraV[Modff[i]]["VAL"];
    uint8_t ms1Vv[NUM_PIN_MODULO] = {ms1Vvi[0], ms1Vvi[1], ms1Vvi[2], ms1Vvi[3], ms1Vvi[4], ms1Vvi[5], ms1Vvi[6], ms1Vvi[7]};

    for (uint8_t j = 0; j < NUM_PIN_MODULO; j++)
    {
      if (ms1V[j] != "")
      {
        for (uint8_t k = 0; k < NUM_IO_TOTAL - 2; k++)
        {
          if (CongfPinsStr[k] == ms1V[j])
          {
            uint8_t PosicionEnPlaca = i * NUM_PIN_MODULO + j;
            // struct data_ModBackend data_mod_prov = {0};
            if (k < 4)
            {
              data_mod_Band[k].device = Ascensor_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Band[k].posPin = PosicionEnPlaca;
              data_mod_Band[k].estadoPin = ms1Vv[j] > 0;
              data_mod_Band[k].modIO = OUTPUT;
            }
            else if (k < 8 && k >= 4)
            {
              data_mod_Seguridades[k - posBand].device = Ascensor_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Seguridades[k - posBand].posPin = PosicionEnPlaca;
              data_mod_Seguridades[k - posBand].estadoPin = ms1Vv[j] > 0;
              data_mod_Seguridades[k - posBand].modIO = OUTPUT;
            }
            else if (k < 16 && k >= 8)
            {
              data_mod_Alertas[k - posSeg].device = Ascensor_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Alertas[k - posSeg].posPin = PosicionEnPlaca;
              data_mod_Alertas[k - posSeg].estadoPin = ms1Vv[j] > 0;
              data_mod_Alertas[k - posSeg].modIO = OUTPUT;
            }
            else if (k < 22 && k >= 20)
            {
              data_mod_Puertas[k - 20].device = Ascensor_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Puertas[k - 20].posPin = PosicionEnPlaca;
              data_mod_Puertas[k - 20].estadoPin = ms1Vv[j] > 0;
              data_mod_Puertas[k - 20].modIO = INPUT;
            }
            else if (k < 20 && k >= 16)
            {
              data_mod_Cabinas[k - 16].device = Ascensor_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Cabinas[k - 16].posPin = PosicionEnPlaca;
              data_mod_Cabinas[k - 16].estadoPin = ms1Vv[j] > 0;
              data_mod_Cabinas[k - 16].modIO = INPUT;
            }
            /*if ( Ascensor_VerificarModuloSegunPosicion(PosicionEnPlaca) == devPCF )
            {
              data_mod_PCF[countPCF] = data_mod_prov;
              countPCF++;
            }*/
            // ESP_SERIAL_ASC.print("MOD: " + ms1V[j]  + " => ");
            // String deviceName = (data_mod_prov.device == dev595)?"595":"PCF";
            // ESP_SERIAL_ASC.print("Device:" + deviceName );
            // ESP_SERIAL_ASC.print(", Pos:" + String( data_mod_prov.posPin ) );
            // deviceName = (data_mod_prov.estadoPin)?"ON":"OFF";
            // ESP_SERIAL_ASC.print(", Estado:" + deviceName  );
            // deviceName = (data_mod_prov.modIO == INPUT)?"IN":"OUT";
            // ESP_SERIAL_ASC.println(", IO:" + deviceName  );
            break;
          }
        }
      }
    }
  }
  Backend_ResetModules();
  // PCF_Configuration( data_mod_PCF , countPCF );
  Banderas_Init(data_mod_Band, 4, modoConteoBandera);
  Seguridades_Init(data_mod_Seguridades, 4);
  Alertas_Init(data_mod_Alertas, 8);
  Puertas_Init(data_mod_Puertas, 2);
  Cabinas_Init(data_mod_Cabinas, 4);
  jsonMod_liberarDinMemJsonDoc(JSONObject);
}

void Ascensor_VerificarPosicion()
{
  uint8_t lecturaPuertaAct = 0;
  bool reateardoBaja = true;
  while (!(lecturaPuertaAct == cabinaSubiendoEnAlta || lecturaPuertaAct == cabinaSubiendoEnBaja || lecturaPuertaAct == cabinaBajandoEnAlta || lecturaPuertaAct == cabinaBajandoEnBaja) && Puertas_leerEstadoPuerta() == puertaCerrando)
  {
    lecturaPuertaAct = Cabina_leerEstadoCabina();
    delay(1);
  }
  if (Puertas_leerEstadoPuerta() != puertaCerrando)
    return;
  ESP_SERIAL_ASC.println("Cabina en MOviemiento");
  lecturaPuertaAct = Cabina_leerEstadoCabina();
  reateardoBaja = lecturaPuertaAct == cabinaSubiendoEnBaja || lecturaPuertaAct == cabinaBajandoEnBaja;

  while (Puertas_leerEstadoPuerta() == puertaCerrando)
  {
    while (Cabina_leerEstadoCabina() != cabinaDetenida)
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
      }
    }
  }
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