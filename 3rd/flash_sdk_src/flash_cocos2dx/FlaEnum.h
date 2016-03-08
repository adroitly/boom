//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLAENUM_H__
#define __FLAENUM_H__

#include <cstdint>

enum class FlaErrorCode : std::uint8_t
{
    Success          = 0,   // 成功，无错误
    ReadFileFails    = 1,   // 读取文件失败，有可能是权限不够或者无这个文件
    WrongFormat      = 2,   // 错误格式
    WrongMd5         = 3,   // 文件可能经过修改或者不完整，导致md5检验失败
    VersionIsTooHigh = 4,   // 低版本的SDK不能读取高版本的格式
    NoThisDefinition = 5,   // 读取的文件中没有根节点
    AuthorizedFail   = 6,   // 授权失败
};

enum class FlaPixelFormat : std::uint8_t
{
    RGBA8888 = 0,  // 32 bit
    RGBA4444 = 1,  // 16 bit
};

enum class FlaMovieType : std::uint8_t
{
    Null        = 0,    // 空定义
    Image       = 1,    // 图片
    Shape       = 2,    // 形状
    MorphShape  = 3,    // 形变
    Animation   = 4,    // 动画
    Scene       = 5,    // 场景
    Role        = 6,    // 角色
    Font        = 7,    // 字体
    Text        = 8,    // 文字
    ImageRef    = 9,    // 此类型已被废弃，但保留编号
    Placeholder = 10,   // 占位符
};
    
#endif
