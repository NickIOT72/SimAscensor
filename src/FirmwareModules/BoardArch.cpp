#include "BoardArch.h"
#include "MUX/mux.h"
#include "Rele/Rele.h"
#include "Mod74hc595/Mod74hc595.h"
#include "SoftSerial/SoftSerial.h"
#include "OLEDMod/OLEDMod.h"
#include "../DataModules/JsonMod/JsonMod.h"
#include "../Process/Banderas/Banderas.h"
#include "../Process/Seguridades/Seguridades.h"
#include "../Process/Alertas/Alertas.h"
#include "../Process/Puertas/Puertas.h"
#include "../Process/Cabina/Cabina.h"
#include "../Process/Llamadas/Llamadas.h"

//SoftwareSerial DEGUB_SERIAL_BOARD(DEBUG_RX, DEBUG_TX);

char* CongfPinsStr[TOTAL_PINS_BOARD_CONFIG] = {
    "EXD", "PAD_PN", "PAS", "EXS",
    "FPA","SPC","SA", "SM",
    "BOMB", "EMER", "Q1", "Q2", "FOTO", "MANT","PTC", "AUTAR",
    "RSUB", "RBAJ", "RAV", "RBV", "RABR", "RCER", "VENT", "PATIN",
    "PB", "P1", "P2", "P3", "P4", "P5", "P6", "P7",
    "CB", "C1", "C2", "C3", "C4", "C5", "C6", "C7"
    }; //;

const char strConfInit[] PROGMEM = R"(
{"NombrePlaca": "Placa1",
"Modelo":"V1",
"TIPO_CONTEO":"PADPAS",
"TOTAL_PISOS":8,
"ARCH":{
"MB1":{
"PINNAME": ["PB","P1","P2","P3","P4","P5","P6","P7"],
"VAL":[0,0,0,0,0,0,0,0]
},
"MB2":{
"PINNAME": ["CB","C1","C2","C3","C4","C5","C6","C7"],
"VAL":[0,0,0,0,0,0,0,0]
},
"MB3":{
"PINNAME": ["","","","","","","",""],
"VAL":[0,0,0,0,0,0,0,0]
},
"MB4":{
"PINNAME": ["","","","","","","",""],
"VAL":[0,0,0,0,0,0,0,0]
},
"MB5":{
"PINNAME": ["","","","","","","",""],
"VAL":[0,0,0,0,0,0,0,0]
},
"MB6":{
"PINNAME": ["","","","","","","",""],
"VAL":[0,0,0,0,0,0,0,0]
},
"ME1":{
"PINNAME":["EXD","PAD_PN","PAS","EXS","FPA","SPC","SA","SM"],
"VAL":[0,0,0,0,0,1,1,1]
},
"ME2":{
"PINNAME":["BOMB","EMER","Q1","Q2","FOTO","MANT","PTC","AUTAR"],
"VAL":[0,0,0,0,0,0,0,0]
},
"MS1": {
"PINNAME":["RSUB","RBAJ","RAV","RBV","RABR","RCER","VENT","PATIN"],
"VAL": [0,0,0,0,0,0,0,0]
},
"MS2": {
"PINNAME":["","","","","","","",""],

"VAL": [0,0,0,0,0,0,0,0]
}
}
})";

const char banderasText[] PROGMEM = "Banderas";


int Board_returnNumPiso( String NombrePin )
{
  if( NombrePin == "" ) return - 1;
  else if( NombrePin == "PB" || NombrePin == "CB"  ) return 0;
  else if (NombrePin.substring(0,1) == "P" ) return ( NombrePin.substring(1)  ).toInt();
  else if ( NombrePin.substring(0,1) == "C"  ) return (( NombrePin.substring(1)  ).toInt() + NUM_MAX_PISOS);
  else return -1;
}

uint8_t Board_VerificarModuloSegunPosicion(uint8_t PosicionEnPlaca)
{
  uint8_t valRet = 0;
  if (PosicionEnPlaca < MUX_MOD_INP_POS)
    valRet = MUXBID_MOD;
  else if (PosicionEnPlaca < RELE595_MOD_POS)
    valRet = MUXINP_MOD;
  else if (PosicionEnPlaca < TOTAL_POSITION_BOARD)
    valRet = RELE595_MOD;
  return valRet;
}

void Board_TestExamples()
{
  const int delay_test = 5000;
  //SoftSerial_Degub_println("");
  //uint16_t leerSeg = Banderas_leerBanderas()| (Seguridades_leerEstadoPuerta()<<4) | (Alertas_leerAlertas()<<8);; //
  //SoftSerial_Degub_print(F("Read Seg: "));
  //SoftSerial_Degub_println(leerSeg, BIN);
  //delay(delay_test);

  //unsigned long tstartLlamdas = millis();
  Llamadas_VerificarLlamadas();
  //SoftSerial_Degub_print("Tiempo minimo de funcion llLlamadas_VerificarLlamadas():");
  //SoftSerial_Degub_println( millis() - tstartLlamdas  );

  //SoftSerial_Degub_println(F("Verificando Puerta "));
  //SoftSerial_Degub_println(F("Detener Puerta "));
  //Puertas_PararPuertas();
  //delay(delay_test);
  //SoftSerial_Degub_println(F(" Puerta Abriendo"));
  //Puertas_AbrirPuerta();
  //delay(delay_test);
  //SoftSerial_Degub_println(F(" Puerta Cerrando"));
  //Puertas_CerrarPuerta();
  //delay(delay_test);
  //SoftSerial_Degub_println(F("Detener Puerta "));
  //Puertas_PararPuertas();
  //delay(delay_test);
//
  //SoftSerial_Degub_println(F("Verificando Cabina "));
  //SoftSerial_Degub_println(F("Detener Cabina "));
  //Cabina_Detener();
  //delay(delay_test);
  //SoftSerial_Degub_println(F(" Cabina bajando en BV "));
  //Cabina_BajarEnBV();
  //delay(delay_test);
  //SoftSerial_Degub_println(F(" Cabina bajando en AV "));
  //Cabina_BajarEnAV();
  //delay(delay_test);
  //SoftSerial_Degub_println(F(" Cabina subiendo en BV "));
  //Cabina_BajarEnBV();
  //delay(delay_test);
  //SoftSerial_Degub_println(F(" Cabina subiendo en AV "));
  //Cabina_BajarEnAV();
  //delay(delay_test);
  //SoftSerial_Degub_println(F("Detener Cabina "));
  //Cabina_Detener();
  //delay(delay_test);

}

/**
 * @brief Init modules of the board
 * 
 */
void Board_InitModules()
{
  MUX_Init();
  RELE_Init();
  OLED_Init();
}

void Board_ConfigModules()
{
  /*if (!jsonMod_verificarJson(StrJSONObject))
  {
    SoftSerial_Degub_println(F("Eror1: Confguracion JSON de la placa esta erronea"));
    while (true)
    {
      delay(1);
    }
  }*/
  
  char myChar;
  String StrJSONObject;
  // read back a char
  for (size_t k = 0; k < strlen_P(strConfInit); k++)
  {
    myChar =  pgm_read_byte_near(strConfInit + k);
    if( myChar != '\n' && myChar != ' ' ){
      StrJSONObject += myChar;
    }
    
  }
  SoftSerial_Degub_print("ConfigFile:");
    SoftSerial_Degub_println(StrJSONObject);
  
  char TIPO_CONTEO[20];
  char *titlePart[1] = { "TIPO_CONTEO" };
  JsonMod_FilterChar( StrJSONObject, &TIPO_CONTEO[0] , titlePart, 1 );
  SoftSerial_Degub_println("TIPO_CONTEO:");
  SoftSerial_Degub_print(TIPO_CONTEO);
  
  char NombrePlaca[20]; 
  char *titlePart3[1] = { "NombrePlaca" };
  JsonMod_FilterChar( StrJSONObject,  &NombrePlaca[0], titlePart3, 1 );
  SoftSerial_Degub_println("NombrePlaca:");
  SoftSerial_Degub_print(NombrePlaca);

  int TOTAL_PISOS;
  char *titlePart2[1] = { "TOTAL_PISOS" };
  JsonMod_FilterInt( StrJSONObject, &TOTAL_PISOS, titlePart2, 1 );
  SoftSerial_Degub_println("TOTAL_PISOS:");
  SoftSerial_Degub_print(TOTAL_PISOS);

  uint8_t modoConteoBandera = strcmp( TIPO_CONTEO , "PADPAS" ) == 0  ? PADPAS : PN;


  
  char* Modff[TOTAL_IO_MODULES_BOARD_CONFIG] = {"MB1","MB2","MB3","MB4","MB5","MB6","ME1","ME2","MS1","MS2"};
  uint8_t EspacioModulos[TOTAL_IO_MODULES_BOARD_CONFIG] = {8,8,8,8,8,8,8,8,8,8};

  enum internalOrderPins
  {
    posBand = 4,
    posSeg = 8,
    posAl = 16,
    posPuertas = 18
  };


  struct data_PinBackend data_mod_llamadas[48];
  struct data_PinBackend data_mod_Band[4];
  struct data_PinBackend data_mod_Seguridades[4];
  struct data_PinBackend data_mod_Alertas[8];
  struct data_PinBackend data_mod_Puertas[2];
  struct data_PinBackend data_mod_Cabinas[4];

  // struct data_PinBackend data_mod_PCF[16];
  // uint8_t countPCF = 0;
  uint16_t counterPos = 0;
  SoftSerial_Degub_println("EstrucTURA");
  for (uint8_t i = 0; i < TOTAL_IO_MODULES_BOARD_CONFIG; i++)
  {

    char *titlePart4[3] = { "ARCH",Modff[i], "PINNAME" };
    char PINNAME[8][10];
    JsonMod_FilterCharArray( StrJSONObject,  &PINNAME[0][0], 10, titlePart4, 3 );
    //SoftSerial_Degub_println("ARCH " + String(Modff[i]) +" PINNAME: ");
    
    //for (size_t i = 0; i < 8; i++)
    //{
    //  SoftSerial_Degub_println(PINNAME[i]);
    //}

    char *titlePart5[3] = { "ARCH", Modff[i], "VAL" };
    uint8_t Values[8];
    JsonMod_FilterIntArray( StrJSONObject,  Values, titlePart5, 3 );
    //SoftSerial_Degub_println("ARCH " + String(Modff[i]) +" VAL: ");
    //for (size_t i = 0; i < 8; i++)
    //{
    //  SoftSerial_Degub_println(Values[i]);
    //}

    for (uint8_t j = 0; j < EspacioModulos[i]; j++)
    {
      char* pinameStr = PINNAME[j] ;
      //strcpy( pinameStr, PINNAME[j] );
      //SoftSerial_Degub_println("pinameStr:" + String(pinameStr)  );
      if (strcmp(pinameStr , "" ) != 0)
      {
        for (uint8_t k = 0; k < TOTAL_PINS_BOARD_CONFIG ; k++)
        {
          if (  String(CongfPinsStr[k]) == String(pinameStr  ) 
            &&  String(CongfPinsStr[k]) != "VENT"
            &&  String(CongfPinsStr[k]) != "PATIN" /*strcmp( CongfPinsStr[k] ,pinameStr ) == 0*/ )
          {
            uint8_t pinameVal = Values[j];
            //SoftSerial_Degub_println("pinameVal:" + String(pinameVal)  );
            uint8_t PosicionEnPlaca = counterPos;
            struct data_PinBackend prov_data_mod;
            
            if (k < 4)
            {
              data_mod_Band[k].ModuloDevice = Board_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Band[k].PosicionPlaca = PosicionEnPlaca;
              //strcpy( data_mod_Band[k].nombrePin, pinameStr );
              data_mod_Band[k].EstadoPin= pinameVal >0 ;
              data_mod_Band[k].nombrePin = CongfPinsStr[k];
              prov_data_mod = data_mod_Band[k];
            }
            else if (k < 8 && k >= 4)
            {
              data_mod_Seguridades[k - posBand].ModuloDevice = Board_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Seguridades[k - posBand].PosicionPlaca = PosicionEnPlaca;
              //strcpy( data_mod_Seguridades[k - posBand].nombrePin, pinameStr );
              data_mod_Seguridades[k - posBand].nombrePin = CongfPinsStr[k];
              data_mod_Seguridades[k - posBand].EstadoPin= pinameVal >0 ;
              //data_mod_Seguridades[k].available = false;
              prov_data_mod = data_mod_Seguridades[k - posBand];
            }
            else if (k < 16 && k >= 8)
            {
              data_mod_Alertas[k - posSeg].ModuloDevice = Board_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Alertas[k - posSeg].PosicionPlaca = PosicionEnPlaca;
              //strcpy( data_mod_Alertas[k - posSeg].nombrePin, pinameStr );
              data_mod_Alertas[k - posSeg].nombrePin = CongfPinsStr[k];
              data_mod_Alertas[k - posSeg].EstadoPin= pinameVal >0 ;
              //data_mod_Alertas[k - posSeg].available = false;
              prov_data_mod = data_mod_Alertas[k - posSeg];
            }
            else if (k < 22 && k >= 20)
            {
              data_mod_Puertas[k - 20].ModuloDevice = Board_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Puertas[k - 20].PosicionPlaca = PosicionEnPlaca;
              //strcpy( data_mod_Puertas[k - 20].nombrePin, pinameStr );
              data_mod_Puertas[k - 20].nombrePin = CongfPinsStr[k];
              data_mod_Puertas[k - 20].EstadoPin= pinameVal >0 ;
              //data_mod_Puertas[k - 20].available = false;
              prov_data_mod = data_mod_Puertas[k - 20];
            }
            else if (k < 20 && k >= 16)
            {
              data_mod_Cabinas[k - 16].ModuloDevice = Board_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_Cabinas[k - 16].PosicionPlaca = PosicionEnPlaca;
              data_mod_Cabinas[k - 16].EstadoPin= pinameVal >0 ;
              //strcpy( data_mod_Cabinas[k - 16].nombrePin, pinameStr );
              data_mod_Cabinas[k - 16].nombrePin = CongfPinsStr[k];
              //data_mod_Cabinas[k - 16].available = false;
              prov_data_mod = data_mod_Cabinas[k - 16];
            }
            else if (k < 40 && k >= 24)
            {
              String NombrePin = CongfPinsStr[k] ;
              data_mod_llamadas[k - 24].ModuloDevice = Board_VerificarModuloSegunPosicion(PosicionEnPlaca);
              data_mod_llamadas[k - 24].PosicionPlaca = PosicionEnPlaca;
              data_mod_llamadas[k - 24].EstadoPin= pinameVal >0 ;
              data_mod_llamadas[k - 24].disponible =  true;
              //strcpy( data_mod_llamadas[k - 24].nombrePin, pinameStr );
              data_mod_llamadas[k - 24].nombrePin = CongfPinsStr[k];
              prov_data_mod = data_mod_llamadas[k - 24];
            }
            SoftSerial_Degub_print( "K: ");
            SoftSerial_Degub_print( k);
            SoftSerial_Degub_print( " , ");
            SoftSerial_Degub_print( "PosicionPlaca: ");
            SoftSerial_Degub_print(String( prov_data_mod.PosicionPlaca ));
            SoftSerial_Degub_print(" , NombrePin: ");
            SoftSerial_Degub_print( prov_data_mod.nombrePin );
            String deviceName = ( prov_data_mod.ModuloDevice == RELE595_MOD)?"595":( prov_data_mod.ModuloDevice == MUXINP_MOD)?"MUCINP":"MUXBID";
            SoftSerial_Degub_print( "Device:" );
            SoftSerial_Degub_print( deviceName );
            SoftSerial_Degub_print(", Pos:" );
            SoftSerial_Degub_print(String(  prov_data_mod.PosicionPlaca) );
            deviceName = ( prov_data_mod.EstadoPin )?"ON":"OFF";
            SoftSerial_Degub_print(", Estado:");
            SoftSerial_Degub_println( deviceName  );

            break;
          }
          
        }
      }
      counterPos++;
    }
  }
  while(Serial.available() > 0) {
    char t = Serial.read();
  }

  //while (true)
  //{
  //  delay(3000);
  //  SoftSerial_Degub_println("Prueba Serial2");
  //  Serial.println("Prueba Serial");
  //}

  SoftSerial_Degub_println( "Banderas" );
  Banderas_Init(data_mod_Band, 4, modoConteoBandera);
  SoftSerial_Degub_println( "Seguridades" );
  Seguridades_Init(data_mod_Seguridades, 4);
  SoftSerial_Degub_println( "Alertas" );
  Alertas_Init(data_mod_Alertas, 8);
  SoftSerial_Degub_println( "Puertas"  );
  Puertas_Init(data_mod_Puertas, 2);
  SoftSerial_Degub_println( "Cabinas" );
  Cabinas_Init(data_mod_Cabinas, 4);
  SoftSerial_Degub_println( "Llamadas"  );
  Llamadas_Init( data_mod_llamadas, 16 );

  while (true)
  {
    Board_TestExamples();
  }/**/
  
}


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
