#ifndef _RTC_H
#define _RTC_H

#include <Arduino.h>

struct RTC_data
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minutes;
    uint8_t seconds;
};

void RTC_Init( );
void RTC_setDatetime(  struct RTC_data * rtc_struct );
void RTC_getDateTime(  struct RTC_data * rtc_struct );

#endif // !_RTC_H