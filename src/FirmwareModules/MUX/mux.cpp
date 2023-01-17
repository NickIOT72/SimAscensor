#include "mux.h"
#include "../Mod74hc595/Mod74hc595.h"
#include "../74HC4067MOD/74HC4067MOD.h"
#include "../SoftSerial/SoftSerial.h"
#include "../../FirmwareModules/BoardArch.h"


void MUX_Init()
{
    MOD74HC595_InitLlamads();
    MUX74HC4067_Init();
    //while (1)
    //{
    //  MUX74HC4067_test();
    //}
    //MUX74HC4067_test();
}

void MUX_LeerLlamadas( struct data_PinBackend *config, uint8_t elements )
{
    MUX74HC4067_readPin( config, elements );
}

void MUX_LeeryActLlamadas( struct data_PinBackend *config, uint8_t elements )
{
    MUX74HC4067_readPin( config, elements );
    MOD74HC595_setOutput( config, elements );
}

void MUX_LeerSeg( struct data_PinBackend *config, uint8_t elements )
{
  //  ////DEGUB_SERIAL_MUX.print( F("Modulo Seg: "));
  //  for( uint8_t i = 0; i < elements; i++  )
  //{
  //  ////DEGUB_SERIAL_MUX.print( F("PosicionPlaca: "));
  //  ////DEGUB_SERIAL_MUX.print(String( config[i].PosicionPlaca ));
  //  //DEGUB_SERIAL_BOARD.print(" , MOD: " + String(confg[i].)  + " => ");
  //  String deviceName = ( config[i].ModuloDevice == RELE595_MOD)?"595":( config[i].ModuloDevice == MUXINP_MOD)?"MUCINP":"MUXBID";
  //  ////DEGUB_SERIAL_MUX.print( F("Device:") );
  //  ////DEGUB_SERIAL_MUX.print( deviceName );
  //  ////DEGUB_SERIAL_MUX.print(F(", Pos:") );
  //  ////DEGUB_SERIAL_MUX.print(String(  config[i].PosicionPlaca) );
  //  deviceName = ( config[i].EstadoPin )?"ON":"OFF";
  //  ////DEGUB_SERIAL_MUX.print(F(", Estado:"));
  //  ////DEGUB_SERIAL_MUX.println( deviceName  );
//
  //}
    MUX74HC4067_readPin( config, elements );
}

void MUX_setOutput( struct data_PinBackend *config, uint8_t elements  )
{
    MOD74HC595_setOutput( config, elements );
}