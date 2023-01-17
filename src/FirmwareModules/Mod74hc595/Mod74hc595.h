#ifndef _MOD74HC595_H
#define _MOD74HC595_H

#include <Arduino.h>
#include "../../DataModules/ModBackend/ModBackend.h"

void MOD74HC595_ResetReles( );
void MOD74HC595_InitReles( );
void MOD74HC595_setOutput(const struct data_PinBackend *config, uint8_t elements  );
void MOD74HC595_getInput(struct data_PinBackend *config, uint8_t elements  );
#endif // !1