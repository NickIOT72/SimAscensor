#include <Arduino.h>
#include "Mod74hc595.h"
#include "../BoardArch.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"
#include <ShiftRegister74HC595.h>

ShiftRegister74HC595<NUM_595_MODRELES> sr_reles(MUX_DATAPIN_RELE, MUX_CLKPIN_RELE, MUX_LATCHPIN_RELE);

void MOD74HC595_ResetReles( )
{
    sr_reles.setAllLow();
}

void MOD74HC595_InitReles( )
{
    sr_reles.setAllLow();

    //while(true)
    //{
    //    for( int i = 0 ; i < 16; i++ )
    //    {
    //        SoftSerial_Degub_println("Rele pin" + String(i) + ": HIGH");
    //        sr_reles.set(i,HIGH);
    //        delay(5000);
    //        SoftSerial_Degub_println("Rele pin" + String(i) + ": LOW");
    //        sr_reles.set(i,LOW);
    //        delay(5000);
    //    }
    //    for( int i = 0 ; i < 16; i++ )
    //    {
    //        SoftSerial_Degub_println("Llamadas pin" + String(i) + ": HIGH");
    //        sr_llamadas.set(i,HIGH);
    //        delay(5000);
    //        SoftSerial_Degub_println("Llamadas pin" + String(i) + ": LOW");
    //        sr_llamadas.set(i,LOW);
    //        delay(5000);
    //    }
    //}

}

void MOD74HC595_setOutput(const struct data_PinBackend *config, uint8_t elements )
{
    bool ReleConfg = false;
    for( uint8_t i = 0; i < elements; i++ ){
        uint8_t posPlaca = config[i].PosicionPlaca;
        uint8_t typeDevice = config[i].ModuloDevice;
        if( typeDevice == RELE595_MOD )
        {
            ReleConfg = true;
            sr_reles.setNoUpdate(posPlaca - RELE595_MOD_POS, config[i].EstadoPin?HIGH:LOW);
        }
    }
    if(ReleConfg)sr_reles.updateRegisters();
}

void MOD74HC595_getInput(struct data_PinBackend *config, uint8_t elements  )
{
    for( uint8_t i = 0; i < elements; i++ ){
        uint8_t posPlaca = config[i].PosicionPlaca;
        uint8_t typeDevice = config[i].ModuloDevice;
        if( typeDevice == RELE595_MOD )
        {
            config[i].EstadoPin = sr_reles.get(posPlaca - RELE595_MOD_POS);
        }
    }
}