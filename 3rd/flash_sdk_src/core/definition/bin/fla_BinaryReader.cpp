//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_BinaryReader.h"
#include <sstream>
#include <string.h>
#include "clover/Data.h"
#include "libra/libra_string.h"
#include "clover/KeyValue.h"
#include "../../utility/fla_ZipUtils.h"
#include "clover/ScopeGuard.h"
#include "../../utility/fla_Json.h"
#include "libra/libra_strbuf.h"
#include "fla_BinaryFormat.h"
#include "fla_BinEdgeWriterReader.h"
#include "../fla_DefinitionScene.h"
#include "../fla_DefinitionShape.h"
#include "../fla_DefinitionImage.h"
#include "../fla_DefinitionRole.h"
#include "../fla_DefinitionPlaceholder.h"
#include "../fla_DefinitionFont.h"
#include "../fla_DefinitionText.h"
#include "../fla_DefinitionPackage.h"
#include "../bin/fla_BinParseShape.h"
#include "../bin/fla_Codec.h"
#include "../../platform/fla_PlatformTraits.h"
#include "../../utility/fla_md5.h"

namespace fla
{
    static std::string nameFromJson(const std::string& json)
    {
        if (json.empty())
        {
            return json;
        }

        auto dict = clover::json::stringToValue(json);
        if (dict.isDict())
        {
            auto name = dict.dict()["name"];
            if (name.isString())
            {
                return name.string();
            }
        }
        return "";
    }

    inline uint16_t readSpriteFlags(const uint8_t*& ptr)
    {
        uint16_t flags = bin::readUI8(ptr);
        if (flags & bin::PlaceObjFlags_Use16BitFlag)
        {
            ptr--;
            flags = bin::readUI16(ptr);
        }
        return flags;
    }

    static void parseSpriteObj(const uint8_t*& ptr, bin::BinDataEncoder* encoder, PlaceObject& obj)
    {
        uint16_t flags = readSpriteFlags(ptr);

        if (flags & bin::PlaceObjFlags_Remove)
        {
            obj.setRemoveObject(true);
            obj.setDepth(bin::readUI16(ptr));
            return;
        }

        obj.setDepth(bin::readUI16(ptr));
        if (flags & bin::PlaceObjFlags_HasCharacterID)
        {
            obj.setCharacterID(bin::readUI16(ptr));
        }

        if (flags & bin::PlaceObjFlags_HasTrans)
        {
            obj.setTrans(encoder->readMatrix(ptr));
        }

        if (flags & bin::PlaceObjFlags_HasColorTrans)
        {
            obj.setColorTrans(encoder->readColorTransform(ptr));
        }

        if (flags & bin::PlaceObjFlags_HasRatio)
        {
            obj.setRatio(bin::readUI16(ptr));
        }

        if (flags & bin::PlaceObjFlags_HasClipDepth)
        {
            obj.setClipDepth(bin::readUI16(ptr));
        }

        if (flags & bin::PlaceObjFlags_HasBlendMode)
        {
            obj.setBlendMode(static_cast<BlendMode>(bin::readUI8(ptr)));
        }
    }

    void BinaryReader::parseSprite(DefinitionAnimation& sprite, bin::BinDataEncoder* encoder, const uint8_t* ptr)
    {
        int count = bin::readUI16(ptr);
        sprite.getFrames().resize(count);
        sprite.setName(nameFromJson(bin::readString(ptr)));

        uint16_t index = bin::readUI16(ptr);
        DefinitionMap<int> defintions;
        CLOVER_SCOPE_EXIT
        {
            sprite.setDefinitions(defintions);
        };

        while (index != ((uint16_t)-1))
        {
            size_t objCout = bin::readUI16(ptr);

            auto& frames = sprite.getFrames()[index];
            frames.resize(objCout);

            for (size_t i = 0; i < objCout; i++)
            {
                parseSpriteObj(ptr, encoder, frames[i]);
                auto& obj = frames[i];

                if (obj.hasCharacterID() && !obj.isRemoveObject())
                {
                    Definition::Ptr definition = readDefinition(obj.characterID());
                    if (definition)
                    {
                        defintions.push_back(definition);
                    }
                }
            }
            index = bin::readUI16(ptr);
        }
    }

    Definition::Ptr BinaryReader::parseScene_v1(const uint8_t* ptr, int len)
    {
        FLA_UNUSED(len);

        bin::BinDataEncoder_v1 encoder;
        auto scene = DefinitionScene::create();
        scene->setId(bin::readUI16(ptr));
        scene->setSize(bin::readSize(ptr));
        scene->setColor(bin::readColor(ptr));
        parseSprite(*scene, &encoder, ptr);
        return scene;
    }

    Definition::Ptr BinaryReader::parseSprite_v1(const uint8_t* ptr, int len)
    {
        FLA_UNUSED(len);
        bin::BinDataEncoder_v1 encoder;
        auto sprite = DefinitionAnimation::create();
        sprite->setId(bin::readUI16(ptr));
        parseSprite(*sprite, &encoder, ptr);
        return sprite;
    }

    Definition::Ptr BinaryReader::parseScene_v2(const uint8_t* ptr, int len)
    {
        FLA_UNUSED(len);
        bin::BinDataEncoder_v2 encoder;
        auto scene = DefinitionScene::create();
        scene->setId(bin::readUI16(ptr));
        scene->setSize(bin::readSize(ptr));
        scene->setColor(bin::readColor(ptr));
        parseSprite(*scene, &encoder, ptr);
        return scene;
    }

    Definition::Ptr BinaryReader::parseSprite_v2(const uint8_t* ptr, int len)
    {
        FLA_UNUSED(len);
        bin::BinDataEncoder_v2 encoder;
        auto sprite = DefinitionAnimation::create();
        sprite->setId(bin::readUI16(ptr));
        parseSprite(*sprite, &encoder, ptr);
        return sprite;
    }

    Definition::Ptr BinaryReader::parseShape(const uint8_t* ptr, int len)
    {
        auto savePtr = ptr;
        auto shape = DefinitionShape::create();
        shape->setId(bin::readUI16(ptr));
        shape->setBounds(bin::readRect(ptr));
        shape->setName(nameFromJson(bin::readString(ptr)));
        shape->setRawData(ptr, len - (ptr - savePtr));
        return shape;
    }

    Definition::Ptr BinaryReader::parsePackage(const uint8_t* ptr, int len)
    {
        FLA_UNUSED(len);
        auto package = DefinitionPackage::create();
        package->setId(bin::readUI16(ptr));
        package->setSpace(bin::readFloat(ptr));
        package->setTileType((DefinitionPackage::TileType)bin::readUI8(ptr));
        package->setName(nameFromJson(bin::readString(ptr)));

        size_t size = bin::readUI16(ptr);
        std::vector<fla::DefinitionScene::Ptr> scens;
        for (size_t i = 0; i < size; i++)
        {
            auto Id = bin::readUI16(ptr);
            auto definition = readDefinition(Id);
            if (definition && definition->getType() == DefinitionType::Scene)
            {
                auto scene = fla::ptr_case<DefinitionScene>(definition);
                scens.push_back(scene);
            }
        }
        package->setScenes(std::move(scens));
        return package;
    }

    Definition::Ptr BinaryReader::parsePlaceholde(const uint8_t* ptr, int len)
    {
        FLA_UNUSED(len);
        auto placeholder = DefinitionPlaceholder::create();
        placeholder->setId(bin::readUI16(ptr));
        placeholder->setBounds(bin::readRect(ptr));
        placeholder->setName(nameFromJson(bin::readString(ptr)));
        return placeholder;
    }

    Definition::Ptr BinaryReader::parseMorphShape(const uint8_t* ptr, int len)
    {
        auto savePtr = ptr;

        auto shape = DefinitionMorphShape::create();
        shape->setId(bin::readUI16(ptr));

        DefinitionMorphShape::RectT rt;
        rt.start = bin::readRect(ptr);
        rt.end = bin::readRect(ptr);
        shape->setBounds(rt);
        shape->setName(nameFromJson(bin::readString(ptr)));

        shape->setRawData(ptr, len - (ptr - savePtr));

        return shape;
    }

    Definition::Ptr BinaryReader::parseImage(const uint8_t* ptr, int len)
    {
        FLA_UNUSED(len);
        auto image = DefinitionImage::create();
        image->setId(bin::readUI16(ptr));
        image->setSize(bin::readSize(ptr));
        image->setName(nameFromJson(bin::readString(ptr)));

        Image::ImageType imageType = (Image::ImageType)bin::readUI8(ptr);
        auto dataSize = bin::readUI16Or32(ptr);
        auto implImage = PlatformTraits::Image::create();

        clover::LightData imageData(ptr, dataSize);
        implImage->setImageData(imageData, imageType);

        image->setImage(implImage);
        return image;
    }

    Definition::Ptr BinaryReader::parseText(const uint8_t* ptr, int len)
    {
        FLA_UNUSED(len);
        auto text = DefinitionText::create();
        text->setId(bin::readUI16(ptr));
        text->setTextBounds(bin::readRect(ptr));
        text->setTextMatrix(bin::readMatrix(ptr));
        text->setName(nameFromJson(bin::readString(ptr)));

        uint8_t flags = bin::readUI8(ptr);
        while (flags != 0)
        {
            TextRecord r;
            r.styleFlags = flags;

            if (r.hasFont())
            {
                uint16_t fontId = bin::readUI16(ptr);
                auto font = _dict[fontId];
                if (font && font->getType() == DefinitionType::Font)
                {
                    r.font = fla::ptr_case<DefinitionFont>(font);
                }
                r.textHeight = bin::readFloat(ptr);
            }

            if (r.hasColor())
            {
                r.color = bin::readColor(ptr);
            }

            if (r.hasXOffset())
            {
                r.offset.x = bin::readFloat(ptr);
            }

            if (r.hasYOffset())
            {
                r.offset.y = bin::readFloat(ptr);
            }

            auto size = bin::readUI16(ptr);
            for (auto i = 0; i < size; i++)
            {
                GlyphEntry en;
                en.code = bin::readUI16(ptr);
                en.advance = bin::readFloat(ptr);
                r.glyphEntries.push_back(en);
            }

            text->records().push_back(r);
            flags = bin::readUI8(ptr);
        }

        return text;
    }

    Definition::Ptr BinaryReader::parseFont(const uint8_t* ptr, int len)
    {
        auto savePtr = ptr;
        auto font = DefinitionFont::create();
        font->setId(bin::readUI16(ptr));
        font->languageCode = bin::readUI8(ptr);
        font->fontFlags = bin::readUI8(ptr);
        font->setName(nameFromJson(bin::readString(ptr)));

        auto fontSize = len - (ptr - savePtr);
        if (fontSize > 0)
        {
            if (font->hasLayout())
            {
                font->ascent = bin::readFloat(ptr);
                font->descent = bin::readFloat(ptr);
                font->leading = bin::readFloat(ptr);

                auto size = bin::readUI16(ptr);
                for (auto i = 0; i < size; i++)
                {
                    KerningRecord r;
                    r.code1 = bin::readUI16(ptr);
                    r.code2 = bin::readUI16(ptr);
                    r.adjustment = bin::readFloat(ptr);
                }
            }

            auto size = bin::readUI16(ptr);
            for (auto i = 0; i < size; i++)
            {
                FontItem item;
                item.code = bin::readUI16(ptr);
                if (font->hasLayout())
                {
                    item.bounds = bin::readRect(ptr);
                    item.advance = bin::readFloat(ptr);
                }
                bin::readString(ptr);
                font->addItem(item);

                auto* findItem = font->findItem(item.code);
                if (findItem)
                {
                    parseSingleShape(findItem->glyph, ptr);
                }
            }
        }
        return font;
    }

    BinaryReader::BinaryReader()
    {
        _frameRate = 24;
        _rootId = 0;
        _ignorePlaceHolde = false;
        _checkAuthorizedFunc = nullptr;
        _version.major = 0;
        _version.minor = 0;
    }

    Definition::Ptr BinaryReader::parseRole(const uint8_t* ptr, int len)
    {
        FLA_UNUSED(len);
        auto role = DefinitionRole::create();
        role->setId(bin::readUI16(ptr));
        const std::string& defaultName = bin::readString(ptr);
        role->setName(nameFromJson(bin::readString(ptr)));

        uint8_t flag = bin::readUI8(ptr);
        while (!(flag & bin::RoleStateFlags_IsEnd))
        {
            if (flag & bin::RoleStateFlags_IsRef)
            {
                uint16_t Id = bin::readUI16(ptr);
                auto state = bin::readString(ptr);
                auto define = readDefinition(Id);
                if (define)
                {
                    define->setDataInfo(_dataInfo);
                    role->addState(state, define);
                }
            }
            else
            {
                int tag = 0;
                int len = 0;
                bin::readTagAndLen(ptr, tag, len);
                auto savePtr = ptr;
                Definition::Ptr definition = parseDefinition(ptr, tag, len);
                ptr = savePtr + len;
                auto state = bin::readString(ptr);
                if (definition)
                {
                    definition->setIsRoleState(true);
                    definition->setDataInfo(_dataInfo);
                    role->addState(state, definition);
                }
            }
            flag = bin::readUI8(ptr);
        }

        role->setDefualtState(defaultName);
        return role;
    }

    Definition::Ptr BinaryReader::parseDefinition(const uint8_t* ptr, int tag, int len)
    {
        if (tag == bin::TagType_Placeholde && _ignorePlaceHolde)
        {
            return Definition::Ptr();
        }

        struct
        {
            int key;
            decltype(&BinaryReader::parseFont) value;
        } table[] = {
            { bin::TagType_Scene_v1, &BinaryReader::parseScene_v1 },
            { bin::TagType_Scene_v2, &BinaryReader::parseScene_v2 },
            { bin::TagType_Shape, &BinaryReader::parseShape },
            { bin::TagType_Animation_v1, &BinaryReader::parseSprite_v1 },
            { bin::TagType_Animation_v2, &BinaryReader::parseSprite_v2 },
            { bin::TagType_Role, &BinaryReader::parseRole },
            { bin::TagType_Font, &BinaryReader::parseFont },
            { bin::TagType_Text, &BinaryReader::parseText },
            { bin::TagType_MorphShape, &BinaryReader::parseMorphShape },
            { bin::TagType_Image, &BinaryReader::parseImage },
            { bin::TagType_Placeholde, &BinaryReader::parsePlaceholde },
            { bin::TagType_Package, &BinaryReader::parsePackage },
        };

        auto memberFun = clover::keyvalue_map(table, tag, nullptr);
        if (memberFun)
        {
            auto definition = (this->*memberFun)(ptr, len);
            if (definition)
            {
                definition->onFinishParse();
            }
            return definition;
        }
        return Definition::Ptr();
    }

    static inline void setErrorCode(ErrorCode* result, ErrorCode code)
    {
        if (result)
        {
            *result = code;
        }
    }

    bool BinaryReader::parseData(const uint8_t* data, size_t dataSize, ErrorCode* errorCode)
    {
        if (dataSize < sizeof(bin::Header))
        {
            setErrorCode(errorCode, ErrorCode::WrongFormat);
            return false;
        }

        const uint8_t* dataPtr = data;

        _dataBeginOffsetFile = 0;
        bin::Header header = bin::readHeader(dataPtr);
        if (strncmp((char*)header.magic, fla_header_magic, 4) != 0)
        {
            setErrorCode(errorCode, ErrorCode::WrongFormat);
            return false;
        }

        uint8_t md5[16];
        md5_state_t md5_state;
        md5_init(&md5_state);
        md5_append(&md5_state, data + 16, (int)dataSize - 16);
        md5_finish(&md5_state, md5);

        if (memcmp(md5, header.md5, 16) != 0)
        {
            setErrorCode(errorCode, ErrorCode::CheckMd5Fails);
            return false;
        }
        
        _version.major = header.majorVersion;
        _version.minor = header.minorVersion;

        if (header.majorVersion > 1 || header.minorVersion > 1)
        {
            setErrorCode(errorCode, ErrorCode::VersionIsTooHigh);
            return false;
        }

        _dict.clear();
        _catalog.clearAllItems();

        // 需要zip解压
        if (header.flags & bin::HeaderFlags_zipCompress)
        {
            const uint8_t* endPtr = data + dataSize;
            _dataBeginOffsetFile = static_cast<int>(dataPtr - data);
            fla::data_zipUncompress(dataPtr, endPtr - dataPtr).swap(_unzipData);
            dataPtr = _unzipData.begin();
            endPtr = _unzipData.end();
        }
        else
        {
            _dataBeginOffsetFile = 0;
            _unzipData.clear();
            _unzipData.pushData(data, dataSize);
            dataPtr = _unzipData.begin() + (dataPtr - data);
        }

        // 文件中是否包含目录
        _hasCatalogSection = (header.flags & bin::HeaderFlags_hasCatalog) != 0;

        _rootId = bin::readUI16(dataPtr);
        _frameRate = bin::readUI16(dataPtr);
        /*
         frameRate是浮点数，写入的时候乘以256，可以表示一些小数位
         */
        if (_frameRate > 256.0)
        {
            _frameRate /= 256.0f;
        }
        bin::readString(dataPtr);

        auto md5String = libra::str_md5HexString(header.md5);
        _dataInfo = FlaDataInfo::create();
        _dataInfo->setFrameRate(_frameRate);
        _dataInfo->setDataMd5(md5String, header.md5);

        _dataInfoWithImages = FlaDataInfoWithImages::create();
        _dataInfoWithImages->setFrameRate(_frameRate);
        _dataInfoWithImages->setDataMd5(md5String, header.md5);

        setErrorCode(errorCode, ErrorCode::Success);
        _dataBeginPtr = dataPtr;
        _dataBeginOffsetFile += (_dataBeginPtr - _unzipData.begin());
        return true;
    }

    bool BinaryReader::loadData(const void* data, size_t len, ErrorCode* errorCode)
    {
        if (_checkAuthorizedFunc && !_checkAuthorizedFunc())
        {
            setErrorCode(errorCode, ErrorCode::AuthorizedFail);
            return false;
        }

        if (data == nullptr || len == 0)
        {
            setErrorCode(errorCode, ErrorCode::ReadFileFails);
            return false;
        }
        return parseData((uint8_t*)data, len, errorCode);
    }

    void BinaryReader::buildCatalogFromSection()
    {
        const uint8_t* begin = _dataBeginPtr;
        const uint8_t* end = _unzipData.end();
        while (end - begin >= 2)
        {
            int tag = 0;
            int len = 0;
            bin::readTagAndLen(begin, tag, len);
            if (tag == bin::TagType_Catalog)
            {
                _catalog.clearAllItems();
                _catalog.readData(begin);
                break;
            }
            begin += len;
        }
    }

    void BinaryReader::buildCatalogFromRawData()
    {
        _catalog.clearAllItems();
        const uint8_t* begin = _dataBeginPtr;
        const uint8_t* end = _unzipData.end();

        while (end - begin >= 2)
        {
            auto savePtr = begin;
            int tag = 0;
            int len = 0;
            bin::readTagAndLen(begin, tag, len);
            if (tag != bin::TagType_Catalog)
            {
                const uint8_t* ptr = begin;
                uint16_t Id = bin::readUI16(ptr);
                auto offset = savePtr - _dataBeginPtr + _dataBeginOffsetFile;
                std::string name;

                switch (tag)
                {
                    case bin::TagType_Role:
                        bin::skipString(ptr);  // 跳过角色的默认动作
                        name = nameFromJson(bin::readString(ptr));
                        break;

                    case bin::TagType_Animation_v1:
                    case bin::TagType_Animation_v2:
                        ptr += sizeof(uint16_t);
                        name = nameFromJson(bin::readString(ptr));
                        break;

                    case bin::TagType_Shape:
                        bin::skipRect(ptr);
                        name = nameFromJson(bin::readString(ptr));
                        break;

                    case bin::TagType_MorphShape:
                        bin::skipRect(ptr);
                        bin::skipRect(ptr);
                        name = nameFromJson(bin::readString(ptr));
                        break;

                    case bin::TagType_Image:
                        bin::skipSize(ptr);
                        name = nameFromJson(bin::readString(ptr));
                        break;

                    default:
                        break;
                }
                _catalog.addItem(Id, name, static_cast<int>(offset));
            }
            begin += len;
        }
    }

    // 创建目录
    void BinaryReader::buildCatalog()
    {
        if (_hasCatalogSection)
        {
            buildCatalogFromSection();
        }
        else
        {
            buildCatalogFromRawData();
        }
    }

    void BinaryReader::setupDataInfo(const Definition::Ptr& definition)
    {
        auto type = definition->getType();
        if (type == DefinitionType::Shape || type == DefinitionType::MorphShape)
        {
            definition->setDataInfo(_dataInfoWithImages);
        }
        else
        {
            definition->setDataInfo(_dataInfo);
            if (type == DefinitionType::Image)
            {
                _dataInfoWithImages->addImage(fla::ptr_case<DefinitionImage>(definition));
            }
        }
    }

    Definition::Ptr BinaryReader::readDefinition(int Id)
    {
        // 查找相应Id对应的define
        auto iter = _dict.find(Id);
        if (iter != _dict.end())
        {
            return iter->second;
        }

        if (_catalog.isEmpty())
        {
            buildCatalog();
        }

        auto offset = _catalog.findOffset(Id);
        if (offset != BinCatalog::NotFound)
        {
            const uint8_t* begin = _dataBeginPtr - _dataBeginOffsetFile + offset;
            int tag = 0;
            int len = 0;
            bin::readTagAndLen(begin, tag, len);

            Definition::Ptr definition = parseDefinition(begin, tag, len);
            if (definition)
            {
                _dict[definition->getId()] = definition;
                setupDataInfo(definition);

                if (definition->getId() == Id)
                {
                    return definition;
                }
            }
        }
        return Definition::Ptr();
    }

    Definition::Ptr BinaryReader::readDefinition(const std::string& name)
    {
        if (_catalog.isEmpty())
        {
            buildCatalog();
        }

        auto Id = _catalog.findId(name);
        if (Id != BinCatalog::NotFound)
        {
            return readDefinition(Id);
        }
        return Definition::Ptr();
    }

    void BinaryReader::readAllDefinitions()
    {
        const uint8_t* begin = _dataBeginPtr;
        const uint8_t* end = _unzipData.end();

        while (end - begin >= 2)
        {
            int tag = 0;
            int len = 0;
            bin::readTagAndLen(begin, tag, len);

            auto definition = parseDefinition(begin, tag, len);
            if (definition)
            {
                _dict[definition->getId()] = definition;
                setupDataInfo(definition);
            }
            begin += len;
        }
    }

    const std::map<int, Definition::Ptr>& BinaryReader::dict() const
    {
        if (_dict.empty())
        {
            const_cast<BinaryReader*>(this)->readAllDefinitions();
        }
        return _dict;
    }

    Definition::Ptr BinaryReader::readRoot()
    {
        auto iter = _dict.find(_rootId);
        if (iter != _dict.end())
        {
            return iter->second;
        }

        if (_dict.empty())
        {
            readAllDefinitions();
            return _dict[_rootId];
        }
        return readDefinition(_rootId);
    }
}
