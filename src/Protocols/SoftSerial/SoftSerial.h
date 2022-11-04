#ifndef _SOFTSERIAL_H
#define _SOFTSERIAL_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define      BAUD_SERIAL 9600

#if defined(ESP8266)
    #define ESP_RX 14
    #define ESP_TX 12 
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    #define ESP_RX 10
    #define ESP_TX 4 
#endif


#endif // !_SOFTSERIAL_H