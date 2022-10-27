#include <Arduino.h>
#include "PCF8575Mod.h"
#include <PCF8575.h>
#include "../../Protocols/SoftSerial/SoftSerial.h"

SoftwareSerial ESP_SERIAL_PCF(ESP_RX, ESP_TX);

bool keyChanged = false;

void interruptFunct()
{
    keyChanged = true;
}

PCF8575 pcf8575(ADDRRESS_PCFMOD, DEVICE_INTERRUPTED_PIN,  interruptFunct );

void PCF_Reset()
{
    for( uint8_t i = 0; i < 16; i++  )
    {
        pcf8575.pinMode( i , INPUT   );
    }
}

void PCF_setOutput( const struct data_ModBackend *config, uint8_t elements )
{
    for( int i = 0; i < elements; i++ ){
        uint8_t posPlaca = config[i].posPin >POS_INIT_PLACA ? config[i].posPin - POS_INIT_PLACA :config[i].posPin;
        uint8_t modIOplaca = config[i].modIO;
        if ( modIOplaca == OUTPUT ){
            pcf8575.digitalWrite(posPlaca, config[i].estadoPin);
        } 
    }
}

void PCF_Configuration(const struct data_ModBackend *config, uint8_t elements){
    for( int i = 0; i < elements; i++ ){
        uint8_t posPlaca = config[i].posPin >POS_INIT_PLACA ? config[i].posPin - POS_INIT_PLACA:config[i].posPin;
        uint8_t modIOplaca = config[i].modIO;
        pcf8575.pinMode( posPlaca , modIOplaca   );
        if ( modIOplaca == OUTPUT ){
            pcf8575.digitalWrite(posPlaca, config[i].estadoPin);
        } 
    }
}

void PCF_Init()
{
    pcf8575.begin();
    PCF_Reset();
}

uint16_t PCF_readBuffer()
{
    keyChanged = false;
    return pcf8575.digitalReadAll();
}

bool PCF_verifyInt(){return keyChanged;}