#ifndef _MOD74HC595_H
#define _MOD74HC595_H

#include "../ModBackend.h"

#define NUM_MOD_595 3

#if defined(ESP8266)
    #define DATAPIN_595 0
    #define CLKPIN_595 9
    #define LATCHPIN_595 10
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    #define DATAPIN_595 A0
    #define CLKPIN_595 A1
    #define LATCHPIN_595 A2
#endif

struct Mod75HC595_Backend {
    uint8_t DataPin;
    uint8_t ClockPin;
    uint8_t LatchPin;
    uint8_t Modulos;
};

void MOD74HC595_Init( );
void MOD74HC595_Configuration( const struct data_ModBackend *config, uint8_t elements );
void MOD74HC595_setOutput(const struct data_ModBackend *config, uint8_t elements  );
void MOD74HC595_Reset( );
uint32_t MOD74HC595_Configuration();

#endif // !1