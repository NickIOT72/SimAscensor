#include "Puertas.h"
#include "../../modules/Mod74hc595/Mod74hc595.h"
#include "../../modules/PCF8575/PCF8575Mod.h"

struct data_ModBackend data_mod_Puertas[2];

void Puertas_Init( const struct data_ModBackend *confg, uint8_t elements)
{
    for( uint8_t i = 0; i < elements; i++  )
    {
        data_mod_Puertas[i].device = confg[i].device;
        data_mod_Puertas[i].posPin = confg[i].posPin;
        data_mod_Puertas[i].estadoPin = confg[i].estadoPin;
    }
    for( uint8_t i = 0; i < elements; i++  )
    {
        struct data_ModBackend data_mod_Puertas_prov[] = { data_mod_Puertas[i] };
        //data_mod_Puertas[i].device==dev595?MOD74HC595_setOutput( data_mod_Puertas_prov , 1):
    }
    
}