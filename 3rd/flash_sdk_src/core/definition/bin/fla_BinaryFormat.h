//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_BINARYFORMATE__
#define __FLA_BINARYFORMATE__

#include <stdint.h>
#include <vector>
#include "fla_BinData.h"
#include "../../base/fla_Base.h"

namespace fla
{
    namespace bin
    {
        enum TagType
        {
            TagType_Header     = 0,
            TagType_Shape      = 1,     // 形状
            TagType_Animation_v1  = 2,     // 动画
            TagType_Scene_v1   = 3,     // 场景
            TagType_Role       = 4,     // 角色
            TagType_Font       = 5,     // 字体
            TagType_Unsupport  = 6,     // (不再支持，但需要保留)
            TagType_Text       = 7,     // 文字
            TagType_MorphShape = 8,     // 形变
            TagType_ImageRef   = 9,     // 图片引用, (不再支持，但需要保留）
            TagType_Catalog    = 10,    // 目录表，指明每个定义在文件中所处的位置
            TagType_Image      = 11,    // 图片
            TagType_Placeholde = 12,    // 占位
            TagType_Package    = 13,
            TagType_Animation_v2  = 14,
            TagType_Scene_v2   = 15,
        };

        enum PlaceObjFlags
        {
            PlaceObjFlags_Use16BitFlag   = 0x01,
            PlaceObjFlags_Remove         = 0x02,
            PlaceObjFlags_HasCharacterID = 0x04,
            PlaceObjFlags_HasTrans       = 0x08,
            PlaceObjFlags_HasColorTrans  = 0x10,
            PlaceObjFlags_HasRatio       = 0x20,
            PlaceObjFlags_HasClipDepth   = 0x40,
            PlaceObjFlags_HasBlendMode   = 0x80,
        };

        enum RoleStateFlags
        {
            RoleStateFlags_IsRef = 0x01,
            RoleStateFlags_IsEnd = 0x02,
        };

        enum
        {
            HeaderFlags_zipCompress = 0x0001,// 使用zip压缩
            HeaderFlags_hasCatalog  = 0x0002,// 文件是否包含目录表
        };

        enum
        {
            LineStyleFlag_OnlyWidthAndColor = 0x0001,
        };

        struct Header
        {
            uint8_t md5[16];        //  检验，默认为md5

            // 从这里开始计算md5，包括版本号和flags
            uint8_t magic[4];       //  魔数，一定为, atjc,
            uint8_t majorVersion;   //  主版本号
            uint8_t minorVersion;   //  次版本号
            uint32_t flags;         //  标志位, 指明后面的数字是否有压缩
            // 当zipCompress标志位为1之后，后面的数据需要先进行zip解压
        };
        
#if FLA_FOR_PUBLIC
        #define fla_header_magic    "ffjc"
#else
        #define fla_header_magic    "atjc"
#endif
    

        /////////////////////////////////////////////////////////////////

        ///////////////
        // Tag
        void writeTagAndLen(Data& data, int tag, int len);
        size_t tagAndLenBytes(int len);
        void readTagAndLen(const uint8_t*& ptr, int& tag, int& len);

        //////////////////
        // header
        inline void writeHeader(Data& data, const Header& header)
        {
            writeBytes(data, header.md5, 16);
            writeBytes(data, header.magic, 4);
            writeUI8(data, header.majorVersion);
            writeUI8(data, header.minorVersion);
            writeUI32(data, header.flags);
        }

        inline int headerBytes()
        {
            return 16 + 4 + 1 + 1 + 4;
        }

        inline Header readHeader(const uint8_t*& ptr)
        {
            Header header;
            readBytes(ptr, header.md5, 16);
            readBytes(ptr, header.magic, 4);
            header.majorVersion = readUI8(ptr);
            header.minorVersion = readUI8(ptr);
            header.flags = readUI32(ptr);
            return header;
        }
    }
}

#endif
