//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_utils.h"
#include <algorithm>
#include "libra/libra_math.h"
#include "libra/libra_string.h"
#include <assert.h>

namespace fla
{
    const int kEdgeSpace = 2;
    Rect adjustRectForRender(const Rect& rt, real_t sizeScale)
    {
        auto result = rt;

        result.width *= sizeScale;
        result.height *= sizeScale;

        // 使得渲染时候纹理的包围框稍微扩大一点，防止绘画时候被截掉阴影
        if (libra::is_float(result.x) || libra::is_float(result.width))
        {
            result.x = libra::floor(result.x - kEdgeSpace);
            result.width = libra::ceil(result.width + kEdgeSpace * 2);
        }

        if (libra::is_float(result.y) || libra::is_float(result.height))
        {
            result.y = libra::floor(result.y - kEdgeSpace);
            result.height = libra::ceil(result.height + kEdgeSpace * 2);
        }

        // 调成偶数导出
        if (libra::is_odd(result.width))
        {
            result.width += 1;
        }

        if (libra::is_odd(result.height))
        {
            result.height += 1;
        }
        return result;
    }

    Point adjustPointForRender(const Rect& rt)
    {
        Point pt(rt.x, rt.y);
        if (libra::is_float(rt.x) || libra::is_float(rt.width))
        {
            pt.x = libra::floor(rt.x - kEdgeSpace);
        }

        if (libra::is_float(rt.y) || libra::is_float(rt.height))
        {
            pt.y = libra::floor(rt.y - kEdgeSpace);
        }
        return pt;
    }

    static inline char* buff_addString(char* buf, const char* str, size_t size)
    {
        assert(strlen(str) == size);
        strncpy(buf, str, size);
        return buf + size;
    }

    static inline char* buff_addUint32(char* buf, uint32_t v)
    {
        return buf + uint32_to_str(v, buf);
    }

    std::string keyOfCache(const std::string& dataMd5, int Id, int tag, float scale, float ratio)
    {
        assert(Id >= 0);
        assert(tag >= 0);
        assert(scale >= 0);
        assert(ratio >= 0);

        // 产生缓存的key的时候，需要加_分割
        // 因为12 1，跟 1 21, 直接拼接的时候，都产生121，就有机会引起重名
        // 而加上_分割，就没有这个问题
        char buffer[64];
        char* ptr = buffer;
        ptr = buff_addString(ptr, "2_", 2);
        ptr = buff_addString(ptr, dataMd5.c_str(), dataMd5.size());
        ptr = buff_addString(ptr, "_", 1);
        ptr = buff_addUint32(ptr, Id);
        ptr = buff_addString(ptr, "_", 1);
        ptr = buff_addUint32(ptr, tag);
        ptr = buff_addString(ptr, "_", 1);
        ptr = buff_addUint32(ptr, static_cast<int>(scale * 100));
        ptr = buff_addString(ptr, "_", 1);
        ptr = buff_addUint32(ptr, static_cast<int>(ratio * 100));
        assert(ptr - buffer < 64);
        return std::string(buffer, ptr);
    }
}
