#include "BoardArch.h"
#include "MUX/mux.h"
#include "Rele/Rele.h"
#include "Mod74hc595/Mod74hc595.h"
#include "../Protocols/SoftSerial/SoftSerial.h"
#include "OLEDMod/OLEDMod.h"
#include "../DataModules/JsonMod/JsonMod.h"
#include "../Ascensor/Banderas/Banderas.h"
#include "../Ascensor/Seguridades/Seguridades.h"
#include "../Ascensor/Alertas/Alertas.h"
#include "../Ascensor/Puertas/Puertas.h"
#include "../Ascensor/Cabina/Cabina.h"

void Board_setMultipleOutputDevice( struct data_PinBackend *confg, uint8_t elements )
{

    for(  uint8_t i =0; i < elements; i++ )
    {
        switch (confg[i].ModuloDevice)
        {
          case MUXBID_MOD :
            MUX_setOutput( &confg[i], 1  );
            break;
          case MUXINP_MOD :
            break;
          case RELE595_MOD :
            RELE_setOutput( &confg[i], 1  );
            break;
          default:
              break;
        }
    }
}

void Board_setOneOutputDevice(  struct data_PinBackend *confg )
{
  switch (confg[0].ModuloDevice)
  {
    case MUXBID_MOD :
      MUX_setOutput( confg, 1  );
      break;
    case MUXINP_MOD :
      break;
    case RELE595_MOD :
      RELE_setOutput( confg, 1  );
      break;
    default:
        break;
  }

}


void Board_getMultipleInputDevice( struct data_PinBackend *confg, uint8_t elements )
{
    for(  uint8_t i =0; i < elements; i++ )
    {
        switch (confg[i].ModuloDevice)
        {
          case MUXBID_MOD :
            MUX_LeerLlamadas( &confg[i], 1  );
            break;
          case MUXINP_MOD :
            MUX_LeerSeg( &confg[i], 1  );
            break;
          case RELE595_MOD :
            RELE_LeerReles( &confg[i], 1  );
            break;
          default:
        break;
        }
    }
}

void Board_getOneInputDevice(struct data_PinBackend *confg)
{
  switch (confg[0].ModuloDevice)
  {
    case MUXBID_MOD :
      MUX_LeerLlamadas( confg, 1  );
      break;
    case MUXINP_MOD :
      MUX_LeerSeg( confg, 1  );
      break;
    case RELE595_MOD :
      RELE_LeerReles( confg, 1  );
      break;
    default:
        break;
  }
}


void Board_getInputSetOutputDevice( struct data_PinBackend *confg, uint8_t elements )
{
    struct data_PinBackend data_mod_MUXBID_MOD[elements];
    struct data_PinBackend data_mod_MUXINP_MOD[elements];
    struct data_PinBackend data_mod_RELE595_MOD_POS[elements];

    uint8_t count_MUXBID_MOD = 0;
    uint8_t count_MUXINP_MOD = 0;
    uint8_t count_RELE595_MOD_POS = 0;
    for(  uint8_t i =0; i < elements; i++ )
    {
        switch (confg[i].ModuloDevice)
        {
          case MUXBID_MOD :
            data_mod_MUXBID_MOD[count_MUXBID_MOD] = confg[i];
            count_MUXBID_MOD++;
            break;
          case MUXINP_MOD :
            data_mod_MUXINP_MOD[count_MUXINP_MOD] = confg[i];
            count_MUXINP_MOD++;
            break;
          case RELE595_MOD :
            data_mod_RELE595_MOD_POS[count_RELE595_MOD_POS] = confg[i];
            count_RELE595_MOD_POS++;
            break;
          default:
              break;
        }
    }
    if ( count_MUXBID_MOD > 0 ) MUX_LeeryActLlamadas( data_mod_MUXBID_MOD, count_MUXBID_MOD  );
    //if ( count_MUXINP_MOD > 0 ) MUX_LeerSeg( data_mod_MUXBID_MOD, count_MUXINP_MOD  );
    //if ( count_RELE595_MOD_POS > 0 ) RELE_LeerReles( data_mod_RELE595_MOD_POS, count_RELE595_MOD_POS  );
}
