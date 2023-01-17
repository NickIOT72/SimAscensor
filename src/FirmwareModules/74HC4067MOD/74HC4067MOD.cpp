#include <Arduino.h>
#include "./74HC4067MOD.h"
#include <Mux.h>
#include "../SoftSerial/SoftSerial.h"
#include "../../FirmwareModules/BoardArch.h"

//SoftwareSerial DEGUB_SERIAL_MOD4067(DEBUG_RX, DEBUG_TX);

using namespace admux;

/**
 * Creates a Mux instance.
 *
 * 1st argument is the SIG (signal) pin (Arduino digital input pin 3).
 * 2nd argument is the S0-S3 (channel control) pins (Arduino pins 8, 9, 10, 11).
 */
Mux muxllamada1(Pin(MUX_PIN_OUT1, INPUT , PinType::Digital), Pinset(MUX_PIN_S0, MUX_PIN_S1, MUX_PIN_S2, MUX_PIN_S3));
Mux muxllamada2(Pin(MUX_PIN_OUT2, INPUT, PinType::Digital), Pinset(MUX_PIN_S0, MUX_PIN_S1, MUX_PIN_S2, MUX_PIN_S3));
Mux muxllamada3(Pin(MUX_PIN_OUT3, INPUT, PinType::Digital), Pinset(MUX_PIN_S0, MUX_PIN_S1, MUX_PIN_S2, MUX_PIN_S3));

Mux muxrele(Pin(MUX_PIN_OUT4, INPUT, PinType::Digital), Pinset(MUX_PIN_S0, MUX_PIN_S1, MUX_PIN_S2, MUX_PIN_S3));

void MUX74HC4067_Init()
{
  pinMode( MUX_PIN_ENA1 , OUTPUT);
  pinMode( MUX_PIN_ENA2 , OUTPUT);
  pinMode( MUX_PIN_ENA3 , OUTPUT);
  pinMode( MUX_PIN_ENA4 , OUTPUT);
  digitalWrite( MUX_PIN_ENA1, HIGH );
  digitalWrite( MUX_PIN_ENA2, HIGH );
  digitalWrite( MUX_PIN_ENA3, HIGH );
  digitalWrite( MUX_PIN_ENA4, HIGH );
}

void MUX74HC4067_test()
{
  SoftSerial_Degub_println(F("Test MUX74HC4067 "));
    delay(5000);
    uint16_t data;
    uint16_t arrayPinEnable[4]= { MUX_PIN_ENA1, MUX_PIN_ENA2, MUX_PIN_ENA3 , MUX_PIN_ENA4};
    Mux arrayMux[4] = {muxllamada1 , muxllamada2, muxllamada3 , muxrele};
    for( uint8_t j = 0; j < 4; j = j +3 )
    {
      digitalWrite( arrayPinEnable[j], LOW );
      for (byte i = 0; i < arrayMux[j].channelCount(); i++) {
        data = arrayMux[j].read(i) /* Reads from channel i (returns HIGH or LOW) */;
        SoftSerial_Degub_print(F("data "));
        SoftSerial_Degub_print(int(data));
        
        SoftSerial_Degub_print(F(" , Push button at channel ")); SoftSerial_Degub_print(j*16 + i); SoftSerial_Degub_print(F(" is ")); SoftSerial_Degub_println(data > 500 ? "pressed" : "not pressed");
        delay(5000);
      }
      digitalWrite( arrayPinEnable[j], HIGH );
    }
    //////SoftSerial_Degub_println();
    delay(100);
}

void MUX74HC4067_readPin( struct data_PinBackend *config, uint8_t elements ){
  Mux arrayMux[4] = {muxllamada1 , muxllamada2, muxllamada3, muxrele };
  uint8_t arrayPinEnable[4]= { MUX_PIN_ENA1, MUX_PIN_ENA2, MUX_PIN_ENA3, MUX_PIN_ENA4 };
  for( uint8_t i = 0; i < elements; i++ )
  {
    uint8_t pinEnableChoose = config[i].PosicionPlaca/16;
    uint8_t pin = config[i].PosicionPlaca - pinEnableChoose*16;
    digitalWrite( arrayPinEnable[pinEnableChoose], LOW );
    delayMicroseconds(5);
    uint16_t data = arrayMux[pinEnableChoose].read( pin );
    config[i].EstadoPin = !(data > 0);
    digitalWrite( arrayPinEnable[pinEnableChoose], HIGH );
    //char bufferMux[150];
    //sprintf( bufferMux, "DATA:%d, Mod#%d, Push button Pin: %d , Push button at channel %d is %s",data,pinEnableChoose, pin, config[i].PosicionPlaca, config[i].EstadoPin ? "pressed" : "not pressed");
    //SoftSerial_Degub_print(bufferMux);
    //SoftSerial_Degub_print(F("Push button Pin: "));
    //SoftSerial_Degub_print(pin);
    //SoftSerial_Degub_print(F(" , Push button at channel "));
    //SoftSerial_Degub_print(config[i].PosicionPlaca);
    //SoftSerial_Degub_println(config[i].EstadoPin ? "pressed" : "not pressed");
    //delay(2000);
    
  }
}

void MUX74HC4067_readPin( uint8_t *pinsPlaca, uint8_t elements ){
  Mux arrayMux[4] = {muxllamada1 , muxllamada2, muxllamada3, muxrele };
  uint8_t arrayPinEnable[4]= { MUX_PIN_ENA1, MUX_PIN_ENA2, MUX_PIN_ENA3, MUX_PIN_ENA4 };
  for( uint8_t i = 0; i < elements; i++ )
  {
    uint8_t pinEnableChoose = i /16;
    uint8_t pin = i - pinEnableChoose*16;
    //SoftSerial_Degub_print(F("Push button Pin: "));
    //SoftSerial_Degub_print(pin);
    digitalWrite( arrayPinEnable[pinEnableChoose], LOW );
    //delayMicroseconds(10);
    uint16_t data = arrayMux[pinEnableChoose].read( pin );
    pinsPlaca[i] = !(data > 0);
    //SoftSerial_Degub_print(F(" , Push button at channel ")); SoftSerial_Degub_print(config[i].PosicionPlaca); SoftSerial_Degub_print(F(" is ")); SoftSerial_Degub_println(config[i].EstadoPin ? "pressed" : "not pressed");
    digitalWrite( arrayPinEnable[pinEnableChoose], HIGH );
  }
}