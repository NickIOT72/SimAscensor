#ifndef _74HC4067MOD_H
#define _74HC4067MOD_H

#include "../ModBackend.h"

#define POS_INIT_PLACA 24

#if defined(ESP8266)
    #define DEVICE_INTERRUPTED_PIN 9
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    #define PINA 22
    #define PINB 23
    #define PINC 24
    #define PIND 25
    #define PINE 26
    #define PINX 27
#endif

//void PCF_Reset();
void MUX74HC4067_test();
void MUX74HC4067_Init();
//uint16_t PCF_readBuffer();
//bool PCF_verifyInt();
uint16_t MUX74HC4067_Configuration(const struct data_ModBackend *config, uint8_t elements);
uint16_t MUX74HC4067_readPinsAll();
uint16_t MUX74HC4067_readPin( uint8_t pin  );
//void PCF_setOutput( const struct data_ModBackend *config, uint8_t elements );

#endif // !_74HC4067MOD_H