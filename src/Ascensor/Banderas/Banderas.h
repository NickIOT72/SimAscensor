#ifndef _BANDERAS_H
#define _BANDERAS_H

#include <Arduino.h>
#include "../../modules/ModBackend.h"

#define DELAY_AV 100
#define DELAY_BV 250

extern uint16_t contadorSecuenciaPiso;
extern uint8_t contadorBanderas;
extern uint8_t limiteConteoBanderas;
extern uint8_t modoConteoBandera;

enum modoDeBanderas{
    PADPAS,
    PN
};

enum limitesConteoPADPAS {
    piso_base_x = 0,
    piso_base_y = 2,
    piso_ascensor_x,
    piso_ascensor_cambio = 8,
    piso_ascensor_y = 11,
    piso_final_x ,
    piso_final_y = 14
};

const uint8_t pisosSecuenciaPASPAD[15] = {
	0b00001110,
	0b00001010,
	0b00001000,
    0b00000000,
	0b00000010,
	0b00000000,
	0b00000100,
	0b00000110,
	0b00000010,
	0b00000000,
	0b00000100,
    0b00000000,
    0b00000001,
	0b00000101,
	0b00000111   
};

enum bitOrder_Banderas {
    bitEXD,
    bitPAD_PN,
    bitPAS,
    bitEXS
};

void Banderas_Init(  const struct data_ModBackend *confg, uint8_t elements, uint8_t modoConteoBanderas);

uint8_t Banderas_leerBanderas();
void IncrementarBandera(int *PisoActual, int *TotalPisos);
void DecrementarBandera(int *PisoActual);
void Banderas_resetContadorBanderas();

#endif // !_BANDERAS_H