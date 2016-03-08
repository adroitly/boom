/*
 The MIT License (MIT)

 Copyright (c) 2015 HJC hjcapple@gmail.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "libra_string.h"
#include <assert.h>
#include <algorithm>
#include "libra_strbuf.h"


bool str_starts_with(const char* str, const char* prefix)
{
    assert(str);
    assert(prefix);
    while (*prefix)
    {
        if (*prefix++ != *str++)
        {
            return false;
        }
    }
    return true;
}

const char* str_skip_if(const char* begin, const char* end, int (*fun)(int))
{
    assert(end >= begin);
    while (begin != end && fun(begin[0]))
    {
        begin++;
    }
    return begin;
}

const char* str_skip_char(const char* begin, const char* end, char c)
{
    assert(end >= begin);
    while (begin != end && begin[0] == c)
    {
        begin++;
    }
    return begin;
}

const char* str_rskip_char(const char* begin, const char* end, char c)
{
    assert(end >= begin);
    while (begin != end && end[-1] == c)
    {
        end--;
    }
    return end;
}

const char* str_rskip_if(const char* begin, const char* end, int (*fun)(int))
{
    assert(end >= begin);
    while (begin != end && fun(end[-1]))
    {
        end--;
    }
    return end;
}

const char* str_find_char(const char* begin, const char* end, char c)
{
    assert(end >= begin);
    while (begin != end && begin[0] != c)
    {
        begin++;
    }
    return begin;
}

const char* str_find_if(const char* begin, const char* end, int (*fun)(int))
{
    assert(end >= begin);
    while (begin != end && !fun(begin[0]))
    {
        begin++;
    }
    return begin;
}

const char* str_rfind_char(const char* begin, const char* end, char c)
{
    assert(end >= begin);
    while (begin != end && end[-1] != c)
    {
        end--;
    }
    return end;
}

const char* str_rfind_if(const char* begin, const char* end, int (*fun)(int))
{
    assert(end >= begin);
    while (begin != end && !fun(end[-1]))
    {
        end--;
    }
    return end;
}

bool str_iequal(const char* str0, const char* str1)
{
    char c0, c1;
    while (c0 = *str0, c1 = *str1, c0 || c1)
    {
        if (tolower(c0) != tolower(c1))
        {
            return false;
        }
        ++str0;
        ++str1;
    }
    return true;
}

size_t str_digits10(uint32_t v)
{
    size_t result = 1;
    for (;;)
    {
        if (v < 10)
        {
            return result;
        }

        if (v < 100)
        {
            return result + 1;
        }

        if (v < 1000)
        {
            return result + 2;
        }

        if (v < 10000)
        {
            return result + 3;
        }
        // Skip ahead by 4 orders of magnitude
        v /= 10000U;
        result += 4;
    }
    return result;
}

void uint32_to_str2(uint32_t value, char* dst, size_t digits10)
{
    static const char digits[201] =
        "0001020304050607080910111213141516171819"
        "2021222324252627282930313233343536373839"
        "4041424344454647484950515253545556575859"
        "6061626364656667686970717273747576777879"
        "8081828384858687888990919293949596979899";

    assert(dst && digits10 > 0);
    size_t const length = digits10;
    size_t next = length - 1;
    while (value >= 100)
    {
        uint32_t i = (value % 100) * 2;
        value /= 100;
        dst[next] = digits[i + 1];
        dst[next - 1] = digits[i];
        next -= 2;
    }
    // Handle last 1-2 digits
    if (value < 10)
    {
        dst[next] = '0' + (uint32_t)value;
    }
    else
    {
        uint32_t i = (uint32_t)value * 2;
        dst[next] = digits[i + 1];
        dst[next - 1] = digits[i];
    }
    dst[length] = 0;
}

size_t uint32_to_str(uint32_t value, char* dst)
{
    assert(dst);
    size_t len = str_digits10(value);
    uint32_to_str2(value, dst, len);
    return len;
}

bool libra_slice_equal(libra_slice r0, libra_slice r1)
{
    size_t len0 = r0.end - r0.begin;
    size_t len1 = r1.end - r1.begin;
    if (len0 != len1)
    {
        return false;
    }
    return !strncmp(r0.begin, r1.begin, len0);
}

namespace libra
{
    std::string str_repeat(const std::string& str, int n)
    {
        std::string result;
        for (auto i = 0; i < n; i++)
        {
            result += str;
        }
        return result;
    }

    void str_replaceAll(std::string& str, const std::string& old_value, const std::string& new_value)
    {
        size_t start = 0;
        for (;;)
        {
            size_t pos = str.find(old_value, start);
            if (pos == std::string::npos)
            {
                break;
            }

            str.replace(pos, old_value.length(), new_value);
            start = pos + new_value.length();
        }
    }

    std::string str_readFromPath(const std::string& path)
    {
        FILE* file = fopen(path.c_str(), "r");
        std::string result;

        if (file == nullptr)
        {
            return result;
        }

        const size_t read_len = 1024;
        char buf[read_len];
        for (;;)
        {
            size_t n = fread(buf, 1, read_len, file);
            result.insert(result.size(), buf, n);
            if (n < read_len)
            {
                break;
            }
        }
        fclose(file);
        return result;
    }

    void str_writeToPath(const std::string& str, const std::string& path)
    {
        FILE* file = fopen(path.c_str(), "w");
        if (file == nullptr)
        {
            return;
        }
        fwrite(str.c_str(), str.size(), 1, file);
        fclose(file);
    }

    std::vector<std::string> str_split(const std::string& str, const std::string& split_str)
    {
        assert(!split_str.empty());
        if (str.empty())
        {
            return std::vector<std::string>();
        }

        std::vector<std::string> result;
        auto iter = str.begin();
        for (;;)
        {
            auto search_iter = std::search(iter, str.end(), split_str.begin(), split_str.end());
            if (iter != search_iter)
            {
                result.push_back(std::string(iter, search_iter));
            }

            if (search_iter == str.end())
            {
                break;
            }
            iter = search_iter + split_str.size();
        }
        return result;
    }

    std::string str_format(const char* format, ...)
    {
        strbuf_init_stack(result, 64);
        auto_strbuf_finish finish(result);

        va_list vlist;
        va_start(vlist, format);
        strbuf_push_vformat(result, format, vlist);
        va_end(vlist);
        return strbuf_cstr(result);
    }

    inline std::string s_uuid_string(unsigned char uuid[16], decltype(strbuf_push_hex_str) push_callback)
    {
        strbuf_init_stack(result, 64);
        auto_strbuf_finish finish(result);

        push_callback(result, uuid, 4);
        strbuf_push_char(result, '-');
        push_callback(result, uuid + 4, 2);
        strbuf_push_char(result, '-');
        push_callback(result, uuid + 6, 2);
        strbuf_push_char(result, '-');
        push_callback(result, uuid + 8, 2);
        strbuf_push_char(result, '-');
        push_callback(result, uuid + 10, 6);

        assert(strbuf_length(result) == 36);
        return strbuf_cstr(result);
    }

    std::string str_uuidHexString(unsigned char uuid[16])
    {
        return s_uuid_string(uuid, strbuf_push_hex_str);
    }

    std::string str_uuidHexStringUpper(unsigned char uuid[16])
    {
        return s_uuid_string(uuid, strbuf_push_hex_str_upper);
    }

    inline std::string s_md5_hex(unsigned char md5[16], decltype(strbuf_push_hex_str) push_callback)
    {
        strbuf_init_stack(result, 36);
        auto_strbuf_finish finish(result);

        push_callback(result, md5, 16);
        assert(strbuf_length(result) == 32);
        return strbuf_cstr(result);
    }

    std::string str_md5HexString(unsigned char md5[16])
    {
        return s_md5_hex(md5, strbuf_push_hex_str);
    }

    std::string str_md5HexStringUpper(unsigned char md5[16])
    {
        return s_md5_hex(md5, strbuf_push_hex_str_upper);
    }
}
