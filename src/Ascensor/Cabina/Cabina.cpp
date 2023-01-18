#include <Arduino.h>
#include "Cabina.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"
#include "../Banderas/Banderas.h"
#include "../Ascensor.h"
#include "../../FirmwareModules/74HC4067MOD/74HC4067MOD.h"


struct data_PinBackend data_mod_Cabinas[4];

uint8_t EstadoCabina= 0;

void Cabina_Rest()
{
    struct data_PinBackend prov_d;
    for(uint8_t i = 0; i < 4; i++)
    {
        data_mod_Cabinas[i] = prov_d;
    }
}

void Cabinas_Init(  const struct data_PinBackend *confg, uint8_t elements)
{
    Cabina_Rest();
    for( uint8_t i = 0; i < elements; i++  )
    {
        data_mod_Cabinas[i] = confg[i];
    }
    EstadoCabina = Banderas_leerBanderas();
}

uint8_t Cabina_leerEstadoCabina()
{
    MUX74HC4067_readPin( data_mod_Cabinas , 4);
    uint8_t lecturaCAbina = (data_mod_Cabinas[bitRSUB].EstadoPin + 0)<< bitRSUB | (data_mod_Cabinas[bitRBAJ].EstadoPin + 0)<< bitRBAJ | (data_mod_Cabinas[bitRAV].EstadoPin + 0)<< bitRAV | (data_mod_Cabinas[bitRBJ].EstadoPin + 0)<< bitRBJ ;
    return lecturaCAbina;
}