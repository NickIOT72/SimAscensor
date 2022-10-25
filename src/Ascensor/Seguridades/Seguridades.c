#include "Seguridades.h"
#include "../../modules/Mod74hc595/Mod74hc595.h"

struct data_ModBackend data_mod_595[4];

void Seguridades_Init( const struct data_ModBackend *confg, uint8_t elements)
{
    for( uint8_t i = 0; i < elements; i++  )
    {
        data_mod_595[i].posPin = confg[i].posPin;
        data_mod_595[i].estadoPin = confg[i].estadoPin;
    }
    MOD74HC595_setOutput(data_mod_595 , elements );
}


uint8_t Seguridades_leerEstadoPuerta()
{
    uint8_t estadoPuerta =  (uint8_t)(data_mod_595[bitFPA].estadoPin) << 2 | (uint8_t)(data_mod_595[bitSPC].estadoPin) << 1 | (uint8_t)(data_mod_595[bitSA].estadoPin);
    return estadoPuerta;
}

void Seguridades_ActivarSM()
{
    data_mod_595[bitSM].estadoPin = true;
    struct data_ModBackend data_mod_595_SM[]={data_mod_595[bitSM]};
    MOD74HC595_setOutput(data_mod_595_SM , 1 );
}

void Seguridades_ApagarSM()
{
    data_mod_595[bitSM].estadoPin = false;
    struct data_ModBackend data_mod_595_SM[]={data_mod_595[bitSM]};
    MOD74HC595_setOutput(data_mod_595_SM , 1 );
}