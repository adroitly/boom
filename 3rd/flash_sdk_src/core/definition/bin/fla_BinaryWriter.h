//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_BINARYWRITER__
#define __FLA_BINARYWRITER__

#include "fla_BinaryFormat.h"
#include "fla_BaseWriter.h"
#include "clover/Data.h"
#include "fla_ScaleMap.h"

namespace fla
{
    namespace bin
    {
        class BinDataCoder;
    }
    
    // 写入二进制数据
    class BinaryWriter : public BaseWriter<bin::Data>
    {
    public:
        typedef enum
        {
            CatoryType_None,
            CatoryType_Has,
        } CatoryType;

        BinaryWriter(const Definition::Ptr& root, float frameRate);
        void writeToFile(const std::string& filePath, const fla::ScaleMap& scaleMap, CatoryType catoryType);
        void writeToData(clover::Data& data, const fla::ScaleMap& scaleMap, CatoryType catoryType);

    private:
        virtual bool isAvailable(const bin::Data& data) const override;

        template <typename ShapeT>
        void exportShapeImage(const ShapeT& shape);

        bin::Data write(const DefinitionShape::Ptr& define, float scale) override;
        bin::Data write(const DefinitionAnimation::Ptr& define, float scale) override;
        bin::Data write(const DefinitionMorphShape::Ptr& define, float scale) override;
        bin::Data write(const DefinitionScene::Ptr& define, float scale) override;
        bin::Data write(const DefinitionRole::Ptr& define, float scale) override;
        bin::Data write(const DefinitionFont::Ptr& font, float scale) override;
        bin::Data write(const DefinitionText::Ptr& text, float scale) override;
        bin::Data write(const DefinitionImage::Ptr& image, float scale) override;
        bin::Data write(const DefinitionPlaceholder::Ptr& ptr, float scale) override;
        bin::Data write(const DefinitionPackage::Ptr& ptr, float scale) override;

        bin::Data exportCatory(size_t headerSize);

        bool exportSpriteFrame(bin::Data& data,
                               bin::BinDataCoder* coder,
                               const DefinitionAnimation& define,
                               AnimationFrame& currentFrame,
                               int frameIndex,
                               float scale);

        void exportSprite(bin::Data& data, bin::BinDataCoder* coder, const DefinitionAnimation& define, float scale);
        void exportBinData(bin::Data& headerData, bin::Data& zipData, CatoryType catoryType);
    };

    template <typename ShapeT>
    void BinaryWriter::exportShapeImage(const ShapeT& shape)
    {
        // 输出用到的Bitmap
        assert(shape->getDataInfo());
        for (auto& fillStyle : shape->getShape().fillStyles)
        {
            if (fillStyle.isBitmapStyle())
            {
                auto bitmapId = fillStyle.bitmapId();
                auto bitmap = shape->getDataInfoWithImages()->findImage(bitmapId);
                if (bitmap)
                {
                    exportDefinition(bitmap);
                }
            }
        }
    }
}

#endif
