#include "Puertas.h"
#include "../../modules/Mod74hc595/Mod74hc595.h"
#include "../../modules/PCF8575/PCF8575Mod.h"

struct data_ModBackend data_mod_Puertas[2];

void Puerta_Rest()
{
    for(uint8_t i = 0; i < 2; i++)
    {
        data_mod_Puertas[i] = {0};
    }
}

void Puertas_Init( const struct data_ModBackend *confg, uint8_t elements)
{
    Puerta_Rest();
    for( uint8_t i = 0; i < elements; i++  )
    {
        data_mod_Puertas[i].device = confg[i].device;
        data_mod_Puertas[i].modIO = confg[i].modIO;
        data_mod_Puertas[i].posPin = confg[i].posPin;
        data_mod_Puertas[i].estadoPin = confg[i].estadoPin;
    }
    Backend_setOutputDevice(data_mod_Puertas , elements );
    
}