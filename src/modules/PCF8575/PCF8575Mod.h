#ifndef _PCF8575MOD_H
#define _PCF8575MOD_H

#include <Arduino.h>

extern bool keyChanged = false;

#if defined(ESP8266)
    #define DEVICE_INTERRUPTED_PIN 9
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    #define DEVICE_INTERRUPTED_PIN 2
#endif

#define ADDRRESS_PCFMOD 0x21

void PCF_Init();
void PCF_readBuffer();
bool PCF_verifyInt();
void PCF_Configuration(uint16_t pincConfg);

#endif // !_PCF8575MOD_H