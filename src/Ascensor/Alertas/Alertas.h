#ifndef _ALERTAS_H
#define _ALERTAS_H

#include <Arduino.h>
#include "../../DataModules/ModBackend/ModBackend.h"

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

void Alertas_Init(  const struct data_PinBackend *confg, uint8_t elements);

uint8_t Alertas_leerAlertas(void);

void Alertas_ActivarALerta( uint8_t bitAlerta);
void Alertas_ApagarAlerta(uint8_t bitAlerta);

#endif // !_ALERTAS_H