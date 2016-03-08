//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __LIBRA_HEX_H__
#define __LIBRA_HEX_H__

#include "libra_config.h"

/*
 * The functions and macros in this file is from Linux Kernel
 * (include/linux/kernel.h)
 */

extern const char hex_asc[];
extern const char hex_asc_upper[];

#define hex_asc_lo(x) hex_asc[((x)&0x0f)]
#define hex_asc_hi(x) hex_asc[((x)&0xf0) >> 4]

#define hex_asc_upper_lo(x) hex_asc_upper[((x)&0x0f)]
#define hex_asc_upper_hi(x) hex_asc_upper[((x)&0xf0) >> 4]

static libra_inline char* hex_byte_pack(char* buf, uint8_t byte)
{
    *buf++ = hex_asc_hi(byte);
    *buf++ = hex_asc_lo(byte);
    return buf;
}

static libra_inline char* hex_byte_pack_upper(char* buf, uint8_t byte)
{
    *buf++ = hex_asc_upper_hi(byte);
    *buf++ = hex_asc_upper_lo(byte);
    return buf;
}

libra_extern int hex_to_bin(char ch);

static libra_inline int hex_to_bin2(char c0, char c1)
{
    return hex_to_bin(c0) * 16 + hex_to_bin(c1);
}

#endif
