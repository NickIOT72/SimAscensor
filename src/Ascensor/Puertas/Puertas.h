#ifndef _PUERTAS_H
#define _PUERTAS_H

#include <Arduino.h>
#include "../../modules/ModBackend.h"

#define NUM_SEG 4

enum bitOrder_Puertas {
    bitRSUB,
    bitRBAJ
};

enum puertaEstadoRele { puertoStop , puertaAbriendo, puertaCerrando, falllaPuerta };

void Puertas_Init(  const struct data_ModBackend *confg, uint8_t elements);

uint8_t Puertas_leerEstadoPuerta();
void Puertas_Abrir();
void Puertas_Cerrar();
void Puertas_Stop();

#endif // !_PUERTAS_H