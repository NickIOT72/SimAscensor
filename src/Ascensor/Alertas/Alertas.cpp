#include "Alertas.h"
#include "../../FirmwareModules/Mod74hc595/Mod74hc595.h"
#include "../../FirmwareModules/BoardArch.h"

struct data_PinBackend data_mod_Alertas[8];

/**
 * @brief Resetar los struct del odulo banderas
 * 
 */

void Alertas_reset()
{
    struct data_PinBackend prov_d;
  for( uint8_t i = 0; i < 4; i++  )
  {
    data_mod_Alertas[i]= prov_d;
  }
}

void Alertas_Init(  const struct data_PinBackend *confg, uint8_t elements)
{
    for( uint8_t i = 0; i < elements; i++  )
    {
        data_mod_Alertas[i] = confg[i];
    }
    Board_setMultipleOutputDevice(data_mod_Alertas , elements );
}

uint8_t Alertas_leerAlertas(void)
{
    uint8_t estadoAlerta= 0;
    for(int i =0 ; i < 8; i++)
    {
        estadoAlerta |= (uint8_t)(data_mod_Alertas[ i ].EstadoPin) << i;
    }
    return estadoAlerta;
}

void Alertas_ActivarALerta( uint8_t bitAlerta)
{
    data_mod_Alertas[bitAlerta].EstadoPin = true;
    struct data_PinBackend data_PinBackend_prov[]={data_mod_Alertas[bitAlerta]};
    Board_setMultipleOutputDevice(data_PinBackend_prov , 1 );
}

void Alertas_ApagarAlerta(uint8_t bitAlerta)
{
    data_mod_Alertas[bitAlerta].EstadoPin = false;
    struct data_PinBackend data_PinBackend_prov[]={data_mod_Alertas[bitAlerta]};
    Board_setMultipleOutputDevice(data_PinBackend_prov , 1 );
}