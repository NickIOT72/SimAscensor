#ifndef _74HC4067MOD_H
#define _74HC4067MOD_H

#include "../../DataModules/ModBackend/ModBackend.h"

void MUX74HC4067_test();
void MUX74HC4067_Init();
void MUX74HC4067_readPin( struct data_PinBackend *config, uint8_t elements  );
void MUX74HC4067_readPin( uint8_t *pinsPlaca, uint8_t elements );

#endif // !_74HC4067MOD_H