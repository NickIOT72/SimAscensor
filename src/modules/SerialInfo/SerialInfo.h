#ifndef _SERIALINFO_H
#define _SERIALINFO_H

#define BAUDRATE_SERIALINFO 9600

#define ESP_HARDWARE_SERIAL

//extern String SerialInfoBuffer = "";

#if defined(ESP8266)
    #define ESP_RX_SI 14
    #define ESP_TX_SI 12
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    #define ESP_RX_SI 11
    #define ESP_TX_SI 7
#endif

#include <Arduino.h>


void SerialInfo_Init();
void SerialInfo_LeerUARTdata();
void SerialInfo_SendDataToMega( String FileSend );

#endif // !_SERIALINFO_H