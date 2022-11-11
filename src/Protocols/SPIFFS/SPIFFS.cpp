#include "./SPIFFS.h"
#if defined(ESP8266)
    #include "FS.h"
#endif

#include "../SoftSerial/SoftSerial.h"

SoftwareSerial ESP_SERIAL_SPIFFS(ESP_RX, ESP_TX);

#if defined(ESP8266)

    void SPIFFS_InitSPIFFS()
    {
        if (!SPIFFS.begin())
        {
            ESP_SERIAL_SPIFFS.println("An Error has occurred while mounting SPIFFS");
            while (true)
            {
                delay(1);
            }
            
        }
    }

    void SPIFFS_printFiles()
    {
        ESP_SERIAL_SPIFFS.println("List of Files");
        Dir dir = SPIFFS.openDir("");
        while (dir.next())
        {
            ESP_SERIAL_SPIFFS.print(dir.fileName());
            ESP_SERIAL_SPIFFS.print(" ");
            ESP_SERIAL_SPIFFS.println(dir.fileSize());
        }
    }

    void SPIFFS_DeleteFile(String path)
    {
        if( SPIFFS.remove(path) )
        {
            ESP_SERIAL_SPIFFS.println("File \"" + path + "\"removed succesfully");
        }
        else
        {
            ESP_SERIAL_SPIFFS.println("File \"" + path + "\"not found or doesn't exist");
            ESP_SERIAL_SPIFFS.println("Available Files");
            SPIFFS_printFiles();
        }

    }

    void SPIFFS_CreateFile(String path)
    {
        File file = SPIFFS.open(path, "w");
        if (!file)
        {
            ESP_SERIAL_SPIFFS.println("There was an error opening the file(" + path + ") for writing");
            return;
        }
        file.close();
    }

    void SPIFFS_AppendFile(String path, String data)
    {
        File file = SPIFFS.open(path, "a");
        if (!file)
        {
            ESP_SERIAL_SPIFFS.println("There was an error opening the file(" + path + ") for appending");
            return;
        }
        if (file.print(data))
        {
            ESP_SERIAL_SPIFFS.println("File was appended");
        }
        else
        {
            ESP_SERIAL_SPIFFS.println("File write failed");
        }

        file.close();
        String FileRead = SPIFFS_ReadFile(path);
        ESP_SERIAL_SPIFFS.println("File Info: " + FileRead);
    }

    void SPIFFS_UpdateFile(String path, String data)
    {
        File file = SPIFFS.open(path, "w");
        if (!file)
        {
            ESP_SERIAL_SPIFFS.println("There was an error opening the file(" + path + ") for writing");
            return;
        }
        if (file.print(data))
        {
            ESP_SERIAL_SPIFFS.println("File was written");
        }
        else
        {
            ESP_SERIAL_SPIFFS.println("File write failed");
        }

        file.close();
        String FileRead = SPIFFS_ReadFile(path);
        ESP_SERIAL_SPIFFS.println("File Info: " + FileRead);
    }

    String SPIFFS_ReadFile(String path)
    {
        File file3 = SPIFFS.open(path, "r");
        if (!file3)
        {
            ESP_SERIAL_SPIFFS.println("Failed to open file for reading");
            return "";
        }
        ESP_SERIAL_SPIFFS.println("File Content:");
        String FileToSend = "";
        while (file3.available())
        {
            FileToSend += String(char(file3.read()));
        }
        file3.close();
        ESP_SERIAL_SPIFFS.println(FileToSend);
        return FileToSend;
    }

#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    
#endif