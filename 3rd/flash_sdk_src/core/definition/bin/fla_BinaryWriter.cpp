//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_BinaryWriter.h"
#include <sstream>
#include <string.h>
#include "clover/Data.h"
#include "clover/KeyValue.h"
#include "../../utility/fla_ZipUtils.h"
#include "../../utility/fla_Json.h"
#include "fla_BinEdgeWriterReader.h"
#include "../fla_DefinitionShape.h"
#include "../fla_DefinitionAnimation.h"
#include "../fla_DefinitionScene.h"
#include "../fla_DefinitionRole.h"
#include "../fla_DefinitionFont.h"
#include "../fla_DefinitionText.h"
#include "../../utility/fla_md5.h"
#include "../../graphics/fla_transToImage.h"
#include "../../definition/bin/fla_BinCatalog.h"
#include "../../definition/bin/fla_Codec.h"

namespace fla
{
    struct CoderTraits
    {
        typedef bin::BinDataCoder_v2 type;
        enum
        {
            Scene_Tag = bin::TagType_Scene_v2
        };
        enum
        {
            Sprite_Tag = bin::TagType_Animation_v2
        };
    };

    static struct
    {
        DefinitionType key;
        int value;
    } s_tagTables[] = {
        { DefinitionType::Scene, CoderTraits::Scene_Tag },
        { DefinitionType::Animation, CoderTraits::Sprite_Tag },
        { DefinitionType::Shape, bin::TagType_Shape },
        { DefinitionType::Role, bin::TagType_Role },
        { DefinitionType::Font, bin::TagType_Font },
        { DefinitionType::Image, bin::TagType_Image },
        { DefinitionType::Text, bin::TagType_Text },
        { DefinitionType::MorphShape, bin::TagType_MorphShape },
        { DefinitionType::ImageRef, bin::TagType_ImageRef },
        { DefinitionType::Placeholder, bin::TagType_Placeholde },
        { DefinitionType::Package, bin::TagType_Package },
    };

    static int GetTag(const Definition::Ptr& define)
    {
        return clover::keyvalue_map(s_tagTables, define->getType(), -1);
    }

    // 将名字编码成json格式，也就是
    // {name:xxx}
    static std::string jsonFromName(const std::string& name)
    {
        if (name.empty())
        {
            return name;
        }

        clover::json::Value dict = clover::json::Value::makeDict();
        dict.dict()["name"] = clover::json::Value(name);
        return clover::json::valueToString(dict);
    }

    // 将data中的数据写入文件
    inline void file_writeData(FILE* file, const bin::Data& data)
    {
        fwrite(&data[0], 1, data.size(), file);
    }

    // 将矩阵缩放
    inline Matrix matrixScale(const Matrix& matrix, float scale)
    {
        return Matrix::matrixScale(matrix, scale);
    }

    inline Holder<Matrix, 2> matrixScale(const Holder<Matrix, 2>& matrix, float scale)
    {
        Holder<Matrix, 2> result;
        result.start = matrixScale(matrix.start, scale);
        result.end = matrixScale(matrix.end, scale);
        return result;
    }

    // 写入描边样式
    template <int N>
    static void writeLineStyle(bin::Data& data, const LineStyleBase<N>& lineStyle, float scale)
    {
        bin::writeFloat(data, lineStyle.width * scale);
        bin::writeColor(data, lineStyle.color);

        uint8_t flags = 0;
        if (lineStyle.onlyWidthAndColor)
        {
            flags = bin::LineStyleFlag_OnlyWidthAndColor;
        }

        bin::writeUI8(data, flags);

        if (!lineStyle.onlyWidthAndColor)
        {
            bin::writeUI8(data, static_cast<uint8_t>(lineStyle.startCapStyle));
            bin::writeUI8(data, static_cast<uint8_t>(lineStyle.endCapStyle));
            bin::writeUI8(data, static_cast<uint8_t>(lineStyle.jointStyle));
            bin::writeFloat(data, lineStyle.miterLimitFactor * scale);
        }
    }

    // 写入填充样式
    template <int N>
    static void writeFillStyle(bin::Data& data,
                               const FillStyleBase<N>& fillStyle,
                               float scale,
                               const ScaleMap& scaleMap)
    {
        auto fillType = fillStyle.fillType();

        // 暂时不支持Fill_FocalRadialGradient输出
        if (fillType == FillType::FocalRadialGradient)
        {
            fillType = FillType::RadialGradient;
        }

        auto saveLengt = data.size();
        bin::writeUI8(data, (uint8_t)fillType);

        // 颜色填充
        if (fillStyle.isSolidStyle())
        {
            bin::writeColor(data, fillStyle.solidColor());
        }

        // 渐变填充
        else if (fillStyle.isGradientStyle())
        {
            auto matrix = matrixScale(fillStyle.gradient().matrix(), scale);
            bin::writeMatrix(data, matrix, scale);

            if (fillType == FillType::FocalRadialGradient)
            {
                bin::writeFloat(data, fillStyle.gradient().focalPoint());
            }

            auto count = fillStyle.gradient().records().size();
            bin::writeUI16(data, count);
            for (auto& r : fillStyle.gradient().records())
            {
                bin::writeColor(data, r.color);
                bin::writeUI8(data, r.location * 255);
            }
        }
        // 图片填充
        else if (fillStyle.isBitmapStyle())
        {
            auto bitmapScale = scaleMap.getScale(fillStyle.bitmapId());

            auto matrix = matrixScale(fillStyle.bitmapMatrix(), scale / bitmapScale);
            bin::writeMatrix(data, matrix, scale);
            bin::writeUI16(data, fillStyle.bitmapId());
        }
        else
        {
            data[saveLengt] = (uint8_t)FillType::Solid;
            bin::writeColor(data, Color4());
        }
    }

    // 写入边
    static void writeEdgeList(bin::Data& data, const EdgeList& edges, float scale)
    {
        Point curPt = edges.firstPt();
        bin::EdgeWriterReader edgeHelper(scale, curPt);

        for (auto edge : edges)
        {
            bool useCompressed = !edges.isLastEdge(edge);
            if (edge->getType() == EdgeType::LineTo)
            {
                fla::LineTo* lineTo = (fla::LineTo*)edge;
                edgeHelper.writeEdgeLine(data, *lineTo, useCompressed);
            }
            else if (edge->getType() == EdgeType::CurveTo)
            {
                fla::CurveTo* curveTo = (fla::CurveTo*)edge;
                edgeHelper.writeEdgeCurve(data, *curveTo, useCompressed);
            }
        }
        bin::writeUI8(data, bin::EdgeWriterReader::EdgeType_End);
    }

    // 路径
    static void exportPaths(bin::Data& data, const std::vector<MorphPath>& paths, float scale)
    {
        bin::writeUI16Or32(data, paths.size());
        for (auto& path : paths)
        {
            bin::writePoint(data, path.edges<0>().firstPt(), scale);
            bin::writePoint(data, path.edges<1>().firstPt(), scale);
            bin::writeUI16(data, path.lineStyle() + 1);
            bin::writeUI16(data, path.fillStyle() + 1);

            writeEdgeList(data, path.edges<0>(), scale);
            writeEdgeList(data, path.edges<1>(), scale);

            exportPaths(data, path.subPaths(), scale);
        }
    }

    static void exportPaths(bin::Data& data, const std::vector<Path>& paths, float scale)
    {
        bin::writeUI16Or32(data, paths.size());
        for (auto& path : paths)
        {
            bin::writePoint(data, path.edges<0>().firstPt(), scale);
            bin::writeUI16(data, path.lineStyle() + 1);
            bin::writeUI16(data, path.fillStyle() + 1);

            writeEdgeList(data, path.edges<0>(), scale);

            exportPaths(data, path.subPaths(), scale);
        }
    }

    // 形状
    template <typename ShapeT>
    static void exportSingleShape(bin::Data& data, const ShapeT& shape, float scale, const ScaleMap& scaleMap)
    {
        bin::writeUI16(data, shape.lineStyles.size());
        for (auto& iter : shape.lineStyles)
        {
            writeLineStyle(data, iter, scale);
        }

        bin::writeUI16(data, shape.fillStyles.size());
        for (auto& iter : shape.fillStyles)
        {
            writeFillStyle(data, iter, scale, scaleMap);
        }

        exportPaths(data, shape.paths, scale);
    }

    bin::Data BinaryWriter::write(const DefinitionMorphShape::Ptr& define, float scale)
    {
        // 输出用到的Bitmap
        exportShapeImage(define);

        bin::Data data;
        bin::writeUI16(data, define->getId());
        bin::writeRect(data, define->bounds().start, scale);
        bin::writeRect(data, define->bounds().end, scale);
        bin::writeString(data, jsonFromName(define->getName()));  // 附加信息

        exportSingleShape(data, define->getShape(), scale, getScaleMap());
        return data;
    }

    bin::Data BinaryWriter::write(const DefinitionPlaceholder::Ptr& define, float scale)
    {
        bin::Data data;
        bin::writeUI16(data, define->getId());
        bin::writeRect(data, define->getBounds(), scale);
        bin::writeString(data, jsonFromName(define->getName()));
        return data;
    }

    bin::Data BinaryWriter::write(const DefinitionShape::Ptr& define, float scale)
    {
        exportShapeImage(define);
        bin::Data data;
        bin::writeUI16(data, define->getId());
        bin::writeRect(data, define->getBounds(), scale);
        bin::writeString(data, jsonFromName(define->getName()));  // 附加信息
        exportSingleShape(data, define->getShape(), scale, getScaleMap());
        return data;
    }

    bool BinaryWriter::exportSpriteFrame(bin::Data& data,
                                         bin::BinDataCoder* coder,
                                         const DefinitionAnimation& sprite,
                                         AnimationFrame& currentFrame,
                                         int frameIndex,
                                         float scale)
    {
        auto& frame = sprite.getFrames()[frameIndex];
        if (frame.empty())
        {
            return false;
        }

        bin::writeUI16(data, frameIndex);
        bin::writeUI16(data, frame.size());

        AnimationFrame preveFrame = currentFrame;
        sprite.gotoFrame(frameIndex, currentFrame);
        Matrix trans;

        for (auto& obj : frame)
        {
            if (obj.isRemoveObject())
            {
                uint8_t flags = 0;
                flags |= bin::PlaceObjFlags_Remove;
                bin::writeUI8(data, flags);
                bin::writeUI16(data, obj.depth());
            }
            else
            {
                uint8_t flags = 0;
                auto saveLength = data.size();

                bin::writeUI8(data, flags);
                bin::writeUI16(data, obj.depth());

                if (obj.hasCharacterID())
                {
                    flags |= bin::PlaceObjFlags_HasCharacterID;
                    bin::writeUI16(data, obj.characterID());
                    Definition::Ptr define = sprite.findDefinition(obj.characterID());
                    if (define)
                    {
                        exportDefinition(define);
                    }
                }

                if (computePlaceTrans(obj, preveFrame, currentFrame, scale, trans))
                {
                    flags |= bin::PlaceObjFlags_HasTrans;
                    coder->writeMatrix(data, trans, scale);
                }

                if (obj.hasColorTrans())
                {
                    flags |= bin::PlaceObjFlags_HasColorTrans;
                    coder->writeColorTransform(data, obj.colorTrans());
                }

                if (obj.hasRatio())
                {
                    flags |= bin::PlaceObjFlags_HasRatio;
                    bin::writeUI16(data, obj.ratio());
                }

                if (obj.hasClipDepth())
                {
                    flags |= bin::PlaceObjFlags_HasClipDepth;
                    bin::writeUI16(data, obj.clipDepth());
                }

                if (obj.hasBlendMode())
                {
                    flags |= bin::PlaceObjFlags_HasBlendMode;
                    bin::writeUI8(data, static_cast<uint8_t>(obj.blendMode()));
                }

                *reinterpret_cast<decltype(flags)*>(&data[saveLength]) = flags;
            }
        }
        return true;
    }

    void BinaryWriter::exportSprite(bin::Data& data,
                                    bin::BinDataCoder* coder,
                                    const DefinitionAnimation& sprite,
                                    float scale)
    {
        bin::writeUI16(data, sprite.getFrameCount());
        bin::writeString(data, jsonFromName(sprite.getName()));  // 附加信息

        AnimationFrame currentFrame;
        for (size_t index = 0; index < sprite.getFrames().size(); index++)
        {
            exportSpriteFrame(data, coder, sprite, currentFrame, (int)index, scale);
        }
        bin::writeUI16(data, (uint16_t)(-1));  // 结束标记
    }

    bin::Data BinaryWriter::write(const DefinitionAnimation::Ptr& define, float scale)
    {
        bin::Data data;
        CoderTraits::type coder;

        bin::writeUI16(data, define->getId());
        exportSprite(data, &coder, *define, scale);
        return data;
    }

    bin::Data BinaryWriter::write(const DefinitionImage::Ptr& image, float scale)
    {
        bin::Data data;
        auto implImage = image->getImage();
        if (implImage)
        {
            auto imageSize = image->getSize();
            if (image->isSupportScale() && scale != 1.0f)
            {
                implImage = implImage->scaleImageData(scale, image->getSize(), &imageSize);
            }

            bin::writeUI16(data, image->getId());
            bin::writeSize(data, imageSize, 1.0);
            bin::writeString(data, jsonFromName(image->getName()));  // 附加信息

            bin::writeUI8(data, (uint8_t)implImage->getImageType());
            bin::writeUI16Or32(data, implImage->getImageData().size());
            bin::writeData(data, implImage->getImageData());
        }
        return data;
    }

    bin::Data BinaryWriter::write(const DefinitionScene::Ptr& definition, float scale)
    {
        bin::Data data;
        CoderTraits::type coder;
        bin::writeUI16(data, definition->getId());
        bin::writeSize(data, definition->getSize(), scale);

        bin::writeColor(data, definition->getColor());
        exportSprite(data, &coder, *definition, scale);
        return data;
    }

    bin::Data BinaryWriter::write(const DefinitionPackage::Ptr& ptr, float scale)
    {
        bin::Data data;
        bin::writeUI16(data, ptr->getId());
        bin::writeFloat(data, ptr->getSpace() * scale);
        bin::writeUI8(data, (uint8_t)ptr->getTileType());
        bin::writeString(data, jsonFromName(ptr->getName()));

        auto& scenes = ptr->getScenes();
        bin::writeUI16(data, scenes.size());
        for (auto& scene : scenes)
        {
            exportDefinition(scene);
            bin::writeUI16(data, scene->getId());
        }
        return data;
    }

    bin::Data BinaryWriter::write(const DefinitionFont::Ptr& font, float scale)
    {
        bin::Data data;
        bin::writeUI16(data, font->getId());
        bin::writeUI8(data, font->languageCode);
        bin::writeUI8(data, font->fontFlags);
        bin::writeString(data, jsonFromName(font->getName()));

        if (font->hasLayout())
        {
            bin::writeFloat(data, font->ascent);
            bin::writeFloat(data, font->descent);
            bin::writeFloat(data, font->leading);

            bin::writeUI16(data, font->kerningTables().size());
            for (auto& record : font->kerningTables())
            {
                bin::writeUI16(data, record.code1);
                bin::writeUI16(data, record.code2);
                bin::writeFloat(data, record.adjustment);
            }
        }

        bin::writeUI16(data, font->items().size());
        for (auto& iter : font->items())
        {
            auto& item = iter.second;
            bin::writeUI16(data, item.code);

            if (font->hasLayout())
            {
                bin::writeRect(data, item.bounds, scale);
                bin::writeFloat(data, item.advance);
            }
            bin::writeString(data, "");  // 附加信息
            exportSingleShape(data, item.glyph, scale, getScaleMap());
        }

        return data;
    }

    bin::Data BinaryWriter::write(const DefinitionText::Ptr& text, float scale)
    {
        bin::Data data;
        bin::writeUI16(data, text->getId());
        bin::writeRect(data, text->textBounds(), scale);
        bin::writeMatrix(data, text->textMatrix(), scale);
        bin::writeString(data, jsonFromName(text->getName()));

        for (auto& r : text->records())
        {
            // 如果有字体，但是字体为空，应该跳过
            if (r.hasFont() && !r.font)
            {
                continue;
            }

            bin::writeUI8(data, r.styleFlags);
            if (r.hasFont())
            {
                exportDefinition(r.font);
                bin::writeUI16(data, r.font->getId());
                bin::writeFloat(data, r.textHeight * scale);
            }

            if (r.hasColor())
            {
                bin::writeColor(data, r.color);
            }

            if (r.hasXOffset())
            {
                bin::writeFloat(data, r.offset.x * scale);
            }

            if (r.hasYOffset())
            {
                bin::writeFloat(data, r.offset.y * scale);
            }

            bin::writeUI16(data, r.glyphEntries.size());
            for (auto& entry : r.glyphEntries)
            {
                bin::writeUI16(data, entry.code);
                bin::writeFloat(data, entry.advance * scale);
            }
        }
        bin::writeUI8(data, 0);
        return data;
    }

    bin::Data BinaryWriter::write(const DefinitionRole::Ptr& define, float scale)
    {
        bin::Data data;
        bin::writeUI16(data, define->getId());
        bin::writeString(data, define->defaultName());
        bin::writeString(data, jsonFromName(define->getName()));

        for (auto& state : define->getStates())
        {
            uint8_t flag = 0;
            if (!state.definition->isRoleState())
            {
                flag |= bin::RoleStateFlags_IsRef;
            }

            bin::writeUI8(data, flag);
            if (state.definition->isRoleState())
            {
                bin::Data tmpData = exportDataDefine(state.definition, scale);
                bin::writeTagAndLen(data, GetTag(state.definition), (int)tmpData.size());
                bin::writeData(data, tmpData);
                bin::writeString(data, state.name);
            }
            else
            {
                bin::writeUI16(data, state.definition->getId());
                bin::writeString(data, state.name);
            }
        }

        uint8_t flag = bin::RoleStateFlags_IsEnd;
        bin::writeUI8(data, flag);
        return data;
    }

    bin::Data BinaryWriter::exportCatory(size_t headerSize)
    {
        fla::BinCatalog catalog;  // 目录项
        for (auto& item : getItems())
        {
            auto define = item->define;
            catalog.addItem(define->getId(), define->getName(), 0);
        }

        bin::Data catalogData;
        catalog.writeToData(catalogData);

        size_t fileOffset = headerSize;
        fileOffset += catalogData.size() + bin::tagAndLenBytes((int)catalogData.size());
        catalog.clearAllItems();

        for (auto& item : getItems())
        {
            auto define = item->define;
            catalog.addItem(define->getId(), define->getName(), (int)fileOffset);
            fileOffset += item->data.size() + bin::tagAndLenBytes((int)item->data.size());
        }

        catalogData.clear();
        catalog.writeToData(catalogData);
        return catalogData;
    }

    void BinaryWriter::exportBinData(bin::Data& headerData, bin::Data& zipData, CatoryType catoryType)
    {
        assert(headerData.size() == 0);
        assert(zipData.size() == 0);

        exportDefinition(getRoot());

        bin::writeUI16(zipData, getRoot()->getId());
        bin::writeUI16(zipData, getFrameRate() * 256);
        bin::writeString(zipData, "");  // 附加信息

        if (catoryType == CatoryType_Has)
        {
            bin::Data catoryData = exportCatory(bin::headerBytes() + (int)zipData.size());
            if (catoryData.size() > 0)
            {
                bin::writeTagAndLen(zipData, bin::TagType_Catalog, (int)catoryData.size());
                bin::writeData(zipData, catoryData);
            }
        }

        for (auto& item : getItems())
        {
            bin::writeTagAndLen(zipData, GetTag(item->define), (int)item->data.size());
            bin::writeData(zipData, item->data);
        }

        bool zipCompress = false;
        if (catoryType == CatoryType_None)
        {
            auto tmpData = data_zipCompress(&zipData[0], (int)zipData.size());
            if (!tmpData.empty())
            {
                zipData = bin::Data(tmpData.begin(), tmpData.end());
                zipCompress = true;
            }
        }

        bin::Header header;
        char magic[] = fla_header_magic;
        strncpy((char*)header.magic, magic, 4);
        header.flags = 0;
        header.majorVersion = 1;
        header.minorVersion = 1;

        if (zipCompress)
        {
            header.flags |= bin::HeaderFlags_zipCompress;
        }

        if (catoryType == CatoryType_Has)
        {
            header.flags |= bin::HeaderFlags_hasCatalog;
        }

        bin::writeHeader(headerData, header);

        md5_state_t md5_state;
        md5_init(&md5_state);
        md5_append(&md5_state, &headerData[16], (int)headerData.size() - 16);
        md5_append(&md5_state, &zipData[0], (int)zipData.size());
        md5_finish(&md5_state, &headerData[0]);
    }

    BinaryWriter::BinaryWriter(const Definition::Ptr& root, float frameRate) : BaseWriter<bin::Data>(root, frameRate)
    {
    }

    void BinaryWriter::writeToData(clover::Data& data, const fla::ScaleMap& scaleMap, CatoryType catoryType)
    {
        data.clear();

        bin::Data zipData;
        bin::Data headerData;
        setScaleMap(scaleMap);

        exportBinData(headerData, zipData, catoryType);

        data.pushData(&headerData[0], headerData.size());
        data.pushData(&zipData[0], zipData.size());
    }

    void BinaryWriter::writeToFile(const std::string& filePath, const fla::ScaleMap& scaleMap, CatoryType catoryType)
    {
        clover::Data data;
        writeToData(data, scaleMap, catoryType);
        data.writeToFile(filePath);
    }

    bool BinaryWriter::isAvailable(const bin::Data& data) const
    {
        return data.size() > 0;
    }
}
