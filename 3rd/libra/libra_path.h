//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __LIBRA_PATH_H__
#define __LIBRA_PATH_H__

#include "libra_config.h"
#include "libra_strbuf.h"
#include "libra_string.h"

libra_extern char libra_path_set_separator(char c);
libra_extern char libra_path_get_separator();

libra_extern void libra_path_join(libra_strbuf* path, const char* p0);
libra_extern void libra_path_join2(libra_strbuf* path, const char* p0, ...);
libra_extern void libra_path_join_ext(libra_strbuf* path, const char* ext);
libra_extern void libra_path_replace_ext(libra_strbuf* path, const char* ext);

libra_extern void libra_path_remove_ext(libra_strbuf* path);
libra_extern void libra_path_remove_last(libra_strbuf* path);

libra_extern void libra_path_get_ext(libra_strbuf* ext, const char* path_begin, const char* path_end);
libra_extern void libra_path_get_ext2(libra_strbuf* ext, const char* path);

libra_extern void libra_path_get_last(libra_strbuf* last, const char* path_begin, const char* path_end);
libra_extern void libra_path_get_last2(libra_strbuf* last, const char* path);

libra_extern void libra_path_get_real(libra_strbuf* real, const char* path_begin, const char* path_end);
libra_extern void libra_path_get_real2(libra_strbuf* real, const char* path);

libra_extern void libra_path_relative(libra_strbuf* result, libra_slice path, libra_slice base);
libra_extern void libra_path_relative2(libra_strbuf* result, const char* path, const char* base);

libra_extern void libra_path_walk(const char* path_begin,
                                  const char* path_end,
                                  void (*fun)(const char* begin, const char* end, void* ctx),
                                  void* ctx);
libra_extern void libra_path_walk2(const char* path, void (*fun)(const char* str, void* ctx), void* ctx);

#if defined(__cplusplus)
namespace libra
{
    // for path
    char path_set_separator(char c);
    char path_get_separator();

    std::string path_real(const std::string& path);
    std::string path_relative(const std::string& path, const std::string& base);

    std::vector<std::string> path_components(const std::string& path);

    // 取得路径的扩展名
    std::string path_get_ext(const std::string& path);

    // 添加扩展名
    std::string path_join_ext(const std::string& path, const std::string& extension);

    // 替换扩展名
    std::string path_replace_ext(const std::string& path, const std::string& extension);

    std::string path_remove_last(const std::string& path);

    std::string path_remove_ext(const std::string& path);

    std::string path_last_component(const std::string& path);

    std::string path_join(const std::string& path, const std::string& component);
}

#endif

#endif
