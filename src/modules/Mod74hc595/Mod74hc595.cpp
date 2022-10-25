#include <Arduino.h>
#include "Mod74hc595.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"
#include <ShiftRegister74HC595.h>

SoftwareSerial ESP_SERIAL_595(ESP_RX, ESP_TX);

struct Mod75HC595_Backend ModAsc = {DATAPIN_595,CLKPIN_595,LATCHPIN_595,  NUM_MOD_595 };

ShiftRegister74HC595<NUM_MOD_595> sr(DATAPIN_595, CLKPIN_595, LATCHPIN_595);

void MOD74HC595_Init( )
{
    sr.setAllLow();
}

void MOD74HC595_setOutput(const struct data_ModBackend *config, uint8_t elements )
{
    for( uint8_t i = 0; i < elements; i++ ){
        if(config[i].posPin >= 0  )sr.setNoUpdate((uint8_t)config[i].posPin , (uint8_t)config[i].estadoPin);
    }
    sr.updateRegisters();
}