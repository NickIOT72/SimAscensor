#ifndef _PCF8575MOD_H
#define _PCF8575MOD_H

#include "../ModBackend.h"

#define POS_INIT_PLACA 24

#if defined(ESP8266)
    #define DEVICE_INTERRUPTED_PIN 9
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    #define DEVICE_INTERRUPTED_PIN 2
#endif

#define ADDRRESS_PCFMOD 0x21

void PCF_Init(const struct data_ModBackend *config, uint8_t elements);
uint16_t PCF_readBuffer();
bool PCF_verifyInt();
void PCF_Configuration(const struct data_ModBackend *config, uint8_t elements);
void PCF_setOutput( const struct data_ModBackend *config, uint8_t elements );

#endif // !_PCF8575MOD_H