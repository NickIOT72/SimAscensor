#ifndef _MODBACKEND_H
#define _MODBACKEND_H

enum deviceMod { dev595, devPCF, dev4067 };
enum oredenDeviceMod { device595pos=24, deviceMUX4067pos = 40 };

struct data_ModBackend {
    uint8_t device;
    uint8_t modIO;
    uint8_t posPin;
    bool estadoPin;
};

void Backend_ResetModules();
void Backend_setOutputDevice(  const struct data_ModBackend *confg, uint8_t elements );
void Backend_readInputDevice(  const struct data_ModBackend *confg, uint8_t elements );

#endif // !1