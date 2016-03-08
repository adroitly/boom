//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __LIBRA_MEMBUF_H__
#define __LIBRA_MEMBUF_H__

#include "libra_config.h"
#include <assert.h>

typedef struct
{
    size_t capacity;
    size_t size;
    bool needFree;
    char* buf;
} libra_membuf;

/*
 当outside不为空时候，首先使用外部的存储空间。
 */
libra_extern void membuf_init(libra_membuf* buf, void* outside, size_t capacity);
libra_extern void membuf_finish(libra_membuf* buf);

static libra_inline size_t membuf_size(const libra_membuf* buf)
{
    return buf->size;
}

static libra_inline size_t membuf_capacity(const libra_membuf* buf)
{
    return buf->capacity;
}

static libra_inline void* membuf_ptr(const libra_membuf* buf, size_t idx)
{
    return buf->buf + idx;
}

static libra_inline void* membuf_begin(const libra_membuf* buf)
{
    return buf->buf;
}

static libra_inline void* membuf_end(const libra_membuf* buf)
{
    return buf->buf + buf->size;
}

static libra_inline void membuf_put(libra_membuf* buf, size_t idx, char c)
{
    buf->buf[idx] = c;
}

libra_extern void* membuf_expand(libra_membuf* buf, size_t size);

libra_extern void membuf_resize(libra_membuf* buf, size_t size);
static libra_inline void membuf_pop(libra_membuf* buf, size_t size)
{
    assert(buf->size >= size);
    buf->size -= size;
}

libra_extern void membuf_push(libra_membuf* buf, const void* data, size_t dataSize);
libra_extern void membuf_earse(libra_membuf* buf, size_t begin, size_t dataSize);

#define __membuf_init_stack_line(name, size, line)        \
    libra_membuf libra_macro_concat(name, line);          \
    libra_membuf* name = &libra_macro_concat(name, line); \
    char libra_macro_concat(__stackbuf, line)[size];      \
    membuf_init(name, libra_macro_concat(__stackbuf, line), size);

#define membuf_init_stack(name, size) __membuf_init_stack_line(name, size, __LINE__)

#endif
