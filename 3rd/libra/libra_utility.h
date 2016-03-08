//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __LIBRA_UTILITY_H__
#define __LIBRA_UTILITY_H__

#include "libra_config.h"
#include <string.h>

namespace libra
{
    inline bool is_big_endian()
    {
        union
        {
            short s;
            char c[sizeof(short)];
        } un;
        un.s = 0x0102;
        return un.c[0] == 1;
    }

    inline bool is_little_endian()
    {
        return !is_big_endian();
    }

    inline void bzero(void* buffer, size_t size)
    {
        memset(buffer, 0, size);
    }
}

libra_extern void libra_uuid_generate(unsigned char result[16]);

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#endif
