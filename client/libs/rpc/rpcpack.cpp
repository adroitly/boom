//
//  rpcpack.cpp
//  RPCTest
//
//  Created by HJC on 15/2/11.
//  Copyright (c) 2015年 HJC. All rights reserved.
//

#include "rpcpack.h"
#include "CRC.h"
#include "NetDataChange.h"
#include <string.h>

namespace rpc
{
    void message_pack(libra_membuf* buf, libra_slice cmd, libra_slice data)
    {
        membuf_push(buf, cmd.begin, cmd.end - cmd.begin);
        
        // cmd以'\0'结尾
        char c = 0;
        membuf_push(buf, &c, 1);
        
        if (data.begin < data.end)
        {
            membuf_push(buf, data.begin, data.end - data.begin);
        }
        
        // 插入crc
        auto crcStr = static_cast<char*>(membuf_ptr(buf, 0));
        CRCType hostCRC = CRC::get_crc16(crcStr, (unsigned int)membuf_size(buf));
        CRCType netCRC = NetDataChange::HostToNet(hostCRC);
        
        membuf_push(buf, &netCRC, sizeof(CRCType));
                
//        for (int index=0; index<buf->size; index++)
//        {
//            printf("%d,", buf->buf[index]);
//        }
//        printf("crc1=%d, crc2=%d\n", hostCRC, netCRC);
    }
    
    bool message_is_complete(const char* begin, size_t size)
    {
        if (size < 3)
        {
            return false;
        }
        
        CRCType crcPoint = *(CRCType *)(begin + size - sizeof(CRCType));
        
        unsigned int crcSize = (unsigned int)(size - sizeof(CRCType));
        CRCType hostCRC = CRC::get_crc16(begin, crcSize);
        CRCType netCRC = NetDataChange::HostToNet(hostCRC);
        
        return crcPoint == netCRC;
    }
    
    void message_unpack(const char* begin,
                        size_t size,
                        libra_slice* cmd,
                        libra_slice* data)
    {
        assert(size > sizeof(CRCType));
        const char* end = begin + size - sizeof(CRCType);
        const char* ptr_zero = str_find_char(begin, end, 0);
        cmd->begin = begin;
        cmd->end = ptr_zero;

        if (ptr_zero + 1 >= end)
        {
            data->begin = data->end = 0;
        }
        else
        {
            data->begin = ptr_zero + 1;
            data->end = end;
        }
    }
}