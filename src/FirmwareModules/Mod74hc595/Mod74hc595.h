#ifndef _MOD74HC595_H
#define _MOD74HC595_H

#include <Arduino.h>
#include "../../DataModules/ModBackend/ModBackend.h"

/**
 * Crear Struct para guardar:
 * 1. Nombre del Modulo
 * 2. Pins A UTILIZAR [8]
 * 3. Estado de Cada Pin [8]
*/

void MOD74HC595_Reset( );
void MOD74HC595_Init( );
void MOD74HC595_setOutput(const struct data_PinBackend *config, uint8_t elements  );
void MOD74HC595_getInput(struct data_PinBackend *config, uint8_t elements  );
void MOD74HC595_test();

#endif // !1