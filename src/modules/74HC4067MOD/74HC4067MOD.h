#ifndef _74HC4067MOD_H
#define _74HC4067MOD_H

#include "../ModBackend.h"

#define POS_INIT_PLACA 24

#if defined(ESP8266)
    #define MUX_PINA 15
    #define MUX_PINB 13
    #define MUX_PINC 12
    #define MUX_PIND 14
    #define MUX_PINE 16
    #define MUX_PINX 16
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    #define MUX_PINA 22
    #define MUX_PINB 23
    #define MUX_PINC 24
    #define MUX_PIND 25
    #define MUX_PINE 26
    #define MUX_PINX 27
#endif

//void PCF_Reset();
void MUX74HC4067_test();
void MUX74HC4067_Init();
//uint16_t PCF_readBuffer();
//bool PCF_verifyInt();
void MUX74HC4067_Configuration(const struct data_ModBackend *config, uint8_t elements);
uint16_t MUX74HC4067_readPinsAll();
uint16_t MUX74HC4067_readPin(  struct data_ModBackend *config, uint8_t elements);
//void PCF_setOutput( const struct data_ModBackend *config, uint8_t elements );

#endif // !_74HC4067MOD_H