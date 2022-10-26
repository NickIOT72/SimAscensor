#include <Arduino.h>
#include "Ascensor.h"
#include "../modules/ModBackend.h"
#include "Seguridades/Seguridades.h"
#include "Banderas/Banderas.h"
#include "Alertas/Alertas.h"
#include "Puertas/Puertas.h"

void Ascensor_Init( JsonDocument &JSONObject)
{
    ActualizarModulos( JSONObject);
}

void ActualizarModulos(JsonDocument &JSONObject)
{
  String CongfPinsStr[24] = {"EXD", "PAD_PN", "PAS", "EXS", "FPA", "SPC", "SA", "SM", "BOMB", "EMER", "Q1", "Q2", "FOTO", "MANT", "PTC", "AUTAR","RSUB", "RBAJ", "RAV", "RBV", "RABR", "RCER", "VENT", "PATIN"};//;
  String Modff[NUM_TOTAL_MODULOS] = {"MS1", "MS2", "MSA","ME1","MEA"};
//DynamicJsonDocument JSONObject(JSON_Buffer);
  //if ( !verificarJson( Str,  JSONObject) ) return;
  String TIPO_CONTEO = JSONObject["TIPO_CONTEO"];
  bool modoConteoBandera = TIPO_CONTEO == "PADPAS"?PADPAS:PN;

  JsonObject EstructuraV = JSONObject["ARCH"];

  struct data_ModBackend data_mod_Band[4]; 
  struct data_ModBackend data_mod_Seguridades[4];
  struct data_ModBackend data_mod_Alertas[8];
  struct data_ModBackend data_mod_Puertas[2];

  for (uint8_t i = 0; i < NUM_TOTAL_MODULOS; i++)
  {
    JsonArray ms1Vi = EstructuraV[Modff[i]]["PINNAME"];
    String ms1V[NUM_PIN_MODULO] = {ms1Vi[0], ms1Vi[1], ms1Vi[2], ms1Vi[3], ms1Vi[4], ms1Vi[5], ms1Vi[6], ms1Vi[7]};

    JsonArray ms1Vvi = EstructuraV[Modff[i]]["VAL"];
    uint8_t ms1Vv[NUM_PIN_MODULO] = {ms1Vvi[0], ms1Vvi[1], ms1Vvi[2], ms1Vvi[3], ms1Vvi[4], ms1Vvi[5], ms1Vvi[6], ms1Vvi[7]};
    

    for (uint8_t j = 0; j < 8 ;  j++ )
    {
      if ( ms1V[i] != ""  )
      {
        for( uint8_t k = 0; k < 24; k++ )
        {
          if ( CongfPinsStr[k] ==  ms1V[i] )
          {
            uint8_t PosicionEnPlaca = NUM_TOTAL_MODULOS*i + j;
            if( k < 4 ){
              data_mod_Band[k].device = PosicionEnPlaca >= 24?devPCF:dev595;
              data_mod_Band[k].posPin = PosicionEnPlaca;
              data_mod_Band[k].estadoPin = ms1Vv[i];
              data_mod_Band[k].modIO = OUTPUT;
            }
            else if ( k < 8 ){
              data_mod_Seguridades[k-4].device = PosicionEnPlaca >= 24?devPCF:dev595;
              data_mod_Seguridades[k-4].posPin = PosicionEnPlaca;
              data_mod_Seguridades[k-4].estadoPin = ms1Vv[i];
              data_mod_Seguridades[k-4].modIO = OUTPUT;
            }
            else if ( k < 16 ){
              data_mod_Alertas[k-8].device = PosicionEnPlaca >= 24?devPCF:dev595;
              data_mod_Alertas[k-8].posPin = PosicionEnPlaca;
              data_mod_Alertas[k-8].estadoPin = ms1Vv[i];
              data_mod_Alertas[k-8].modIO = OUTPUT;
            }
            else if ( k < 18 ){
              data_mod_Puertas[k-16].device = PosicionEnPlaca >= 24?devPCF:dev595;
              data_mod_Puertas[k-16].posPin = PosicionEnPlaca;
              data_mod_Puertas[k-16].estadoPin = ms1Vv[i];
              data_mod_Puertas[k-16].modIO = INPUT;
            }
            break;
          }
        }


      }
    }
   
    
  } 
  Banderas_Init( data_mod_Band ,  4);
  Seguridades_Init( data_mod_Band, 4 );
  Alertas_Init(  data_mod_Alertas , 8);
  Puertas_Init(data_mod_Puertas ,  2 );

}