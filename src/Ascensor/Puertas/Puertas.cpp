#include <Arduino.h>
#include "Puertas.h"
#include "../Seguridades/Seguridades.h"
#include "../../FirmwareModules/74HC4067MOD/74HC4067MOD.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"

struct data_PinBackend data_mod_Puertas[2];

uint8_t contadorPuertas = 0;
uint8_t limiteConteoPuertas = 50;

uint8_t EstadoPuerta = 0;

void Puerta_Rest()
{
    struct data_PinBackend prov_d;
    for(uint8_t i = 0; i < 2; i++)
    {
        data_mod_Puertas[i] = prov_d;
    }
    contadorPuertas = 0;
}

void Puertas_Init( const struct data_PinBackend *confg, uint8_t elements)
{
    Puerta_Rest();
    for (uint8_t i = 0; i < elements; i++)
    {
        data_mod_Puertas[i] = confg[i];
    }
    EstadoPuerta = Seguridades_leerEstadoPuerta();
    if( EstadoPuerta == abiertaPuerta ) contadorPuertas = limiteConteoPuertas;
}

uint16_t Puertas_leerEstadoPuerta()
{
    MUX74HC4067_readPin( data_mod_Puertas , 2);
    uint16_t lecturaPuerta = (data_mod_Puertas[bitRAB].EstadoPin+0)<< bitRAB | (data_mod_Puertas[bitRCR].EstadoPin+0)<< bitRCR;
    return lecturaPuerta;
}


void Puertas_AbriendoPuerta()
{   
    static bool AperturaCercana = false;
    if( contadorPuertas >= limiteConteoPuertas  ) return;
    if( Puertas_leerEstadoPuerta() != puertaAbriendo  ) return;
    contadorPuertas++;
    //SoftSerial_Degub_print("Apertura de Puerta Conteo:");
    //SoftSerial_Degub_println(contadorPuertas);
    
    if ( contadorPuertas >= 0 && contadorPuertas < 3 && EstadoPuerta != cerradoPuerta )
    {
        SoftSerial_Degub_println("Apertura de Puerta Iniciada");
        EstadoPuerta = cerradoPuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }else if ( contadorPuertas >= 3 && contadorPuertas < 5 && EstadoPuerta != CierreEsperandoSA )
    {
        SoftSerial_Degub_println("Apertura de Puerta saliendo de SA");
        EstadoPuerta = CierreEsperandoSA;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }else if ( contadorPuertas >= 5 && contadorPuertas < 45 && EstadoPuerta != entrePuerta )
    {
        SoftSerial_Degub_println("Apertura de Puerta entre puertas");
        EstadoPuerta = entrePuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }else if ( contadorPuertas >= 45 && contadorPuertas < limiteConteoPuertas && EstadoPuerta == entrePuerta )
    {
        if( !AperturaCercana ){
            AperturaCercana = true;
            SoftSerial_Degub_println("Apertura de Puerta en 90%");  
        }
        
    }else if ( contadorPuertas == limiteConteoPuertas && EstadoPuerta != abiertaPuerta )
    {
        SoftSerial_Degub_println("Apertura de Puerta Completada");
        AperturaCercana = false;
        EstadoPuerta = abiertaPuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }
}


void Puertas_CerrandoPuerta()
{
    static bool AperturaCercana = false;
    if( contadorPuertas == 0  ) return;
    if( Puertas_leerEstadoPuerta() != puertaCerrando  ) return;
    contadorPuertas--;
    if ( contadorPuertas == 0 && EstadoPuerta != cerradoPuerta )
    {
        SoftSerial_Degub_println("Cierre de Puerta finalizado");
        EstadoPuerta = cerradoPuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );
        AperturaCercana = false;
    }
    else if ( contadorPuertas > 0 && contadorPuertas < 3 && EstadoPuerta == CierreEsperandoSA )
    {
        if( !AperturaCercana ){
            AperturaCercana = true;
            SoftSerial_Degub_println("Cierre de Puerta en 95%");  
        }
    }else if ( contadorPuertas >= 3 && contadorPuertas < 5 && EstadoPuerta != CierreEsperandoSA )
    {
        SoftSerial_Degub_println("Cierre de Puerta saliendo de SA");
        EstadoPuerta = CierreEsperandoSA;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }else if ( contadorPuertas >= 5 && contadorPuertas < 45 && EstadoPuerta != entrePuerta )
    {
        SoftSerial_Degub_println("Cierre de puertas entre puertas");
        EstadoPuerta = entrePuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );

    }else if ( contadorPuertas >= 45 && contadorPuertas <= limiteConteoPuertas && EstadoPuerta != abiertaPuerta )
    {
        SoftSerial_Degub_println("Cierre de Puerta Iniciada");
        EstadoPuerta = abiertaPuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );
        
    }
}