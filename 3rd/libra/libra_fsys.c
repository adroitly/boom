//=============================================================================
//  libra
//
//  Copyright (C) 2014 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "libra_fsys.h"
#include "libra_strbuf.h"
#include "libra_path.h"
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

typedef struct
{
    const char* name;
    fsys_file_type type;
} libra_dir_item;

#ifdef _WIN32

typedef struct
{
    WIN32_FIND_DATAA data;
    HANDLE handle;
    char name[MAX_PATH];
    bool isFinish;
} libra_dir;

static bool libra_dir_open(libra_dir* dir, libra_strbuf* path)
{
    size_t old_len = strbuf_length(path);
    libra_path_join(path, "*.*");

    HANDLE handle = FindFirstFileA(strbuf_cstr(path), &dir->data);

    strbuf_pop(path, strbuf_length(path) - old_len);

    dir->isFinish = false;
    dir->handle = handle;
    return (handle != INVALID_HANDLE_VALUE);
}

static libra_inline fsys_file_type s_get_file_type(DWORD attr)
{
    if (attr & FILE_ATTRIBUTE_DIRECTORY)
    {
        return fsys_file_type_dir;
    }

    if (attr & FILE_ATTRIBUTE_ARCHIVE)
    {
        return fsys_file_type_reg;
    }
    return fsys_file_type_none;
}

static bool libra_dir_next(libra_dir* dir, libra_dir_item* item)
{
    if (dir->isFinish)
    {
        return false;
    }
#ifdef _MSC_VER
    strncpy_s(dir->name, MAX_PATH, dir->data.cFileName, MAX_PATH);
#else
    strncpy(dir->name, dir->data.cFileName, MAX_PATH);
#endif
    item->name = dir->name;
    item->type = s_get_file_type(dir->data.dwFileAttributes);
    dir->isFinish = FindNextFileA(dir->handle, &dir->data) == FALSE;
    return true;
}

static libra_inline void libra_dir_close(libra_dir* dir)
{
    dir->isFinish = true;
    FindClose(dir->handle);
}

#else

typedef struct
{
    DIR* dir;
} libra_dir;

static libra_inline bool libra_dir_open(libra_dir* dir, libra_strbuf* path)
{
    DIR* impl = opendir(strbuf_cstr(path));
    dir->dir = impl;
    return (impl != NULL);
}

static libra_inline fsys_file_type s_get_file_type(struct dirent* ent)
{
    if (ent->d_type == DT_DIR)
    {
        return fsys_file_type_dir;
    }
    else if (ent->d_type == DT_REG)
    {
        return fsys_file_type_reg;
    }
    return fsys_file_type_none;
}

static libra_inline bool libra_dir_next(libra_dir* dir, libra_dir_item* item)
{
    struct dirent* ent = readdir(dir->dir);
    if (ent != NULL)
    {
        item->name = ent->d_name;
        item->type = s_get_file_type(ent);
        return true;
    }
    return false;
}

static libra_inline void libra_dir_close(libra_dir* dir)
{
    closedir(dir->dir);
    dir->dir = NULL;
}

#endif

////////////////////////////////////////////////////

#ifdef _WIN32

BOOL FindFirstFileExists(const char* lpPath, DWORD dwFilter)
{
    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(lpPath, &fd);
    BOOL bFilter = (FALSE == dwFilter) ? TRUE : fd.dwFileAttributes & dwFilter;
    BOOL RetValue = ((hFind != INVALID_HANDLE_VALUE) && bFilter) ? TRUE : FALSE;
    FindClose(hFind);
    return RetValue;
}

bool fsys_is_dir(const char* path)
{
    return FindFirstFileExists(path, FILE_ATTRIBUTE_DIRECTORY) == TRUE;
}

bool fsys_is_reg(const char* path)
{
    return FindFirstFileExists(path, FILE_ATTRIBUTE_ARCHIVE) == TRUE;
}

bool fsys_is_exists(const char* path)
{
    return FindFirstFileExists(path, FALSE) == TRUE;
}

bool fsys_mkdir(const char* path)
{
    return CreateDirectoryA(path, NULL) == TRUE;
}

bool fsys_rmdir(const char* path)
{
    return RemoveDirectoryA(path) == TRUE;
}

bool fsys_rmreg(const char* path)
{
    return DeleteFileA(path) == TRUE;
}

void fsys_getcwd(libra_strbuf* buf)
{
    char path[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, path);
    strbuf_asign(buf, path);
}

#else

bool fsys_is_dir(const char* path)
{
    struct stat path_stat;
    if (stat(path, &path_stat) != 0)
    {
        return false;
    }
    return S_ISDIR(path_stat.st_mode);
}

bool fsys_is_reg(const char* path)
{
    struct stat path_stat;
    if (stat(path, &path_stat) != 0)
    {
        return false;
    }
    return S_ISREG(path_stat.st_mode);
}

bool fsys_is_exists(const char* path)
{
    return access(path, F_OK) == 0;
}

bool fsys_mkdir(const char* path)
{
    return mkdir(path, 0755) == 0;
}

bool fsys_rmdir(const char* path)
{
    return rmdir(path) == 0;
}

bool fsys_rmreg(const char* path)
{
    return unlink(path) == 0;
}

void fsys_getcwd(libra_strbuf* buf)
{
    char* path = getcwd(NULL, -1);
    strbuf_asign(buf, path);
    free(path);
}

#endif

static libra_inline bool is_empty_dir(const char* name)
{
    return (!strcmp(name, ".") || !strcmp(name, ".."));
}

static void dir_walk_impl(libra_strbuf* fullpath, libra_strbuf* refpath, fsys_walk_fun_t walkfun, void* ctx)
{
    libra_dir dir;
    libra_dir_item item;

    if (!libra_dir_open(&dir, fullpath))
    {
        return;
    }

    while (libra_dir_next(&dir, &item))
    {
        if (is_empty_dir(item.name))
        {
            continue;
        }

        bool result = walkfun(strbuf_cstr(refpath), item.name, item.type, ctx);
        if (result && item.type == fsys_file_type_dir)
        {
            size_t old_len0 = strbuf_length(fullpath);
            size_t old_len1 = strbuf_length(refpath);

            libra_path_join(fullpath, item.name);
            libra_path_join(refpath, item.name);

            dir_walk_impl(fullpath, refpath, walkfun, ctx);

            strbuf_pop(fullpath, strbuf_length(fullpath) - old_len0);
            strbuf_pop(refpath, strbuf_length(refpath) - old_len1);
        }
    }

    libra_dir_close(&dir);
}

void fsys_dir_walk(const char* basepath, fsys_walk_fun_t walkfun, void* ctx)
{
    strbuf_init_stack(fullpath, 64);
    strbuf_init_stack(refBuf, 64);

    strbuf_push_string(fullpath, basepath);
    dir_walk_impl(fullpath, refBuf, walkfun, ctx);

    strbuf_finish(fullpath);
    strbuf_finish(refBuf);
}

bool fsys_rmdir_recursively(const char* path)
{
    return fsys_rmdir_contents(path) && fsys_rmdir(path);
}

typedef struct
{
    fsys_file_type type;
    libra_strbuf path;
} libra_file_item;

typedef struct
{
    libra_membuf* items;
    const char* basePath;
} libra_file_item_ctx;

static bool rmdir_walk_fun(const char* refPath, const char* name, fsys_file_type fileType, void* ctx)
{
    libra_file_item_ctx* item_ctx = (libra_file_item_ctx*)ctx;
    libra_file_item* item = (libra_file_item*)membuf_expand(item_ctx->items, sizeof(libra_file_item));

    item->type = fileType;

    libra_strbuf* path = &item->path;
    libra_strbuf_init(path, NULL, 128);

    strbuf_push_string(path, item_ctx->basePath);
    libra_path_join2(path, refPath, name, NULL);

    return true;
}

bool fsys_rmdir_contents(const char* path)
{
    membuf_init_stack(items, sizeof(libra_file_item) * 16);
    libra_file_item_ctx ctx = { items, path };

    fsys_dir_walk(path, rmdir_walk_fun, &ctx);

    libra_file_item* begin = (libra_file_item*)membuf_begin(items);
    libra_file_item* end = (libra_file_item*)membuf_end(items);

    // 从后面开始删除
    for (; end != begin; end--)
    {
        libra_file_item* ptr = end - 1;
        const char* path = strbuf_cstr(&ptr->path);
        if (ptr->type == fsys_file_type_dir)
        {
            fsys_rmdir(path);
        }
        else if (ptr->type == fsys_file_type_reg)
        {
            fsys_rmreg(path);
        }
        strbuf_finish(&ptr->path);
    }

    membuf_finish(items);
    return true;
}

bool fsys_let_dir_exists(const char* path)
{
    if (fsys_is_dir(path))
    {
        return true;
    }

    strbuf_init_stack(sub_dir, 64);
    strbuf_push_string(sub_dir, path);
    libra_path_remove_last(sub_dir);

    if (!strbuf_is_empty(sub_dir) && fsys_let_dir_exists(strbuf_cstr(sub_dir)))
    {
        strbuf_finish(sub_dir);
        return fsys_mkdir(path);
    }

    strbuf_finish(sub_dir);
    return true;
}
