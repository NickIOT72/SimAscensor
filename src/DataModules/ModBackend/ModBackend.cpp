#include "ModBackend.h"
//#include "../../FirmwareModules/SoftSerial/SoftSerial.h"
#include "../../FirmwareModules/BoardArch.h"
#include "../../FirmwareModules/RTC/RTC.h"

struct RTC_data *RTC_Reg;


void Backend_sendMessage(  )
{
    RTC_getDateTime( RTC_Reg );
    String fecha_tiempo = String(RTC_Reg->year);
    fecha_tiempo += "/";
    fecha_tiempo += String(RTC_Reg->month);
    fecha_tiempo += "/";
}

//SoftwareSerial DEGUB_SERIAL_BACKEND(DEBUG_RX, DEBUG_TX);
/**
 * @brief Actualizar la salida de la placa con el struct de backend
 * 1. se crean los array de struct de acuerdo al numero dedeviceMod que existen en la placa
 * 2. se verifca el deviceMod de cada struct y se añaden al array correspondiente
 * 3. si hay strcut guardados, se envian a al funcion corespondiente para colocar el estado la salida
 * 
 * @param confg 
 * @param elements 
 */

void Backend_Init()
{
    //Serial.begin(BAUD_SERIAL_FIRMWARE);
    //DEGUB_SERIAL_BACKEND.begin(BAUD_SERIAL_DEGUB);
    //BLE_SERIAL.begin( BAUD_SERIAL_BLE );
    //GSM_SERIAL.begin( BAUD_SERIAL_GSM );
}

void Backend_UpdateState(struct data_PinBackend *confg, uint8_t elements)
{
    for ( uint8_t i = 0; i < elements; i++ )
    {
        confg[i].EstadoPin = confg[i].EstadoPin;
    }
}

void Backend_Registro_Iniciar( struct data_EventRegisterBackend * reg )
{
    reg->Estado = true;
    reg->TiempoInicial = millis();
}

void Backend_Registro_Reiniciar( struct data_EventRegisterBackend * reg )
{
    reg->TiempoInicial = millis();
}


void Backend_Registro_Finalizar( struct data_EventRegisterBackend * reg  , String msgEvent  )
{
    reg->Estado = false;
    reg->TiempoInicial = 0;
    reg->TituloEvento = 0 ;
    reg->ContadorCatidadVecesEventoFinalizado++;
    //DEGUB_SERIAL_BACKEND.println("Evento: " + msgEvent);
    
}

void Backend_Registro_Fallido( struct data_EventRegisterBackend * reg , String msgEvent  )
{
    reg->Estado = false;
    reg->TiempoInicial = 0;
    reg->TituloEvento = 0 ;
    reg->ContadorCatidadVecesEventoFallido++;
    //DEGUB_SERIAL_BACKEND.println("Evento: " + msgEvent);
}

void Backend_Registro_Detener( struct data_EventRegisterBackend * reg )
{
    reg->UltimoTiempoTranscurrido = millis() - reg->TiempoInicial;
    reg->TiempoInicial = 0;
}

void Backend_Registro_Reanudar( struct data_EventRegisterBackend * reg )
{
    reg->TiempoInicial = millis() + reg->UltimoTiempoTranscurrido ;
    reg->UltimoTiempoTranscurrido = 0;
}

bool Backend_Registro_EventoDetenido( struct data_EventRegisterBackend * reg )
{
    return !reg->TiempoInicial && reg->Estado;
}

void Backend_Registro_Cancelado( struct data_EventRegisterBackend * reg  )
{
    reg->Estado = false;
    reg->TiempoInicial = 0;
    reg->TituloEvento = 0 ;
}