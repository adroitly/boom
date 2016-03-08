//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "libra_date.h"
#include <stdint.h>

int libra_days_in_month(int month, bool is_leap_year)
{
    static uint8_t dasy[] = {
        0,   // 0
        31,  // 1
        28,  // 2
        31,  // 3
        30,  // 4
        31,  // 5
        30,  // 6
        31,  // 7
        31,  // 8
        30,  // 9
        31,  // 10
        30,  // 11
        31,  // 12
    };
    if (month == 2 && is_leap_year)
    {
        return 29;
    }
    return dasy[month];
}

bool libra_is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

libra_time_formatted libra_format_seconds(long seconds)
{
    libra_time_formatted formatTime;
    const int seconds_per_minute = 60;
    const int seconds_per_hour = seconds_per_minute * 60;
    const int seconds_per_day = seconds_per_hour * 24;

    formatTime.day = ((int)seconds / seconds_per_day);
    seconds -= seconds_per_hour * formatTime.day;

    formatTime.hour = ((int)seconds / seconds_per_hour);
    seconds -= seconds_per_hour * formatTime.hour;

    formatTime.minute = ((int)seconds / seconds_per_minute);
    seconds -= seconds_per_minute * formatTime.minute;

    formatTime.second = (int)seconds;
    return formatTime;
}
