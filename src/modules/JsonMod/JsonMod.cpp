#include "JsonMod.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"

SoftwareSerial ESP_SERIAL_JSON(ESP_RX, ESP_TX);

bool jsonMod_verificarJson(String Str, JsonDocument &JSONObject )
{
    ESP_SERIAL_JSON.begin(BAUD_SERIAL);
    ESP_SERIAL_JSON.println("J1:");
    ESP_SERIAL_JSON.println(Str.length() + 1);
    char StrProvp[Str.length() + 1];
    Str.toCharArray(StrProvp, Str.length() + 1);

    DeserializationError error2 = deserializeJson(JSONObject, StrProvp);
    if (error2)
    {
        ESP_SERIAL_JSON.println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    ESP_SERIAL_JSON.println("Data json: ");
    serializeJson(JSONObject, ESP_SERIAL_JSON);
    return true;
}

bool jsonMod_verificarJson(char* charjson, JsonDocument &JSONObject )
{
    ESP_SERIAL_JSON.begin(BAUD_SERIAL);
    ESP_SERIAL_JSON.println("J2:");
    DeserializationError error2 = deserializeJson(JSONObject, charjson);
    if (error2)
    {
        ESP_SERIAL_JSON.println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    ESP_SERIAL_JSON.println("Data json: ");
    serializeJson(JSONObject, ESP_SERIAL_JSON);
    return true;
}

bool jsonMod_verificarJson(String Str )
{
    ESP_SERIAL_JSON.begin(BAUD_SERIAL);
    ESP_SERIAL_JSON.println("J3:");
    char StrProvp[Str.length() + 1];
    Str.toCharArray(StrProvp, Str.length() + 1);
    DynamicJsonDocument JSONObject(JSON_Buffer);
    DeserializationError error2 = deserializeJson(JSONObject, StrProvp);
    if (error2)
    {
        ESP_SERIAL_JSON.println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    ESP_SERIAL_JSON.println("Data json: ");
    serializeJson(JSONObject, ESP_SERIAL_JSON);
    return true;
}

bool jsonMod_verificarJson(char* charjson )
{
    ESP_SERIAL_JSON.begin(BAUD_SERIAL);
    ESP_SERIAL_JSON.println("J4:");
    DynamicJsonDocument JSONObject(JSON_Buffer);
    DeserializationError error2 = deserializeJson(JSONObject, charjson);
    if (error2)
    {
        ESP_SERIAL_JSON.println("DeserializeJson() for f2b message failed: " + String(error2.c_str()));
        return false;
    }
    ESP_SERIAL_JSON.println("Data json: ");
    serializeJson(JSONObject, ESP_SERIAL_JSON);
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