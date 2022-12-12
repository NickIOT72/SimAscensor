#ifndef _SEGURIDADES_H
#define _SEGURIDADES_H

#include <Arduino.h>
#include "../../modules/ModBackend.h"

#define NUM_SEG 4

enum bitOrder_Seguridades {
    bitFPA,
    bitSPC,
    bitSA,
    bitSM
};

/*enum puertaEstado { abiertaPuerta , 
FALLA_FPA_SPC, 
FALLA_FPA_SPC_SA, 
FallaFPA_SA, 
entrePuerta, 
CierreEsperandoSPC, 
CierreEsperandoSA, 
cerradoPuerta };
*/


enum puertaEstado { 
cerradoPuerta ,
CierreEsperandoSA,
CierreEsperandoSPC, 
entrePuerta, 
FallaFPA_SA, 
FALLA_FPA_SPC_SA, 
FALLA_FPA_SPC, 
abiertaPuerta
};

void Seguridades_Init(  const struct data_ModBackend *confg, uint8_t elements);

uint8_t Seguridades_leerEstadoPuerta();
void Seguridades_ActivarSM();
void Seguridades_ApagarSM();
void Seguridades_actualizarPuerta( uint8_t LecEstadoPuerta );

#endif // !_OLEDMOD_H