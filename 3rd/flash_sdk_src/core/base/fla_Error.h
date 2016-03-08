//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_ERROR_H__
#define __FLA_ERROR_H__

#include <string>
#include <cstdint>

namespace fla
{
    enum class ErrorCode : int8_t
    {
        Success = 0,           // 成功，无错误
        ReadFileFails = 1,     // 读取文件失败，有可能是权限不够或者无这个文件
        WrongFormat = 2,       // 错误格式
        CheckMd5Fails = 3,     // 文件可能经过修改或者不完整，导致md5检验失败
        VersionIsTooHigh = 4,  // 不能读取高版本
        NoThisDefine = 5,      // 读取的文件中没有根节点
        AuthorizedFail = 6,    // 授权失败
    };

    std::string descriptionFromCode(ErrorCode code);
}

#endif
