#include "JsonMod.h"
#include "../../FirmwareModules/SoftSerial/SoftSerial.h"
#include "../../FirmwareModules/BoardArch.h"

// SoftwareSerial DEGUB_SERIAL_JSONMOD(DEBUG_RX, DEBUG_TX);
 

#if defined(ARDUINO_BLUEPILL_F103C8)


bool jsonMod_verificarJson(String Str)
{
    char StrProvp[Str.length() + 1];
    Str.toCharArray(StrProvp, Str.length() + 1);
    DynamicJsonBuffer jsonBuffer(JSON_Buffer);
    JsonVariant root = jsonBuffer.parseObject(StrProvp);
    if (root.is<JsonObject>())
    {
        // SoftSerial_Degub_println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    // SoftSerial_Degub_println(F("Data json: "));
    jsonMod_limpiarJsonDoc(jsonBuffer);
    jsonMod_liberarDinMemJsonDoc(jsonBuffer);
    // serializeJson(JSONObject, DEGUB_SERIAL_JSONMOD);
    return true;
}

bool jsonMod_verificarJson(char *json)
{
    DynamicJsonBuffer jsonBuffer(JSON_Buffer);
    JsonVariant root = jsonBuffer.parseObject(json);
    if (root.is<JsonObject>())
    {
        // SoftSerial_Degub_println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    // SoftSerial_Degub_println(F("Data json: "));
    jsonMod_limpiarJsonDoc(jsonBuffer);
    jsonMod_liberarDinMemJsonDoc(jsonBuffer);
    // serializeJson(JSONObject, DEGUB_SERIAL_JSONMOD);
    return true;
}

void jsonMod_liberarDinMemJsonDoc(DynamicJsonBuffer &JsonObject)
{
    JsonObject.~DynamicJsonBufferBase();
}

void JsonMod_FilterPrint(String NewJsonInit, JsonBuffer &JSONObjectFilter, char *titleDta[], uint8_t elements);

void JsonMod_SerialInit()
{
    // Serial.begin(BAUD_SERIAL_FIRMWARE);
    // Serial_2.begin(9600);
    // BLE_SERIAL.begin( BAUD_SERIAL_BLE );
    // GSM_SERIAL.begin( BAUD_SERIAL_GSM );
}

void JsonMod_FilterIntArray(String NewJsonInit, uint8_t *variableStore, char *titleDta[], uint8_t elements)
{
    StaticJsonBuffer<JSON_Buffer> doc;
    StaticJsonBuffer<500> filter;

    JsonObject& object = doc.parseObject(NewJsonInit);

    String returnData = "";

    if (elements == 1)
        returnData = object[titleDta[0]].as<String>();
    else if (elements == 2)
        returnData = object[titleDta[0]][titleDta[1]].as<String>();
    else if (elements == 3)
        returnData = object[titleDta[0]][titleDta[1]][titleDta[2]].as<String>();

    JsonArray& strArray = filter.parseArray( returnData );

    for (size_t i = 0; i < 8; i++)
    {
        variableStore[i] = strArray[i].as<uint8_t>();
    }

    //SoftSerial_Degub_println(F("Data json: "));
    //SoftSerial_Degub_println(returnData);
}

void JsonMod_FilterCharArray(String NewJsonInit, char *variableStore, uint8_t n_size, char *titleDta[], uint8_t elements)
{   
    StaticJsonBuffer<JSON_Buffer> doc;
    StaticJsonBuffer<500> filter;

    JsonObject& object = doc.parseObject(NewJsonInit);

    String returnData = "";
        //SoftSerial_Degub_println("NewJsonInit:");
    //SoftSerial_Degub_println(NewJsonInit);

    if (elements == 1)
        returnData = object[titleDta[0]].as<String>();
    else if (elements == 2)
        returnData = object[titleDta[0]][titleDta[1]].as<String>();
    else if (elements == 3)
        returnData = object[titleDta[0]][titleDta[1]][titleDta[2]].as<String>();

    //SoftSerial_Degub_println("returnData:");
    //SoftSerial_Degub_println(returnData);
    
    JsonArray& strArray = filter.parseArray( returnData );

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
}

void JsonMod_FilterChar(String NewJsonInit, char *variableStore, char *titleDta[], uint8_t elements)
{
    //DynamicJsonBuffer doc(JSON_Buffer);

    char jsonch[ NewJsonInit.length() +1 ];
    NewJsonInit.toCharArray( jsonch, NewJsonInit.length() +1 );

    StaticJsonBuffer<JSON_Buffer> doc;
    JsonObject& object = doc.parseObject(jsonch);

    String returnData = "";

    if (elements == 1)
        returnData = object[titleDta[0]].as<String>();
    else if (elements == 2)
        returnData = object[titleDta[0]][titleDta[1]].as<String>();
    else if (elements == 3)
        returnData = object[titleDta[0]][titleDta[1]][titleDta[2]].as<String>();
    
    char strArray[ returnData.length() + 1];
    returnData.toCharArray( strArray,   returnData.length() + 1  );
    for( int i = 0; i < returnData.length() + 1; i++ )
    {
        *(variableStore+i) = strArray[i];
    }
    
    
    //strcpy( variableStore , strArray );

    //SoftSerial_Degub_println(F("Data json: "));
    //SoftSerial_Degub_println(returnData);

    //jsonMod_liberarDinMemJsonDoc(doc);

}

void JsonMod_FilterInt(String NewJsonInit, int *valor, char *titleDta[], uint8_t elements)
{
   StaticJsonBuffer<JSON_Buffer> doc;

    JsonObject& object = doc.parseObject(NewJsonInit);

    String returnData = "";

    if (elements == 1)
        returnData = object[titleDta[0]].as<String>();
    else if (elements == 2)
        returnData = object[titleDta[0]][titleDta[1]].as<String>();
    else if (elements == 3)
        returnData = object[titleDta[0]][titleDta[1]][titleDta[2]].as<String>();

    *valor = returnData.toInt();


    //SoftSerial_Degub_println(F("Data json: "));
    //SoftSerial_Degub_println(returnData);
}



#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega644A__) || defined(ESP8266)

StaticJsonDocument<500> filter;
StaticJsonDocument<500> doc;

void jsonMod_Example()
{
    JsonMod_SerialInit();

    String input = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
    // if( jsonMod_verificarJson(input) ) //SoftSerial_Degub_println(F("Json Funciona "));
}

bool jsonMod_verificarJson(String Str, JsonDocument &JSONObject)
{
    JSONObject.clear();
    char StrProvp[Str.length() + 1];
    Str.toCharArray(StrProvp, Str.length() + 1);

    // SoftSerial_Degub_println(F("Data input json: "));
    // SoftSerial_Degub_println(StrProvp);

    DeserializationError error2 = deserializeJson(JSONObject, StrProvp);
    if (error2)
    {
        // SoftSerial_Degub_println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    // SoftSerial_Degub_println(F("Data json: "));
    // serializeJson(JSONObject, DEGUB_SERIAL_JSONMOD);
    return true;
}

bool jsonMod_verificarJson(char *charjson, JsonDocument &JSONObject)
{
    JSONObject.clear();
    DeserializationError error2 = deserializeJson(JSONObject, charjson);
    if (error2)
    {
        // SoftSerial_Degub_println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    // SoftSerial_Degub_println(F("Data json: "));
    // serializeJson(JSONObject, DEGUB_SERIAL_JSONMOD);
    return true;
}

bool jsonMod_verificarJson(String Str)
{
    char StrProvp[Str.length() + 1];
    Str.toCharArray(StrProvp, Str.length() + 1);
    DynamicJsonDocument JSONObject(JSON_Buffer);
    DeserializationError error2 = deserializeJson(JSONObject, StrProvp);
    if (error2)
    {
        // SoftSerial_Degub_println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    // SoftSerial_Degub_println(F("Data json: "));
    JSONObject.garbageCollect();
    // serializeJson(JSONObject, DEGUB_SERIAL_JSONMOD);
    return true;
}

bool jsonMod_verificarJson(char *charjson)
{
    DynamicJsonDocument JSONObject(JSON_Buffer);
    DeserializationError error2 = deserializeJson(JSONObject, charjson);
    if (error2)
    {
        // SoftSerial_Degub_println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    // SoftSerial_Degub_println(F("Data json: "));
    JSONObject.garbageCollect();
    // serializeJson(JSONObject, DEGUB_SERIAL_JSONMOD);
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

void JsonMod_FilterPrint(String NewJsonInit, JsonDocument &JSONObjectFilter, char *titleDta[], uint8_t elements)
{
    // The filter: it contains "true" for each value we want to keep

    // Deserialize the document
    deserializeJson(doc, NewJsonInit, DeserializationOption::Filter(JSONObjectFilter));

    JsonObject returnData;

    if (elements == 1)
        returnData = doc[titleDta[0]];
    else if (elements == 2)
        returnData = doc[titleDta[0]][titleDta[1]];
    else if (elements == 3)
        returnData = doc[titleDta[0]][titleDta[1]][titleDta[2]];
    // SoftSerial_Degub_println(returnData.memoryUsage());  // 16 on AVR
    // SoftSerial_Degub_println(F("Data json: "));

    returnData.clear();

    // serializeJson(returnData, DEGUB_SERIAL_JSONMOD);
    // SoftSerial_Degub_println(doc.memoryUsage());  // 16 on AVR
    jsonMod_limpiarJsonDoc(doc);
}

void JsonMod_SerialInit()
{
    // Serial.begin(BAUD_SERIAL_FIRMWARE);
    // DEGUB_SERIAL_JSONMOD.begin(9600);
    // BLE_SERIAL.begin( BAUD_SERIAL_BLE );
    // GSM_SERIAL.begin( BAUD_SERIAL_GSM );
}

void JsonMod_FilterIntArray(String NewJsonInit, uint8_t *variableStore, char *titleDta[], uint8_t elements)
{

    if (elements == 1)
        filter[titleDta[0]] = true;
    else if (elements == 2)
        filter[titleDta[0]][titleDta[1]] = true;
    else if (elements == 3)
        filter[titleDta[0]][titleDta[1]][titleDta[2]] = true;

    deserializeJson(doc, NewJsonInit, DeserializationOption::Filter(filter));

    JsonArray returnData;

    if (elements == 1)
        returnData = doc[titleDta[0]];
    else if (elements == 2)
        returnData = doc[titleDta[0]][titleDta[1]];
    else if (elements == 3)
        returnData = doc[titleDta[0]][titleDta[1]][titleDta[2]];

    for (size_t i = 0; i < 8; i++)
    {
        variableStore[i] = returnData[i].as<uint8_t>();
    }
    returnData.clear();

    String jSONData = "";
    SoftSerial_Degub_println(F("Data json: "));
    serializeJson(doc, jSONData);
    SoftSerial_Degub_println(jSONData);

    jsonMod_limpiarJsonDoc(doc);

    jsonMod_limpiarJsonDoc(filter);
}

void JsonMod_FilterCharArray(String NewJsonInit, char *variableStore, uint8_t n_size, char *titleDta[], uint8_t elements)
{   
    if (elements == 1)
        filter[titleDta[0]] = true;
    else if (elements == 2)
        filter[titleDta[0]][titleDta[1]] = true;
    else if (elements == 3)
        filter[titleDta[0]][titleDta[1]][titleDta[2]] = true;

    deserializeJson(doc, NewJsonInit, DeserializationOption::Filter(filter));

    JsonArray returnData;

    if (elements == 1)
        returnData = doc[titleDta[0]];
    else if (elements == 2)
        returnData = doc[titleDta[0]][titleDta[1]];
    else if (elements == 3)
        returnData = doc[titleDta[0]][titleDta[1]][titleDta[2]];

    for (size_t i = 0; i < 8; i++)
    {
        String sensor = returnData[i].as<String>();
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
}

void JsonMod_FilterChar(String NewJsonInit, char *variableStore, char *titleDta[], uint8_t elements)
{
    // The filter: it contains "true" for each value we want to keep
    if (elements == 1)
        filter[titleDta[0]] = true;
    else if (elements == 2)
        filter[titleDta[0]][titleDta[1]] = true;
    else if (elements == 3)
        filter[titleDta[0]][titleDta[1]][titleDta[2]] = true;

    // Deserialize the document
    deserializeJson(doc, NewJsonInit, DeserializationOption::Filter(filter));
    // SoftSerial_Degub_println(doc.memoryUsage());  // 16 on AVR
    char *returnData;

    if (elements == 1)
        strcpy(variableStore, doc[titleDta[0]].as<char *>());
    else if (elements == 2)
        strcpy(variableStore, doc[titleDta[0]][titleDta[1]].as<char *>());
    else if (elements == 3)
        strcpy(variableStore, doc[titleDta[0]][titleDta[1]][titleDta[2]].as<char *>());

    String jSONData = "";
    SoftSerial_Degub_println(F("Data json: "));
    serializeJson(doc, jSONData);
    SoftSerial_Degub_println(jSONData);

    jsonMod_limpiarJsonDoc(doc);

    jsonMod_limpiarJsonDoc(filter);
}

void JsonMod_FilterInt(String NewJsonInit, int *valor, char *titleDta[], uint8_t elements)
{
    // The filter: it contains "true" for each value we want to keep
    if (elements == 1)
        filter[titleDta[0]] = true;
    else if (elements == 2)
        filter[titleDta[0]][titleDta[1]] = true;
    else if (elements == 3)
        filter[titleDta[0]][titleDta[1]][titleDta[2]] = true;

    // Deserialize the document
    deserializeJson(doc, NewJsonInit, DeserializationOption::Filter(filter));
    // SoftSerial_Degub_println(doc.memoryUsage());  // 16 on AVR
    int returnData;

    if (elements == 1)
        returnData = doc[titleDta[0]];
    else if (elements == 2)
        returnData = doc[titleDta[0]][titleDta[1]];
    else if (elements == 3)
        returnData = doc[titleDta[0]][titleDta[1]][titleDta[2]];

    *valor = returnData;

    // SoftSerial_Degub_println(F("Data json: "));
    // serializeJson(doc, DEGUB_SERIAL_JSONMOD);

    jsonMod_limpiarJsonDoc(doc);

    jsonMod_limpiarJsonDoc(filter);
}



#endif
