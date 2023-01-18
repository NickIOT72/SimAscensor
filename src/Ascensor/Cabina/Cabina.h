#ifndef _CABINA_H
#define _CABINA_H

#include "../../DataModules/ModBackend/ModBackend.h"

extern uint8_t EstadoCabina;

enum bitOrder_Cabina {
    bitRSUB,
    bitRBAJ,
    bitRAV,
    bitRBJ
};

enum cabinaEstadoRele { cabinaDetenida, Falla_RSUB, Falla_RBAJ, Falla_RSUB_RBAJ, 
    Falla_RAV, cabinaSubiendoEnAlta, cabinaBajandoEnAlta,  Falla_rav_rsub_rbaj,
    Falla_RBJ, cabinaSubiendoEnBaja, cabinaBajandoEnBaja,  Falla_rbj_rsub_rbaj,
    Falla_RAV_RBJ, FALLA_RSUB_RAV_RSUB, FALLA_RBAJ_RAV_RSUB , FALLA_RSUB_RBAJ_RAV_RBJ};

void Cabinas_Init(  const struct data_PinBackend *confg, uint8_t elements);

uint8_t Cabina_leerEstadoCabina();

#endif // !_CABINA_H