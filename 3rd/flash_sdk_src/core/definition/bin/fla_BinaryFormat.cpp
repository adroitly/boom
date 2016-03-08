//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_BinaryFormat.h"
#include <sstream>

namespace fla
{
    namespace bin
    {
        void writeTagAndLen(Data& data, int tag, int len)
        {
            if (len < 0x3f)
            {
                uint16_t tagAndLen = (tag << 6) | len;
                writeUI16(data, tagAndLen);
            }
            else
            {
                uint16_t tagAndLen = (tag << 6) | 0x3f;
                writeUI16(data, tagAndLen);
                writeUI32(data, len);
            }
        }

        size_t tagAndLenBytes(int len)
        {
            if (len < 0x3f)
            {
                return 2;
            }
            else
            {
                return 6;
            }
        }

        void readTagAndLen(const uint8_t*& ptr, int& tag, int& len)
        {
            int tagAndLen = readUI16(ptr);
            int tagLen = tagAndLen & 0x3f;
            if (tagLen == 0x3f)
            {
                tagLen = readUI32(ptr);
            }
            tag = tagAndLen >> 6;
            len = tagLen;
        }
    }
}
