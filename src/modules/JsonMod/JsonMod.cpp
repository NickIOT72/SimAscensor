#include "JsonMod.h"
//#include "../../FirmwareModules/SoftSerial/SoftSerial.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"

SoftwareSerial DEGUB_SERIAL_JSONMOD(ESP_RX, ESP_TX);


StaticJsonDocument<300> filter;
StaticJsonDocument<300> doc;

void JsonMod_SerialInit()
{
    //Serial.begin(BAUD_SERIAL_FIRMWARE);
    DEGUB_SERIAL_JSONMOD.begin(9600);
    //BLE_SERIAL.begin( BAUD_SERIAL_BLE );
    //GSM_SERIAL.begin( BAUD_SERIAL_GSM );
}

void JsonMod_FilterIntArray(String NewJsonInit, uint8_t* variableStore, char* titleDta[], uint8_t elements )
{

        if( elements == 1 ) filter[titleDta[0]] = true;
        else if( elements == 2 )filter[titleDta[0]][titleDta[1]] = true;
        else if( elements == 3 )filter[titleDta[0]][titleDta[1]][titleDta[2]] = true;

        
        deserializeJson(doc, NewJsonInit, DeserializationOption::Filter(filter));

        JsonArray returnData;

        if( elements == 1 )returnData = doc[titleDta[0]];
        else if( elements == 2 )returnData = doc[titleDta[0]][titleDta[1]];
        else if( elements == 3 )returnData = doc[titleDta[0]][titleDta[1]][titleDta[2]];
    
        for (size_t i = 0; i < 8 ; i++)
        {
            variableStore[i] = returnData[i].as<uint8_t>();
        } 
        returnData.clear();

        //DEGUB_SERIAL_JSONMOD.println(F("Data json: "));
        serializeJson(doc, DEGUB_SERIAL_JSONMOD);

        jsonMod_limpiarJsonDoc(doc);

        jsonMod_limpiarJsonDoc(filter);

}

void JsonMod_FilterCharArray(String NewJsonInit, char *variableStore, uint8_t n_size, char *titleDta[], uint8_t elements)
{   

    if( elements == 1 ) filter[titleDta[0]] = true;
    else if( elements == 2 )filter[titleDta[0]][titleDta[1]] = true;
    else if( elements == 3 )filter[titleDta[0]][titleDta[1]][titleDta[2]] = true;

    deserializeJson(doc, NewJsonInit, DeserializationOption::Filter(filter));
    

    JsonArray strArray;

    if( elements == 1 )strArray = doc[titleDta[0]];
    else if( elements == 2 )strArray = doc[titleDta[0]][titleDta[1]];
    else if( elements == 3 )strArray = doc[titleDta[0]][titleDta[1]][titleDta[2]];
    

    for (size_t i = 0; i < 8; i++)
    {
        String sensor = strArray[i].as<String>();
        char sensorCh[ sensor.length() +1 ];
        sensor.toCharArray( sensorCh, sensor.length() +1  );
        for( int8_t j = 0 ; j < sensor.length() +1; j++ )
        {
         *( variableStore + i*n_size + j) = sensorCh[j];
        }
        //strcpy(variableStore[i], sensorCh);
        
        //SoftSerial_Degub_println(variableStore[i]);
    }

    //SoftSerial_Degub_println(F("Data json: "));
    //SoftSerial_Degub_println(returnData);
    //delay(2000);

    strArray.clear();

        //DEGUB_SERIAL_JSONMOD.println(F("Data json: "));
        //serializeJson(doc, DEGUB_SERIAL_JSONMOD);

        jsonMod_limpiarJsonDoc(doc);

        jsonMod_limpiarJsonDoc(filter);
}


void JsonMod_FilterCharArray(String NewJsonInit, char* variableStore[], char* titleDta[], uint8_t elements )
{

        if( elements == 1 ) filter[titleDta[0]] = true;
        else if( elements == 2 )filter[titleDta[0]][titleDta[1]] = true;
        else if( elements == 3 )filter[titleDta[0]][titleDta[1]][titleDta[2]] = true;

        
        deserializeJson(doc, NewJsonInit, DeserializationOption::Filter(filter));

        JsonArray returnData;

        if( elements == 1 )returnData = doc[titleDta[0]];
        else if( elements == 2 )returnData = doc[titleDta[0]][titleDta[1]];
        else if( elements == 3 )returnData = doc[titleDta[0]][titleDta[1]][titleDta[2]];
    
        for (size_t i = 0; i < 8 ; i++)
        {
            const char* sensor = returnData[i].as<char*>();
            strcpy( variableStore[i], sensor );
            
        } 
        returnData.clear();

        //DEGUB_SERIAL_JSONMOD.println(F("Data json: "));
        //serializeJson(doc, DEGUB_SERIAL_JSONMOD);

        jsonMod_limpiarJsonDoc(doc);

        jsonMod_limpiarJsonDoc(filter);

}

void JsonMod_FilterChar(String NewJsonInit, char* variableStore, char* titleDta[], uint8_t elements)
{
    // The filter: it contains "true" for each value we want to keep
    if( elements == 1 ) filter[titleDta[0]] = true;
    else if( elements == 2 )filter[titleDta[0]][titleDta[1]] = true;
    else if( elements == 3 )filter[titleDta[0]][titleDta[1]][titleDta[2]] = true;

    // Deserialize the document
    deserializeJson(doc, NewJsonInit, DeserializationOption::Filter(filter));
    ////DEGUB_SERIAL_JSONMOD.println(doc.memoryUsage());  // 16 on AVR
    char* returnData;

    if( elements == 1 ) strcpy( variableStore, doc[titleDta[0]]);
    else if( elements == 2 )strcpy( variableStore, doc[titleDta[0]][titleDta[1]]);
    else if( elements == 3 )strcpy( variableStore, doc[titleDta[0]][titleDta[1]][titleDta[2]]);

    //DEGUB_SERIAL_JSONMOD.println(F("Data json: "));
    //serializeJson(doc, DEGUB_SERIAL_JSONMOD);
    //DEGUB_SERIAL_JSONMOD.println(F("Data json char: "));
    //DEGUB_SERIAL_JSONMOD.println(variableStore);
    jsonMod_limpiarJsonDoc(doc);

    jsonMod_limpiarJsonDoc(filter);

}

void JsonMod_FilterInt(String NewJsonInit, int* valor, char* titleDta[], uint8_t elements)
{
    // The filter: it contains "true" for each value we want to keep
    if( elements == 1 ) filter[titleDta[0]] = true;
    else if( elements == 2 )filter[titleDta[0]][titleDta[1]] = true;
    else if( elements == 3 )filter[titleDta[0]][titleDta[1]][titleDta[2]] = true;

    // Deserialize the document
    deserializeJson(doc, NewJsonInit, DeserializationOption::Filter(filter));
    ////DEGUB_SERIAL_JSONMOD.println(doc.memoryUsage());  // 16 on AVR
    int returnData;

    if( elements == 1 )returnData = doc[titleDta[0]];
    else if( elements == 2 )returnData = doc[titleDta[0]][titleDta[1]];
    else if( elements == 3 )returnData = doc[titleDta[0]][titleDta[1]][titleDta[2]];

    *valor = returnData;

    ////DEGUB_SERIAL_JSONMOD.println(F("Data json: "));
    //serializeJson(doc, DEGUB_SERIAL_JSONMOD);
    
    jsonMod_limpiarJsonDoc(doc);

    jsonMod_limpiarJsonDoc(filter);

}

void JsonMod_FilterPrint(String NewJsonInit, JsonDocument &JSONObjectFilter, char* titleDta[], uint8_t elements)
{
    // The filter: it contains "true" for each value we want to keep

    // Deserialize the document
    deserializeJson(doc, NewJsonInit, DeserializationOption::Filter(JSONObjectFilter));
    
    JsonObject returnData;

    if( elements == 1 )returnData = doc[titleDta[0]];
    else if( elements == 2 )returnData = doc[titleDta[0]][titleDta[1]];
    else if( elements == 3 )returnData = doc[titleDta[0]][titleDta[1]][titleDta[2]];
    ////DEGUB_SERIAL_JSONMOD.println(returnData.memoryUsage());  // 16 on AVR
    ////DEGUB_SERIAL_JSONMOD.println(F("Data json: "));
    
    returnData.clear();

    //serializeJson(returnData, DEGUB_SERIAL_JSONMOD);
    ////DEGUB_SERIAL_JSONMOD.println(doc.memoryUsage());  // 16 on AVR
    jsonMod_limpiarJsonDoc(doc);

}





void jsonMod_Example()
{
    JsonMod_SerialInit();
    
    String input = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
    //if( jsonMod_verificarJson(input) ) ////DEGUB_SERIAL_JSONMOD.println(F("Json Funciona "));
  
  
}

bool jsonMod_verificarJson(String Str, JsonDocument &JSONObject )
{
    JSONObject.clear();
    char StrProvp[Str.length() + 1];
    Str.toCharArray(StrProvp, Str.length() + 1);

    ////DEGUB_SERIAL_JSONMOD.println(F("Data input json: "));
    ////DEGUB_SERIAL_JSONMOD.println(StrProvp);

    DeserializationError error2 = deserializeJson(JSONObject, StrProvp);
    if (error2)
    {
        ////DEGUB_SERIAL_JSONMOD.println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    ////DEGUB_SERIAL_JSONMOD.println(F("Data json: "));
    //serializeJson(JSONObject, DEGUB_SERIAL_JSONMOD);
    return true;
}

bool jsonMod_verificarJson(char* charjson, JsonDocument &JSONObject )
{
    JSONObject.clear();
    DeserializationError error2 = deserializeJson(JSONObject, charjson);
    if (error2)
    {
        ////DEGUB_SERIAL_JSONMOD.println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    ////DEGUB_SERIAL_JSONMOD.println(F("Data json: "));
    //serializeJson(JSONObject, DEGUB_SERIAL_JSONMOD);
    return true;
}




bool jsonMod_verificarJson(String Str )
{
    char StrProvp[Str.length() + 1];
    Str.toCharArray(StrProvp, Str.length() + 1);
    DynamicJsonDocument JSONObject(JSON_Buffer);
    DeserializationError error2 = deserializeJson(JSONObject, StrProvp);
    if (error2)
    {
        ////DEGUB_SERIAL_JSONMOD.println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    ////DEGUB_SERIAL_JSONMOD.println(F("Data json: "));
    JSONObject.garbageCollect();
    //serializeJson(JSONObject, DEGUB_SERIAL_JSONMOD);
    return true;
}

bool jsonMod_verificarJson(char* charjson )
{
    DynamicJsonDocument JSONObject(JSON_Buffer);
    DeserializationError error2 = deserializeJson(JSONObject, charjson);
    if (error2)
    {
        ////DEGUB_SERIAL_JSONMOD.println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    ////DEGUB_SERIAL_JSONMOD.println(F("Data json: "));
    JSONObject.garbageCollect();
    //serializeJson(JSONObject, DEGUB_SERIAL_JSONMOD);
    return true;
}

void jsonMod_liberarDinMemJsonDoc(DynamicJsonDocument &JsonObject)
{
    JsonObject.~BasicJsonDocument();
}

void jsonMod_limpiarJsonDoc(JsonDocument &JsonObject)
{
    JsonObject.clear();
}