//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "libra_utf8.h"

static size_t utf8_length(const char* utf8)
{
    uint8_t lead = *utf8;
    if (lead < 0x80)
    {
        return 1;
    }
    else if ((lead >> 5) == 0x6)
    {
        return 2;
    }
    else if ((lead >> 4) == 0xe)
    {
        return 3;
    }
    else if ((lead >> 3) == 0x1e)
    {
        return 4;
    }
    return 0;
}

static size_t to_utf8_length(uint32_t cp)
{
    if (cp < 0x80)
    {
        return 1;
    }
    else if (cp < 0x800)
    {
        return 2;
    }
    else if (cp < 0x10000)
    {
        return 3;
    }
    else
    {
        return 4;
    }
    return 0;
}

libra_inline static uint8_t mask8(char oc)
{
    return oc;
}

static size_t nextUtf8(const char* utf8, const char* end, uint16_t* c)
{
    size_t len = utf8_length(utf8);
    if (utf8 + len > end)
    {
        return 0;
    }

    switch (len)
    {
        case 0:
            break;

        case 1:
            *c = *utf8++;
            break;

        case 2:
        {
            uint32_t cp = mask8(*utf8++);
            cp = ((cp << 6) & 0x7ff) + (mask8(*utf8++) & 0x3f);
            *c = cp;
        }
        break;

        case 3:
        {
            uint32_t cp = mask8(*utf8++);
            cp = ((cp << 12) & 0xffff) + ((mask8(*utf8++) << 6) & 0xfff);
            cp += (*utf8++) & 0x3f;
            *c = cp;
        }
        break;

        case 4:
        {
            uint32_t cp = mask8(*utf8++);
            cp = ((cp << 18) & 0x1fffff) + ((mask8(*utf8++) << 12) & 0x3ffff);
            cp += (mask8(*utf8++) << 6) & 0xfff;
            cp += (*utf8++) & 0x3f;
            *c = cp;
        }
        break;

        default:
            break;
    }
    return len;
}

static size_t fillUtf8(char* utf8, const char* end, uint32_t cp)
{
    size_t len = to_utf8_length(cp);
    if (utf8 + len > end)
    {
        return 0;
    }

    switch (len)
    {
        case 1:
            *(utf8++) = cp;
            break;

        case 2:
            *(utf8++) = (char)((cp >> 6) | 0xc0);
            *(utf8++) = (char)((cp & 0x3f) | 0x80);
            break;

        case 3:
            *(utf8++) = (char)((cp >> 12) | 0xe0);
            *(utf8++) = (char)(((cp >> 6) & 0x3f) | 0x80);
            *(utf8++) = (char)((cp & 0x3f) | 0x80);
            break;

        case 4:
            *(utf8++) = (char)((cp >> 18) | 0xf0);
            *(utf8++) = (char)(((cp >> 12) & 0x3f) | 0x80);
            *(utf8++) = (char)(((cp >> 6) & 0x3f) | 0x80);
            *(utf8++) = (char)((cp & 0x3f) | 0x80);
            break;

        default:
            break;
    }

    return len;
}

size_t utf16_from_utf8(uint16_t* dst, size_t dlen, const char* src, size_t slen)
{
    const char* ptr = src;
    const char* end = src + slen;
    size_t count = 0;

    if (dst == 0 || dlen == 0)
    {
        while (ptr < end)
        {
            size_t tmp = utf8_length(ptr);
            if (tmp == 0)
            {
                break;
            }
            ptr += tmp;
            count++;
        }
        return count;
    }
    else
    {
        while (ptr < end && count < dlen)
        {
            size_t tmp = nextUtf8(ptr, end, dst);
            if (tmp == 0)
            {
                break;
            }

            ptr += tmp;
            count++;
            dst++;
        }
    }
    return count;
}

size_t utf8_from_utf16(char* dst, size_t dlen, const uint16_t* src, size_t slen)
{
    const uint16_t* ptr = src;
    const uint16_t* end = src + slen;
    size_t count = 0;

    if (dst == 0 || dlen == 0)
    {
        while (ptr < end)
        {
            count += to_utf8_length((uint32_t)*ptr);
            ptr++;
        }
    }
    else
    {
        const char* utf8End = dst + dlen;
        const char* begin = dst;

        while (ptr < end && dst < utf8End)
        {
            size_t tmp = fillUtf8(dst, utf8End, (uint32_t)*ptr);
            if (tmp == 0)
            {
                break;
            }
            ptr++;
            dst += tmp;
        }
        count = dst - begin;
    }
    return count;
}
