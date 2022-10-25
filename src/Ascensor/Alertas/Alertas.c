#include "Alertas.h"
#include <Arduino.h>
#include "../../modules/Mod74hc595/Mod74hc595.h"

struct data_ModBackend data_mod_Alertas[8];

void Alertas_Init(  const struct data_ModBackend *confg, uint8_t elements)
{
    for( uint8_t i = 0; i < elements; i++  )
    {
        data_mod_Alertas[i].posPin = confg[i].posPin;
        data_mod_Alertas[i].estadoPin = confg[i].estadoPin;
    }
    MOD74HC595_setOutput(data_mod_Alertas , elements );
}

uint8_t Alertas_leerAlertas()
{
    uint8_t estadoAlerta= 0;
    for(int i =0 ; i < 8; i++)
    {
        estadoAlerta |= (uint8_t)(data_mod_Alertas[ i ].estadoPin) << i;
    }
    return estadoAlerta;
}

void Alertas_ActivarALerta( uint8_t bitAlerta)
{
    data_mod_Alertas[bitAlerta].estadoPin = true;
    struct data_ModBackend data_ModBackend_prov[]={data_mod_Alertas[bitAlerta]};
    MOD74HC595_setOutput(data_ModBackend_prov , 1 );
}

void Alertas_ApagarAlerta(uint8_t bitAlerta)
{
    data_mod_Alertas[bitAlerta].estadoPin = true;
    struct data_ModBackend data_ModBackend_prov[]={data_mod_Alertas[bitAlerta]};
    MOD74HC595_setOutput(data_ModBackend_prov , 1 );
}