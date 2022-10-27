#include "Banderas.h"
#include "../../modules/ModBackend.h"

struct data_ModBackend data_mod_Banderas[4];

uint16_t contadorSecuenciaPiso = 0;
uint8_t contadorBanderas = 0;
uint8_t limiteConteoBanderas = 10;
uint8_t modoConteoBandera = PADPAS;


/**
 * @brief Resetar los struct del odulo banderas
 * 
 */

void Banderas_resetBanderas()
{
  for( uint8_t i = 0; i < 4; i++  )
  {
    data_mod_Banderas[i]= {0};
  }
}

void Banderas_ActualizarEstadoBanderas( uint8_t SecAct){
  data_mod_Banderas[bitEXD].estadoPin = ((SecAct>>3)&0x01);
  data_mod_Banderas[bitPAD_PN].estadoPin = ((SecAct>>2)&0x01);
  data_mod_Banderas[bitPAS].estadoPin = ((SecAct>>1)&0x01);
  data_mod_Banderas[bitEXS].estadoPin = ((SecAct>>0)&0x01);
  Backend_setOutputDevice(data_mod_Banderas , 4 );
  contadorBanderas = 0;
}

/**
 * @brief Se inicializa el modulo de banderas
 * 1. se limpia el array data_mod_Banderas;
 * 2. se configruar el modo de conteo de banderas y el strut backend de cada pin
 * 3. se configura el modulo de banderas usando la funcion del backend
 * 
 * @param confg 
 * @param elements 
 * @param modoConteoBanderas2 
 */

void Banderas_Init( const struct data_ModBackend *confg, uint8_t elements, uint8_t modoConteoBanderas2)
{
    Banderas_resetBanderas();
    modoConteoBandera = modoConteoBanderas2;
    for( uint8_t i = 0; i < elements; i++  )
    {
      data_mod_Banderas[i].device = confg[i].device;
      data_mod_Banderas[i].modIO = confg[i].modIO;
      data_mod_Banderas[i].posPin = confg[i].posPin;
      data_mod_Banderas[i].estadoPin = ( i == bitPAS && modoConteoBandera == PN )?false:confg[i].estadoPin;
    }
    Backend_setOutputDevice(data_mod_Banderas , elements );
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
      
      Banderas_ActualizarEstadoBanderas( SecAct);
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
      Banderas_ActualizarEstadoBanderas( SecAct);
    }
  }
}