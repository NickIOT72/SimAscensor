#include <Arduino.h>
#include "ModBackend.h"
#include "Mod74hc595/Mod74hc595.h"
#include "PCF8575/PCF8575Mod.h"


/**
 * @brief Actualizar la salida de la placa con el struct de backend
 * 1. se crean los array de struct de acuerdo al numero dedeviceMod que existen en la placa
 * 2. se verifca el deviceMod de cada struct y se añaden al array correspondiente
 * 3. si hay strcut guardados, se envian a al funcion corespondiente para colocar el estado la salida
 * 
 * @param confg 
 * @param elements 
 */


void Backend_ResetModules()
{
    PCF_Reset();
    MOD74HC595_Reset();
}

void Backend_confgDevice(  const struct data_ModBackend *confg, uint8_t elements )
{
    struct data_ModBackend data_mod_595[elements];
    struct data_ModBackend data_mod_PCF[elements];

    uint8_t count595 = 0;
    uint8_t countPCF = 0;

    for(  uint8_t i =0; i < elements; i++ )
    {
        switch (confg[i].device)
        {
        case devPCF :
            data_mod_PCF[countPCF] = confg[i];
            countPCF++;
            break;
        case dev595 :
            data_mod_595[count595] = confg[i];
            count595++;
            break;
        default:
            break;
        }
    }

    if ( countPCF > 0 ) { PCF_Configuration(data_mod_PCF,countPCF ); };

}

void Backend_setOutputDevice(  const struct data_ModBackend *confg, uint8_t elements )
{
    struct data_ModBackend data_mod_595[elements];
    struct data_ModBackend data_mod_PCF[elements];

    uint8_t count595 = 0;
    uint8_t countPCF = 0;

    for(  uint8_t i =0; i < elements; i++ )
    {
        switch (confg[i].device)
        {
        case devPCF :
            data_mod_PCF[countPCF] = confg[i];
            countPCF++;
            break;
        case dev595 :
            data_mod_595[count595] = confg[i];
            count595++;
            break;
        default:
            break;
        }
    }

    if ( countPCF > 0 ) PCF_setOutput( data_mod_PCF,countPCF  );
    if ( count595 > 0 ) MOD74HC595_setOutput( data_mod_595 , count595  );

}

void Backend_readInputDevice(  const struct data_ModBackend *confg, uint8_t elements )
{
    struct data_ModBackend data_mod_595[elements];
    struct data_ModBackend data_mod_PCF[elements];

    uint8_t count595 = 0;
    uint8_t countPCF = 0;

    for(  uint8_t i =0; i < elements; i++ )
    {
        switch (confg[i].device)
        {
        case devPCF :
            data_mod_PCF[countPCF] = confg[i];
            countPCF++;
            break;
        case dev595 :
            data_mod_595[count595] = confg[i];
            count595++;
            break;
        default:
            break;
        }
    }
    

    if ( countPCF > 0 ) PCF_setOutput( data_mod_PCF,countPCF  );
    if ( count595 > 0 ) MOD74HC595_setOutput( data_mod_595 , count595  );

}