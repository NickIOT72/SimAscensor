#ifndef _ASCENSOR_H
#define _ASCENSOR_H

#include <ArduinoJson.h>

enum deviceMod { dev595, devPCF, dev4067 };
enum oredenDeviceMod { device595pos=24, deviceMUX4067pos = 40 };

#define NUM_PISOS 24
extern int TotalPisos;
extern int pisoActual;

#define NUM_IO_TOTAL 24 

#define NUM_TOTAL_MODULOS 5
#define NUM_PIN_MODULO 8

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

void Ascensor_Init( String StrJSONObject   );
void ActualizarModulos(String StrJSONObject);
void Ascensor_VerificarPosicion();
bool VerificarCabina();

#endif // !_ASCENSORES_H