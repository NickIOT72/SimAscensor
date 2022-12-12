#include "Seguridades.h"
#include "../../modules/Mod74hc595/Mod74hc595.h"

struct data_ModBackend data_mod_Seguridades[4];


/**
 * @brief Resetar los struct del odulo seguridades
 * 
 */

void Seguridades_resetSeguridades()
{
  for( uint8_t i = 0; i < 4; i++  )
  {
    data_mod_Seguridades[i]= {0};
  }
}

/**
 * @brief Se inicializa el modulo de Seguridades
 * 1. se limpia el array data_mod_Banderas;
 * 2. se configruar el modo de conteo de banderas y el strut backend de cada pin
 * 3. se configura el modulo de banderas usando la funcion del backend
 * 
 * @param confg 
 * @param elements 
 */
void Seguridades_Init( const struct data_ModBackend *confg, uint8_t elements)
{
    Seguridades_resetSeguridades();
    for( uint8_t i = 0; i < elements; i++  )
    {
        data_mod_Seguridades[i].device = confg[i].device;
        data_mod_Seguridades[i].modIO = confg[i].modIO;
        data_mod_Seguridades[i].posPin = confg[i].posPin;
        data_mod_Seguridades[i].estadoPin = confg[i].estadoPin;
    }
    MOD74HC595_setOutput(data_mod_Seguridades , elements );
}


uint8_t Seguridades_leerEstadoPuerta()
{
    uint8_t estadoPuerta =  (uint8_t)(data_mod_Seguridades[bitFPA].estadoPin) << 2 | (uint8_t)(data_mod_Seguridades[bitSPC].estadoPin) << 1 | (uint8_t)(data_mod_Seguridades[bitSA].estadoPin);
    return estadoPuerta;
}

void Seguridades_ActivarSM()
{
    data_mod_Seguridades[bitSM].estadoPin = false;
    struct data_ModBackend data_mod_Seguridades_SM[]={data_mod_Seguridades[bitSM]};
    MOD74HC595_setOutput(data_mod_Seguridades_SM , 1 );
}

void Seguridades_ApagarSM()
{
    data_mod_Seguridades[bitSM].estadoPin = true;
    struct data_ModBackend data_mod_Seguridades_SM[]={data_mod_Seguridades[bitSM]};
    MOD74HC595_setOutput(data_mod_Seguridades_SM , 1 );
}

void Seguridades_actualizarPuerta( uint8_t LecEstadoPuerta )
{
    data_mod_Seguridades[bitFPA].estadoPin = (((LecEstadoPuerta >> 2)&(0X01)) > 0);
    data_mod_Seguridades[bitSPC].estadoPin = (((LecEstadoPuerta >> 1)&(0X01))> 0);
    data_mod_Seguridades[bitSA].estadoPin = (((LecEstadoPuerta)&(0X01))> 0);
    
    struct data_ModBackend data_mod_Seguridades_SM[]={data_mod_Seguridades[bitFPA], data_mod_Seguridades[bitSPC],  data_mod_Seguridades[bitSA]  };
    MOD74HC595_setOutput(data_mod_Seguridades_SM , 3 );
}