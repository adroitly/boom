//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __LIBRA_FSYS_H__
#define __LIBRA_FSYS_H__

#include "libra_config.h"
#include "libra_strbuf.h"

// 目录是否存在
libra_extern bool fsys_is_dir(const char* path);

// 是否普通文件
libra_extern bool fsys_is_reg(const char* path);

// 路径是否存在
libra_extern bool fsys_is_exists(const char* path);

// 创建目录
libra_extern bool fsys_mkdir(const char* path);

// 删除目录
libra_extern bool fsys_rmdir(const char* path);

// 删除文件
libra_extern bool fsys_rmreg(const char* path);

// 删除目录, 包括目录下的所有文件
libra_extern bool fsys_rmdir_recursively(const char* path);

// 删除目录下的所有文件和目录，不包括本目录
libra_extern bool fsys_rmdir_contents(const char* path);

// 使得目录存在
libra_extern bool fsys_let_dir_exists(const char* path);

// 获取当前的文件路径
libra_extern void fsys_getcwd(libra_strbuf* buf);

typedef enum
{
    fsys_file_type_none,
    fsys_file_type_dir,  // 目录
    fsys_file_type_reg,  // 普通文件
} fsys_file_type;

typedef bool (*fsys_walk_fun_t)(const char* refpath, const char* name, fsys_file_type filetype, void* ctx);
libra_extern void fsys_dir_walk(const char* basepath, fsys_walk_fun_t walkfun, void* ctx);

#if defined(__cplusplus)
#include <functional>
namespace libra
{
    typedef std::function<bool(const char* refpath, const char* name, fsys_file_type filetype)> fsys_walk_fun_t;
    static bool fsys_walk_callback(const char* refpath, const char* name, fsys_file_type filetype, void* ctx)
    {
        auto fun = reinterpret_cast<fsys_walk_fun_t*>(ctx);
        return (*fun)(refpath, name, filetype);
    }

    static inline void fsys_dir_walk(const char* basepath, const fsys_walk_fun_t& walkfun)
    {
        ::fsys_dir_walk(basepath, fsys_walk_callback, (void*)&walkfun);
    }
}
#endif

#endif
