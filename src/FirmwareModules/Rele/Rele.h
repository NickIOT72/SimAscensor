#ifndef _RELE_H
#define _RELE_H

#include <Arduino.h>
#include "../../DataModules/ModBackend/ModBackend.h"

void RELE_Init();
void RELE_LeerReles( struct data_PinBackend *config, uint8_t elements );
void RELE_setOutput( struct data_PinBackend *config, uint8_t elements );

#endif