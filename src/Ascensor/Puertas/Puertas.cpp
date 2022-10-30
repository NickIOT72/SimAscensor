#include <Arduino.h>
#include "Puertas.h"
#include "../Seguridades/Seguridades.h"
#include "../../modules/74HC4067MOD/74HC4067MOD.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"

SoftwareSerial ESP_SERIAL_PUERTA(ESP_RX, ESP_TX);

struct data_ModBackend data_mod_Puertas[8];

uint8_t contadorPuertas = 0;
uint8_t limiteConteoPuertas = 30;

uint8_t EstadoPuerta = 0;

void Puerta_Rest()
{
    for(uint8_t i = 0; i < 8; i++)
    {
        data_mod_Puertas[i] = {0};
    }
    contadorPuertas = 0;

}

void Puertas_Init( const struct data_ModBackend *confg, uint8_t elements)
{
    ESP_SERIAL_PUERTA.begin(9600);
    Puerta_Rest();
    for( uint8_t i = 0; i < elements; i++  )
    {
        data_mod_Puertas[i].device = confg[i].device;
        data_mod_Puertas[i].modIO = confg[i].modIO;
        data_mod_Puertas[i].posPin = confg[i].posPin;
        data_mod_Puertas[i].estadoPin = confg[i].estadoPin;
    }
    EstadoPuerta = Seguridades_leerEstadoPuerta();
}

uint16_t Puertas_leerEstadoPuerta()
{
    uint8_t lecturaRAB =  MUX74HC4067_readPin( data_mod_Puertas[bitRAB].posPin - 24 );
    uint8_t lecturaRCR =  MUX74HC4067_readPin( data_mod_Puertas[bitRCR].posPin - 24  );
    uint16_t lecturaPuerta = lecturaRCR << 1 | lecturaRAB;
    //ESP_SERIAL_PUERTA.print( "lectura puertas: " );
    //ESP_SERIAL_PUERTA.println(  lecturaPuerta, BIN   );
    return lecturaPuerta;
}


void Puertas_AbriendoPuerta()
{   
    if( contadorPuertas >= limiteConteoPuertas  ) return;
    if( Puertas_leerEstadoPuerta() != puertaAbriendo  ) return;
    contadorPuertas++;
    if ( contadorPuertas >= 0 && contadorPuertas < 5 && EstadoPuerta != cerradoPuerta )
    {
        EstadoPuerta = cerradoPuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }else if ( contadorPuertas > 0 && contadorPuertas <= 45 && EstadoPuerta != entrePuerta )
    {
        EstadoPuerta = entrePuerta;
        Seguridades_actualizarPuerta( entrePuerta );
    }else if ( contadorPuertas > 45 && contadorPuertas < limiteConteoPuertas && EstadoPuerta != CierreEsperandoSA )
    {
        EstadoPuerta = CierreEsperandoSA;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }else if ( contadorPuertas == limiteConteoPuertas && EstadoPuerta != abiertaPuerta )
    {
        EstadoPuerta = abiertaPuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }
}


void Puertas_CerrandoPuerta()
{
    if( contadorPuertas == 0  ) return;
    if( Puertas_leerEstadoPuerta() != puertaCerrando  ) return;
    contadorPuertas--;
    if ( contadorPuertas == 0  &&  EstadoPuerta != cerradoPuerta )
    {
        EstadoPuerta = cerradoPuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }else if ( contadorPuertas > 0 && contadorPuertas <= 45 && EstadoPuerta != entrePuerta )
    {
        EstadoPuerta = entrePuerta;
        Seguridades_actualizarPuerta( entrePuerta );
    }else if ( contadorPuertas > 45 && contadorPuertas < limiteConteoPuertas && EstadoPuerta != CierreEsperandoSA )
    {
        EstadoPuerta = CierreEsperandoSA;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }else if ( contadorPuertas == limiteConteoPuertas && EstadoPuerta != abiertaPuerta )
    {
        EstadoPuerta = abiertaPuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }
}