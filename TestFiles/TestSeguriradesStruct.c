#include <stdio.h>
#include <stdlib.h>

struct data_ModBackend {
    int posPin;
    int estadoPin;
};


struct data_ModBackend data_mod_595[4];

void Seguridades_Init( const struct data_ModBackend *confg, uint8_t elements)
{
    for( uint8_t i = 0; i < elements; i++  )
    {
        data_mod_595[i].posPin = confg[i].posPin;
        data_mod_595[i].estadoPin = confg[i].estadoPin;
    }
    MOD74HC595_setOutput(data_mod_595 , elements );
}

