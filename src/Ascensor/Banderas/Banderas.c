#include "Banderas.h"
#include <Arduino.h>
#include "../../modules/ModBackend.h"
#include "../../modules/Mod74hc595/Mod74hc595.h"

struct data_ModBackend data_mod_Banderas[4];

uint16_t contadorSecuenciaPiso = 0;
uint8_t contadorBanderas = 0;
uint8_t limiteConteoBanderas = 10;
bool modoConteoBandera = PADPAS;

void Banderas_Init( const struct data_ModBackend *confg, uint8_t elements)
{
    for( uint8_t i = 0; i < elements; i++  )
    {
        data_mod_Banderas[i].posPin = confg[i].posPin;
        data_mod_Banderas[i].estadoPin = confg[i].estadoPin;
    }
    MOD74HC595_setOutput(data_mod_Banderas , elements );
}

uint8_t Banderas_leerBanderas()
{
    uint8_t mod = 0;
    if ( modoConteoBandera ==  PADPAS )
    {
      mod = (uint8_t)(data_mod_Banderas[bitEXD].estadoPin) << 3 | (uint8_t)(data_mod_Banderas[bitPAD_PN].estadoPin) << 2 | (uint8_t)(data_mod_Banderas[bitPAS].estadoPin) << 1| (uint8_t)(data_mod_Banderas[bitEXS].estadoPin);
    }
    else{
      mod = (uint8_t)(data_mod_Banderas[bitEXD].estadoPin) << 2 | (uint8_t)(data_mod_Banderas[bitPAD_PN].estadoPin) << 1 | (uint8_t)(data_mod_Banderas[bitEXS].estadoPin);
    }
    return mod;
}

void IncrementarBandera(uint8_t *PisoActual, uint8_t *TotalPisos)
{
  if (  modoConteoBandera == PADPAS )
  {
    contadorBanderas++;
    if ( contadorBanderas >= limiteConteoBanderas )
    {
      if (  contadorBanderas < 14 ) contadorSecuenciaPiso++;
      
      uint8_t SecAct = pisosSecuenciaPASPAD[14 - contadorSecuenciaPiso];
      if (  contadorSecuenciaPiso == piso_ascensor_y )
      {
        if (  *PisoActual +1 == *TotalPisos )
        {
          contadorSecuenciaPiso = piso_final_x;
        }
        else {
          contadorSecuenciaPiso = piso_ascensor_x;
        }
      }
      else if(contadorSecuenciaPiso == piso_ascensor_cambio  )
      {
        *PisoActual = *PisoActual  +1 ;
      }
      
      data_mod_Banderas[bitEXD].estadoPin = ((SecAct>>3)&0x01);
      data_mod_Banderas[bitPAD_PN].estadoPin = ((SecAct>>2)&0x01);
      data_mod_Banderas[bitPAS].estadoPin = ((SecAct>>1)&0x01);
      data_mod_Banderas[bitEXS].estadoPin = ((SecAct>>0)&0x01);

      contadorBanderas = 0;
    }
  }
}

void DecrementarBandera(uint8_t *PisoActual)
{
  if (  modoConteoBandera == PADPAS )
  {
    contadorBanderas++;
    if ( contadorBanderas >= limiteConteoBanderas )
    {
      if (  contadorBanderas > 0 ) contadorSecuenciaPiso--;
      
      uint8_t SecAct = pisosSecuenciaPASPAD[14 - contadorSecuenciaPiso];
      if (  contadorSecuenciaPiso == piso_ascensor_x )
      {
        if (  *PisoActual - 1 == 0 )
        {
          contadorSecuenciaPiso = piso_base_y;
        }
        else {
          contadorSecuenciaPiso = piso_ascensor_y;
        }
      }
      else if(contadorSecuenciaPiso == piso_ascensor_cambio  )
      {
        *PisoActual = *PisoActual -1 ;
      }
      data_mod_Banderas[bitEXD].estadoPin = ((SecAct>>3)&0x01);
      data_mod_Banderas[bitPAD_PN].estadoPin = ((SecAct>>2)&0x01);
      data_mod_Banderas[bitPAS].estadoPin = ((SecAct>>1)&0x01);
      data_mod_Banderas[bitEXS].estadoPin = ((SecAct>>0)&0x01);

      contadorBanderas = 0;
    }
  }
}