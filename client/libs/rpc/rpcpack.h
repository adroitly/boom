//
//  rpcpack.h
//  RPCTest
//
//  Created by HJC on 15/2/11.
//  Copyright (c) 2015年 HJC. All rights reserved.
//

#ifndef __RPCPACK_H__
#define __RPCPACK_H__

#include "libra/libra_membuf.h"
#include "libra/libra_string.h"

namespace rpc
{
    typedef unsigned short CRCType;
    void message_pack(libra_membuf* buf, libra_slice cmd, libra_slice data);
    
    // 检查数据是否完整
    bool message_is_complete(const char* begin, size_t size);
    void message_unpack(const char* begin,
                        size_t size,
                        libra_slice* cmd,
                        libra_slice* data);
}

#endif
