#include "PCF8575Mod.h"
#include <PCF8575.h>
#include "../../Protocols/SoftSerial/SoftSerial.h"

SoftwareSerial ESP_SERIAL_PCF(ESP_RX, ESP_TX);

PCF8575 pcf8575(ADDRRESS_PCFMOD, DEVICE_INTERRUPTED_PIN,  interruptFunct );

bool keyChanged = false;
uint16_t Confg

void interruptFunct()
{
    keyChanged = true;
}

void PCF_Configuration(uint16_t pincConfg){
    for (uint8_t i = 0; i < 16; i++)
    {
        pcf8575.pinMode(i, (pincConfg >> i)&(0x0001)  );
    }
}

void PCF_Init()
{
    pcf8575.begin();
    PCF_Configuration(0);
}

uint16_t PCF_readBuffer()
{
    keyChanged = false;
    return digitalReadAll();
}

bool PCF_verifyInt(){return keyChanged}