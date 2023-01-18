#include "Banderas.h"
#include "../../DataModules/ModBackend/ModBackend.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"
#include "../../FirmwareModules/BoardArch.h"

struct data_PinBackend data_mod_Banderas[4];

uint16_t contadorSecuenciaPiso = 0;
uint8_t contadorBanderas = 0;
uint8_t limiteConteoBanderas[15] = { 2,10,85,100,5,85,10,5,10,100,5,185,85,10,2 };
uint8_t modoConteoBandera = PADPAS;

uint8_t contadorSecuenciaAnterior = 0;
/**
 * @brief Resetar los struct del odulo banderas
 * 
 */

void Banderas_resetBanderas()
{
  struct data_PinBackend prov_d;
  for( uint8_t i = 0; i < 4; i++  )
  {
    data_mod_Banderas[i]= prov_d;
  }
}

void Banderas_ActualizarEstadoBanderas( uint8_t SecAct){
  
  data_mod_Banderas[bitEXD].EstadoPin = ((SecAct>>3)&0x01);
  data_mod_Banderas[bitPAD_PN].EstadoPin  = ((SecAct>>2)&0x01);
  data_mod_Banderas[bitPAS].EstadoPin  = ((SecAct>>1)&0x01);
  data_mod_Banderas[bitEXS].EstadoPin  = ((SecAct>>0)&0x01);
  Board_setMultipleOutputDevice(data_mod_Banderas , 4 );
  contadorBanderas = 0;
  SoftSerial_Degub_print("EXD,PAD,PAS,EXS:");
  SoftSerial_Degub_println(SecAct , BIN);
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

void Banderas_Init( const struct data_PinBackend *confg, uint8_t elements, uint8_t modoConteoBanderas2)
{
    Banderas_resetBanderas();
    modoConteoBandera = modoConteoBanderas2;
    for( uint8_t i = 0; i < elements; i++  )
    {
      data_mod_Banderas[i] = confg[i];
      data_mod_Banderas[i].EstadoPin  = ( i == bitPAS && modoConteoBandera == PN )?false:confg[i].EstadoPin ;
    }
    Board_setMultipleOutputDevice(data_mod_Banderas , elements );
    for(uint8_t i = 0; i < CANT_POS_ASC; i++)
    {
      if( Banderas_leerBanderas() == pisosSecuenciaPASPAD[i] )
      {
        contadorSecuenciaPiso = i;
        SoftSerial_Degub_print("Band: ");
        SoftSerial_Degub_print(Banderas_leerBanderas() , BIN);
        SoftSerial_Degub_print("POS Elevatpr: ");
        SoftSerial_Degub_println(contadorSecuenciaPiso);
        break;
      }
    }
    
}

uint8_t Banderas_leerBanderas()
{
    uint8_t mod = 0;
    if ( modoConteoBandera ==  PADPAS )
    {
      mod = (uint8_t)(data_mod_Banderas[bitEXD].EstadoPin ) << 3 | (uint8_t)(data_mod_Banderas[bitPAD_PN].EstadoPin ) << 2 | (uint8_t)(data_mod_Banderas[bitPAS].EstadoPin ) << 1| (uint8_t)(data_mod_Banderas[bitEXS].EstadoPin );
    }
    else{
      mod = (uint8_t)(data_mod_Banderas[bitEXD].EstadoPin ) << 2 | (uint8_t)(data_mod_Banderas[bitPAD_PN].EstadoPin ) << 1 | (uint8_t)(data_mod_Banderas[bitEXS].EstadoPin );
    }
    return mod;
}

void Banderas_resetContadorBanderas()
{
  contadorBanderas = 0;
}

bool llegando= false;
bool direccion= false;

void IncrementarBandera(int *PisoActual, int *TotalPisos)
{
  bool pisodelay = false;
  if(contadorSecuenciaPiso == CANT_POS_ASC -1 && *PisoActual ==  *TotalPisos ) return;
  if (  modoConteoBandera == PADPAS )
  {
    if( !direccion &&  contadorBanderas > 0 ) { contadorBanderas--; return;}
    if( !direccion ) { contadorSecuenciaPiso = contadorSecuenciaAnterior ; contadorBanderas = limiteConteoBanderas[contadorSecuenciaPiso]; direccion=true;}
    contadorBanderas++;
    if ( contadorBanderas >= limiteConteoBanderas[contadorSecuenciaPiso] )
    {
      uint8_t SecAct = pisosSecuenciaPASPAD[contadorSecuenciaPiso];
      Banderas_ActualizarEstadoBanderas( SecAct);
      contadorSecuenciaAnterior = contadorSecuenciaPiso;
      if ( contadorSecuenciaPiso == piso_base_y )
      {
        SoftSerial_Degub_println("Saliendo de referencia");
        contadorSecuenciaPiso++;
        llegando = true;
      }
      else if (  contadorSecuenciaPiso == piso_ascensor_y  )
      {
        if (  *PisoActual + 1 == *TotalPisos )
        {
          contadorSecuenciaPiso = piso_final_x - 1;
          SoftSerial_Degub_println("llegando a piso final");
          llegando = true;
        }
        else {
          contadorSecuenciaPiso = piso_ascensor_x;
          SoftSerial_Degub_println("llegando a piso seguiente");
          llegando = true;
        }
      }
      else if(contadorSecuenciaPiso == piso_ascensor_cambio  )
      {
        if(llegando){ *PisoActual = *PisoActual  +1 ; llegando = false; }  
        SoftSerial_Degub_print("Piso Actual:");
        SoftSerial_Degub_println(*PisoActual);
        SoftSerial_Degub_print("Piso Final:");
        SoftSerial_Degub_println(*TotalPisos);
        contadorSecuenciaPiso++;
        pisodelay = true;
      }
      else if(contadorSecuenciaPiso == piso_final_y  )
      {
        SoftSerial_Degub_print("llego a Piso final");
        llegando = false;
        *PisoActual = *TotalPisos;
        pisodelay = true;
      }
      else{
        if (  contadorSecuenciaPiso < CANT_POS_ASC -1) contadorSecuenciaPiso++;
      }
      //if( pisodelay )delay(5000);
      
      
    }
  }
}

void DecrementarBandera(int *PisoActual)
{
  bool pisodelay = false;
  if(contadorSecuenciaPiso == 0 && *PisoActual == 0) return;
  if (  modoConteoBandera == PADPAS )
  {
    if( direccion &&  contadorBanderas > 0 ) { contadorBanderas--; return;}
    if( direccion ) { contadorSecuenciaPiso = contadorSecuenciaAnterior ; contadorBanderas = limiteConteoBanderas[contadorSecuenciaPiso]; direccion=false;}
    contadorBanderas++;
    if ( contadorBanderas >= limiteConteoBanderas[contadorSecuenciaPiso] )
    {
      uint8_t SecAct = pisosSecuenciaPASPAD[contadorSecuenciaPiso];
      Banderas_ActualizarEstadoBanderas( SecAct);
      contadorSecuenciaAnterior = contadorSecuenciaPiso;
      if ( contadorSecuenciaPiso == piso_final_x )
      {
        contadorSecuenciaPiso = piso_ascensor_y + 1;
        SoftSerial_Degub_println("Saliendo de piso final");
        llegando = true;
      }
      else if (  contadorSecuenciaPiso == piso_ascensor_x   )
      {
        if (  *PisoActual - 1 == 0 )
        {
          contadorSecuenciaPiso = piso_base_y;
          SoftSerial_Degub_println("llegando a piso referencia");
          llegando = true;
        }
        else {
          contadorSecuenciaPiso = piso_ascensor_y;
          SoftSerial_Degub_println("llegando a piso seguiente");
          llegando = true;
        }
      }
      else if(contadorSecuenciaPiso == piso_ascensor_cambio  )
      {
        if(llegando){ *PisoActual = *PisoActual  -1 ; llegando = false; }  
        SoftSerial_Degub_print("Piso Actual:");
        SoftSerial_Degub_println(*PisoActual);
        contadorSecuenciaPiso--;
        pisodelay = true;
      }
      else if(contadorSecuenciaPiso == piso_base_x  )
      {
        SoftSerial_Degub_print("llego a refrencia");
        *PisoActual = 0;
        llegando = false;
        pisodelay = true;
      }
      else{
        if (  contadorSecuenciaPiso > 0 ) contadorSecuenciaPiso--;
      }
      //if( pisodelay )delay(5000);
      
      
    }
  }
}