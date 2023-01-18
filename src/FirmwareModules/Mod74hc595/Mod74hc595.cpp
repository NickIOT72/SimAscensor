#include <Arduino.h>
#include "Mod74hc595.h"
#include "../BoardArch.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"
#include <ShiftRegister74HC595.h>

ShiftRegister74HC595<NUM_595_MOD> sr_595(MUX_DATAPIN, MUX_CLKPIN, MUX_LATCHPIN);

void MOD74HC595_Reset( )
{
    sr_595.setAllLow();
}

void MOD74HC595_Init( )
{
    sr_595.setAllLow();
}

void MOD74HC595_test()
{
    uint8_t tt = 0;
    while(tt < 2)
    {
        for( int i = 0 ; i < NUM_595_MOD*8; i++ )
        {
            SoftSerial_Degub_println("Rele pin" + String(i) + ": HIGH");
            sr_595.set(i,HIGH);
            delay(100);
            SoftSerial_Degub_println("Rele pin" + String(i) + ": LOW");
            sr_595.set(i,LOW);
            delay(100);
        }
        tt++;
    }
}

void MOD74HC595_setOutput(const struct data_PinBackend *config, uint8_t elements )
{
    bool ReleConfg = false;
    for( uint8_t i = 0; i < elements; i++ ){
        if(!ReleConfg)ReleConfg = true;
        sr_595.setNoUpdate(config[i].PosModulo, config[i].EstadoPin?HIGH:LOW);
    }
    if(ReleConfg)sr_595.updateRegisters();
}

void MOD74HC595_getInput(struct data_PinBackend *config, uint8_t elements  )
{
    for( uint8_t i = 0; i < elements; i++ ){
        config[i].EstadoPin = sr_595.get(config[i].PosModulo);
    }
}