#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>

struct Mod75HC595_Backend {
    uint8_t DataPin;
    uint8_t ClockPin;
    uint8_t LatchPin;
    uint8_t Modulos;
};


struct Mod75HC595_Backend mod595 = {0};

int MOD74HC595_Init( struct Mod75HC595_Backend *config);
int main()
{
    struct Mod75HC595_Backend mod595_1 = { 1,2,3,4 };

    MOD74HC595_Init( &mod595_1 );
    printf("strcut %d,%d,%d,%d", mod595.ClockPin,mod595.DataPin, mod595.LatchPin, mod595.Modulos);
    return 0;
}

int MOD74HC595_Init( struct Mod75HC595_Backend *config)
{
    mod595 = *config;
}