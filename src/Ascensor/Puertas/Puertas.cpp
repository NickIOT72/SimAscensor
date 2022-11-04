#include <Arduino.h>
#include "Puertas.h"
#include "../Seguridades/Seguridades.h"
#include "../../modules/74HC4067MOD/74HC4067MOD.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"

SoftwareSerial ESP_SERIAL_PUERTA(ESP_RX, ESP_TX);

struct data_ModBackend data_mod_Puertas[2];

uint8_t contadorPuertas = 0;
uint8_t limiteConteoPuertas = 50;

uint8_t EstadoPuerta = 0;

void Puerta_Rest()
{
    for(uint8_t i = 0; i < 2; i++)
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
    uint8_t lecturaRAB =  !MUX74HC4067_readPin( data_mod_Puertas[bitRAB].posPin - 24 );
    uint8_t lecturaRCR =  !MUX74HC4067_readPin( data_mod_Puertas[bitRCR].posPin - 24  );
    uint16_t lecturaPuerta = lecturaRCR << 1 | lecturaRAB;
    //ESP_SERIAL_PUERTA.print( "lectura puertas: " );
    //ESP_SERIAL_PUERTA.println(  lecturaPuerta, BIN   );
    return lecturaPuerta;
}


void Puertas_AbriendoPuerta()
{   
    static bool AperturaCercana = false;
    if( contadorPuertas >= limiteConteoPuertas  ) return;
    if( Puertas_leerEstadoPuerta() != puertaAbriendo  ) return;
    contadorPuertas++;
    //ESP_SERIAL_PUERTA.print("Apertura de Puerta Conteo:");
    //ESP_SERIAL_PUERTA.println(contadorPuertas);
    
    if ( contadorPuertas >= 0 && contadorPuertas < 3 && EstadoPuerta != cerradoPuerta )
    {
        ESP_SERIAL_PUERTA.println("Apertura de Puerta Iniciada");
        EstadoPuerta = cerradoPuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }else if ( contadorPuertas >= 3 && contadorPuertas < 5 && EstadoPuerta != CierreEsperandoSA )
    {
        ESP_SERIAL_PUERTA.println("Apertura de Puerta saliendo de SA");
        EstadoPuerta = CierreEsperandoSA;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }else if ( contadorPuertas >= 5 && contadorPuertas < 45 && EstadoPuerta != entrePuerta )
    {
        ESP_SERIAL_PUERTA.println("Apertura de Puerta entre puertas");
        EstadoPuerta = entrePuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }else if ( contadorPuertas >= 45 && contadorPuertas < limiteConteoPuertas && EstadoPuerta == entrePuerta )
    {
        if( !AperturaCercana ){
            AperturaCercana = true;
            ESP_SERIAL_PUERTA.println("Apertura de Puerta en 90%");  
        }
        
    }else if ( contadorPuertas == limiteConteoPuertas && EstadoPuerta != abiertaPuerta )
    {
        ESP_SERIAL_PUERTA.println("Apertura de Puerta Completada");
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
        ESP_SERIAL_PUERTA.println("Cierre de Puerta finalizado");
        EstadoPuerta = cerradoPuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );
        AperturaCercana = false;
    }
    else if ( contadorPuertas > 0 && contadorPuertas < 3 && EstadoPuerta == CierreEsperandoSA )
    {
        if( !AperturaCercana ){
            AperturaCercana = true;
            ESP_SERIAL_PUERTA.println("Cierre de Puerta en 95%");  
        }
    }else if ( contadorPuertas >= 3 && contadorPuertas < 5 && EstadoPuerta != CierreEsperandoSA )
    {
        ESP_SERIAL_PUERTA.println("Cierre de Puerta saliendo de SA");
        EstadoPuerta = CierreEsperandoSA;
        Seguridades_actualizarPuerta( EstadoPuerta );
    }else if ( contadorPuertas >= 5 && contadorPuertas < 45 && EstadoPuerta != entrePuerta )
    {
        ESP_SERIAL_PUERTA.println("Cierre de puertas entre puertas");
        EstadoPuerta = entrePuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );

    }else if ( contadorPuertas >= 45 && contadorPuertas <= limiteConteoPuertas && EstadoPuerta != abiertaPuerta )
    {
        ESP_SERIAL_PUERTA.println("Cierre de Puerta Iniciada");
        EstadoPuerta = abiertaPuerta;
        Seguridades_actualizarPuerta( EstadoPuerta );
        
    }
}