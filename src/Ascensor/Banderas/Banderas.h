#ifndef _BANDERAS_H
#define _BANDERAS_H

#include "../../modules/ModBackend.h"

extern uint16_t contadorSecuenciaPiso;
extern uint8_t contadorBanderas;
extern uint8_t limiteConteoBanderas;
extern bool modoConteoBandera;

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

enum bitOrder_Seguridades {
    bitEXD,
    bitPAD_PN,
    bitPAS,
    bitEXS
};

void Banderas_Init(  const struct data_ModBackend *confg, uint8_t elements);

uint8_t Banderas_leerBanderas();
void IncrementarBandera(uint8_t *PisoActual, uint8_t *TotalPisos);
void DecrementarBandera(uint8_t *PisoActual);

#endif // !_BANDERAS_H