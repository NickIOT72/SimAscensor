#ifndef _SEGURIDADES_H
#define _SEGURIDADES_H

#include "../../modules/ModBackend.h"

#define NUM_SEG 4

enum bitOrder_Seguridades {
    bitSM,
    bitFPA,
    bitSPC,
    bitSA
};

enum puertaEstado { entrePuerta , CierreEsperandoSPC, CierreEsperandoSA, cerradoPuerta , abiertaPuerta, FallaFPA_SA, FALLA_FPA_SPC, FALLA_FPA_SPC_SA };

void Seguridades_Init(  const struct data_ModBackend *confg, uint8_t elements);

uint8_t leerEstadoPuerta();
void ActivarSM();
void ApagarSM();

#endif // !_OLEDMOD_H