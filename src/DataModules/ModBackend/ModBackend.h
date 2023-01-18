#ifndef _MODBACKEND_H
#define _MODBACKEND_H

#include <Arduino.h>

struct data_EventRegisterBackend {
    uint8_t TituloEvento;
    bool TipoEvento;
    bool Estado;
    uint8_t ContadorCatidadVecesEventoFallido;
    uint8_t ContadorCatidadVecesEventoFinalizado;
    uint16_t LimiteTiempo;
    unsigned long TiempoInicial;
    uint16_t UltimoTiempoTranscurrido;
    uint16_t ContadorEvento;
};

struct data_PinBackend {
    uint8_t PosicionPlaca;
    uint8_t ModuloDevice;
    uint8_t PosModulo;
    bool EstadoPin;
    bool disponible = false;
    char* nombrePin;
};

void Backend_UpdateState( struct data_PinBackend *confg, uint8_t elements);
void Backend_Registro_Iniciar( struct data_EventRegisterBackend * reg );
void Backend_Registro_Finalizar( struct data_EventRegisterBackend * reg , String msgEvent );
void Backend_Registro_Cancelado( struct data_EventRegisterBackend * reg );
void Backend_Registro_Fallido( struct data_EventRegisterBackend * reg ,  String msgEvent );
void Backend_Registro_Detener( struct data_EventRegisterBackend * reg );
void Backend_Registro_Reanudar( struct data_EventRegisterBackend * reg );
bool Backend_Registro_EventoDetenido( struct data_EventRegisterBackend * reg );
void Backend_Registro_Reiniciar( struct data_EventRegisterBackend * reg );


#endif // !1