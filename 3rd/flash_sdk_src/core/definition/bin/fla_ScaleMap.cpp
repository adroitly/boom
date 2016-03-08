//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_ScaleMap.h"
#include "../fla_DefinitionAnimation.h"
#include "../fla_DefinitionShape.h"
#include "../fla_DefinitionRole.h"
#include "../fla_DefinitionUtils.h"
#include <sstream>

namespace fla
{
    static float s_computeMatrixScale(const Matrix& matrix)
    {
        auto scaleX = matrix.computeScaleX();
        auto scaleY = matrix.computeScaleY();
        return std::max(scaleX, scaleY);
    }

    void ScaleMap::exportSpriteFrameScales(const DefinitionAnimation::Ptr& sprite, float scale)
    {
        AnimationFrame currentFrame;
        auto frameSize = sprite->getFrames().size();
        for (size_t idx = 0; idx < frameSize; idx++)
        {
            sprite->gotoFrame(static_cast<int>(idx), currentFrame);
            for (auto& obj : currentFrame)
            {
                if (obj.hasCharacterID() && obj.hasTrans())
                {
                    auto define = sprite->findDefinition(obj.characterID());
                    if (define)
                    {
                        auto curScale = s_computeMatrixScale(obj.trans());
                        exportBestScale(define, scale * curScale);
                    }
                }
            }
        }
    }

    void ScaleMap::exportShapeImageScales(const DefinitionShape::Ptr& shape, float scale)
    {
        for (auto& style : shape->getShape().fillStyles)
        {
            if (style.isBitmapStyle())
            {
                auto bitmap = shape->findImage(style.bitmapId());
                auto curScale = s_computeMatrixScale(style.bitmapMatrix());
                if (bitmap)
                {
                    exportBestScale(bitmap, scale * curScale);
                }
            }
        }
    }

    void ScaleMap::adjustImageScale(const Definition::Ptr& rootDefine)
    {
        std::set<Definition::Ptr> shapes;
        extractAllShapes(shapes, rootDefine);

        for (auto& iter : shapes)
        {
            auto shape = fla::ptr_case<DefinitionShape>(iter);
            auto scale = getScale(shape->getId());
            exportShapeImageScales(shape, scale);
        }
    }

    void ScaleMap::exportBestScale(const Definition::Ptr& definition, float scale)
    {
        if (!definition->isRoleState() && definition->getType() != fla::DefinitionType::Scene)
        {
            auto iter = _scales.find(definition->getId());
            if (iter != _scales.end())
            {
                if (iter->second >= scale)
                {
                    return;
                }
            }
        }
        _scales[definition->getId()] = scale;

        switch (definition->getType())
        {
            case DefinitionType::Font:
                _scales[definition->getId()] = 1.0f;
                break;

            case DefinitionType::Shape:
            {
                auto shape = fla::ptr_case<DefinitionShape>(definition);
                auto bounds = shape->getBounds();
                auto maxSize = 2048;

                auto scaleX = maxSize / bounds.width;
                auto scaleY = maxSize / bounds.height;
                _scales[definition->getId()] = std::min(std::min(scaleX, scaleY), scale);
            }
            break;

            case DefinitionType::Image:
            {
                auto image = fla::ptr_case<DefinitionImage>(definition);
                if (image->isSupportScale())
                {
                    auto size = image->getSize();
                    size.width *= scale;
                    size.height *= scale;

                    real_t scaleX = ceil((size.width)) / image->getSize().width;
                    real_t scaleY = ceil((size.height)) / image->getSize().height;

                    _scales[definition->getId()] = std::min<float>(1.0, std::max(scaleX, scaleY));
                }
                else
                {
                    _scales[definition->getId()] = 1.0;
                }
            }
            break;

            case DefinitionType::Scene:
            case DefinitionType::Animation:
            case DefinitionType::Package:
            {
                auto sprite = fla::ptr_case<DefinitionAnimation>(definition);
                exportSpriteFrameScales(sprite, scale);
            }
            break;

            case DefinitionType::Role:
            {
                auto role = fla::ptr_case<DefinitionRole>(definition);
                for (auto& state : role->getStates())
                {
                    exportBestScale(state.definition, scale);
                }
            }
            break;

            default:
                break;
        }
    }

    float ScaleMap::getScale(int Id) const
    {
        auto iter = _scales.find(Id);
        if (iter != _scales.end())
        {
            return iter->second;
        }
        return 1.0f;
    }

    void ScaleMap::setScale(int Id, float scale)
    {
        _scales[Id] = scale;
    }

    void ScaleMap::unionMap(const ScaleMap& m)
    {
        for (auto iter : m._scales)
        {
            auto scale = getScale(iter.first);
            scale *= iter.second;
            _scales[iter.first] = scale;
        }
    }

    void ScaleMap::clear()
    {
        return _scales.clear();
    }

    const std::map<int, float>& ScaleMap::getScales() const
    {
        return _scales;
    }

    std::string ScaleMap::toString() const
    {
        std::stringstream stream;
        for (auto& pair : _scales)
        {
            stream << "[" << pair.first << ", " << pair.second << "]\n";
        }
        return stream.str();
    }
}
