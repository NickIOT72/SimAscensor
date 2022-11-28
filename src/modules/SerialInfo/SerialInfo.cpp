#include "SerialInfo.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"

SoftwareSerial ESP_SERIAL_SI(ESP_RX_SI, ESP_TX_SI);
SoftwareSerial ESP_SERIAL_SI2(ESP_RX, ESP_TX);

void SerialInfo_Init()
{
    #if defined(ESP8266)
        #if defined(ESP_HARDWARE_SERIAL)
            Serial.begin(BAUDRATE_SERIALINFO);
        #else
            ESP_SERIAL_SI.begin(BAUDRATE_SERIALINFO);
        #endif // ESP_HARDWARE_SERIAL
        
    #elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
        ESP_SERIAL_SI.begin(BAUDRATE_SERIALINFO);
    #endif
    ESP_SERIAL_SI2.begin(BAUD_SERIAL);
}

void SerialInfo_LeerUARTdata()
{
    static String buff = "";

    #if defined(ESP8266)
        #if defined(ESP_HARDWARE_SERIAL)
            if ( Serial.available() > 0 )
            {
                while (Serial.available() > 0)
                {
                    String buff2 = String(char(Serial.read()));
                    if( buff2 == "!" )
                    {
                      break;
                    }
                    else{
                      buff += buff2;
                    }
                }
            }
        #else
            if ( ESP_SERIAL_SI.available() > 0 )
            {
                while (ESP_SERIAL_SI.available() > 0)
                {
                    String buff2 = String(char(ESP_SERIAL_SI.read()));
                    if( buff2 == "!" )
                    {
                      break;
                    }
                    else{
                      buff += buff2;
                    }
                }
            }
        #endif // ESP_HARDWARE_SERIAL
    #elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
        if ( ESP_SERIAL_SI.available() > 0 )
        {
            while (ESP_SERIAL_SI.available() > 0)
            {
                String buff2 = String(char(ESP_SERIAL_SI.read()));
                if( buff2 == "!" )
                {
                  break;
                }
                else{
                  buff += buff2;
                }
            }
        }
    #endif
}

void SerialInfo_SendDataToMega(String FileSend)
{
    char buffSerial[FileSend.length() + 1];
    FileSend.toCharArray(buffSerial, FileSend.length() + 1);
    #if defined(ESP8266)
        #if defined(ESP_HARDWARE_SERIAL)
            for (int i = 0; i < FileSend.length() + 1; i++)
            {
                Serial.write(buffSerial[i]);
                if (i % 10 == 0)
                {
                    delay(10);
                }
            }
            Serial.write("!");
        #else
            for (int i = 0; i < FileSend.length() + 1; i++)
            {
                ESP_SERIAL_SI.write(buffSerial[i]);
                if (i % 10 == 0)
                {
                    delay(10);
                }
            }
            ESP_SERIAL_SI.write("!");
        #endif // ESP_HARDWARE_SERIAL
    
    #elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
        for (int i = 0; i < FileSend.length() + 1; i++)
        {
            ESP_SERIAL_SI.write(buffSerial[i]);
            if (i % 10 == 0)
            {
                delay(1);
            }
        }
        ESP_SERIAL_SI.write("!");
        
    #endif
    ESP_SERIAL_SI2.print(FileSend);
}
