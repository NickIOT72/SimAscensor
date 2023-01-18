#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint-gcc.h>

struct data_PinBackend {
    int PosicionPlaca;
    uint8_t ModuloDevice;
    uint8_t PosModulo;
    bool EstadoPin;
    bool disponible;
    char* nombrePin;
};


struct data_PinBackend mod595 = {0};

int MOD74HC595_Init( struct data_PinBackend *config);
int main()
{
    struct data_PinBackend mod595_1 = { 1,2,3, false, false, "hola" };

    MOD74HC595_Init( &mod595_1 );
    printf("strcut %d,%d,%d", mod595.PosicionPlaca,mod595.ModuloDevice, mod595.PosModulo);
    return 0;
}

int MOD74HC595_Init( struct data_PinBackend *config)
{
    mod595 = *config;
}