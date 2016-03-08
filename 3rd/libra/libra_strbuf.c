//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "libra_strbuf.h"
#include "libra_string.h"
#include "libra_safe.h"
#include "libra_hex.h"
#include <stdarg.h>

#if !defined(NDEBUG)
static bool strbuf_is_cstr(libra_strbuf* buf)
{
    libra_membuf* mbuf = &buf->buf;
    assert(membuf_size(mbuf) > 0);
    const char* end = (const char*)membuf_end(mbuf);
    return end[-1] == 0;
}
#endif

void libra_strbuf_init(libra_strbuf* buf, void* outside, size_t capacity)
{
    libra_membuf* mbuf = &buf->buf;
    membuf_init(mbuf, outside, capacity);
    char c = 0;
    membuf_push(mbuf, &c, 1);
    assert(strbuf_length(buf) == 0);
    assert(strbuf_is_cstr(buf));
}

static char* strbuf_expand(libra_strbuf* buf, size_t size)
{
    libra_membuf* mbuf = &buf->buf;
    size_t pos = strbuf_length(buf);
    membuf_resize(mbuf, membuf_size(mbuf) + size);
    return (char*)membuf_ptr(mbuf, pos);
}

void strbuf_push_lstring(libra_strbuf* buf, const char* str, size_t size)
{
    assert(str && size >= 0);
    char* ptr = strbuf_expand(buf, size);
    memcpy(ptr, str, size);
    ptr[size] = 0;
    assert(strbuf_is_cstr(buf));
}

static libra_inline void __strbuf_push_hex_str(libra_strbuf* buf,
                                               const void* input,
                                               size_t size,
                                               char* (*callback)(char*, uint8_t))
{
    assert(input && size >= 0);
    char* ptr = strbuf_expand(buf, size * 2);
    const uint8_t* begin = (const uint8_t*)input;
    const uint8_t* end = begin + size;

    while (begin != end)
    {
        ptr = (*callback)(ptr, *begin);
        begin++;
    }
    *ptr = 0;
    assert(strbuf_is_cstr(buf));
}

void strbuf_push_hex_str_upper(libra_strbuf* buf, const void* input, size_t size)
{
    __strbuf_push_hex_str(buf, input, size, hex_byte_pack_upper);
}

void strbuf_push_hex_str(libra_strbuf* buf, const void* input, size_t size)
{
    __strbuf_push_hex_str(buf, input, size, hex_byte_pack);
}

void strbuf_pop(libra_strbuf* buf, size_t size)
{
    assert(size <= strbuf_length(buf));
    libra_membuf* mbuf = &buf->buf;
    membuf_pop(mbuf, size);
    membuf_put(mbuf, strbuf_length(buf), 0);
    assert(strbuf_is_cstr(buf));
}

void strbuf_push_uint32(libra_strbuf* buf, uint32_t v)
{
    size_t size = str_digits10(v);
    char* ptr = strbuf_expand(buf, size);
    uint32_to_str2(v, ptr, size);
    ptr[size] = 0;
    assert(strbuf_is_cstr(buf));
}

// vsnprintf‘s behaviour is different on windows and linux
// so wrapper it
static int strbuf_vsnprintf(char* buf,
                            size_t buf_size,
                            size_t* try_agin_size,
                            const char* format,
                            va_list vlist)
{
    int format_len = libra_vsnprintf(buf, buf_size, format, vlist);
    if (format_len < 0)
    {
        *try_agin_size = buf_size * 2;
        return -1;
    }

    if (format_len < (int)buf_size)
    {
        return format_len;
    }

    *try_agin_size = format_len + 1;
    return -1;
}

void strbuf_push_vformat(libra_strbuf* buf, const char* format, va_list vlist)
{
    libra_membuf* mbuf = &buf->buf;
    size_t size = membuf_capacity(mbuf) - membuf_size(mbuf);
    if (size == 0)
    {
        membuf_resize(mbuf, membuf_size(mbuf) + 1);
        membuf_pop(mbuf, 1);
        size = membuf_capacity(mbuf) - membuf_size(mbuf);
        assert(size > 0);
    }

    size_t old_len = strbuf_length(buf);
    size_t old_mem_size = membuf_size(mbuf);

    for (;;)
    {
        membuf_resize(mbuf, old_mem_size + size);
        char* ptr = (char*)membuf_ptr(mbuf, old_len);

        va_list copy_list;
        size_t try_agin_size = 0;
        va_copy(copy_list, vlist);
        int format_len = strbuf_vsnprintf(ptr, size, &try_agin_size, format, copy_list);
        va_end(copy_list);

        if (format_len < 0)
        {
            size = try_agin_size;
        }
        else
        {
            ptr[format_len] = 0;
            strbuf_pop(buf, size - format_len);
            assert(old_len + format_len == strbuf_length(buf));
            break;
        }
    }
    assert(strbuf_is_cstr(buf));
}

void strbuf_push_format(libra_strbuf* buf, const char* format, ...)
{
    va_list vlist;
    va_start(vlist, format);
    strbuf_push_vformat(buf, format, vlist);
    va_end(vlist);
    assert(strbuf_is_cstr(buf));
}
