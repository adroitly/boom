//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "libra_path.h"
#include "libra_string.h"
#include <stdarg.h>

#ifdef _WIN32
static char s_separator = '\\';
#else
static char s_separator = '/';
#endif

static libra_inline char s_get_separator()
{
    return s_separator;
}

char libra_path_set_separator(char c)
{
    char old = s_separator;
    s_separator = c;
    return old;
}

char libra_path_get_separator()
{
    return s_get_separator();
}

void libra_path_join(libra_strbuf* path, const char* component)
{
    assert(path);
    assert(component);

    if (str_is_empty(component))
    {
        return;
    }

    size_t size = strbuf_length(path);
    if (size == 0)
    {
        strbuf_push_string(path, component);
        return;
    }

    char separator = s_get_separator();
    const char* str = strbuf_cstr(path);
    if (str[size - 1] != separator)
    {
        strbuf_push_char(path, separator);
    }

    while (*component == separator)
    {
        component++;
    }
    strbuf_push_string(path, component);
}

void libra_path_join2(libra_strbuf* path, const char* p0, ...)
{
    libra_path_join(path, p0);
    va_list vlist;
    va_start(vlist, p0);
    for (;;)
    {
        const char* p = va_arg(vlist, const char*);
        if (p == NULL)
        {
            break;
        }
        libra_path_join(path, p);
    }
    va_end(vlist);
}

void libra_path_join_ext(libra_strbuf* path, const char* ext)
{
    assert(path);
    assert(ext);

    if (str_is_empty(ext))
    {
        return;
    }

    strbuf_push_char(path, '.');
    strbuf_push_string(path, ext);
}

static const char* path_rfind_ext(const char* begin, const char* end, char separator)
{
    while (begin != end)
    {
        char c = end[-1];
        if (c == '.')
        {
            return end;
        }
        if (c == separator)
        {
            return begin;
        }
        end--;
    }
    return end;
}

static const char* path_rfind_last(const char* begin, const char* end, char separator)
{
    return str_rfind_char(begin, end, separator);
}

void libra_path_remove_ext(libra_strbuf* path)
{
    assert(path);
    char separator = s_get_separator();
    const char* begin = strbuf_begin(path);
    const char* end = path_rfind_ext(begin, strbuf_end(path), separator);
    if (end != begin)
    {
        assert(end[-1] == '.');
        end--;
        strbuf_pop(path, strbuf_end(path) - end);
    }
}

void libra_path_remove_last(libra_strbuf* path)
{
    assert(path);
    char separator = s_get_separator();
    const char* begin = strbuf_begin(path);
    // skip path separator
    const char* end = str_rskip_char(begin, strbuf_end(path), separator);
    end = path_rfind_last(begin, end, separator);
    if (end != begin)
    {
        // skip path separator again
        end = str_rskip_char(begin, end, separator);
        strbuf_pop(path, strbuf_end(path) - end);
    }
}

void libra_path_replace_ext(libra_strbuf* path, const char* ext)
{
    assert(path);
    assert(ext);

    libra_path_remove_ext(path);
    libra_path_join_ext(path, ext);
}

void libra_path_get_ext(libra_strbuf* result, const char* path_begin, const char* path_end)
{
    char separator = s_get_separator();
    const char* ptr = path_rfind_ext(path_begin, path_end, separator);
    strbuf_clear(result);
    if (ptr != path_begin)
    {
        strbuf_push_lstring(result, ptr, path_end - ptr);
    }
}

void libra_path_get_ext2(libra_strbuf* ext, const char* path)
{
    libra_path_get_ext(ext, path, path + strlen(path));
}

void libra_path_get_last(libra_strbuf* result, const char* path_begin, const char* path_end)
{
    char separator = s_get_separator();
    path_end = str_rskip_char(path_begin, path_end, separator);
    const char* ptr = path_rfind_last(path_begin, path_end, separator);
    strbuf_clear(result);
    if (ptr != path_begin)
    {
        strbuf_push_lstring(result, ptr, path_end - ptr);
    }
}

void libra_path_get_last2(libra_strbuf* last, const char* path)
{
    libra_path_get_last(last, path, path + strlen(path));
}

static void s_get_realwalk(const char* begin, const char* end, void* ctx)
{
    libra_strbuf* real = (libra_strbuf*)ctx;
    size_t size = end - begin;
    if (size == 1 && begin[0] == '.')
    {
        // do nothing
    }
    else if (size == 2 && begin[0] == '.' && begin[1] == '.')
    {
        libra_path_remove_last(real);
    }
    else
    {
        char separator = s_get_separator();
        size_t size = strbuf_length(real);
        if (size != 0 && strbuf_end(real)[-1] != separator)
        {
            strbuf_push_char(real, separator);
        }
        strbuf_push_lstring(real, begin, end - begin);
    }
}

void libra_path_get_real(libra_strbuf* real, const char* path_begin, const char* path_end)
{
    strbuf_clear(real);
    libra_path_walk(path_begin, path_end, s_get_realwalk, real);
}

void libra_path_get_real2(libra_strbuf* real, const char* path)
{
    libra_path_get_real(real, path, path + strlen(path));
}

static void s_get_rangewalk(const char* begin, const char* end, void* ctx)
{
    libra_membuf* buf = (libra_membuf*)ctx;
    libra_slice range = { begin, end };
    membuf_push(buf, &range, sizeof(range));
}

void libra_path_relative2(libra_strbuf* result, const char* path, const char* base)
{
    libra_slice path_range = { path, path + strlen(path) };
    libra_slice base_range = { base, base + strlen(base) };
    libra_path_relative(result, path_range, base_range);
}

void libra_path_relative(libra_strbuf* result, libra_slice path_, libra_slice base_)
{
    strbuf_clear(result);
    char separator = s_get_separator();
    if (libra_slice_equal(path_, base_))
    {
        char buf[] = { '.', separator, 0 };
        strbuf_push_lstring(result, buf, 2);
        return;
    }

    membuf_init_stack(pathComponents, 64);
    membuf_init_stack(baseComponents, 64);

    libra_path_walk(path_.begin, path_.end, s_get_rangewalk, pathComponents);
    libra_path_walk(base_.begin, base_.end, s_get_rangewalk, baseComponents);

    const libra_slice* pathIter = (const libra_slice*)membuf_begin(pathComponents);
    const libra_slice* pathEnd = (const libra_slice*)membuf_end(pathComponents);

    const libra_slice* baseIter = (const libra_slice*)membuf_begin(baseComponents);
    const libra_slice* baseEnd = (const libra_slice*)membuf_end(baseComponents);

    for (;;)
    {
        if ((pathIter == pathEnd) || (baseIter == baseEnd) || !libra_slice_equal(*pathIter, *baseIter))
        {
            for (; baseIter != baseEnd; ++baseIter)
            {
                char buf[] = { '.', '.', separator, 0 };
                strbuf_push_lstring(result, buf, 3);
            }

            for (; pathIter != pathEnd; ++pathIter)
            {
                if (!strbuf_is_empty(result) && strbuf_end(result)[-1] != separator)
                {
                    strbuf_push_char(result, separator);
                }
                strbuf_push_lstring(result, pathIter->begin, pathIter->end - pathIter->begin);
            }
            break;
        }
        ++pathIter;
        ++baseIter;
    }

    membuf_finish(pathComponents);
    membuf_finish(baseComponents);
}

void libra_path_walk(const char* begin,
                     const char* end,
                     void (*fun)(const char* begin, const char* end, void* ctx),
                     void* ctx)
{
    if (end <= begin)
    {
        return;
    }

    char separator = s_get_separator();
    if (*begin == separator)
    {
        fun(begin, begin + 1, ctx);
        begin++;
    }

    for (;;)
    {
        begin = str_skip_char(begin, end, separator);
        if (begin == end)
        {
            break;
        }

        const char* tmp_end = strchr(begin + 1, separator);
        if (tmp_end == NULL)
        {
            fun(begin, end, ctx);
            break;
        }

        fun(begin, tmp_end, ctx);
        begin = tmp_end + 1;
    }
}

typedef struct
{
    void (*fun)(const char* str, void* ctx);
    void* ctx;
} libra_path_walk2_pair;

static void walk_fun(const char* begin, const char* end, void* ctx)
{
    libra_path_walk2_pair* pair = (libra_path_walk2_pair*)ctx;
    char c = *end;
    *((char*)end) = 0;
    pair->fun(begin, pair->ctx);
    *((char*)end) = c;
}

void libra_path_walk2(const char* path, void (*fun)(const char* str, void* ctx), void* ctx)
{
    strbuf_init_stack(buf, 64);

    strbuf_push_string(buf, path);
    libra_path_walk2_pair pair = { fun, ctx };
    libra_path_walk(strbuf_begin(buf), strbuf_end(buf), walk_fun, &pair);

    strbuf_finish(buf);
}

namespace libra
{
    char path_set_separator(char c)
    {
        return libra_path_set_separator(c);
    }

    char path_get_separator()
    {
        return libra_path_get_separator();
    }

    std::string path_real(const std::string& path)
    {
        strbuf_init_stack(result, 64);
        auto_strbuf_finish finish(result);

        libra_path_get_real(result, path.c_str(), path.c_str() + path.size());
        return strbuf_cstr(result);
    }

    static void path_walk_fun(const char* begin, const char* end, void* ctx)
    {
        std::vector<std::string>* result = (std::vector<std::string>*)ctx;
        result->push_back(std::string(begin, end));
    }

    std::vector<std::string> path_components(const std::string& path)
    {
        std::vector<std::string> result;
        libra_path_walk(path.c_str(), path.c_str() + path.size(), path_walk_fun, (void*)&result);
        return result;
    }

    std::string path_relative(const std::string& p, const std::string& base)
    {
        libra_slice path_range = { p.c_str(), p.c_str() + p.size() };
        libra_slice base_range = { base.c_str(), base.c_str() + base.size() };

        strbuf_init_stack(result, 64);
        auto_strbuf_finish finish(result);

        libra_path_relative(result, path_range, base_range);
        return strbuf_cstr(result);
    }

    std::string path_remove_last(const std::string& path)
    {
        strbuf_init_stack(result, 64);
        auto_strbuf_finish finish(result);

        strbuf_push_lstring(result, path.c_str(), path.size());
        libra_path_remove_last(result);
        return strbuf_cstr(result);
    }

    std::string path_join_ext(const std::string& path, const std::string& extension)
    {
        strbuf_init_stack(result, 64);
        auto_strbuf_finish finish(result);

        strbuf_push_lstring(result, path.c_str(), path.size());
        libra_path_join_ext(result, extension.c_str());
        return strbuf_cstr(result);
    }

    std::string path_replace_ext(const std::string& path, const std::string& newExtension)
    {
        strbuf_init_stack(result, 64);
        auto_strbuf_finish finish(result);

        strbuf_push_lstring(result, path.c_str(), path.size());
        libra_path_replace_ext(result, newExtension.c_str());
        return strbuf_cstr(result);
    }

    std::string path_remove_ext(const std::string& path)
    {
        strbuf_init_stack(result, 64);
        auto_strbuf_finish finish(result);

        strbuf_push_lstring(result, path.c_str(), path.size());
        libra_path_remove_ext(result);
        return strbuf_cstr(result);
    }

    std::string path_get_ext(const std::string& path)
    {
        strbuf_init_stack(result, 64);
        auto_strbuf_finish finish(result);

        libra_path_get_ext(result, path.c_str(), path.c_str() + path.size());
        return strbuf_cstr(result);
    }

    std::string path_last_component(const std::string& path)
    {
        strbuf_init_stack(result, 64);
        auto_strbuf_finish finish(result);

        libra_path_get_last(result, path.c_str(), path.c_str() + path.size());
        return strbuf_cstr(result);
    }

    std::string path_join(const std::string& path, const std::string& component)
    {
        strbuf_init_stack(result, 64);
        auto_strbuf_finish finish(result);

        strbuf_push_lstring(result, path.c_str(), path.size());
        libra_path_join(result, component.c_str());
        return strbuf_cstr(result);
    }
}
