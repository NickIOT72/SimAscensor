#include <Arduino.h>
#include "Cabina.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"
#include "../Banderas/Banderas.h"
#include "../Ascensor.h"
#include "../../modules/74HC4067MOD/74HC4067MOD.h"

SoftwareSerial ESP_SERIAL_CABINA(ESP_RX, ESP_TX);

struct data_ModBackend data_mod_Cabinas[4];

uint8_t EstadoCabina= 0;

void Cabina_Rest()
{
    for(uint8_t i = 0; i < 4; i++)
    {
        data_mod_Cabinas[i] = {0};
    }
}

void Cabinas_Init(  const struct data_ModBackend *confg, uint8_t elements)
{
    ESP_SERIAL_CABINA.begin(9600);
    Cabina_Rest();
    for( uint8_t i = 0; i < elements; i++  )
    {
        data_mod_Cabinas[i].device = confg[i].device;
        data_mod_Cabinas[i].modIO = confg[i].modIO;
        data_mod_Cabinas[i].posPin = confg[i].posPin;
        data_mod_Cabinas[i].estadoPin = confg[i].estadoPin;
    }
    EstadoCabina = Banderas_leerBanderas();
}

uint8_t Cabina_leerEstadoCabina()
{
    uint8_t lecturaRSUB =  !MUX74HC4067_readPin( data_mod_Cabinas[bitRSUB].posPin - 24 );
    uint8_t lecturaRBAJ =  !MUX74HC4067_readPin( data_mod_Cabinas[bitRBAJ].posPin - 24 );
    uint8_t lecturaRAV =  !MUX74HC4067_readPin( data_mod_Cabinas[bitRAV].posPin - 24 );
    uint8_t lecturaRBJ =  !MUX74HC4067_readPin( data_mod_Cabinas[bitRBJ].posPin - 24 );

    uint16_t lecturaCAbina = lecturaRBJ<<3 | lecturaRAV<<2 | lecturaRBAJ<<1 | lecturaRSUB<<0;
    return lecturaCAbina;
}