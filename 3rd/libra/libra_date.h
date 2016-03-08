//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __LIBRA_DATE_H__
#define __LIBRA_DATE_H__

#include "libra_config.h"

libra_extern int libra_days_in_month(int month, bool is_leap_year);
libra_extern bool libra_is_leap_year(int year);

typedef struct
{
    int day;
    int hour;
    int minute;
    int second;
} libra_time_formatted;

// 计算秒数，等于多少天，多少小时，多少分钟，多少秒
libra_extern libra_time_formatted libra_format_seconds(long seconds);

#endif
