//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "libra_membuf.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void membuf_init(libra_membuf* buf, void* outside, size_t capacity)
{
    if (capacity == 0)
    {
        buf->capacity = 0;
        buf->size = 0;
        buf->needFree = false;
        buf->buf = NULL;
    }
    else
    {
        if (outside)
        {
            buf->buf = (char*)outside;
            buf->needFree = false;
        }
        else
        {
            buf->buf = (char*)libra_malloc(capacity);
            buf->needFree = true;
        }

        buf->capacity = capacity;
        buf->size = 0;
    }
}

void membuf_finish(libra_membuf* buf)
{
    if (buf->needFree)
    {
        libra_free(buf->buf);
    }
}

static size_t adjust_capacity(size_t capacity, size_t needSize)
{
    if (capacity == 0)
    {
        return needSize;
    }

    while (capacity < needSize)
    {
        capacity *= 2;
    }
    return capacity;
}

static void libra_buffer_recapacity(libra_membuf* buf, size_t needSize)
{
    if (buf->capacity >= needSize)
    {
        return;
    }

    size_t capacity = adjust_capacity(buf->capacity, needSize);
    assert(capacity >= needSize);

    if (buf->needFree)
    {
        char* newbuf = (char*)libra_realloc(buf->buf, capacity);
        assert(newbuf);
        buf->buf = newbuf;
    }
    else
    {
        char* newbuf = (char*)libra_malloc(capacity);
        memcpy(newbuf, buf->buf, buf->size);
        buf->buf = newbuf;
    }
    buf->needFree = true;
    assert(buf->buf);
    buf->capacity = capacity;
}

void membuf_resize(libra_membuf* buf, size_t size)
{
    libra_buffer_recapacity(buf, size);
    assert(size <= buf->capacity);
    buf->size = size;
}

void* membuf_expand(libra_membuf* buf, size_t size)
{
    assert(size >= 0);
    size_t old_size = buf->size;
    membuf_resize(buf, old_size + size);
    return membuf_ptr(buf, old_size);
}

void membuf_push(libra_membuf* buf, const void* data, size_t dataSize)
{
    libra_buffer_recapacity(buf, buf->size + dataSize);
    memcpy(buf->buf + buf->size, data, dataSize);
    buf->size += dataSize;
}

void membuf_earse(libra_membuf* buf, size_t begin, size_t dataSize)
{
    assert(dataSize > 0);
    assert(begin + dataSize <= buf->size);
    size_t move_size = buf->size - (begin + dataSize);
    memmove(buf->buf + begin, buf->buf + begin + dataSize, move_size);
    buf->size -= dataSize;
}
