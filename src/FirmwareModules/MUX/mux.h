#ifndef _MUX_H
#define _MUX_H

#include <Arduino.h>
#include "../../DataModules/ModBackend/ModBackend.h"

void MUX_Init();
void MUX_LeerLlamadas( struct data_PinBackend *config, uint8_t elements );
void MUX_LeerSeg( struct data_PinBackend *config, uint8_t elements );
void MUX_LeeryActLlamadas( struct data_PinBackend *config, uint8_t elements );
void MUX_setOutput( struct data_PinBackend *config, uint8_t elements  );

#endif