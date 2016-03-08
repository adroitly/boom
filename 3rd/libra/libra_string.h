//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __LIBRA_STRING_H__
#define __LIBRA_STRING_H__

#include "libra_config.h"
#include <string.h>

typedef struct
{
    const char* begin;
    const char* end;
} libra_slice;

static libra_inline libra_slice str_to_range(const char* str)
{
    libra_slice range = { str, str + strlen(str) };
    return range;
}

libra_extern bool libra_slice_equal(libra_slice r0, libra_slice r1);

libra_extern const char* str_skip_char(const char* begin, const char* end, char c);
libra_extern const char* str_skip_if(const char* begin, const char* end, int (*fun)(int));

libra_extern const char* str_rskip_char(const char* begin, const char* end, char c);
libra_extern const char* str_rskip_if(const char* begin, const char* end, int (*fun)(int));

libra_extern const char* str_find_char(const char* begin, const char* end, char c);
libra_extern const char* str_find_if(const char* begin, const char* end, int (*fun)(int));

libra_extern const char* str_rfind_char(const char* begin, const char* end, char c);
libra_extern const char* str_rfind_if(const char* begin, const char* end, int (*fun)(int));

static libra_inline bool str_equal(const char* str0, const char* str1)
{
    return strcmp(str0, str1) == 0;
}

static libra_inline bool str_is_empty(const char* str)
{
    return !(str && *str != 0);
}

libra_extern bool str_starts_with(const char* str, const char* prefix);
libra_extern size_t str_digits10(uint32_t v);
libra_extern size_t uint32_to_str(uint32_t value, char* dst);
libra_extern void uint32_to_str2(uint32_t value, char* dst, size_t digits10);

#if defined(__cplusplus)
#include <string>
#include <vector>
namespace libra
{
    void str_replaceAll(std::string& str, const std::string& old_value, const std::string& new_value);

    // 从文件中读取字符串
    std::string str_readFromPath(const std::string& path);

    // 将字符串写入文件
    void str_writeToPath(const std::string& str, const std::string& path);

    // 字符串分割
    std::vector<std::string> str_split(const std::string& str, const std::string& splitStr);

    // 字符串函数
    std::string str_format(const char* format, ...);
    std::string str_repeat(const std::string& str, int n);
    std::string str_uuidHexString(unsigned char uuid[16]);
    std::string str_uuidHexStringUpper(unsigned char uuid[16]);
    std::string str_md5HexString(unsigned char md5[16]);
    std::string str_md5HexStringUpper(unsigned char md5[16]);
}
#endif

#endif
