//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __LIBRA_STRBUF_H__
#define __LIBRA_STRBUF_H__

#include "libra_config.h"
#include "libra_membuf.h"
#include <string.h>
#include <stdarg.h>

typedef struct
{
    libra_membuf buf;
} libra_strbuf;

libra_extern void libra_strbuf_init(libra_strbuf* buf, void* outside, size_t capacity);

static libra_inline void strbuf_finish(libra_strbuf* buf)
{
    membuf_finish(&buf->buf);
}

libra_extern void strbuf_push_lstring(libra_strbuf* buf, const char* str, size_t size);
libra_extern void strbuf_push_uint32(libra_strbuf* buf, uint32_t v);
libra_extern void strbuf_push_vformat(libra_strbuf* buf, const char* format, va_list vlist);
libra_extern void strbuf_push_format(libra_strbuf* buf, const char* format, ...);
libra_extern void strbuf_push_hex_str(libra_strbuf* buf, const void* input, size_t size);
libra_extern void strbuf_push_hex_str_upper(libra_strbuf* buf, const void* input, size_t size);

static libra_inline void strbuf_push_char(libra_strbuf* buf, char c)
{
    strbuf_push_lstring(buf, &c, 1);
}

static libra_inline const char* strbuf_cstr(const libra_strbuf* buf)
{
    return (const char*)membuf_ptr(&buf->buf, 0);
}

static libra_inline size_t strbuf_length(const libra_strbuf* buf)
{
    return membuf_size(&buf->buf) - 1;
}

static libra_inline const char* strbuf_begin(const libra_strbuf* buf)
{
    return strbuf_cstr(buf);
}

static libra_inline const char* strbuf_end(const libra_strbuf* buf)
{
    return strbuf_cstr(buf) + strbuf_length(buf);
}

static libra_inline bool strbuf_is_empty(const libra_strbuf* buf)
{
    return strbuf_length(buf) == 0;
}

static libra_inline void strbuf_push_string(libra_strbuf* buf, const char* str)
{
    strbuf_push_lstring(buf, str, strlen(str));
}

libra_extern void strbuf_pop(libra_strbuf* buf, size_t size);

static libra_inline void strbuf_clear(libra_strbuf* buf)
{
    strbuf_pop(buf, strbuf_length(buf));
}

static libra_inline void strbuf_asign(libra_strbuf* buf, const char* str)
{
    strbuf_clear(buf);
    strbuf_push_string(buf, str);
}

static libra_inline void strbuf_lassign(libra_strbuf* buf, const char* str, size_t size)
{
    strbuf_clear(buf);
    strbuf_push_lstring(buf, str, size);
}

/*
 strbuf_init_stack(buf, 32); at line 11, will expand to

 libra_strbuf buf11;
 libra_strubf* buf = &buf11;
 char __stackbuf11[32];
 strbuf_init(buf, __stackbuf11, 32);
 */
#define __strbuf_init_stack_line(name, size, line)        \
    libra_strbuf libra_macro_concat(name, line);          \
    libra_strbuf* name = &libra_macro_concat(name, line); \
    char libra_macro_concat(__stackbuf, line)[size];      \
    libra_strbuf_init(name, libra_macro_concat(__stackbuf, line), size);

#define strbuf_init_stack(name, size) __strbuf_init_stack_line(name, size, __LINE__)

#if defined(__cplusplus)
#include <string>

namespace libra
{
    struct auto_strbuf_finish
    {
        auto_strbuf_finish(libra_strbuf* buf) : _buf(buf)
        {
        }
        
        ~auto_strbuf_finish()
        {
            strbuf_finish(_buf);
        }
        
    private:
        libra_strbuf* _buf;
    };
    
    inline void strbuf_push_string(libra_strbuf* buf, const std::string& str)
    {
        strbuf_push_lstring(buf, str.c_str(), str.size());
    }

    inline std::string strbuf_to_string(libra_strbuf* buf)
    {
        auto str = strbuf_cstr(buf);
        return std::string(str, strbuf_length(buf) + str);
    }
}
#endif

#endif
