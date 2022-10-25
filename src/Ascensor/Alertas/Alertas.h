#ifndef _BANDERAS_H
#define _BANDERAS_H

#include "../../modules/ModBackend.h"

enum bitOrder_Alertas {
    bitBOMB,
    bitEMER,
    bitQ1,
    bitQ2,
    bitFOTO,
    bitMANT,
    bitPTC,
    bitAUTAR,
};

void Alertas_Init(  const struct data_ModBackend *confg, uint8_t elements);

uint8_t Alertas_leerAlertas();

void Alertas_ActivarALerta( uint8_t bitAlerta);
void Alertas_ApagarAlerta(uint8_t bitAlerta);

#endif // !_BANDERAS_H