#include <Arduino.h>
#include "Mod74hc595.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"
#include <ShiftRegister74HC595.h>

SoftwareSerial ESP_SERIAL_595(ESP_RX, ESP_TX);

ShiftRegister74HC595<NUM_MOD_595> sr(DATAPIN_595, CLKPIN_595, LATCHPIN_595);

void SerialTest595()
{
    for( int i = 0; i < 24; i++ )
    {
        ESP_SERIAL_595.println("Pin#"+ String(i));
        sr.setNoUpdate(i , HIGH);
        sr.updateRegisters();
        delay(3000);
        sr.setNoUpdate(i, LOW);
        sr.updateRegisters();
        delay(3000);
    }
    while (true)
    {
        delay(1);
    }
     
}

void MOD74HC595_Reset( )
{
    sr.setAllLow();
}

void MOD74HC595_Init( )
{
    ESP_SERIAL_595.begin(9600);
    sr.setAllLow();
}

uint32_t MOD74HC595_Configuration()
{
    uint32_t value = 0;
    for( uint8_t i = 0; i < 24; i++ )
    {
        value |= sr.get(i)<<i;
    }
    return value;
}

void MOD74HC595_Configuration( const struct data_ModBackend *config, uint8_t elements )
{
    for( int i = 0; i < elements; i++ ){
        uint8_t posPlaca = config[i].posPin;
        sr.setNoUpdate(posPlaca, config[i].estadoPin);
    }
    sr.updateRegisters();
}

void MOD74HC595_setOutput(const struct data_ModBackend *config, uint8_t elements )
{
    for( uint8_t i = 0; i < elements; i++ ){
        sr.setNoUpdate((uint8_t)config[i].posPin , (uint8_t)config[i].estadoPin);
    }
    sr.updateRegisters();
}