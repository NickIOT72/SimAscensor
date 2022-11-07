#ifndef _OLEDMOD_H
#define _OLEDMOD_H

#include <Arduino.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// OLED FeatherWing buttons map to different pins depending on board.
// The I2C (Wire) bus may also be different.

#if defined(ESP8266)
    #define ADDRES_OLED 0X3C
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    #define ADDRES_OLED 0X3D
#endif

#define WIRE Wire

void OLED_Init();
void OLED_MensajeInicial();

#endif // !_OLEDMOD_H