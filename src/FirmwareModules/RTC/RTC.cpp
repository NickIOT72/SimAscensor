#include "RTC.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"
#include <RTClib.h>
#include <EEPROM.h>

RTC_DS3231 rtc;

struct RTC_data *RTC_System;


void RTC_saveInEEPROM(struct RTC_data * rtc_struct)
{
    EEPROM.write(2,rtc_struct->year/255);
    EEPROM.write(3,rtc_struct->year%255);
    EEPROM.write(4 , rtc_struct->month ) ;
    EEPROM.write(5 , rtc_struct->day) ;
    EEPROM.write(6, rtc_struct->hour);
    EEPROM.write(7,rtc_struct->minutes);
    EEPROM.write(8, rtc_struct->seconds);
}

void RTC_getFromEEPROM(struct RTC_data * rtc_struct)
{
    rtc_struct->year = EEPROM.read(2)*255 + EEPROM.read(3);
    rtc_struct->month = EEPROM.read(4);
    rtc_struct->day = EEPROM.read(5);
    rtc_struct->hour = EEPROM.read(6);
    rtc_struct->minutes = EEPROM.read(7);
    rtc_struct->day = EEPROM.read(8);
}

/**
 * @brief This function will init the RTC module
 * from position 1 to position 11 of the internal EEPROM will be saved the condition
 * pos 1 => save 1 or 0 if there is rtc saved on the EEPROM
 * pos 2-3 => save the year like ( 2 => 2022/255 & 3 => 2022%255 )
 * pos 4 => save moth
 * pos 5 => save day
 * pos 6 => save hour
 * pos 7 => save minutes
 * pos 8 => save seconds
 * 
 */
void RTC_Init()
{
    EEPROM.begin();
    if (!rtc.begin())
    {
        SoftSerial_Degub_println("Couldn't find RTC");
        while (1)
            delay(10);
    }

    if (rtc.lostPower())
    {
        SoftSerial_Degub_println("RTC lost power, let's set the time!");
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        bool readEEPROM = EEPROM.read(1);
        if(!readEEPROM)
        {
            rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        }
        RTC_getDateTime(RTC_System);
        
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }
}

void RTC_setDatetime(  struct RTC_data * rtc_struct )
{
    rtc.adjust(DateTime(rtc_struct->year,
        rtc_struct->month,
        rtc_struct->day, rtc_struct->hour, 
        rtc_struct->minutes, 
        rtc_struct->seconds));
    RTC_saveInEEPROM( rtc_struct );
}

void RTC_getDateTime(  struct RTC_data * rtc_struct )
{
    DateTime now = rtc.now();
    rtc_struct->year = now.year();
    rtc_struct->month = now.month();
    rtc_struct->day = now.day();
    rtc_struct->hour = now.hour();
    rtc_struct->minutes = now.minute();
    rtc_struct->seconds = now.second();
    RTC_saveInEEPROM( rtc_struct );
}