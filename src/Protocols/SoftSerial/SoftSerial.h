#ifndef _SOFTSERIAL_H
#define _SOFTSERIAL_H

#include <Arduino.h>
#include <ArduinoJson.h>
#if defined(__AVR_ATmega644A__) || defined(__AVR_ATmega328p__) 
    #include <SoftwareSerial.h>
#endif

/* Module DEBUG */
#define ALLOW_DEBUG

#define DEBUG_RX 11
#define DEBUG_TX 10

/* Module GSM */
#define GSM_RX 13
#define GSM_TX 12

/* Module PROGRAM FIRMWARE */
#define PROGRAM_RX 0
#define PROGRAM_TX 1

/* Module BLE */
#define BLE_RX A8
#define BLE_TX A9
    


// VARIABLES USED to set BAUDRATE 
#define      BAUD_SERIAL_FIRMWARE 9600
#define      BAUD_SERIAL_DEGUB 9600
#define      BAUD_SERIAL_BLE 9600
#define      BAUD_SERIAL_GSM 9600

// API of SoftSerial Module
void SoftSerial_IniModules();

void SoftSerial_Degub_print( String Str );
void SoftSerial_Degub_print( const char* Str );
void SoftSerial_Degub_print( int num , int type = DEC );
void SoftSerial_Degub_print( float num );
void SoftSerial_Degub_print( double num );
void SoftSerial_Degub_print( unsigned long num , int type = DEC );
void SoftSerial_Degub_print( long num , int type = DEC );
void SoftSerial_Degub_print( JsonObject &jsonObj );
void SoftSerial_Degub_print( JsonArray &jsonArray );

void SoftSerial_Degub_println( String Str );
void SoftSerial_Degub_println( const char* Str );
void SoftSerial_Degub_println( int num , int type = DEC );
void SoftSerial_Degub_println( float num );
void SoftSerial_Degub_println( double num );
void SoftSerial_Degub_println( unsigned long num , int type = DEC );
void SoftSerial_Degub_println( long num , int type = DEC );
#endif // !_SOFTSERIAL_H