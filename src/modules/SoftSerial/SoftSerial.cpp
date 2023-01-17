#include "SoftSerial.h"
#include "../../FirmwareModules/BoardArch.h"


// VARIABLES USE TO ALLOW SERIAL PRINTING
bool ALLOW_DEGUB_SERIAL = true; 
bool ALLOW_BLE_SERIAL = false; 
bool ALLOW_GSM_SERIAL = false; 

/**
 * @brief Configure Serial ports accroding to board architecture
 * 
 */

#if defined(__AVR_ATmega644A__) 

HardwareSerial & DEGUB_SERIAL = Serial1;
SoftwareSerial BLE_SERIAL(BLE_RX, BLE_TX);
SoftwareSerial GSM_SERIAL(GSM_RX, GSM_TX);

#elif defined(__AVR_ATmega2560__)

HardwareSerial & DEGUB_SERIAL = Serial1;
HardwareSerial & BLE_SERIAL = Serial2;
HardwareSerial & GSM_SERIAL = Serial3;


#elif defined(ARDUINO_BLUEPILL_F103C8)

HardwareSerial DEGUB_SERIAL(USART2);

#endif

/**
 * @brief Initialize Seria ports according with the Init Conditions
 * 
 */

void SoftSerial_IniModules()
{
    Serial.begin(BAUD_SERIAL_FIRMWARE);
    if(ALLOW_DEGUB_SERIAL)
        DEGUB_SERIAL.begin(BAUD_SERIAL_DEGUB);
    if(ALLOW_BLE_SERIAL)
        BLE_SERIAL.begin(BAUD_SERIAL_DEGUB);
    if(ALLOW_GSM_SERIAL)
        GSM_SERIAL.begin(BAUD_SERIAL_DEGUB);
}

/**
 * @brief Funtions reserved for STM32 mdev borad to print json data
 * 
 */
#if defined(ARDUINO_BLUEPILL_F103C8)

void SoftSerial_Degub_print( JsonArray &jsonArray )
{
    jsonArray.printTo(Serial2);
}

void SoftSerial_Degub_print( JsonObject &jsonObj )
{
    jsonObj.printTo(Serial2);
}

#endif

void SoftSerial_Degub_print(String Str)
{
    DEGUB_SERIAL.print(Str);
}

void SoftSerial_Degub_print(const char *Str)
{
    DEGUB_SERIAL.print(Str);
}

void SoftSerial_Degub_print(int num, int type = DEC)
{
    DEGUB_SERIAL.print(num, type);
}

void SoftSerial_Degub_print(float num)
{
    DEGUB_SERIAL.print(num);
}

void SoftSerial_Degub_print(double num)
{
    DEGUB_SERIAL.print(num);
}

void SoftSerial_Degub_print(unsigned long num, int type = DEC)
{
    DEGUB_SERIAL.println(num, type);
}

void SoftSerial_Degub_print(long num, int type = DEC)
{
    DEGUB_SERIAL.println(num, type);
}

void SoftSerial_Degub_println(String Str)
{
    DEGUB_SERIAL.println(Str);
}

void SoftSerial_Degub_println(const char *Str)
{
    DEGUB_SERIAL.println(Str);
}

void SoftSerial_Degub_println(int num, int type)
{
    DEGUB_SERIAL.println(num, type);
}

void SoftSerial_Degub_println(unsigned long num, int type)
{
    DEGUB_SERIAL.println(num, type);
}

void SoftSerial_Degub_println(long num, int type)
{
    DEGUB_SERIAL.println(num, type);
}

void SoftSerial_Degub_println(float num)
{
    DEGUB_SERIAL.println(num);
}

void SoftSerial_Degub_println(double num)
{
    DEGUB_SERIAL.println(num);
}

