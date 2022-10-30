#ifndef _PUERTAS_H
#define _PUERTAS_H

#include "../../modules/ModBackend.h"

#define NUM_SEG 4

extern uint8_t contadorPuertas;
extern uint8_t limiteConteoPuertas;

extern uint8_t EstadoPuerta;

enum bitOrder_Puertas {
    bitRAB,
    bitRCR
};

enum puertaEstadoRele { puertoStop , puertaAbriendo, puertaCerrando, falllaPuerta };

void Puertas_Init(  const struct data_ModBackend *confg, uint8_t elements);

uint16_t Puertas_leerEstadoPuerta();
void Puertas_AbriendoPuerta();
void Puertas_CerrandoPuerta();

#endif // !_PUERTAS_H