#include "mux.h"
#include "../Mod74hc595/Mod74hc595.h"
#include "../../FirmwareModules/BoardArch.h"



void RELE_Init()
{
    MOD74HC595_Init();
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
