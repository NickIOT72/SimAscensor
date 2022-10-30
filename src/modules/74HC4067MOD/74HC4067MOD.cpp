#include <Arduino.h>
#include "./74HC4067MOD.h"
#include <Mux.h>
#include "../../Protocols/SoftSerial/SoftSerial.h"

SoftwareSerial ESP_SERIAL_MUX(ESP_RX, ESP_TX);

using namespace admux;

/*
 * Creates a Mux instance.
 *
 * 1st argument is the SIG (signal) pin (Arduino digital input pin 3).
 * 2nd argument is the S0-S3 (channel control) pins (Arduino pins 8, 9, 10, 11).
 */
Mux mux(Pin(MUX_PINX, INPUT, PinType::Digital), Pinset(MUX_PINA, MUX_PINB, MUX_PINC, MUX_PIND));

void MUX74HC4067_Init()
{
    ESP_SERIAL_MUX.begin(9600);
}

void MUX74HC4067_test()
{
   byte data;
  for (byte i = 0; i < mux.channelCount(); i++) {
    data = mux.read(i) /* Reads from channel i (returns HIGH or LOW) */;

    ESP_SERIAL_MUX.print("Push button at channel "); ESP_SERIAL_MUX.print(i); ESP_SERIAL_MUX.print(" is "); ESP_SERIAL_MUX.println(data == LOW ? "pressed" : "not pressed");
  }
  ESP_SERIAL_MUX.println();
  delay(1500);
}

uint16_t MUX74HC4067_readPin( uint8_t pin  ){
    uint8_t data = mux.read(pin);
    //ESP_SERIAL_MUX.print("Push button at channel "); ESP_SERIAL_MUX.print(pin); ESP_SERIAL_MUX.print(" is "); ESP_SERIAL_MUX.println(data == LOW ? "pressed" : "not pressed");
    //delay(1000);
    return data;
}

uint16_t MUX74HC4067_readPinsAll()
{
    uint16_t data;
    for (byte i = 0; i < mux.channelCount(); i++) {
        data |= mux.read(i) << i /* Reads from channel i (returns HIGH or LOW) */;
    }
    return data;
}