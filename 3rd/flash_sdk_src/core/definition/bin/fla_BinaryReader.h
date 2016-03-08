//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_BINARYREADER_H__
#define __FLA_BINARYREADER_H__

#include <map>
#include "clover/Data.h"
#include "../fla_Definition.h"
#include "../fla_DefinitionUtils.h"
#include "../fla_FlaDataInfo.h"
#include "./fla_BinCatalog.h"
#include "../../base/fla_Error.h"
#include "../fla_DefinitionMap.h"

namespace fla
{
    namespace bin
    {
        class BinDataEncoder;
    }

    // 读入二进制格式的动画矢量数据，
    // 写入的类对应为 fla::BinaryWriter
    class DefinitionAnimation;
    class BinaryReader
    {
    public:
        struct Version
        {
            uint8_t major;
            uint8_t minor;
        };
        
        typedef bool (*CheckAuthorizedFunc)();
        BinaryReader();

        float getFrameRate() const
        {
            return _frameRate;
        }
        
        const Version& getVersion() const
        {
            return _version;
        }

        int getRootId() const
        {
            return _rootId;
        }

        const std::map<int, Definition::Ptr>& dict() const;

        void setIgnorePlaceHolde(bool ignorePlaceHolde)
        {
            _ignorePlaceHolde = ignorePlaceHolde;
        }

        void setCheckAuthorizedFunc(const CheckAuthorizedFunc& func)
        {
            _checkAuthorizedFunc = func;
        }

        bool loadData(const void* data, size_t len, ErrorCode* errorCode);

        void readAllDefinitions();
        Definition::Ptr readRoot();
        Definition::Ptr readDefinition(int Id);
        Definition::Ptr readDefinition(const std::string& name);

    private:
        bool parseData(const uint8_t* data, size_t len, ErrorCode* errorCode);
        bool parseHeader(const uint8_t*& ptr, int len);
        Definition::Ptr parseDefinition(const uint8_t* ptr, int tag, int len);
        Definition::Ptr parseScene_v1(const uint8_t* ptr, int len);
        Definition::Ptr parseSprite_v1(const uint8_t* ptr, int len);

        Definition::Ptr parseScene_v2(const uint8_t* ptr, int len);
        Definition::Ptr parseSprite_v2(const uint8_t* ptr, int len);

        Definition::Ptr parseMorphShape(const uint8_t* ptr, int len);
        Definition::Ptr parseShape(const uint8_t* ptr, int len);
        Definition::Ptr parseRole(const uint8_t* ptr, int len);
        Definition::Ptr parseFont(const uint8_t* ptr, int len);
        Definition::Ptr parseText(const uint8_t* ptr, int len);
        Definition::Ptr parseImage(const uint8_t* ptr, int len);
        Definition::Ptr parsePlaceholde(const uint8_t* ptr, int len);
        Definition::Ptr parsePackage(const uint8_t* ptr, int len);
        void setupDataInfo(const Definition::Ptr& definition);
        void parseSprite(DefinitionAnimation& sprite, bin::BinDataEncoder* encoder, const uint8_t* ptr);
        void buildCatalog();
        void buildCatalogFromSection();
        void buildCatalogFromRawData();

    private:
        Version _version;
        fla::FlaDataInfo::Ptr _dataInfo;
        fla::FlaDataInfoWithImages::Ptr _dataInfoWithImages;
        std::map<int, Definition::Ptr> _dict;
        fla::BinCatalog _catalog;
        clover::Data _unzipData;
        float _frameRate;
        int _rootId;
        int _dataBeginOffsetFile;
        const uint8_t* _dataBeginPtr;
        CheckAuthorizedFunc _checkAuthorizedFunc;
        bool _hasCatalogSection;
        bool _ignorePlaceHolde;
    };
}

#endif
