#ifndef _ASCENSORES_H
#define _ASCENSORES_H

#include <Arduino.h>

#define NUM_PISOS 24
extern uint8_t TotalPisos;

enum nombreModulos { MS1, MS2, MSA, ME1, MEA };

enum OrdenConfgPins
{
  EXDpos,
  PAD_PNpos,
  PASpos,
  EXSpos,
  FPApos,
  SPCpos,
  SApos,
  SMpos,
  BOMBpos,
  EMERpos,
  Q1pos,
  Q2pos,
  FOTOpos,
  MANTpos,
  PTCpos,
  AUTARpos,
  RSUBpos,
  RBAJpos,
  RAVpos,
  RBVpos,
  RABRpos,
  RCERpos,
  VENTpos,
  PATINpos
};

enum moduloExtensor{ MOD595, MODPCF };

struct ModulosExtensores {
    bool modEst;
    String ModuloNombre;
    int posicion[8];
    String pinNombre[8];
    int Estado[8];
};

extern int* CongfPinsPoint[24];
extern int* EstadoPinsPoint[24];

#endif // !_ASCENSORES_H