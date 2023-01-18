#include "Seguridades.h"
#include "../../FirmwareModules/Mod74hc595/Mod74hc595.h"

struct data_PinBackend data_mod_Seguridades[4];

/**
 * @brief Resetar los struct del odulo seguridades
 *
 */

void Seguridades_resetSeguridades()
{
    struct data_PinBackend prov_d;
    for (uint8_t i = 0; i < 4; i++)
    {
        data_mod_Seguridades[i] = prov_d;
    }
}

/**
 * @brief Se inicializa el modulo de Seguridades
 * 1. se limpia el array data_mod_Banderas;
 * 2. se configruar el modo de conteo de banderas y el strut backend de cada pin
 * 3. se configura el modulo de banderas usando la funcion del backend
 *
 * @param confg
 * @param elements
 */
void Seguridades_Init(const struct data_PinBackend *confg, uint8_t elements)
{
    Seguridades_resetSeguridades();
    for (uint8_t i = 0; i < elements; i++)
    {
        data_mod_Seguridades[i] = confg[i];
    }
    MOD74HC595_setOutput(data_mod_Seguridades, elements);
}

uint8_t Seguridades_leerEstadoPuerta()
{
    uint8_t estadoPuerta = (uint8_t)(data_mod_Seguridades[bitFPA].EstadoPin) << 2 | (uint8_t)(data_mod_Seguridades[bitSPC].EstadoPin) << 1 | (uint8_t)(data_mod_Seguridades[bitSA].EstadoPin);
    return estadoPuerta;
}

void Seguridades_ActivarSM()
{
    data_mod_Seguridades[bitSM].EstadoPin = false;
    struct data_PinBackend data_mod_Seguridades_SM[] = {data_mod_Seguridades[bitSM]};
    MOD74HC595_setOutput(data_mod_Seguridades_SM, 1);
}

void Seguridades_ApagarSM()
{
    data_mod_Seguridades[bitSM].EstadoPin = true;
    struct data_PinBackend data_mod_Seguridades_SM[] = {data_mod_Seguridades[bitSM]};
    MOD74HC595_setOutput(data_mod_Seguridades_SM, 1);
}

void Seguridades_actualizarPuerta(uint8_t LecEstadoPuerta)
{
    data_mod_Seguridades[bitFPA].EstadoPin = (((LecEstadoPuerta >> 2) & (0X01)) > 0);
    data_mod_Seguridades[bitSPC].EstadoPin = (((LecEstadoPuerta >> 1) & (0X01)) > 0);
    data_mod_Seguridades[bitSA].EstadoPin = (((LecEstadoPuerta) & (0X01)) > 0);

    struct data_PinBackend data_mod_Seguridades_SM[] = {data_mod_Seguridades[bitFPA], data_mod_Seguridades[bitSPC], data_mod_Seguridades[bitSA]};
    MOD74HC595_setOutput(data_mod_Seguridades_SM, 3);
}