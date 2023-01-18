#ifndef _BANDERAS_H
#define _BANDERAS_H

#include <Arduino.h>

#define DELAY_AV 10
#define DELAY_BV 40
#define CANT_POS_ASC 15

extern uint16_t contadorSecuenciaPiso;
extern uint8_t contadorBanderas;
extern uint8_t contadorSecuenciaAnterior;
extern uint8_t limiteConteoBanderas[15] ;
extern uint8_t modoConteoBandera;
extern bool llegando;
extern bool direccion;

enum modoDeBanderas{
    PADPAS,
    PN
};

enum limitesConteoPADPAS {
    piso_base_x = 0,
    piso_base_y = 2,
    piso_ascensor_x,
    piso_ascensor_cambio = 7,
    piso_ascensor_y = 10,
    piso_final_x = 12,
    piso_final_y = 14
};


const uint8_t pisosSecuenciaPASPAD[15] = {
	0b00001110,//2
	0b00001010,//10
	0b00001000,//85
    0b00000000,//100
	0b00000010,//5
	0b00000000,//85
	0b00000100,//10
	0b00000110,//5
	0b00000010,//10
	0b00000000,//100
	0b00000100,//5
    0b00000000,//85
    0b00000001,//85
	0b00000101,//10
	0b00000111 //2
};

enum bitOrder_Banderas {
    bitEXD,
    bitPAD_PN,
    bitPAS,
    bitEXS
};

void Banderas_Init(  const struct data_PinBackend *confg, uint8_t elements, uint8_t modoConteoBanderas);

uint8_t Banderas_leerBanderas();
void IncrementarBandera(int *PisoActual, int *TotalPisos);
void DecrementarBandera(int *PisoActual);
void Banderas_resetContadorBanderas();

#endif // !_BANDERAS_H