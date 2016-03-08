//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_BASEWRITER__
#define __FLA_BASEWRITER__

#include "../fla_Definition.h"
#include "../fla_DefinitionShape.h"
#include "../fla_DefinitionAnimation.h"
#include "../fla_DefinitionScene.h"
#include "../fla_DefinitionRole.h"
#include "../fla_DefinitionImage.h"
#include "../fla_DefinitionPlaceholder.h"
#include "../fla_DefinitionFont.h"
#include "../fla_DefinitionText.h"
#include "../fla_DefinitionMorphShape.h"
#include "../fla_DefinitionPackage.h"
#include "fla_ScaleMap.h"
#include <vector>
#include <map>

namespace fla
{
    template <typename T>
    struct BaseItem
    {
        BaseItem() : scale(1.0)
        {
        }
        Definition::Ptr define;
        T data;
        float scale;
    };

    class DefinitionImage;
    class DefinitionShape;
    class DefinitionScene;
    class DefinitionRole;

    // 数据导出的基类
    template <typename T>
    class BaseWriter
    {
    public:
        BaseWriter(const Definition::Ptr& root, float frameRate);

    protected:
        float getFrameRate() const
        {
            return _frameRate;
        }
        Definition::Ptr getRoot() const
        {
            return _root;
        }

        void setScaleMap(const ScaleMap& map)
        {
            _scales = map;
        }

        const ScaleMap& getScaleMap() const
        {
            return _scales;
        }

        typedef BaseItem<T> ItemType;
        typedef std::shared_ptr<ItemType> ItemPtr;
        const std::vector<ItemPtr>& getItems() const
        {
            return _items;
        }

    protected:
        T exportDataDefine(const fla::Definition::Ptr& definition, float scale);
        void exportDefinition(const fla::Definition::Ptr& definition);

        virtual T write(const DefinitionShape::Ptr& ptr, float scale) = 0;
        virtual T write(const DefinitionMorphShape::Ptr& ptr, float scale) = 0;
        virtual T write(const DefinitionAnimation::Ptr& ptr, float scale) = 0;
        virtual T write(const DefinitionScene::Ptr& ptr, float scale) = 0;
        virtual T write(const DefinitionRole::Ptr& ptr, float scale) = 0;
        virtual T write(const DefinitionFont::Ptr& ptr, float scale) = 0;
        virtual T write(const DefinitionText::Ptr& ptr, float scale) = 0;
        virtual T write(const DefinitionImage::Ptr& ptr, float scale) = 0;
        virtual T write(const DefinitionPlaceholder::Ptr& ptr, float scale) = 0;
        virtual T write(const DefinitionPackage::Ptr& ptr, float scale) = 0;

        virtual bool isAvailable(const T& data) const = 0;

        bool computePlaceTrans(const PlaceObject& obj,
                               const AnimationFrame& prevFrame,
                               const AnimationFrame& currFrame,
                               float scale,
                               Matrix& trans);

    private:
        ItemPtr findItem(int Id);
        float findScale(int Id);
        void addItem(const T& data, const Definition::Ptr& define);

    private:
        Definition::Ptr _root;
        ScaleMap _scales;
        std::vector<ItemPtr> _items;
        std::map<int, ItemPtr> _itemMap;
        float _frameRate;
    };

    template <typename T>
    BaseWriter<T>::BaseWriter(const Definition::Ptr& root, float frameRate)
    {
        _root = root;
        _frameRate = frameRate;
    }

    template <typename T>
    void BaseWriter<T>::addItem(const T& data, const Definition::Ptr& define)
    {
        auto item = findItem(define->getId());
        if (item)
        {
            item->data = data;
        }
        else
        {
            item = ItemPtr(new ItemType());
            item->define = define;
            item->data = data;
            item->scale = findScale(define->getId());
            _items.push_back(item);
            _itemMap[define->getId()] = item;
        }
    }

    template <typename T>
    typename BaseWriter<T>::ItemPtr BaseWriter<T>::findItem(int Id)
    {
        auto iter = _itemMap.find(Id);
        if (iter != _itemMap.end())
        {
            return iter->second;
        }
        return ItemPtr();
    }

    template <typename T>
    float BaseWriter<T>::findScale(int Id)
    {
        return _scales.getScale(Id);
    }

    template <typename T>
    T BaseWriter<T>::exportDataDefine(const fla::Definition::Ptr& definition, float scale)
    {
        T data;
        switch (definition->getType())
        {
            case DefinitionType::Shape:
                data = write(fla::ptr_case<DefinitionShape>(definition), scale);
                break;

            case DefinitionType::Animation:
                data = write(fla::ptr_case<DefinitionAnimation>(definition), scale);
                break;

            case DefinitionType::Scene:
                data = write(fla::ptr_case<DefinitionScene>(definition), scale);
                break;

            case DefinitionType::Role:
                data = write(fla::ptr_case<DefinitionRole>(definition), scale);
                break;

            case DefinitionType::Font:
                data = write(fla::ptr_case<DefinitionFont>(definition), scale);
                break;

            case DefinitionType::Text:
                data = write(fla::ptr_case<DefinitionText>(definition), scale);
                break;

            case DefinitionType::MorphShape:
                data = write(fla::ptr_case<DefinitionMorphShape>(definition), scale);
                break;

            case DefinitionType::Image:
                data = write(fla::ptr_case<DefinitionImage>(definition), scale);
                break;

            case DefinitionType::Placeholder:
                data = write(fla::ptr_case<DefinitionPlaceholder>(definition), scale);
                break;

            case DefinitionType::Package:
                data = write(fla::ptr_case<DefinitionPackage>(definition), scale);
                break;

            default:
                break;
        }
        return data;
    }

    template <typename T>
    void BaseWriter<T>::exportDefinition(const fla::Definition::Ptr& define)
    {
        auto item = findItem(define->getId());

        // 已经导出了，就立即返回
        if (item)
        {
            return;
        }

        auto result = define;
        if (define->getType() == DefinitionType::Shape)
        {
            auto shape = fla::ptr_case<DefinitionShape>(define);
            if (shape->getShape().isStyleInvisible())
            {
                result = DefinitionPlaceholder::createWithOriginal<DefinitionShape>(shape);
            }
        }
        T data = exportDataDefine(result, findScale(result->getId()));
        if (isAvailable(data))
        {
            addItem(data, result);
        }
    }

    template <typename T>
    bool BaseWriter<T>::computePlaceTrans(const PlaceObject& obj,
                                          const AnimationFrame& preveFrame,
                                          const AnimationFrame& currentFrame,
                                          float scale,
                                          Matrix& trans)
    {
        if (obj.hasTrans())
        {
            auto iter = currentFrame.findWithDepth(obj.depth());
            auto item = findItem(iter->characterID());
            if (item)
            {
                trans = Matrix::matrixScale(obj.trans(), scale / item->scale);
            }
            else
            {
                trans = obj.trans();
            }
            return true;
        }
        else
        {
            auto iter1 = preveFrame.findWithDepth(obj.depth());
            if (iter1 != preveFrame.end())
            {
                auto iter2 = currentFrame.findWithDepth(obj.depth());
                if (iter1->characterID() != iter2->characterID())
                {
                    auto item1 = findItem(iter1->characterID());
                    auto item2 = findItem(iter2->characterID());

                    if (item1 && item2 && item1->scale != item2->scale)
                    {
                        trans = Matrix::matrixScale(iter2->trans(), scale / item2->scale);
                        return true;
                    }
                }
            }
        }
        return false;
    }
}

#endif
