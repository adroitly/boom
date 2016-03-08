//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================
#ifndef __LIBRA_SAFE_H__
#define __LIBRA_SAFE_H__

#include "libra_config.h"
#include <stdio.h>
#include <stdarg.h>

#ifdef _MSC_VER

static libra_inline FILE* libra_fopen(const char* filename, const char* mode)
{
    FILE* file = NULL;
    errno_t error = fopen_s(&file, filename, mode);
    return (error == 0) ? file : NULL;
}

static libra_inline int libra_vsnprintf(char* buf,
                                        size_t max_size,
                                        const char* format,
                                        va_list vlist)
{
    return vsnprintf_s(buf, max_size, _TRUNCATE, format, vlist);
}

#else

static libra_inline FILE* libra_fopen(const char* filename, const char* mode)
{
    return fopen(filename, mode);
}

static libra_inline int libra_vsnprintf(char* buf,
                                        size_t max_size,
                                        const char* format,
                                        va_list vlist)
{
    return vsnprintf(buf, max_size, format, vlist);
}

#endif

#endif
