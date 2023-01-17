#include "mux.h"
#include "../Mod74hc595/Mod74hc595.h"
//#include "../SoftSerial/SoftSerial.h"
#include "../../FirmwareModules/BoardArch.h"

//SoftwareSerial DEGUB_SERIAL_RELE(DEBUG_RX, DEBUG_TX);

void Rele_SoftSerial_IniModules()
{
    //Serial.begin(BAUD_SERIAL_FIRMWARE);
    //DEGUB_SERIAL_RELE.begin(BAUD_SERIAL_DEGUB);
    //BLE_SERIAL.begin( BAUD_SERIAL_BLE );
    //GSM_SERIAL.begin( BAUD_SERIAL_GSM );
}


void RELE_Init()
{
    Rele_SoftSerial_IniModules();
    MOD74HC595_InitReles();
}

void RELE_setOutput( struct data_PinBackend *config, uint8_t elements )
{
    Backend_UpdateState( config, elements );
    MOD74HC595_setOutput( config, elements );
}

void RELE_LeerReles( struct data_PinBackend *config, uint8_t elements )
{
    Backend_UpdateState( config, elements );
    MOD74HC595_getInput( config, elements );
}
