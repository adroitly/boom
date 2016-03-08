//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_Error.h"
#include "clover/KeyValue.h"

namespace fla
{
    static struct
    {
        ErrorCode key;
        const char* value;
    } s_descTable[] = { { ErrorCode::Success, "success" },
                        { ErrorCode::ReadFileFails, "read file fails" },
                        { ErrorCode::WrongFormat, "wrong format" },
                        { ErrorCode::CheckMd5Fails, "check md5 fails" },
                        { ErrorCode::VersionIsTooHigh, "version is too high" } };

    std::string descriptionFromCode(ErrorCode code)
    {
        return clover::keyvalue_map(s_descTable, code, "unkown error");
    }
}
